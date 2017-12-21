void updateAlarms()
{
  // clear, free, delete all possible alarms
  for (byte i=0; i<=50; i++) Alarm.free(i);

  //////// POWER ALARMS ////////
  if (schedLights1.active==1)
  {
    Alarm.alarmRepeat(schedLights1.onHour,schedLights1.onMinute,0,AlarmPwrLight1_On);
    Alarm.alarmRepeat(schedLights1.offHour,schedLights1.offMinute,0,AlarmPwrLight1_Off);
  }
  if (schedLights1s2.active==1)
  {
    Alarm.alarmRepeat(schedLights1s2.onHour,schedLights1s2.onMinute,0,AlarmPwrLight1_On);
    Alarm.alarmRepeat(schedLights1s2.offHour,schedLights1s2.offMinute,0,AlarmPwrLight1_Off);
  }
  if (schedLights2.active==1)
  {
    Alarm.alarmRepeat(schedLights2.onHour,schedLights2.onMinute,0,AlarmPwrLight2_On);
    Alarm.alarmRepeat(schedLights2.offHour,schedLights2.offMinute,0,AlarmPwrLight2_Off);
  }
  if (schedLights2s2.active==1)
  {
    Alarm.alarmRepeat(schedLights2s2.onHour,schedLights2s2.onMinute,0,AlarmPwrLight2_On);
    Alarm.alarmRepeat(schedLights2s2.offHour,schedLights2s2.offMinute,0,AlarmPwrLight2_Off);
  }
  if (schedCirc.active==1)
  {
    Alarm.alarmRepeat(schedCirc.onHour,schedCirc.onMinute,0,AlarmPwrCirc_On);
    Alarm.alarmRepeat(schedCirc.offHour,schedCirc.offMinute,0,AlarmPwrCirc_Off);
  }
  if (schedCo2.active==1)
  {
    Alarm.alarmRepeat(schedCo2.onHour,schedCo2.onMinute,0,AlarmPwrCO2_On);
    Alarm.alarmRepeat(schedCo2.offHour,schedCo2.offMinute,0,AlarmPwrCO2_Off);
  }
  if (schedAux1.active==1)
  {
    if(schedAux1.timer==0)
    {
      Alarm.alarmRepeat(schedAux1.onHour,schedAux1.onMinute,0,AlarmPwrAux1_On);
      Alarm.alarmRepeat(schedAux1.offHour,schedAux1.offMinute,0,AlarmPwrAux1_Off);
    }else
    {
      Alarm.timerRepeat(schedAux1.onHour,schedAux1.onMinute,0,AlarmPwrAux1_Timer);
    }
  }
  if (schedAux2.active==1)
  {
    if(schedAux1.timer==0)
    {
      Alarm.alarmRepeat(schedAux2.onHour,schedAux2.onMinute,0,AlarmPwrAux2_On);
      Alarm.alarmRepeat(schedAux2.offHour,schedAux2.offMinute,0,AlarmPwrAux2_Off);
    }else
    {
      Alarm.timerRepeat(schedAux2.onHour,schedAux2.onMinute,0,AlarmPwrAux2_Timer);
    }
  }

  //////// RAMP ALARMS ////////
  Alarm.alarmRepeat(ramp1.onHour,ramp1.onMinute,0,AlarmRamp1);
  Alarm.alarmRepeat(ramp2.onHour,ramp2.onMinute,0,AlarmRamp2);
  Alarm.alarmRepeat(ramp3.onHour,ramp3.onMinute,0,AlarmRamp3);
  Alarm.alarmRepeat(ramp4.onHour,ramp4.onMinute,0,AlarmRamp4);
  Alarm.alarmRepeat(ramp5.onHour,ramp5.onMinute,0,AlarmRamp5);
  Alarm.alarmRepeat(ramp6.onHour,ramp6.onMinute,0,AlarmRamp6);
  
  //////// Ramp PWM to 0, 4 hours after ramp6 ////////
  byte zeroHour = ((ramp6.onHour + 4) % 24);
  byte zeroMin = ramp6.onMinute;
  Alarm.alarmRepeat(zeroHour,zeroMin,0,rampToZero);
  
  //////// DOSING ALARMS ////////
  if (pump1.Sunday==1)
  {
    Alarm.alarmRepeat(dowSunday, pump1.onHour,pump1.onMinute,0,AlarmMacros);
  }
  if (pump2.Sunday==1)
  {
    Alarm.alarmRepeat(dowSunday, pump2.onHour,pump2.onMinute,0,AlarmMicros);
  }
  if (pump3.Sunday==1)
  {
    Alarm.alarmRepeat(dowSunday, pump3.onHour,pump3.onMinute,0,AlarmExcel);
  }
  if (pump1.Monday==1)
  {
    Alarm.alarmRepeat(dowMonday, pump1.onHour,pump1.onMinute,0,AlarmMacros);
  }
  if (pump2.Monday==1)
  {
    Alarm.alarmRepeat(dowMonday, pump2.onHour,pump2.onMinute,0,AlarmMicros);
  }
  if (pump3.Monday==1)
  {
    Alarm.alarmRepeat(dowMonday, pump3.onHour,pump3.onMinute,0,AlarmExcel);
  }
  if (pump1.Tuesday==1)
  {
    Alarm.alarmRepeat(dowTuesday, pump1.onHour,pump1.onMinute,0,AlarmMacros);
  }
  if (pump2.Tuesday==1)
  {
    Alarm.alarmRepeat(dowTuesday, pump2.onHour,pump2.onMinute,0,AlarmMicros);
  }
  if (pump3.Tuesday==1)
  {
    Alarm.alarmRepeat(dowTuesday, pump3.onHour,pump3.onMinute,0,AlarmExcel);
  }
  if (pump1.Wednesday==1)
  {
    Alarm.alarmRepeat(dowWednesday, pump1.onHour,pump1.onMinute,0,AlarmMacros);
  }
  if (pump2.Wednesday==1)
  {
    Alarm.alarmRepeat(dowWednesday, pump2.onHour,pump2.onMinute,0,AlarmMicros);
  }
  if (pump3.Wednesday==1)
  {
    Alarm.alarmRepeat(dowWednesday, pump3.onHour,pump3.onMinute,0,AlarmExcel);
  }
  if (pump1.Thursday==1)
  {
    Alarm.alarmRepeat(dowThursday, pump1.onHour,pump1.onMinute,0,AlarmMacros);
  }
  if (pump2.Thursday==1)
  {
    Alarm.alarmRepeat(dowThursday, pump2.onHour,pump2.onMinute,0,AlarmMicros);
  }
  if (pump3.Thursday==1)
  {
    Alarm.alarmRepeat(dowThursday, pump3.onHour,pump3.onMinute,0,AlarmExcel);
  }
  if (pump1.Friday==1)
  {
    Alarm.alarmRepeat(dowFriday, pump1.onHour,pump1.onMinute,0,AlarmMacros);
  }
  if (pump2.Friday==1)
  {
    Alarm.alarmRepeat(dowFriday, pump2.onHour,pump2.onMinute,0,AlarmMicros);
  }
  if (pump3.Friday==1)
  {
    Alarm.alarmRepeat(dowFriday, pump3.onHour,pump3.onMinute,0,AlarmExcel);
  }
  if (pump1.Saturday==1)
  {
    Alarm.alarmRepeat(dowSaturday, pump1.onHour,pump1.onMinute,0,AlarmMacros);
  }
  if (pump2.Saturday==1)
  {
    Alarm.alarmRepeat(dowSaturday, pump2.onHour,pump2.onMinute,0,AlarmMicros);
  }
  if (pump3.Saturday==1)
  {
    Alarm.alarmRepeat(dowSaturday, pump3.onHour,pump3.onMinute,0,AlarmExcel);
  }
  Serial.print(F("# of alarms: "));
  Serial.println(Alarm.count());
}

//===Light1 routines===

void AlarmPwrLight1_On() 
{
  digitalWrite(pwrLight1Pin, HIGH);
  globalPower.pwrLight1=1;
  if (dispScreen==1) myFiles.load(178, 121, 24, 24, pwrLightIconS[globalPower.pwrLight1]);
}
void AlarmPwrLight1_Off()
{
  digitalWrite(pwrLight1Pin, LOW);
  globalPower.pwrLight1 = 0;
  if (dispScreen==1) myFiles.load(178, 121, 24, 24, pwrLightIconS[globalPower.pwrLight1]); // update home screen
}

//===Light2 routines===

void AlarmPwrLight2_On()
{
  digitalWrite(pwrLight2Pin, HIGH);
  globalPower.pwrLight2=1;
  if (dispScreen==1) myFiles.load(206, 121, 24, 24, pwrLightIconS[globalPower.pwrLight2]);
}
void AlarmPwrLight2_Off()
{
  digitalWrite(pwrLight2Pin, LOW);
  globalPower.pwrLight2 = 0;
  if (dispScreen==1) myFiles.load(206, 121, 24, 24, pwrLightIconS[globalPower.pwrLight2]); // update home screen
}

//===CO2 routines===

void AlarmPwrCO2_On()
{
  if((feedingActive==true)&&(feedSetting.pwrCO2==true))
  {
    preFeedPower.pwrCO2 = 1;
  }else
  {
    digitalWrite(pwrCO2Pin, HIGH);
    globalPower.pwrCO2=1;
  }
  //if (dispScreen==1) myFiles.load(206, 177, 24, 24, pwrCO2IconS[globalPower.pwrCO2]);
  if (dispScreen==1) myFiles.load(178, 177, 24, 24, pwrCO2IconS[globalPower.pwrCO2]);//co2/heat swapped
}
void AlarmPwrCO2_Off()
{
  if((feedingActive==true)&&(feedSetting.pwrCO2==true))
  {
    preFeedPower.pwrCO2 = 0;
  }else
  {
    digitalWrite(pwrCO2Pin, LOW);
    globalPower.pwrCO2 = 0;
  }
  //if (dispScreen==1) myFiles.load(206, 177, 24, 24, pwrCO2IconS[globalPower.pwrCO2]); // update home screen
  if (dispScreen==1) myFiles.load(178, 177, 24, 24, pwrCO2IconS[globalPower.pwrCO2]); //co2/heat swapped
}
void pwrCO2_On()
{
  digitalWrite(pwrCO2Pin, HIGH);
  globalPower.pwrCO2=1;
  //if (dispScreen==1) myFiles.load(206, 177, 24, 24, pwrCO2IconS[globalPower.pwrCO2]);
  if (dispScreen==1) myFiles.load(178, 177, 24, 24, pwrCO2IconS[globalPower.pwrCO2]);//co2/heat swapped
}
void pwrCO2_Off()
{
  digitalWrite(pwrCO2Pin, LOW);
  globalPower.pwrCO2 = 0;
  //if (dispScreen==1) myFiles.load(206, 177, 24, 24, pwrCO2IconS[globalPower.pwrCO2]); // update home screen
  if (dispScreen==1) myFiles.load(178, 177, 24, 24, pwrCO2IconS[globalPower.pwrCO2]); //co2/heat swapped
}

//===Circ routines===

void AlarmPwrCirc_On() 
{
  if((feedingActive==true)&&(feedSetting.pwrCirc==true))
  {
    preFeedPower.pwrCirc = 1;
  }else
  {
    digitalWrite(pwrCircPin, HIGH);
    globalPower.pwrCirc=1;
  }
  if (dispScreen==1) myFiles.load(206, 149, 24, 24, pwrCircIconS[globalPower.pwrCirc]);
}
void AlarmPwrCirc_Off()
{
  if((feedingActive==true)&&(feedSetting.pwrCirc==true))
  {
    preFeedPower.pwrCirc = 0;
  }else
  {
    digitalWrite(pwrCircPin, LOW);
    globalPower.pwrCirc = 0;
  }
  if (dispScreen==1) myFiles.load(206, 149, 24, 24, pwrCircIconS[globalPower.pwrCirc]); // update home screen
}
void pwrCirc_On() //turn outlet on regardless of feeding
{
  digitalWrite(pwrCircPin, HIGH);
  globalPower.pwrCirc=1;
  preFeedPower.pwrCirc = 1;
  if (dispScreen==1) myFiles.load(206, 149, 24, 24, pwrCircIconS[globalPower.pwrCirc]);
}
void pwrCirc_Off()
{
  digitalWrite(pwrCircPin, LOW);
  globalPower.pwrCirc = 0;
  preFeedPower.pwrCirc = 0;
  if (dispScreen==1) myFiles.load(206, 149, 24, 24, pwrCircIconS[globalPower.pwrCirc]); // update home screen
}

//===Filter routines===

void AlarmPwrFilter_On() 
{
  //turn outlet on if not feeding, otherwise set prefeed to on so outlet turns on after feeding
  if((feedingActive==true)&&(feedSetting.pwrFilter==true))
  {
    preFeedPower.pwrFilter = 1;
  }else
  {
    digitalWrite(pwrFilterPin, HIGH);
    globalPower.pwrFilter=1;
  }
  if (dispScreen==1) myFiles.load(178, 149, 24, 24, pwrFilterIconS[globalPower.pwrFilter]); 
}
void AlarmPwrFilter_Off()
{
  if((feedingActive==true)&&(feedSetting.pwrFilter==true))
  {
    preFeedPower.pwrFilter = 0;
  }else
  {
    digitalWrite(pwrFilterPin, LOW);
    globalPower.pwrFilter = 0;
  }
  if (dispScreen==1) myFiles.load(178, 149, 24, 24, pwrFilterIconS[globalPower.pwrFilter]); // update home screen
}
void pwrFilter_On() //turn outlet on regardless of feeding
{
  digitalWrite(pwrFilterPin, HIGH);
  globalPower.pwrFilter=1;
  preFeedPower.pwrFilter = 1;
  if (dispScreen==1) myFiles.load(178, 149, 24, 24, pwrFilterIconS[globalPower.pwrFilter]); // update home screen
}
void pwrFilter_Off()
{
  digitalWrite(pwrFilterPin, LOW);
  globalPower.pwrFilter = 0;
  preFeedPower.pwrFilter = 0;
  if (dispScreen==1) myFiles.load(178, 149, 24, 24, pwrFilterIconS[globalPower.pwrFilter]); // update home screen
}

//===Heater routines===

void AlarmPwrHeat_On()
{
  if((feedingActive==true)&&(feedSetting.pwrHeat==true))
  {
    preFeedPower.pwrHeat = 1;
  }else
  {
    digitalWrite(pwrHeatPin, HIGH);
    globalPower.pwrHeat=1;
  }
  //if (dispScreen==1) myFiles.load(178, 177, 24, 24, pwrHeatIconS[globalPower.pwrHeat]); // update home screen
  if (dispScreen==1) myFiles.load(206, 177, 24, 24, pwrHeatIconS[globalPower.pwrHeat]); //co2/heater swapped
}
void AlarmPwrHeat_Off()
{
  if((feedingActive==true)&&(feedSetting.pwrHeat==true))
  {
    preFeedPower.pwrHeat = 0;
  }else
  {
    digitalWrite(pwrHeatPin, LOW);
    globalPower.pwrHeat = 0;
  }
  //if (dispScreen==1) myFiles.load(178, 177, 24, 24, pwrHeatIconS[globalPower.pwrHeat]); // update home screen
  if (dispScreen==1) myFiles.load(206, 177, 24, 24, pwrHeatIconS[globalPower.pwrHeat]); //co2/heater swapped
}
void pwrHeat_On()
{
  digitalWrite(pwrHeatPin, HIGH);
  globalPower.pwrHeat=1;
  //if (dispScreen==1) myFiles.load(178, 177, 24, 24, pwrHeatIconS[globalPower.pwrHeat]); // update home screen
  if (dispScreen==1) myFiles.load(206, 177, 24, 24, pwrHeatIconS[globalPower.pwrHeat]); //co2/heater swapped
}
void pwrHeat_Off()
{
  digitalWrite(pwrHeatPin, LOW);
  globalPower.pwrHeat = 0;
  //if (dispScreen==1) myFiles.load(178, 177, 24, 24, pwrHeatIconS[globalPower.pwrHeat]); // update home screen
  if (dispScreen==1) myFiles.load(206, 177, 24, 24, pwrHeatIconS[globalPower.pwrHeat]); //co2/heater swapped
}

//===Aux1 routines===

void AlarmPwrAux1_On()
{
  if((feedingActive==true)&&(feedSetting.pwrAux1==true))
  {
    preFeedPower.pwrAux1 = 1;
  }else
  {
    digitalWrite(pwrAux1Pin, HIGH);
    globalPower.pwrAux1=1;
  }
  if (dispScreen==1) myFiles.load(178, 205, 24, 24, pwrAux1IconS[globalPower.pwrAux1]); // update home screen
}
void AlarmPwrAux1_Off()
{
  if((feedingActive==true)&&(feedSetting.pwrCirc==true))
  {
    preFeedPower.pwrAux1 = 0;
  }else
  {
    digitalWrite(pwrAux1Pin, LOW);
    globalPower.pwrAux1 = 0;
  }
  if (dispScreen==1) myFiles.load(178, 205, 24, 24, pwrAux1IconS[globalPower.pwrAux1]); // update home screen
}
void pwrAux1_On() //turn outlet on regardless of feeding
{
  digitalWrite(pwrAux1Pin, HIGH);
  globalPower.pwrAux1=1;
  preFeedPower.pwrAux1 = 1;
  if (dispScreen==1) myFiles.load(178, 205, 24, 24, pwrAux1IconS[globalPower.pwrAux1]); // update home screen
}
void pwrAux1_Off()
{
  digitalWrite(pwrAux1Pin, LOW);
  globalPower.pwrAux1 = 0;
  preFeedPower.pwrAux1 = 0;
  if (dispScreen==1) myFiles.load(178, 205, 24, 24, pwrAux1IconS[globalPower.pwrAux1]); // update home screen
}
void AlarmPwrAux1_Timer()
{
  Serial.print(F("Aux1 Timer triggered.\n"));
  if((feedingActive==true)&&(feedSetting.pwrAux1==true))
  {
    preFeedPower.pwrAux1 = 1;
  }else
  {
    digitalWrite(pwrAux1Pin, HIGH);
    globalPower.pwrAux1=1;
  }
  aux1TimerState = true;
  aux1TimerStart = millis();
  aux1TimerFinish = (schedAux1.offHour * 60) + schedAux1.offMinute;
  aux1TimerFinish = aux1TimerFinish * 1000;
  
  if (dispScreen==1) myFiles.load(178, 205, 24, 24, pwrAux1IconS[globalPower.pwrAux1]); // update home screen
}

//===Aux2 routines===

void AlarmPwrAux2_On()
{
  if((feedingActive==true)&&(feedSetting.pwrAux2==true))
  {
    preFeedPower.pwrAux2 = 1;
  }else
  {
    digitalWrite(pwrAux2Pin, HIGH);
    globalPower.pwrAux2=1;
  }
  if (dispScreen==1) myFiles.load(206, 205, 24, 24, pwrAux2IconS[globalPower.pwrAux2]); // update home screen
}
void AlarmPwrAux2_Off()
{
  if((feedingActive==true)&&(feedSetting.pwrAux2==true))
  {
    preFeedPower.pwrAux2 = 0;
  }else
  {
    digitalWrite(pwrAux2Pin, LOW);
    globalPower.pwrAux2 = 0;
  }
  if (dispScreen==1) myFiles.load(206, 205, 24, 24, pwrAux2IconS[globalPower.pwrAux2]); // update home screen
}
void pwrAux2_On() //turn outlet on regardless of feeding
{
  digitalWrite(pwrAux2Pin, HIGH);
  globalPower.pwrAux2=1;
  preFeedPower.pwrAux2 = 1;
  if (dispScreen==1) myFiles.load(206, 205, 24, 24, pwrAux2IconS[globalPower.pwrAux2]); // update home screen
}
void pwrAux2_Off()
{
  digitalWrite(pwrAux2Pin, LOW);
  globalPower.pwrAux2 = 0;
  preFeedPower.pwrAux2 = 0;
  if (dispScreen==1) myFiles.load(206, 205, 24, 24, pwrAux2IconS[globalPower.pwrAux2]); // update home screen
}
void AlarmPwrAux2_Timer()
{
  if((feedingActive==true)&&(feedSetting.pwrAux2==true))
  {
    preFeedPower.pwrAux2 = 1;
  }else
  {
    digitalWrite(pwrAux2Pin, HIGH);
    globalPower.pwrAux2=1;
  }
  aux2TimerState = true;
  aux2TimerStart = millis();
  aux2TimerFinish = ((schedAux2.offHour * 60) + schedAux2.offMinute) * 1000;
  if (dispScreen==1) myFiles.load(206, 205, 24, 24, pwrAux2IconS[globalPower.pwrAux2]); // update home screen
}

//===Fan routines===

void alarmFan1on()
{
  digitalWrite(fan1Pin,HIGH);
  //Send command to turn remote fan on
  Serial2.println("FAN-ON");
}

void alarmFan1off()
{
  digitalWrite(fan1Pin,LOW);
  //Send command to turn remote fan off
  Serial2.println("FAN-OFF");
}

void alarmFan2on()
{
  digitalWrite(fan2Pin,HIGH);
}

void alarmFan2off()
{
  digitalWrite(fan2Pin,LOW);
}

//===Ramp alarms===

void AlarmRamp1()
{
  fadeFromMode = 3;  //0=high sun, 1=mid sun, 2=low sun, 3=moon
  fadeToMode = 2;  //0=high sun, 1=mid sun, 2=low sun, 3=moon

  // last color is the starting point of the fade
  lastColor.chan1 = currentColor.chan1;
  lastColor.chan2 = currentColor.chan2;
  lastColor.chan3 = currentColor.chan3;
  lastColor.chan4 = currentColor.chan4;
  lastColor.chan5 = currentColor.chan5;
  lastColor.chan6 = currentColor.chan6;

  // target color is low sun
  if(lightCSP == false)
  {
    //if using PCA9685 scale values to 12-bit
    if(PCA9685Installed == true)
    {
      targetColor.chan1 = map(lightLowSun.chan1,0,100,0,4095);
      targetColor.chan2 = map(lightLowSun.chan2,0,100,0,4095);
      targetColor.chan3 = map(lightLowSun.chan3,0,100,0,4095);
      targetColor.chan4 = map(lightLowSun.chan4,0,100,0,4095);
      targetColor.chan5 = map(lightLowSun.chan5,0,100,0,4095);
      targetColor.chan6 = map(lightLowSun.chan6,0,100,0,4095);
    } else
    {
      targetColor.chan1 = map(lightLowSun.chan1,0,100,0,255);
      targetColor.chan2 = map(lightLowSun.chan2,0,100,0,255);
      targetColor.chan3 = map(lightLowSun.chan3,0,100,0,255);
      targetColor.chan4 = map(lightLowSun.chan4,0,100,0,255);
      targetColor.chan5 = map(lightLowSun.chan5,0,100,0,255);
      targetColor.chan6 = map(lightLowSun.chan6,0,100,0,255);
    }
  }else
  {
    targetColor.chan1 = lightLowSun.chan1;
    targetColor.chan2 = lightLowSun.chan2;
    targetColor.chan3 = lightLowSun.chan3;
    targetColor.chan4 = lightLowSun.chan4;
    targetColor.chan5 = lightLowSun.chan5;
    targetColor.chan6 = lightLowSun.chan6;
  }

  // calculate how long to run the fade for
  int fadeHours = ramp1.offHour;
  int fadeMins = ramp1.offMinute;  
  fadeDurationSeconds = ((fadeHours*60*60)+(fadeMins*60));

  fadeStartingSeconds = now();
  fadeInProgress = true;
  currentLightMode=4;
  if (dispScreen==1) checkLighting();
  
  printRampValues(1);
}

void AlarmRamp2()
{
  fadeFromMode = 2;  //0=high sun, 1=mid sun, 2=low sun, 3=moon
  fadeToMode = 1;  //0=high sun, 1=mid sun, 2=low sun, 3=moon

  // last color is the starting point of the fade
  lastColor.chan1 = currentColor.chan1;
  lastColor.chan2 = currentColor.chan2;
  lastColor.chan3 = currentColor.chan3;
  lastColor.chan4 = currentColor.chan4;
  lastColor.chan5 = currentColor.chan5;
  lastColor.chan6 = currentColor.chan6;

  // target color is mid sun
  if(lightCSP == false)
  {
    //if using PCA9685 scale values to 12-bit
    if(PCA9685Installed == true)
    {
      targetColor.chan1 = map(lightMidSun.chan1,0,100,0,4095);
      targetColor.chan2 = map(lightMidSun.chan2,0,100,0,4095);
      targetColor.chan3 = map(lightMidSun.chan3,0,100,0,4095);
      targetColor.chan4 = map(lightMidSun.chan4,0,100,0,4095);
      targetColor.chan5 = map(lightMidSun.chan5,0,100,0,4095);
      targetColor.chan6 = map(lightMidSun.chan6,0,100,0,4095);
    } else
    {
      targetColor.chan1 = map(lightMidSun.chan1,0,100,0,255);
      targetColor.chan2 = map(lightMidSun.chan2,0,100,0,255);
      targetColor.chan3 = map(lightMidSun.chan3,0,100,0,255);
      targetColor.chan4 = map(lightMidSun.chan4,0,100,0,255);
      targetColor.chan5 = map(lightMidSun.chan5,0,100,0,255);
      targetColor.chan6 = map(lightMidSun.chan6,0,100,0,255);
    }
  }else
  {
    targetColor.chan1 = lightMidSun.chan1;
    targetColor.chan2 = lightMidSun.chan2;
    targetColor.chan3 = lightMidSun.chan3;
    targetColor.chan4 = lightMidSun.chan4;
    targetColor.chan5 = lightMidSun.chan5;
    targetColor.chan6 = lightMidSun.chan6;
  }

  // calculate how long to run the fade for
  int fadeHours = ramp2.offHour;
  int fadeMins = ramp2.offMinute;  
  fadeDurationSeconds = ((fadeHours*60*60)+(fadeMins*60));

  fadeStartingSeconds = now();
  fadeInProgress = true;
  currentLightMode=4;
  if (dispScreen==1) checkLighting();
  
  printRampValues(2);
}

void AlarmRamp3()
{
  fadeFromMode = 1;  //0=high sun, 1=mid sun, 2=low sun, 3=moon
  fadeToMode = 0;  //0=high sun, 1=mid sun, 2=low sun, 3=moon

  // last color is the starting point of the fade
  lastColor.chan1 = currentColor.chan1;
  lastColor.chan2 = currentColor.chan2;
  lastColor.chan3 = currentColor.chan3;
  lastColor.chan4 = currentColor.chan4;
  lastColor.chan5 = currentColor.chan5;
  lastColor.chan6 = currentColor.chan6;

  // target color is high sun
  if(lightCSP == false)
  {
    //if using PCA9685 scale values to 12-bit
    if(PCA9685Installed == true)
    {
      targetColor.chan1 = map(lightHighSun.chan1,0,100,0,4095);
      targetColor.chan2 = map(lightHighSun.chan2,0,100,0,4095);
      targetColor.chan3 = map(lightHighSun.chan3,0,100,0,4095);
      targetColor.chan4 = map(lightHighSun.chan4,0,100,0,4095);
      targetColor.chan5 = map(lightHighSun.chan5,0,100,0,4095);
      targetColor.chan6 = map(lightHighSun.chan6,0,100,0,4095);
    } else
    {
      targetColor.chan1 = map(lightHighSun.chan1,0,100,0,255);
      targetColor.chan2 = map(lightHighSun.chan2,0,100,0,255);
      targetColor.chan3 = map(lightHighSun.chan3,0,100,0,255);
      targetColor.chan4 = map(lightHighSun.chan4,0,100,0,255);
      targetColor.chan5 = map(lightHighSun.chan5,0,100,0,255);
      targetColor.chan6 = map(lightHighSun.chan6,0,100,0,255);
    }
  }else
  {
    targetColor.chan1 = lightHighSun.chan1;
    targetColor.chan2 = lightHighSun.chan2;
    targetColor.chan3 = lightHighSun.chan3;
    targetColor.chan4 = lightHighSun.chan4;
    targetColor.chan5 = lightHighSun.chan5;
    targetColor.chan6 = lightHighSun.chan6;
  }

  // calculate how long to run the fade for
  int fadeHours = ramp3.offHour;
  int fadeMins = ramp3.offMinute;  
  fadeDurationSeconds = ((fadeHours*60*60)+(fadeMins*60));

  fadeStartingSeconds = now();
  fadeInProgress = true;
  currentLightMode=4;
  if (dispScreen==1) checkLighting();
  
  printRampValues(3);
}

void AlarmRamp4()
{
  fadeFromMode = 0;  //0=high sun, 1=mid sun, 2=low sun, 3=moon
  fadeToMode = 1;  //0=high sun, 1=mid sun, 2=low sun, 3=moon

  // last color is the starting point of the fade
  lastColor.chan1 = currentColor.chan1;
  lastColor.chan2 = currentColor.chan2;
  lastColor.chan3 = currentColor.chan3;
  lastColor.chan4 = currentColor.chan4;
  lastColor.chan5 = currentColor.chan5;
  lastColor.chan6 = currentColor.chan6;

  // target color is mid sun
  if(lightCSP == false)
  {
    //if using PCA9685 scale values to 12-bit
    if(PCA9685Installed == true)
    {
      targetColor.chan1 = map(lightMidSun.chan1,0,100,0,4095);
      targetColor.chan2 = map(lightMidSun.chan2,0,100,0,4095);
      targetColor.chan3 = map(lightMidSun.chan3,0,100,0,4095);
      targetColor.chan4 = map(lightMidSun.chan4,0,100,0,4095);
      targetColor.chan5 = map(lightMidSun.chan5,0,100,0,4095);
      targetColor.chan6 = map(lightMidSun.chan6,0,100,0,4095);
    } else
    {
      targetColor.chan1 = map(lightMidSun.chan1,0,100,0,255);
      targetColor.chan2 = map(lightMidSun.chan2,0,100,0,255);
      targetColor.chan3 = map(lightMidSun.chan3,0,100,0,255);
      targetColor.chan4 = map(lightMidSun.chan4,0,100,0,255);
      targetColor.chan5 = map(lightMidSun.chan5,0,100,0,255);
      targetColor.chan6 = map(lightMidSun.chan6,0,100,0,255);
    }
  }else
  {
    targetColor.chan1 = lightMidSun.chan1;
    targetColor.chan2 = lightMidSun.chan2;
    targetColor.chan3 = lightMidSun.chan3;
    targetColor.chan4 = lightMidSun.chan4;
    targetColor.chan5 = lightMidSun.chan5;
    targetColor.chan6 = lightMidSun.chan6;
  }

  // calculate how long to run the fade for
  int fadeHours = ramp4.offHour;
  int fadeMins = ramp4.offMinute;  
  fadeDurationSeconds = ((fadeHours*60*60)+(fadeMins*60));

  fadeStartingSeconds = now();
  fadeInProgress = true;
  currentLightMode=4;
  if (dispScreen==1) checkLighting();
  
  printRampValues(4);
}

void AlarmRamp5()
{
  fadeFromMode = 1;  //0=high sun, 1=mid sun, 2=low sun, 3=moon
  fadeToMode = 2;  //0=high sun, 1=mid sun, 2=low sun, 3=moon

  // last color is the starting point of the fade
  lastColor.chan1 = currentColor.chan1;
  lastColor.chan2 = currentColor.chan2;
  lastColor.chan3 = currentColor.chan3;
  lastColor.chan4 = currentColor.chan4;
  lastColor.chan5 = currentColor.chan5;
  lastColor.chan6 = currentColor.chan6;

  // target color is low sun
  if(lightCSP == false)
  {
    //if using PCA9685 scale values to 12-bit
    if(PCA9685Installed == true)
    {
      targetColor.chan1 = map(lightLowSun.chan1,0,100,0,4095);
      targetColor.chan2 = map(lightLowSun.chan2,0,100,0,4095);
      targetColor.chan3 = map(lightLowSun.chan3,0,100,0,4095);
      targetColor.chan4 = map(lightLowSun.chan4,0,100,0,4095);
      targetColor.chan5 = map(lightLowSun.chan5,0,100,0,4095);
      targetColor.chan6 = map(lightLowSun.chan6,0,100,0,4095);
    } else
    {
      targetColor.chan1 = map(lightLowSun.chan1,0,100,0,255);
      targetColor.chan2 = map(lightLowSun.chan2,0,100,0,255);
      targetColor.chan3 = map(lightLowSun.chan3,0,100,0,255);
      targetColor.chan4 = map(lightLowSun.chan4,0,100,0,255);
      targetColor.chan5 = map(lightLowSun.chan5,0,100,0,255);
      targetColor.chan6 = map(lightLowSun.chan6,0,100,0,255);
    }
  }else
  {
    targetColor.chan1 = lightLowSun.chan1;
    targetColor.chan2 = lightLowSun.chan2;
    targetColor.chan3 = lightLowSun.chan3;
    targetColor.chan4 = lightLowSun.chan4;
    targetColor.chan5 = lightLowSun.chan5;
    targetColor.chan6 = lightLowSun.chan6;
  }

  // calculate how long to run the fade for
  int fadeHours = ramp5.offHour;
  int fadeMins = ramp5.offMinute;  
  fadeDurationSeconds = ((fadeHours*60*60)+(fadeMins*60));

  fadeStartingSeconds = now();
  fadeInProgress = true;
  currentLightMode=4;
  if (dispScreen==1) checkLighting();
  
  printRampValues(5);
}

void AlarmRamp6()
{
  fadeFromMode = 2;  //0=high sun, 1=mid sun, 2=low sun, 3=moon
  fadeToMode = 3;  //0=high sun, 1=mid sun, 2=low sun, 3=moon

  // last color is the starting point of the fade
  lastColor.chan1 = currentColor.chan1;
  lastColor.chan2 = currentColor.chan2;
  lastColor.chan3 = currentColor.chan3;
  lastColor.chan4 = currentColor.chan4;
  lastColor.chan5 = currentColor.chan5;
  lastColor.chan6 = currentColor.chan6;
  
  targetColor.chan1 = lightMoon.chan1;
  targetColor.chan2 = lightMoon.chan2;
  targetColor.chan3 = lightMoon.chan3;
  targetColor.chan4 = lightMoon.chan4;
  targetColor.chan5 = lightMoon.chan5;
  targetColor.chan6 = lightMoon.chan6;
  
  // check for lunar scaling enabled
  byte lunarEnabled = EEPROM.read(70);
  if (lunarEnabled == true)
  {
    //scale moon values based on lunar cycle from 0-100 to 0-Max percentage
    byte lunarValue = lunarCycleScaling();
    targetColor.chan1 = map(targetColor.chan1,0,100,0,lunarValue);
    targetColor.chan2 = map(targetColor.chan2,0,100,0,lunarValue);
    targetColor.chan3 = map(targetColor.chan3,0,100,0,lunarValue);
    targetColor.chan4 = map(targetColor.chan4,0,100,0,lunarValue);
    targetColor.chan5 = map(targetColor.chan5,0,100,0,lunarValue);
    targetColor.chan6 = map(targetColor.chan6,0,100,0,lunarValue);
  }

  // target color is moonlight
  if(lightCSP == false)
  {
    //if using PCA9685 scale values to 12-bit
    if(PCA9685Installed == true)
    {
      targetColor.chan1 = map(targetColor.chan1,0,100,0,4095);
      targetColor.chan2 = map(targetColor.chan2,0,100,0,4095);
      targetColor.chan3 = map(targetColor.chan3,0,100,0,4095);
      targetColor.chan4 = map(targetColor.chan4,0,100,0,4095);
      targetColor.chan5 = map(targetColor.chan5,0,100,0,4095);
      targetColor.chan6 = map(targetColor.chan6,0,100,0,4095);
    } else
    {
      targetColor.chan1 = map(targetColor.chan1,0,100,0,255);
      targetColor.chan2 = map(targetColor.chan2,0,100,0,255);
      targetColor.chan3 = map(targetColor.chan3,0,100,0,255);
      targetColor.chan4 = map(targetColor.chan4,0,100,0,255);
      targetColor.chan5 = map(targetColor.chan5,0,100,0,255);
      targetColor.chan6 = map(targetColor.chan6,0,100,0,255);
    }
  }

  // calculate how long to run the fade for
  int fadeHours = ramp6.offHour;
  int fadeMins = ramp6.offMinute;  
  fadeDurationSeconds = ((fadeHours*60*60)+(fadeMins*60));

  fadeStartingSeconds = now();
  fadeInProgress = true;
  currentLightMode=4;
  if (dispScreen==1) checkLighting();
  
  printRampValues(6);
}

void printRampValues(byte ramp)
{
  if(ramp == 0)
  {
    Serial.print(F("\nLight 1 shut off!\n"));
  }else
  {
    Serial.print(F("\nRamp "));
    Serial.print(ramp);
    Serial.print(F(" triggered!\n"));
  }
  Serial.print(F("Last Colors: "));
  Serial.print(lastColor.chan1);Serial.print(F(","));Serial.print(lastColor.chan2);Serial.print(F(","));
  Serial.print(lastColor.chan3);Serial.print(F(","));Serial.print(lastColor.chan4);Serial.print(F(","));
  Serial.print(lastColor.chan5);Serial.print(F(","));Serial.println(lastColor.chan6);
  Serial.print(F("Target Colors: "));
  Serial.print(targetColor.chan1);Serial.print(F(","));Serial.print(targetColor.chan2);Serial.print(F(","));
  Serial.print(targetColor.chan3);Serial.print(F(","));Serial.print(targetColor.chan4);Serial.print(F(","));
  Serial.print(targetColor.chan5);Serial.print(F(","));Serial.println(targetColor.chan6);
  Serial.print(F("fadeDurationSeconds: "));
  Serial.println(fadeDurationSeconds);
}

//===Pump alarms===

void AlarmMacros()
{
  Serial.print(F("Pump1 started.\n"));
  unsigned int pumpTime=EEPROM.read(23);  // 23 // pump 1 ms/ml
  unsigned int doseAmt=EEPROM.read(20); // 20 // dose in mL
  pumpTime=((pumpTime*10)*doseAmt); // multiply ms/mL by number of mL to pump
  analogWrite(dosingPump1, 255);
  
  pump1State = true;
  pump1StartMillis = millis();
  pump1millis = pumpTime;

  // update resevoir volume, storing as high/low bytes so we can store bigger numbers
  unsigned int vol_H=EEPROM.read(32); // read the remaining volume for pump 1 (high byte, ^10)
  unsigned int vol_L=EEPROM.read(33); // read the remaining volume for pump 1 (low byte)
  unsigned int vol=((vol_H*10)+vol_L); // combine high and low byte to get volume
  if(vol > doseAmt)
  {
    vol=(vol-doseAmt); // subtract off what we just dosed
    vol_H = vol / 10;
    vol_L = vol % 10;
  }else
  {
    vol_H = 0;
    vol_L = 0;
  }
  EEPROM.write(32,vol_H); // write high byte to memory
  EEPROM.write(33,vol_L); // write low byte to memory

  if (dispScreen==1) checkDosing(); // update home screen
}

void AlarmMicros()
{
  Serial.print(F("Pump2 started.\n"));
  unsigned int pumpTime=EEPROM.read(24);  // 24 // pump 2 sec/ml
  unsigned int doseAmt=EEPROM.read(21); // 21 // dose in mL
  pumpTime=((pumpTime*10)*doseAmt); // multiply ms/mL by number of mL to pump
  analogWrite(dosingPump2, 255);
  
  pump2State = true;
  pump2StartMillis = millis();
  pump2millis = pumpTime;

  // update resevoir volume, storing as high/low bytes so we can store bigger numbers
  unsigned int vol_H=EEPROM.read(34); // read the remaining volume for pump 1 (high byte, ^10)
  unsigned int vol_L=EEPROM.read(35); // read the remaining volume for pump 1 (low byte)
  unsigned int vol= ((vol_H*10)+vol_L); // combine high and low byte to get volume
  if(vol > doseAmt)
  {
    vol=vol-doseAmt; // subtract off what we just dosed
    vol_H=vol/10; // divide by 10 to get high byte
    vol_L=vol%10; // remainder is low byte
  }else
  {
    vol_H = 0;
    vol_L = 0;
  }
  EEPROM.write(34,vol_H); // write high byte to memory
  EEPROM.write(35,vol_L); // write low byte to memory

  if (dispScreen==1) checkDosing(); // update home screen
}

void AlarmExcel()
{
  Serial.print(F("Pump3 started.\n"));
  unsigned int pumpTime=EEPROM.read(25);  // 25 // pump 3 sec/ml
  unsigned int doseAmt=EEPROM.read(22); // 22 // dose in mL
  pumpTime=((pumpTime*10)*doseAmt); // multiply ms/mL by number of mL to pump
  analogWrite(dosingPump3, 255);
  
  pump3State = true;
  pump3StartMillis = millis();
  pump3millis = pumpTime;

  // update resevoir volume, storing as high/low bytes so we can store bigger numbers
  unsigned int vol_H=EEPROM.read(36); // read the remaining volume for pump 1 (high byte, ^10)
  unsigned int vol_L=EEPROM.read(37); // read the remaining volume for pump 1 (low byte)
  unsigned int vol= ((vol_H*10)+vol_L); // combine high and low byte to get volume
  if(vol > doseAmt)
  {
    vol=(vol-doseAmt); // subtract off what we just dosed
    vol_H=vol/10; // divide by 10 to get high byte
    vol_L=vol%10; // remainder is low byte
  }else
  {
    vol_H = 0;
    vol_L = 0;
  }
  EEPROM.write(36,vol_H); // write high byte to memory
  EEPROM.write(37,vol_L); // write low byte to memory

  if (dispScreen==1) checkDosing(); // update home screen
}

// run once per day at noon, reload moonlight values and if lunar cycle is enabled scale
// by percent based on current position of lunar calender (scales from 10-100%
void AlarmLunarScaling()
{
  //re-load moon values
  lightMoon.chan1=EEPROM.read(430);
  lightMoon.chan2=EEPROM.read(431);
  lightMoon.chan3=EEPROM.read(432);
  lightMoon.chan4=EEPROM.read(433);
  lightMoon.chan5=EEPROM.read(434);
  lightMoon.chan6=EEPROM.read(435);
  
  //if lunar cycle is enabled scale values
  byte lunarEnabled = EEPROM.read(70);
  if (lunarEnabled == true)
  {
    lightMoon.chan1 = (lunarCycleScaling() * lightMoon.chan1 ) / 100;
    lightMoon.chan2 = (lunarCycleScaling() * lightMoon.chan2 ) / 100;
    lightMoon.chan3 = (lunarCycleScaling() * lightMoon.chan3 ) / 100;
    lightMoon.chan4 = (lunarCycleScaling() * lightMoon.chan4 ) / 100;
    lightMoon.chan5 = (lunarCycleScaling() * lightMoon.chan5 ) / 100;
    lightMoon.chan6 = (lunarCycleScaling() * lightMoon.chan6 ) / 100;
  }
  
  if(lightCSP == false)
  {
    //if using PCA9685 scale values to 12-bit
    if(PCA9685Installed == true)
    {
      lightMoon.chan1 = map(lightMoon.chan1,0,100,0,4095);
      lightMoon.chan2 = map(lightMoon.chan2,0,100,0,4095);
      lightMoon.chan3 = map(lightMoon.chan3,0,100,0,4095);
      lightMoon.chan4 = map(lightMoon.chan4,0,100,0,4095);
      lightMoon.chan5 = map(lightMoon.chan5,0,100,0,4095);
      lightMoon.chan6 = map(lightMoon.chan6,0,100,0,4095);
    } else //scale for 8-bit
    {
      lightMoon.chan1 = map(lightMoon.chan1,0,100,0,255);
      lightMoon.chan2 = map(lightMoon.chan2,0,100,0,255);
      lightMoon.chan3 = map(lightMoon.chan3,0,100,0,255);
      lightMoon.chan4 = map(lightMoon.chan4,0,100,0,255);
      lightMoon.chan5 = map(lightMoon.chan5,0,100,0,255);
      lightMoon.chan6 = map(lightMoon.chan6,0,100,0,255);
    }
  }
}

// Turn off PWM signals when light1 is set to turn off, code can be removed to keep light 
// on until dawn, i just like having the lights completely off
void rampToZero()
{
  // last color is the starting point of the fade
  lastColor.chan1 = currentColor.chan1;
  lastColor.chan2 = currentColor.chan2;
  lastColor.chan3 = currentColor.chan3;
  lastColor.chan4 = currentColor.chan4;
  lastColor.chan5 = currentColor.chan5;
  lastColor.chan6 = currentColor.chan6;

  // target color is low sun
  targetColor.chan1 = 0;
  targetColor.chan2 = 0;
  targetColor.chan3 = 0;
  targetColor.chan4 = 0;
  targetColor.chan5 = 0;
  targetColor.chan6 = 0;

  fadeDurationSeconds = 1800; // fade to 0 in 30 minutes
  fadeStartingSeconds = now();
  fadeInProgress = true;
  fadeFromMode = 3;
  fadeToMode = 3;
  currentLightMode = 3;
  
  printRampValues(0);
}
