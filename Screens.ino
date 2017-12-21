void screenHome()  // draw main home screen showing overview info
{
  touchWaitTime = LONG_WAIT;
  if(dispScreen != 1)
  {
    myGLCD.clrScr(); // clear if not home
  }else
  {
    //myGLCD.setColor(0,0,0);
    //myGLCD.fillRect(0,32,239,254); // clear the screen between the header and the dock
  }
  
  dispScreen=1;  // set screen so we can know what screen was touched later
  
  updateTimeDate(true);

  // draw dock, home icon, and header
  myFiles.load(0, 254, 240, 66, "dock.raw",4);
  myFiles.load(2, 2, 30, 30, "1home.raw",4);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(34, 81, 255);
  myGLCD.print(F("HOME"), 36, 12);

  // draw lines to divide screen
  myGLCD.setColor(175, 175, 175);
  myGLCD.drawLine(40, 31, 239, 31); // under header  
  myGLCD.drawLine(0, 110, 239, 110); // across screen below temp
  myGLCD.drawLine(56, 110, 56, 237); // 1st cutting into 4ths
  myGLCD.drawLine(105, 110, 105, 237); // 2nd cutting into 4ths
  myGLCD.drawLine(168, 110, 168, 237); // 3rd cutting into 4ths
  myGLCD.drawLine(120, 31, 120, 110); // cutting top section in half for ATO

  myGLCD.drawLine(0, 237, 239, 237); // across above dock

  // draw temperature to screen
  drawTemp();

  // display feeding info
  drawFeeding();
  myFiles.load(5, 172, 46, 46, "1feed.raw",4);

  // display lighting info
  checkLighting();

  // get remainding doses
  checkDosing();
  
  // display ATO status
  drawATO();

  // draw power status of outputs
  myFiles.load(178, 121, 24, 24, pwrLightIconS[globalPower.pwrLight1],4);
  myFiles.load(206, 121, 24, 24, pwrLightIconS[globalPower.pwrLight2],4);
  myFiles.load(178, 149, 24, 24, pwrFilterIconS[globalPower.pwrFilter],4);
  myFiles.load(206, 149, 24, 24, pwrCircIconS[globalPower.pwrCirc],4);
  //swap locations of heater/co2 since my dc adaptor for co2 won't fit
  //myFiles.load(178, 177, 24, 24, pwrHeatIconS[globalPower.pwrHeat],4);//normal
  //myFiles.load(206, 177, 24, 24, pwrCO2IconS[globalPower.pwrCO2],4);  //normal
  myFiles.load(178, 177, 24, 24, pwrCO2IconS[globalPower.pwrCO2],4);//swapped
  myFiles.load(206, 177, 24, 24, pwrHeatIconS[globalPower.pwrHeat],4);//swapped
  myFiles.load(178, 205, 24, 24, pwrAux1IconS[globalPower.pwrAux1],4);
  myFiles.load(206, 205, 24, 24, pwrAux2IconS[globalPower.pwrAux2],4);
}

void screenFeeding()  // start the feeding cycle and draw the feeding screen
{
  dispScreen=2;
  touchWaitTime = LONG_WAIT;
  
  myGLCD.clrScr();
  updateTimeDate(true);

  // draw header and footer
  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 239, 307); // at footer
  myFiles.load(2, 2, 30, 30, "2feed.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(0, 184, 19);
  myGLCD.print(F("FEEDING"), 36, 12);
  myFiles.load(107, 294, 26, 26, "foothome.raw",2);

  myGLCD.setFont(arial_bold);
  myGLCD.setColor(0, 184, 19);
  myGLCD.print(F("TIME REMAINING"), CENTER, 60);
  myGLCD.setColor(240, 240, 255);

  // buttons to stop and restart feeding
  myFiles.load(67, 223, 48, 48, "2stop.raw",2);
  myFiles.load(124, 223, 48, 48, "2restart.raw",2);

  // picture of fish eating
  myFiles.load(74, 110, 92, 92, "2feeding.raw",2);

  // start feeding cycle if not already active
  if (feedingActive==false)
  {
    // capture current power status so we can return to it
    preFeedPower.pwrLight1 = globalPower.pwrLight1;
    preFeedPower.pwrLight2 = globalPower.pwrLight2;
    preFeedPower.pwrFilter = globalPower.pwrFilter;
    preFeedPower.pwrCirc = globalPower.pwrCirc;
    preFeedPower.pwrHeat = globalPower.pwrHeat;
    preFeedPower.pwrCO2 = globalPower.pwrCO2; 
    preFeedPower.pwrAux1 = globalPower.pwrAux1;
    preFeedPower.pwrAux2 = globalPower.pwrAux2;

    // fire power relays as configured
    if(feedSetting.pwrHeat)
    {
      if (feedPower.pwrHeat==1) AlarmPwrHeat_On();
      else if (feedPower.pwrHeat==0) AlarmPwrHeat_Off();
    }
    if(feedSetting.pwrCO2)
    {
      if (feedPower.pwrCO2==1) AlarmPwrCO2_On();
      else if (feedPower.pwrCO2==0) AlarmPwrCO2_Off();
    }
    if(feedSetting.pwrFilter)
    {
      if (feedPower.pwrFilter==1) AlarmPwrFilter_On();
      else if (feedPower.pwrFilter==0) AlarmPwrFilter_Off();
    }
    if(feedSetting.pwrCirc)
    {
      if (feedPower.pwrCirc==1) AlarmPwrCirc_On();
      else if (feedPower.pwrCirc==0) AlarmPwrCirc_Off();
    }
    if(feedSetting.pwrAux1)
    {
      if (feedPower.pwrAux1==1) AlarmPwrAux1_On();
      else if (feedPower.pwrAux1==0) AlarmPwrAux1_Off();
    }
    if(feedSetting.pwrAux2)
    {
      if (feedPower.pwrAux2==1) AlarmPwrAux2_On();
      else if (feedPower.pwrAux2==0) AlarmPwrAux2_Off();
    }

    feedingActive=true;
    startFeedingTime = now(); // mark when feeding started
    
    Serial.print(F("Feeding Started.\n"));
  }
  checkFeeding();
}

void screenPower()  // draw the screen to turn power outputs on/off
{
  dispScreen=3;
  touchWaitTime = LONG_WAIT;

  myGLCD.clrScr();
  updateTimeDate(true);

  // draw footer
  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "foothome.raw",2);

  // draw header
  myFiles.load(2, 2, 30, 30, "3power.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(222, 8, 51);
  myGLCD.print(F("POWER"), 36, 12);

  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("MASTER"), CENTER, 52);

  // all on and all off buttons
  myFiles.load(73, 77, 40, 40, "3allon.raw",2);
  myFiles.load(128, 77, 40, 40, "3alloff.raw",2);

  // load all power icons and power dots
  myFiles.load(15, 139, 48, 48, pwrLightIcon[globalPower.pwrLight1],4);
  myFiles.load(34, 192, 10, 11, pwrDot[globalPower.pwrLight1],4);
  myFiles.load(69, 139, 48, 48, pwrLightIcon[globalPower.pwrLight2],4);
  myFiles.load(88, 192, 10, 11, pwrDot[globalPower.pwrLight2],4);
  myFiles.load(124, 139, 48, 48, pwrFilterIcon[globalPower.pwrFilter],4);
  myFiles.load(143, 192, 10, 11, pwrDot[globalPower.pwrFilter],4);
  myFiles.load(178, 139, 48, 48, pwrCircIcon[globalPower.pwrCirc],4);
  myFiles.load(197, 192, 10, 11, pwrDot[globalPower.pwrCirc],4);
  myFiles.load(15, 212, 48, 48, pwrHeatIcon[globalPower.pwrHeat],4);
  myFiles.load(34, 264, 10, 11, pwrDot[globalPower.pwrHeat],4);
  myFiles.load(69, 212, 48, 48, pwrCO2Icon[globalPower.pwrCO2],4);
  myFiles.load(88, 264, 10, 11, pwrDot[globalPower.pwrCO2],4);
  myFiles.load(124, 212, 48, 48, pwrAux1Icon[globalPower.pwrAux1],4);
  myFiles.load(143, 264, 10, 11, pwrDot[globalPower.pwrAux1],4);
  myFiles.load(178, 212, 48, 48, pwrAux2Icon[globalPower.pwrAux2],4);
  myFiles.load(197, 264, 10, 11, pwrDot[globalPower.pwrAux2],4);
}

void screenSettings()  // draw the screen that has all of the extra settings apps
{
  dispScreen=4;
  touchWaitTime = LONG_WAIT;

  myGLCD.clrScr();
  updateTimeDate(true);
  
  // draw header
  myFiles.load(2, 2, 30, 30, "4extras.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(F("SETTINGS  "), 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer

  myFiles.load(107, 294, 26, 26, "foothome.raw",4);  // footer home button

  if ((globalPower.pwrLight1==1)||(lightCSP==false))
  {
    myFiles.load(10, 50, 48, 63, "4lights.raw",4);
  }
  else
  {
    myFiles.load(10, 50, 48, 63, "4lightsF.raw",4);
  }
  myFiles.load(67, 50, 48, 63, "4clock.raw",4);
  myFiles.load(124, 50, 48, 63, "4feeding.raw",4);
  myFiles.load(181, 50, 48, 63, "4sched.raw",4);
  myFiles.load(10, 118, 48, 63, "4sensors.raw",4);
  myFiles.load(67, 118, 48, 63, "4dosing.raw",4);
  myFiles.load(124, 118, 48, 63, "4screen.raw",4);
  myFiles.load(181, 118, 48, 63, "4ato.raw",4);
  myFiles.load(10, 186, 48, 63, "4lunar.raw",4);
  if (lightCSP==true) myFiles.load(67, 186, 48, 63, "4colorF.raw",4);//gray out icon for IR lights
  if (lightCSP==false)myFiles.load(67, 186, 48, 63, "4color.raw",4);
  myFiles.load(124, 186, 48, 63, "4graph.raw",4);
}

void screenLights() // draw the screen for configuring the lights
{
  dispScreen=5; 
  touchWaitTime = LONG_WAIT;

  myGLCD.clrScr();
  updateTimeDate(true);

  // draw header
  myFiles.load(2, 2, 30, 30, "5lights.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(185, 55, 255);
  myGLCD.print(F("LIGHT MODES"), 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer

  myGLCD.drawLine(0, 94, 239, 94); // vertical center line
  myGLCD.drawLine(0, 168, 239, 168); // vertical center line

  myFiles.load(107, 294, 26, 26, "footextr.raw",2); // footer button

  // draw buttons based on current mode (either selected or not selected)
  if (currentLightMode==0)// high sun
  {
    myFiles.load(10, 39, 48, 48, lightModeS[0],2);
    myFiles.load(10, 39, 48, 48, lightMode[0],2);
    myFiles.load(67, 39, 48, 48, lightMode[1],2);
    myFiles.load(124, 39, 48, 48, lightMode[2],2);
    myFiles.load(181, 39, 48, 48, lightMode[3],2);
    myFiles.load(10, 101, 48, 63, lightEdit[1],2);
    myFiles.load(181, 101, 48, 63, lightResync[1],2);    

    // get RGBW for high sun
    currentColor.chan1=EEPROM.read(400);
    currentColor.chan2=EEPROM.read(401);
    currentColor.chan3=EEPROM.read(402);
    currentColor.chan4=EEPROM.read(403);
    currentColor.chan5=EEPROM.read(404);
    currentColor.chan6=EEPROM.read(405);
    
    // draw bargraphs
    drawLEDBarGraph(1, currentColor.chan1);
    drawLEDBarGraph(2, currentColor.chan2);
    drawLEDBarGraph(3, currentColor.chan3);
    drawLEDBarGraph(4, currentColor.chan4);
    drawLEDBarGraph(5, currentColor.chan5);
    drawLEDBarGraph(6, currentColor.chan6);
    
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
    }
  }  
  else if (currentLightMode==1) // mid sun
  {
    myFiles.load(10, 39, 48, 48, lightMode[0],2);
    myFiles.load(67, 39, 48, 48, lightModeS[1],2);
    myFiles.load(124, 39, 48, 48, lightMode[2],2);
    myFiles.load(181, 39, 48, 48, lightMode[3],2);
    myFiles.load(10, 101, 48, 63, lightEdit[1],2);
    myFiles.load(181, 101, 48, 63, lightResync[1],2);    

    // get RGBW for mid sun
    currentColor.chan1=EEPROM.read(410);
    currentColor.chan2=EEPROM.read(411);
    currentColor.chan3=EEPROM.read(412);
    currentColor.chan4=EEPROM.read(413);
    currentColor.chan5=EEPROM.read(414);
    currentColor.chan6=EEPROM.read(415);
    
    // draw bargraphs
    drawLEDBarGraph(1, currentColor.chan1);
    drawLEDBarGraph(2, currentColor.chan2);
    drawLEDBarGraph(3, currentColor.chan3);
    drawLEDBarGraph(4, currentColor.chan4);
    drawLEDBarGraph(5, currentColor.chan5);
    drawLEDBarGraph(6, currentColor.chan6);
    
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
    }
  }
  else if (currentLightMode==2) // low sun
  {
    myFiles.load(10, 39, 48, 48, lightMode[0],2);
    myFiles.load(67, 39, 48, 48, lightMode[1],2);
    myFiles.load(124, 39, 48, 48, lightModeS[2],2);
    myFiles.load(181, 39, 48, 48, lightMode[3],2);
    myFiles.load(10, 101, 48, 63, lightEdit[1],2);
    myFiles.load(181, 101, 48, 63, lightResync[1],2);    

    // get RGBW for low sun
    currentColor.chan1=EEPROM.read(420);
    currentColor.chan2=EEPROM.read(421);
    currentColor.chan3=EEPROM.read(422);
    currentColor.chan4=EEPROM.read(423);
    currentColor.chan5=EEPROM.read(424);
    currentColor.chan6=EEPROM.read(425);
    
    // draw bargraphs
    drawLEDBarGraph(1, currentColor.chan1);
    drawLEDBarGraph(2, currentColor.chan2);
    drawLEDBarGraph(3, currentColor.chan3);
    drawLEDBarGraph(4, currentColor.chan4);
    drawLEDBarGraph(5, currentColor.chan5);
    drawLEDBarGraph(6, currentColor.chan6);
    
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
    }
  }
  else if (currentLightMode==3) // moon
  {
    myFiles.load(10, 39, 48, 48, lightMode[0],2);
    myFiles.load(67, 39, 48, 48, lightMode[1],2);
    myFiles.load(124, 39, 48, 48, lightMode[2],2);
    myFiles.load(181, 39, 48, 48, lightModeS[3],2);
    myFiles.load(10, 101, 48, 63, lightEdit[1],2);
    myFiles.load(181, 101, 48, 63, lightResync[1],2);

    // get RGBW for moon
    currentColor.chan1=EEPROM.read(430);
    currentColor.chan2=EEPROM.read(431);
    currentColor.chan3=EEPROM.read(432);
    currentColor.chan4=EEPROM.read(433);
    currentColor.chan5=EEPROM.read(434);
    currentColor.chan6=EEPROM.read(435);
    
    // draw bargraphs
    drawLEDBarGraph(1, currentColor.chan1);
    drawLEDBarGraph(2, currentColor.chan2);
    drawLEDBarGraph(3, currentColor.chan3);
    drawLEDBarGraph(4, currentColor.chan4);
    drawLEDBarGraph(5, currentColor.chan5);
    drawLEDBarGraph(6, currentColor.chan6);
    
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
    }
  }
  else if ((currentLightMode==4)||(currentLightMode==5)) // lights in transition or unknown
  {
    myFiles.load(10, 39, 48, 48, lightMode[0],2);
    myFiles.load(67, 39, 48, 48, lightMode[1],2);
    myFiles.load(124, 39, 48, 48, lightMode[2],2);
    myFiles.load(181, 39, 48, 48, lightMode[3],2);
    myFiles.load(10, 101, 48, 63, lightEdit[0],2);
    myFiles.load(181, 101, 48, 63, lightResync[1],2);
    
    if(lightCSP == true)
    {
      // draw bargraphs
      drawLEDBarGraph(1, currentColor.chan1);
      drawLEDBarGraph(2, currentColor.chan2);
      drawLEDBarGraph(3, currentColor.chan3);
      drawLEDBarGraph(4, currentColor.chan4);
      drawLEDBarGraph(5, 0);
      drawLEDBarGraph(6, 0);
    }else
    {
      byte temp1,temp2,temp3,temp4,temp5,temp6;
      if(PCA9685Installed == true)  //if using PCA9685 scale values to 12-bit
      {
        temp1 = map(currentColor.chan1,0,4095,0,100);
        temp2 = map(currentColor.chan2,0,4095,0,100);
        temp3 = map(currentColor.chan3,0,4095,0,100);
        temp4 = map(currentColor.chan4,0,4095,0,100);
        temp5 = map(currentColor.chan5,0,4095,0,100);
        temp6 = map(currentColor.chan6,0,4095,0,100);
      }else
      {
        temp1 = map(currentColor.chan1,0,255,0,100);
        temp2 = map(currentColor.chan2,0,255,0,100);
        temp3 = map(currentColor.chan3,0,255,0,100);
        temp4 = map(currentColor.chan4,0,255,0,100);
        temp5 = map(currentColor.chan5,0,255,0,100);
        temp6 = map(currentColor.chan6,0,255,0,100);
      }
      // draw bargraphs
      drawLEDBarGraph(1, temp1);
      drawLEDBarGraph(2, temp2);
      drawLEDBarGraph(3, temp3);
      drawLEDBarGraph(4, temp4);
      drawLEDBarGraph(5, temp5);
      drawLEDBarGraph(6, temp6);
    }
  }

  // draw the rest of the buttons disabled until the edit button is pressed
  myFiles.load(67, 101, 48, 63, lightSave[0],2);
  myFiles.load(124, 101, 48, 63, lightCancel[0],2);
  
  tempColor = currentColor;
  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 255, 255);
}

void screenLightsIR() // draw the screen for configuring the lights
{
  dispScreen=24;
  touchWaitTime = LONG_WAIT;
  
  char char3[3]; // used for converting numbers to char
  char char3t[3];

  myGLCD.clrScr();
  updateTimeDate(true);

  // draw header
  myFiles.load(2, 2, 30, 30, "5lights.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(185, 55, 255);
  myGLCD.print(F("LIGHT MODES"), 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer

  myGLCD.drawLine(0, 94, 239, 94); // vertical center line
  myGLCD.drawLine(0, 168, 239, 168); // vertical center line

  myFiles.load(107, 294, 26, 26, "footextr.raw",2); // footer button

  // draw buttons based on current mode (either selected or not selected)
  if (currentLightMode==0)// high sun
  {
    Serial.print(F("Light mode = 0\n"));
    myFiles.load(10, 39, 48, 48, lightModeS[0],2);
    myFiles.load(67, 39, 48, 48, lightMode[1],2);
    myFiles.load(124, 39, 48, 48, lightMode[2],2);
    myFiles.load(181, 39, 48, 48, lightMode[3],2);
    myFiles.load(10, 101, 48, 63, lightEdit[1],2);
    myFiles.load(181, 101, 48, 63, lightResync[1],2);    

    // get RGBW for high sun
    currentColor.chan1=EEPROM.read(400);
    currentColor.chan2=EEPROM.read(401);
    currentColor.chan3=EEPROM.read(402);
    currentColor.chan4=EEPROM.read(403);
    currentColor.chan5=EEPROM.read(404);
    currentColor.chan6=EEPROM.read(405);
  }  
  else if (currentLightMode==1) // mid sun
  {
    Serial.print(F("Light mode = 1\n"));
    myFiles.load(10, 39, 48, 48, lightMode[0],2);
    myFiles.load(67, 39, 48, 48, lightModeS[1],2);
    myFiles.load(124, 39, 48, 48, lightMode[2],2);
    myFiles.load(181, 39, 48, 48, lightMode[3],2);
    myFiles.load(10, 101, 48, 63, lightEdit[1],2);
    myFiles.load(181, 101, 48, 63, lightResync[1],2);    

    // get RGBW for mid sun
    currentColor.chan1=EEPROM.read(410);
    currentColor.chan2=EEPROM.read(411);
    currentColor.chan3=EEPROM.read(412);
    currentColor.chan4=EEPROM.read(413);
    currentColor.chan5=EEPROM.read(414);
    currentColor.chan6=EEPROM.read(415);
  }
  else if (currentLightMode==2) // low sun
  {
    Serial.print(F("Light mode = 2\n"));
    myFiles.load(10, 39, 48, 48, lightMode[0],2);
    myFiles.load(67, 39, 48, 48, lightMode[1],2);
    myFiles.load(124, 39, 48, 48, lightModeS[2],2);
    myFiles.load(181, 39, 48, 48, lightMode[3],2);
    myFiles.load(10, 101, 48, 63, lightEdit[1],2);
    myFiles.load(181, 101, 48, 63, lightResync[1],2);    

    // get RGBW for low sun
    currentColor.chan1=EEPROM.read(420);
    currentColor.chan2=EEPROM.read(421);
    currentColor.chan3=EEPROM.read(422);
    currentColor.chan4=EEPROM.read(423);
    currentColor.chan5=EEPROM.read(424);
    currentColor.chan6=EEPROM.read(425);
  }
  else if (currentLightMode==3) // moon
  {
    Serial.print(F("Light mode = 3\n"));
    myFiles.load(10, 39, 48, 48, lightMode[0],2);
    myFiles.load(67, 39, 48, 48, lightMode[1],2);
    myFiles.load(124, 39, 48, 48, lightMode[2],2);
    myFiles.load(181, 39, 48, 48, lightModeS[3],2);
    myFiles.load(10, 101, 48, 63, lightEdit[1],2);
    myFiles.load(181, 101, 48, 63, lightResync[1],2);

    // get RGBW for moon
    currentColor.chan1=EEPROM.read(430);
    currentColor.chan2=EEPROM.read(431);
    currentColor.chan3=EEPROM.read(432);
    currentColor.chan4=EEPROM.read(433);
    currentColor.chan5=EEPROM.read(434);
    currentColor.chan6=EEPROM.read(435);
  }
  else if ((currentLightMode==4)||(currentLightMode==5)) // lights in transition or unknown
  {
    myFiles.load(10, 39, 48, 48, lightMode[0],2);
    myFiles.load(67, 39, 48, 48, lightMode[1],2);
    myFiles.load(124, 39, 48, 48, lightMode[2],2);
    myFiles.load(181, 39, 48, 48, lightMode[3],2);
    myFiles.load(10, 101, 48, 63, lightEdit[0],2);
    myFiles.load(181, 101, 48, 63, lightResync[1],2);
  }

  //Draw greyed out up/down arrows
  myFiles.load(10, 175, 48, 48, lightGray[0]);
  myFiles.load(67, 175, 48, 48, lightGray[0]);
  myFiles.load(124, 175, 48, 48, lightGray[0]);
  myFiles.load(181, 175, 48, 48, lightGray[0]);

  myFiles.load(10, 241, 48, 48, lightGray[1]);
  myFiles.load(67, 241, 48, 48, lightGray[1]);
  myFiles.load(124, 241, 48, 48, lightGray[1]);
  myFiles.load(181, 241, 48, 48, lightGray[1]);
  
  // draw the RGBW values to the screen
  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 255, 255);
  
  byte dx = 25;
  if(currentColor.chan1 < 9)  dx += 4;
  if(currentColor.chan1 < 99) dx += 4;
  itoa(currentColor.chan1, char3, 10);
  myGLCD.print(char3, dx, 228);

  dx = 80;
  if(currentColor.chan2 < 9)  dx += 4;
  if(currentColor.chan2 < 99) dx += 4;
  itoa(currentColor.chan2, char3, 10);
  myGLCD.print(char3, dx, 228);

  dx = 138;
  if(currentColor.chan3 < 9)  dx += 4;
  if(currentColor.chan3 < 99) dx += 4;
  itoa(currentColor.chan3, char3, 10);
  myGLCD.print(char3, dx, 228);

  dx = 195;
  if(currentColor.chan4 < 9)  dx += 4;
  if(currentColor.chan4 < 99) dx += 4;
  itoa(currentColor.chan4, char3, 10);
  myGLCD.print(char3, dx, 228);


  // draw the rest of the buttons disabled until the edit button is pressed
  myFiles.load(67, 101, 48, 63, lightSave[0],2);
  myFiles.load(124, 101, 48, 63, lightCancel[0],2);
  
  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 255, 255);
}

void screenSensors()
{
  dispScreen = 18;
  touchWaitTime = LONG_WAIT;
  
  myGLCD.clrScr();
  updateTimeDate(true);
  
  // draw header
  myFiles.load(2, 2, 30, 30, "18sense.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("Sensors"), 36, 12);
  
  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "foothome.raw",2);
  
  // Sensor 1-3 names
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("Sensor 1"), 2, 55);
  myGLCD.print(F("Sensor 2"), 2, 108);
  myGLCD.print(F("Sensor 3"), 2, 161);
  myGLCD.print(F("Display units"), 2, 214);
  
  // Sensor descriptions
  //myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 0, 77);
  myGLCD.print(F("Water"), 15, 75);
  myGLCD.print(F("Heatsink"), 15, 128);
  myGLCD.print(F("Internal"), 15, 181);
  
  sensor1Enabled = EEPROM.read(50);
  sensor2Enabled = EEPROM.read(51);
  sensor3Enabled = EEPROM.read(52);
  displayInC = EEPROM.read(57);
  // Enable/disable buttons
  myFiles.load(170, 55, 30, 30, schedActiveB[sensor1Enabled],2);
  myFiles.load(170, 108, 30, 30, schedActiveB[sensor2Enabled],2);
  myFiles.load(170, 161, 30, 30, schedActiveB[sensor3Enabled],2);
  
  //display units
  myFiles.load(100, 259, 14, 12, "c.raw",2);
  myFiles.load(180, 259, 14, 12, "f.raw",2);
  myFiles.load(60, 250, 30, 30, schedActiveB[displayInC],2);
  myFiles.load(140, 250, 30, 30, schedActiveB[!displayInC],2);
  
  //settings buttons
  if(sensor1Enabled) myFiles.load(210, 58, 26, 26, "footextr.raw",2);
  if(sensor2Enabled) myFiles.load(210, 111, 26, 26, "footextr.raw",2);
  if(sensor3Enabled) myFiles.load(210, 164, 26, 26, "footextr.raw",2);
}

void screenHeatsink()
{
  dispScreen = 19;
  
  myGLCD.clrScr();
  updateTimeDate(true);
  
  char char6[6];
  
  // draw header
  myFiles.load(2, 2, 30, 30, "18sense.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("Heatsink"), 36, 12);
  
  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw",2);
  
  // lines to divide screen
  myGLCD.drawLine(0, 97, 239, 97); 
  myGLCD.drawLine(0, 163, 239, 163);
  myGLCD.drawLine(0, 229, 239, 229);
  
  // buttons for adjusting off temp
  myFiles.load(162, 37, 24, 24, arrowButton[0],2);
  myFiles.load(162, 67, 24, 24, arrowButton[1],2);

  // buttons for adjusting the on temp
  myFiles.load(162, 103, 24, 24, arrowButton[0],2);
  myFiles.load(162, 133, 24, 24, arrowButton[1],2);
  
  // buttons for adjusting calibration
  myFiles.load(136, 169, 24, 24, arrowButton[0],2);
  myFiles.load(136, 199, 24, 24, arrowButton[1],2);
  
  // off icon
  myFiles.load(10, 40, 96, 48, "19fanoff.raw",2);
  //myGLCD.setColor(0, 51, 222);
  myGLCD.setColor(222, 8, 51); // Add Thiago
  //myGLCD.print(F("FAN"), 105, 42);
  //myGLCD.print(F("OFF"), 106, 69);
  myGLCD.print(F("OFF"), 106, 58);
  
  //display fan off temp
  heatsinkFanOffTemp=EEPROM.read(54);
  itoa(heatsinkFanOffTemp, char6, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char6, 194, 56);
  if(displayInC == true) myFiles.load(226, 58, 14, 12, "c.raw",2);
  if(displayInC == false)myFiles.load(226, 58, 14, 12, "f.raw",2);
  
  // draw the on icon
  myFiles.load(10, 106, 96, 48, "19fanon.raw",2);
  //myGLCD.setColor(222, 8, 51);
  myGLCD.setColor(0, 184, 19); // Add Thiago
  //myGLCD.print(F("FAN"), 110, 108);
  //myGLCD.print(F("ON"), 120, 122);
  myGLCD.print(F("ON"), 120, 122);
  
  //display fan on temp
  heatsinkFanOnTemp=EEPROM.read(53);
  itoa(heatsinkFanOnTemp, char6, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char6, 194, 122);
  if(displayInC == true) myFiles.load(226, 124, 14, 12, "c.raw",2);
  if(displayInC == false)myFiles.load(226, 124, 14, 12, "f.raw",2);
  
  // calibration offset
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print(F("Sensor"),10,174);
  myGLCD.print(F("Offset"),10,201);
    
  // display value to screen
  byte storedVal = EEPROM.read(59);
  byte dx = 176;
  if(storedVal < 128)dx = 160;
  sensor2Calibration = ((float)storedVal - 128) / 10;
  dtostrf(sensor2Calibration, 3, 1, char6);  //convert to string
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char6, dx, 188);
  
  // display units on screen
  if(displayInC == false)myFiles.load(226, 190, 14, 12, "f.raw",2);
  if(displayInC == true) myFiles.load(226, 190, 14, 12, "c.raw",2);
  
  // enable/disable display of sensor
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print(F("Display?"),10,254);
  //myFiles.load(170, 247, 30, 30, schedActiveB[displaySensor2],2);
  myFiles.load(162, 251, 46, 22, schedOnOff[displaySensor2],2);
}

void screenInternalTemp()
{
  dispScreen = 20;
  
  myGLCD.clrScr();
  updateTimeDate(true);
  char char6[6];
  // draw header
  myFiles.load(2, 2, 30, 30, "18sense.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("Internal"), 36, 12);
  
  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw",2);
  
  // lines to divide screen
  myGLCD.drawLine(0, 97, 239, 97); 
  myGLCD.drawLine(0, 163, 239, 163);
  myGLCD.drawLine(0, 229, 239, 229);
  
  // buttons for adjusting off temp
  myFiles.load(162, 37, 24, 24, arrowButton[0],2);
  myFiles.load(162, 67, 24, 24, arrowButton[1],2);

  // buttons for adjusting the on temp
  myFiles.load(162, 103, 24, 24, arrowButton[0],2);
  myFiles.load(162, 133, 24, 24, arrowButton[1],2);
  
  // buttons for adjusting calibration
  myFiles.load(136, 169, 24, 24, arrowButton[0],2);
  myFiles.load(136, 199, 24, 24, arrowButton[1],2);
  
  // off icon
  myFiles.load(10, 40, 96, 48, "19fanoff.raw",2);
  //myGLCD.setColor(0, 51, 222);
  myGLCD.setColor(222, 8, 51); // Add Thiago
  //myGLCD.print(F("FAN"), 105, 42);
  //myGLCD.print(F("OFF"), 106, 69);
  myGLCD.print(F("OFF"), 106, 58);

  // draw the on icon
  myFiles.load(10, 106, 96, 48, "19fanon.raw",2);
  //myGLCD.setColor(222, 8, 51);
  myGLCD.setColor(0, 184, 19); // Add Thiago
  //myGLCD.print(F("FAN"), 110, 108);
  //myGLCD.print(F("ON"), 120, 122);
  myGLCD.print(F("ON"), 120, 122);
  
  //display fan off temp
  internalFanOffTemp = EEPROM.read(56);
  itoa(internalFanOffTemp, char6, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char6, 194, 56);
  if(displayInC == true) myFiles.load(226, 58, 14, 12, "c.raw",2);
  if(displayInC == false)myFiles.load(226, 58, 14, 12, "f.raw",2);
  
  //display fan on temp
  internalFanOnTemp = EEPROM.read(55);
  itoa(internalFanOnTemp, char6, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char6, 194, 122);
  if(displayInC == true) myFiles.load(226, 124, 14, 12, "c.raw",2);
  if(displayInC == false)myFiles.load(226, 124, 14, 12, "f.raw",2);
  
  // calibration offset
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print(F("Sensor"),10,174);
  myGLCD.print(F("Offset"),10,201);
    
  // display value to screen
  byte storedVal = EEPROM.read(60);
  byte dx = 176;
  if(storedVal < 128)dx = 160;
  sensor3Calibration = ((float)storedVal - 128) / 10;
  dtostrf(sensor3Calibration, 3, 1, char6);  //convert to string
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char6, dx, 188);
  
  // display units on screen
  if(displayInC == false)myFiles.load(226, 190, 14, 12, "f.raw",2);
  if(displayInC == true) myFiles.load(226, 190, 14, 12, "c.raw",2);
  
  // enable/disable display of sensor
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print(F("Display?"),10,254);
  //myFiles.load(170, 247, 30, 30, schedActiveB[displaySensor3],2);
  myFiles.load(162, 251, 46, 22, schedOnOff[displaySensor3],2);
}

void screenClock()  // draw the screen for setting the date/time
{
  dispScreen=6; 

  myGLCD.clrScr();
  updateTimeDate(true);

  // draw header
  myFiles.load(2, 2, 30, 30, "6clock.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(47, 168, 208);
  myGLCD.print(F("CLOCK"), 36, 12);

  myGLCD.print(F("TIME"), CENTER, 46);
  myGLCD.print(F("DATE"), CENTER, 167);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 155, 239, 155); // center line

  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 255, 255);

  // draw clock buttons and text
  myGLCD.print("24H", 12, 72);
  myFiles.load(12, 89, 24, 24, arrowButton[0],2);
  myFiles.load(12, 119, 24, 24, arrowButton[1],2);
  myGLCD.print("M", 91, 72);
  myFiles.load(83, 89, 24, 24, arrowButton[0],2);
  myFiles.load(83, 119, 24, 24, arrowButton[1],2);
  myGLCD.print("S", 172, 72);
  myFiles.load(164, 89, 24, 24, arrowButton[0],2);
  myFiles.load(164, 119, 24, 24, arrowButton[1],2);

  // draw date buttons and text
  myGLCD.print("M", 20, 194);
  myFiles.load(12, 211, 24, 24, arrowButton[0],2);
  myFiles.load(12, 241, 24, 24, arrowButton[1],2);
  myGLCD.print("D", 91, 194);
  myFiles.load(83, 211, 24, 24, arrowButton[0],2);
  myFiles.load(83, 241, 24, 24, arrowButton[1],2);
  myGLCD.print("Y", 172, 194);
  myFiles.load(164, 211, 24, 24, arrowButton[0],2);
  myFiles.load(164, 241, 24, 24, arrowButton[1],2);

  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 77, 0);

  saveRTC.Hour = hour();
  saveRTC.Minute = minute(); 
  saveRTC.Second = 0; // always have 0 seconds
  saveRTC.Day = day();
  saveRTC.Month = month();
  saveRTC.Year = (year()-1970);

  char char3[3];
  char char3t[3];

  // draw the date and time to the screen

  itoa(saveRTC.Hour, char3, 10);
  if (saveRTC.Hour>=0 && saveRTC.Hour<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 45, 108);

  itoa(saveRTC.Minute, char3, 10);
  if (saveRTC.Minute>=0 && saveRTC.Minute<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 123, 108);

  myGLCD.print("00", 201, 108);

  itoa(saveRTC.Month, char3, 10);
  if (saveRTC.Month>=0 && saveRTC.Month<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 45, 230);

  itoa(saveRTC.Day, char3, 10);
  if (saveRTC.Day>=0 && saveRTC.Day<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 123, 230);

  //saveRTC.Year is offset from 1970 so we subtract 30 from number to get offset from 2000
  itoa((saveRTC.Year-30), char3, 10);
  if (((saveRTC.Year-30) >= 0) && ((saveRTC.Year-30) <= 9)) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 201, 230);

  // buttons to save or cancel
  myFiles.load(12, 286, 84, 26, "6cancel.raw",2);
  myFiles.load(144, 286, 84, 26, "6set.raw",2);

}

void screenFeedSettings() // screen for setting the minutes and power settings for feeding
{
  dispScreen=7;
  touchWaitTime = LONG_WAIT;

  myGLCD.clrScr();
  updateTimeDate(true);

  // draw header
  myFiles.load(2, 2, 30, 30, "2feed.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(0, 184, 19);
  myGLCD.print(F("FEED CONFIG"), 36, 12);
  myGLCD.print(F("MINUTES"), 24, 65);

  // buttons for changing minutes
  myFiles.load(158, 46, 24, 24, arrowButton[0],2);
  myFiles.load(158, 76, 24, 24, arrowButton[1],2);

  myGLCD.setColor(255, 77, 0);

  // display current setting for minutes
  char char3[3];
  itoa(feedingMins, char3, 10);
  myGLCD.print(char3, 190, 65);

  myGLCD.setColor(222, 8, 51);
  myGLCD.print(F("POWER SETUP"), CENTER, 113);

  myGLCD.setColor(130, 130, 130);

  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 121, 32, 121); // LEFT OF POWER
  myGLCD.drawLine(208, 121, 239, 121); // Right of power
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw",2);

  // Feeding settings stored in EEPROM
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

  // load power icons based on saved settings
  myFiles.load(41, 140, 48, 48, pwrHeatIcon[feedPower.pwrHeat],2);
  myFiles.load(96, 140, 48, 48, pwrFilterIcon[feedPower.pwrFilter],2);
  myFiles.load(150, 140, 48, 48, pwrCircIcon[feedPower.pwrCirc],2);
  myFiles.load(41, 220, 48, 48, pwrCO2Icon[feedPower.pwrCO2],2);
  myFiles.load(96, 220, 48, 48, pwrAux1Icon[feedPower.pwrAux1],2);
  myFiles.load(150, 220, 48, 48, pwrAux2Icon[feedPower.pwrAux2],2);
  
  // load enable/disable icons based on saved settings
  myFiles.load(42, 189, 46, 22, schedOnOff[feedSetting.pwrHeat],2);
  myFiles.load(97, 189, 46, 22, schedOnOff[feedSetting.pwrFilter],2);
  myFiles.load(151, 189, 46, 22, schedOnOff[feedSetting.pwrCirc],2);
  myFiles.load(42, 269, 46, 22, schedOnOff[feedSetting.pwrCO2],2);
  myFiles.load(97, 269, 46, 22, schedOnOff[feedSetting.pwrAux1],2);
  myFiles.load(151, 269, 46, 22, schedOnOff[feedSetting.pwrAux2],2);
}

void screenHeater() // screen for choosing temp settings for the heater
{
  dispScreen=8;
  
  char char6[6]; // used to convernt numbers to char

  myGLCD.clrScr();
  updateTimeDate(true);

  // draw header
  myFiles.load(2, 2, 30, 30, "8heat.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(34, 81, 255);
  myGLCD.print(F("HEATER SETUP"), 36, 12);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw",2);
  
  // lines to divide screen
  myGLCD.drawLine(0, 97, 239, 97); 
  myGLCD.drawLine(0, 163, 239, 163);
  myGLCD.drawLine(0, 229, 239, 229);
  
  // buttons for adjusting off temp
  myFiles.load(162, 37, 24, 24, arrowButton[0],2);
  myFiles.load(162, 67, 24, 24, arrowButton[1],2);

  // buttons for adjusting the on temp
  myFiles.load(162, 103, 24, 24, arrowButton[0],2);
  myFiles.load(162, 133, 24, 24, arrowButton[1],2);
  
  // buttons for adjusting calibration
  myFiles.load(136, 169, 24, 24, arrowButton[0],2);
  myFiles.load(136, 199, 24, 24, arrowButton[1],2);

  // off icon
  myFiles.load(17, 40, 48, 48, "8off.raw",2);
  myGLCD.setColor(222, 8, 51);
  //myGLCD.print(F("HEATER"), 64, 42);
  //myGLCD.print(F("OFF"), 88, 69);
  myGLCD.print("OFF", 88, 58); // Add Thiago

  // get the setting for heat off and print it
  heatOffTemp = (EEPROM.read(17)); // 17 // heater off temp
  itoa(heatOffTemp, char6, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char6, 193, 56);
  if(displayInC == true) myFiles.load(226, 58, 14, 12, "c.raw",2);
  if(displayInC == false)myFiles.load(226, 58, 14, 12, "f.raw",2);

  // draw the on icon
  myFiles.load(17, 106, 48, 48, "8on.raw",2);
  //myGLCD.setColor(222, 8, 51);
  //myGLCD.print(F("HEATER"), 64, 108);
  //myGLCD.print(F("ON"), 96, 135);
  myGLCD.setColor(0, 184, 19); // Add Thiago
  myGLCD.print("ON", 96, 122); // Add Thiago

  // get the setting for heat on and print it
  heatOnTemp = (EEPROM.read(18));
  itoa(heatOnTemp, char6, 10); // 18 // heater on temp
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char6, 195, 122);
  if(displayInC == true) myFiles.load(226, 124, 14, 12, "c.raw",2);
  if(displayInC == false)myFiles.load(226, 124, 14, 12, "f.raw",2);

  // calibration offset
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print(F("Sensor"),10,174);
  myGLCD.print(F("Offset"),10,201);
  
  // display value to screen
  byte storedVal = EEPROM.read(58);
  byte dx = 176;
  if(storedVal < 128)dx = 160;
  sensor1Calibration = ((float)storedVal - 128) / 10;
  dtostrf(sensor1Calibration, 3, 1, char6);  //convert to string
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char6, dx, 188);
  
  // display units on screen
  if(displayInC == false)myFiles.load(226, 190, 14, 12, "f.raw",2);
  if(displayInC == true) myFiles.load(226, 190, 14, 12, "c.raw",2);
  
  // enable/disable display of sensor
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print(F("Display?"),10,254);
  //myFiles.load(170, 247, 30, 30, schedActiveB[displaySensor1],2);
  myFiles.load(162, 251, 46, 22, schedOnOff[displaySensor1],2);
}

void screenSchedule() // screen with icons to allow setting schedules
{
  dispScreen=9;
  touchWaitTime = LONG_WAIT;
  
  myGLCD.clrScr();
  updateTimeDate(true);

  // draw header
  myFiles.load(2, 2, 30, 30, "9sched.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("SCHEDULE"), 36, 12);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw",2);

  // draw schedule icons
  myFiles.load(10, 50, 48, 63, "9power.raw",2);
  myFiles.load(67, 50, 48, 63, "4dosing.raw",2);
  myFiles.load(124, 50, 48, 63, "4lights.raw",2);
}

void screenDosing(byte pumpNo)  // screen to configure the 3 dosing pumps
{
  scheduleItem=pumpNo;
  dispScreen=10;
  touchWaitTime = LONG_WAIT;
  
  char char5[5];

  myGLCD.clrScr();
  updateTimeDate(true);

  // draw header
  myFiles.load(2, 2, 30, 30, "10dose.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(138, 93, 35);
  myGLCD.print(F("DOSING SETUP"), 36, 12);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 293, 26, 26, "footextr.raw",2);

  // 3 horizontal separater lines
  myGLCD.drawLine(0, 95, 239, 95);
  myGLCD.drawLine(0, 161, 239, 161);
  myGLCD.drawLine(0, 227, 239, 227);
  
  //Display pump selectors
  myFiles.load(12, 39, 46, 48,"15pump1.raw",2);
  myFiles.load(70, 39, 46, 48,"15pump2.raw",2);
  myFiles.load(128, 39, 46, 48,"15pump3.raw",2);
  
  //Highlight selected pump
  myGLCD.setColor(VGA_WHITE); 
  if(pumpNo == 1) myGLCD.drawRoundRect(10,37,60,89);//x1,y1,x2,y2
  if(pumpNo == 2) myGLCD.drawRoundRect(68,37,118,89);//x1,y1,x2,y2
  if(pumpNo == 3) myGLCD.drawRoundRect(126,37,176,89);//x1,y1,x2,y2

  // DOSE AMOUNT
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("DOSE"), 4, 105);
  myGLCD.print(F("AMOUNT"), 4, 131);

  // buttons to adjust dose amount
  myFiles.load(145, 101, 24, 24, arrowButton[0],2);
  myFiles.load(145, 131, 24, 24, arrowButton[1],2);

  // read dose amount setting and print it
  byte doseAmt;
  if (pumpNo==1)
  {
    doseAmt=EEPROM.read(20); // 20 // pump1 dose in mL
  }
  else if (pumpNo==2)
  {
    doseAmt=EEPROM.read(21); // 21 // pump2 dose in mL
  }
  else if (pumpNo==3)
  {
    doseAmt=EEPROM.read(22); // 22 // pump3 dose in mL
  }
  itoa(doseAmt, char5, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char5, 175, 121);

  //PUMP SPEED
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("PUMP"), 4, 174);
  myGLCD.print(F("SPEED"), 4, 200);
  
  // buttons to adjust pump time
  myFiles.load(145, 167, 24, 24, arrowButton[0],2);
  myFiles.load(145, 197, 24, 24, arrowButton[1],2);

  // read in pump time and display it in seconds
  int pumpTime;
  int doseCap;
  if (pumpNo==1)
  {
    pumpTime=EEPROM.read(23); // 23 // pump 1 sec/ml
  }
  else if (pumpNo==2)
  {
    pumpTime=EEPROM.read(24); // 24 // pump 1 sec/ml
  }
  else if (pumpNo==3)
  {
    pumpTime=EEPROM.read(25); // 25 // pump 1 sec/ml
  }
  pumpTime=pumpTime*10;
  itoa(pumpTime, char5, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(arial_bold);
  myGLCD.print(char5, 175, 186);  // 175 if 4 chars

  // PUMP test button and calibration
  myFiles.load(92, 170, 48, 48, "10test.raw",2);

  //Reservoir size
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("FULL"),4,240);
  myGLCD.print(F("VOL."),4,266);

  if (pumpNo==1)
  {
    doseCap=EEPROM.read(26); // 26 // dosing 1 resevior capacity in mL;
  }
  if (pumpNo==2)
  {
    doseCap=EEPROM.read(261); // 27 // dosing 2 resevior capacity in mL;
  } 
  if (pumpNo==3)
  {
    doseCap=EEPROM.read(263); // 28 // dosing 3 resevior capacity in mL;    
  }
  doseCap=doseCap*10; // saved value is ^10
  itoa(doseCap, char5, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(arial_bold);
  myGLCD.print(char5, 175, 252);
  
  // buttons to adjust reservoir
  myFiles.load(145, 233, 24, 24, arrowButton[0],2);
  myFiles.load(145, 263, 24, 24, arrowButton[1],2);
  
  // fill reservoir icon
  myFiles.load(92, 236, 48, 48, "10fill.raw",2);
  
  // units of measurement labels
  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("mL"), 195, 146);
  myGLCD.print(F("ms/mL)"), 183, 211);
  myGLCD.print(F("mL"), 195, 277);
}

void screenPwrSchedule() // this is the screen to show the power schedule
{
  dispScreen=11; 
  touchWaitTime = LONG_WAIT;
  
  myGLCD.clrScr();
  updateTimeDate(true);

  char char3[3];
  char char3t[3];

  // draw header 
  myFiles.load(2, 2, 30, 30, "9sched.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("SCHEDULE"), 36, 12);

  //myGLCD.setColor(222, 8, 51);
  //myGLCD.print(F("POWER"), CENTER, 50);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footschd.raw",2);

  // grid for schedule
  myGLCD.drawLine(0, 85, 239, 85);
  myGLCD.drawLine(65, 110, 239, 110);
  myGLCD.drawLine(0, 135, 239, 135);
  myGLCD.drawLine(65, 160, 239, 160);
  myGLCD.drawLine(0, 185, 239, 185);
  myGLCD.drawLine(0, 210, 239, 210);
  myGLCD.drawLine(0, 235, 239, 235);
  myGLCD.drawLine(0, 260, 239, 260);
 // myGLCD.drawLine(0, 285, 239, 285);

  // write power schedule column headers
  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("ON"), 99, 63);
  myGLCD.print(F("OFF"), 144, 63);
  myGLCD.print(F("(Freq)"), 83, 74);
  myGLCD.print(F("(DUR.)"), 132, 74);
    
  myGLCD.print(F("ACTIVE"), 202, 34, 90);
  myGLCD.print(F("TIMER?"), 226, 34, 90);

  ///////////////////////////////// Lights 1 schedule
  if (schedLights1.active==1) myGLCD.setColor(255, 255, 255);
  else myGLCD.setColor(185, 185, 185);
  myFiles.load(192, 89, 18, 18,  schedActive[schedLights1.active],2);

  myGLCD.print(F("LIGHT1 S1"), 8, 94);

  // convert light 1 on hour to char
  itoa(schedLights1.onHour, char3, 10); 
  if (schedLights1.onHour>=0 && schedLights1.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 87, 94);         
  myGLCD.print(":", 103, 94);         

  // convert light 1 on min to char
  itoa(schedLights1.onMinute, char3, 10); 
  if (schedLights1.onMinute>=0 && schedLights1.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 111, 94);

  // convert light 1 off hour to char
  itoa(schedLights1.offHour, char3, 10); 
  if (schedLights1.offHour>=0 && schedLights1.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 136, 94);         
  myGLCD.print(":", 152, 94);         

  // convert light 1 on min to char
  itoa(schedLights1.offMinute, char3, 10); 
  if (schedLights1.offMinute>=0 && schedLights1.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 160, 94);


///////////////////////////////// Lights 1 schedule 2
  if (schedLights1s2.active==1) myGLCD.setColor(255, 255, 255);
  else myGLCD.setColor(185, 185, 185);
  myFiles.load(192, 114, 18, 18,  schedActive[schedLights1s2.active],2);

  myGLCD.print("S2", 64, 119);

  // convert light 1 s2 on hour to char
  itoa(schedLights1s2.onHour, char3, 10); 
  if (schedLights1s2.onHour>=0 && schedLights1s2.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 86, 119);         
  myGLCD.print(":", 102, 119);         

  // convert light 1 on min to char
  itoa(schedLights1s2.onMinute, char3, 10); 
  if (schedLights1s2.onMinute>=0 && schedLights1s2.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 110, 119);

  // convert light 1 s2 off hour to char
  itoa(schedLights1s2.offHour, char3, 10); 
  if (schedLights1s2.offHour>=0 && schedLights1s2.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 136, 119);         
  myGLCD.print(":", 152, 119);         

  // convert light 1 on min to char
  itoa(schedLights1s2.offMinute, char3, 10); 
  if (schedLights1s2.offMinute>=0 && schedLights1s2.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 164, 119);
 
  ///////////////////////////////// Lights 2 schedule
  if (schedLights2.active==1) myGLCD.setColor(255, 255, 255);
  else myGLCD.setColor(185, 185, 185);
  myFiles.load(192, 139, 18, 18,  schedActive[schedLights2.active],2);

  myGLCD.print(F("LIGHT2 S1"), 8, 144);

  // convert on hour to char
  itoa(schedLights2.onHour, char3, 10); 
  if (schedLights2.onHour>=0 && schedLights2.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 87, 144);         
  myGLCD.print(":", 103, 144);         

  // convert on min to char
  itoa(schedLights2.onMinute, char3, 10); 
  if (schedLights2.onMinute>=0 && schedLights2.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 111, 144);

  // convert off hour to char
  itoa(schedLights2.offHour, char3, 10); 
  if (schedLights2.offHour>=0 && schedLights2.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 136, 144);         
  myGLCD.print(":", 152, 144);         

  // convert off min to char
  itoa(schedLights2.offMinute, char3, 10); 
  if (schedLights2.offMinute>=0 && schedLights2.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 160, 144);

  
  ///////////////////////////////// Lights 2 schedule 2
  if (schedLights2s2.active==1) myGLCD.setColor(255, 255, 255);
  else myGLCD.setColor(185, 185, 185);
  myFiles.load(192, 164, 18, 18,  schedActive[schedLights2s2.active],2);

  myGLCD.print("S2", 64, 168);

  // convert on hour to char
  itoa(schedLights2s2.onHour, char3, 10); 
  if (schedLights2s2.onHour>=0 && schedLights2s2.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 86 , 168);         
  myGLCD.print(":", 102, 168);         

  // convert on min to char
  itoa(schedLights2s2.onMinute, char3, 10); 
  if (schedLights2s2.onMinute>=0 && schedLights2s2.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 110, 168);

  // convert off hour to char
  itoa(schedLights2s2.offHour, char3, 10); 
  if (schedLights2s2.offHour>=0 && schedLights2s2.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 136, 168);
  myGLCD.print(":", 152, 168);

  // convert off min to char
  itoa(schedLights2s2.offMinute, char3, 10); 
  if (schedLights2s2.offMinute>=0 && schedLights2s2.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 160, 168);

  ///////////////////////////////// schedCirc schedule
  if (schedCirc.active==1) myGLCD.setColor(255, 255, 255);
  else myGLCD.setColor(185, 185, 185);
  myFiles.load(192, 189, 18, 18, schedActive[schedCirc.active],2);

  myGLCD.print(F("CIRC"), 8, 193);

  // convert on hour to char
  itoa(schedCirc.onHour, char3, 10); 
  if (schedCirc.onHour>=0 && schedCirc.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 87, 193);         
  myGLCD.print(":", 103, 193);         

  // convert on min to char
  itoa(schedCirc.onMinute, char3, 10); 
  if (schedCirc.onMinute>=0 && schedCirc.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 111, 193);

  // convert off hour to char
  itoa(schedCirc.offHour, char3, 10); 
  if (schedCirc.offHour>=0 && schedCirc.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 136, 193);         
  myGLCD.print(":", 152, 193);         

  // convert off min to char
  itoa(schedCirc.offMinute, char3, 10); 
  if (schedCirc.offMinute>=0 && schedCirc.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 160, 193);

  ///////////////////////////////// schedCo2 schedule
  if (schedCo2.active==1) myGLCD.setColor(255, 255, 255);
  else myGLCD.setColor(185, 185, 185);
  myFiles.load(192, 214, 18, 18, schedActive[schedCo2.active],2);
  myGLCD.print(F("CO2"), 8, 218);

  // convert on hour to char
  itoa(schedCo2.onHour, char3, 10); 
  if (schedCo2.onHour>=0 && schedCo2.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 87, 218);         
  myGLCD.print(":", 103, 218);         

  // convert on min to char
  itoa(schedCo2.onMinute, char3, 10); 
  if (schedCo2.onMinute>=0 && schedCo2.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 111, 218);

  // convert off hour to char
  itoa(schedCo2.offHour, char3, 10); 
  if (schedCo2.offHour>=0 && schedCo2.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 136, 218);         
  myGLCD.print(":", 152, 218);         

  // convert off min to char
  itoa(schedCo2.offMinute, char3, 10); 
  if (schedCo2.offMinute>=0 && schedCo2.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 160, 218);

  ///////////////////////////////// schedAux1 schedule
  if (schedAux1.active==1) myGLCD.setColor(255, 255, 255);
  else myGLCD.setColor(185, 185, 185);
  myFiles.load(192, 239, 18, 18, schedActive[schedAux1.active],2);
  myFiles.load(216, 239, 18, 18, schedActive[schedAux1.timer],2);

  myGLCD.print(F("AUX 1"), 8, 244);

  // convert on hour to char
  itoa(schedAux1.onHour, char3, 10); 
  if (schedAux1.onHour>=0 && schedAux1.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 87, 244);         
  myGLCD.print(":", 103, 244);         

  // convert on min to char
  itoa(schedAux1.onMinute, char3, 10); 
  if (schedAux1.onMinute>=0 && schedAux1.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 111, 244);

  // convert off hour to char
  itoa(schedAux1.offHour, char3, 10); 
  if (schedAux1.offHour>=0 && schedAux1.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 136, 244);         
  myGLCD.print(":", 152, 244);         

  // convert off min to char
  itoa(schedAux1.offMinute, char3, 10); 
  if (schedAux1.offMinute>=0 && schedAux1.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 160, 244);

  ///////////////////////////////// schedAux2 schedule
  if (schedAux2.active==1) myGLCD.setColor(255, 255, 255);
  else myGLCD.setColor(185, 185, 185);
  myFiles.load(192, 264, 18, 18, schedActive[schedAux2.active],2);
  myFiles.load(216, 264, 18, 18, schedActive[schedAux2.timer],2);

  myGLCD.print(F("AUX 2"), 8, 268);

  // convert on hour to char
  itoa(schedAux2.onHour, char3, 10); 
  if (schedAux2.onHour>=0 && schedAux2.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 87, 268);         
  myGLCD.print(":", 103, 268);         

  // convert on min to char
  itoa(schedAux2.onMinute, char3, 10); 
  if (schedAux2.onMinute>=0 && schedAux2.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 111, 268);

  // convert off hour to char
  itoa(schedAux2.offHour, char3, 10); 
  if (schedAux2.offHour>=0 && schedAux2.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 136, 268);         
  myGLCD.print(":", 152, 268);         

  // convert off min to char
  itoa(schedAux2.offMinute, char3, 10); 
  if (schedAux2.offMinute>=0 && schedAux2.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 160, 268);
}

void screenPwrScheduleItem(int itemNo) // screen for editing the schedule of an individual power relay
{
  dispScreen=12;
  
  myGLCD.clrScr();
  updateTimeDate(true);

  char char3[3];
  char char3t[3];

  // draw header
  myFiles.load(2, 2, 30, 30, "9sched.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("SCHEDULE"), 36, 12);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footschd.raw",2);

  myGLCD.setColor(222, 8, 51);
  myGLCD.print(F("POWER:"), 8, 50);
  myGLCD.setColor(255, 255, 255);

  // print on/off/active and buttons
  myGLCD.print(F("ON"), 8, 113);
  myGLCD.print(F("OFF"), 8, 194);
  myGLCD.print(F("ACTIVE"), 8, 256);

  myGLCD.setFont(Sinclair_S);

  // buttons to edit the hour ON
  myGLCD.print("H", 91, 77);
  myFiles.load(83, 94, 24, 24, arrowButton[0],2);
  myFiles.load(83, 124, 24, 24, arrowButton[1],2);

  // buttons to edit the minute ON
  myGLCD.print("M", 172, 77);
  myFiles.load(164, 94, 24, 24, arrowButton[0],2);
  myFiles.load(164, 124, 24, 24, arrowButton[1],2);

  // buttons to edit the hour off
  myGLCD.print("H", 91, 158);
  myFiles.load(83, 175, 24, 24, arrowButton[0],2);
  myFiles.load(83, 205, 24, 24, arrowButton[1],2);

  // buttons to edit the minute off
  myGLCD.print("M", 172, 158);
  myFiles.load(164, 175, 24, 24, arrowButton[0],2);
  myFiles.load(164, 205, 24, 24, arrowButton[1],2);

  int isActive, onHour, onMin, offHour, offMin; // vars for schedule
  scheduleItem=itemNo; // track which item's scheudle we are editing
  myGLCD.setFont(arial_bold);

  // set variables based on the item we are scheduling

  if (itemNo==1) // light 1
  {
    myGLCD.print(F("LIGHT 1"), 108, 50);
    isActive=schedLights1.active;
    onHour=schedLights1.onHour;
    onMin=schedLights1.onMinute;
    offHour=schedLights1.offHour;
    offMin=schedLights1.offMinute;
  }
  else if (itemNo==10) // light 1 Schedule 2
  {
    myGLCD.print(F("LIGHT1 S2"), 96, 50);
    isActive=schedLights1s2.active;
    onHour=schedLights1s2.onHour;
    onMin=schedLights1s2.onMinute;
    offHour=schedLights1s2.offHour;
    offMin=schedLights1s2.offMinute;
  }
  else if (itemNo==2) // light 1
  {
    myGLCD.print(F("LIGHT 2"), 108, 50);
    isActive=schedLights2.active;
    onHour=schedLights2.onHour;
    onMin=schedLights2.onMinute;
    offHour=schedLights2.offHour;
    offMin=schedLights2.offMinute;
  }
  else if (itemNo==11) // light 2 Schedule 2
  {
    myGLCD.print("LIGHT2 S2", 96, 50);
    isActive=schedLights2s2.active;
    onHour=schedLights2s2.onHour;
    onMin=schedLights2s2.onMinute;
    offHour=schedLights2s2.offHour;
    offMin=schedLights2s2.offMinute;
  }
  else if (itemNo==3) // Circ
  {
    myGLCD.print(F("CIRC"), 108, 50);
    isActive=schedCirc.active;
    onHour=schedCirc.onHour;
    onMin=schedCirc.onMinute;
    offHour=schedCirc.offHour;
    offMin=schedCirc.offMinute;
  }
  else if (itemNo==4) // CO2
  {
    myGLCD.print(F("CO2"), 108, 50);
    isActive=schedCo2.active;
    onHour=schedCo2.onHour;
    onMin=schedCo2.onMinute;
    offHour=schedCo2.offHour;
    offMin=schedCo2.offMinute;
  }
  else if (itemNo==5) // Aux1
  {
    myGLCD.print(F("AUX 1"), 108, 50);
    isActive=schedAux1.active;
    onHour=schedAux1.onHour;
    onMin=schedAux1.onMinute;
    offHour=schedAux1.offHour;
    offMin=schedAux1.offMinute;
  }
  else if (itemNo==6) // Aux2
  {
    myGLCD.print(F("AUX 2"), 108, 50);
    isActive=schedAux2.active;
    onHour=schedAux2.onHour;
    onMin=schedAux2.onMinute;
    offHour=schedAux2.offHour;
    offMin=schedAux2.offMinute;
  }

  // now draw the schedule to the screen

  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 77, 0);

  itoa(onHour, char3, 10);
  if (onHour>=0 && onHour<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 123, 113);

  itoa(onMin, char3, 10);
  if (onMin>=0 && onMin<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 201, 113);

  itoa(offHour, char3, 10);
  if (offHour>=0 && offHour<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 123, 194);

  itoa(offMin, char3, 10);
  if (offMin>=0 && offMin<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 201, 194);

  //myFiles.load(161, 249, 30, 30, schedActiveB[isActive],2);
  myFiles.load(162, 253, 46, 22, schedOnOff[isActive],2);
}

void screenPwrAuxItem(int itemNo) // screen for editing the schedule of an individual power relay
{
  dispScreen=25;
  
  myGLCD.clrScr();
  updateTimeDate(true);

  char char3[3];
  char char3t[3];
  
  // draw header
  myFiles.load(2, 2, 30, 30, "9sched.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("SCHEDULE"), 36, 12);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footschd.raw",2);

  myGLCD.setColor(222, 8, 51);
  myGLCD.print(F("POWER:"), 8, 50);
  myGLCD.setColor(255, 255, 255);

  // set variables based on the item we are scheduling
  
  int isActive, isTimer, onHour, onMin, offHour, offMin; // vars for schedule
  scheduleItem=itemNo; // track which item's scheudle we are editing
  myGLCD.setFont(arial_bold);
  
  if (itemNo==5) // Aux1
  {
    myGLCD.print(F("AUX 1"), 108, 50);
    isActive=schedAux1.active;
    onHour=schedAux1.onHour;
    onMin=schedAux1.onMinute;
    offHour=schedAux1.offHour;
    offMin=schedAux1.offMinute;
    isTimer=schedAux1.timer;
  }
  else if (itemNo==6) // Aux2
  {
    myGLCD.print(F("AUX 2"), 108, 50);
    isActive=schedAux2.active;
    onHour=schedAux2.onHour;
    onMin=schedAux2.onMinute;
    offHour=schedAux2.offHour;
    offMin=schedAux2.offMinute;
    isTimer=schedAux2.timer;
  }

  if(isTimer)
  {
    // print on/off/active and buttons
    myGLCD.print(F("REPEAT"), 5, 109);
    myGLCD.print(F("DUR-"), 5, 177);
    myGLCD.print(F("ATION"), 5, 193);
    myGLCD.print("H", 112, 73);
    myGLCD.print("M", 178, 73);
    myGLCD.print("M", 112, 148);
    myGLCD.print("S", 178, 148);
  }else
  {
    myGLCD.print(F("ON"), 5, 109);
    myGLCD.print(F("OFF"), 5, 185);
    myGLCD.print("H", 112, 73);
    myGLCD.print("M", 178, 73);
    myGLCD.print("H", 112, 148);
    myGLCD.print("M", 178, 148);
  }
  myGLCD.print(F("ACTIVE"), 5, 235);
  myGLCD.print(F("TIMER"), 5, 269);

  myGLCD.setFont(Sinclair_S);

  // buttons to edit the hour ON
  myFiles.load(108, 90, 24, 24, arrowButton[0],2);
  myFiles.load(108, 120, 24, 24, arrowButton[1],2);

  // buttons to edit the minute ON
  myFiles.load(174, 90, 24, 24, arrowButton[0],2);
  myFiles.load(174, 120, 24, 24, arrowButton[1],2);

  // buttons to edit the hour off
  myFiles.load(108, 166, 24, 24, arrowButton[0],2);
  myFiles.load(108, 196, 24, 24, arrowButton[1],2);

  // buttons to edit the minute off
  myFiles.load(174, 166, 24, 24, arrowButton[0],2);
  myFiles.load(174, 196, 24, 24, arrowButton[1],2);

  // now draw the schedule to the screen

  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 77, 0);

  itoa(onHour, char3, 10);
  if (onHour>=0 && onHour<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 137, 109);

  itoa(onMin, char3, 10);
  if (onMin>=0 && onMin<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 203, 109);

  itoa(offHour, char3, 10);
  if (offHour>=0 && offHour<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 137, 185);

  itoa(offMin, char3, 10);
  if (offMin>=0 && offMin<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 203, 185);

  //myFiles.load(161, 228, 30, 30, schedActiveB[isActive],2);
  myFiles.load(153, 232, 46, 22, schedOnOff[isActive],2);
  myFiles.load(153, 266, 46, 22, schedOnOff[isTimer],2);
}

void screenATO() // screen for editing the ATO settings
{
  dispScreen=17;
  
  myGLCD.clrScr();
  updateTimeDate(true);

  char char3[4];
  char char3t[4];

  // draw header
  myFiles.load(2, 2, 30, 30, "17ATO.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("ATO Settings"), 36, 12);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw",2);
  
  // Low level time buttons
  myFiles.load(150, 42, 24, 24, arrowButton[0],2);
  myFiles.load(150, 72, 24, 24, arrowButton[1],2);
  
  // draw low level time label
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("LOW LEVEL"), 2, 49);
  myGLCD.print(F("TIME"), 4, 70);
  myGLCD.setFont(Sinclair_S);
  myGLCD.print(F("BEFORE TOP OFF"), 8, 90);
  myGLCD.setFont(arial_bold);
  
  // Max run time buttons
  myFiles.load(150, 110, 24, 24, arrowButton[0],2);
  myFiles.load(150, 140, 24, 24, arrowButton[1],2);
  
  myGLCD.setFont(arial_bold);
  myGLCD.print(F("MAX RUN"), 2, 112);
  myGLCD.print(F("TIME"), 4, 133);

  //Labels for enable buttons
  myGLCD.print(F("ATO SYSTEM"), 8, 188);
  myGLCD.print(F("ENABLED"), 8, 209);
  
  myGLCD.print(F("RESERVOIR"), 8, 244);
  myGLCD.print(F("SWITCH"), 8, 265);
  
  //display low level wait time
  byte waitTime=EEPROM.read(42); // 42 // Low level wait time
  byte dx = 0;
  if(waitTime < 9) dx += 16;
  if(waitTime < 99) dx += 16;
  itoa(waitTime, char3, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char3, 180+dx, 59);
  
  //display low level wait time
  int maxRunTime=EEPROM.read(43); // 43 // Max run-time
  maxRunTime=maxRunTime*10;
  dx = 0;
  if(maxRunTime < 9)  dx += 16;
  if(maxRunTime < 99) dx += 16;
  itoa(maxRunTime, char3, 10);
  //myGLCD.setColor(255, 77, 0);
  myGLCD.print(char3, 180+dx, 127);
  
  byte enableATO = EEPROM.read(40);
  byte enableSwitch = EEPROM.read(41);
  //myFiles.load(180, 196, 30, 30, schedActiveB[enableATO],2); //ATO Enabled
  //myFiles.load(180, 249, 30, 30, schedActiveB[enableSwitch],2); //Reservoir switch enabled
  myFiles.load(172, 200, 46, 22, schedOnOff[enableATO],2); //ATO Enabled
  myFiles.load(172, 253, 46, 22, schedOnOff[enableSwitch],2); //Reservoir switch enabled
  
  //draw units
  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("MIN"), 190, 83);
  myGLCD.print(F("SEC"), 190, 152);
}


void screenResyncLights() // this screen is displayed quickly as the lights are resynced
{
  myGLCD.clrScr();
  updateTimeDate(true);

  myFiles.load(2, 2, 30, 30, "5lights.raw");

  myGLCD.setFont(arial_bold);
  myGLCD.setColor(185, 55, 255);
  myGLCD.print(F("LIGHTS MODES"), 36, 12);

  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("RESYNCING"), CENTER, 132);
  myGLCD.print(F("LIGHTS..."), CENTER, 168);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
}


void screenLightRamps() // this is the screen to schedule light ramping
{
  dispScreen=13;
  touchWaitTime = LONG_WAIT;
  
  myGLCD.clrScr();
  updateTimeDate(true);

  char char3[3];
  char char3t[3];

  // draw header
  myFiles.load(2, 2, 30, 30, "9sched.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("SCHEDULE"), 36, 12);

  myGLCD.setColor(185, 55, 255);
  myGLCD.print(F("LIGHT RAMP"), CENTER, 50);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footschd.raw",2);

  // grid for schedule
  myGLCD.drawLine(0, 100, 239, 100);
  myGLCD.drawLine(0, 126, 239, 126);
  myGLCD.drawLine(0, 152, 239, 152);
  myGLCD.drawLine(0, 178, 239, 178);
  myGLCD.drawLine(0, 204, 239, 204);
  myGLCD.drawLine(0, 230, 239, 230);
  myGLCD.drawLine(0, 256, 239, 256);

  // schedule headers
  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("MODE"), 24, 90);
  myGLCD.print(F("START"), 100, 90);
  myGLCD.print(F("LENGTH"), 176, 90);

  // ramp mode icons
  myFiles.load(9, 104, 66, 19, "13ramp1.raw",2);
  myFiles.load(9, 130, 66, 19, "13ramp2.raw",2);
  myFiles.load(9, 156, 66, 19, "13ramp3.raw",2);
  myFiles.load(9, 182, 66, 19, "13ramp4.raw",2);
  myFiles.load(9, 208, 66, 19, "13ramp5.raw",2);
  myFiles.load(9, 234, 66, 19, "13ramp6.raw",2);

  /////////////////////////////////// RAMP 1

  // convert on hour to char
  itoa(ramp1.onHour, char3, 10); 
  if (ramp1.onHour>=0 && ramp1.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 100, 109);         
  myGLCD.print(":", 116, 109);         

  // convert on min to char
  itoa(ramp1.onMinute, char3, 10); 
  if (ramp1.onMinute>=0 && ramp1.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 124, 109);

  // convert off hour to char
  itoa(ramp1.offHour, char3, 10); 
  if (ramp1.offHour>=0 && ramp1.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 180, 109);         
  myGLCD.print(":", 196, 109);         

  // convert off min to char
  itoa(ramp1.offMinute, char3, 10); 
  if (ramp1.offMinute>=0 && ramp1.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 204, 109); 

  ///////////////////////////////// RAMP 2 schedule

  // convert on hour to char
  itoa(ramp2.onHour, char3, 10); 
  if (ramp2.onHour>=0 && ramp2.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 100, 135);         
  myGLCD.print(":", 116, 135);         

  // convert on min to char
  itoa(ramp2.onMinute, char3, 10); 
  if (ramp2.onMinute>=0 && ramp2.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 124, 135);

  // convert off hour to char
  itoa(ramp2.offHour, char3, 10); 
  if (ramp2.offHour>=0 && ramp2.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 180, 135);         
  myGLCD.print(":", 196, 135);         

  // convert off min to char
  itoa(ramp2.offMinute, char3, 10); 
  if (ramp2.offMinute>=0 && ramp2.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 204, 135);

  ///////////////////////////////// RAMP 3 schedule

  // convert on hour to char
  itoa(ramp3.onHour, char3, 10); 
  if (ramp3.onHour>=0 && ramp3.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 100, 160);         
  myGLCD.print(":", 116, 160);         

  // convert on min to char
  itoa(ramp3.onMinute, char3, 10); 
  if (ramp3.onMinute>=0 && ramp3.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 124, 160);

  // convert off hour to char
  itoa(ramp3.offHour, char3, 10); 
  if (ramp3.offHour>=0 && ramp3.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 180, 160);         
  myGLCD.print(":", 196, 160);         

  // convert off min to char
  itoa(ramp3.offMinute, char3, 10); 
  if (ramp3.offMinute>=0 && ramp3.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 204, 160);

  ///////////////////////////////// RAMP 4 schedule

  // convert on hour to char
  itoa(ramp4.onHour, char3, 10); 
  if (ramp4.onHour>=0 && ramp4.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 100, 186);         
  myGLCD.print(":", 116, 186);         

  // convert on min to char
  itoa(ramp4.onMinute, char3, 10); 
  if (ramp4.onMinute>=0 && ramp4.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 124, 186);

  // convert off hour to char
  itoa(ramp4.offHour, char3, 10); 
  if (ramp4.offHour>=0 && ramp4.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 180, 186);         
  myGLCD.print(":", 196, 186);         

  // convert off min to char
  itoa(ramp4.offMinute, char3, 10); 
  if (ramp4.offMinute>=0 && ramp4.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 204, 186);

  ///////////////////////////////// RAMP 5 schedule

  // convert on hour to char
  itoa(ramp5.onHour, char3, 10); 
  if (ramp5.onHour>=0 && ramp5.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 100, 212);         
  myGLCD.print(":", 116, 212);         

  // convert on min to char
  itoa(ramp5.onMinute, char3, 10); 
  if (ramp5.onMinute>=0 && ramp5.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 124, 212);

  // convert off hour to char
  itoa(ramp5.offHour, char3, 10); 
  if (ramp5.offHour>=0 && ramp5.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 180, 212);         
  myGLCD.print(":", 196, 212);         

  // convert off min to char
  itoa(ramp5.offMinute, char3, 10); 
  if (ramp5.offMinute>=0 && ramp5.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 204, 212);

  ///////////////////////////////// RAMP 6 schedule

  // convert on hour to char
  itoa(ramp6.onHour, char3, 10); 
  if (ramp6.onHour>=0 && ramp6.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 100, 238);         
  myGLCD.print(":", 116, 238);         

  // convert on min to char
  itoa(ramp6.onMinute, char3, 10); 
  if (ramp6.onMinute>=0 && ramp6.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 124, 238);

  // convert off hour to char
  itoa(ramp6.offHour, char3, 10); 
  if (ramp6.offHour>=0 && ramp6.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 180, 238);         
  myGLCD.print(":", 196, 238);         

  // convert off min to char
  itoa(ramp6.offMinute, char3, 10); 
  if (ramp6.offMinute>=0 && ramp6.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 204, 238);

  //////////////////////////////////// print power information
  myGLCD.setColor(222, 8, 51);
  myGLCD.print(F("POWER ON"), 28, 276);
  myGLCD.print(F("POWER OFF"), 144, 276);
  myGLCD.setColor(255, 255, 255);
  // convert light 1 on hour to char
  itoa(schedLights1.onHour, char3, 10); 
  if (schedLights1.onHour>=0 && schedLights1.onHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 40, 288);         
  myGLCD.print(":", 56, 288);         

  // convert light 1 on min to char
  itoa(schedLights1.onMinute, char3, 10); 
  if (schedLights1.onMinute>=0 && schedLights1.onMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 64, 288);

  // convert light 1 off hour to char
  itoa(schedLights1.offHour, char3, 10); 
  if (schedLights1.offHour>=0 && schedLights1.offHour<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 160, 288);         
  myGLCD.print(":", 176, 288);         

  // convert light 1 off min to char
  itoa(schedLights1.offMinute, char3, 10); 
  if (schedLights1.offMinute>=0 && schedLights1.offMinute<=9) // add a zero if needed
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 184, 288);

}

void screenLightRampItem(byte rampNo)  // screen to edit the ramp schedule for an individual item
{
  dispScreen=14;
  
  myGLCD.clrScr();
  updateTimeDate(true);

  char char3[3];
  char char3t[3];

  scheduleItem=rampNo; // keep track of which item we are editing

  // draw header
  myFiles.load(2, 2, 30, 30, "9sched.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("SCHEDULE"), 36, 12);

  myGLCD.setColor(185, 55, 255);
  myGLCD.print(F("RAMP"), 36, 34);

  itoa(rampNo, char3, 10); //convert rampNo to char to display
  myGLCD.print(char3, 116, 34);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footschd.raw",2);

  myGLCD.drawLine(75, 182, 239, 182); // separator line


  myFiles.load(15, 160, 29, 45, "14down.raw",2); // down arrow

  myGLCD.setColor(255, 255, 255);

  myGLCD.print(F("START"), 75, 84);
  myGLCD.print(F("LENGTH"), 75, 192);

  myGLCD.setFont(Sinclair_S);

  // start hour up/down
  myGLCD.print("H", 83, 103);
  myFiles.load(75, 120, 24, 24, arrowButton[0],2);
  myFiles.load(75, 150, 24, 24, arrowButton[1],2);

  // start min up/down
  myGLCD.print("M", 162, 103);
  myFiles.load(154, 120, 24, 24, arrowButton[0],2);
  myFiles.load(154, 150, 24, 24, arrowButton[1],2);

  // length hour up/down
  myGLCD.print("H", 83, 214);
  myFiles.load(75, 231, 24, 24, arrowButton[0],2);
  myFiles.load(75, 261, 24, 24, arrowButton[1],2);

  // length min up/down
  myGLCD.print("M", 162, 214);
  myFiles.load(154, 231, 24, 24, arrowButton[0],2);
  myFiles.load(154, 261, 24, 24, arrowButton[1],2);

  int onHour, onMin, offHour, offMin; // vars for schedule

  // based on which ramp mode, get schedule and print mode and icons
  if (rampNo==1)
  {
    onHour=ramp1.onHour;
    onMin=ramp1.onMinute;
    offHour=ramp1.offHour; // duration/length... not tehcnically "off"
    offMin=ramp1.offMinute; // duration/length... not tehcnically "off"
    myGLCD.print(F("MOON TO LOW SUN"), 40, 54);
    myFiles.load(6, 101, 48, 48, lightMode[3],2); // starting mode
    myFiles.load(6, 212, 48, 48, lightMode[2],2); // ending mode
  }
  else if (rampNo==2)
  {
    onHour=ramp2.onHour;
    onMin=ramp2.onMinute;
    offHour=ramp2.offHour; // duration/length... not tehcnically "off"
    offMin=ramp2.offMinute; // duration/length... not tehcnically "off"
    myGLCD.print(F("LOW SUN TO MID SUN"), 40, 54);
    myFiles.load(6, 101, 48, 48, lightMode[2],2); // starting mode
    myFiles.load(6, 212, 48, 48, lightMode[1],2); // ending mode
  }
  else if (rampNo==3)
  {
    onHour=ramp3.onHour;
    onMin=ramp3.onMinute;
    offHour=ramp3.offHour; // duration/length... not tehcnically "off"
    offMin=ramp3.offMinute; // duration/length... not tehcnically "off"
    myGLCD.print(F("MID SUN TO HIGH SUN"), 40, 54);
    myFiles.load(6, 101, 48, 48, lightMode[1],2); // starting mode
    myFiles.load(6, 212, 48, 48, lightMode[0],2); // ending mode
  }
  else if (rampNo==4)
  {
    onHour=ramp4.onHour;
    onMin=ramp4.onMinute;
    offHour=ramp4.offHour; // duration/length... not tehcnically "off"
    offMin=ramp4.offMinute; // duration/length... not tehcnically "off"
    myGLCD.print(F("HIGH SUN TO MID SUN"), 40, 54);
    myFiles.load(6, 101, 48, 48, lightMode[0],2); // starting mode
    myFiles.load(6, 212, 48, 48, lightMode[1],2); // ending mode
  }
  else if (rampNo==5)
  {
    onHour=ramp5.onHour;
    onMin=ramp5.onMinute;
    offHour=ramp5.offHour; // duration/length... not tehcnically "off"
    offMin=ramp5.offMinute; // duration/length... not tehcnically "off"
    myGLCD.print(F("MID SUN TO LOW SUN"), 40, 54);
    myFiles.load(6, 101, 48, 48, lightMode[1],2); // starting mode
    myFiles.load(6, 212, 48, 48, lightMode[2],2); // ending mode
  }
  else if (rampNo==6)
  {
    onHour=ramp6.onHour;
    onMin=ramp6.onMinute;
    offHour=ramp6.offHour; // duration/length... not tehcnically "off"
    offMin=ramp6.offMinute; // duration/length... not tehcnically "off"
    myGLCD.print(F("LOW SUN TO MOON"), 40, 54);
    myFiles.load(6, 101, 48, 48, lightMode[2],2); // starting mode
    myFiles.load(6, 212, 48, 48, lightMode[3],2); // ending mode
  }

  // WRITE OUT ALL OF THE STORED TIMES
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 77, 0);

  itoa(onHour, char3, 10);
  if (onHour>=0 && onHour<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 110, 139);

  itoa(onMin, char3, 10);
  if (onMin>=0 && onMin<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 189, 139);

  itoa(offHour, char3, 10);
  if (offHour>=0 && offHour<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 110, 250);

  itoa(offMin, char3, 10);
  if (offMin>=0 && offMin<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 189, 250);
}

// screen for scheduling the dosing pumps, screen draws based on which pump
void screenDosingSched(byte pumpNo) 
{
  dispScreen=15;
  
  myGLCD.clrScr();
  updateTimeDate(true);

  char char3[3];
  char char3t[3];

  scheduleItem=pumpNo; // track which pump we are editing

  // draw header
  myFiles.load(2, 2, 30, 30, "9sched.raw",2);
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(238, 0, 145);
  myGLCD.print(F("SCHEDULE"), 36, 12);

  myGLCD.setColor(138, 93, 35);
  myGLCD.print(F("DOSING"), 36, 34);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myGLCD.drawLine(70, 70, 70, 170); // separator line
  myFiles.load(107, 294, 26, 26, "footschd.raw",2);

  // macro and micro buttons to swap schedules
  myFiles.load(12, 61, 46, 48,"15pump1.raw",2);
  myFiles.load(12, 110, 46, 48,"15pump2.raw",2);
  myFiles.load(12, 159, 46, 48,"15pump3.raw",2);
  
  //Highlight selected pump
  myGLCD.setColor(VGA_WHITE); 
  if(pumpNo == 1) myGLCD.drawRoundRect(12,61,58,109);//x1,y1,x2,y2
  if(pumpNo == 2) myGLCD.drawRoundRect(12,110,58,158);//x1,y1,x2,y2
  if(pumpNo == 3) myGLCD.drawRoundRect(12,159,58,207);//x1,y1,x2,y2
  
  // vars for scheduling
  byte onHour, onMin, daySun, dayMon, dayTue, dayWed, dayThu, dayFri, daySat;

  // based on which pump, get the schedule 
  if (pumpNo==1)
  {
    myGLCD.setColor(34, 81, 255);  // blue for macros
    myGLCD.print(F("MACROS"), 85, 70);
    onHour=pump1.onHour;
    onMin=pump1.onMinute;
    daySun=pump1.Sunday;
    dayMon=pump1.Monday;
    dayTue=pump1.Tuesday;
    dayWed=pump1.Wednesday;
    dayThu=pump1.Thursday;
    dayFri=pump1.Friday;
    daySat=pump1.Saturday;
  }
  else if (pumpNo==2)
  {
    myGLCD.setColor(255, 77, 0);  // orange for micros
    myGLCD.print(F("MICROS"), 85, 70);
    onHour=pump2.onHour;
    onMin=pump2.onMinute;
    daySun=pump2.Sunday;
    dayMon=pump2.Monday;
    dayTue=pump2.Tuesday;
    dayWed=pump2.Wednesday;
    dayThu=pump2.Thursday;
    dayFri=pump2.Friday;
    daySat=pump2.Saturday;
  }
  else if (pumpNo==3)
  {
    myGLCD.setColor(34, 255, 77);  // green for excel
    myGLCD.print(F("EXCEL"), 85, 70);
    onHour=pump3.onHour;
    onMin=pump3.onMinute;
    daySun=pump3.Sunday;
    dayMon=pump3.Monday;
    dayTue=pump3.Tuesday;
    dayWed=pump3.Wednesday;
    dayThu=pump3.Thursday;
    dayFri=pump3.Friday;
    daySat=pump3.Saturday;
  }
  // convert schedule to char and print
  itoa(onHour, char3, 10);
  if (onHour>=0 && onHour<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 120, 129);

  itoa(onMin, char3, 10);
  if (onMin>=0 && onMin<=9) // add a zero
  {
    itoa(0, char3t, 10); //make char3t 0
    strcat(char3t, char3);
    strcpy (char3,char3t);
  }
  myGLCD.print(char3, 199, 129);

  // buttons to set time
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(Sinclair_S);
  myGLCD.print(F("H"), 93, 93);
  myFiles.load(85, 110, 24, 24, arrowButton[0],2);
  myFiles.load(85, 140, 24, 24, arrowButton[1],2);
  myGLCD.print(F("M"), 172, 93);
  myFiles.load(164, 110, 24, 24, arrowButton[0],2);
  myFiles.load(164, 140, 24, 24, arrowButton[1],2);

  // days of the week check boxes
  myGLCD.print(F("SUN"), 54, 203);
  myFiles.load(51, 214, 30, 30, schedActiveB[daySun],2); 
  myGLCD.print(F("MON"), 108, 203);
  myFiles.load(105, 214, 30, 30, schedActiveB[dayMon],2); 
  myGLCD.print(F("TUE"), 162, 203);
  myFiles.load(159, 214, 30, 30, schedActiveB[dayTue],2); 
  myGLCD.print(F("WED"), 33, 250);
  myFiles.load(30, 261, 30, 30, schedActiveB[dayWed],2); 
  myGLCD.print(F("THU"), 87, 250);
  myFiles.load(84, 261, 30, 30, schedActiveB[dayThu],2); 
  myGLCD.print(F("FRI"), 135, 250);
  myFiles.load(132, 261, 30, 30, schedActiveB[dayFri],2); 
  myGLCD.print(F("SAT"), 189, 250);
  myFiles.load(186, 261, 30, 30, schedActiveB[daySat],2); 
}

void screenScreen() // this is the screen for setting brightness settings
{
  dispScreen=16;
  char char3[3]; // used to convernt numbers to char
  char char4[4]; // used to convernt numbers to char

  myGLCD.clrScr();
  updateTimeDate(true);

  // draw header
  myFiles.load(2, 2, 30, 30, "16screen.raw");
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(F("SCREEN"), 36, 12);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(40, 31, 239, 31); // under header

  // 3 horizontal separater lines
  myGLCD.drawLine(0, 102, 239, 102);
  myGLCD.drawLine(0, 170, 239, 170);
  myGLCD.drawLine(0, 238, 239, 238);

  // draw return home labels
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("RETURN"), 4, 49);
  myGLCD.print(F("TO HOME"), 4, 70);
  myGLCD.setFont(Sinclair_S);
  myGLCD.print(F("AFTER LAST TOUCH"), 8, 90);

  // return to home up/down buttons
  myFiles.load(145, 42, 24, 24, arrowButton[0]);
  myFiles.load(145, 72, 24, 24, arrowButton[1]);

  // draw return home setting
  myGLCD.setFont(arial_bold);
  itoa(screenRetHome, char3, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(char3, 191, 59);

  // auto dim labels
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("AUTO-DIM"), 4, 112);
  myGLCD.print(F("LEVEL"), 4, 133);
  myGLCD.setFont(Sinclair_S);
  myGLCD.print(F("1 TO 10 (1=dim)"), 6, 154);

  // auto dim up/down
  myFiles.load(145, 110, 24, 24, arrowButton[0]);
  myFiles.load(145, 140, 24, 24, arrowButton[1]);

  // auto dim setting
  itoa(screenDimLevel, char3, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(arial_bold);
  myGLCD.print(char3, 191, 127);

  // auto dim seconds labels
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("AUTO-DIM"), 4, 181);
  myGLCD.print(F("SECONDS"), 4, 202);
  myGLCD.setFont(Sinclair_S);
  myGLCD.print(F("AFTER LAST TOUCH"), 6, 223);

  // auto dim seconds up/down
  myFiles.load(145, 178, 24, 24, arrowButton[0]);
  myFiles.load(145, 208, 24, 24, arrowButton[1]);

  // auto dim seconds setting
  itoa(screenDimSec, char4, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(arial_bold);
  myGLCD.print(char4, 191, 197);

  // brightness labels
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("BRIGHT"), 4, 249);
  myGLCD.setFont(Sinclair_S);
  myGLCD.print(F("WHEN IN USE"), 6, 270);

  // brightness up/down
  myFiles.load(145, 245, 24, 24, arrowButton[0]);
  myFiles.load(145, 275, 24, 24, arrowButton[1]);

  // brightness setting
  itoa(screenBrightMem, char4, 10);
  myGLCD.setColor(255, 77, 0);
  myGLCD.setFont(arial_bold);
  myGLCD.print(char4, 191, 264);

  // labels under each setting
  myGLCD.setFont(Sinclair_S);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("MIN"), 195, 83);
  myGLCD.print(F("1-10"), 187, 151);
  myGLCD.print(F("SEC"), 195, 221);
  myGLCD.print(F("1-10"), 187, 288);

  myGLCD.setColor(130, 130, 130);  
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw");
}

void screenLunar()
{
  dispScreen=21;

  myGLCD.clrScr();
  updateTimeDate(true);

  // draw header
  myFiles.load(2, 2, 30, 30, "21moon.raw");
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(185, 55, 255);
  myGLCD.print(F("Lunar Cycle"), 36, 12);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer

  myFiles.load(107, 294, 26, 26, "footextr.raw"); // footer button
  
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print(F("Enabled"), 39, 62);
  
  // Enable/disable buttons
  byte lunarEnabled = EEPROM.read(70);
  myFiles.load(190, 55, 30, 30, schedActiveB[lunarEnabled]);
  
  myGLCD.print(F("Current cycle:"), 8, 100);
  byte moonType = 0; 
  // 0 = new moon, 1 = New Crescent, 2 = First Quarter, 3 = Waxing Gibbous, 4 = Full Moon, 
  // 5 = Waning Gibbous, 6 = Last Quarter, 7 = Old Crescent
  byte lunarCycleDay = getLunarCycleDay();
  if ((lunarCycleDay >= 0) && (lunarCycleDay <= 2))
  {
    moonType = 0;
    myGLCD.print(F("New moon"), 56, 200);
  }
  if ((lunarCycleDay >= 3) && (lunarCycleDay <= 5))
  {
    moonType = 1;
    myGLCD.print(F("New Crescent"), 24, 200);
  }
  if ((lunarCycleDay >= 6) && (lunarCycleDay <= 9))
  {
    moonType = 2;
    myGLCD.print(F("First Quarter"), 16, 200);
  }
  if ((lunarCycleDay >= 10) && (lunarCycleDay <= 12))
  {
    moonType = 3;
    myGLCD.print(F("Waxing Gibbous"), 8, 200);
  }
  if ((lunarCycleDay >= 13) && (lunarCycleDay <= 16))
  {
    moonType = 4;
    myGLCD.print(F("Full moon"), 48, 200);
  }
  if ((lunarCycleDay >= 17) && (lunarCycleDay <= 20)) 
  {
    moonType = 5;
    myGLCD.print(F("Waning Gibbous"), 8, 200);
  }
  if ((lunarCycleDay >= 21) && (lunarCycleDay <= 23))
  {
    moonType = 6;
    myGLCD.print(F("Last Quarter"), 24, 200);
  }
  if ((lunarCycleDay >= 24) && (lunarCycleDay <= 27))
  {
    moonType = 7;
    myGLCD.print(F("Old Crescent"), 24, 200);
  }
  if ((lunarCycleDay >= 28) && (lunarCycleDay <= 30))
  {
    moonType = 0;
    myGLCD.print(F("New moon"), 56, 200);
  }
  
  myFiles.load(87, 120, 65, 65, moonImages[moonType]);
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(Sinclair_S);
  myGLCD.print(F("Adjusts Moonlight setting"), 20, 240);
  myGLCD.print(F("down to 10% based on"), 40, 250);
  myGLCD.print(F("lunar calender"), 64, 260);
}

void screenColor(byte selectedChan)
{
  dispScreen=22;

  if(selectedChan == 0) //re-draw entire screen
  {
    myGLCD.clrScr();
    updateTimeDate(true);
  
    // draw header
    myFiles.load(2, 2, 30, 30, "22color.raw");
    myGLCD.setFont(arial_bold);
    myGLCD.setColor(255, 77, 0);
    myGLCD.print(F("LED colors"), 36, 12);

    myGLCD.setColor(130, 130, 130);
    myGLCD.drawLine(40, 31, 239, 31); // under header
    myGLCD.drawLine(0, 307, 104, 307); // left footer
    myGLCD.drawLine(136, 307, 239, 307); // right footer

    myFiles.load(107, 294, 26, 26, "footextr.raw");  // footer settings button
    
    myGLCD.setFont(arial_bold);
    myGLCD.setColor(255, 255, 255);
    myGLCD.print(F("Current colors"), 8, 49);
    myGLCD.print(F("Available"), 48, 200);
    myGLCD.print(F("Colors"), 72, 220);
    
    //draw labels above colors
    myGLCD.setFont(Sinclair_S);
    myGLCD.print(F("LED 1"), 28, 71);
    myGLCD.print(F("LED 2"), 99, 71);
    myGLCD.print(F("LED 3"), 170, 71);
    myGLCD.print(F("LED 4"), 28, 131);
    myGLCD.print(F("LED 5"), 99, 131);
    myGLCD.print(F("LED 6"), 170, 131);
    
    //Draw available colors
    myGLCD.setColor(VGAColor[0]);
    myGLCD.fillRect(8, 243, 33, 268);
    myGLCD.setColor(VGAColor[1]);
    myGLCD.fillRect(41, 243, 66, 268);
    myGLCD.setColor(VGAColor[2]);
    myGLCD.fillRect(74, 243, 99, 268);
    myGLCD.setColor(VGAColor[3]);
    myGLCD.fillRect(107, 243, 132, 268);
    myGLCD.setColor(VGAColor[4]);
    myGLCD.fillRect(140, 243, 165, 268);
    myGLCD.setColor(VGAColor[5]);
    myGLCD.fillRect(173, 243, 198, 268);
    myGLCD.setColor(VGAColor[6]);
    myGLCD.fillRect(206, 243, 231, 268);
  }
    
  //Unselected outlines
  myGLCD.setColor(100, 100, 100);
  myGLCD.drawRect(26, 80, 71, 125); //bar 1
  myGLCD.drawRect(25, 79, 72, 126);
  myGLCD.drawRect(97, 80, 142, 125); //bar 2
  myGLCD.drawRect(96, 79, 143, 126);
  myGLCD.drawRect(168, 80, 213, 125); //bar 3
  myGLCD.drawRect(167, 79, 214, 126);
  myGLCD.drawRect(26, 140, 71, 185); //bar 4
  myGLCD.drawRect(25, 139, 72, 186);
  myGLCD.drawRect(97, 140, 142, 185); //bar 5
  myGLCD.drawRect(96, 139, 143, 186);
  myGLCD.drawRect(168, 140, 213, 185); //bar 6
  myGLCD.drawRect(167, 139, 214, 186);
  
  //fill in current colors
  myGLCD.setColor(VGAColor[barColors[0]]);
  myGLCD.fillRect(27, 81, 70, 124);
  myGLCD.setColor(VGAColor[barColors[1]]);
  myGLCD.fillRect(98, 81, 141, 124);
  myGLCD.setColor(VGAColor[barColors[2]]);
  myGLCD.fillRect(169, 81, 212, 124);
  myGLCD.setColor(VGAColor[barColors[3]]);
  myGLCD.fillRect(27, 141, 70, 184);
  myGLCD.setColor(VGAColor[barColors[4]]);
  myGLCD.fillRect(98, 141, 141, 184);
  myGLCD.setColor(VGAColor[barColors[5]]);
  myGLCD.fillRect(169, 141, 212, 184);
  
  // selected outlines (2 pixels thick)
  myGLCD.setColor(VGA_WHITE);
  if(selectedChan == 1){myGLCD.drawRect(25, 79, 72, 126);myGLCD.drawRect(26, 80, 71, 125);}
  if(selectedChan == 2){myGLCD.drawRect(96, 79, 143, 126);myGLCD.drawRect(97, 80, 142, 125);}
  if(selectedChan == 3){myGLCD.drawRect(167, 79, 214, 126);myGLCD.drawRect(168, 80, 213, 125);}
  if(selectedChan == 4){myGLCD.drawRect(25, 139, 72, 186);myGLCD.drawRect(26, 140, 71, 185);}
  if(selectedChan == 5){myGLCD.drawRect(96, 139, 143, 186);myGLCD.drawRect(97, 140, 142, 185);}
  if(selectedChan == 6){myGLCD.drawRect(167, 139, 214, 186);myGLCD.drawRect(168, 140, 213, 185);}
}

// This will graph the LED channels.  Change xS/yS to move graph 0,0 position around, change dx/dy to resize.
// **Note: this was written for portrail display printing the graph sideways.  In order to print it properly 
// on a landscape display the parts printing the outline/grid/LED channels needs to be updated.
void screenGraphLEDs()
{
  dispScreen = 23;
  myGLCD.clrScr();
  // draw header
  myFiles.load(2, 2, 30, 30, "23graph.raw");
  myGLCD.setFont(arial_bold);
  myGLCD.setColor(255, 77, 0);
  myGLCD.print(F("LED graph"), 36, 12);
  updateTimeDate(true);

  myGLCD.setColor(130, 130, 130);
  myGLCD.drawLine(40, 31, 239, 31); // under header
  myGLCD.drawLine(0, 307, 104, 307); // left footer
  myGLCD.drawLine(136, 307, 239, 307); // right footer
  myFiles.load(107, 294, 26, 26, "footextr.raw");  // footer settings button
  
  //Draw graph
  byte xS = 65;   // x coordinate of 0,0 position of graph
  byte yS = 50;   // y coordinate of 0,0 position of graph
  byte dx = 240;  // number of pixels on x-axis
  byte dy = 144;  // number of pixels on y-axis
  char char6[6];
  
  // draw graph outline
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRect(xS, yS, xS+dy, yS+dx);
  
  /* graph outline for portrait
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRect(xS, yS, xS+dx, yS+dy);
  */
  
  // draw axis labels
  myGLCD.setFont(arial_bold);
  myGLCD.print(F("% Output"),xS+8,yS-17);
  myGLCD.setFont(Sinclair_S);
  myGLCD.print(F("12:00AM"),xS-57,yS-2);
  myGLCD.print(F("6:00AM"),xS-49,yS-4+(dx/4));
  myGLCD.print(F("12:00PM"),xS-57,yS-4+(dx/2));
  myGLCD.print(F("6:00PM"),xS-49,yS-4+((dx*3)/4));
  myGLCD.print(F("12:00AM"),xS-57,yS-4+dx);
  
  // draw graph grid
  myGLCD.setColor(100, 100, 100);
  for( int a = 1 ; a < 24 ; a++) // one line per hour
  {
    myGLCD.drawLine(xS+1,yS+(a*(dx/24)),xS+dy-1,yS+(a*(dx/24)));
  }
  for( int a = 1 ; a < 4 ; a++) // one line at 25/50/75% PWM
  {
    myGLCD.drawLine(xS+a*(dy/4),yS+1,xS+a*(dy/4),yS+dx-1);
  }
  
  /* grids for portrait
  myGLCD.setColor(100, 100, 100);
  for( int a = 1 ; a < 24 ; a++) // one line per hour
  {
    myGLCD.drawLine(xS+(a*(dx/24)),yS+1,xS+(a*(dx/24)),yS+dy-1);
  }
  for( int a = 1 ; a < 4 ; a++) // one line at 25/50/75% PWM
  {
    myGLCD.drawLine(xS+1,yS+a*(dy/4),xS+dx-1,yS+a*(dy/4));
  }
  */
  
  //===========  Graphing code starts here  =========================

  //draw channel 1 line here
  graphChannel(lightLowSun.chan1,lightMidSun.chan1,lightHighSun.chan1,lightMoon.chan1,1,xS,yS,dx,dy);
  //draw channel 2 line here
  graphChannel(lightLowSun.chan2,lightMidSun.chan2,lightHighSun.chan2,lightMoon.chan2,2,xS,yS,dx,dy);
  //draw channel 3 line here
  graphChannel(lightLowSun.chan3,lightMidSun.chan3,lightHighSun.chan3,lightMoon.chan3,3,xS,yS,dx,dy);
  //draw channel 4 line here
  graphChannel(lightLowSun.chan4,lightMidSun.chan4,lightHighSun.chan4,lightMoon.chan4,4,xS,yS,dx,dy);
  if(lightCSP == false)
  {
    //draw channel 5 line here
    graphChannel(lightLowSun.chan5,lightMidSun.chan5,lightHighSun.chan5,lightMoon.chan5,5,xS,yS,dx,dy);
    //draw channel 6 line here
    graphChannel(lightLowSun.chan6,lightMidSun.chan6,lightHighSun.chan6,lightMoon.chan6,6,xS,yS,dx,dy);
  }
  // refresh outline to cover any lines that print on it
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRect(xS, yS, xS+dy, yS+dx);
}

void graphChannel(int lowSunVal,int midSunVal,int highSunVal,int moonVal,byte channel,int x,int y,int dx,int dy)
{
  unsigned int divisor = 1440 / dx; // Minutes in a day divided by number of x-axis pixels
  //14 x,y points on graph, 12 points at ramp start/ends and 1 each for start/end of graph
  unsigned int xPos[14]; 
  unsigned int yPos[14];
  //if ramp starts before midnight but ends after this variable is used to calculate the cross-over value
  long transitionValue; 
  long rampTime;
  
  //calculate start/end time of each ramp
  unsigned long startRamp1 = (ramp1.onHour*60) + ramp1.onMinute;
  unsigned long endRamp1 = startRamp1 + ((ramp1.offHour*60) + ramp1.offMinute);
  unsigned long startRamp2 = (ramp2.onHour*60) + ramp2.onMinute;
  unsigned long endRamp2 = startRamp2 + ((ramp2.offHour*60) + ramp2.offMinute);
  unsigned long startRamp3 = (ramp3.onHour*60) + ramp3.onMinute;
  unsigned long endRamp3 = startRamp3 + ((ramp3.offHour*60) + ramp3.offMinute);
  unsigned long startRamp4 = (ramp4.onHour*60) + ramp4.onMinute;
  unsigned long endRamp4 = startRamp4 + ((ramp4.offHour*60) + ramp4.offMinute);
  unsigned long startRamp5 = (ramp5.onHour*60) + ramp5.onMinute;
  unsigned long endRamp5 = startRamp5 + ((ramp5.offHour*60) + ramp5.offMinute);
  unsigned long startRamp6 = (ramp6.onHour*60) + ramp6.onMinute;
  unsigned long endRamp6 = startRamp6 + ((ramp6.offHour*60) + ramp6.offMinute);
  
  // divide by divisor to bring scale to 0-dx
  startRamp1 /= divisor;
  endRamp1 /= divisor;
  startRamp2 /= divisor;
  endRamp2 /= divisor;
  startRamp3 /= divisor;
  endRamp3 /= divisor;
  startRamp4 /= divisor;
  endRamp4 /= divisor;
  startRamp5 /= divisor;
  endRamp5 /= divisor;
  startRamp6 /= divisor;
  endRamp6 /= divisor;
  
  //roll-over any end points after midnight
  if(endRamp1 > dx) endRamp1 -= dx;
  if(endRamp2 > dx) endRamp2 -= dx;
  if(endRamp3 > dx) endRamp3 -= dx;
  if(endRamp4 > dx) endRamp4 -= dx;
  if(endRamp5 > dx) endRamp5 -= dx;
  if(endRamp6 > dx) endRamp6 -= dx;
  
  //y-axis points (% of PWM output)
  moonVal = map(moonVal,0,100,1,dy-1); // results in value of 0-dy excluding graph outline
  lowSunVal = map(lowSunVal,0,100,1,dy-1); 
  midSunVal = map(midSunVal,0,100,1,dy-1);
  highSunVal = map(highSunVal,0,100,1,dy-1);
  
  if(startRamp1 < endRamp6) // case 1: ramp 1 starts after midnight
  {
    xPos[0] = 0; //start at 0:00
    yPos[0] = moonVal;
    xPos[1] = startRamp1;
    yPos[1] = moonVal;
    xPos[2] = endRamp1;
    yPos[2] = lowSunVal;
    xPos[3] = startRamp2;
    yPos[3] = lowSunVal;
    xPos[4] = endRamp2;
    yPos[4] = midSunVal;
    xPos[5] = startRamp3;
    yPos[5] = midSunVal;
    xPos[6] = endRamp3;
    yPos[6] = highSunVal;
    xPos[7] = startRamp4;
    yPos[7] = highSunVal;
    xPos[8] = endRamp4;
    yPos[8] = midSunVal;
    xPos[9] = startRamp5;
    yPos[9] = midSunVal;
    xPos[10] = endRamp5;
    yPos[10] = lowSunVal;
    xPos[11] = startRamp6;
    yPos[11] = lowSunVal;
    xPos[12] = endRamp6;
    yPos[12] = moonVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = moonVal;
  }else if(endRamp6 < startRamp6) //case 2: ramp 6 starts before but ends after midnight
  {
    //calculate value at midnight:
    rampTime = ((ramp1.offHour*60) + ramp1.offMinute) / divisor;
    transitionValue = (endRamp6 * (lowSunVal - moonVal));
    transitionValue = transitionValue / rampTime;
    transitionValue += moonVal;
    xPos[0] = 0; //start at 0:00
    yPos[0] = transitionValue;
    xPos[1] = endRamp6;
    yPos[1] = moonVal;
    xPos[2] = startRamp1;
    yPos[2] = moonVal;
    xPos[3] = endRamp1;
    yPos[3] = lowSunVal;
    xPos[4] = startRamp2;
    yPos[4] = lowSunVal;
    xPos[5] = endRamp2;
    yPos[5] = midSunVal;
    xPos[6] = startRamp3;
    yPos[6] = midSunVal;
    xPos[7] = endRamp3;
    yPos[7] = highSunVal;
    xPos[8] = startRamp4;
    yPos[8] = highSunVal;
    xPos[9] = endRamp4;
    yPos[9] = midSunVal;
    xPos[10] = startRamp5;
    yPos[10] = midSunVal;
    xPos[11] = endRamp5;
    yPos[11] = lowSunVal;
    xPos[12] = startRamp6;
    yPos[12] = lowSunVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = transitionValue;
  }else if(startRamp6 < endRamp5) //case 3: ramp 6 starts after midnight
  {
    xPos[0] = 0; //start at 0:00
    yPos[0] = lowSunVal;
    xPos[1] = startRamp6;
    yPos[1] = lowSunVal;
    xPos[2] = endRamp6;
    yPos[2] = moonVal;
    xPos[3] = startRamp1;
    yPos[3] = moonVal;
    xPos[4] = endRamp1;
    yPos[4] = lowSunVal;
    xPos[5] = startRamp2;
    yPos[5] = lowSunVal;
    xPos[6] = endRamp2;
    yPos[6] = midSunVal;
    xPos[7] = startRamp3;
    yPos[7] = midSunVal;
    xPos[8] = endRamp3;
    yPos[8] = highSunVal;
    xPos[9] = startRamp4;
    yPos[9] = highSunVal;
    xPos[10] = endRamp4;
    yPos[10] = midSunVal;
    xPos[11] = startRamp5;
    yPos[11] = midSunVal;
    xPos[12] = endRamp5;
    yPos[12] = lowSunVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = lowSunVal;
  }else if(endRamp5 < startRamp5) //case 4: ramp 5 starts before but ends after midnight
  {
    //calculate value at midnight:
    rampTime = ((ramp5.offHour*60) + ramp5.offMinute) / divisor;
    transitionValue = (endRamp5 * (midSunVal - lowSunVal));
    transitionValue = transitionValue / rampTime;
    transitionValue += lowSunVal;
    xPos[0] = 0; //start at 0:00
    yPos[0] = transitionValue;
    xPos[1] = endRamp5;
    yPos[1] = lowSunVal;
    xPos[2] = startRamp6;
    yPos[2] = lowSunVal;
    xPos[3] = endRamp6;
    yPos[3] = moonVal;
    xPos[4] = startRamp1;
    yPos[4] = moonVal;
    xPos[5] = endRamp1;
    yPos[5] = lowSunVal;
    xPos[6] = startRamp2;
    yPos[6] = lowSunVal;
    xPos[7] = endRamp2;
    yPos[7] = midSunVal;
    xPos[8] = startRamp3;
    yPos[8] = midSunVal;
    xPos[9] = endRamp3;
    yPos[9] = highSunVal;
    xPos[10] = startRamp4;
    yPos[10] = highSunVal;
    xPos[11] = endRamp4;
    yPos[11] = midSunVal;
    xPos[12] = startRamp5;
    yPos[12] = midSunVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = transitionValue;
  }else if(startRamp5 < endRamp4) //case 5: ramp 5 starts after midnight
  {
    xPos[0] = 0; //start at 0:00
    yPos[0] = midSunVal;
    xPos[1] = startRamp5;
    yPos[1] = midSunVal;
    xPos[2] = endRamp5;
    yPos[2] = lowSunVal;
    xPos[3] = startRamp6;
    yPos[3] = lowSunVal;
    xPos[4] = endRamp6;
    yPos[4] = moonVal;
    xPos[5] = startRamp1;
    yPos[5] = moonVal;
    xPos[6] = endRamp1;
    yPos[6] = lowSunVal;
    xPos[7] = startRamp2;
    yPos[7] = lowSunVal;
    xPos[8] = endRamp2;
    yPos[8] = midSunVal;
    xPos[9] = startRamp3;
    yPos[9] = midSunVal;
    xPos[10] = endRamp3;
    yPos[10] = highSunVal;
    xPos[11] = startRamp4;
    yPos[11] = highSunVal;
    xPos[12] = endRamp4;
    yPos[12] = midSunVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = midSunVal;
  }else if(endRamp4 < startRamp4) //case  6: ramp 4 starts before but ends after midnight
  {
    //calculate value at midnight:
    rampTime = ((ramp4.offHour*60) + ramp4.offMinute) / divisor;
    transitionValue = (endRamp4 * (highSunVal - midSunVal));
    transitionValue = transitionValue / rampTime;
    transitionValue += midSunVal;
    xPos[0] = 0; //start at 0:00
    yPos[0] = transitionValue;
    xPos[1] = endRamp4;
    yPos[1] = midSunVal;
    xPos[2] = startRamp5;
    yPos[2] = midSunVal;
    xPos[3] = endRamp5;
    yPos[3] = lowSunVal;
    xPos[4] = startRamp6;
    yPos[4] = lowSunVal;
    xPos[5] = endRamp6;
    yPos[5] = moonVal;
    xPos[6] = startRamp1;
    yPos[6] = moonVal;
    xPos[7] = endRamp1;
    yPos[7] = lowSunVal;
    xPos[8] = startRamp2;
    yPos[8] = lowSunVal;
    xPos[9] = endRamp2;
    yPos[9] = midSunVal;
    xPos[10] = startRamp3;
    yPos[10] = midSunVal;
    xPos[11] = endRamp3;
    yPos[11] = highSunVal;
    xPos[12] = startRamp4;
    yPos[12] = highSunVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = transitionValue;
  }else if(startRamp4 < endRamp3) //case  7: ramp 4 starts after midnight
  {
    xPos[0] = 0; //start at 0:00
    yPos[0] = highSunVal;
    xPos[1] = startRamp4;
    yPos[1] = highSunVal;
    xPos[2] = endRamp4;
    yPos[2] = midSunVal;
    xPos[3] = startRamp5;
    yPos[3] = midSunVal;
    xPos[4] = endRamp5;
    yPos[4] = lowSunVal;
    xPos[5] = startRamp6;
    yPos[5] = lowSunVal;
    xPos[6] = endRamp6;
    yPos[6] = moonVal;
    xPos[7] = startRamp1;
    yPos[7] = moonVal;
    xPos[8] = endRamp1;
    yPos[8] = lowSunVal;
    xPos[9] = startRamp2;
    yPos[9] = lowSunVal;
    xPos[10] = endRamp2;
    yPos[10] = midSunVal;
    xPos[11] = startRamp3;
    yPos[11] = midSunVal;
    xPos[12] = endRamp3;
    yPos[12] = highSunVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = highSunVal;
  }else if(endRamp3 < startRamp3) //case  8: ramp 3 starts before but ends after midnight
  {
    //calculate value at midnight:
    rampTime = ((ramp3.offHour*60) + ramp3.offMinute) / divisor;
    transitionValue = (endRamp3 * (midSunVal - highSunVal));
    transitionValue = transitionValue / rampTime;
    transitionValue += highSunVal;
    xPos[0] = 0; //start at 0:00
    yPos[0] = transitionValue;
    xPos[1] = endRamp3;
    yPos[1] = highSunVal;
    xPos[2] = startRamp4;
    yPos[2] = highSunVal;
    xPos[3] = endRamp4;
    yPos[3] = midSunVal;
    xPos[4] = startRamp5;
    yPos[4] = midSunVal;
    xPos[5] = endRamp5;
    yPos[5] = lowSunVal;
    xPos[6] = startRamp6;
    yPos[6] = lowSunVal;
    xPos[7] = endRamp6;
    yPos[7] = moonVal;
    xPos[8] = startRamp1;
    yPos[8] = moonVal;
    xPos[9] = endRamp1;
    yPos[9] = lowSunVal;
    xPos[10] = startRamp2;
    yPos[10] = lowSunVal;
    xPos[11] = endRamp2;
    yPos[11] = midSunVal;
    xPos[12] = startRamp3;
    yPos[12] = midSunVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = transitionValue;
  }else if(startRamp3 < endRamp2) //case  9: ramp 3 starts after midnight
  {
    xPos[0] = 0; //start at 0:00
    yPos[0] = midSunVal;
    xPos[1] = startRamp3;
    yPos[1] = midSunVal;
    xPos[2] = endRamp3;
    yPos[2] = highSunVal;
    xPos[3] = startRamp4;
    yPos[3] = highSunVal;
    xPos[4] = endRamp4;
    yPos[4] = midSunVal;
    xPos[5] = startRamp5;
    yPos[5] = midSunVal;
    xPos[6] = endRamp5;
    yPos[6] = lowSunVal;
    xPos[7] = startRamp6;
    yPos[7] = lowSunVal;
    xPos[8] = endRamp6;
    yPos[8] = moonVal;
    xPos[9] = startRamp1;
    yPos[9] = moonVal;
    xPos[10] = endRamp1;
    yPos[10] = lowSunVal;
    xPos[11] = startRamp2;
    yPos[11] = lowSunVal;
    xPos[12] = endRamp2;
    yPos[12] = midSunVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = midSunVal;
  }else if(endRamp2 < startRamp2) //case 10: ramp 2 starts before but ends after midnight
  {
    //calculate value at midnight:
    rampTime = ((ramp2.offHour*60) + ramp2.offMinute) / divisor;
    transitionValue = (endRamp2 * (lowSunVal - midSunVal));
    transitionValue = transitionValue / rampTime;
    transitionValue += midSunVal;
    xPos[0] = 0; //start at 0:00
    yPos[0] = transitionValue;
    xPos[1] = endRamp2;
    yPos[1] = midSunVal;
    xPos[2] = startRamp3;
    yPos[2] = midSunVal;
    xPos[3] = endRamp3;
    yPos[3] = highSunVal;
    xPos[4] = startRamp4;
    yPos[4] = highSunVal;
    xPos[5] = endRamp4;
    yPos[5] = midSunVal;
    xPos[6] = startRamp5;
    yPos[6] = midSunVal;
    xPos[7] = endRamp5;
    yPos[7] = lowSunVal;
    xPos[8] = startRamp6;
    yPos[8] = lowSunVal;
    xPos[9] = endRamp6;
    yPos[9] = moonVal;
    xPos[10] = startRamp1;
    yPos[10] = moonVal;
    xPos[11] = endRamp1;
    yPos[11] = lowSunVal;
    xPos[12] = startRamp2;
    yPos[12] = lowSunVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = transitionValue;
  }else if(startRamp2 < endRamp1) //case 11: ramp 2 starts after midnight
  {
    xPos[0] = 0; //start at 0:00
    yPos[0] = lowSunVal;
    xPos[1] = startRamp2;
    yPos[1] = lowSunVal;
    xPos[2] = endRamp2;
    yPos[2] = midSunVal;
    xPos[3] = startRamp3;
    yPos[3] = midSunVal;
    xPos[4] = endRamp3;
    yPos[4] = highSunVal;
    xPos[5] = startRamp4;
    yPos[5] = highSunVal;
    xPos[6] = endRamp4;
    yPos[6] = midSunVal;
    xPos[7] = startRamp5;
    yPos[7] = midSunVal;
    xPos[8] = endRamp5;
    yPos[8] = lowSunVal;
    xPos[9] = startRamp6;
    yPos[9] = lowSunVal;
    xPos[10] = endRamp6;
    yPos[10] = moonVal;
    xPos[11] = startRamp1;
    yPos[11] = moonVal;
    xPos[12] = endRamp1;
    yPos[12] = lowSunVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = lowSunVal;
  }else if(endRamp1 < startRamp1) //case 12: ramp 1 starts before but ends after midnight
  {
    //calculate value at midnight:
    rampTime = ((ramp1.offHour*60) + ramp1.offMinute) / divisor;
    transitionValue = (endRamp1 * (moonVal - lowSunVal));
    transitionValue = transitionValue / rampTime;
    transitionValue += lowSunVal;
    xPos[0] = 0; //start at 0:00
    yPos[0] = transitionValue;
    xPos[1] = endRamp1;
    yPos[1] = lowSunVal;
    xPos[2] = startRamp2;
    yPos[2] = lowSunVal;
    xPos[3] = endRamp2;
    yPos[3] = midSunVal;
    xPos[4] = startRamp3;
    yPos[4] = midSunVal;
    xPos[5] = endRamp3;
    yPos[5] = highSunVal;
    xPos[6] = startRamp4;
    yPos[6] = highSunVal;
    xPos[7] = endRamp4;
    yPos[7] = midSunVal;
    xPos[8] = startRamp5;
    yPos[8] = midSunVal;
    xPos[9] = endRamp5;
    yPos[9] = lowSunVal;
    xPos[10] = startRamp6;
    yPos[10] = lowSunVal;
    xPos[11] = endRamp6;
    yPos[11] = moonVal;
    xPos[12] = startRamp1;
    yPos[12] = moonVal;
    xPos[13] = dx-1; //end at 24:00
    yPos[13] = transitionValue;
  }
  
  //draw channel line here (portrait display)
  myGLCD.setColor(VGAColor[barColors[channel-1]]); //set to proper color for channel
  for(int i = 0; i < 13 ; i++)
  {
    myGLCD.drawLine(x+yPos[i],y+xPos[i],x+yPos[i+1],y+xPos[i+1]);
  }
  
  //draw channel line here (landscape display)
  /*myGLCD.setColor(VGAColor[color]); 
  for(int i = 0; i < 13 ; i++)
  {
    myGLCD.drawLine(x+xPos[i]  ,y+yPos[i]  ,x+xPos[i+1]  ,y+yPos[i+1]);
  }*/
}
