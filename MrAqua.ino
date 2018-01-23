// iAqua Aquarium Controller w/ iPhone-like Interface
// Written by Dan Cunningham, aka AnotherHobby @ plantedtank.net
// Various updates added by Ryan Truss, aka MrMan
// Much code was swiped, modified, and integrated or otherwise inspired from other public works
// All code is public domain, feel free to use, abuse, edit, and share
// Written for Arduino Mega 2560
//
// MrAqua v2.5.2
// -Updated feeding to allow not including outlets in feeding routine
// -Updated homescreen ATO display (empty reservoir shows as alarm instead of always displaying)
//
// MrAqua v2.5.0
// -Added watchdog to reset MCU on code freezing
// -Fixed bug where aux1 in timer mode would turn off aux2
// -Updated feeding screen/home screen to show exact time remaining instead of <x minutes
// -Swapped CO2 and Heater pin/icon locations, search for "swapped" to find all instaces and revert
// -Added code to use Serial2 to send/receive information from remote LED module (send LED values, 
//  fan state, reading LED heatsink temperature and request for LED values)
//
// MrAqua v2.4.0
// -Fix power schedule screen (45 degree text is unreadable)
// -Update auto-dimming to use an idle after x minutes timer instead of reading ambient light
// -Home screen now shows all 3 temperatures at the same time if more than just water sensor is enabled
//
// MrAqua v2.3.6
// -Add ability for Aux1 and Aux2 to be used as repeated timer rather than single 24Hr schedule
// -Updated some of the check boxes to on/off icon to fit with theme of the program
// -Updated power alarm behaviours during feeding to avoid devices turning on/off when they shouldn't
//
// MrAqua v2.3.5
// -Fixed startup where outputs would be ON but display showing them OFF
// -Added manual ATO turn-on by pressing section on home screen (runs for max run time)
//
// MrAqua v2.3.3 / 2.3.4
// -Fixed some bugs including heatsink temp sensor using wrong pin, dosing amount limits and PCB temp 
//  sensor not able to read in degrees F
//
// MrAqua v2.3.2
// -Added seperate screen function for IR lights using up/down arrows
// -Dosing alarms now trigger the start but main loop turns them off.  This way the program doesn't
//  freeze when it starts to dose
// -Corrected heatsink temp sensor to use correct device address
//
// MrAqua v2.3.1
// -Added code from alphabeta to add a second on/off schedule for lights
// -Updated light values/system so stored values are always 0-100
// -Updated home screen dosing to correctly draw tubes and not allow remaining volume to go below 0
//
// MrAqua 
// -Updated feeding routine to only toggle filter/pump/aux outputs
// -Added graph display for LED channels 
// -Added routine writeToLED(channel,value) to handle writing to either PCA or Mega PWM pins
// -Modified LED PWM code to optionally use PCA9685 for 12-bit dimming
// -Added 5th/6th LED channel, moved EEPROM for LED values to 400's
// -Added lunar cycle control
// -Added probe settings menu to enable/disable temp sensors and change display units between C and F
// -Added sub-settings menus for sensors to control when fans turn on/off (external fan 
//  controlled by heatsink sensor, internal fan controlled by internal temp) or heater in case of
//  probe 1.  Also added calibration offset for probes
// -Changed feeding, update time and screen dim tracking to using RTC instead of millis 
//  (millis only used for tracking touch timing for better resolution)
// -Changed code for 3 pumps, reworked schedule and setting screens to select a pump and then
//  individual pump dose amounts
// -Added code for ATO
// -Changed LED color setting to bargraph (0-100%) instead of up/down button
// -Added color setting menu for changing bargraph colors
// -Added routine for sending commands to sat+ with the updated bargraphs
// -switched RTClib to DS1307RTC library
// -switched to sdfat and utft_sdraw library for accessing SD card files (can use larger SD 
//  cards and has faster loading speeds)
// -Added read of displayInCelcius to startup
// -Added boolean displayIn12Hr to change clock to 24Hr/12Hr
//
// Original iAqua revision documentation:
// CURRENT VERSION 1.0.4
// - the smart startup routine has been reworked and fixed by robsworld78 at The Planted Tank forums!
// - added a first run routine that will zero out all EEPROM data that is needed by iAqua
//
// VERSION 1.0.3
// - fixed smartstartup routine bugs
// - fixed dosing display when resevoir goes negative due to forgettig to hit fill
// - added robsworld78 at The Planted Tank's PWM smart startup lighting code
// - fixed issue when temp turned red, and then turned feeding time red
//
// VERSION:  1.0.2
// - more accurate math for how doses were calcualted on home screen
// - updated power schedules to update home screen immediately
// - day name was off using new RTC and Time library
//
// VERSION:  1.0.1
// - created smart startup routine
// - fixed math bug with dosing pump speed saving to eeprom
// - changed PWM pins for dosing pumps to make room for RGBW PWM pins
// - changed from previous RTC library to RTClib.h
//
// VERSION:  1.0
// - initial version
//
// EEPROM locations (saved settings)
// SPACE // DESCRIPTION
// 0 // 
// 1 // feeding enable filter
// 2 // feeding enable circ
// 3 // feeding enable heat
// 4 // feeding enable co2
// 5 // feeding enable aux 1
// 6 // feeding enable aux 2
// 7 // feeding minutes setting
// 8 // feeding  light 1 (0 off, 1 on)
// 9 // feeding pwr light 2 (0 off, 1 on)
// 10 // feeding pwr filter (0 off, 1 on)
// 11 // feeding pwr circ (0 off, 1 on)
// 12 // feeding pwr heat (0 off, 1 on)
// 13 // feeding pwr co2 (0 off, 1 on)
// 14 // feeding pwr aux 1 (0 off, 1 on)
// 15 // feeding pwr aux 2 (0 off, 1 on)
// 16 // NOT USED
// 17 // heater off temp
// 18 // heater on temp
// 19 // NOT USED
// 20 // pump 1 dose in mL
// 21 // pump 2 dose in mL
// 22 // pump 3 dose in mL
// 23 // pump 1 sec/ml
// 24 // pump 2 sec/ml
// 25 // pump 3 sec/ml
// 26 // dosing reseviors capacity in mL
// 27 // 
// 28 // screen:  return home
// 29 // screen:  autodim level
// 30 // screen:  autodim seconds
// 31 // screen:  brightness if no dim
// 32 // pump 1 remaining volume high byte ^10th
// 33 // pump 1 remaining volume low byte
// 34 // pump 2 remaining volume high byte ^10th
// 35 // pump 2 remaining volume low byte
// 36 // pump 3 remaining volume high byte ^10th
// 37 // pump 3 remaining volume low byte
// ... //
// 40 // ATO Enabled
// 41 // Reservoir switch Enabled
// 42 // Low level wait time in minutes
// 43 // Max run-time / 10
// 44 // ATO alarm flagged
// ... //
// 50 // Temp sensor 1 installed (water)
// 51 // Temp sensor 2 installed (heatsink)
// 52 // Internal sensor installed (MCP9701)
// 53 // Heatsink fan on temperature
// 54 // Heatsink fan off temperature
// 55 // Internal fan on temperature
// 56 // Internal fan off temperature
// 57 // Display in celcius?
// 58 // sensor 1 calibration offset
// 59 // sensor 2 calibration offset
// 60 // sensor 3 calibration offset
// 61 // display sensor 1 on home screen
// 62 // display sensor 2 on home screen
// 63 // display sensor 3 on home screen
// ... // 
// 70 // Lunar cycle enabled
// 71 // Clouds enabled
// 72 // Cloud start hour
// 73 // Cloud start minute
// 74 // Cloud run hours
// 75 // Cloud run minutes
// 76 // Cloud channels enabled (bit 0 = chan1, bit 1 = chan2...)
// ... //
// 80 // bar 1 color
// 81 // bar 2 color
// 82 // bar 3 color
// 83 // bar 4 color
// 84 // bar 5 color
// 85 // bar 6 color
// 86 // bar 7 color
// 87 // bar 8 color
// 88 // bar 9 color
// ... //
// 100-139 // power scheudle
// 220-243 // light ramp schedule
// 280-284 // light bar colors
// 300 // pump1 onHour
// 301 // pump1 onMin
// 302 // pump1 SUN
// 303 // pump1 MON
// 304 // pump1 TUE
// 305 // pump1 WED
// 306 // pump1 THUR
// 307 // pump1 FRI
// 308 // pump1 SAT
// 309-317 // pump2
// 318-326 // pump3
// ... //
// 400+ // LED values

#include <avr/wdt.h> //added for WDT
#include <Wire.h> // needed by tons of stuff
#include <EEPROM.h>  // used to store and retrieve settings from memory
#include <UTFT.h>  // used to interface with the TFT display
#include <SdFat.h>
#include <UTFT_SdRaw.h>
#include <UTouch.h>  // used to interface with the touch controller on the TFT display
#include <DS1307RTC.h>
//#include <DS3232RTC.h>
#include <TimeLib.h>
#include <TimeAlarms.h>  // used to power schedules
#include <IRremote.h>  // used to send IR commands to the light, LED must be on pin 9
#include <OneWire.h> // network library to communicate with the DallasTemperature sensor, 
#include <DallasTemperature.h>  // library for the Temp sensor itself
#include <Adafruit_PWMServoDriver.h> //PCA9865

UTFT myGLCD(SSD1289,38,39,40,41); // start up an instance of the TFT screen
UTouch myTouch(46,45,44,43,42);  // start up an instance of for touch
//UTouch myTouch(6, 5, 4, 3, 2); // For standard TFT shield

// file system object
SdFat sd;
const byte ChipSelect = 53; // For TFT Shield
UTFT_SdRaw myFiles(&myGLCD);

// Declare which fonts we will be using
extern uint8_t Sinclair_S[];
extern uint8_t arial_bold[];

//initialize PCA9865
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// define relay pins
const int pwrLight1Pin = A0;
const int pwrLight2Pin = A1;
const int pwrFilterPin = A2;
const int pwrCircPin = A3;
//const int pwrHeatPin = A4;  //normal operation
//const int pwrCO2Pin = A5;   //normal operation
const int pwrHeatPin = A5;//co2/heater pins swapped
const int pwrCO2Pin = A4; //co2/heater pins swapped
const int pwrAux1Pin = A6;
const int pwrAux2Pin = A7;

//define misc pins
const int lightSensorPin = A8;  // analog pin for the ambient light sensor
const int pressureSensorPin = A9;  // analog pin for the CO2 pressure sensor
const int fan1Pin = A11;
const int fan2Pin = A12;
const int internalTempPin = A13;
const int ATOFloatPin = A14;
const int TankFloatPin = A15;
const int screenBrightPin = 8; // pwm pin for the LCD backlight
//define pump pins
const int dosingPump1 = 10;
const int dosingPump2 = 11;
const int dosingPump3 = 12;
const int ATOPumpPin = 13;
// define RGBW PWM pins
const int led1Pin = 2;
const int led2Pin = 3;
const int led3Pin = 4;
const int led4Pin = 5;
const int led5Pin = 6;
const int led6Pin = 7;

// Pins for temperature sensor
#define ONE_WIRE_BUS_W 47  //water sensor on pin 47
#define ONE_WIRE_BUS_H 49  //Heatsink sensor on pin 49

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWireW(ONE_WIRE_BUS_W);
OneWire oneWireH(ONE_WIRE_BUS_H);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensorW(&oneWireW);
DallasTemperature sensorH(&oneWireH);

// Device address variables
DeviceAddress waterSensor;
DeviceAddress heatsinkSensor;

// create an IR instance
IRsend irsend;

byte dispScreen=0;    // screens are listed below
//1-home
//    2-feeding
//    3-power
//    4-settings
//        5 - Light Settings
//        6 - clock
//        7 - feed settings
//        18- sensor settings
//            8 - heater settings
//            19- heatsink fan settings
//            20- internal fan settings
//        9 - Schedule
//            11 - Power schedule
//                12 - Power item
//            15 - Dosing
//            13 - Light ramps schedule screen
//                14 - light ramp schedule
//        10 - Dosing settings (index 1-3 for pump#)
//        16 - Screen settings
//        17 - ATO settings
//        21 - Lunar settings
//        22 - Light bargraph color settings
//        23 - LED graph
//        24 - Light Settings for IR lights

byte scheduleItem; // track which item is being scheduled
byte currentLightMode=0;  //0=high sun, 1=mid sun, 2=low sun, 3=moon, 4=transition, 5=unknown
byte lightEditing=0;  // track if we are actively editing lights

// the next 5 variables will be set at the start of a lighting fade
int fadeDurationSeconds = 0; 
unsigned long fadeStartingSeconds = 0;
unsigned long fadeTimeLeft;
boolean fadeInProgress = false;
byte fadeFromMode = 0;  //0=high sun, 1=mid sun, 2=low sun, 3=moon
byte fadeToMode = 0;  //0=high sun, 1=mid sun, 2=low sun, 3=moon

struct RGBW // for storing light intensity values
{
  unsigned int chan1;
  unsigned int chan2;
  unsigned int chan3;
  unsigned int chan4;
  unsigned int chan5;
  unsigned int chan6;
};
typedef struct RGBW LightColor;

LightColor currentColor = {
  0,0,0,0,0,0}; // The current color of the light (used for fading)
LightColor lastColor = {
  0,0,0,0,0,0};   // The previous color of the light (used for fading)
LightColor targetColor = {
  0,0,0,0,0,0}; // The target color of the light (used for fading)
LightColor tempColor = {
  0,0,0,0,0,0}; // The temporary color of the light (used for updating sat+)

LightColor lightHighSun = {
  0,0,0,0,0,0}; // store the RGBW values for the CS+ M1 button
LightColor lightMidSun = {
  0,0,0,0,0,0}; // store the RGBW values for the CS+ M2 button 
LightColor lightLowSun = {
  0,0,0,0,0,0}; // store the RGBW values for the CS+ M3 button 
LightColor lightMoon = {
  0,0,0,0,0,0}; // store the RGBW values for the CS+ M4 button 
  
//red, green, blue, white, yellow, violet, aqua
const unsigned int VGAColor[] = {0xF800, 0x07E0, 0x001F, 0xFFFF, 0xFFE0, 0xF81F, 0x07FF};

//store colours for bargraphs
byte barColors[6] = {0,1,2,3,4,5};
byte selectedChan = 0; // used for tracking which channel is selected when changing colors

// used for time
tmElements_t prevRTC, saveRTC;
boolean displayIn12Hr = true;

// used for storing power states of relays
struct PWR
{  
  byte pwrLight1;
  byte pwrLight2;
  byte pwrFilter;
  byte pwrCirc;
  byte pwrHeat;
  byte pwrCO2;
  byte pwrAux1;
  byte pwrAux2;
} 
feedPower, preFeedPower, globalPower;

// used for storing power states of relays
struct FEED
{  
  byte pwrLight1;
  byte pwrLight2;
  byte pwrFilter;
  byte pwrCirc;
  byte pwrHeat;
  byte pwrCO2;
  byte pwrAux1;
  byte pwrAux2;
} 
feedSetting;

// holds the schedule for power relays and light ramping
struct PWRSCHED
{  
  byte active;
  byte onHour;
  byte onMinute;
  byte offHour;
  byte offMinute;
  byte timer;
} 
schedLights1,schedLights1s2,schedLights2,schedLights2s2,schedCirc,schedCo2,schedAux1,schedAux2,
  ramp1,ramp2,ramp3,ramp4,ramp5,ramp6;
unsigned long aux1TimerStart = 0;
unsigned long aux1TimerFinish = 0;
unsigned long aux2TimerStart = 0;
unsigned long aux2TimerFinish = 0;
boolean aux1TimerState = false;
boolean aux2TimerState = false;

// holds the schedulin for 2 dosing pumps
struct PUMPSCHED
{  
  byte onHour;
  byte onMinute;
  byte Sunday;
  byte Monday;
  byte Tuesday;
  byte Wednesday;
  byte Thursday;
  byte Friday;
  byte Saturday;
} 
pump1, pump2, pump3;

int x, y; //touch coordinates

//Feeding variables
boolean feedingActive=false; // track if feeding is currently active
byte feedingMins=0; // stores how long the feeding should be
time_t lastFeedingTime; //time of last feeding
time_t startFeedingTime;

// Sensor variables
boolean displayInC = true;
boolean sensor1Enabled = true; // water
boolean sensor2Enabled = false; // heatsink
boolean sensor3Enabled = false; // internal
boolean displaySensor1 = true;
boolean displaySensor2 = true;
boolean displaySensor3 = false;
byte sensorToDisplay = 1;
float temperature = 0;  // water temperature
float temperature2 = 0;  // heatsink temperature
float temperature3 = 0; // internal temperature
float sensor1Calibration = 0.0; // calibration offset for sensor 1 (water)
float sensor2Calibration = 0.0; // calibration offset for sensor 2 (heatsink)
float sensor3Calibration = 0.0; // calibration offset for sensor 3 (internal)
boolean fan1status = false;
boolean fan2status = false;
byte internalFanOnTemp = 45;
byte internalFanOffTemp = 40;
byte heatsinkFanOnTemp = 40;
byte heatsinkFanOffTemp = 45;

//heater variables
boolean heaterWarning=false; // keeps track if there is an active overheating issue
boolean heaterWarningCleared=true; // keeps track if we clear the warning, impacts home screen icon
byte heatOffTemp = 30;
byte heatOnTemp = 25;

//dosing pump variables
boolean pump1State = false;
boolean pump2State = false;
boolean pump3State = false;
unsigned long pump1StartMillis = 0;
unsigned long pump2StartMillis = 0;
unsigned long pump3StartMillis = 0;
unsigned long pump1millis = 0;
unsigned long pump2millis = 0;
unsigned long pump3millis = 0;

//ATO variables
boolean ATOEnabled = true;
boolean ResSwitchEnabled = false;
boolean WaterLevel = HIGH;
boolean ReservoirLevel = HIGH;
boolean ATOAlarm = false;
boolean ATOPumpState = LOW;
time_t ATOStartTime = 0;
time_t ATOPumpStartTime = 0;
unsigned long ATORunTime = 120;    //seconds to run ATO pump for before flagging an alarm
unsigned long ATOWaitTime = 60; //time to wait in minutes

// various millis to keep track of touch timing
unsigned long prevMillisTouch = 0;
unsigned int touchWaitTime = 350;
#define LONG_WAIT 500
#define MEDIUM_WAIT 150
#define SHORT_WAIT 25

// time variables to track clock updating, dimming timing and time to return home from a menu
time_t lastUpdateTime = 0; // track 5 seconds for refreshing clock and temp
time_t lastCheckTime = 0; // track 1 second for checking ATO and feeding
time_t dimTime = 0; // used for brightness adjustment
time_t homeTime = 0; // used for returning home after configured time

// screen settings corresponding to eeprom values 28-31
byte screenRetHome, screenDimLevel, screenDimSec, screenBrightMem, screenBrightness;
boolean idleScreenState = false;

byte backLight = 255;  // startup brightness to 100%
boolean backlightTouch = true; // initial setting of true to start the screen bright after boot

// if you have a Current Satellite Plus, this is true
// if you are controlling your lights directly with PWM, this is false
boolean lightCSP = true;
int maxIR = 100; //using e-series

//If PCA9865 is installed this is true, otherwise it is false to use Arduino PWM pins
boolean PCA9685Installed = true;

//variable for Serial2 communication with remote arduino
#define INPUT_SIZE 20
char input[INPUT_SIZE+1];

/*
// REMOTE CONTROL CODES FOR CURRENT SATELLITE PLUS
const unsigned long POWER = 0x20DF02FD;
const unsigned long FULLORANGE = 0x20DF3AC5;
const unsigned long FULLLIGHTBLUE = 0x20DFBA45;
const unsigned long FULLPURPLE = 0x20DF827D;
const unsigned long FULLWHITE = 0x20DF1AE5;
//const unsigned long FULLYELLOW = 0x20DF9A65;
const unsigned long FULLSPECTRUM = 0x20DF9A65;
const unsigned long FULLBLUE = 0x20DFA25D;
const unsigned long REDUP = 0x20DF2AD5;
const unsigned long REDDOWN = 0x20DF0AF5;
const unsigned long GREENUP = 0x20DFAA55;
const unsigned long GREENDOWN = 0x20DF8A75;
const unsigned long BLUEUP = 0x20DF926D;
const unsigned long BLUEDOWN = 0x20DFB24D;
const unsigned long WHITEUP = 0x20DF12ED;
const unsigned long WHITEDOWN = 0x20DF32CD;
const unsigned long M1 = 0x20DF38C7;
const unsigned long M2 = 0x20DFB847;
const unsigned long M3 = 0x20DF7887;
const unsigned long M4 = 0x20DFF807;*/

// REMOTE CONTROL CODES FOR ECOXOTIC E-SERIES
const unsigned long POWER = 0x20DF02FD;
const unsigned long FULLSPECTRUM = 0x20DFAA55;
const unsigned long ENTER = 0x20DFA25D;
const unsigned long RESUME = 0x20DF22DD;
const unsigned long DYNAMICLIGHTNING = 0x20DFA857;
const unsigned long DYNAMICCLOUD = 0x20DF6897;
const unsigned long REDUP = 0x20DF0AF5;
const unsigned long REDDOWN = 0x20DF38C7;
const unsigned long GREENUP = 0x20DF8A75;
const unsigned long GREENDOWN = 0x20DFB847;
const unsigned long BLUEUP = 0x20DFB24D;
const unsigned long BLUEDOWN = 0x20DF7887;
const unsigned long WHITEUP = 0x20DF32CD;
const unsigned long WHITEDOWN = 0x20DFF807;
const unsigned long M1 = 0x20DF58A7; //Daylight on remote
const unsigned long M2 = 0x20DF9867;
const unsigned long M3 = 0x20DF18E7;
const unsigned long M4 = 0x20DFD827; //Moon on remote

// selected lights mode buttons for lights screen
char *lightModeS[] = {
  "5hsunS.raw","5msunS.raw","5lsunS.raw","5moonS.raw"};
// off lights mode buttons for lights screen
char *lightModeF[] = {
  "5hmsunF.raw","5lsunF.raw","5moonF.raw"};
// neutral lights mode buttons for lights screen
char *lightMode[] = {
  "5hsun.raw","5msun.raw","5lsun.raw","5moon.raw"};

// editing buttons for the lights screen, disabled and enabled
char *lightEdit[] = {
  "5editF.raw", "5editN.raw"};
char *lightSave[] = {
  "5saveF.raw", "5saveN.raw"};
char *lightResync[] = {
  "5resynF.raw", "5resynN.raw"};
char *lightCancel[] = {
  "5canF.raw", "5canN.raw"};
  
// lights adjustment buttons for lights screen (RGBW up and down) 
char *lightWhite[] = {
  "5Wup.raw", "5Wdown.raw"};
char *lightRed[] = {
  "5Rup.raw", "5Rdown.raw"};
char *lightGreen[] = {
  "5Gup.raw", "5Gdown.raw"};
char *lightBlue[] = {
  "5Bup.raw", "5Bdown.raw"};
char *lightGray[] = {
  "5Fup.raw", "5Fdown.raw"}; // disabled button

// large power buttons for the power screen and the feeding configuration screen, off and on
char *pwrLightIcon[] = {
  "3light_F.raw","3light_N.raw"};
char *pwrFilterIcon[] = {
  "3filt_F.raw","3filt_N.raw"};
char *pwrCircIcon[] = {
  "3circ_F.raw","3circ_N.raw"};
char *pwrHeatIcon[] = {
  "3heat_F.raw","3heat_N.raw"};
char *pwrCO2Icon[] = {
  "3co2_F.raw","3co2_N.raw"};
char *pwrAux1Icon[] = {
  "3aux1_F.raw","3aux1_N.raw"};
char *pwrAux2Icon[] = {
  "3aux2_F.raw","3aux2_N.raw"};

// on off power dot under each power button on the power screen and feeding config screen
char *pwrDot[] = {
  "3dotR.raw","3dotG.raw"};

// small power icons for the home screen, off and on
char *pwrLightIconS[] = {
  "1lightF.raw","1lightN.raw"};
char *pwrFilterIconS[] = {
  "1filtF.raw","1filtN.raw"};
char *pwrCircIconS[] = {
  "1circF.raw","1circN.raw"};
char *pwrHeatIconS[] = {
  "1heatF.raw","1heatN.raw"};
char *pwrCO2IconS[] = {
  "1co2F.raw","1co2N.raw"};
char *pwrAux1IconS[] = {
  "1aux1F.raw","1aux1N.raw"};
char *pwrAux2IconS[] = {
  "1aux2F.raw","1aux2N.raw"};

// small light mode icons for home screen
char *lightModeSm[] = {
  "1hsun.raw","1msun.raw","1lsun.raw","1moon.raw"};
  
//moon images 
// 0 = new moon, 1 = New Crescent, 2 = First Quarter, 3 = Waxing Gibbous, 4 = Full Moon, 
// 5 = Waning Gibbous, 6 = Last Quarter, 7 = Old Crescent
char *moonImages[] = {
  "21new.raw","21ncres.raw","21firstq.raw","21waxg.raw","21full.raw","21wang.raw",
  "21lastq.raw","21ocres.raw"};

// 24 pixel up and down arrow buttons used on several screens
char *arrowButton[] = {
  "24whUp.raw", "24whDn.raw"};

// enabled or not enabled small check boxes for the power schedule screen
char *schedActive[] = {
  "11dis.raw","11enab.raw"};
// enabled or not enabled large check boxes for the power item schedule screen
char *schedActiveB[] = {
  "11disB.raw","11enabB.raw"};
char *schedOnOff[] = {
  "3off.raw","3on.raw"};
// high/low water level display icon
char *WaterIcon[] = {
  "1wlow.raw","1whigh.raw"};
  
//watchdog timer definitions/variables  
unsigned long resetTime = 0;
#define TIMEOUTPERIOD 10000                   // You can make this time as long as you want
#define doggieTickle() resetTime = millis();  // This macro will reset the timer
void(* resetFunc) (void) = 0;                 //declare reset function @ address 0

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

//              END GLOBAL VARIABLES                      //

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void watchdogSetup()
{
  cli();  // disable all interrupts
  wdt_reset(); // reset the WDT timer
  MCUSR &= ~(1<<WDRF);  // because the data sheet said to
  /*
  WDTCSR configuration:
  WDIE = 1 :Interrupt Enable
  WDE = 1  :Reset Enable - I won't be using this on the 2560
  WDP3 = 1 :For 2000ms Time-out
  WDP2 = 0 :bit pattern is 
  WDP1 = 0 :0111  change this for a different
  WDP0 = 1 :timeout period.
  */
  // Enter Watchdog Configuration mode:
  WDTCSR = (1<<WDCE) | (1<<WDE);
  // Set Watchdog settings: interrupte enable, 1001 for timer
  WDTCSR = (1<<WDIE) | (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
  sei();
  Serial.println(F("\nFinished watchdog setup"));  // just here for testing
}

ISR(WDT_vect) // Watchdog timer interrupt.
{ 
  if(millis() - resetTime > TIMEOUTPERIOD){
    resetFunc();     // This will call location zero and cause a reboot.
  }
}

int freeRam ()
{
  // Returns available SRAM
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  Wire.begin();
  delay(100);
  
  watchdogSetup();
  
  pinMode(48,OUTPUT);
  digitalWrite(48,HIGH);
  
  // set default values for the first ever run
  firstRunSetup();

  // initiate the screen and touch 
  myGLCD.InitLCD(PORTRAIT);
  myTouch.InitTouch(PORTRAIT);
  myTouch.setPrecision(PREC_MEDIUM);

  // init SD card
  sd.begin(ChipSelect, SPI_FULL_SPEED);
  
  // boot up logo
  analogWrite(screenBrightPin, 255);
  myGLCD.clrScr();
  myFiles.load(26, 110, 188, 72, "iAqua.raw");
  myGLCD.setColor(255,255,255);
  myGLCD.setFont(arial_bold);
  myGLCD.print(F("v2.5.1"), CENTER, 292);
  Serial.println(F("v2.5.1"));
  
  //Check RTC status
  setSyncProvider(RTC.get);
  delay(100);
  if(timeStatus()!= timeSet)
  {
    Serial.print(F("Unable to sync with RTC"));
    saveRTC.Year = 45;
    saveRTC.Month = 1;
    saveRTC.Day = 1;
    saveRTC.Hour = 6;
    saveRTC.Minute = 0;
    saveRTC.Second = 0;
    RTC.set(makeTime(saveRTC));
    setTime(makeTime(saveRTC));
    delay(500);
  }
  lastFeedingTime = now(); //not storing feeding time in eeprom due to high rate of writing
  lastUpdateTime = now();
  lastCheckTime = now();
  
  // Start PCA9865
  if(PCA9685Installed == true)
  {
    pwm.begin();
    pwm.setPWMFreq(120);
  }
  // used for PWM lighting control
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);

  // set all pin modes for output and inputs
  pinMode(pwrLight1Pin, OUTPUT);
  pinMode(pwrLight2Pin, OUTPUT);
  pinMode(pwrFilterPin, OUTPUT);
  pinMode(pwrCircPin, OUTPUT);
  pinMode(pwrHeatPin, OUTPUT);
  pinMode(pwrCO2Pin, OUTPUT);
  pinMode(pwrAux2Pin, OUTPUT);
  pinMode(pwrAux1Pin, OUTPUT);
  
  pinMode(screenBrightPin, OUTPUT);
  pinMode(lightSensorPin, INPUT);
  pinMode(pressureSensorPin, INPUT);

  pinMode(dosingPump1, OUTPUT);
  pinMode(dosingPump2, OUTPUT);
  pinMode(dosingPump3, OUTPUT);
  pinMode(ATOPumpPin,OUTPUT);
  pinMode(ATOFloatPin,INPUT);
  pinMode(TankFloatPin,INPUT);
  digitalWrite(dosingPump1,LOW);
  digitalWrite(dosingPump2,LOW);
  digitalWrite(dosingPump3,LOW);
  digitalWrite(ATOPumpPin,LOW);
  
  pinMode(internalTempPin,INPUT);
  digitalWrite(fan1Pin,LOW);
  digitalWrite(fan2Pin,LOW);
  pinMode(fan1Pin,OUTPUT);
  pinMode(fan2Pin,OUTPUT);

  sensorW.begin();                       //start up temperature library
  sensorW.getAddress(waterSensor, 0);    //get addresses of temperature sensor
  sensorH.begin();                       //start up temperature library
  sensorH.getAddress(heatsinkSensor, 0); //get addresses of temperature sensor  

  // get bargraph colors
  if (lightCSP==false)
  {
    readBargraphColors();
  }
  
  // get screen settings from eeprom
  readScreenSettings();
  analogWrite(screenBrightPin, screenBrightness); // turn up screen brightness right away
  
  // get feeding settings from EEPROM
  readFeedSettings();
  
  // Read ATO settings
  readATOSettings();
  
  //Check which temp sensors are enabled and their settings
  readSensorSettings();

  // read in power schedule
  readPowerSchedule();

  // read in light ramping schedule
  readRampSchedule();

  // read in the dosing schedule
  readDosingSchedule();

  // synchronize the lights and read in the saved settings
  resyncLights();

  // create all alarams
  updateAlarms();

  // start up all power and set lighting mode according to schedudule
  smartStartup();
  
  delay(1400);
  
  // Print available SRAM for debugging, comment out if you want
  Serial.print(F("SRAM: "));
  Serial.println(freeRam());

  // display home screen
  checkTemp(); //check temperature before drawing to screen
  checkATO(); //check ato status before drawing to screen
  screenHome();  
  
  dimTime = now(); // update millis to keep screen bright
  Serial.println(F("\nEnd of setup."));
  Serial2.print(F("Initialized."));
}

void loop()
{
  unsigned long currentMillis = millis(); // get current millis
  time_t currentTime = now();

  //check temperature every 10 seconds
  if(now() - lastUpdateTime >= 10)
  {
    lastUpdateTime=now();
    checkTemp();
  }
  //check ATO/feeding and update time once per second
  if(now() != lastCheckTime)
  {
    lastCheckTime=now();
    updateTimeDate(false);//passing false results in updating screen only if time or date has changed
    checkATO();
    checkFeeding();
  }
  
  //Check status of current light ramp if applicable
  checkLightRamp();
  
  // check for touch events
  if (myTouch.dataAvailable())
  {
    if (currentMillis - prevMillisTouch > touchWaitTime) // make sure it's been .X sec between touches
    {
      // set backlight touch if not already set and turn up brightness
      if (backlightTouch==false) // backlight touch is for adjusting brightness after touch
      {
        Serial.println(F("Setting backlight to Bright value"));
        backLight = map(screenBrightMem,1,10,10,255);
        analogWrite(screenBrightPin, backLight);
        backlightTouch=true;
      }
      prevMillisTouch=currentMillis; // reset the touch timer
      dimTime = currentTime; // reset screen dim timer
      homeTime = currentTime; // reset return home timer
      processMyTouch();
    }
  }
  
  // adjust brightness automatically unless touch event
  unsigned long pastSeconds;
  if (screenDimSec!=0) // if set to 0, we won't dim
  {
    if (screenDimLevel!=0) // if set to 0, we won't dim
    {
      if (backlightTouch==true)
      {
        pastSeconds = (currentTime - dimTime);
        if (pastSeconds > screenDimSec)
        {
          Serial.println(F("Reducing backlight to dim level"));
          backlightTouch=false;
          idleBrightness();
        }
      }
    }
  }

  // if we aren't on the home or feeding screen, we return after preset time of no interaction
  if (screenRetHome != 0) // if set to 0, we don't return home
  {
    if ((dispScreen!=1)&&(dispScreen!=2))
    {
      pastSeconds = (currentTime - homeTime);
      if (pastSeconds > (60*screenRetHome)) 
      {
        Serial.println(F("Returning to home"));
        if (dispScreen==9) updateAlarms(); // this will rebuild all of the schedules
        if (dispScreen==5)
        {
          smartStartupRamp();
          setStartupLighting();
        }
        screenHome();
        touchWaitTime = LONG_WAIT;
      }
    }
  }
  
  //Check dosing pumps
  if(pump1State)
  {
    if(currentMillis > pump1StartMillis + pump1millis)
    {
      pump1State = false;
      analogWrite(dosingPump1, 0);
      Serial.print(F("Pump1 done.\n"));
      if(dispScreen == 10)myFiles.load(92, 170, 48, 48, "10test.raw",2);
    }
  }
  if(pump2State)
  {
    if(currentMillis > pump2StartMillis + pump2millis)
    {
      pump2State = false;
      analogWrite(dosingPump2, 0);
      Serial.print(F("Pump2 done.\n"));
      if(dispScreen == 10)myFiles.load(92, 170, 48, 48, "10test.raw",2);
    }
  }
  if(pump3State)
  {
    if(currentMillis > pump3StartMillis + pump3millis)
    {
      pump3State = false;
      analogWrite(dosingPump3, 0);
      Serial.print(F("Pump3 done.\n"));
      if(dispScreen == 10)myFiles.load(92, 170, 48, 48, "10test.raw",2);
    }
  }
  //Check aux1/2 timers
  if(aux1TimerState)
  {
    if(currentMillis > (aux1TimerStart + aux1TimerFinish))
    {
      AlarmPwrAux1_Off();
      aux1TimerState = false;
      Serial.println(F("Aux1 timer finished."));
    }
  }
  if(aux2TimerState)
  {
    if(currentMillis > (aux2TimerStart + aux2TimerFinish))
    {
      AlarmPwrAux2_Off();
      aux2TimerState = false;
      Serial.println(F("Aux2 timer finished."));
    }
  }
  
  Alarm.delay(10); // must use Alarm delay to use the TimeAlarms library
  doggieTickle();
  /*
  //Parse command/requests from light fixture (only expect TEMP-XX.XX or 
  //LEDValues request at this point)
  if(Serial2.available())
  {
    //if we have received data read it into input char array
    byte size = Serial2.readBytes(input, INPUT_SIZE);
    input[size] = 0;
    char* separator = strchr(input, '-');
    //Check to see if message is incoming data
    if (separator != 0)
    {
      //Received data, actually split the string in 2, replace '-' with 0 and 
      //increase separator to point at the actual value
      *separator = 0;
      ++separator;
      String command = "";
      command.reserve(10);
      command = input;
      
      Serial.print(F("Parameter received: "));
      Serial.println(command);
      
      //do a case structure based on command
      if(command == "TEMP")
      {
        //received value of heatsink temperature
        temperature2 = atof(separator);
        Serial.print(F("Temperature2: "));
        Serial.println(temperature2);
      }
    }
    //check to see if message is a request
    separator = strchr(input, '?');
    if (separator != 0)
    {
      *separator = 0;
      ++separator;
      String request = "";
      request.reserve(10);
      request = input;
      
      Serial.print(F("Request received: "));
      Serial.println(request);
      
      if(request == "LEDValues")
      {
        //received request for all LED channel values
        Serial.println(F("Sending LED values"));
        writeToLED(1,currentColor.chan1);
        writeToLED(2,currentColor.chan2);
        writeToLED(3,currentColor.chan3);
        writeToLED(4,currentColor.chan4);
        writeToLED(5,currentColor.chan5);
        writeToLED(6,currentColor.chan6);
      }
    }
  }*/
  //End Serial2 monitoring
}

void checkLightRamp()
{
  // check on the fading of the lights  
  time_t currentTime = now();
  if(fadeInProgress == true)
  {
    if(currentTime > fadeStartingSeconds + fadeDurationSeconds)   // if we have just finished the fade...
    {
      fadeInProgress = false;
      currentLightMode = fadeToMode;  // If a color fade has been completed, set the final mode
      
      if(lightCSP==true) // for the CSP, we send a hard code to lock in the setting and avoid drift
      {
        // send IR command for correct lighting mode
        if (currentLightMode == 0) irsend.sendNEC(M1,32);
        else if (currentLightMode == 1) irsend.sendNEC(M2,32);
        else if (currentLightMode == 2) irsend.sendNEC(M3,32);
        else if (currentLightMode == 3) irsend.sendNEC(M4,32);
      }
      if(dispScreen==1) screenHome(); // redraw the home screen if we are home
    }
    else   // if the fade is still running
    {
      // If there is a fade in progress, check if there are any IR commands that should be sent
      checkLightFade((currentTime - fadeStartingSeconds), fadeDurationSeconds);
    }
  }
}

void checkATO()
{
  if(ATOEnabled)
  {
    WaterLevel = digitalRead(TankFloatPin);
    if(ResSwitchEnabled)
    {
      if(ReservoirLevel==LOW)
      {
        ReservoirLevel = digitalRead(ATOFloatPin);
        if(ReservoirLevel==HIGH)clearATOdisplay(); //if level goes from low to high clear display
      }else
      {
        ReservoirLevel = digitalRead(ATOFloatPin);
        if(ReservoirLevel==LOW)clearATOdisplay(); //if level goes from low to high clear display
      }
    }else{ReservoirLevel = HIGH;}
    
    if((WaterLevel == LOW) && (ATOAlarm == false) && (ReservoirLevel == HIGH))
    {
      //if start time is not set then set it to now, ie first time low level detected
      if(ATOStartTime == 0)
      {
        Serial.print(F("Low water level detected.\n"));
        ATOStartTime = now();
      }
      // if pump is off and water level has been low for long enough turn pump ON, 
      // this limits how often pump can turn on.
      if(((now() - ATOStartTime) >= ATOWaitTime)&&(ATOPumpState == false))
      {
        Serial.print(F("ATO pump enabled.\n"));
        digitalWrite(ATOPumpPin,HIGH);//turn ATO ON
        ATOPumpState = true;
        ATOPumpStartTime = now();
        clearATOdisplay();
      }
      //if pump is ON and has been on for more than ATORunTime then shut it off and flag alarm
      if(((now() - ATOPumpStartTime) >= ATORunTime)&&(ATOPumpState == true))
      {
        Serial.print(F("ATO pump on too long, alarm flagged.\n"));
        ATOAlarm = true;
        EEPROM.write(44,1); 
        ATOStartTime = 0;
        digitalWrite(ATOPumpPin,LOW);//turn ATO off
        ATOPumpState = false;
        clearATOdisplay();
      }
    }
    if((ATOPumpState == true) && (ReservoirLevel == LOW))
    {
      Serial.print(F("ATO reservoir low, turning pump off.\n"));
      //turn pump off if we run out of water
      digitalWrite(ATOPumpPin,LOW);//turn ATO off
      ATOPumpState = false;      
    }
    if(WaterLevel == HIGH)
    {
      if(ATOPumpState == true) //if high water level is detected while pump is running clear running icon
      {
        Serial.print(F("High water level detected.\n"));
        clearATOdisplay();
      }
      digitalWrite(ATOPumpPin,LOW);
      ATOStartTime = 0;
      ATOPumpStartTime = 0;
      ATOPumpState = false;
    }
  }else
  {
    //if ATO is disabled but turned on, turn off after max run time
    if(((now() - ATOPumpStartTime) >= ATORunTime)&&(ATOPumpState == true))
    {
      digitalWrite(ATOPumpPin,LOW);//turn ATO off
      ATOPumpState = false;
      clearATOdisplay();
    }
  }
  if(dispScreen == 1)
  {
    drawATO();
  }
}
void clearATOdisplay()
{
  if(dispScreen == 1)
  {
    myGLCD.setColor(VGA_BLACK);
    myGLCD.fillRect(121,32,239,109); //clear prev. ATO display
  }
}
  
void drawATO()
{
  //draw water levels
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(arial_bold);
  if(ATOAlarm)
  {
    myFiles.load(150, 52, 60, 55, "1warn.raw",2);
    //myGLCD.setFont(arial_bold);
    //myGLCD.print(F("Alarm"), 140, 36);
    myGLCD.setFont(Sinclair_S);
    myGLCD.print(F("Run-time"), 152, 36);
    myGLCD.print(F("Exceeded"), 152, 44);
  }else if(ATOPumpState)
  {
    myGLCD.setFont(arial_bold);
    myFiles.load(150, 52, 55, 55, "1atoon.raw",2);
    myGLCD.print(F("Running"), 124, 36);
  }else if(ReservoirLevel == LOW)
  {
    myGLCD.setFont(Sinclair_S);
    myFiles.load(150, 52, 60, 55, "1warn.raw",2);
    myGLCD.print(F("Reservoir"), 144, 36);
    myGLCD.print(F("Empty"), 160, 44);
  }else if(ATOEnabled)
  {
    //print letters individually due to space constraints
    myGLCD.setFont(arial_bold);
    myGLCD.print("W", 121, 50);
    myGLCD.print("A", 136, 50);
    myGLCD.print("T", 148, 50);
    myGLCD.print("E", 160, 50);
    myGLCD.print("R", 172, 50);
    myGLCD.print("L", 121, 75);
    myGLCD.print("E", 132, 75);
    myGLCD.print("V", 146, 75);
    myGLCD.print("E", 159, 75);
    myGLCD.print("L", 172, 75);
    //myGLCD.print("T", 122, 36); 
    //myGLCD.print("A", 135, 36);
    //myGLCD.print("N", 148, 36);
    //myGLCD.print("K", 161, 36);
    //myGLCD.print("ATO", 186, 36);
    myFiles.load(188, 46, 50, 50, WaterIcon[WaterLevel],4);
    //myFiles.load(184, 54, 50, 50, WaterIcon[ReservoirLevel],4);
  }else
  {
    myFiles.load(122, 45, 115, 45, "logo.raw",2); //display a iAqua logo if ATO is disabled
  }
}

void checkTemp() // called from the main loop to update temperature reading
{
  if(sensor1Enabled)
  {
    if(sensorW.isConnected(waterSensor))
    {
      sensorW.requestTemperatures();  // get temp from sensor
      if(displayInC == false) temperature = sensorW.getTempF(waterSensor);
      if(displayInC == true)  temperature = sensorW.getTempC(waterSensor);
      temperature = temperature + sensor1Calibration;
      int intTemperature=temperature; // create an integer var of the temp
      if (heaterWarning == false) // with no warning active, check temp against temp warning value
      {
        if (intTemperature >= heatOffTemp)  // turn off heater if over threshold
        {
          Serial.print(F("Water over temperature limit!\n"));
          heaterWarning = true; // turn on warning
          heaterWarningCleared = false;  // warning is obviously not cleared yet
          AlarmPwrHeat_Off(); // turn off heater power
        }
      }
      else if (heaterWarning == true) // if there was a warning, we watch for a low temp to turn heat back on
      {
        if (intTemperature <= heatOnTemp) // turn heater back on when temp drops below setting
        {
          Serial.print(F("Water temperature below limit.\n"));
          heaterWarning=false; // turn off the warning, but do not mark it as cleared so the icon stays red 
          AlarmPwrHeat_On(); // turn heater back on
        }
      }
    }
  }
  if(sensor2Enabled)
  {
    sensorH.requestTemperatures();
    if(displayInC == false) temperature2 = sensorH.getTempF(heatsinkSensor);
    if(displayInC == true)  temperature2 = sensorH.getTempC(heatsinkSensor);
    temperature2 = temperature2 + sensor2Calibration;
    int intTemperature2 = temperature2;
    if(intTemperature2 > heatsinkFanOnTemp)
    {
      if(fan1status == false)
      {
        Serial.print(F("Heatsink temp over limit, T: "));
        Serial.println(temperature2);
        Serial.print(F("Heatsink Fan enabled."));
      }
      alarmFan1on();
      fan1status = true;
    }
    if((fan1status == true)&&(intTemperature2 <= heatsinkFanOffTemp))
    {
      if(fan1status == true)
      {
        Serial.print(F("Heatsink temp under limit, T: "));
        Serial.println(temperature2);
        Serial.print(F("Heatsink Fan disabled."));
      }
      alarmFan1off();
      fan1status = false;
    }
  }
  if(sensor3Enabled)
  {
    unsigned int intTemperature3;
    intTemperature3 = analogRead(internalTempPin);
    intTemperature3 = map(intTemperature3,0,1023,0,5000); //map to mV
    intTemperature3 = intTemperature3 - 400; //offset at 0C
    temperature3 = (float)intTemperature3 / 19.5;
    //if(displayInC == true) intTemperature3 = temperature3;
    if(displayInC == false)
    {
      temperature3 = ((temperature3 * 9.0)/ 5.0) + 32.0; //Convert from C to F
    }
    temperature3 = temperature3 + sensor3Calibration;
    intTemperature3 = temperature3;
    if(intTemperature3 > internalFanOnTemp)
    {
      if(fan2status == false)
      {
        Serial.print(F("Internal temp over limit, T: "));
        Serial.println(temperature3);
        Serial.println(F("Internal Fan enabled."));
      }
      alarmFan2on();
      fan2status = true;
    }
    if((fan2status == true)&&(intTemperature3 <= internalFanOffTemp))
    {
      if(fan2status == true)
      {
        Serial.print(F("Internal temp under limit, T: "));
        Serial.println(temperature3);
        Serial.println(F("Internal Fan disabled."));
      }
      alarmFan2off();
      fan2status = false;
    }
  }
  if(dispScreen == 1)
  {
    drawTemp();
  }
}

void drawTemp()
{
  char tempstring[7];  // water temperature as a string
  boolean displayMultiSensors = (displaySensor2 && sensor2Enabled)||(displaySensor3 && sensor3Enabled);

  myGLCD.setFont(arial_bold);
  
  if(displayMultiSensors == false) //only water temp is enabled
  {
    if(heaterWarning)
    {
      myFiles.load(30, 35, 60, 51, "1thermR.raw",4);
    }else
    {
      myFiles.load(30, 35, 60, 51, "1therm.raw",4);
    }
    if(sensorW.isConnected(waterSensor))
    {
      // set temp color based on alarms on home screen
      if (heaterWarningCleared==true)
      {
        myGLCD.setColor(VGA_WHITE);  // if no warning is active, or it has been acknowledged
        if(displayInC == true)myFiles.load(90, 94, 14, 12, "c.raw",4);
        if(displayInC == false)myFiles.load(90, 94, 14, 12, "f.raw",4);
      }
      else if (heaterWarningCleared==false)
      {
        myGLCD.setColor(222, 8, 51);  // if warning is active and hasn't been acknowledged
        if(displayInC == true)myFiles.load(90, 94, 14, 12, "c_R.raw",4);
        if(displayInC == false)myFiles.load(90, 94, 14, 12, "f_R.raw",4);
      }
      dtostrf(temperature, 4, 1, tempstring);  //convert to string
      myGLCD.print(tempstring, 20, 92);
    }else
    {
      myGLCD.setColor(VGA_WHITE);
      myGLCD.print(F("  N/C  "), 4, 92);
    }
  }
  else //more than one sensor enabled
  {
    //Draw water temp
    if(heaterWarning)
    {
      myFiles.load(2, 33, 28, 24, "1thermRS.raw",4);
    }else
    {
      myFiles.load(2, 33, 28, 24, "1thermS.raw",4);
    }
    if(sensorW.isConnected(waterSensor))
    {
      // set temp color based on alarms on home screen
      if (heaterWarningCleared==true)
      {
        myGLCD.setColor(VGA_WHITE);  // if no warning is active, or it has been acknowledged
        if(displayInC == true)myFiles.load(102, 39, 14, 12, "c.raw",4);
        if(displayInC == false)myFiles.load(102, 39, 14, 12, "f.raw",4);
      }
      else if (heaterWarningCleared==false)
      {
        myGLCD.setColor(222, 8, 51);  // if warning is active and hasn't been acknowledged
        if(displayInC == true)myFiles.load(102, 39, 14, 12, "c_R.raw",4);
        if(displayInC == false)myFiles.load(102, 39, 14, 12, "f_R.raw",4);
      }
      dtostrf(temperature, 4, 1, tempstring);  //convert to string
      myGLCD.print(tempstring, 34, 37);
    }else
    {
      myGLCD.setColor(VGA_WHITE);
      myGLCD.print(F(" N/C "), 36, 37);
    }
    
    //Draw LED temp
    myGLCD.setFont(arial_bold);
    myGLCD.setColor(VGA_WHITE);
    myFiles.load(2, 59, 28, 24, "1temp2S.raw",4);
    if(temperature2 > 0)
    {
      dtostrf(temperature2, 4, 1, tempstring);
      myGLCD.print(tempstring, 34, 63);
      if(displayInC == true)myFiles.load(102, 65, 14, 12, "c.raw",4);
      if(displayInC == false)myFiles.load(102, 65, 14, 12, "f.raw",4);
    }else
    {
      myGLCD.setColor(VGA_WHITE);
      myGLCD.print(F(" N/C "), 36, 63);
    }
    
    //Draw controller temp
    myFiles.load(2, 85, 28, 24, "1temp3S.raw",4);
    dtostrf(temperature3, 4, 1, tempstring);
    myGLCD.setFont(arial_bold);
    myGLCD.setColor(VGA_WHITE);
    myGLCD.print(tempstring, 34, 89);
    if(displayInC == true)myFiles.load(102, 91, 14, 12, "c.raw",4);
    if(displayInC == false)myFiles.load(102, 91, 14, 12, "f.raw",4);
  }
}

void checkFeeding() // called from the main loop to update feeding info on home screen
{
  if (feedingActive==true)
  {
    dimTime = now(); // keep the screen bright duing feeding
    if ((now()-startFeedingTime) > (feedingMins*60)) // keep looping until feeding is done
    {
      feedingStop();
      Serial.print(F("Feeding Stopped.\n"));
    }
  }
  if((dispScreen==1)||(dispScreen==2))
  {
    drawFeeding();
  }
}

void drawFeeding()
{
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 255, 255);

  char char4[4]; // used to convert int to char
  int fx; // x value used to center the hours/mins
  boolean writeMinutes = true;

  // if feeding isn't active, display the elapsed hours since last feeding
  if (feedingActive==false)
  {
    int feedHours=calcFeeding(); // calculate how many hours since we've fed the fish

    // print the feeding hours to screen
    if(feedHours < 100)
    {
      itoa(feedHours, char4, 10);
      if (feedHours<10) fx=20; // shift x position to center
      else if (feedHours>9) fx=12; // shift x position to center
      myGLCD.print(char4, fx, 130);
      myGLCD.print(F("HR"), 12, 146);
    }else
    {
      myGLCD.print(F(">99"), 4, 130);
      myGLCD.print(F("HR"), 12, 146);
    }
  }

  // if feeding is active, we display the amount of time left in the feeding cycle
  else if (feedingActive==true)
  {
    // calculate how many minutes are left from millis to display on the screen
    unsigned long feedingTotalSeconds = feedingMins * 60;
    int feedingMinsLeft = (feedingTotalSeconds-(now()-startFeedingTime))/60;
    int feedingSecLeft = (feedingTotalSeconds-(now()-startFeedingTime))%60;

    if (dispScreen==1) // write to home screen
    {
      if(feedingMinsLeft < 10)
      {
        // clear previous value
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(0,146,55,162);
        // set font to green
        myGLCD.setColor(0, 255, 19);
      
        // convert and write minutes to screen
        itoa(feedingMinsLeft, char4, 10);
        myGLCD.print(char4, 2, 130);
        
        // convert and write seconds to screen
        itoa(feedingSecLeft, char4, 10);
        if(feedingSecLeft < 10)
        {
          myGLCD.print("0", 22, 130);
          myGLCD.print(char4, 38, 130);
        }else{myGLCD.print(char4, 22, 130);}
        
        // Draw :
        myGLCD.fillRect(20,134,21,135); 
        myGLCD.fillRect(20,142,21,143);
      }else
      {
        // set font to green
        myGLCD.setColor(0, 255, 19);
        // Write to screen
        myGLCD.print(F(">10"), 4, 130);
        myGLCD.print(F("MIN"), 4, 146);
      }
    }
    else if (dispScreen==2)  // write to feeding screen
    {
      // clear previous value
      //myGLCD.setColor(0, 0, 0);
      //myGLCD.fillRect(40,80,220,96); 
      myGLCD.setColor(255, 255, 255);
      myGLCD.print(":", 112, 80);
      
      // convert and write minutes to screen
      itoa(feedingMinsLeft, char4, 10);
      if(feedingMinsLeft < 10)
      {
        myGLCD.print(" ", 80, 80);
        myGLCD.print(char4, 96, 80);
      }else
      {
        myGLCD.print(char4, 80, 80);
      }
      
      // convert and write seconds to screen
      itoa(feedingSecLeft, char4, 10);
      if(feedingSecLeft < 10)
      {
        myGLCD.print("0", 128, 80);
        myGLCD.print(char4, 144, 80);
      }else
      {
        myGLCD.print(char4, 128, 80);
      }
    }
  }
}

void checkDosing() // updates dosing info on the home screen
{
  char char3[4];  // used to convert int to char

  // just to note, that since we need to store a number higher than 255 in EEPROM, we have a high
  // and low byte when retrieved, the high byte is a number that is converted to the 10th multiple
  // then the low byte is added to the high byte to get our stored value
  // this gives us values up to 2559, which would be over 2L of ferts, so we are set

  long vol1_H=EEPROM.read(32); // read the remaining volume for pump 1 (high byte)
  long vol1_L=EEPROM.read(33); // read the remaining volume for pump 1 (low byte)
  long vol2_H=EEPROM.read(34); // read the remaining volume for pump 2 (high byte *10)
  long vol2_L=EEPROM.read(35); // read the remaining volume for pump 2 (low byte)
  long vol3_H=EEPROM.read(36); // read the remaining volume for pump 3 (high byte *10)
  long vol3_L=EEPROM.read(37); // read the remaining volume for pump 3 (low byte)

  long vol1 = (vol1_H*10)+vol1_L;
  long vol2 = (vol2_H*10)+vol2_L;
  long vol3 = (vol3_H*10)+vol3_L;

  long dose1Amt=EEPROM.read(20); // 20 // pump 1 dose in mL
  long dose2Amt=EEPROM.read(21); // 20 // pump 2 dose in mL
  long dose3Amt=EEPROM.read(22); // 20 // pump 3 dose in mL
  //unsigned int doseCap=EEPROM.read(26); // 26 // dosing reseviors capacity in mL*10;
  //doseCap=doseCap*10;  // to power of 10
  
  long dose1Cap=EEPROM.read(26);
  dose1Cap=dose1Cap*10;  // to power of 10
  long dose2Cap=EEPROM.read(261);
  dose2Cap=dose2Cap*10;  // to power of 10
  long dose3Cap=EEPROM.read(263);
  dose3Cap=dose3Cap*10;  // to power of 10

  long doses1=(vol1/dose1Amt);  // cacluate how many Macro doeses are left
  long doses2=(vol2/dose2Amt);  // cacluate how many Micro are left
  long doses3=(vol3/dose3Amt);  // cacluate how many Micro are left

 // here we prepare to draw the fill over the screen icons
  
  // draw empty fert tubes (red if less than 5 doses)
  if(doses1 > 4)myFiles.load(112, 122, 23, 50, "1ferts.raw",4);
  if(doses1 < 5)myFiles.load(112, 122, 23, 50, "1fertse.raw",4);
  if(doses2 > 4)myFiles.load(138, 122, 23, 50, "1ferts.raw",4);
  if(doses2 < 5)myFiles.load(138, 122, 23, 50, "1fertse.raw",4);
  if(doses3 > 4)myFiles.load(124, 183, 23, 50, "1ferts.raw",4);
  if(doses3 < 5)myFiles.load(124, 183, 23, 50, "1fertse.raw",4);
  
  // set initial Y values of an emtpy resevoir
  long y1mac=165;
  long y1mic=165;
  long y1exc=226;

  // calculate percentage left and generate the y1 coordinate for drawing the fill levels
  if (doses1>0) y1mac = 165 - ((vol1*39)/dose1Cap);  // for Macros
  if (doses2>0) y1mic = 165 - ((vol2*39)/dose2Cap);  // for Micros
  if (doses3>0) y1exc = 226 - ((vol3*39)/dose3Cap);  // for Excel

  // if the math above throws the pixels outside the tube, set it back to empty
  if ((y1mac > 165)||(y1mac < 125)) y1mac = 165;
  if ((y1mic > 165)||(y1mic < 125)) y1mic = 165;
  if ((y1exc > 225)||(y1exc < 186)) y1exc = 226;

  // fill top of fert tube with black as necessary
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(117,125,129,y1mac); //x1,y1,x2,y2
  myGLCD.fillRect(143,125,155,y1mic); 
  myGLCD.fillRect(129,186,141,y1exc); 

  //draw fert fill
  myGLCD.setColor(34, 81, 255);  // blue for macros
  myGLCD.fillRect(117,y1mac,129,165);
  myGLCD.setColor(255, 77, 0);  // orange for micros
  myGLCD.fillRect(143,y1mic,155,165);
  myGLCD.setColor(34, 255, 77);  // green for excel
  myGLCD.fillRect(129,y1exc,141,226);
  
  // values to center remaining dose numerical values over tubes on screen
  int xcharMacro=116;//2 digits
  int xcharMicro=142;
  int xcharExcel=128;
  if (doses1 <= 9) xcharMacro=120;//1 digit
  if (doses2 <= 9) xcharMicro=146;
  if (doses3 <= 9) xcharExcel=132;
  if (doses1 > 99) xcharMacro=112;//3 digits
  if (doses2 > 99) xcharMicro=138;
  if (doses3 > 99) xcharExcel=124;
  
  // draw remaining dose numerical values
  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 255, 255);
  itoa(doses1, char3, 10);
  myGLCD.print(char3, xcharMacro, 112);
  itoa(doses2, char3, 10);
  myGLCD.print(char3, xcharMicro, 112);
  itoa(doses3, char3, 10);
  myGLCD.print(char3, xcharExcel, 174);
}

void checkLighting()
{
  // display lighting info
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRect(57,111,104,236);

  if (currentLightMode==4) // active transition
  {
    myFiles.load(67, 118, 28, 28, lightModeSm[fadeFromMode],4);
    myFiles.load(75, 151, 12, 20, "1arrow.raw",4);
    myFiles.load(67, 174, 28, 28, lightModeSm[fadeToMode],4);

    // Get the time in seconds (since 1970)
    unsigned long rightNow = now();

    // calculate how much time is left in the fade in minutes
    unsigned long timeLeft=((fadeStartingSeconds + fadeDurationSeconds)-rightNow)/60;

    // convert to char
    int minsLeft=timeLeft;
    char char4[4];
    itoa(minsLeft, char4, 10);

    // center the minutes left
    int xmin=0;
    if (minsLeft<10) xmin=77;
    if ((minsLeft>9)&&(minsLeft<100)) xmin=73;
    if (minsLeft>99) xmin=69;

    // clear old data
    myGLCD.setColor(0, 0, 0);
    myGLCD.fillRect(69,207,93,215);

    // print to screen
    myGLCD.setFont(Sinclair_S);
    myGLCD.setColor(255, 255, 255);
    myGLCD.print(char4, xmin, 207);
    myGLCD.print("MIN", 69, 219);
  }
  else if (currentLightMode==5) 
  {//if unknown state print a question mark
    myFiles.load(57, 140, 48, 48, "1quest.raw");
  }
  else
  {// if we are not fading, then print the current mode
    myFiles.load(57, 140, 48, 48, lightMode[currentLightMode],4);
  }
}

// this is called by the light mode editing screen and its touch events
void clearSelectedLight(int cmd) 
{
  if (cmd==1) // switch off the selected icon of an individual light button
  {
    if (currentLightMode==0)
    {
      myFiles.load(10, 39, 48, 48, lightMode[currentLightMode],2);
    }
    else if (currentLightMode==1)
    {
      myFiles.load(67, 39, 48, 48, lightMode[currentLightMode],2);
    }
    else if (currentLightMode==2)
    {
      myFiles.load(124, 39, 48, 48, lightMode[currentLightMode],2);
    }
    else if (currentLightMode==3)
    {
      myFiles.load(181, 39, 48, 48, lightMode[currentLightMode],2);
    }
  }
  else if (cmd==2) // disable all light modes that aren't active
  {
    if (currentLightMode==0)
    {
      // disable all other mode buttons
      myFiles.load(67, 39, 48, 48, lightModeF[0],2);
      myFiles.load(124, 39, 48, 48, lightModeF[1],2);
      myFiles.load(181, 39, 48, 48, lightModeF[2],2);
    }
    else if (currentLightMode==1)
    {
      // disable all other mode buttons
      myFiles.load(10, 39, 48, 48, lightModeF[0],2);
      myFiles.load(124, 39, 48, 48, lightModeF[1],2);
      myFiles.load(181, 39, 48, 48, lightModeF[2],2);
    }
    else if (currentLightMode==2)
    {
      // disable all other mode buttons
      myFiles.load(10, 39, 48, 48, lightModeF[0],2);
      myFiles.load(67, 39, 48, 48, lightModeF[0],2);
      myFiles.load(181, 39, 48, 48, lightModeF[2],2);
    }
    else if (currentLightMode==3)
    {
      // disable all other mode buttons
      myFiles.load(10, 39, 48, 48, lightModeF[0],2);
      myFiles.load(67, 39, 48, 48, lightModeF[0],2);
      myFiles.load(124, 39, 48, 48, lightModeF[1],2);
    }
  }
}

void resyncLights()
{
  // this routine forces the light into a factory preset mode and reads in the stored M1-M4 light modes
  if (lightCSP == true)
  {
    irsend.sendNEC(FULLSPECTRUM,32);
    currentColor.chan1 = maxIR;
    currentColor.chan2 = maxIR;
    currentColor.chan3 = maxIR;
    currentColor.chan4 = maxIR;
  }
  else if (lightCSP == false) 
  {
    currentColor.chan1 = 0;
    currentColor.chan2 = 0;
    currentColor.chan3 = 0;
    currentColor.chan4 = 0;
    currentColor.chan5 = 0;
    currentColor.chan6 = 0;
    writeToLED(1,currentColor.chan1);
    writeToLED(2,currentColor.chan2);
    writeToLED(3,currentColor.chan3);
    writeToLED(4,currentColor.chan4);
    writeToLED(5,currentColor.chan5);
    writeToLED(6,currentColor.chan6);
  }

  targetColor.chan1 = 0;
  targetColor.chan2 = 0;
  targetColor.chan3 = 0;
  targetColor.chan4 = 0;
  targetColor.chan5 = 0;
  targetColor.chan6 = 0;
  lastColor.chan1 = 0;
  lastColor.chan3 = 0;
  lastColor.chan2 = 0;
  lastColor.chan4 = 0;
  lastColor.chan5 = 0;
  lastColor.chan6 = 0;

  currentLightMode=5;

  lightHighSun.chan1=EEPROM.read(400);
  lightHighSun.chan2=EEPROM.read(401);
  lightHighSun.chan3=EEPROM.read(402);
  lightHighSun.chan4=EEPROM.read(403);
  lightHighSun.chan5=EEPROM.read(404);
  lightHighSun.chan6=EEPROM.read(405);
    
  lightMidSun.chan1=EEPROM.read(410);
  lightMidSun.chan2=EEPROM.read(411);
  lightMidSun.chan3=EEPROM.read(412);
  lightMidSun.chan4=EEPROM.read(413);
  lightMidSun.chan5=EEPROM.read(414);
  lightMidSun.chan6=EEPROM.read(415);

  lightLowSun.chan1=EEPROM.read(420);
  lightLowSun.chan2=EEPROM.read(421);
  lightLowSun.chan3=EEPROM.read(422);
  lightLowSun.chan4=EEPROM.read(423);
  lightLowSun.chan5=EEPROM.read(424);
  lightLowSun.chan6=EEPROM.read(425);

  lightMoon.chan1=EEPROM.read(430);
  lightMoon.chan2=EEPROM.read(431);
  lightMoon.chan3=EEPROM.read(432);
  lightMoon.chan4=EEPROM.read(433);  
  lightMoon.chan5=EEPROM.read(434);
  lightMoon.chan6=EEPROM.read(435);
}

void feedingStop()
{
  feedingActive=false; // stop feeding cycle
  lastFeedingTime = now();
  
  if(feedSetting.pwrHeat)
  {
    if (preFeedPower.pwrHeat==1) AlarmPwrHeat_On();
    else if (preFeedPower.pwrHeat==0) AlarmPwrHeat_Off();
  }
  if(feedSetting.pwrCO2)
  {
    if (preFeedPower.pwrCO2==1) AlarmPwrCO2_On();
    else if (preFeedPower.pwrCO2==0) AlarmPwrCO2_Off();
  }
  if(feedSetting.pwrFilter)
  {
    if (preFeedPower.pwrFilter==1) AlarmPwrFilter_On();
    else if (preFeedPower.pwrFilter==0) AlarmPwrFilter_Off();
  }
  if(feedSetting.pwrCirc)
  {
    if (preFeedPower.pwrCirc==1) AlarmPwrCirc_On();
    else if (preFeedPower.pwrCirc==0) AlarmPwrCirc_Off();
  }
  if(feedSetting.pwrAux1)
  {
    if (preFeedPower.pwrAux1==1) AlarmPwrAux1_On();
    else if (preFeedPower.pwrAux1==0) AlarmPwrAux1_Off();
  }
  if(feedSetting.pwrAux2)
  {
    if (preFeedPower.pwrAux2==1) AlarmPwrAux2_On();
    else if (preFeedPower.pwrAux2==0) AlarmPwrAux2_Off();
  }
  if(dispScreen == 1)  //clear previous data
  {
    myGLCD.setColor(0, 0, 0);
    myGLCD.fillRect(1,111,55,171);
    drawFeeding();
  }
  if(dispScreen==2) screenHome(); // Return to the home screen
}

void SaveTime()
{
  time_t saveTime = makeTime(saveRTC);
  setTime(saveTime);
  RTC.set(saveTime);
  updateTimeDate(true);
}

void updateTimeDate(boolean updateTime)
{
  // draw date and time
  myGLCD.setColor(240, 240, 255);
  myGLCD.setFont(Sinclair_S);

  if ((hour()!=prevRTC.Hour) || (minute()!=prevRTC.Minute) || updateTime) {
    prevRTC.Hour = hour();
    prevRTC.Minute = minute();
    if(displayIn12Hr == true)printTime(hourFormat12() , minute(), isPM(), 180, 2);
    if(displayIn12Hr == false)printTime24Hr(hour(),minute(),180,2);
    if(updateTime == false)
    {
      printValueUpdate();
    }
  }

  if ((day()!=prevRTC.Day) || (month()!=prevRTC.Month) || updateTime) {
    prevRTC.Day = day();
    prevRTC.Month = month();
    printDate(40, 2);             
  }
}

void printValueUpdate()
{
  time_t printTime = now();
  Serial.print(F("Updating time: "));
  if(hourFormat12(printTime) < 10)Serial.print(F("0"));
  Serial.print(hourFormat12(printTime));
  Serial.print(F(":"));
  if(minute(printTime) < 10)Serial.print(F("0"));
  Serial.print(minute(printTime));
  Serial.print(F(":"));
  if(second(printTime) < 10)Serial.print(F("0"));
  Serial.print(second(printTime));
  if(fadeInProgress==true)
  {
    Serial.print(F("  Current Colors: "));
    Serial.print(currentColor.chan1);Serial.print(F(","));Serial.print(currentColor.chan2);Serial.print(F(","));
    Serial.print(currentColor.chan3);Serial.print(F(","));Serial.print(currentColor.chan4);Serial.print(F(","));
    Serial.print(currentColor.chan5);Serial.print(F(","));Serial.print(currentColor.chan6);
    Serial.print(F("  Last Colors: "));
    Serial.print(lastColor.chan1);Serial.print(F(","));Serial.print(lastColor.chan2);Serial.print(F(","));
    Serial.print(lastColor.chan3);Serial.print(F(","));Serial.print(lastColor.chan4);Serial.print(F(","));
    Serial.print(lastColor.chan5);Serial.print(F(","));Serial.print(lastColor.chan6);
    Serial.print(F("  Target Colors: "));
    Serial.print(targetColor.chan1);Serial.print(F(","));Serial.print(targetColor.chan2);Serial.print(F(","));
    Serial.print(targetColor.chan3);Serial.print(F(","));Serial.print(targetColor.chan4);Serial.print(F(","));
    Serial.print(targetColor.chan5);Serial.print(F(","));Serial.print(targetColor.chan6);
  }
  Serial.print(F("\n"));
}

void printTime(int thour, int tminute, byte ampm, int posx, int posy)
{
  char tmpTime[8], charT[3];

  tmpTime[0] = '\0';

  if (thour>=0 && thour<=9) {          //add space
    strcat(tmpTime, " ");
    itoa(thour, charT, 10);
    strcat(tmpTime, charT);
  }
  else 
    itoa(thour, tmpTime, 10);

  strcat(tmpTime, ":");  

  if (tminute>=0 && tminute<=9) {         //add 0
    strcat(tmpTime, "0");
    itoa(tminute, charT, 10);
    strcat(tmpTime, charT);
  }
  else {
    itoa(tminute, charT, 10);
    strcat(tmpTime, charT);
  }
  if (ampm==0) strcat(tmpTime, "am");
  else strcat(tmpTime, "pm");

  myGLCD.print(tmpTime, posx, posy);           // Display time  
}

void printTime24Hr(int thour, int tminute, int posx, int posy)
{
  char tmpTime[8], charT[3];

  tmpTime[0] = '\0';

  if (thour>=0 && thour<=9) {       //add space
    strcat(tmpTime, " ");
    itoa(thour, charT, 10);
    strcat(tmpTime, charT);
  }
  else 
    itoa(thour, tmpTime, 10);

  strcat(tmpTime, ":");  

  if (tminute>=0 && tminute<=9) {    //add 0
    strcat(tmpTime, "0");
    itoa(tminute, charT, 10);
    strcat(tmpTime, charT);
  }
  else {
    itoa(tminute, charT, 10);
    strcat(tmpTime, charT);
  }

  myGLCD.print(tmpTime, posx, posy); // Display time  
}

void printDate(int x, int y) 
{
  char  chDate[25], tmpChar[5];

  strcat(chDate, "     ");
  chDate[0] = '\0';
  strcat(chDate, dayShortStr(weekday()));
  strcat(chDate, ", ");
  strcat(chDate, monthShortStr(month()));
  strcat(chDate, " ");
  itoa(day(), tmpChar, 10);
  strcat(chDate, tmpChar);
  // this line is for omitting year
  strcat(chDate, "  ");

  myGLCD.print(chDate, x, y);            //Display date 
}

time_t tmConvert_t(int YYYY, byte MM, byte DD, byte hh, byte mm, byte ss)
{
  tmElements_t tmSet;
  tmSet.Year = YYYY - 1970;
  tmSet.Month = MM;
  tmSet.Day = DD;
  tmSet.Hour = hh;
  tmSet.Minute = mm;
  tmSet.Second = ss;
  return makeTime(tmSet);         //convert to time_t
}

void autoBrightness()
{
  int photocellReading = analogRead(lightSensorPin); 

  // map the photo sensor value of 0-1023 directly to the PWM output of 0-255
  int brightnessLevel=map(photocellReading, 0, 1023, 0, 255);

  // apply a brightness bump or drop based on the user preference autodim setting
  int brightAdjust;
  if (screenDimLevel==1) brightAdjust=-40;
  else if (screenDimLevel==2) brightAdjust=-30;
  else if (screenDimLevel==3) brightAdjust=-20;
  else if (screenDimLevel==4) brightAdjust=-10;
  else if (screenDimLevel==5) brightAdjust=0;
  else if (screenDimLevel==6) brightAdjust=10;
  else if (screenDimLevel==7) brightAdjust=20;
  else if (screenDimLevel==8) brightAdjust=30;
  else if (screenDimLevel==9) brightAdjust=40;
  else if (screenDimLevel==10) brightAdjust=50;
  // apply brightness adjustment
  brightnessLevel=brightnessLevel+brightAdjust; 
  // can't get brighter than 255, must be at least 1 or it's off
  brightnessLevel = constrain(brightnessLevel, 5, 255); 

  int diff = brightnessLevel - backLight;
  if (abs(diff) > 25) // we only adjsut brightness if it's more than a 10% change from where we are now
  {
    rampScreenBrightness(backLight, brightnessLevel);
  }
}
void idleBrightness()
{
  int brightnessLevel;
  
  //brightnessLevel = (screenDimLevel * 25) + 5;
  // can't get brighter than 255, must be at least 1 or it's off
  //brightnessLevel = constrain(brightnessLevel, 5, 255); 
  
  brightnessLevel = map(screenDimLevel,1,10,10,255);
  rampScreenBrightness(backLight, brightnessLevel);
}

// smoothly ramps the screen brightness from one level to another
void rampScreenBrightness(byte fromLevel, byte toLevel)
{
  if (fromLevel<toLevel)
  {
    while (fromLevel<toLevel) 
    {
      analogWrite(screenBrightPin, fromLevel);
      fromLevel++;
      Alarm.delay(5);
    }
  }
  else if (fromLevel>toLevel)
  {
    while (fromLevel>toLevel) 
    {
      analogWrite(screenBrightPin, fromLevel);  
      fromLevel--;
      Alarm.delay(5);
    }
  }
  backLight=toLevel;
  
}

int calcFeeding()
{
  // need to retrieve and calculate last feeding time
  time_t timeSinceLastFeed = now() - lastFeedingTime;
  int elapsedHr = timeSinceLastFeed/60/60;
  return elapsedHr;
}

int SerialReadInt()
{
  // Reads first 3 bytes from serial monitor; anything more is tossed
  byte i;
  char inBytes[4];
  char * inBytesPtr = &inBytes[0];  // Pointer to first element

  for (i=0; i<3; i++)             // Only want first 3 bytes
    inBytes[i] = Serial.read();
  inBytes[i] =  '\0';             // Put NULL character at the end
  while (Serial.read() >= 0)      // If anything else is there, throw it away
    ; // do nothing      
  return atoi(inBytesPtr);        // Convert to decimal
}

void TestCodes (int cmd)
{
  // Handles commands sent in from the serial monitor
  if (cmd==1)
  {
    Serial.print(F("Sensor: "));
    int photocellReading = analogRead(lightSensorPin); 
    Serial.println(photocellReading);
  }
  else if (cmd>1) analogWrite(screenBrightPin, cmd);
}

// Check if there should be any IR commands sent for the color fade, based on time elapsed
void checkLightFade(int secondsElapsed, int durationInSeconds)
{
  // update fade timing info on home screen
  if (dispScreen==1)
  {
    // Get the time in seconds (since 1970)
    unsigned long rightNow = now();

    // calculate how much time is left in the fade in minutes
    unsigned long timeLeft=((fadeStartingSeconds + durationInSeconds)-rightNow)/60;

    // we only update the display if it's a new value
    if (timeLeft!=fadeTimeLeft)
    {
      // update remaining time
      fadeTimeLeft=timeLeft;

      // convert to char
      int minsLeft=timeLeft;
      char char4[4];
      itoa(minsLeft, char4, 10);

      // center the minutes left
      int xmin;
      if (minsLeft<10) xmin=77;
      if ((minsLeft>9)&&(minsLeft<100)) xmin=73;
      if (minsLeft>99) xmin=69;

      // clear old data
      myGLCD.setColor(0, 0, 0);
      myGLCD.fillRect(69,207,93,215);

      // print to screen
      myGLCD.setFont(Sinclair_S);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print(char4, xmin, 207);
      myGLCD.print(F("MIN"), 69, 219);
    }
  }
  
  float tick; // value change per second
  int value; // total value change based on time elapsed
  int difference;

  // Channel 1 (RED) /////////////////////////////////////////////////////////
  if(currentColor.chan1 != targetColor.chan1)
  {
    difference = targetColor.chan1 - lastColor.chan1;
    // Get the change per second for the current color to the target color
    tick = (float)durationInSeconds / (float)difference;
    
    // Get the expected value for the time elapsed
    value = round(secondsElapsed / tick);

    if(currentColor.chan1 < targetColor.chan1) // If the change is positive
    {
      // And if the current color does not match the expected color
      if((lastColor.chan1 + value) > currentColor.chan1)
      {
        // Increase the current color
        currentColor.chan1++;
        if (lightCSP==true) 
        {
          Serial.print(F("red up\n"));
          irsend.sendNEC(REDUP,32);
          Alarm.delay(333);
        }
        if (lightCSP==false)
        {
          writeToLED(1,currentColor.chan1);
        }
      }
    }
    else if(currentColor.chan1 > targetColor.chan1) // If the change is negative
    {
      // And if the current color does not match the expected color
      if((lastColor.chan1 + value) < currentColor.chan1)
      {
        // Decrease the current color
        currentColor.chan1--;
        if (lightCSP==true) 
        {
          Serial.print(F("red down\n"));
          irsend.sendNEC(REDDOWN,32);
          Alarm.delay(333);
        }
        else if (lightCSP==false)
        {
          writeToLED(1,currentColor.chan1);
        }
      }
    }
  }

  // Channel 2 (GREEN) /////////////////////////////////////////////////////////
  if(currentColor.chan2 != targetColor.chan2)
  {
    // Get the change per second for the current color to the target color
    difference = targetColor.chan2 - lastColor.chan2;
    tick = (float)durationInSeconds / (float)difference;

    // Get the expected change for the time elapsed
    value = round(secondsElapsed / tick);

    if(currentColor.chan2 < targetColor.chan2) // If the change is positive
    {
      // And if the current color does not match the expected color
      if((lastColor.chan2 + value) > currentColor.chan2)
      {
        // Increase the current color
        currentColor.chan2++;
        if (lightCSP==true) 
        {
          Serial.print(F("green up\n"));
          irsend.sendNEC(GREENUP,32);
          Alarm.delay(333);
        }
        else if (lightCSP==false)
        {
          writeToLED(2,currentColor.chan2);
        }
      }
    }
    else if(currentColor.chan2 > targetColor.chan2)// If the change is negative
    {
      // And if the current color does not match the expected color
      if((lastColor.chan2 + value) < currentColor.chan2)
      {
        // Decrease the current color
        currentColor.chan2--;
        if (lightCSP==true) 
        {
          Serial.print(F("green down\n"));
          irsend.sendNEC(GREENDOWN,32);
          Alarm.delay(333);
        }
        else if (lightCSP==false)
        {
          writeToLED(2,currentColor.chan2);
        }
      }
    }
  }

  // Channel 3 (BLUE) /////////////////////////////////////////////////////////
  if(currentColor.chan3 != targetColor.chan3)
  {
    // Get the change per second for the current color to the target color
    difference = targetColor.chan3 - lastColor.chan3;
    tick = (float)durationInSeconds / (float)difference;

    // Get the expected change for the time elapsed
    value = round(secondsElapsed / tick);

    if(currentColor.chan3 < targetColor.chan3) // If the change is positive
    {
      // And if the current color does not match the expected color
      if(lastColor.chan3 + value > currentColor.chan3)
      {
        // Increase the current color
        currentColor.chan3++;
        if (lightCSP==true) 
        {
          Serial.print(F("blue up\n"));
          irsend.sendNEC(BLUEUP,32);
          Alarm.delay(333);
        }
        else if (lightCSP==false)
        {
          writeToLED(3,currentColor.chan3);
        }
      }
    }
    else if(currentColor.chan3 > targetColor.chan3)// If the change is negative
    {
      // And if the current color does not match the expected color
      if((lastColor.chan3 + value) < currentColor.chan3)
      {
        // Decrease the current color
        currentColor.chan3--;
        if (lightCSP==true) 
        {
          Serial.print(F("blue down\n"));
          irsend.sendNEC(BLUEDOWN,32);
          Alarm.delay(333);
        }
        else if (lightCSP==false)
        {
          writeToLED(3,currentColor.chan3);
        }
      }
    }
  }

  // Channel 4 (WHITE) /////////////////////////////////////////////////////////
  if(currentColor.chan4 != targetColor.chan4)
  {
    // Get the change per second for the current color to the target color
    difference = targetColor.chan4 - lastColor.chan4;
    tick = (float)durationInSeconds / (float)difference;

    // Get the expected change for the time elapsed
    value = round(secondsElapsed / tick);

    if(currentColor.chan4 < targetColor.chan4) // If the change is positive
    {
      // And if the current color does not match the expected color
      if(lastColor.chan4 + value > currentColor.chan4)
      {
        // Increase the current color
        currentColor.chan4++;
        if (lightCSP==true) 
        {
          Serial.print(F("White up\n"));
          irsend.sendNEC(WHITEUP,32);
          Alarm.delay(333);
        }
        else if (lightCSP==false)
        {
          writeToLED(4,currentColor.chan4);
        }
      }
    }
    else if(currentColor.chan4 > targetColor.chan4)// If the change is negative
    {
      // And if the current color does not match the expected color
      if((lastColor.chan4 + value) < currentColor.chan4)
      {
        // Decrease the current color
        currentColor.chan4--;
        if (lightCSP==true) 
        {
          Serial.print(F("white down\n"));
          irsend.sendNEC(WHITEDOWN, 32);
          Alarm.delay(333);
        }
        else if (lightCSP==false)
        {
          writeToLED(4,currentColor.chan4);
        }
      } 
    }
  }
  // Channel 5 /////////////////////////////////////////////////////////
  if(currentColor.chan5 != targetColor.chan5)
  {
    // Get the change per second for the current color to the target color
    difference = targetColor.chan5 - lastColor.chan5;
    tick = (float)durationInSeconds / (float)difference;
    
    // Get the expected change for the time elapsed
    value = round(secondsElapsed / tick);

    if(currentColor.chan5 < targetColor.chan5) // If the change is positive
    {
      // And if the current color does not match the expected color
      if(lastColor.chan5 + value > currentColor.chan5)
      {
        // Increase the current color
        currentColor.chan5++;
        if (lightCSP==false)
        {
          writeToLED(5,currentColor.chan5);
        }
      }
    }
    else if(currentColor.chan5 > targetColor.chan5)// If the change is negative
    {
      // And if the current color does not match the expected color
      if((lastColor.chan5 + value) < currentColor.chan5)
      {
        // Decrease the current color
        currentColor.chan5--;
        if (lightCSP==false)
        {
          writeToLED(5,currentColor.chan5);
        }
      } 
    }
  }
  // Channel 6 /////////////////////////////////////////////////////////
  if(currentColor.chan6 != targetColor.chan6)
  {
    // Get the change per second for the current color to the target color
    difference = targetColor.chan6 - lastColor.chan6;
    tick = (float)durationInSeconds / (float)difference;

    // Get the expected change for the time elapsed
    value = round(secondsElapsed / tick);

    if(currentColor.chan6 < targetColor.chan6) // If the change is positive
    {
      // And if the current color does not match the expected color
      if(lastColor.chan6 + value > currentColor.chan6)
      {
        // Increase the current color
        currentColor.chan6++;
        if (lightCSP==false)
        {
          writeToLED(6,currentColor.chan6);
        }
      }
    }
    else if(currentColor.chan6 > targetColor.chan6)// If the change is negative
    {
      // And if the current color does not match the expected color
      if((lastColor.chan6 + value) < currentColor.chan6)
      {
        // Decrease the current color
        currentColor.chan6--;
        if (lightCSP==false)
        {
          writeToLED(6,currentColor.chan6);
        }
      } 
    }
  }//end channel 6
}//end routine

void drawLEDBarGraph(byte barNum, int value)
{
  int x,y;
  char char5[5];
  
  Serial.print(F("Bargrah "));
  Serial.print(barNum);
  Serial.print(F(": "));
  Serial.print(value);
  Serial.println(F("%"));
    
  //determine xy coordinates based on bar being displayed
  if(barNum == 1){x=10;y=185;}
  if(barNum == 2){x=48;y=185;}
  if(barNum == 3){x=86;y=185;}
  if(barNum == 4){x=124;y=185;}
  if(barNum == 5){x=162;y=185;}
  if(barNum == 6){x=200;y=185;}
  
  //erase old bargraph & percentage
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(x-3,y-10,x+28,y-1);
  myGLCD.fillRect(x+1,y+1,x+27,y+99);
  
  //draw new bargraph
  myGLCD.setColor(VGAColor[barColors[barNum-1]]);
  myGLCD.drawRect(x,y,x+28,y+100);
  myGLCD.fillRect(x,(y+100-value),x+28,(y+100));
  
  //write percentage
  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(VGA_WHITE);
  itoa(value, char5, 10);
  strcat(char5,"%");
  if(value < 100) x = x + 8;
  if(value < 10) x = x + 8;
  myGLCD.print(char5,x-3,y-10);
}

void updateIRValues(byte prevColor, byte newColor, byte chan)
{
  //erase old bargraphs
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,169,239,290);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setFont(arial_bold);
  myGLCD.print(F("Sending"),60,200);
  myGLCD.print(F("IR signals"),20,220);
  
  byte difference;
  
  if( newColor > prevColor )
  {
    difference = newColor - prevColor;
    for(int x = prevColor; x != newColor; x++)
    {
      if(chan == 1)irsend.sendNEC(REDUP,32);
      if(chan == 2)irsend.sendNEC(GREENUP,32);
      if(chan == 3)irsend.sendNEC(BLUEUP,32);
      if(chan == 4)irsend.sendNEC(WHITEUP,32);
      Alarm.delay(333);
      displayUpdatingIR((newColor-x),difference);
    }
  }
  if( prevColor > newColor )
  {
    difference = prevColor - newColor;
    for(int x = prevColor; x != newColor; x--)
    {
      if(chan == 1)irsend.sendNEC(REDDOWN,32);
      if(chan == 2)irsend.sendNEC(GREENDOWN,32);
      if(chan == 3)irsend.sendNEC(BLUEDOWN,32);
      if(chan == 4)irsend.sendNEC(WHITEDOWN,32);
      Alarm.delay(333);
      displayUpdatingIR(abs(newColor-x),difference);
    }
  }
  // clear area
  myGLCD.setColor(0,0,0);
  myGLCD.fillRect(1,169,239,290);
  // draw bargraphs
  drawLEDBarGraph(1, currentColor.chan1);
  drawLEDBarGraph(2, currentColor.chan2);
  drawLEDBarGraph(3, currentColor.chan3);
  drawLEDBarGraph(4, currentColor.chan4);
  drawLEDBarGraph(5, currentColor.chan5);
  drawLEDBarGraph(6, currentColor.chan6);
}

void displayUpdatingIR(int x, byte difference)
{
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRect(20,240,220,260);
  unsigned int dx = 200 - ((x * 200) / difference);
  myGLCD.fillRect(20,240,(20+dx),260);
}

// returns scaling factor for current day in lunar cycle
byte lunarCycleScaling()
{
  byte scaleFactor[] = {25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,
                      95,90,85,80,75,70,65,60,55,50,45,40,35,30};
  tmElements_t fixedDate = {0,35,20,0,7,1,0};
  long lp = 2551443;
  time_t newMoonCycle = makeTime(fixedDate);
  long phase = (now() - newMoonCycle) % lp;
  long returnValue = ((phase / 86400) + 1);
  return scaleFactor[returnValue];
}

// returns day in lunar cycle 0-29
byte getLunarCycleDay()
{
  tmElements_t fixedDate = {0,35,20,0,7,1,0};
  long lp = 2551443;
  time_t newMoonCycle = makeTime(fixedDate);
  long phase = (now() - newMoonCycle) % lp;
  long returnValue = ((phase / 86400) + 1);
  return returnValue;
}

//writes value to LED channel
void writeToLED(byte chan, unsigned int value)
{
  //Send LED value to serial2 port
  Serial2.print("LED-");
  Serial2.print(chan);
  Serial2.print("-");
  Serial2.println(value);
  if(PCA9685Installed == true)
  {
    value = constrain(value,0,4096);
    chan = chan - 1;  //chan-1 because channel 1 is on PWM0 pin
    pwm.setPWM(chan,0,value); 
  }
  if(PCA9685Installed == false)
  {
    if(chan == 1)analogWrite(led1Pin, value);
    if(chan == 2)analogWrite(led2Pin, value);
    if(chan == 3)analogWrite(led3Pin, value);
    if(chan == 4)analogWrite(led4Pin, value);
    if(chan == 5)analogWrite(led5Pin, value);
    if(chan == 6)analogWrite(led6Pin, value);
  }
}
