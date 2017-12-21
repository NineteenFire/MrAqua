void firstRunSetup()
{
  // we need to track if this has EVER run, because we only want it to run once ever
  int EEPROMAddress = 2014;
  int EEPROMValue = 66;
  if(EEPROM.read(EEPROMAddress)!= EEPROMValue)
  {
    EEPROM.write(EEPROMAddress,EEPROMValue); // write to EEPROM so this never runs again

    // default screen settings
    EEPROM.write(28,2); 
    EEPROM.write(29,5);
    EEPROM.write(30,30);
    EEPROM.write(31,255);

    // set default feeding values on first launch
    EEPROM.write(1,1);   // 6 // feeding enable filter
    EEPROM.write(2,1);   // 6 // feeding enable circ
    EEPROM.write(3,1);   // 6 // feeding enable heat
    EEPROM.write(4,1);   // 6 // feeding enable co2
    EEPROM.write(5,1);   // 6 // feeding enable aux1
    EEPROM.write(6,1);   // 6 // feeding enable aux2
    EEPROM.write(7,10);  // 7 // feeding minutes setting
    EEPROM.write(8,1);   // 8 // feeding  light 1 (0 off, 1 on)
    EEPROM.write(9,1);   // 9 // feeding pwr light 2 (0 off, 1 on)
    EEPROM.write(10,1);  // 10 // feeding pwr filter (0 off, 1 on)
    EEPROM.write(11,0);  // 11 // feeding pwr circ (0 off, 1 on)
    EEPROM.write(12,1);  // 12 // feeding pwr heat (0 off, 1 on)
    EEPROM.write(13,1);  // 13 // feeding pwr co2 (0 off, 1 on)
    EEPROM.write(14,0);  // 14 // feeding pwr aux 1 (0 off, 1 on)
    EEPROM.write(15,0);  // 15 // feeding pwr aux 2 (0 off, 1 on)

    // set default heater values on first launch
    EEPROM.write(16,1);  // 16 // heater settings saved (0 for no, 1 for yes)
    EEPROM.write(17,29); // 17 // heater off temp
    EEPROM.write(18,25); // 18 // heater on temp
    EEPROM.write(19,30); // 19 // heater alarm temp

    // power schedules, zero them all out
    EEPROM.write(100,0);   // lights1 isActive
    EEPROM.write(101,0);   //         on hour
    EEPROM.write(102,0);   //         on minute
    EEPROM.write(103,0);   //         off hour
    EEPROM.write(104,0);   //         off minute
    EEPROM.write(105,0);   // lights2
    EEPROM.write(106,0);   //
    EEPROM.write(107,0);   //
    EEPROM.write(108,0);   //
    EEPROM.write(109,0);   //
    EEPROM.write(110,0);   // circulation pump
    EEPROM.write(111,0);   //
    EEPROM.write(112,0);   //
    EEPROM.write(113,0);   //
    EEPROM.write(114,0);   //
    EEPROM.write(115,0);   // CO2
    EEPROM.write(116,0);   //
    EEPROM.write(117,0);   //
    EEPROM.write(118,0);   //
    EEPROM.write(119,0);   //
    EEPROM.write(120,0);   // Aux1
    EEPROM.write(121,0);   //
    EEPROM.write(122,0);   //
    EEPROM.write(123,0);   //
    EEPROM.write(124,0);   //
    EEPROM.write(125,0);   // Aux2
    EEPROM.write(126,0);   //
    EEPROM.write(127,0);   //
    EEPROM.write(128,0);   //
    EEPROM.write(129,0);   //
    EEPROM.write(130,0);   // lights1 s2
    EEPROM.write(131,0);   //
    EEPROM.write(132,0);   //
    EEPROM.write(133,0);   //
    EEPROM.write(134,0);   // 
    EEPROM.write(135,0);   //lights2 s2
    EEPROM.write(136,0);   //
    EEPROM.write(137,0);   //
    EEPROM.write(138,0);   //
    EEPROM.write(139,0);   //
    EEPROM.write(140,0);   //Aux1 timer
    EEPROM.write(141,0);   //Aux2 timer

    //light ramp schedules
    EEPROM.write(220,6);   // ramp1 on hour
    EEPROM.write(221,0);   // ramp1 on minute
    EEPROM.write(222,1);   // ramp1 off hour
    EEPROM.write(223,0);   // ramp1 off minute
    EEPROM.write(224,8);   // ramp2 
    EEPROM.write(225,0);   //
    EEPROM.write(226,1);   //
    EEPROM.write(227,0);   //
    EEPROM.write(228,11);   // ramp3 
    EEPROM.write(229,0);   //
    EEPROM.write(230,1);   //
    EEPROM.write(231,0);   //
    EEPROM.write(232,18);   // ramp4 
    EEPROM.write(233,0);   //
    EEPROM.write(234,1);   //
    EEPROM.write(235,0);   //
    EEPROM.write(236,20);   // ramp5 
    EEPROM.write(237,0);   //
    EEPROM.write(238,1);   //
    EEPROM.write(239,0);   //
    EEPROM.write(240,22);   // ramp6 
    EEPROM.write(241,0);   //
    EEPROM.write(242,1);   //
    EEPROM.write(243,0);   //
    
    // dosing schedules
    EEPROM.write(300,7);   // pump1 on hour
    EEPROM.write(301,0);   //       on minute
    EEPROM.write(302,0);   //       Sun
    EEPROM.write(303,1);   //       Mon
    EEPROM.write(304,0);   //       Tue
    EEPROM.write(305,1);   //       Wed
    EEPROM.write(306,0);   //       Thur
    EEPROM.write(307,1);   //       Fri
    EEPROM.write(308,0);   //       Sat
    EEPROM.write(309,7);   // pump2
    EEPROM.write(310,0);   //
    EEPROM.write(311,0);   //
    EEPROM.write(312,0);   //
    EEPROM.write(313,1);   //
    EEPROM.write(314,0);   //
    EEPROM.write(315,1);   //
    EEPROM.write(316,0);   //
    EEPROM.write(317,1);   //
    EEPROM.write(318,10);  // pump3
    EEPROM.write(319,0);   //
    EEPROM.write(320,1);   //
    EEPROM.write(321,1);   //
    EEPROM.write(322,1);   //
    EEPROM.write(323,1);   //
    EEPROM.write(324,1);   //
    EEPROM.write(325,1);   //
    EEPROM.write(326,1);   //
    
    // light bar colours
    EEPROM.write(80,0);  // bar 1 color index
    EEPROM.write(81,1);  // bar 2 color index
    EEPROM.write(82,2);  // bar 3 color index
    EEPROM.write(83,3);  // bar 4 color index
    EEPROM.write(84,4);  // bar 5 color index
    EEPROM.write(85,5);  // bar 6 color index
    EEPROM.write(86,3);  // bar 7 color index
    EEPROM.write(87,3);  // bar 8 color index
    EEPROM.write(88,3);  // bar 9 color index
    EEPROM.write(89,3);  // bar 10 color index
    
    //ATO settings
    EEPROM.write(40,0);   // 40 // ATO Enabled
    EEPROM.write(41,0);   // 41 // Reservoir switch Enabled
    EEPROM.write(42,60);  // 42 // Low level wait time in minutes
    EEPROM.write(43,18);  // 43 // Max run-time (multiple of 10 seconds)
    EEPROM.write(44,0);   // 44 // ATO alarm
    
    // Sensor information
    EEPROM.write(50,1);    // 50 // Temp sensor 1 installed (water)
    EEPROM.write(51,0);    // 51 // Temp sensor 2 installed (heatsink)
    EEPROM.write(52,0);    // 52 // Internal sensor installed (MCP9701)
    EEPROM.write(53,40);   // 53 // Heatsink fan on temperature
    EEPROM.write(54,35);   // 54 // Heatsink fan off temperature
    EEPROM.write(55,40);   // 55 // Internal fan on temperature
    EEPROM.write(56,35);   // 56 // Internal fan off temperature
    EEPROM.write(57,1);    // 57 // Display in celcius?
    EEPROM.write(58,128);  // 58 // sensor 1 calibration offset
    EEPROM.write(59,128);  // 59 // sensor 2 calibration offset
    EEPROM.write(60,128);  // 60 // sensor 3 calibration offset
    EEPROM.write(61,1);    // 61 // display sensor 1 on home screen
    EEPROM.write(62,1);    // 62 // display sensor 1 on home screen
    EEPROM.write(63,0);    // 63 // display sensor 1 on home screen
    
    // Pump information
    EEPROM.write(20,10);  // 20 // pump 1 dose in mL
    EEPROM.write(21,10);  // 21 // pump 2 dose in mL
    EEPROM.write(22,5);   // 22 // pump 3 dose in mL
    EEPROM.write(23,80);  // 23 // pump 1 ms^10/ml
    EEPROM.write(24,80);  // 24 // pump 2 ms^10/ml
    EEPROM.write(25,80);  // 25 // pump 3 ms^10/ml
    EEPROM.write(26,100); // 26 // dosing 1 reseviors capacity in mL
    EEPROM.write(27,0);   // 27 // dosing 2 reserviors capacity in ML
    EEPROM.write(261,100); // 28 // dosing 3 reserviors capacity in mL
    EEPROM.write(262,0);   // 27 // dosing 2 reserviors capacity in ML
    EEPROM.write(263,100); // 28 // dosing 3 reserviors capacity in mL
    EEPROM.write(264,0);   // 28 // dosing 3 reserviors capacity in mL
    
    EEPROM.write(32,100); // remaining volume for pump 1 (high byte ^10)
    EEPROM.write(33,0);   // remaining volume for pump 1 (low byte)
    EEPROM.write(34,100); // remaining volume for pump 2 (high byte ^10)
    EEPROM.write(35,0);   // remaining volume for pump 2 (low byte)
    EEPROM.write(36,100); // remaining volume for pump 3 (high byte ^10)
    EEPROM.write(37,0);   // remaining volume for pump 3 (low byte)
    
    // RGBW values         // 0=high sun, 1=mid sun, 2=low sun, 3=moon
    EEPROM.write(400,0);   // HS red
    EEPROM.write(401,0);   // HS green
    EEPROM.write(402,0);   // HS blue
    EEPROM.write(403,0);   // HS cool white
    EEPROM.write(404,0);   // HS warm white
    EEPROM.write(405,0);   // HS UV
    EEPROM.write(406,0);   //    chan7
    EEPROM.write(407,0);   //    chan8
    EEPROM.write(408,0);   //    chan9
    EEPROM.write(409,0);   //    chan10
    EEPROM.write(410,0);   // MS
    EEPROM.write(411,0);   // 
    EEPROM.write(412,0);   // 
    EEPROM.write(413,0);   // 
    EEPROM.write(414,0);   // 
    EEPROM.write(415,0);   // 
    EEPROM.write(416,0);   // 
    EEPROM.write(417,0);   // 
    EEPROM.write(418,0);   // 
    EEPROM.write(419,0);   // 
    EEPROM.write(420,0);   // LS
    EEPROM.write(421,0);   // 
    EEPROM.write(422,0);   // 
    EEPROM.write(423,0);   // 
    EEPROM.write(424,0);   // 
    EEPROM.write(425,0);   // 
    EEPROM.write(426,0);   // 
    EEPROM.write(427,0);   // 
    EEPROM.write(428,0);   // 
    EEPROM.write(429,0);   // 
    EEPROM.write(430,0);   // Moon
    EEPROM.write(431,0);   // 
    EEPROM.write(432,0);   // 
    EEPROM.write(433,0);   // 
    EEPROM.write(434,0);   // 
    EEPROM.write(435,0);   // 
    EEPROM.write(436,0);   // 
    EEPROM.write(437,0);   // 
    EEPROM.write(438,0);   // 
    EEPROM.write(439,0);   // 
    
    // Weather effects
    EEPROM.write(70,0);       // lunar cycle enabled
    EEPROM.write(71,0);       // Cloud effects enabled
    EEPROM.write(72,B111111); // channels enabled
    EEPROM.write(73,0);       // length in minutes
    EEPROM.write(74,0);       // thunderstorm enabled
    EEPROM.write(75,B111111); // channels enabled
    EEPROM.write(76,0);       // length in minutes
    EEPROM.write(77,0);   // 
    EEPROM.write(78,0);   // 
    EEPROM.write(79,0);   // 
  }
  if(EEPROM.read(EEPROMAddress+1)!= EEPROMValue)
  {
    EEPROM.write(EEPROMAddress+1,EEPROMValue);
    EEPROM.write(1,1);   // 6 // feeding enable filter
    EEPROM.write(2,1);   // 6 // feeding enable circ
    EEPROM.write(3,1);   // 6 // feeding enable heat
    EEPROM.write(4,1);   // 6 // feeding enable co2
    EEPROM.write(5,1);   // 6 // feeding enable aux1
    EEPROM.write(6,1);   // 6 // feeding enable aux2
  }
}

void readSensorSettings()
{
  sensor1Enabled = EEPROM.read(50);
  sensor2Enabled = EEPROM.read(51);
  sensor3Enabled = EEPROM.read(52);
  heatsinkFanOnTemp = EEPROM.read(53);
  heatsinkFanOffTemp = EEPROM.read(54);
  internalFanOnTemp = EEPROM.read(55);
  internalFanOffTemp = EEPROM.read(56);
  
  heatOffTemp=EEPROM.read(17);
  heatOnTemp=EEPROM.read(18);
  
  byte storedVal = EEPROM.read(58);
  sensor1Calibration = ((float)storedVal - 128) / 10;
  storedVal = EEPROM.read(59);
  sensor2Calibration = ((float)storedVal - 128) / 10;
  storedVal = EEPROM.read(60);
  sensor3Calibration = ((float)storedVal - 128) / 10;
  
  displaySensor1 = EEPROM.read(61);
  displaySensor2 = EEPROM.read(62);
  displaySensor3 = EEPROM.read(63);
  
  displayInC = EEPROM.read(57);
  
  Serial.print(F("sensor1Calibration: "));
  Serial.println(sensor1Calibration);
  Serial.print(F("sensor2Calibration: "));
  Serial.println(sensor2Calibration);
  Serial.print(F("sensor3Calibration: "));
  Serial.println(sensor3Calibration);
}

void readPowerSchedule()
{
  // load power schedule from eeprom
  schedLights1.active = EEPROM.read(100);
  schedLights1.onHour = EEPROM.read(101);
  schedLights1.onMinute = EEPROM.read(102);
  schedLights1.offHour = EEPROM.read(103);
  schedLights1.offMinute = EEPROM.read(104);
  
  schedLights1s2.active = EEPROM.read(130);  
  schedLights1s2.onHour = EEPROM.read(131);
  schedLights1s2.onMinute = EEPROM.read(132);
  schedLights1s2.offHour = EEPROM.read(133);
  schedLights1s2.offMinute = EEPROM.read(134);
  
  schedLights2.active = EEPROM.read(105);
  schedLights2.onHour = EEPROM.read(106);
  schedLights2.onMinute = EEPROM.read(107);
  schedLights2.offHour = EEPROM.read(108);
  schedLights2.offMinute = EEPROM.read(109);
  
  schedLights2s2.active = EEPROM.read(135);
  schedLights2s2.onHour = EEPROM.read(136);
  schedLights2s2.onMinute = EEPROM.read(137);
  schedLights2s2.offHour = EEPROM.read(138);
  schedLights2s2.offMinute = EEPROM.read(139);
  
  schedCirc.active = EEPROM.read(110);
  schedCirc.onHour = EEPROM.read(111);
  schedCirc.onMinute = EEPROM.read(112);
  schedCirc.offHour = EEPROM.read(113);
  schedCirc.offMinute = EEPROM.read(114);
  
  schedCo2.active = EEPROM.read(115);
  schedCo2.onHour = EEPROM.read(116);
  schedCo2.onMinute = EEPROM.read(117);
  schedCo2.offHour = EEPROM.read(118);
  schedCo2.offMinute = EEPROM.read(119);
  
  schedAux1.active = EEPROM.read(120);
  schedAux1.onHour = EEPROM.read(121);
  schedAux1.onMinute = EEPROM.read(122);
  schedAux1.offHour = EEPROM.read(123);
  schedAux1.offMinute = EEPROM.read(124);
  schedAux1.timer = EEPROM.read(140);
  
  schedAux2.active = EEPROM.read(125);
  schedAux2.onHour = EEPROM.read(126);
  schedAux2.onMinute = EEPROM.read(127);
  schedAux2.offHour = EEPROM.read(128);
  schedAux2.offMinute = EEPROM.read(129);
  schedAux2.timer = EEPROM.read(141);
  
  if(schedAux1.timer > 1)
  {
    EEPROM.write(140,0);   //Aux1 timer
    schedAux1.timer = 0;
  }
  if(schedAux2.timer > 1)
  {
    EEPROM.write(141,0);   //Aux2 timer
    schedAux2.timer = 0;
  }
}

void readRampSchedule()
{
  // load lighting ramp schedule from eeprom
  ramp1.onHour = EEPROM.read(220);
  ramp1.onMinute = EEPROM.read(221);
  ramp1.offHour = EEPROM.read(222);
  ramp1.offMinute = EEPROM.read(223);

  ramp2.onHour = EEPROM.read(224);
  ramp2.onMinute = EEPROM.read(225);
  ramp2.offHour = EEPROM.read(226);
  ramp2.offMinute = EEPROM.read(227);

  ramp3.onHour = EEPROM.read(228);
  ramp3.onMinute = EEPROM.read(229);
  ramp3.offHour = EEPROM.read(230);
  ramp3.offMinute = EEPROM.read(231);

  ramp4.onHour = EEPROM.read(232);
  ramp4.onMinute = EEPROM.read(233);
  ramp4.offHour = EEPROM.read(234);
  ramp4.offMinute = EEPROM.read(235);

  ramp5.onHour = EEPROM.read(236);
  ramp5.onMinute = EEPROM.read(237);
  ramp5.offHour = EEPROM.read(238);
  ramp5.offMinute = EEPROM.read(239);

  ramp6.onHour = EEPROM.read(240);
  ramp6.onMinute = EEPROM.read(241);
  ramp6.offHour = EEPROM.read(242);
  ramp6.offMinute = EEPROM.read(243);
}

void readDosingSchedule()
{
  // load dosing schedule from eeprom
  pump1.onHour = EEPROM.read(300);
  pump1.onMinute = EEPROM.read(301);

  pump1.Sunday = EEPROM.read(302);
  pump1.Monday = EEPROM.read(303);
  pump1.Tuesday = EEPROM.read(304);
  pump1.Wednesday = EEPROM.read(305);
  pump1.Thursday = EEPROM.read(306);
  pump1.Friday = EEPROM.read(307);
  pump1.Saturday = EEPROM.read(308);

  pump2.onHour = EEPROM.read(309);
  pump2.onMinute = EEPROM.read(310);

  pump2.Sunday = EEPROM.read(311);
  pump2.Monday = EEPROM.read(312);
  pump2.Tuesday = EEPROM.read(313);
  pump2.Wednesday = EEPROM.read(314);
  pump2.Thursday = EEPROM.read(315);
  pump2.Friday = EEPROM.read(316);
  pump2.Saturday = EEPROM.read(317);

  pump3.onHour = EEPROM.read(318);
  pump3.onMinute = EEPROM.read(319);

  pump3.Sunday = EEPROM.read(320);
  pump3.Monday = EEPROM.read(321);
  pump3.Tuesday = EEPROM.read(322);
  pump3.Wednesday = EEPROM.read(323);
  pump3.Thursday = EEPROM.read(324);
  pump3.Friday = EEPROM.read(325);
  pump3.Saturday = EEPROM.read(326);
}

void readFeedSettings()
{
  feedSetting.pwrFilter=EEPROM.read(1);
  feedSetting.pwrCirc=EEPROM.read(2);
  feedSetting.pwrHeat=EEPROM.read(3);
  feedSetting.pwrCO2=EEPROM.read(4);
  feedSetting.pwrAux1=EEPROM.read(5);
  feedSetting.pwrAux2=EEPROM.read(6);
  
  feedingMins=EEPROM.read(7);
  
  feedPower.pwrLight1=EEPROM.read(8);
  feedPower.pwrLight2=EEPROM.read(9);
  feedPower.pwrFilter=EEPROM.read(10);
  feedPower.pwrCirc=EEPROM.read(11);
  feedPower.pwrHeat=EEPROM.read(12);
  feedPower.pwrCO2=EEPROM.read(13);
  feedPower.pwrAux1=EEPROM.read(14);
  feedPower.pwrAux2=EEPROM.read(15);
}

void readATOSettings()
{
  ATORunTime = (EEPROM.read(43))*10;
  ATOWaitTime = (EEPROM.read(42))*60;
  ATOEnabled = EEPROM.read(40);
  ResSwitchEnabled = EEPROM.read(41);
  ATOAlarm = EEPROM.read(44);
}

void readScreenSettings()
{
  screenRetHome = EEPROM.read(28);  //How long to wait before returning home
  screenDimLevel = EEPROM.read(29); //Brightness during idle
  screenDimSec = EEPROM.read(30);   //How long to wait for idle
  screenBrightMem = EEPROM.read(31);//Brightness during operation
  //change to v2.4.0 where stored value is %/10 (ie 1 is 10%)
  if(screenBrightMem > 10)
  {
    screenBrightMem = 10;
    EEPROM.write(31,10);
  }
  screenBrightness = screenBrightMem * 25;
}

void readBargraphColors()
{
  for(int i = 0; i < 6 ; i++)
  {
    barColors[i] = EEPROM.read(80+i);
  }
}

// Giving some big credit here, my original version of the smart startup had several bugs with schedules wrapping past midnight.
// This new smart startup routine was reworked and fixed by robsworld78 at The Planted Tank forums
void smartStartup()
{
  // get the current time in UNIX time, which is FAR easier for time calculations and comparisons
  // also must set UTC offset for mktime to calcuate stuff correct
  time_t currentStamp = now();
  time_t midnight = tmConvert_t(year(),month(),day(),23,59,59); // current day 11:59:59pm
  //Might work: time_t midnight = nextMidnight(now());
  time_t powerOn;
  time_t powerOff;
  time_t powerOffNextDay;

  //// POWER STARTUP:  LIGHTS 1
  // read in the power schedule and see if we are at a time when it should be on
  if (schedLights1.active == 1) 
  {
    time_t powerOn = tmConvert_t(year(),month(),day(),schedLights1.onHour,schedLights1.onMinute,0); // get a unix time stamp for the power on
    time_t powerOff = tmConvert_t(year(),month(),day(),schedLights1.offHour,schedLights1.offMinute,0); // get a unix time stamp for the power off  
    time_t powerOffNextDay = tmConvert_t(year(),month(),day(),schedLights1.offHour,schedLights1.offMinute,0);   
    powerOffNextDay = powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrLight1_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrLight1_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrLight1_On();
      else AlarmPwrLight1_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrLight1_On();
    else  AlarmPwrLight1_Off();
  }
  if((schedLights1s2.active == 1)&&(globalPower.pwrLight1 == false))
  {
    time_t powerOn = tmConvert_t(year(),month(),day(),schedLights1s2.onHour,schedLights1s2.onMinute,0); // get a unix time stamp for the power on
    time_t powerOff = tmConvert_t(year(),month(),day(),schedLights1s2.offHour,schedLights1s2.offMinute,0); // get a unix time stamp for the power off  
    time_t powerOffNextDay = tmConvert_t(year(),month(),day(),schedLights1s2.offHour,schedLights1s2.offMinute,0);   
    powerOffNextDay = powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrLight1_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrLight1_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrLight1_On();
      else AlarmPwrLight1_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrLight1_On();
    else  AlarmPwrLight1_Off();
  }

  //// POWER STARTUP:  LIGHTS 2
  // read in the power schedule and see if we are at a time when it should be on
  if (schedLights2.active == 1) 
  {  
    powerOn = tmConvert_t(year(),month(),day(),schedLights2.onHour,schedLights2.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedLights2.offHour,schedLights2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedLights2.offHour,schedLights2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrLight2_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrLight2_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrLight2_On();
      else AlarmPwrLight2_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrLight2_On();
    else AlarmPwrLight2_Off();
  }
  if((schedLights2s2.active == 1)&&(globalPower.pwrLight2 == false))
  {  
    powerOn = tmConvert_t(year(),month(),day(),schedLights2s2.onHour,schedLights2s2.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedLights2s2.offHour,schedLights2s2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedLights2s2.offHour,schedLights2s2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrLight2_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrLight2_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrLight2_On();
      else AlarmPwrLight2_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrLight2_On();
    else AlarmPwrLight2_Off();
  }

  //// POWER STARTUP:  FILTER  
  AlarmPwrFilter_On(); // the filter is ALWAYS ON

  //// POWER STARTUP:  CIRCULATION PUMP
  // read in the power schedule and see if we are at a time when it should be on
  if (schedCirc.active == 1) 
  {
    powerOn = tmConvert_t(year(),month(),day(),schedCirc.onHour,schedCirc.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedCirc.offHour,schedCirc.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedCirc.offHour,schedCirc.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay=powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrCirc_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrCirc_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrCirc_On();
      else AlarmPwrCirc_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrCirc_On();
    else AlarmPwrCirc_Off();
  }    

  //// POWER STARTUP:  HEATER  
  AlarmPwrHeat_On(); // the heater is ALWAYS ON

  //// POWER STARTUP:  CO2
  // read in the power schedule and see if we are at a time when it should be on
  if (schedCo2.active == 1) 
  {
    powerOn = tmConvert_t(year(),month(),day(),schedCo2.onHour,schedCo2.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedCo2.offHour,schedCo2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedCo2.offHour,schedCo2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay=powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrCO2_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrCO2_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrCO2_On();
      else AlarmPwrCO2_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrCO2_On();
    else AlarmPwrCO2_Off();
  }

  //// POWER STARTUP:  AUX 1
  // read in the power schedule and see if we are at a time when it should be on
  if((schedAux1.active == 1)&&(schedAux1.timer == false))
  {
    powerOn = tmConvert_t(year(),month(),day(),schedAux1.onHour,schedAux1.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedAux1.offHour,schedAux1.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedAux1.offHour,schedAux1.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay=powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrAux1_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrAux1_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrAux1_On();
      else AlarmPwrAux1_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrAux1_On();
    else AlarmPwrAux1_Off();
  }
  else if((schedAux1.active == 1)&&(schedAux1.timer == true))
  {
    AlarmPwrAux1_Timer();
  }
  
  //// POWER STARTUP:  AUX 2
  // read in the power schedule and see if we are at a time when it should be on
  if((schedAux2.active == 1)&&(schedAux2.timer == false))
  {
    powerOn = tmConvert_t(year(),month(),day(),schedAux2.onHour,schedAux2.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedAux2.offHour,schedAux2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedAux2.offHour,schedAux2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay=powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrAux2_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrAux2_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrAux2_On();
      else AlarmPwrAux2_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrAux2_On();
    else AlarmPwrAux2_Off();
  }
  else if((schedAux2.active == 1)&&(schedAux2.timer == true))
  {
    AlarmPwrAux2_Timer();
  }

  // lighting mode is restored to value with closest start time after current time
  smartStartupRamp();
  setStartupLighting();
}

void smartStartupRamp()
{
  time_t currentStamp = now();
  time_t midnight = tmConvert_t(year(),month(),day(),23,59,59); // current day 11:59:59pm
  time_t rampStart1 = tmConvert_t(year(),month(),day(),ramp1.onHour,ramp1.onMinute,0);
  time_t rampStart2 = tmConvert_t(year(),month(),day(),ramp2.onHour,ramp2.onMinute,0);
  time_t rampStart3 = tmConvert_t(year(),month(),day(),ramp3.onHour,ramp3.onMinute,0);
  time_t rampStart4 = tmConvert_t(year(),month(),day(),ramp4.onHour,ramp4.onMinute,0);
  time_t rampStart5 = tmConvert_t(year(),month(),day(),ramp5.onHour,ramp5.onMinute,0);
  time_t rampStart6 = tmConvert_t(year(),month(),day(),ramp6.onHour,ramp6.onMinute,0);

  //// Ramp 2 after midnight
  if ((rampStart2<rampStart1) && (currentStamp>rampStart1))
  {
    currentLightMode=2;
  }
  else if ((rampStart2<rampStart1) && (currentStamp<rampStart2))
  {
    currentLightMode=2;
  }    
  else if (((rampStart2<rampStart1) && (currentStamp>rampStart2) && (currentStamp<rampStart3)))
  {
    currentLightMode=1;
  } 
  else if (((rampStart2<rampStart1) && (currentStamp>rampStart3) && (currentStamp<rampStart4)))
  {
    currentLightMode=0;
  } 
  else if (((rampStart2<rampStart1) && (currentStamp>rampStart4) && (currentStamp<rampStart5)))
  {
    currentLightMode=1;
  } 
  else if (((rampStart2<rampStart1) && (currentStamp>rampStart5) && (currentStamp<rampStart6)))
  {
    currentLightMode=2;
  }       
  //// Ramp 3 after midnight
  else if (((rampStart2>rampStart1) && (rampStart3<rampStart1) && (currentStamp>rampStart2)))
  {
    currentLightMode=1;
  }
  else if (((rampStart2>rampStart1) && (rampStart3<rampStart1) && (currentStamp<rampStart3)))
  {
    currentLightMode=1;
  }    
  else if ((((rampStart2>rampStart1) && (rampStart3<rampStart1) && (currentStamp>rampStart3) && (currentStamp<rampStart4))))
  {
    currentLightMode=0;
  } 
  else if ((((rampStart2>rampStart1) && (rampStart3<rampStart1) && (currentStamp>rampStart4) && (currentStamp<rampStart5))))
  {
    currentLightMode=1;
  } 
  else if ((((rampStart2>rampStart1) && (rampStart3<rampStart1) && (currentStamp>rampStart5) && (currentStamp<rampStart6))))
  {
    currentLightMode=2;
  }      
  //// Ramp 4 after midnight
  else if ((((rampStart2>rampStart1) && (rampStart3>rampStart1) && (rampStart4<rampStart1) && (currentStamp>rampStart3))))
  {
    currentLightMode=0;
  }
  else if ((((rampStart2>rampStart1) && (rampStart3>rampStart1) && (rampStart4<rampStart1) && (currentStamp<rampStart4))))
  {
    currentLightMode=0;
  }    
  else if (((((rampStart2>rampStart1) && (rampStart3>rampStart1) && (rampStart4<rampStart1) && (currentStamp>rampStart4) && (currentStamp<rampStart5)))))
  {
    currentLightMode=1;
  } 
  else if (((((rampStart2>rampStart1) && (rampStart3>rampStart1) && (rampStart4<rampStart1) && (currentStamp>rampStart5) && (currentStamp<rampStart6)))))
  {
    currentLightMode=2;
  }  
  //// Ramp 5 after midnight
  else if (((((rampStart2>rampStart1) && (rampStart3>rampStart1) && (rampStart4>rampStart1) && (rampStart5<rampStart1) && (currentStamp>rampStart4)))))  ////winner
  {
    currentLightMode=1;
  }
  else if (((((rampStart2>rampStart1) && (rampStart3>rampStart1) && (rampStart4>rampStart1) && (rampStart5<rampStart1) && (currentStamp<rampStart5))))) /// after midnight
  {
    currentLightMode=1;
  }    
  else if ((((((rampStart2>rampStart1) && (rampStart3>rampStart1) && (rampStart4>rampStart1) && (rampStart5<rampStart1) && (currentStamp>rampStart5) && (currentStamp<rampStart6))))))
  {  
    currentLightMode=2;
  }
  //// Ramp 6 after midnight  
  else if ((((((rampStart2>rampStart1) && (rampStart3>rampStart1) && (rampStart4>rampStart1) && (rampStart5>rampStart1) && (rampStart6<rampStart1) && (currentStamp>rampStart5))))))
  {
    currentLightMode=2;
  }
  else if ((((((rampStart2>rampStart1) && (rampStart3>rampStart1) && (rampStart4>rampStart1) && (rampStart5>rampStart1) && (rampStart6<rampStart1) && (currentStamp<rampStart6))))))
  {
    currentLightMode=2;
  }    
  else if (((((((rampStart2>rampStart1) && (rampStart3>rampStart1) && (rampStart4>rampStart1) && (rampStart5>rampStart1) && (rampStart6<rampStart1) && (currentStamp>rampStart6) && (currentStamp<rampStart1)))))))
  {
    currentLightMode=3;
  }   
  //// start of regular ramping during 24hr period       
  else if ((currentStamp>rampStart1) && (currentStamp<rampStart2)) // if we are after ramp 1
  {
    currentLightMode=2;
  }  
  else if ((currentStamp>rampStart2) && (currentStamp<rampStart3)) // if we are not in the previous ramp, but are still before this one
  {
    currentLightMode=1;
  }
  else if ((currentStamp>rampStart3) && (currentStamp<rampStart4)) // if we are not in the previous ramp, but are still before this one
  {
    currentLightMode=0;
  }
  else if ((currentStamp>rampStart4) && (currentStamp<rampStart5)) // if we are not in the previous ramp, but are still before this one
  {
    currentLightMode=1;
  }
  else if ((currentStamp>rampStart5) && (currentStamp<rampStart6)) // if we are not in the previous ramp, but are still before this one
  {
    currentLightMode=2;
  }
  else if ((currentStamp>rampStart6) && (currentStamp<rampStart1+86400)) // if we are not in the previous ramp, but are still before this one
  {
    currentLightMode=3;
  }
  else if ((currentStamp<midnight) && (currentStamp<rampStart1)) // if we are not in the previous ramp, but are still before this one
  {
    currentLightMode=3;
  }
}

void setStartupLighting()
{
  if (currentLightMode==0)
  {
    currentColor = lightHighSun;
    if(lightCSP==true)irsend.sendNEC(M1,32);
  }
  else if (currentLightMode==1)
  {
    currentColor = lightMidSun;
    if(lightCSP==true)irsend.sendNEC(M2,32);
  }
  else if (currentLightMode==2)
  {
    currentColor = lightLowSun;
    if(lightCSP==true)irsend.sendNEC(M3,32);
  }
  else if (currentLightMode==3)
  {
    currentColor = lightMoon;
    if(lightCSP==true)irsend.sendNEC(M4,32);
  }
  else 
  {
    currentColor = lightLowSun;
    if(lightCSP==true)irsend.sendNEC(M3,32);
  }
  
  if(lightCSP == false)
  {
    if(PCA9685Installed == true)  //if using PCA9685 scale values to 12-bit
    {
      currentColor.chan1 = map(currentColor.chan1,0,100,0,4095);
      currentColor.chan2 = map(currentColor.chan2,0,100,0,4095);
      currentColor.chan3 = map(currentColor.chan3,0,100,0,4095);
      currentColor.chan4 = map(currentColor.chan4,0,100,0,4095);
      currentColor.chan5 = map(currentColor.chan5,0,100,0,4095);
      currentColor.chan6 = map(currentColor.chan6,0,100,0,4095);
    } else  //otherwise scale to 8-bit
    {
      currentColor.chan1 = map(currentColor.chan1,0,100,0,255);
      currentColor.chan2 = map(currentColor.chan2,0,100,0,255);
      currentColor.chan3 = map(currentColor.chan3,0,100,0,255);
      currentColor.chan4 = map(currentColor.chan4,0,100,0,255);
      currentColor.chan5 = map(currentColor.chan5,0,100,0,255);
      currentColor.chan6 = map(currentColor.chan6,0,100,0,255);
    }
    writeToLED(1,currentColor.chan1);
    writeToLED(2,currentColor.chan2);
    writeToLED(3,currentColor.chan3);
    writeToLED(4,currentColor.chan4);
    writeToLED(5,currentColor.chan5);
    writeToLED(6,currentColor.chan6);
  }
}

void smartStartupPower()
{
  // get the current time in UNIX time, which is FAR easier for time calculations and comparisons
  // also must set UTC offset for mktime to calcuate stuff correct
  time_t currentStamp = now();
  time_t midnight = tmConvert_t(year(),month(),day(),23,59,59); // current day 11:59:59pm
  //Might work: time_t midnight = nextMidnight(now());
  time_t powerOn;
  time_t powerOff;
  time_t powerOffNextDay;

  //// POWER STARTUP:  LIGHTS 1
  // read in the power schedule and see if we are at a time when it should be on
  if (schedLights1.active == 1) 
  {
    time_t powerOn = tmConvert_t(year(),month(),day(),schedLights1.onHour,schedLights1.onMinute,0); // get a unix time stamp for the power on
    time_t powerOff = tmConvert_t(year(),month(),day(),schedLights1.offHour,schedLights1.offMinute,0); // get a unix time stamp for the power off  
    time_t powerOffNextDay = tmConvert_t(year(),month(),day(),schedLights1.offHour,schedLights1.offMinute,0);   
    powerOffNextDay = powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrLight1_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrLight1_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrLight1_On();
      else AlarmPwrLight1_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrLight1_On();
    else  AlarmPwrLight1_Off();
  }
  if((schedLights1s2.active == 1)&&(globalPower.pwrLight1 == false))
  {
    time_t powerOn = tmConvert_t(year(),month(),day(),schedLights1s2.onHour,schedLights1s2.onMinute,0); // get a unix time stamp for the power on
    time_t powerOff = tmConvert_t(year(),month(),day(),schedLights1s2.offHour,schedLights1s2.offMinute,0); // get a unix time stamp for the power off  
    time_t powerOffNextDay = tmConvert_t(year(),month(),day(),schedLights1s2.offHour,schedLights1s2.offMinute,0);   
    powerOffNextDay = powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrLight1_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrLight1_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrLight1_On();
      else AlarmPwrLight1_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrLight1_On();
    else  AlarmPwrLight1_Off();
  }

  //// POWER STARTUP:  LIGHTS 2
  // read in the power schedule and see if we are at a time when it should be on
  if (schedLights2.active == 1) 
  {  
    powerOn = tmConvert_t(year(),month(),day(),schedLights2.onHour,schedLights2.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedLights2.offHour,schedLights2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedLights2.offHour,schedLights2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrLight2_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrLight2_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrLight2_On();
      else AlarmPwrLight2_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrLight2_On();
    else AlarmPwrLight2_Off();
  }
  if((schedLights2s2.active == 1)&&(globalPower.pwrLight2 == false))
  {  
    powerOn = tmConvert_t(year(),month(),day(),schedLights2s2.onHour,schedLights2s2.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedLights2s2.offHour,schedLights2s2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedLights2s2.offHour,schedLights2s2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrLight2_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrLight2_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrLight2_On();
      else AlarmPwrLight2_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrLight2_On();
    else AlarmPwrLight2_Off();
  }

  //// POWER STARTUP:  FILTER  
  AlarmPwrFilter_On(); // the filter is ALWAYS ON

  //// POWER STARTUP:  CIRCULATION PUMP
  // read in the power schedule and see if we are at a time when it should be on
  if (schedCirc.active == 1) 
  {
    powerOn = tmConvert_t(year(),month(),day(),schedCirc.onHour,schedCirc.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedCirc.offHour,schedCirc.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedCirc.offHour,schedCirc.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay=powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrCirc_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrCirc_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrCirc_On();
      else AlarmPwrCirc_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrCirc_On();
    else AlarmPwrCirc_Off();
  }    

  //// POWER STARTUP:  HEATER  
  AlarmPwrHeat_On(); // the heater is ALWAYS ON

  //// POWER STARTUP:  CO2
  // read in the power schedule and see if we are at a time when it should be on
  if (schedCo2.active == 1) 
  {
    powerOn = tmConvert_t(year(),month(),day(),schedCo2.onHour,schedCo2.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedCo2.offHour,schedCo2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedCo2.offHour,schedCo2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay=powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrCO2_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrCO2_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrCO2_On();
      else AlarmPwrCO2_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrCO2_On();
    else AlarmPwrCO2_Off();
  }

  //// POWER STARTUP:  AUX 1
  // read in the power schedule and see if we are at a time when it should be on
  if ((schedAux1.active == 1)&&(schedAux1.timer == false))
  {
    powerOn = tmConvert_t(year(),month(),day(),schedAux1.onHour,schedAux1.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedAux1.offHour,schedAux1.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedAux1.offHour,schedAux1.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay=powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrAux1_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrAux1_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrAux1_On();
      else AlarmPwrAux1_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrAux1_On();
    else AlarmPwrAux1_Off();
  }

  //// POWER STARTUP:  AUX 2
  // read in the power schedule and see if we are at a time when it should be on
  if ((schedAux2.active == 1)&&(schedAux2.timer == false))
  {
    powerOn = tmConvert_t(year(),month(),day(),schedAux2.onHour,schedAux2.onMinute,0); // get a unix time stamp for the power on
    powerOff = tmConvert_t(year(),month(),day(),schedAux2.offHour,schedAux2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay = tmConvert_t(year(),month(),day(),schedAux2.offHour,schedAux2.offMinute,0); // get a unix time stamp for the power off  
    powerOffNextDay=powerOffNextDay+86400;

    if (powerOn==powerOff) AlarmPwrAux2_On();
    else if (powerOn>powerOff) 
    {
      if ((currentStamp>=powerOn) && (powerOffNextDay>=midnight)) AlarmPwrAux2_On();
      else if (((currentStamp<=powerOn) && (currentStamp<=powerOff) && (powerOffNextDay>=midnight))) AlarmPwrAux2_On();
      else AlarmPwrAux2_Off();
    }
    else if ((currentStamp>=powerOn) && (currentStamp<=powerOff)) AlarmPwrAux2_On();
    else AlarmPwrAux2_Off();
  }
}
