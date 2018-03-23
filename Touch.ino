void processMyTouch() // this is a huge block dedicated to processing all touch screen events
{
  myTouch.read();
  x = myTouch.getX();
  y = myTouch.getY();
  Serial.print(F("Touch: "));
  //Serial.print(F("  x = "));
  Serial.print(x);
  Serial.print(F(","));
  Serial.println(y);

  // initiate char vars for converting numbers to char for display
  char char3[3];
  char char3t[3] = "0"; // 3 so it can hold zero, another char and end of line
  char char6[6]; // -12.5 offset would be 5 plus an end of line
  
  itoa(0, char3t, 10); //make char3t 0
  
  // we evaluate touch based on which screen we are in

  switch (dispScreen) 
  {

  case 1:  // home screen
    
    if ((x>=30)&&(x<=90)&&(y>=35)&&(y<=86)) // pressed the thermometer to clear a warning
    {
      if(heaterWarningCleared == false)
      {
        heaterWarningCleared=true; // clear warning
        screenHome();
      }
    }
    if ((x>=150)&&(x<=210)&&(y>=50)&&(y<=105)) // pressed the ATO area
    {
      if(ATOAlarm)
      {
        Serial.print(F("ATO Alarm cleared.\n"));
        ATOAlarm=false; // clear warning
        EEPROM.write(44,0);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRect(121,32,239,109);
        drawATO();
      }
      if((ATOEnabled == false)&&(ATOPumpState == false))
      {
        digitalWrite(ATOPumpPin,HIGH);//turn ATO ON
        ATOPumpState = true;
        ATOPumpStartTime = now();
        if(dispScreen == 1)
        {
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect(121,32,239,109); //clear prev. ATO display
          drawATO();
        }
        touchWaitTime = LONG_WAIT;
      }
      else if((ATOEnabled == false)&&(ATOPumpState == true))
      {
        digitalWrite(ATOPumpPin,LOW);//turn ATO ON
        ATOPumpState = false;
        if(dispScreen == 1)
        {
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect(121,32,239,109); //clear prev. ATO display
          drawATO();
        }
      }
    }
    if ((x>=10)&&(x<=58)&&(y>=266)&&(y<=314)) // home dock icon
    {
      smartStartupPower();
      screenHome();
    }
    if ((x>=67)&&(x<=115)&&(y>=266)&&(y<=314)) // feeding dock icon
    {
      screenFeeding();
    }

    // coordinates of the power putton
    if ((x>=124)&&(x<=172)&&(y>=266)&&(y<=314)) // power dock icon
    {
      screenPower();
    }

    // coordinates of the exras button
    if ((x>=181)&&(x<=229)&&(y>=266)&&(y<=314)) // settings dock icon
    {
      screenSettings();
    }
    break;

  case 2:    // feeding screen

    if ((x>=67)&&(x<=115)&&(y>=223)&&(y<=271))  // stop button  
    {     
      feedingStop();
    }

    if ((x>=124)&&(x<=172)&&(y>=223)&&(y<=271))  // restart button  
    {     
      startFeedingTime = now(); // re-start the feeding timer
    }

    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // home button  
    {     
      screenHome();
    }

    break;

  case 3:    // power screen

    if ((x>=69)&&(x<=118)&&(y>=77)&&(y<=125))        // all on  
    {
      // turn on all power outputs
      AlarmPwrLight1_On();
      AlarmPwrLight2_On();
      pwrFilter_On();
      pwrCirc_On();
      pwrHeat_On();
      pwrCO2_On();
      pwrAux1_On();
      pwrAux2_On();
      screenPower(); // redraw screen
    }
    else if ((x>=125)&&(x<=174)&&(y>=77)&&(y<=125))    // all off
    {
      // turn off all power outputs
      AlarmPwrLight1_Off();
      AlarmPwrLight2_Off();
      pwrFilter_Off();
      pwrCirc_Off();
      pwrHeat_Off();
      pwrCO2_Off();
      pwrAux1_Off();
      pwrAux2_Off();
      screenPower(); // redraw screen
    }

    else if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // home button  
    {     
      screenHome();
    }

    else if ((x>=15)&&(x<=64)&&(y>=139)&&(y<=187))    // Front lights power
    {
      //toggle power
      if (globalPower.pwrLight1==0) AlarmPwrLight1_On();
      else if (globalPower.pwrLight1==1) AlarmPwrLight1_Off();
      // draw icons
      myFiles.load(15, 139, 48, 48, pwrLightIcon[globalPower.pwrLight1]);
      myFiles.load(34, 192, 10, 11, pwrDot[globalPower.pwrLight1]);
    }
    else if ((x>=69)&&(x<=118)&&(y>=139)&&(y<=187))    // Back lights power
    {
      // toggle power
      if (globalPower.pwrLight2==0) AlarmPwrLight2_On();
      else if (globalPower.pwrLight2==1) AlarmPwrLight2_Off();
      // draw icons
      myFiles.load(69, 139, 48, 48, pwrLightIcon[globalPower.pwrLight2]);
      myFiles.load(88, 192, 10, 11, pwrDot[globalPower.pwrLight2]);
    }
    else if ((x>=124)&&(x<=173)&&(y>=139)&&(y<=187))    // Filter power
    {
      // toggle power
      if (globalPower.pwrFilter==0) pwrFilter_On();
      else if (globalPower.pwrFilter==1)pwrFilter_Off();
      // draw icons
      myFiles.load(124, 139, 48, 48, pwrFilterIcon[globalPower.pwrFilter]);
      myFiles.load(143, 192, 10, 11, pwrDot[globalPower.pwrFilter]);
    }
    else if ((x>=178)&&(x<=227)&&(y>=139)&&(y<=187))    // Circ power
    {
      // toggle power
      if (globalPower.pwrCirc==0) pwrCirc_On();
      else if (globalPower.pwrCirc==1) pwrCirc_Off();
      // draw icons
      myFiles.load(178, 139, 48, 48, pwrCircIcon[globalPower.pwrCirc] );
      myFiles.load(197, 192, 10, 11, pwrDot[globalPower.pwrCirc]);
    }

    else if ((x>=15)&&(x<=64)&&(y>=198)&&(y<=246))    // Heat power
    {
      // toggle power
      if (globalPower.pwrHeat==0) AlarmPwrHeat_On();
      else if (globalPower.pwrHeat==1)AlarmPwrHeat_Off();
      // draw icons
      myFiles.load(15, 212, 48, 48, pwrHeatIcon[globalPower.pwrHeat] );
      myFiles.load(34, 264, 10, 11, pwrDot[globalPower.pwrHeat]);
    }
    else if ((x>=69)&&(x<=118)&&(y>=198)&&(y<=246))    // CO2 power
    {
      // toggle power
      if (globalPower.pwrCO2==0) AlarmPwrCO2_On();
      else if (globalPower.pwrCO2==1) AlarmPwrCO2_Off();
      // draw icons
      myFiles.load(69, 212, 48, 48, pwrCO2Icon[globalPower.pwrCO2] );
      myFiles.load(88, 264, 10, 11, pwrDot[globalPower.pwrCO2]);
    }
    else if ((x>=124)&&(x<=173)&&(y>=198)&&(y<=246))    // aux 1 power
    {
      // toggle power
      if (globalPower.pwrAux1==0) pwrAux1_On();
      else if (globalPower.pwrAux1==1) pwrAux1_Off();
      // draw icons
      myFiles.load(124, 212, 48, 48, pwrAux1Icon[globalPower.pwrAux1] );
      myFiles.load(143, 264, 10, 11, pwrDot[globalPower.pwrAux1]);
    }
    else if ((x>=178)&&(x<=227)&&(y>=198)&&(y<=246))    // aux 2 power
    {
      // toggle power
      if (globalPower.pwrAux2==0) pwrAux2_On();
      else if (globalPower.pwrAux2==1) pwrAux2_Off();
      // draw icons  
      myFiles.load(178, 212, 48, 48, pwrAux2Icon[globalPower.pwrAux2] );
      myFiles.load(197, 264, 10, 11, pwrDot[globalPower.pwrAux2]);
    }
    break;

  case 4:    // settings screen

    touchWaitTime = LONG_WAIT;
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // home button  
    {
      screenHome();
    }

    if ((x>=10)&&(x<=58)&&(y>=50)&&(y<=113))
    {
      // only respond to the lights button if they are turned on or PWM
      if ((globalPower.pwrLight1==1)||(lightCSP==false))
      {
        if(lightCSP==false)screenLights();
        if(lightCSP==true)screenLightsIR();
      }
    }
    else if ((x>=67)&&(x<=115)&&(y>=50)&&(y<=113))
    {
      screenClock();
    }
    else if ((x>=124)&&(x<=172)&&(y>=50)&&(y<=113))
    {
      screenFeedSettings();
    }
    else if ((x>=181)&&(x<=229)&&(y>=50)&&(y<=113))
    {
      screenSchedule();
    }
    else if ((x>=10)&&(x<=58)&&(y>=118)&&(y<=181))
    {
      screenSensors();
    }
    else if ((x>=67)&&(x<=115)&&(y>=118)&&(y<=181))
    {
      screenDosing(1);
    }
    else if ((x>=124)&&(x<=172)&&(y>=118)&&(y<=181))
    {
      screenScreen();
    }
    else if ((x>=181)&&(x<=229)&&(y>=118)&&(y<=181))
    {
      screenATO();
    }
    else if ((x>=10)&&(x<=58)&&(y>=186)&&(y<=249))
    {
      screenLunar();
    }
    else if ((x>=67)&&(x<=115)&&(y>=186)&&(y<=249))
    {
      if (lightCSP==false)
      {
        selectedChan = 0;
        screenColor(selectedChan);
      }
    }
    else if ((x>=124)&&(x<=172)&&(y>=186)&&(y<=249))
    {
      screenGraphLEDs();
    }

    break;

  case 5:    // lights screen

    if (lightEditing==0) // actions for buttons that are active when editing is not active
    {
      boolean updateLightValues=false; // track if we need to update the light values at the end due to mode change

      if ((x>=10)&&(x<=58)&&(y>=39)&&(y<=87))        //  full sun mode button
      {
        clearSelectedLight(1); // deselect the previously selected light
        currentLightMode=0;
        if (lightCSP==true) irsend.sendNEC(M1,32); // send IR to lights to change modes
        currentColor = lightHighSun; // update current color values
        tempColor = lightHighSun;
        myFiles.load(10, 101, 48, 63, lightEdit[1]); // activate the edit button
        myFiles.load(10, 39, 48, 48, lightModeS[currentLightMode]); // draw the button selected
        updateLightValues=true; // update the light values
      }
      else if ((x>=67)&&(x<=115)&&(y>=39)&&(y<=87))    //  mid sun mode button
      {
        clearSelectedLight(1); // deselect the previously selected light
        currentLightMode=1;
        if (lightCSP==true) irsend.sendNEC(M2,32); // send IR to lights to change modes
        currentColor = lightMidSun;
        tempColor = lightMidSun;
        myFiles.load(10, 101, 48, 63, lightEdit[1]); // activate the edit button
        myFiles.load(67, 39, 48, 48, lightModeS[currentLightMode]); // draw the button selected
        updateLightValues=true; // update the light values
      }
      else if ((x>=124)&&(x<=172)&&(y>=39)&&(y<=87))      //  low sun mode button
      {
        clearSelectedLight(1); // deselect the previously selected light
        currentLightMode=2;
        if (lightCSP==true) irsend.sendNEC(M3,32); // send IR to lights to change modes
        currentColor = lightLowSun;
        tempColor = lightLowSun;
        myFiles.load(10, 101, 48, 63, lightEdit[1]); // activate the edit button
        myFiles.load(124, 39, 48, 48, lightModeS[currentLightMode]); // draw the button selected
        updateLightValues=true; // update the light values
      }
      else if ((x>=181)&&(x<=229)&&(y>=39)&&(y<=87))     //  moon mode button
      {
        clearSelectedLight(1); // deselect the previously selected light
        currentLightMode=3;
        if (lightCSP==true) irsend.sendNEC(M4,32); // send IR to lights to change modes
        currentColor = lightMoon;
        tempColor = lightMoon;
        myFiles.load(10, 101, 48, 63, lightEdit[1]); // activate the edit button
        myFiles.load(181, 39, 48, 48, lightModeS[currentLightMode]); // draw the button selected
        updateLightValues=true; // update the light values
      }
      else if ((x>=10)&&(x<=58)&&(y>=101)&&(y<=149))        //  edit button
      {
        touchWaitTime = SHORT_WAIT; // can adjust sliders faster than every half second
        clearSelectedLight(2); // turn off light modes that are inactive
        lightEditing=1; // activate editing mode
        myFiles.load(181, 101, 48, 63, lightResync[0]); // disable resync
        myFiles.load(10, 101, 48, 63, lightEdit[0]); // disable edit
        myFiles.load(67, 101, 48, 63, lightSave[1]); // enable save
        myFiles.load(124, 101, 48, 63, lightCancel[1]); // enable cancel
      }
      else if ((x>=181)&&(x<=229)&&(y>=101)&&(y<=149))    //  resync button
      {
        screenResyncLights(); // display that we are resyncing
        resyncLights(); // actually resync the lights
        screenLights(); // redraw the lights screen
      }

      // if modes were switched, we need to update the lighting values
      if (updateLightValues==1)
      {
        //cancel any in progress fades since we are editing the light values
        fadeInProgress = false;
        //update bargraphs to currentColor
        drawLEDBarGraph(1,currentColor.chan1);
        drawLEDBarGraph(2,currentColor.chan2);
        drawLEDBarGraph(3,currentColor.chan3);
        drawLEDBarGraph(4,currentColor.chan4);
        drawLEDBarGraph(5,currentColor.chan5);
        drawLEDBarGraph(6,currentColor.chan6);
        //update LEDs to currentColor
        if(lightCSP == false)
        {
          //if using PCA9685 scale values to 12-bit
          if(PCA9685Installed == true)
          {
            currentColor.chan1 = map(currentColor.chan1,0,100,0,4095);
            currentColor.chan2 = map(currentColor.chan2,0,100,0,4095);
            currentColor.chan3 = map(currentColor.chan3,0,100,0,4095);
            currentColor.chan4 = map(currentColor.chan4,0,100,0,4095);
            currentColor.chan5 = map(currentColor.chan5,0,100,0,4095);
            currentColor.chan6 = map(currentColor.chan6,0,100,0,4095);
          } else //otherwise scale to 8-bit
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
    }

    else if (lightEditing==1) // actions for buttons that are active when editing is active
    {
      int dy;
      if ((x>=67)&&(x<=115)&&(y>=101)&&(y<=149))    //  save button
      {
        touchWaitTime = LONG_WAIT; // return to normal delays between touch events
        screenResyncLights(); // show that we are working

        // setup eeprom rgbw variables
        int e1, e2, e3, e4, e5, e6;
        // holding bytes to rescale 0-4095 values to bytes for saving
        byte v1, v2, v3, v4, v5, v6;

        // save current light mode
        if (currentLightMode==0)
        {
          e1=400; // eeprom location to save M1 red
          e2=401; // eeprom location to save M1 green
          e3=402; // eeprom location to save M1 blue
          e4=403; // eeprom location to save M1 cool white
          e5=404;
          e6=405;
          if (lightCSP==true) irsend.sendNEC(M1,32); // save values to position 1 on lights
          //if (lightCSP==true) irsend.sendNEC(0xFFFFFFFF,32); // start sending footer to save
        }
        else if (currentLightMode==1)
        {
          e1=410; // eeprom location to save M2 red
          e2=411; // eeprom location to save M2 green
          e3=412; // eeprom location to save M2 blue
          e4=413; // eeprom location to save M2 cool white
          e5=414;
          e6=415;
          if (lightCSP==true) irsend.sendNEC(M2,32); // save values to position 2 on lights
          //if (lightCSP==true) irsend.sendNEC(0xFFFFFFFF,32); //  start sending footer to save
        }
        else if (currentLightMode==2)
        {
          e1=420; // eeprom location to save M3 red
          e2=421; // eeprom location to save M3 green
          e3=422; // eeprom location to save M3 blue
          e4=423; // eeprom location to save M3 cool white
          e5=424;
          e6=425;
          if (lightCSP==true) irsend.sendNEC(M3,32); // save values to position 3 on lights
          //if (lightCSP==true) irsend.sendNEC(0xFFFFFFFF,32); //  start sending footer to save
        }
        else if (currentLightMode==3)
        {
          e1=430; // eeprom location to save M4 red
          e2=431; // eeprom location to save M4 green
          e3=432; // eeprom location to save M4 blue
          e4=433; // eeprom location to save M4 cool white
          e5=434;
          e6=435;
          if (lightCSP==true) irsend.sendNEC(M4,32); // save values to position 4 on lights
          //if (lightCSP==true) irsend.sendNEC(0xFFFFFFFF,32); //  start sending footer to save
        }
        if (lightCSP==true) 
        {
          // blast the footer for 3 seconds to save the memory position in the light
          unsigned long currentMillis = millis(); // get current millis
          unsigned long blastMillis = millis(); // get current millis
          while ((blastMillis-currentMillis)<3000)
          {
            irsend.sendNEC(0xFFFFFFFF,32); // blast footer to save
            blastMillis = millis(); // get current millis
          }
        }
        Serial.print(F("LED values before saving: \n"));
        Serial.print(F("currentColor.chan1: "));
        Serial.println(currentColor.chan1);
        Serial.print(F("currentColor.chan2: "));
        Serial.println(currentColor.chan2);
        Serial.print(F("currentColor.chan3: "));
        Serial.println(currentColor.chan3);
        Serial.print(F("currentColor.chan4: "));
        Serial.println(currentColor.chan4);
        Serial.print(F("currentColor.chan5: "));
        Serial.println(currentColor.chan5);
        Serial.print(F("currentColor.chan6: "));
        Serial.println(currentColor.chan6);
        Serial.print(F("currentLightMode: "));
        Serial.println(currentLightMode);
        
        //if not using IR light then currentColor needs to be scaled down to 0-100
        if(lightCSP == false)
        {
          if(PCA9685Installed == true)
          {
            v1 = map(currentColor.chan1,0,4095,0,100);
            v2 = map(currentColor.chan2,0,4095,0,100);
            v3 = map(currentColor.chan3,0,4095,0,100);
            v4 = map(currentColor.chan4,0,4095,0,100);
            v5 = map(currentColor.chan5,0,4095,0,100);
            v6 = map(currentColor.chan6,0,4095,0,100);
          }else
          {
            v1 = map(currentColor.chan1,0,255,0,100);
            v2 = map(currentColor.chan2,0,255,0,100);
            v3 = map(currentColor.chan3,0,255,0,100);
            v4 = map(currentColor.chan4,0,255,0,100);
            v5 = map(currentColor.chan5,0,255,0,100);
            v6 = map(currentColor.chan6,0,255,0,100);
          }
        }
        else
        {
          v1 = currentColor.chan1;
          v2 = currentColor.chan2;
          v3 = currentColor.chan3;
          v4 = currentColor.chan4;
          v5 = 0;
          v6 = 0;
        }
        // save new values to eeprom locations
        EEPROM.write(e1,v1);
        EEPROM.write(e2,v2);
        EEPROM.write(e3,v3);
        EEPROM.write(e4,v4);
        EEPROM.write(e5,v5);
        EEPROM.write(e6,v6);

        lightEditing = 0; // disable editing
        int prevMode = currentLightMode; // keep track of what mode we are in
        resyncLights(); // we resync the lights after saving
        currentLightMode = prevMode; // return to the saved mode 

        // switch back to the lighting mode you saved
        if (lightCSP==true) 
        {
          if (currentLightMode==0) irsend.sendNEC(M1,32); // activate the mode you just saved
          else if (currentLightMode==1) irsend.sendNEC(M2,32); // activate the mode you just saved
          else if (currentLightMode==2) irsend.sendNEC(M3,32); // activate the mode you just saved
          else if (currentLightMode==3) irsend.sendNEC(M4,32); // activate the mode you just saved
          //irsend.sendNEC(0xFFFFFFFF,32); // send footer
        }
        setStartupLighting();
        screenLights(); // redraw the screen
      }
      else if ((x>=124)&&(x<=172)&&(y>=101)&&(y<=149))      //  cancel button
      {
        lightEditing=0;
        touchWaitTime = LONG_WAIT;
        // switch back to current light mode
        if (currentLightMode==0) 
        {
          currentColor=lightHighSun;
          if (lightCSP==true) irsend.sendNEC(M1,32);
        }
        else if (currentLightMode==1) 
        {
          currentColor=lightMidSun;
          if (lightCSP==true) irsend.sendNEC(M2,32);
        }
        else if (currentLightMode==2) 
        {
          currentColor=lightLowSun;
          if (lightCSP==true) irsend.sendNEC(M3,32);
        }
        else if (currentLightMode==3) 
        {
          currentColor=lightMoon;
          if (lightCSP==true) irsend.sendNEC(M4,32);
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
          } else //otherwise scale to 8-bit
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
        screenLights(); // redraw screen
      }
      else if ((x>=10)&&(x<=38)&&(y>=185)&&(y<=285))    //  red bargraph
      {
        dy = 285-y;
        drawLEDBarGraph(1,dy);
        if(PCA9685Installed == true)currentColor.chan1 = map(dy, 0, 100, 0, 4095);
        if(PCA9685Installed == false)currentColor.chan1 = map(dy, 0, 100, 0, 255);
        writeToLED(1,currentColor.chan1);
      }
      else if ((x>=48)&&(x<=76)&&(y>=185)&&(y<=285))    //  Green bargraph
      {
        dy = 285-y;
        drawLEDBarGraph(2,dy);
        if(PCA9685Installed == true)currentColor.chan2 = map(dy, 0, 100, 0, 4095);
        if(PCA9685Installed == false)currentColor.chan2 = map(dy, 0, 100, 0, 255);
        writeToLED(2,currentColor.chan2);
      }
      else if ((x>=86)&&(x<=114)&&(y>=185)&&(y<=285))      //  blue bargraph
      {
        dy = 285-y;
        drawLEDBarGraph(3,dy);
        if(PCA9685Installed == true)currentColor.chan3 = map(dy, 0, 100, 0, 4095);
        if(PCA9685Installed == false)currentColor.chan3 = map(dy, 0, 100, 0, 255);
        writeToLED(3,currentColor.chan3);
      }
      else if ((x>=124)&&(x<=152)&&(y>=185)&&(y<=285))   // white bargraph
      {
        dy = 285-y; //dy will be between 0 and 100
        drawLEDBarGraph(4,dy); //update bargraph with new value
        if(PCA9685Installed == true)currentColor.chan4 = map(dy, 0, 100, 0, 4095);
        if(PCA9685Installed == false)currentColor.chan4 = map(dy, 0, 100, 0, 255);
        writeToLED(4,currentColor.chan4);
      }
      else if ((x>=162)&&(x<=190)&&(y>=185)&&(y<=285))   // warm white bargraph
      {
        dy = 285-y;
        drawLEDBarGraph(5,dy);
        if(PCA9685Installed == true)currentColor.chan5 = map(dy, 0, 100, 0, 4095);
        if(PCA9685Installed == false)currentColor.chan5 = map(dy, 0, 100, 0, 255);
        writeToLED(5,currentColor.chan5);
      }
      else if ((x>=200)&&(x<=228)&&(y>=185)&&(y<=285))   // Ultra violet bargraph
      {
        dy = 285-y;
        drawLEDBarGraph(6,dy);
        if(PCA9685Installed == true)currentColor.chan6 = map(dy, 0, 100, 0, 4095);
        if(PCA9685Installed == false)currentColor.chan6 = map(dy, 0, 100, 0, 255);
        writeToLED(6,currentColor.chan6);
      }
    }

    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button 
    {
      touchWaitTime = LONG_WAIT;
      //determine which light mode we should return to before leaving lighting screen
      smartStartupRamp();
      setStartupLighting();
      screenSettings();
    }

    break;

  case 6:    // clock screen for setting time

    myGLCD.setFont(arial_bold);
    myGLCD.setColor(255, 77, 0);
    touchWaitTime = MEDIUM_WAIT;

    if ((x>=12)&&(x<=96)&&(y>=286)&&(y<=312))  // cancel button  
    {     
      screenSettings();
    }
    else if ((x>=144)&&(x<=228)&&(y>=286)&&(y<=312))  // save button  
    {     
      SaveTime();
      screenSettings();
    }
    else if ((x>=12)&&(x<=36)&&(y>=89)&&(y<=113))  // hour up button
    {     
      saveRTC.Hour=(saveRTC.Hour+1);
      if (saveRTC.Hour>23) saveRTC.Hour=0;
      itoa(saveRTC.Hour, char3, 10);
      if (saveRTC.Hour>=0 && saveRTC.Hour<=9) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 45, 108);
    }
    else if ((x>=12)&&(x<=36)&&(y>=119)&&(y<=143))  // hour down button  
    {     
      saveRTC.Hour=(saveRTC.Hour-1);
      if (saveRTC.Hour>23) saveRTC.Hour=23;
      itoa(saveRTC.Hour, char3, 10);
      if (saveRTC.Hour>=0 && saveRTC.Hour<=9) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 45, 108);
    }
    else if ((x>=83)&&(x<=107)&&(y>=89)&&(y<=113))  // min up button  
    {     
      saveRTC.Minute=(saveRTC.Minute+1);
      if (saveRTC.Minute>59) saveRTC.Minute=0;
      itoa(saveRTC.Minute, char3, 10);
      if (saveRTC.Minute>=0 && saveRTC.Minute<=9) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 123, 108);

    }
    else if ((x>=83)&&(x<=107)&&(y>=119)&&(y<=143))  // min down button  
    {     
      saveRTC.Minute=(saveRTC.Minute-1);
      if (saveRTC.Minute>59) saveRTC.Minute=59;
      itoa(saveRTC.Minute, char3, 10);
      if (saveRTC.Minute>=0 && saveRTC.Minute<=9) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 123, 108);
    }
    else if ((x>=164)&&(x<=188)&&(y>=89)&&(y<=113))  // sec up button  
    {     
      saveRTC.Second=(saveRTC.Second+1);
      if (saveRTC.Second>59) saveRTC.Second=0;
      itoa(saveRTC.Second, char3, 10);
      if (saveRTC.Second>=0 && saveRTC.Second<=9) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 201, 108);

    }
    else if ((x>=164)&&(x<=188)&&(y>=119)&&(y<=143))  // sec down button  
    {     
      saveRTC.Second=(saveRTC.Second-1);
      if (saveRTC.Second>59) saveRTC.Second=59;
      itoa(saveRTC.Second, char3, 10);
      if (saveRTC.Second>=0 && saveRTC.Second<=9) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 201, 108);
    }

    else if ((x>=12)&&(x<=36)&&(y>=211)&&(y<=235))  // month up button  
    {     
      saveRTC.Month=(saveRTC.Month+1);
      if (saveRTC.Month>12) saveRTC.Month=1;
      itoa(saveRTC.Month, char3, 10);
      if (saveRTC.Month>=0 && saveRTC.Month<=9) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 45, 230);

    }
    else if ((x>=12)&&(x<=36)&&(y>=241)&&(y<=265))  // month down button  
    {     
      saveRTC.Month=(saveRTC.Month-1);
      if (saveRTC.Month<1) saveRTC.Month=12;
      itoa(saveRTC.Month, char3, 10);
      if (saveRTC.Month>=0 && saveRTC.Month<=9) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 45, 230);
    }
    else if ((x>=83)&&(x<=107)&&(y>=211)&&(y<=235))  // day up button  
    {     
      saveRTC.Day=(saveRTC.Day+1);
      if (saveRTC.Day>31) saveRTC.Day=1;
      itoa(saveRTC.Day, char3, 10);
      if (saveRTC.Day>=0 && saveRTC.Day<=9) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 123, 230);

    }
    else if ((x>=83)&&(x<=107)&&(y>=241)&&(y<=265))  // day down button  
    {     
      saveRTC.Day=(saveRTC.Day-1);
      if (saveRTC.Day<1) saveRTC.Day=31;
      itoa(saveRTC.Day, char3, 10);
      if (saveRTC.Day>=0 && saveRTC.Day<=9) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 123, 230);
    }
    else if ((x>=164)&&(x<=188)&&(y>=211)&&(y<=235))  // year up button  
    {     
      saveRTC.Year=(saveRTC.Year+1);
      if (saveRTC.Year>129) saveRTC.Year=30; // 30 == 2000, 130 == 2100
      itoa((saveRTC.Year-30), char3, 10);
      if (saveRTC.Year>=30 && saveRTC.Year<=39) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 201, 230);

    }
    else if ((x>=164)&&(x<=188)&&(y>=241)&&(y<=265))  // year down button  
    {     
      saveRTC.Year=(saveRTC.Year-1);
      if (saveRTC.Year<30) saveRTC.Year=129;
      itoa((saveRTC.Year-30), char3, 10);
      if (saveRTC.Year>=30 && saveRTC.Year<=39) // add a zero
      {
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 201, 230);
    }

    break;

  case 7:    // feeding schedule screen

    if ((x>=158)&&(x<=182)&&(y>=46)&&(y<=70)) // minutes up button 
    {
      feedingMins=feedingMins+1;
      EEPROM.write(7,feedingMins);
      itoa(feedingMins, char3, 10);
      if (feedingMins>=0 && feedingMins<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.setFont(arial_bold);
      myGLCD.setColor(255, 77, 0);
      myGLCD.print(char3, 190, 65);
    }
    else if ((x>=158)&&(x<=182)&&(y>=76)&&(y<=100))  // minutes down
    {
      if (feedingMins>1) // don't increment lower than 1 minute
      {
        feedingMins=feedingMins-1;
        EEPROM.write(7,feedingMins);
        itoa(feedingMins, char3, 10);
        if (feedingMins>=0 && feedingMins<=9) // add a zero
        {
          //itoa(0, char3t, 10); //make char3t 0
          strcat(char3t, char3);
          strcpy (char3,char3t);
        }
        myGLCD.setFont(arial_bold);
        myGLCD.setColor(255, 77, 0);
        myGLCD.print(char3, 190, 65);
      }
    }
    else if ((x>=41)&&(x<=89)&&(y>=140)&&(y<=188))  // pwrHeatIcon  
    {
      // toggle to opposite power setting
      if (feedPower.pwrHeat==0) feedPower.pwrHeat=1;
      else if (feedPower.pwrHeat==1) feedPower.pwrHeat=0;
      // save to memory
      EEPROM.write(12, feedPower.pwrHeat);
      // update icons
      myFiles.load(41, 140, 48, 48, pwrHeatIcon[feedPower.pwrHeat],2);
    }
    else if ((x>=96)&&(x<=144)&&(y>=140)&&(y<=188))  // pwrFilterIcon  
    {
      // toggle to opposite power setting
      if (feedPower.pwrFilter==0) feedPower.pwrFilter=1;
      else if (feedPower.pwrFilter==1) feedPower.pwrFilter=0;
      // save to memory
      EEPROM.write(10, feedPower.pwrFilter);
      // update icons
      myFiles.load(96, 140, 48, 48, pwrFilterIcon[feedPower.pwrFilter],2);
    }
    else if ((x>=150)&&(x<=198)&&(y>=140)&&(y<=188))  // pwrCircIcon  
    {
      // toggle to opposite power setting
      if (feedPower.pwrCirc==0) feedPower.pwrCirc=1;
      else if (feedPower.pwrCirc==1) feedPower.pwrCirc=0;
      // save to memory
      EEPROM.write(11, feedPower.pwrCirc);
      // update icons
      myFiles.load(150, 140, 48, 48, pwrCircIcon[feedPower.pwrCirc],2);
    }
    else if ((x>=41)&&(x<=89)&&(y>=220)&&(y<=268))  // pwrCO2Icon  
    {
      // toggle to opposite power setting
      if (feedPower.pwrCO2==0) feedPower.pwrCO2=1;
      else if (feedPower.pwrCO2==1) feedPower.pwrCO2=0;
      // save to memory
      EEPROM.write(13, feedPower.pwrCO2);
      // update icons
      myFiles.load(41, 220, 48, 48, pwrCO2Icon[feedPower.pwrCO2],2);
    }
    else if ((x>=96)&&(x<=144)&&(y>=220)&&(y<=268))  // pwrAux1Icon  
    {
      // toggle to opposite power setting
      if (feedPower.pwrAux1==0) feedPower.pwrAux1=1;
      else if (feedPower.pwrAux1==1) feedPower.pwrAux1=0;
      // save to memory
      EEPROM.write(14, feedPower.pwrAux1);
      // update icons
      myFiles.load(96, 220, 48, 48, pwrAux1Icon[feedPower.pwrAux1],2);
    }
    else if ((x>=150)&&(x<=198)&&(y>=220)&&(y<=268))  // pwrAux2Icon  
    {
      // toggle to opposite power setting
      if (feedPower.pwrAux2==0) feedPower.pwrAux2=1;
      else if (feedPower.pwrAux2==1) feedPower.pwrAux2=0;
      // save to memory
      EEPROM.write(15, feedPower.pwrAux2);
      // update icons
      myFiles.load(150, 220, 48, 48, pwrAux2Icon[feedPower.pwrAux2],2);
    }
    else if ((x>=42)&&(x<=88)&&(y>=189)&&(y<=211))  // Enable heat feed setting
    {
      // toggle to opposite power setting
      if (feedSetting.pwrHeat==0) feedSetting.pwrHeat=1;
      else if (feedSetting.pwrHeat==1) feedSetting.pwrHeat=0;
      // save to memory
      EEPROM.write(3, feedSetting.pwrHeat);
      // update icons
      myFiles.load(42, 189, 46, 22, schedOnOff[feedSetting.pwrHeat],2);
    }
    else if ((x>=97)&&(x<=143)&&(y>=189)&&(y<=211))  // Enable filter feed setting
    {
      // toggle to opposite power setting
      if (feedSetting.pwrFilter==0) feedSetting.pwrFilter=1;
      else if (feedSetting.pwrFilter==1) feedSetting.pwrFilter=0;
      // save to memory
      EEPROM.write(1, feedSetting.pwrFilter);
      // update icons
      myFiles.load(97, 189, 46, 22, schedOnOff[feedSetting.pwrFilter],2);
    }
    else if ((x>=151)&&(x<=197)&&(y>=189)&&(y<=211))  // Enable circ feed setting
    {
      // toggle to opposite power setting
      if (feedSetting.pwrCirc==0) feedSetting.pwrCirc=1;
      else if (feedSetting.pwrCirc==1) feedSetting.pwrCirc=0;
      // save to memory
      EEPROM.write(2, feedSetting.pwrCirc);
      // update icons
      myFiles.load(151, 189, 46, 22, schedOnOff[feedSetting.pwrCirc],2);
    }
    else if ((x>=42)&&(x<=88)&&(y>=269)&&(y<=291))  // Enable CO2 feed setting
    {
      // toggle to opposite power setting
      if (feedSetting.pwrCO2==0) feedSetting.pwrCO2=1;
      else if (feedSetting.pwrCO2==1) feedSetting.pwrCO2=0;
      // save to memory
      EEPROM.write(4, feedSetting.pwrCO2);
      // update icons
      myFiles.load(42, 269, 46, 22, schedOnOff[feedSetting.pwrCO2],2);
    }
    else if ((x>=97)&&(x<=143)&&(y>=269)&&(y<=291))  // Enable Aux1 feed setting
    {
      // toggle to opposite power setting
      if (feedSetting.pwrAux1==0) feedSetting.pwrAux1=1;
      else if (feedSetting.pwrAux1==1) feedSetting.pwrAux1=0;
      // save to memory
      EEPROM.write(5, feedSetting.pwrAux1);
      // update icons
      myFiles.load(97, 269, 46, 22, schedOnOff[feedSetting.pwrAux1],2);
    }
    else if ((x>=151)&&(x<=197)&&(y>=269)&&(y<=291))  // Enable Aux2 feed setting
    {
      // toggle to opposite power setting
      if (feedSetting.pwrAux2==0) feedSetting.pwrAux2=1;
      else if (feedSetting.pwrAux2==1) feedSetting.pwrAux2=0;
      // save to memory
      EEPROM.write(6, feedSetting.pwrAux2);
      // update icons
      myFiles.load(151, 269, 46, 22, schedOnOff[feedSetting.pwrAux2],2);
    }
    else if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button  
    {
      EEPROM.write(6,1);
      // exit screen
      screenSettings();
    }

    break;

  case 8:    // heater settings screen

    myGLCD.setColor(255, 77, 0);
    myGLCD.setFont(arial_bold);
    touchWaitTime = MEDIUM_WAIT;

    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button  
    {
      screenSensors();
    }
    else if ((x>=162)&&(x<=186)&&(y>=37)&&(y<=61))  // off up button  
    {
      heatOffTemp=EEPROM.read(17); // read existing setting
      heatOffTemp=heatOffTemp+1; // increment
      itoa(heatOffTemp, char3, 10);
      myGLCD.print(char3, 194, 56);
      EEPROM.write(17,heatOffTemp); // save setting
    }
    else if ((x>=162)&&(x<=186)&&(y>=67)&&(y<=91))  // off down button  
    {
      heatOffTemp=EEPROM.read(17); // read existing setting
      heatOffTemp=heatOffTemp-1; // increment
      itoa(heatOffTemp, char3, 10);
      myGLCD.print(char3, 194, 56);
      EEPROM.write(17,heatOffTemp); // save setting
    }
    else if ((x>=162)&&(x<=186)&&(y>=103)&&(y<=127))  // on up button  
    {
      heatOnTemp=EEPROM.read(18); // read existing setting
      heatOnTemp=heatOnTemp+1; // increment
      itoa(heatOnTemp, char3, 10);
      myGLCD.print(char3, 194, 122);
      EEPROM.write(18,heatOnTemp); // save setting
    }
    else if ((x>=162)&&(x<=186)&&(y>=133)&&(y<=157))  // on down button  
    {
      heatOnTemp=EEPROM.read(18); // read existing setting
      heatOnTemp=heatOnTemp-1; // increment
      itoa(heatOnTemp, char3, 10);
      myGLCD.print(char3, 194, 122);
      EEPROM.write(18,heatOnTemp); // save setting
    }
    else if ((x>=136)&&(x<=160)&&(y>=169)&&(y<=193))  // offset up button  
    {
      byte storedVal = EEPROM.read(58);
      byte dx = 176;
      if(storedVal < 227)
      {
        storedVal++;
        EEPROM.write(58,storedVal);
        if(storedVal < 128)dx = 160;
        sensor1Calibration = ((float)storedVal - 128) / 10;
        dtostrf(sensor1Calibration, 3, 1, char6);  //convert to string
        myGLCD.print(char6, dx, 188);
        if(displayInC == true) myFiles.load(226, 190, 14, 12, "c.raw",2);
        if(displayInC == false)myFiles.load(226, 190, 14, 12, "f.raw",2);
        myGLCD.setColor(VGA_BLACK);
        if(storedVal >= 128)myGLCD.fillRect(160,188,176,204);//erase negative sign
      }
    }
    else if ((x>=136)&&(x<=160)&&(y>=199)&&(y<=223))  // offset down button  
    {
      byte storedVal = EEPROM.read(58);
      byte dx = 176;
      if(storedVal > 29)
      {
        storedVal--;
        EEPROM.write(58,storedVal);
        if(storedVal < 128)dx = 160;
        sensor1Calibration = ((float)storedVal - 128) / 10;
        dtostrf(sensor1Calibration, 3, 1, char6);  //convert to string
        myGLCD.print(char6, dx, 188);
        if(displayInC == true) myFiles.load(226, 190, 14, 12, "c.raw",2);
        if(displayInC == false)myFiles.load(226, 190, 14, 12, "f.raw",2);
      }
    }
    else if ((x>=162)&&(x<=208)&&(y>=251)&&(y<=273))  // enable display of sensor
    {
      displaySensor1 = EEPROM.read(61);
      if(displaySensor1)
      {
        displaySensor1 = false;
        EEPROM.write(61,0);
      }else
      {
        displaySensor1 = true;
        EEPROM.write(61,1);
      }
      //myFiles.load(170, 247, 30, 30, schedActiveB[displaySensor1],2);
      myFiles.load(162, 251, 46, 22, schedOnOff[displaySensor1],2);
    }
    break;

  case 9:    // schedule screen

    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // home button  
    {
      updateAlarms(); // this will rebuild all of the schedules
      screenSettings();
    }
    else if ((x>=10)&&(x<=58)&&(y>=50)&&(y<=113))
    {
      screenPwrSchedule();
    }
    else if ((x>=67)&&(x<=115)&&(y>=50)&&(y<=113))
    {
      screenDosingSched(1); // send 1 to start with Macro pump
    }
    else if ((x>=124)&&(x<=172)&&(y>=50)&&(y<=113))
    {
      screenLightRamps();
    }

    break;

  case 10:    // dosing configuration screen
    // scheduleItem 1 = macros
    // scheduleItem 2 = micros
    // scheduleItem 3 = excel
    touchWaitTime = LONG_WAIT;
    int doseCap;
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // schedule button  
    {
      screenSettings();
    }
    else if ((x>=12)&&(x<=58)&&(y>=39)&&(y<=87))  // macros button  
    {
      if (scheduleItem!=1) screenDosing(1); // switch to macros schedule
    }
    else if ((x>=70)&&(x<=116)&&(y>=39)&&(y<=87))  // micros button  
    {
      if (scheduleItem!=2) screenDosing(2); // switch to micros schedule
    }
    else if ((x>=128)&&(x<=174)&&(y>=39)&&(y<=87))  // excel button  
    {
      if (scheduleItem!=3) screenDosing(3); // switch to excel schedule
    }
    else if ((x>=145)&&(x<=169)&&(y>=101)&&(y<=125))   // dose up
    {
      touchWaitTime = MEDIUM_WAIT;
      byte doseAmt;
      if (scheduleItem==1)
      {
        doseAmt=EEPROM.read(20); // 20 // pump1 dose in mL
      }
      else if (scheduleItem==2)
      {
        doseAmt=EEPROM.read(21); // 21 // pump2 dose in mL
      }
      else if (scheduleItem==3)
      {
        doseAmt=EEPROM.read(22); // 22 // pump3 dose in mL
      }
      if (doseAmt < 255)doseAmt=doseAmt+1;  // increment up by one
      itoa(doseAmt, char3, 10);
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(arial_bold);
      if (doseAmt>=0 && doseAmt<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 175, 121); // display dose size
      if (scheduleItem==1)
      {
        EEPROM.write(20,doseAmt);  // save to memory
      }
      else if (scheduleItem==2)
      {
        EEPROM.write(21,doseAmt);  // save to memory
      }
      else if (scheduleItem==3)
      {
        EEPROM.write(22,doseAmt);  // save to memory
      }
    }
    else if ((x>=145)&&(x<=169)&&(y>=131)&&(y<=155))   // dose down
    {
      touchWaitTime = MEDIUM_WAIT;
      byte doseAmt;
      if (scheduleItem==1)
      {
        doseAmt=EEPROM.read(20); // 20 // pump1 dose in mL
      }
      else if (scheduleItem==2)
      {
        doseAmt=EEPROM.read(21); // 21 // pump2 dose in mL
      }
      else if (scheduleItem==3)
      {
        doseAmt=EEPROM.read(22); // 22 // pump3 dose in mL
      }
      if (doseAmt > 1) doseAmt=doseAmt-1;  // increment up by one
      itoa(doseAmt, char3, 10);
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(arial_bold);
      if (doseAmt>=0 && doseAmt<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 175, 121); // display dose size
      if (scheduleItem==1)
      {
        EEPROM.write(20,doseAmt);  // save to memory
      }
      else if (scheduleItem==2)
      {
        EEPROM.write(21,doseAmt);  // save to memory
      }
      else if (scheduleItem==3)
      {
        EEPROM.write(22,doseAmt);  // save to memory
      }
    }
    else if ((x>=145)&&(x<=169)&&(y>=167)&&(y<=191))   // pump sec increased by .1 (technically 10 since it's 10th power)
    {
      touchWaitTime = MEDIUM_WAIT;
      int pumpSpeed;
      if (scheduleItem==1)
      {
        pumpSpeed=EEPROM.read(23); // 23 // pump 1 sec/ml
      }
      else if (scheduleItem==2)
      {
        pumpSpeed=EEPROM.read(24); // 24 // pump 2 sec/ml
      }
      else if (scheduleItem==3)
      {
        pumpSpeed=EEPROM.read(25); // 25 // pump 3 sec/ml
      }
      if (pumpSpeed < 255) pumpSpeed=(pumpSpeed+1);  // increment up by 1
      if (scheduleItem==1)
      {
        EEPROM.write(23,pumpSpeed);  // save to memory
      }
      else if (scheduleItem==2)
      {
        EEPROM.write(24,pumpSpeed);  // save to memory
      }
      else if (scheduleItem==3)
      {
        EEPROM.write(25,pumpSpeed);  // save to memory
      }
      pumpSpeed=(pumpSpeed*10);  // convert to power of 10 to get actual ms
      itoa(pumpSpeed, char6, 10);
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(arial_bold);
      myGLCD.print(char6, 175, 186);
    }
    else if ((x>=145)&&(x<=169)&&(y>=197)&&(y<=221))   // pump sec decreased by .1 (technically 10 since it's 10th power)
    {
      touchWaitTime = MEDIUM_WAIT;
      int pumpSpeed;
      if (scheduleItem==1)
      {
        pumpSpeed=EEPROM.read(23); // 23 // pump 1 sec/ml
      }
      else if (scheduleItem==2)
      {
        pumpSpeed=EEPROM.read(24); // 24 // pump 2 sec/ml
      }
      else if (scheduleItem==3)
      {
        pumpSpeed=EEPROM.read(25); // 25 // pump 3 sec/ml
      }
      if (pumpSpeed > 1) pumpSpeed=(pumpSpeed-1);  // increment up by 1
      if (scheduleItem==1)
      {
        EEPROM.write(23,pumpSpeed);  // save to memory
      }
      else if (scheduleItem==2)
      {
        EEPROM.write(24,pumpSpeed);  // save to memory
      }
      else if (scheduleItem==3)
      {
        EEPROM.write(25,pumpSpeed);  // save to memory
      }
      pumpSpeed=(pumpSpeed*10);  // convert to power of 10 to get actual ms
      itoa(pumpSpeed, char6, 10);
      myGLCD.setColor(0,0,0);
      myGLCD.fillRect(175,197,239,213); // clear previous value
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(arial_bold);
      myGLCD.print(char6, 175, 186);
    }
    else if ((x>=92)&&(x<=140)&&(y>=170)&&(y<=218))   // pump test button
    {
      touchWaitTime = LONG_WAIT;
      //int pumpTime;
      //int doseAmt;
      myFiles.load(92, 170, 48, 48, "10test2.raw"); 
      if (scheduleItem==1)
      {
        AlarmMacros();
      }
      else if (scheduleItem==2)
      {
        AlarmMicros();
      }
      else if (scheduleItem==3)
      {
        AlarmExcel();
      }
    }
    else if ((x>=145)&&(x<=169)&&(y>=233)&&(y<=257))   // resevoir volume up by 10
    {
      touchWaitTime = MEDIUM_WAIT;
      if (scheduleItem==1)
      {
        doseCap=EEPROM.read(26); // 26 // dosing 1 resevior capacity in mL;
      }
      else if (scheduleItem==2)
      {
        doseCap=EEPROM.read(261); // 27 // dosing 2 resevior capacity in mL;
      }
      else if (scheduleItem==3)
      {
        doseCap=EEPROM.read(263); // 280 // dosing 3 resevior capacity in mL;
      }

      if (doseCap < 255) doseCap=(doseCap+1);  // increment up by 10
      if (scheduleItem==1)
      {
        EEPROM.write(26,doseCap); // 26 // dosing 1 resevior capacity in mL;
      }
      else if (scheduleItem==2)
      {
        EEPROM.write(261,doseCap); // 27 // dosing 2 resevior capacity in mL;
      }
      else if (scheduleItem==3)
      {
        EEPROM.write(263,doseCap); // 280 // dosing 3 resevior capacity in mL;
      }
      // EEPROM.write(26,doseCap); // save new value
      doseCap=(doseCap*10);  // convert to power of 10 to get actual mL
      itoa(doseCap, char6, 10);
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(arial_bold);
      myGLCD.print(char6, 175, 252);
      //Should add check here to make sure remaining volumes max out at new full volume
    }
    else if ((x>=145)&&(x<=169)&&(y>=263)&&(y<=287))   // resevoir volume down by 10
    {
      touchWaitTime = MEDIUM_WAIT;
      if (scheduleItem==1)
      {
        doseCap=EEPROM.read(26); // 26 // dosing 1 resevior capacity in mL;
      }
      else if (scheduleItem==2)
      {
        doseCap=EEPROM.read(261); // 27 // dosing 2 resevior capacity in mL;
      }
      else if (scheduleItem==3)
      {
        doseCap=EEPROM.read(263); // 280 // dosing 3 resevior capacity in mL;
      }

      // int doseCap=EEPROM.read(26); // 22 // dosing reseviors capacity in mL;
      if (doseCap > 1) doseCap=(doseCap-1);  // decrease by 1
      if (scheduleItem==1)
      {
        EEPROM.write(26,doseCap); // 26 // dosing 1 resevior capacity in mL;
      }
      else if (scheduleItem==2)
      {
        EEPROM.write(261,doseCap); // 27 // dosing 2 resevior capacity in mL;
      }
      else if (scheduleItem==3)
      {
        EEPROM.write(263,doseCap); // 280 // dosing 3 resevior capacity in mL;
      }
      //EEPROM.write(26,doseCap); // save new value
      doseCap=(doseCap*10);  // convert to power of 10 to get actual mL
      itoa(doseCap, char6, 10);
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(arial_bold);
      myGLCD.print(char6, 175, 252);
    }
    else if ((x>=92)&&(x<=140)&&(y>=236)&&(y<=284))   // fill reservoir
    {
      touchWaitTime = LONG_WAIT;
      int doseCapacity;
      //reload test icon so it's clear from screen it was pressed
      myGLCD.setColor(VGA_BLACK);
      myGLCD.fillRect(92,242,140,293);
      myFiles.load(92, 236, 48, 48, "10fill.raw");
      //int doseCapacity=EEPROM.read(26); // 26 // dosing reseviors capacity in mL*10;
      if (scheduleItem==1)
      {
        doseCapacity=EEPROM.read(26); // 26 // dosing 1 resevior capacity in mL*10;
        EEPROM.write(32,doseCapacity);
        EEPROM.write(33,0);
      }
      else if (scheduleItem==2)
      {
        doseCapacity=EEPROM.read(261); // 27 // dosing 2 resevior capacity in mL*10;
        EEPROM.write(34,doseCapacity);
        EEPROM.write(35,0);
      }
      else if (scheduleItem==3)
      {
        doseCapacity=EEPROM.read(263); // 280 // dosing 3 resevior capacity in mL*10;
        EEPROM.write(36,doseCapacity);
        EEPROM.write(37,0);
      }
    }
    
    break;

  case 11:    // power schedule screen

    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // schedule button  
    {     
      screenSchedule();
    }
    else if ((x>=0)&&(x<=185)&&(y>=85)&&(y<=110)) // Light 1
    {
      screenPwrScheduleItem(1);
    }
    else if ((x>=0)&&(x<=185)&&(y>=111)&&(y<=135)) // Light 1 Schedule 2
    {
      screenPwrScheduleItem(10);
    }
    else if ((x>=0)&&(x<=185)&&(y>=136)&&(y<=160))  // Light 2 Schedule 1
    {
      screenPwrScheduleItem(2);
    }
    else if ((x>=0)&&(x<=185)&&(y>=161)&&(y<=185)) // Light 2 Schedule 2
    {
      screenPwrScheduleItem(11);
    }
    else if ((x>=0)&&(x<=185)&&(y>=186)&&(y<=210))  // Circ
    {
      screenPwrScheduleItem(3);
    }
    else if ((x>=0)&&(x<=185)&&(y>=211)&&(y<=235))  // CO2
    {
      screenPwrScheduleItem(4);
    }
    else if ((x>=0)&&(x<=185)&&(y>=236)&&(y<=260))  // Aux 1
    {
      screenPwrAuxItem(5);
    }
    else if ((x>=0)&&(x<=185)&&(y>=261)&&(y<=285))  // Aux2
    {
      screenPwrAuxItem(6);
    }

    break;

  case 12:    // power item schedule screen

    myGLCD.setFont(arial_bold);
    myGLCD.setColor(255, 77, 0);
    touchWaitTime = MEDIUM_WAIT;
    
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // schedule button  
    {     
      screenPwrSchedule();
    }
    else if ((x>=83)&&(x<=107)&&(y>=94)&&(y<=118)) // on hour up
    {
      int onHour;
      if (scheduleItem==1)
      {
        if (schedLights1.onHour==23) schedLights1.onHour=0;
        else schedLights1.onHour=schedLights1.onHour+1;
        onHour=schedLights1.onHour;
        EEPROM.write(101,onHour); // save to memory
      }
      else if (scheduleItem==10)
      {
        if (schedLights1s2.onHour==23) schedLights1s2.onHour=0;
        else schedLights1s2.onHour=schedLights1s2.onHour+1;
        onHour=schedLights1s2.onHour;
        EEPROM.write(131,onHour); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (schedLights2.onHour==23) schedLights2.onHour=0;
        else schedLights2.onHour=schedLights2.onHour+1;
        onHour=schedLights2.onHour;
        EEPROM.write(106,onHour); // save to memory
      }
      else if (scheduleItem==11)
      {
        if (schedLights2s2.onHour==23) schedLights2s2.onHour=0;
        else schedLights2s2.onHour=schedLights2s2.onHour+1;
        onHour=schedLights2s2.onHour;
        EEPROM.write(136,onHour); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (schedCirc.onHour==23) schedCirc.onHour=0;
        else schedCirc.onHour=schedCirc.onHour+1;
        onHour=schedCirc.onHour;
        EEPROM.write(111,onHour); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (schedCo2.onHour==23) schedCo2.onHour=0;
        else schedCo2.onHour=schedCo2.onHour+1;
        onHour=schedCo2.onHour;
        EEPROM.write(116,onHour); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (schedAux1.onHour==23) schedAux1.onHour=0;
        else schedAux1.onHour=schedAux1.onHour+1;
        onHour=schedAux1.onHour;
        EEPROM.write(121,onHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.onHour==23) schedAux2.onHour=0;
        else schedAux2.onHour=schedAux2.onHour+1;
        onHour=schedAux2.onHour;
        EEPROM.write(126,onHour); // save to memory
      }

      // print to screen
      itoa(onHour, char3, 10);
      if (onHour>=0 && onHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 123, 113);

    }
    else if ((x>=83)&&(x<=107)&&(y>=124)&&(y<=148)) // on hour down
    {
      int onHour;
      if (scheduleItem==1)
      {
        if (schedLights1.onHour==0) schedLights1.onHour=23;
        else schedLights1.onHour=schedLights1.onHour-1;
        onHour=schedLights1.onHour;
        EEPROM.write(101,onHour); // save to memory
      }
      else if (scheduleItem==10)
      {
        if (schedLights1s2.onHour==0) schedLights1s2.onHour=23;
        else schedLights1s2.onHour=schedLights1s2.onHour-1;
        onHour=schedLights1s2.onHour;
        EEPROM.write(131,onHour); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (schedLights2.onHour==0) schedLights2.onHour=23;
        else schedLights2.onHour=schedLights2.onHour-1;
        onHour=schedLights2.onHour;
        EEPROM.write(106,onHour); // save to memory
      }
      else if (scheduleItem==11)
      {
        if (schedLights2s2.onHour==0) schedLights2s2.onHour=23;
        else schedLights2s2.onHour=schedLights2s2.onHour-1;
        onHour=schedLights2s2.onHour;
        EEPROM.write(136,onHour); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (schedCirc.onHour==0) schedCirc.onHour=23;
        else schedCirc.onHour=schedCirc.onHour-1;
        onHour=schedCirc.onHour;
        EEPROM.write(111,onHour); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (schedCo2.onHour==0) schedCo2.onHour=23;
        else schedCo2.onHour=schedCo2.onHour-1;
        onHour=schedCo2.onHour;
        EEPROM.write(116,onHour); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (schedAux1.onHour==0) schedAux1.onHour=23;
        else schedAux1.onHour=schedAux1.onHour-1;
        onHour=schedAux1.onHour;
        EEPROM.write(121,onHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.onHour==0) schedAux2.onHour=23;
        else schedAux2.onHour=schedAux2.onHour-1;
        onHour=schedAux2.onHour;
        EEPROM.write(126,onHour); // save to memory
      }

      // print to screen
      itoa(onHour, char3, 10);
      if (onHour>=0 && onHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 123, 113);

    }
    else if ((x>=164)&&(x<=188)&&(y>=94)&&(y<=118)) // on min up
    {
      int onMinute;
      if (scheduleItem==1)
      {
        if (schedLights1.onMinute==59) schedLights1.onMinute=0;
        else schedLights1.onMinute=schedLights1.onMinute+1;
        onMinute=schedLights1.onMinute;
        EEPROM.write(102,onMinute); // save to memory
      }
      else if (scheduleItem==10)
      {
        if (schedLights1s2.onMinute==59) schedLights1s2.onMinute=0;
        else schedLights1s2.onMinute=schedLights1s2.onMinute+1;
        onMinute=schedLights1s2.onMinute;
        EEPROM.write(132,onMinute); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (schedLights2.onMinute==59) schedLights2.onMinute=0;
        else schedLights2.onMinute=schedLights2.onMinute+1;
        onMinute=schedLights2.onMinute;
        EEPROM.write(107,onMinute); // save to memory
      }
      else if (scheduleItem==11)
      {
        if (schedLights2s2.onMinute==59) schedLights2s2.onMinute=0;
        else schedLights2s2.onMinute=schedLights2s2.onMinute+1;
        onMinute=schedLights2s2.onMinute;
        EEPROM.write(137,onMinute); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (schedCirc.onMinute==59) schedCirc.onMinute=0;
        else schedCirc.onMinute=schedCirc.onMinute+1;
        onMinute=schedCirc.onMinute;
        EEPROM.write(112,onMinute); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (schedCo2.onMinute==59) schedCo2.onMinute=0;
        else schedCo2.onMinute=schedCo2.onMinute+1;
        onMinute=schedCo2.onMinute;
        EEPROM.write(117,onMinute); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (schedAux1.onMinute==59) schedAux1.onMinute=0;
        else schedAux1.onMinute=schedAux1.onMinute+1;
        onMinute=schedAux1.onMinute;
        EEPROM.write(122,onMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.onMinute==59) schedAux2.onMinute=0;
        else schedAux2.onMinute=schedAux2.onMinute+1;
        onMinute=schedAux2.onMinute;
        EEPROM.write(127,onMinute); // save to memory
      }

      // print to screen
      itoa(onMinute, char3, 10);
      if (onMinute>=0 && onMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 201, 113);

    }
    else if ((x>=164)&&(x<=188)&&(y>=124)&&(y<=148)) // on min down
    {
      int onMinute;
      if (scheduleItem==1)
      {
        if (schedLights1.onMinute==0) schedLights1.onMinute=59;
        else schedLights1.onMinute=schedLights1.onMinute-1;
        onMinute=schedLights1.onMinute;
        EEPROM.write(102,onMinute); // save to memory
      }
      else if (scheduleItem==10)
      {
        if (schedLights1s2.onMinute==0) schedLights1s2.onMinute=59;
        else schedLights1s2.onMinute=schedLights1s2.onMinute-1;
        onMinute=schedLights1s2.onMinute;
        EEPROM.write(132,onMinute); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (schedLights2.onMinute==0) schedLights2.onMinute=59;
        else schedLights2.onMinute=schedLights2.onMinute-1;
        onMinute=schedLights2.onMinute;
        EEPROM.write(107,onMinute); // save to memory
      }
      else if (scheduleItem==11)
      {
        if (schedLights2s2.onMinute==0) schedLights2s2.onMinute=59;
        else schedLights2s2.onMinute=schedLights2s2.onMinute-1;
        onMinute=schedLights2s2.onMinute;
        EEPROM.write(137,onMinute); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (schedCirc.onMinute==0) schedCirc.onMinute=59;
        else schedCirc.onMinute=schedCirc.onMinute-1;
        onMinute=schedCirc.onMinute;
        EEPROM.write(112,onMinute); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (schedCo2.onMinute==0) schedCo2.onMinute=59;
        else schedCo2.onMinute=schedCo2.onMinute-1;
        onMinute=schedCo2.onMinute;
        EEPROM.write(117,onMinute); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (schedAux1.onMinute==0) schedAux1.onMinute=59;
        else schedAux1.onMinute=schedAux1.onMinute-1;
        onMinute=schedAux1.onMinute;
        EEPROM.write(122,onMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.onMinute==0) schedAux2.onMinute=59;
        else schedAux2.onMinute=schedAux2.onMinute-1;
        onMinute=schedAux2.onMinute;
        EEPROM.write(127,onMinute); // save to memory
      }

      // print to screen
      itoa(onMinute, char3, 10);
      if (onMinute>=0 && onMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 201, 113);

    }
    else if ((x>=83)&&(x<=107)&&(y>=175)&&(y<=199)) // off hour up
    {
      int offHour;
      if (scheduleItem==1)
      {
        if (schedLights1.offHour==23) schedLights1.offHour=0;
        else schedLights1.offHour=schedLights1.offHour+1;
        offHour=schedLights1.offHour;
        EEPROM.write(103,offHour); // save to memory
      }
      else if (scheduleItem==10)
      {
        if (schedLights1s2.offHour==23) schedLights1s2.offHour=0;
        else schedLights1s2.offHour=schedLights1s2.offHour+1;
        offHour=schedLights1s2.offHour;
        EEPROM.write(133,offHour); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (schedLights2.offHour==23) schedLights2.offHour=0;
        else schedLights2.offHour=schedLights2.offHour+1;
        offHour=schedLights2.offHour;
        EEPROM.write(108,offHour); // save to memory
      }
      else if (scheduleItem==11)
      {
        if (schedLights2s2.offHour==23) schedLights2s2.offHour=0;
        else schedLights2s2.offHour=schedLights2s2.offHour+1;
        offHour=schedLights2s2.offHour;
        EEPROM.write(138,offHour); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (schedCirc.offHour==23) schedCirc.offHour=0;
        else schedCirc.offHour=schedCirc.offHour+1;
        offHour=schedCirc.offHour;
        EEPROM.write(113,offHour); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (schedCo2.offHour==23) schedCo2.offHour=0;
        else schedCo2.offHour=schedCo2.offHour+1;
        offHour=schedCo2.offHour;
        EEPROM.write(118,offHour); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (schedAux1.offHour==23) schedAux1.offHour=0;
        else schedAux1.offHour=schedAux1.offHour+1;
        offHour=schedAux1.offHour;
        EEPROM.write(123,offHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.offHour==23) schedAux2.offHour=0;
        else schedAux2.offHour=schedAux2.offHour+1;
        offHour=schedAux2.offHour;
        EEPROM.write(128,offHour); // save to memory
      }

      // print to screen
      itoa(offHour, char3, 10);
      if (offHour>=0 && offHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 123, 194);            
    }
    else if ((x>=83)&&(x<=107)&&(y>=205)&&(y<=229)) // off hour down
    {
      int offHour;
      if (scheduleItem==1)
      {
        if (schedLights1.offHour==0) schedLights1.offHour=23;
        else schedLights1.offHour=schedLights1.offHour-1;
        offHour=schedLights1.offHour;
        EEPROM.write(103,offHour); // save to memory
      }
      else if (scheduleItem==10)
      {
        if (schedLights1s2.offHour==0) schedLights1s2.offHour=23;
        else schedLights1s2.offHour=schedLights1s2.offHour-1;
        offHour=schedLights1s2.offHour;
        EEPROM.write(133,offHour); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (schedLights2.offHour==0) schedLights2.offHour=23;
        else schedLights2.offHour=schedLights2.offHour-1;
        offHour=schedLights2.offHour;
        EEPROM.write(108,offHour); // save to memory
      }
      else if (scheduleItem==11)
      {
        if (schedLights2s2.offHour==0) schedLights2s2.offHour=23;
        else schedLights2s2.offHour=schedLights2s2.offHour-1;
        offHour=schedLights2s2.offHour;
        EEPROM.write(138,offHour); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (schedCirc.offHour==0) schedCirc.offHour=23;
        else schedCirc.offHour=schedCirc.offHour-1;
        offHour=schedCirc.offHour;
        EEPROM.write(113,offHour); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (schedCo2.offHour==0) schedCo2.offHour=23;
        else schedCo2.offHour=schedCo2.offHour-1;
        offHour=schedCo2.offHour;
        EEPROM.write(118,offHour); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (schedAux1.offHour==0) schedAux1.offHour=23;
        else schedAux1.offHour=schedAux1.offHour-1;
        offHour=schedAux1.offHour;
        EEPROM.write(123,offHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.offHour==0) schedAux2.offHour=23;
        else schedAux2.offHour=schedAux2.offHour-1;
        offHour=schedAux2.offHour;
        EEPROM.write(128,offHour); // save to memory
      }

      // print to screen
      itoa(offHour, char3, 10);
      if (offHour>=0 && offHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 123, 194);               
    }
    else if ((x>=164)&&(x<=188)&&(y>=175)&&(y<=199)) // off min up
    {
      int offMinute;
      if (scheduleItem==1)
      {
        if (schedLights1.offMinute==59) schedLights1.offMinute=0;
        else schedLights1.offMinute=schedLights1.offMinute+1;
        offMinute=schedLights1.offMinute;
        EEPROM.write(104,offMinute); // save to memory
      }
      else if (scheduleItem==10)
      {
        if (schedLights1s2.offMinute==59) schedLights1s2.offMinute=0;
        else schedLights1s2.offMinute=schedLights1s2.offMinute+1;
        offMinute=schedLights1s2.offMinute;
        EEPROM.write(134,offMinute); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (schedLights2.offMinute==59) schedLights2.offMinute=0;
        else schedLights2.offMinute=schedLights2.offMinute+1;
        offMinute=schedLights2.offMinute;
        EEPROM.write(109,offMinute); // save to memory
      }
      else if (scheduleItem==11)
      {
        if (schedLights2s2.offMinute==59) schedLights2s2.offMinute=0;
        else schedLights2s2.offMinute=schedLights2s2.offMinute+1;
        offMinute=schedLights2s2.offMinute;
        EEPROM.write(139,offMinute); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (schedCirc.offMinute==59) schedCirc.offMinute=0;
        else schedCirc.offMinute=schedCirc.offMinute+1;
        offMinute=schedCirc.offMinute;
        EEPROM.write(114,offMinute); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (schedCo2.offMinute==59) schedCo2.offMinute=0;
        else schedCo2.offMinute=schedCo2.offMinute+1;
        offMinute=schedCo2.offMinute;
        EEPROM.write(119,offMinute); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (schedAux1.offMinute==59) schedAux1.offMinute=0;
        else schedAux1.offMinute=schedAux1.offMinute+1;
        offMinute=schedAux1.offMinute;
        EEPROM.write(124,offMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.offMinute==59) schedAux2.offMinute=0;
        else schedAux2.offMinute=schedAux2.offMinute+1;
        offMinute=schedAux2.offMinute;
        EEPROM.write(129,offMinute); // save to memory
      }

      // print to screen
      itoa(offMinute, char3, 10);
      if (offMinute>=0 && offMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 201, 194);

    }
    else if ((x>=164)&&(x<=188)&&(y>=205)&&(y<=229)) // off min down
    {
      int offMinute;
      if (scheduleItem==1)
      {
        if (schedLights1.offMinute==0) schedLights1.offMinute=59;
        else schedLights1.offMinute=schedLights1.offMinute-1;
        offMinute=schedLights1.offMinute;
        EEPROM.write(104,offMinute); // save to memory
      }
      else if (scheduleItem==10)
      {
        if (schedLights1s2.offMinute==0) schedLights1s2.offMinute=59;
        else schedLights1s2.offMinute=schedLights1s2.offMinute-1;
        offMinute=schedLights1s2.offMinute;
        EEPROM.write(134,offMinute); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (schedLights2.offMinute==0) schedLights2.offMinute=59;
        else schedLights2.offMinute=schedLights2.offMinute-1;
        offMinute=schedLights2.offMinute;
        EEPROM.write(109,offMinute); // save to memory
      }
      else if (scheduleItem==11)
      {
        if (schedLights2s2.offMinute==0) schedLights2s2.offMinute=59;
        else schedLights2s2.offMinute=schedLights2s2.offMinute-1;
        offMinute=schedLights2s2.offMinute;
        EEPROM.write(139,offMinute); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (schedCirc.offMinute==0) schedCirc.offMinute=59;
        else schedCirc.offMinute=schedCirc.offMinute-1;
        offMinute=schedCirc.offMinute;
        EEPROM.write(114,offMinute); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (schedCo2.offMinute==0) schedCo2.offMinute=59;
        else schedCo2.offMinute=schedCo2.offMinute-1;
        offMinute=schedCo2.offMinute;
        EEPROM.write(119,offMinute); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (schedAux1.offMinute==0) schedAux1.offMinute=59;
        else schedAux1.offMinute=schedAux1.offMinute-1;
        offMinute=schedAux1.offMinute;
        EEPROM.write(124,offMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.offMinute==0) schedAux2.offMinute=59;
        else schedAux2.offMinute=schedAux2.offMinute-1;
        offMinute=schedAux2.offMinute;
        EEPROM.write(129,offMinute); // save to memory
      }

      // print to screen
      itoa(offMinute, char3, 10);
      if (offMinute>=0 && offMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 201, 194);

    }
    else if ((x>=162)&&(x<=208)&&(y>=253)&&(y<=275)) // active button
    {
      touchWaitTime = LONG_WAIT;
      int isActive;
      if (scheduleItem==1)
      {
        if (schedLights1.active==1) schedLights1.active=0;
        else schedLights1.active=1;
        isActive=schedLights1.active;
        EEPROM.write(100,isActive); // save to memory
      }
      if (scheduleItem==10)
      {
        if (schedLights1s2.active==1) schedLights1s2.active=0;
        else schedLights1s2.active=1;
        isActive=schedLights1s2.active;
        EEPROM.write(130,isActive); // save to memory
      }
      if (scheduleItem==2)
      {
        if (schedLights2.active==1) schedLights2.active=0;
        else schedLights2.active=1;
        isActive=schedLights2.active;
        EEPROM.write(105,isActive); // save to memory
      }
      if (scheduleItem==11)
      {
        if (schedLights2s2.active==1) schedLights2s2.active=0;
        else schedLights2s2.active=1;
        isActive=schedLights2s2.active;
        EEPROM.write(135,isActive); // save to memory
      }
      if (scheduleItem==3)
      {
        if (schedCirc.active==1) schedCirc.active=0;
        else schedCirc.active=1;
        isActive=schedCirc.active;
        EEPROM.write(110,isActive); // save to memory
      }
      if (scheduleItem==4)
      {
        if (schedCo2.active==1) schedCo2.active=0;
        else schedCo2.active=1;
        isActive=schedCo2.active;
        EEPROM.write(115,isActive); // save to memory
      }
      if (scheduleItem==5)
      {
        if (schedAux1.active==1) schedAux1.active=0;
        else schedAux1.active=1;
        isActive=schedAux1.active;
        EEPROM.write(120,isActive); // save to memory
      }
      if (scheduleItem==6)
      {
        if (schedAux2.active==1) schedAux2.active=0;
        else schedAux2.active=1;
        isActive=schedAux2.active;
        EEPROM.write(125,isActive); // save to memory
      }

      //myFiles.load(161, 249, 30, 30, schedActiveB[isActive]);
      myFiles.load(162, 253, 46, 22, schedOnOff[isActive],2);
    }

    break;

  case 13:    // light ramp schedule screen

    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // schedule button  
    {     
      screenSchedule();
    }
    else if ((x>=0)&&(x<=185)&&(y>=100)&&(y<=125)) 
    {     
      screenLightRampItem(1);
    }
    else if ((x>=0)&&(x<=185)&&(y>=126)&&(y<=151))
    {
      screenLightRampItem(2);
    }
    else if ((x>=0)&&(x<=185)&&(y>=152)&&(y<=177))
    {
      screenLightRampItem(3);
    }
    else if ((x>=0)&&(x<=185)&&(y>=178)&&(y<=203))
    {
      screenLightRampItem(4);
    }
    else if ((x>=0)&&(x<=185)&&(y>=204)&&(y<=229))
    {
      screenLightRampItem(5);
    }
    else if ((x>=0)&&(x<=185)&&(y>=230)&&(y<=255))
    {
      screenLightRampItem(6);
    }

    break;

  case 14:    // light ramp schedule screen

    myGLCD.setFont(arial_bold);
    myGLCD.setColor(255, 77, 0);
    touchWaitTime = MEDIUM_WAIT;
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // schedule button  
    {
      screenLightRamps();
    }
    else if ((x>=75)&&(x<=99)&&(y>=120)&&(y<=144)) // on hour up
    {
      int onHour;
      if (scheduleItem==1)
      {
        if (ramp1.onHour==23) ramp1.onHour=0;
        else ramp1.onHour=ramp1.onHour+1;
        onHour=ramp1.onHour;
        EEPROM.write(220,onHour); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (ramp2.onHour==23) ramp2.onHour=0;
        else ramp2.onHour=ramp2.onHour+1;
        onHour=ramp2.onHour;
        EEPROM.write(224,onHour); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (ramp3.onHour==23) ramp3.onHour=0;
        else ramp3.onHour=ramp3.onHour+1;
        onHour=ramp3.onHour;
        EEPROM.write(228,onHour); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (ramp4.onHour==23) ramp4.onHour=0;
        else ramp4.onHour=ramp4.onHour+1;
        onHour=ramp4.onHour;
        EEPROM.write(232,onHour); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (ramp5.onHour==23) ramp5.onHour=0;
        else ramp5.onHour=ramp5.onHour+1;
        onHour=ramp5.onHour;
        EEPROM.write(236,onHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (ramp6.onHour==23) ramp6.onHour=0;
        else ramp6.onHour=ramp6.onHour+1;
        onHour=ramp6.onHour;
        EEPROM.write(240,onHour); // save to memory
      }

      // print to screen
      itoa(onHour, char3, 10);
      if (onHour>=0 && onHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 110, 139);

    }
    else if ((x>=75)&&(x<=99)&&(y>=150)&&(y<=174)) // on hour down
    {
      int onHour;
      if (scheduleItem==1)
      {
        if (ramp1.onHour==0) ramp1.onHour=23;
        else ramp1.onHour=ramp1.onHour-1;
        onHour=ramp1.onHour;
        EEPROM.write(220,onHour); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (ramp2.onHour==0) ramp2.onHour=23;
        else ramp2.onHour=ramp2.onHour-1;
        onHour=ramp2.onHour;
        EEPROM.write(224,onHour); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (ramp3.onHour==0) ramp3.onHour=23;
        else ramp3.onHour=ramp3.onHour-1;
        onHour=ramp3.onHour;
        EEPROM.write(228,onHour); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (ramp4.onHour==0) ramp4.onHour=23;
        else ramp4.onHour=ramp4.onHour-1;
        onHour=ramp4.onHour;
        EEPROM.write(232,onHour); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (ramp5.onHour==0) ramp5.onHour=23;
        else ramp5.onHour=ramp5.onHour-1;
        onHour=ramp5.onHour;
        EEPROM.write(236,onHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (ramp6.onHour==0) ramp6.onHour=23;
        else ramp6.onHour=ramp6.onHour-1;
        onHour=ramp6.onHour;
        EEPROM.write(240,onHour); // save to memory
      }

      // print to screen
      itoa(onHour, char3, 10);
      if (onHour>=0 && onHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 110, 139);

    }
    else if ((x>=154)&&(x<=178)&&(y>=120)&&(y<=144)) // on min up
    {
      int onMinute;
      if (scheduleItem==1)
      {
        if (ramp1.onMinute==59) ramp1.onMinute=0;
        else ramp1.onMinute=ramp1.onMinute+1;
        onMinute=ramp1.onMinute;
        EEPROM.write(221,onMinute); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (ramp2.onMinute==59) ramp2.onMinute=0;
        else ramp2.onMinute=ramp2.onMinute+1;
        onMinute=ramp2.onMinute;
        EEPROM.write(225,onMinute); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (ramp3.onMinute==59) ramp3.onMinute=0;
        else ramp3.onMinute=ramp3.onMinute+1;
        onMinute=ramp3.onMinute;
        EEPROM.write(229,onMinute); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (ramp4.onMinute==59) ramp4.onMinute=0;
        else ramp4.onMinute=ramp4.onMinute+1;
        onMinute=ramp4.onMinute;
        EEPROM.write(233,onMinute); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (ramp5.onMinute==59) ramp5.onMinute=0;
        else ramp5.onMinute=ramp5.onMinute+1;
        onMinute=ramp5.onMinute;
        EEPROM.write(237,onMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (ramp6.onMinute==59) ramp6.onMinute=0;
        else ramp6.onMinute=ramp6.onMinute+1;
        onMinute=ramp6.onMinute;
        EEPROM.write(241,onMinute); // save to memory
      }

      // print to screen
      itoa(onMinute, char3, 10);
      if (onMinute>=0 && onMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 189, 139);

    }
    else if ((x>=154)&&(x<=178)&&(y>=150)&&(y<=174)) // on min down
    {
      int onMinute;
      if (scheduleItem==1)
      {
        if (ramp1.onMinute==0) ramp1.onMinute=59;
        else ramp1.onMinute=ramp1.onMinute-1;
        onMinute=ramp1.onMinute;
        EEPROM.write(221,onMinute); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (ramp2.onMinute==0) ramp2.onMinute=59;
        else ramp2.onMinute=ramp2.onMinute-1;
        onMinute=ramp2.onMinute;
        EEPROM.write(225,onMinute); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (ramp3.onMinute==0) ramp3.onMinute=59;
        else ramp3.onMinute=ramp3.onMinute-1;
        onMinute=ramp3.onMinute;
        EEPROM.write(229,onMinute); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (ramp4.onMinute==0) ramp4.onMinute=59;
        else ramp4.onMinute=ramp4.onMinute-1;
        onMinute=ramp4.onMinute;
        EEPROM.write(233,onMinute); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (ramp5.onMinute==0) ramp5.onMinute=59;
        else ramp5.onMinute=ramp5.onMinute-1;
        onMinute=ramp5.onMinute;
        EEPROM.write(237,onMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (ramp6.onMinute==0) ramp6.onMinute=59;
        else ramp6.onMinute=ramp6.onMinute-1;
        onMinute=ramp6.onMinute;
        EEPROM.write(241,onMinute); // save to memory
      }

      // print to screen
      itoa(onMinute, char3, 10);
      if (onMinute>=0 && onMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 189, 139);

    }
    else if ((x>=75)&&(x<=99)&&(y>=231)&&(y<=255)) // off hour up
    {
      int offHour;
      if (scheduleItem==1)
      {
        if (ramp1.offHour==23) ramp1.offHour=0;
        else ramp1.offHour=ramp1.offHour+1;
        offHour=ramp1.offHour;
        EEPROM.write(222,offHour); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (ramp2.offHour==23) ramp2.offHour=0;
        else ramp2.offHour=ramp2.offHour+1;
        offHour=ramp2.offHour;
        EEPROM.write(226,offHour); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (ramp3.offHour==23) ramp3.offHour=0;
        else ramp3.offHour=ramp3.offHour+1;
        offHour=ramp3.offHour;
        EEPROM.write(230,offHour); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (ramp4.offHour==23) ramp4.offHour=0;
        else ramp4.offHour=ramp4.offHour+1;
        offHour=ramp4.offHour;
        EEPROM.write(234,offHour); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (ramp5.offHour==23) ramp5.offHour=0;
        else ramp5.offHour=ramp5.offHour+1;
        offHour=ramp5.offHour;
        EEPROM.write(238,offHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (ramp6.offHour==23) ramp6.offHour=0;
        else ramp6.offHour=ramp6.offHour+1;
        offHour=ramp6.offHour;
        EEPROM.write(242,offHour); // save to memory
      }

      // print to screen
      itoa(offHour, char3, 10);
      if (offHour>=0 && offHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 110, 250);
    }
    else if ((x>=75)&&(x<=99)&&(y>=261)&&(y<=285)) // off hour down
    {
      int offHour;
      if (scheduleItem==1)
      {
        if (ramp1.offHour==0) ramp1.offHour=23;
        else ramp1.offHour=ramp1.offHour-1;
        offHour=ramp1.offHour;
        EEPROM.write(222,offHour); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (ramp2.offHour==0) ramp2.offHour=23;
        else ramp2.offHour=ramp2.offHour-1;
        offHour=ramp2.offHour;
        EEPROM.write(226,offHour); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (ramp3.offHour==0) ramp3.offHour=23;
        else ramp3.offHour=ramp3.offHour-1;
        offHour=ramp3.offHour;
        EEPROM.write(230,offHour); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (ramp4.offHour==0) ramp4.offHour=23;
        else ramp4.offHour=ramp4.offHour-1;
        offHour=ramp4.offHour;
        EEPROM.write(234,offHour); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (ramp5.offHour==0) ramp5.offHour=23;
        else ramp5.offHour=ramp5.offHour-1;
        offHour=ramp5.offHour;
        EEPROM.write(238,offHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (ramp6.offHour==0) ramp6.offHour=23;
        else ramp6.offHour=ramp6.offHour-1;
        offHour=ramp6.offHour;
        EEPROM.write(242,offHour); // save to memory
      }

      // print to screen
      itoa(offHour, char3, 10);
      if (offHour>=0 && offHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 110, 250);
    }
    else if ((x>=154)&&(x<=178)&&(y>=231)&&(y<=255)) // off min up
    {
      int offMinute;
      if (scheduleItem==1)
      {
        if (ramp1.offMinute==59) ramp1.offMinute=0;
        else ramp1.offMinute=ramp1.offMinute+1;
        offMinute=ramp1.offMinute;
        EEPROM.write(223,offMinute); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (ramp2.offMinute==59) ramp2.offMinute=0;
        else ramp2.offMinute=ramp2.offMinute+1;
        offMinute=ramp2.offMinute;
        EEPROM.write(227,offMinute); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (ramp3.offMinute==59) ramp3.offMinute=0;
        else ramp3.offMinute=ramp3.offMinute+1;
        offMinute=ramp3.offMinute;
        EEPROM.write(231,offMinute); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (ramp4.offMinute==59) ramp4.offMinute=0;
        else ramp4.offMinute=ramp4.offMinute+1;
        offMinute=ramp4.offMinute;
        EEPROM.write(235,offMinute); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (ramp5.offMinute==59) ramp5.offMinute=0;
        else ramp5.offMinute=ramp5.offMinute+1;
        offMinute=ramp5.offMinute;
        EEPROM.write(239,offMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (ramp6.offMinute==59) ramp6.offMinute=0;
        else ramp6.offMinute=ramp6.offMinute+1;
        offMinute=ramp6.offMinute;
        EEPROM.write(243,offMinute); // save to memory
      }

      // print to screen
      itoa(offMinute, char3, 10);
      if (offMinute>=0 && offMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 189, 250);

    }
    else if ((x>=154)&&(x<=178)&&(y>=261)&&(y<=285)) // off min down
    {
      int offMinute;
      if (scheduleItem==1)
      {
        if (ramp1.offMinute==0) ramp1.offMinute=59;
        else ramp1.offMinute=ramp1.offMinute-1;
        offMinute=ramp1.offMinute;
        EEPROM.write(223,offMinute); // save to memory
      }
      else if (scheduleItem==2)
      {
        if (ramp2.offMinute==0) ramp2.offMinute=59;
        else ramp2.offMinute=ramp2.offMinute-1;
        offMinute=ramp2.offMinute;
        EEPROM.write(227,offMinute); // save to memory
      }
      else if (scheduleItem==3)
      {
        if (ramp3.offMinute==0) ramp3.offMinute=59;
        else ramp3.offMinute=ramp3.offMinute-1;
        offMinute=ramp3.offMinute;
        EEPROM.write(231,offMinute); // save to memory
      }
      else if (scheduleItem==4)
      {
        if (ramp4.offMinute==0) ramp4.offMinute=59;
        else ramp4.offMinute=ramp4.offMinute-1;
        offMinute=ramp4.offMinute;
        EEPROM.write(235,offMinute); // save to memory
      }
      else if (scheduleItem==5)
      {
        if (ramp5.offMinute==0) ramp5.offMinute=59;
        else ramp5.offMinute=ramp5.offMinute-1;
        offMinute=ramp5.offMinute;
        EEPROM.write(239,offMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (ramp6.offMinute==0) ramp6.offMinute=59;
        else ramp6.offMinute=ramp6.offMinute-1;
        offMinute=ramp6.offMinute;
        EEPROM.write(243,offMinute); // save to memory
      }

      // print to screen
      itoa(offMinute, char3, 10);
      if (offMinute>=0 && offMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 189, 250);

    }
    break;

  case 15:  // macro and micro dosing schedule

    // scheduleItem 1 = macros
    // scheduleItem 2 = micros
    // scheduleItem 3 = excel
    myGLCD.setFont(arial_bold);

    // set font color based on micros or macros
    if (scheduleItem==1) myGLCD.setColor(34, 81, 255);
    if (scheduleItem==2) myGLCD.setColor(255, 77, 0);
    if (scheduleItem==3) myGLCD.setColor(34, 255, 77);

    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // schedule button  
    {     
      screenSchedule();
    }
    else if ((x>=12)&&(x<=58)&&(y>=61)&&(y<=109))  // macros button  
    {     
      if (scheduleItem!=1) screenDosingSched(1); // switch to macros schedule
    }
    else if ((x>=12)&&(x<=58)&&(y>=110)&&(y<=158))  // micros button  
    {     
      if (scheduleItem!=2) screenDosingSched(2); // switch to micros schedule
    }
    else if ((x>=12)&&(x<=58)&&(y>=159)&&(y<=207))  // excel button  
    {     
      if (scheduleItem!=3) screenDosingSched(3); // switch to excel schedule
    }
    else if ((x>=85)&&(x<=109)&&(y>=110)&&(y<=134)) // on hour up
    {
      int onHour;
      if (scheduleItem==1) // for Macros
      {
        if (pump1.onHour==23) pump1.onHour=0;
        else pump1.onHour=pump1.onHour+1;
        onHour=pump1.onHour;
        EEPROM.write(300,onHour); // save to memory
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.onHour==23) pump2.onHour=0;
        else pump2.onHour=pump2.onHour+1;
        onHour=pump2.onHour;
        EEPROM.write(309,onHour); // save to memory
      }
      else if (scheduleItem==3) // for Excel
      {
        if (pump3.onHour==23) pump3.onHour=0;
        else pump3.onHour=pump3.onHour+1;
        onHour=pump3.onHour;
        EEPROM.write(318,onHour); // save to memory
      }
      // print to screen
      itoa(onHour, char3, 10);
      if (onHour>=0 && onHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 120, 129);

    }
    else if ((x>=85)&&(x<=109)&&(y>=140)&&(y<=164)) // on hour down
    {
      int onHour;
      if (scheduleItem==1) // for Macros
      {
        if (pump1.onHour==0) pump1.onHour=23;
        else pump1.onHour=pump1.onHour-1;
        onHour=pump1.onHour;
        EEPROM.write(300,onHour); // save to memory
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.onHour==0) pump2.onHour=23;
        else pump2.onHour=pump2.onHour-1;
        onHour=pump2.onHour;
        EEPROM.write(309,onHour); // save to memory
      }
      else if (scheduleItem==3) // for Excel
      {
        if (pump3.onHour==0) pump3.onHour=23;
        else pump3.onHour=pump3.onHour-1;
        onHour=pump3.onHour;
        EEPROM.write(318,onHour); // save to memory
      }
      // print to screen
      itoa(onHour, char3, 10);
      if (onHour>=0 && onHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 120, 129);         
    } 

    else if ((x>=164)&&(x<=188)&&(y>=110)&&(y<=134)) // on min up
    {
      int onMinute;
      if (scheduleItem==1) // for Macros
      {
        if (pump1.onMinute==59) pump1.onMinute=0;
        else pump1.onMinute=pump1.onMinute+1;
        onMinute=pump1.onMinute;
        EEPROM.write(301,onMinute); // save to memory
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.onMinute==59) pump2.onMinute=0;
        else pump2.onMinute=pump2.onMinute+1;
        onMinute=pump2.onMinute;
        EEPROM.write(310,onMinute); // save to memory
      }
      else if (scheduleItem==3) // for Micros
      {
        if (pump3.onMinute==59) pump3.onMinute=0;
        else pump3.onMinute=pump3.onMinute+1;
        onMinute=pump3.onMinute;
        EEPROM.write(319,onMinute); // save to memory
      }
      // print to screen
      itoa(onMinute, char3, 10);
      if (onMinute>=0 && onMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 199, 129);
    }
    else if ((x>=164)&&(x<=188)&&(y>=140)&&(y<=164)) // on min down
    {
      int onMinute;
      if (scheduleItem==1) // for Macros
      {
        if (pump1.onMinute==0) pump1.onMinute=59;
        else pump1.onMinute=pump1.onMinute-1;
        onMinute=pump1.onMinute;
        EEPROM.write(301,onMinute); // save to memory
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.onMinute==0) pump2.onMinute=59;
        else pump2.onMinute=pump2.onMinute-1;
        onMinute=pump2.onMinute;
        EEPROM.write(310,onMinute); // save to memory
      }
      else if (scheduleItem==3) // for Excel
      {
        if (pump3.onMinute==0) pump3.onMinute=59;
        else pump3.onMinute=pump3.onMinute-1;
        onMinute=pump3.onMinute;
        EEPROM.write(319,onMinute); // save to memory
      }
      // print to screen
      itoa(onMinute, char3, 10);
      if (onMinute>=0 && onMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 199, 129);
    }
    else if ((x>=51)&&(x<=81)&&(y>=214)&&(y<=244)) // dose on Sunday
    {
      if (scheduleItem==1) // for Macros
      {
        if (pump1.Sunday==1) pump1.Sunday=0;
        else pump1.Sunday=1;
        EEPROM.write(302,pump1.Sunday); // save to memory
        myFiles.load(51, 214, 30, 30, schedActiveB[pump1.Sunday]); 
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.Sunday==1) pump2.Sunday=0;
        else pump2.Sunday=1;
        EEPROM.write(311,pump2.Sunday); // save to memory
        myFiles.load(51, 214, 30, 30, schedActiveB[pump2.Sunday]); 
      }
      else if (scheduleItem==3) // for Excel
      {
        if (pump3.Sunday==1) pump3.Sunday=0;
        else pump3.Sunday=1;
        EEPROM.write(320,pump3.Sunday); // save to memory
        myFiles.load(51, 214, 30, 30, schedActiveB[pump3.Sunday]); 
      }
    }
    else if ((x>=105)&&(x<=135)&&(y>=214)&&(y<=244)) // dose on Monday
    {
      if (scheduleItem==1) // for Macros
      {
        if (pump1.Monday==1) pump1.Monday=0;
        else pump1.Monday=1;
        EEPROM.write(303,pump1.Monday); // save to memory
        myFiles.load(105, 214, 30, 30, schedActiveB[pump1.Monday]); 
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.Monday==1) pump2.Monday=0;
        else pump2.Monday=1;
        EEPROM.write(312,pump2.Monday); // save to memory
        myFiles.load(105, 214, 30, 30, schedActiveB[pump2.Monday]); 
      }
      else if (scheduleItem==3) // for Excel
      {
        if (pump3.Monday==1) pump3.Monday=0;
        else pump3.Monday=1;
        EEPROM.write(321,pump3.Monday); // save to memory
        myFiles.load(105, 214, 30, 30, schedActiveB[pump3.Monday]); 
      }
    }
    else if ((x>=159)&&(x<=189)&&(y>=214)&&(y<=244)) // dose on Tuesday
    {
      if (scheduleItem==1) // for Macros
      {
        if (pump1.Tuesday==1) pump1.Tuesday=0;
        else pump1.Tuesday=1;
        EEPROM.write(304,pump1.Tuesday); // save to memory
        myFiles.load(159, 214, 30, 30, schedActiveB[pump1.Tuesday]); 
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.Tuesday==1) pump2.Tuesday=0;
        else pump2.Tuesday=1;
        EEPROM.write(313,pump2.Tuesday); // save to memory
        myFiles.load(159, 214, 30, 30, schedActiveB[pump2.Tuesday]); 
      }
      else if (scheduleItem==3) // for Excel
      {
        if (pump3.Tuesday==1) pump3.Tuesday=0;
        else pump3.Tuesday=1;
        EEPROM.write(322,pump3.Tuesday); // save to memory
        myFiles.load(159, 214, 30, 30, schedActiveB[pump3.Tuesday]); 
      }
    }
    else if ((x>=30)&&(x<=60)&&(y>=261)&&(y<=291)) // dose on Wednesday
    {
      if (scheduleItem==1) // for Macros
      {
        if (pump1.Wednesday==1) pump1.Wednesday=0;
        else pump1.Wednesday=1;
        EEPROM.write(305,pump1.Wednesday); // save to memory
        myFiles.load(30, 261, 30, 30, schedActiveB[pump1.Wednesday]); 
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.Wednesday==1) pump2.Wednesday=0;
        else pump2.Wednesday=1;
        EEPROM.write(314,pump2.Wednesday); // save to memory
        myFiles.load(30, 261, 30, 30, schedActiveB[pump2.Wednesday]); 
      }
      else if (scheduleItem==3) // for Excel
      {
        if (pump3.Wednesday==1) pump3.Wednesday=0;
        else pump3.Wednesday=1;
        EEPROM.write(323,pump3.Wednesday); // save to memory
        myFiles.load(30, 261, 30, 30, schedActiveB[pump3.Wednesday]); 
      }
    }
    else if ((x>=84)&&(x<=114)&&(y>=261)&&(y<=291)) // dose on Thursday
    {
      if (scheduleItem==1) // for Macros
      {
        if (pump1.Thursday==1) pump1.Thursday=0;
        else pump1.Thursday=1;
        EEPROM.write(306,pump1.Thursday); // save to memory
        myFiles.load(84, 261, 30, 30, schedActiveB[pump1.Thursday]); 
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.Thursday==1) pump2.Thursday=0;
        else pump2.Thursday=1;
        EEPROM.write(315,pump2.Thursday); // save to memory
        myFiles.load(84, 261, 30, 30, schedActiveB[pump2.Thursday]); 
      }
      else if (scheduleItem==3) // for Excel
      {
        if (pump3.Thursday==1) pump3.Thursday=0;
        else pump3.Thursday=1;
        EEPROM.write(324,pump3.Thursday); // save to memory
        myFiles.load(84, 261, 30, 30, schedActiveB[pump3.Thursday]); 
      }
    }
    else if ((x>=132)&&(x<=162)&&(y>=261)&&(y<=291)) // dose on Friday
    {
      if (scheduleItem==1) // for Macros
      {
        if (pump1.Friday==1) pump1.Friday=0;
        else pump1.Friday=1;
        EEPROM.write(307,pump1.Friday); // save to memory
        myFiles.load(132, 261, 30, 30, schedActiveB[pump1.Friday]); 
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.Friday==1) pump2.Friday=0;
        else pump2.Friday=1;
        EEPROM.write(316,pump2.Friday); // save to memory
        myFiles.load(132, 261, 30, 30, schedActiveB[pump2.Friday]); 
      }
      else if (scheduleItem==3) // for Excel
      {
        if (pump3.Friday==1) pump3.Friday=0;
        else pump3.Friday=1;
        EEPROM.write(325,pump3.Friday); // save to memory
        myFiles.load(132, 261, 30, 30, schedActiveB[pump3.Friday]); 
      }
    }
    else if ((x>=186)&&(x<=216)&&(y>=261)&&(y<=291)) // dose on Saturday
    {
      if (scheduleItem==1) // for Macros
      {
        if (pump1.Saturday==1) pump1.Saturday=0;
        else pump1.Saturday=1;
        EEPROM.write(308,pump1.Saturday); // save to memory
        myFiles.load(186, 261, 30, 30, schedActiveB[pump1.Saturday]); 
      }
      else if (scheduleItem==2) // for Micros
      {
        if (pump2.Saturday==1) pump2.Saturday=0;
        else pump2.Saturday=1;
        EEPROM.write(317,pump2.Saturday); // save to memory
        myFiles.load(186, 261, 30, 30, schedActiveB[pump2.Saturday]); 
      }
      else if (scheduleItem==3) // for Excel
      {
        if (pump3.Saturday==1) pump3.Saturday=0;
        else pump3.Saturday=1;
        EEPROM.write(326,pump3.Saturday); // save to memory
        myFiles.load(186, 261, 30, 30, schedActiveB[pump3.Saturday]); 
      }
    }
    break;

  case 16:  // screen brightness settings 

    myGLCD.setFont(arial_bold);
    touchWaitTime = MEDIUM_WAIT;
    // byte screenRetHome, screenDimLevel, screenDimSec, screenBrightMem;

    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button  
    {     
      screenSettings();
    }  
    else if ((x>=145)&&(x<=169)&&(y>=42)&&(y<=66))   // return home min up
    {
      if (screenRetHome<255)
      {
        screenRetHome=screenRetHome+1;  // increment up by one
        itoa(screenRetHome, char3, 10);
        if (screenRetHome>=0 && screenRetHome<=9) // add a zero
        {
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect(191,59,239,75); // clear previous value
        }
        myGLCD.setColor(255, 77, 0);
        myGLCD.print(char3, 191, 59); 
        EEPROM.write(28,screenRetHome);  // save to memory
      }
    }
    else if ((x>=145)&&(x<=169)&&(y>=72)&&(y<=96))    // return home min down
    {
      if (screenRetHome>0)
      {
        screenRetHome=screenRetHome-1;  // increment down by one
        itoa(screenRetHome, char3, 10);
        myGLCD.setColor(255, 77, 0);
        if (screenRetHome>=0 && screenRetHome<=9) // add a zero
        {
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect(191,59,239,75); // clear previous value
        }
        myGLCD.setColor(255, 77, 0);
        myGLCD.print(char3, 191, 59); 
        EEPROM.write(28,screenRetHome);  // save to memory
      }
    }
    else if ((x>=145)&&(x<=169)&&(y>=110)&&(y<=134))   // auto-dim level up by 1
    {
      if (screenDimLevel < 10)
      {
        screenDimLevel=(screenDimLevel+1);  // increment up by 1
        EEPROM.write(29,screenDimLevel); // save new value
        itoa(screenDimLevel, char3, 10);
        myGLCD.setColor(255, 77, 0);
        myGLCD.print(char3, 191, 127);
      }
    }
    else if ((x>=145)&&(x<=169)&&(y>=140)&&(y<=164))   // auto-dim level down by 1
    {
      if (screenDimLevel > 1)
      {
        if (screenDimLevel == 10) // clear old data
        {
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect(191,127,223,143); // clear previous value
        }
        screenDimLevel=(screenDimLevel-1);  // increment up by 1
        EEPROM.write(29,screenDimLevel); // save new value
        itoa(screenDimLevel, char3, 10);
        myGLCD.setColor(255, 77, 0);
        myGLCD.print(char3, 191, 127);
      }
    }
    else if ((x>=145)&&(x<=169)&&(y>=178)&&(y<=202))   // dim seconds up by 1
    {
      if (screenDimSec<255)
      {
        screenDimSec=(screenDimSec+1);  // increment up by 1
        EEPROM.write(30,screenDimSec); // save new value
        itoa(screenDimSec, char6, 10);
        myGLCD.setColor(255, 77, 0);
        myGLCD.print(char6, 191, 197);
      }
    }
    else if ((x>=145)&&(x<=169)&&(y>=178)&&(y<=232))   // dim seconds down by one
    {
      if (screenDimSec>0)
      {
        screenDimSec=(screenDimSec-1);  // increment up by 1
        EEPROM.write(30,screenDimSec); // save new value
        itoa(screenDimSec, char6, 10);
        myGLCD.setColor(255, 77, 0);
        myGLCD.print(char6, 191, 197);
      }
    }
    else if ((x>=145)&&(x<=169)&&(y>=245)&&(y<=269))   // brightness up by 1
    {
      if (screenBrightMem < 10)
      {
        screenBrightMem=(screenBrightMem+1);  // increment up by 1
        EEPROM.write(31,screenBrightMem); // save new value
        itoa(screenBrightMem, char6, 10);
        myGLCD.setColor(255, 77, 0);
        myGLCD.print(char6, 191, 264);
        backLight = map(screenBrightMem,1,10,10,255);
        analogWrite(screenBrightPin, backLight);
      }
    }
    else if ((x>=145)&&(x<=169)&&(y>=275)&&(y<=299))   // brightness down by one
    {
      if (screenBrightMem>1)
      {
        if (screenBrightMem == 10) // clear old data
        {
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect(191,264,223,280); // clear previous value
        }
        screenBrightMem=(screenBrightMem-1);  // Decrease by 1
        EEPROM.write(31,screenBrightMem); // save new value
        itoa(screenBrightMem, char6, 10);
        myGLCD.setColor(255, 77, 0);
        myGLCD.print(char6, 191, 264);
        backLight = map(screenBrightMem,1,10,10,255);
        analogWrite(screenBrightPin, backLight);
      }
    }
    break;
    
  case 17:  // ATO settings
  
    touchWaitTime = MEDIUM_WAIT;
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button  
    {     
      screenSettings();
    }
    else if ((x>=150)&&(x<=174)&&(y>=42)&&(y<=66))   // low level wait time up
    {
      byte waitTime=EEPROM.read(42); // 42 // low level wait time in minutes
      waitTime++;  // increase by one
      EEPROM.write(42,waitTime);  // save to memory
      ATOWaitTime = waitTime * 60; // update wait time
      myGLCD.setColor(0, 0, 0); //clear old value
      myGLCD.fillRect(180,59,239,75);
      itoa(waitTime, char3, 10);
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(arial_bold);
      byte dx = 0;
      if(waitTime < 9)  dx += 16;
      if(waitTime < 99) dx += 16;
      myGLCD.print(char3, 180+dx, 59); // display new value
    }
    else if ((x>=150)&&(x<=174)&&(y>=72)&&(y<=96))   // low level wait time down
    {
      byte waitTime=EEPROM.read(42); // 42 // low level wait time in minutes
      waitTime--;  // decrease by one
      EEPROM.write(42,waitTime);  // save to memory
      ATOWaitTime = waitTime * 60;
      myGLCD.setColor(0, 0, 0); //clear old value
      myGLCD.fillRect(180,59,239,75);
      itoa(waitTime, char3, 10);
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(arial_bold);
      byte dx = 0;
      if(waitTime < 9)  dx += 16;
      if(waitTime < 99) dx += 16;
      myGLCD.print(char3, 180+dx, 59); // display new value
    }
    else if ((x>=150)&&(x<=174)&&(y>=110)&&(y<=134))   // max run-time up
    {
      int maxRunTime=EEPROM.read(43); // 43 // max run time (*10 seconds)
      if(maxRunTime < 99)maxRunTime++;  // increase by one
      EEPROM.write(43,maxRunTime);  // save to memory
      ATORunTime = maxRunTime*10; // convert to power of 10 to get actual sec.
      itoa(ATORunTime, char6, 10);
      myGLCD.setColor(0, 0, 0); //clear old value
      myGLCD.fillRect(180,127,239,143);
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(arial_bold);
      byte dx = 0;
      if(ATORunTime < 9)  dx += 16;
      if(ATORunTime < 99) dx += 16;
      myGLCD.print(char6, 180+dx, 127);
    }
    else if ((x>=150)&&(x<=174)&&(y>=140)&&(y<=164))   // max run-time down
    {
      int maxRunTime=EEPROM.read(43); // 43 // max run time (*10 seconds)
      if(maxRunTime > 1)maxRunTime--;  // decrease by one
      EEPROM.write(43,maxRunTime);  // save to memory
      ATORunTime = maxRunTime*10; // convert to power of 10 to get actual sec.
      itoa(ATORunTime, char6, 10);
      myGLCD.setColor(0, 0, 0); //clear old value
      myGLCD.fillRect(180,127,239,143);
      myGLCD.setColor(255, 77, 0);
      myGLCD.setFont(arial_bold);
      byte dx = 0;
      if(ATORunTime < 9)  dx += 16;
      if(ATORunTime < 99) dx += 16;
      myGLCD.print(char6, 180+dx, 127);
    }
    else if ((x>=172)&&(x<=218)&&(y>=200)&&(y<=222))   // ATO System enable
    {
      touchWaitTime = LONG_WAIT;
      byte enableATO = EEPROM.read(40);
      if(enableATO == 1)
      {
        ATOEnabled = false;
      }
      else
      {
        ATOEnabled = true;
      }
      EEPROM.write(40,ATOEnabled);
      //myFiles.load(180, 196, 30, 30, schedActiveB[ATOEnabled]);
      myFiles.load(172, 200, 46, 22, schedOnOff[ATOEnabled],2);
    }
    else if ((x>=172)&&(x<=218)&&(y>=253)&&(y<=275))   // Reservoir switch enable
    {
      touchWaitTime = LONG_WAIT;
      byte enableSwitch = EEPROM.read(41);
      if(enableSwitch == 1)
      {
        ResSwitchEnabled = false;
      }
      else
      {
        ResSwitchEnabled = true;
      }
      EEPROM.write(41,ResSwitchEnabled);
      //myFiles.load(180, 249, 30, 30, schedActiveB[ResSwitchEnabled]);
      myFiles.load(172, 253, 46, 22, schedOnOff[ResSwitchEnabled],2);
    }
    break;
    
  case 18:  // Sensor settings
  
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button  
    {     
      screenSettings();
    }
    else if ((x>=170)&&(x<=200)&&(y>=55)&&(y<=85))   // Enable sensor 1
    {
      if(sensor1Enabled)
      {
        sensor1Enabled = false;
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(210,58,236,84);//erase setting button
      }else
      {
        sensor1Enabled = true;
        myFiles.load(210, 58, 26, 26, "footextr.raw",2); //draw setting button
        sensorW.begin();
        sensorW.getAddress(waterSensor, 0); //refresh device address
      }
      EEPROM.write(50,sensor1Enabled);
      myFiles.load(170, 55, 30, 30, schedActiveB[sensor1Enabled]);
    }
    else if ((x>=170)&&(x<=200)&&(y>=108)&&(y<=138))   // Enable sensor 2
    {
      if(sensor2Enabled)
      {
        sensor2Enabled = false;
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(210,111,236,137);//erase setting button
        alarmFan1off();
      }else
      {
        sensor2Enabled = true;
        myFiles.load(210, 111, 26, 26, "footextr.raw",2);//draw setting button
        sensorH.begin();
        sensorH.getAddress(heatsinkSensor, 0); //refresh address of temperature sensor
      }
      EEPROM.write(51,sensor2Enabled);
      myFiles.load(170, 108, 30, 30, schedActiveB[sensor2Enabled]);
    }
    else if ((x>=170)&&(x<=200)&&(y>=161)&&(y<=191))   // Enable sensor 3
    {
      if(sensor3Enabled)
      {
        sensor3Enabled = false;
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRect(210,164,236,190);//erase setting button
        alarmFan2off();
      }else
      {
        sensor3Enabled = true;
        myFiles.load(210, 164, 26, 26, "footextr.raw",2);//draw setting button
      }
      EEPROM.write(52,sensor3Enabled);
      myFiles.load(170, 161, 30, 30, schedActiveB[sensor3Enabled]);
    }
    else if ((x>=210)&&(x<=236)&&(y>=58)&&(y<=84))   // Sensor 1 settings
    {
      if(sensor1Enabled)
      {
        screenHeater();
        sensorW.begin();
        sensorW.getAddress(waterSensor, 0); //refresh device address
      }
    }
    else if ((x>=210)&&(x<=236)&&(y>=111)&&(y<=137))   // Sensor 2 settings
    {
      if(sensor2Enabled)
      {
        screenHeatsink();
        sensorH.begin();
        sensorH.getAddress(heatsinkSensor, 0); //refresh address of temperature sensor
      }
    }
    else if ((x>=210)&&(x<=236)&&(y>=164)&&(y<=190))   // Sensor 3 settings
    {
      if(sensor3Enabled)
      {
        screenInternalTemp();
      }
    }
    else if ((x>=60)&&(x<=90)&&(y>=250)&&(y<=280))   // Display in celcius
    {
      displayInC = true;
      EEPROM.write(57,displayInC);
      myFiles.load(60, 250, 30, 30, schedActiveB[1]);
      myFiles.load(140, 250, 30, 30, schedActiveB[0]);
    }
    else if ((x>=140)&&(x<=170)&&(y>=250)&&(y<=280))   // Display in farenheit
    {
      displayInC = false;
      EEPROM.write(57,displayInC);
      myFiles.load(60, 250, 30, 30, schedActiveB[0]);
      myFiles.load(140, 250, 30, 30, schedActiveB[1]);
    }
    break;
    
  case 19:  // Heatsink fan settings
  
    myGLCD.setFont(arial_bold);
    myGLCD.setColor(255, 77, 0);
    touchWaitTime = MEDIUM_WAIT;
    
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button  
    {     
      screenSensors();
    }
    else if ((x>=162)&&(x<=186)&&(y>=37)&&(y<=61)) // Fan off temp up arrow
    {
      heatsinkFanOffTemp=EEPROM.read(54); // read existing setting
      heatsinkFanOffTemp=heatsinkFanOffTemp+1; // increment
      itoa(heatsinkFanOffTemp, char3, 10);
      myGLCD.print(char3, 194, 56);
      EEPROM.write(54,heatsinkFanOffTemp); // save setting
    }
    else if ((x>=162)&&(x<=186)&&(y>=67)&&(y<=91)) // Fan off temp down arrow
    {
      heatsinkFanOffTemp=EEPROM.read(54); // read existing setting
      heatsinkFanOffTemp=heatsinkFanOffTemp-1; // decrease
      itoa(heatsinkFanOffTemp, char3, 10);
      myGLCD.print(char3, 194, 56);
      EEPROM.write(54,heatsinkFanOffTemp); // save setting
    }
    else if ((x>=162)&&(x<=186)&&(y>=103)&&(y<=127)) // Fan on temp up arrow
    {
      heatsinkFanOnTemp=EEPROM.read(53); // read existing setting
      heatsinkFanOnTemp=heatsinkFanOnTemp+1; // increase
      itoa(heatsinkFanOnTemp, char3, 10);
      myGLCD.print(char3, 194, 122);
      EEPROM.write(53,heatsinkFanOnTemp); // save setting
    }
    else if ((x>=162)&&(x<=186)&&(y>=133)&&(y<=157)) // Fan on temp down arrow
    {
      heatsinkFanOnTemp=EEPROM.read(53); // read existing setting
      heatsinkFanOnTemp=heatsinkFanOnTemp-1; // decrease
      itoa(heatsinkFanOnTemp, char3, 10);
      myGLCD.print(char3, 194, 122);
      EEPROM.write(53,heatsinkFanOnTemp); // save setting
    }
    else if ((x>=136)&&(x<=160)&&(y>=169)&&(y<=193))  // offset up button  
    {
      byte storedVal = EEPROM.read(59);
      byte dx = 176;
      if(storedVal < 227)
      {
        storedVal++;
        EEPROM.write(59,storedVal);
        if(storedVal < 128)dx = 160;
        sensor2Calibration = ((float)storedVal - 128) / 10;
        dtostrf(sensor2Calibration, 3, 1, char6);  //convert to string
        myGLCD.print(char6, dx, 188);
        if(displayInC == true) myFiles.load(226, 190, 14, 12, "c.raw",2);
        if(displayInC == false)myFiles.load(226, 190, 14, 12, "f.raw",2);
        myGLCD.setColor(VGA_BLACK);
        if(storedVal >= 128)myGLCD.fillRect(160,188,176,204);//erase negative sign
      }
    }
    else if ((x>=136)&&(x<=160)&&(y>=199)&&(y<=223))  // offset down button  
    {
      byte storedVal = EEPROM.read(59);
      byte dx = 176;
      if(storedVal > 29)
      {
        storedVal--;
        EEPROM.write(59,storedVal);
        if(storedVal < 128)dx = 160;
        sensor2Calibration = ((float)storedVal - 128) / 10;
        dtostrf(sensor2Calibration, 3, 1, char6);  //convert to string
        myGLCD.print(char6, dx, 188);
        if(displayInC == true) myFiles.load(226, 190, 14, 12, "c.raw",2);
        if(displayInC == false)myFiles.load(226, 190, 14, 12, "f.raw",2);
      }
    }
    else if ((x>=162)&&(x<=208)&&(y>=251)&&(y<=273))  // enable display of sensor
    {
      displaySensor2 = EEPROM.read(62);
      if(displaySensor2)
      {
        displaySensor2 = false;
        EEPROM.write(62,0);
      }else
      {
        displaySensor2 = true;
        EEPROM.write(62,1);
      }
      //myFiles.load(170, 247, 30, 30, schedActiveB[displaySensor2],2);
      myFiles.load(162, 251, 46, 22, schedOnOff[displaySensor2],2);
    }
    break;
    
  case 20:  // Internal temperature fan settings
  
    myGLCD.setFont(arial_bold);
    myGLCD.setColor(255, 77, 0);
    touchWaitTime = MEDIUM_WAIT;
    
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button  
    {     
      screenSensors();
    }
    else if ((x>=162)&&(x<=186)&&(y>=37)&&(y<=61)) // Fan off temp up arrow
    {
      internalFanOffTemp=EEPROM.read(56); // read existing setting
      internalFanOffTemp=internalFanOffTemp+1; // increment
      itoa(internalFanOffTemp, char3, 10);
      myGLCD.print(char3, 194, 56);
      EEPROM.write(56,internalFanOffTemp); // save setting
    }
    else if ((x>=162)&&(x<=186)&&(y>=67)&&(y<=91)) // Fan off temp down arrow
    {
      internalFanOffTemp=EEPROM.read(56); // read existing setting
      internalFanOffTemp=internalFanOffTemp-1; // decrease
      itoa(internalFanOffTemp, char3, 10);
      myGLCD.print(char3, 194, 56);
      EEPROM.write(56,internalFanOffTemp); // save setting
    }
    else if ((x>=162)&&(x<=186)&&(y>=103)&&(y<=127)) // Fan on temp up arrow
    {
      internalFanOnTemp=EEPROM.read(55); // read existing setting
      internalFanOnTemp=internalFanOnTemp+1; // increase
      itoa(internalFanOnTemp, char3, 10);
      myGLCD.print(char3, 194, 122);
      EEPROM.write(55,internalFanOnTemp); // save setting
    }
    else if ((x>=162)&&(x<=186)&&(y>=133)&&(y<=157)) // Fan on temp down arrow
    {
      internalFanOnTemp=EEPROM.read(55); // read existing setting
      internalFanOnTemp=internalFanOnTemp-1; // decrease
      itoa(internalFanOnTemp, char3, 10);
      myGLCD.print(char3, 194, 122);
      EEPROM.write(55,internalFanOnTemp); // save setting
    }
    else if ((x>=136)&&(x<=160)&&(y>=169)&&(y<=193))  // offset up button
    {
      byte storedVal = EEPROM.read(60);
      byte dx = 176;
      if(storedVal < 227)
      {
        storedVal++;
        EEPROM.write(60,storedVal);
        if(storedVal < 128)dx = 160;
        sensor3Calibration = ((float)storedVal - 128) / 10;
        dtostrf(sensor3Calibration, 3, 1, char6);  //convert to string
        myGLCD.print(char6, dx, 188);
        if(displayInC == true) myFiles.load(226, 190, 14, 12, "c.raw",2);
        if(displayInC == false)myFiles.load(226, 190, 14, 12, "f.raw",2);
        myGLCD.setColor(VGA_BLACK);
        if(storedVal >= 128)myGLCD.fillRect(160,188,176,204);//erase negative sign
      }
    }
    else if ((x>=136)&&(x<=160)&&(y>=199)&&(y<=223))  // offset down button  
    {
      byte storedVal = EEPROM.read(60);
      byte dx = 176;
      if(storedVal > 29)
      {
        storedVal--;
        EEPROM.write(60,storedVal);
        if(storedVal < 128)dx = 160;
        sensor3Calibration = ((float)storedVal - 128) / 10;
        dtostrf(sensor3Calibration, 3, 1, char6);  //convert to string
        myGLCD.print(char6, dx, 188);
        if(displayInC == true) myFiles.load(226, 190, 14, 12, "c.raw",2);
        if(displayInC == false)myFiles.load(226, 190, 14, 12, "f.raw",2);
      }
    }
    else if ((x>=162)&&(x<=208)&&(y>=251)&&(y<=273))  // enable display of sensor
    {
      displaySensor3 = EEPROM.read(63);
      if(displaySensor3)
      {
        displaySensor3 = false;
        EEPROM.write(63,0);
      }else
      {
        displaySensor3 = true;
        EEPROM.write(63,1);
      }
      //myFiles.load(170, 247, 30, 30, schedActiveB[displaySensor3],2);
      myFiles.load(162, 251, 46, 22, schedOnOff[displaySensor3],2);
    }
    break;
    
  case 21:  // Lunar cycle settings
  
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button  
    {
      screenSettings();
    }
    else if ((x>=190)&&(x<=220)&&(y>=55)&&(y<=85))  // enable button  
    {
      byte lunarEnabled = EEPROM.read(70);
      if(lunarEnabled)
      {
        lunarEnabled = false;
      }else
      {
        lunarEnabled = true;
      }
      EEPROM.write(70,lunarEnabled);
      myFiles.load(190, 55, 30, 30, schedActiveB[lunarEnabled]);
    }
    break;
    
  case 22:  // Bargraph color settings
    
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button  
    {
      screenSettings();
    }
    else if ((x>=26)&&(x<=71)&&(y>=80)&&(y<=125))  // bar1 selected  
    {
      selectedChan = 1;
      screenColor(selectedChan);
    }
    else if ((x>=97)&&(x<=140)&&(y>=80)&&(y<=125))  // bar2 selected  
    {
      selectedChan = 2;
      screenColor(selectedChan);
    }
    else if ((x>=168)&&(x<=213)&&(y>=80)&&(y<=125))  // bar3 selected  
    {
      selectedChan = 3;
      screenColor(selectedChan);
    }
    else if ((x>=26)&&(x<=71)&&(y>=140)&&(y<=185))  // bar4 selected  
    {
      selectedChan = 4;
      screenColor(selectedChan);
    }
    else if ((x>=97)&&(x<=142)&&(y>=140)&&(y<=185))  // bar5 selected  
    {
      selectedChan = 5;
      screenColor(selectedChan);
    }
    else if ((x>=168)&&(x<=213)&&(y>=140)&&(y<=185))  // bar6 selected  
    {
      selectedChan = 6;
      screenColor(selectedChan);
    }
    else if ((x>=8)&&(x<=33)&&(y>=243)&&(y<=268))  // color 1 selected  
    {
      EEPROM.write(79+selectedChan,0);
      barColors[selectedChan-1] = 0;
      screenColor(selectedChan);
    }
    else if ((x>=41)&&(x<=66)&&(y>=243)&&(y<=268))  // color 2 selected  
    {
      EEPROM.write(79+selectedChan,1);
      barColors[selectedChan-1] = 1;
      screenColor(selectedChan);
    }
    else if ((x>=74)&&(x<=99)&&(y>=243)&&(y<=268))  // color 3 selected  
    {
      EEPROM.write(79+selectedChan,2);
      barColors[selectedChan-1] = 2;
      screenColor(selectedChan);
    }
    else if ((x>=107)&&(x<=132)&&(y>=243)&&(y<=268))  // color 4 selected  
    {
      EEPROM.write(79+selectedChan,3);
      barColors[selectedChan-1] = 3;
      screenColor(selectedChan);
    }
    else if ((x>=140)&&(x<=165)&&(y>=243)&&(y<=268))  // color 5 selected  
    {
      EEPROM.write(79+selectedChan,4);
      barColors[selectedChan-1] = 4;
      screenColor(selectedChan);
    }
    else if ((x>=173)&&(x<=198)&&(y>=243)&&(y<=268))  // color 6 selected  
    {
      EEPROM.write(79+selectedChan,5);
      barColors[selectedChan-1] = 5;
      screenColor(selectedChan);
    }
    else if ((x>=206)&&(x<=231)&&(y>=243)&&(y<=268))  // color 7 selected  
    {
      EEPROM.write(79+selectedChan,6);
      barColors[selectedChan-1] = 6;
      screenColor(selectedChan);
    }
    
    break;
    
  case 23:
  
    if((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button  
    {
      screenSettings();
    }
    
    break;
    
  case 24:
    
    if (lightEditing==0) // actions for buttons that are active when editing is not active
    {
      boolean updateLightValues=false; // track if we need to update the light values at the end due to mode change

      if ((x>=10)&&(x<=58)&&(y>=39)&&(y<=87))        //  full sun mode button
      {
        clearSelectedLight(1); // deselect the previously selected light
        currentLightMode=0;
        if (lightCSP==true) irsend.sendNEC(M1,32); // send IR to lights to change modes
        currentColor = lightHighSun; // update current color values
        tempColor = lightHighSun;
        myFiles.load(10, 101, 48, 63, lightEdit[1]); // activate the edit button
        myFiles.load(10, 39, 48, 48, lightModeS[currentLightMode]); // draw the button selected
        updateLightValues=true; // update the light values
      }
      else if ((x>=67)&&(x<=115)&&(y>=39)&&(y<=87))    //  mid sun mode button
      {
        clearSelectedLight(1); // deselect the previously selected light
        currentLightMode=1;
        if (lightCSP==true) irsend.sendNEC(M2,32); // send IR to lights to change modes
        currentColor = lightMidSun;
        tempColor = lightMidSun;
        myFiles.load(10, 101, 48, 63, lightEdit[1]); // activate the edit button
        myFiles.load(67, 39, 48, 48, lightModeS[currentLightMode]); // draw the button selected
        updateLightValues=true; // update the light values
      }
      else if ((x>=124)&&(x<=172)&&(y>=39)&&(y<=87))      //  low sun mode button
      {
        clearSelectedLight(1); // deselect the previously selected light
        currentLightMode=2;
        if (lightCSP==true) irsend.sendNEC(M3,32); // send IR to lights to change modes
        currentColor = lightLowSun;
        tempColor = lightLowSun;
        myFiles.load(10, 101, 48, 63, lightEdit[1]); // activate the edit button
        myFiles.load(124, 39, 48, 48, lightModeS[currentLightMode]); // draw the button selected
        updateLightValues=true; // update the light values
      }
      else if ((x>=181)&&(x<=229)&&(y>=39)&&(y<=87))     //  moon mode button
      {
        clearSelectedLight(1); // deselect the previously selected light
        currentLightMode=3;
        if (lightCSP==true) irsend.sendNEC(M4,32); // send IR to lights to change modes
        currentColor = lightMoon;
        tempColor = lightMoon;
        myFiles.load(10, 101, 48, 63, lightEdit[1]); // activate the edit button
        myFiles.load(181, 39, 48, 48, lightModeS[currentLightMode]); // draw the button selected
        updateLightValues=true; // update the light values
      }
      else if ((x>=10)&&(x<=58)&&(y>=101)&&(y<=149))        //  edit button
      {
        touchWaitTime = MEDIUM_WAIT; // can adjust sliders faster than every half second
        clearSelectedLight(2); // turn off light modes that are inactive
        lightEditing=1; // activate editing mode
        myFiles.load(181, 101, 48, 63, lightResync[0]); // disable resync
        myFiles.load(10, 101, 48, 63, lightEdit[0]); // disable edit
        myFiles.load(67, 101, 48, 63, lightSave[1]); // enable save
        myFiles.load(124, 101, 48, 63, lightCancel[1]); // enable cancel
        
        // enable RGBW buttons
        myFiles.load(10, 175, 48, 48, lightRed[0]);
        myFiles.load(67, 175, 48, 48, lightGreen[0]);
        myFiles.load(124, 175, 48, 48, lightBlue[0]);
        myFiles.load(181, 175, 48, 48, lightWhite[0]);
        
        myFiles.load(10, 241, 48, 48, lightRed[1]);
        myFiles.load(67, 241, 48, 48, lightGreen[1]);
        myFiles.load(124, 241, 48, 48, lightBlue[1]);
        myFiles.load(181, 241, 48, 48, lightWhite[1]);
      }
      else if ((x>=181)&&(x<=229)&&(y>=101)&&(y<=149))    //  resync button
      {
        screenResyncLights(); // display that we are resyncing
        resyncLights(); // actually resync the lights
        screenLightsIR(); // redraw the lights screen
      }

      // if modes were switched, we need to update the lighting values
      if (updateLightValues==1)
      {
        //Clear old RGBW values
        myGLCD.setColor(0,0,0);
        myGLCD.fillRect(0,228,239,236);
        
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
      }
    }
    else if (lightEditing==1) // actions for buttons that are active when editing is active
    {
      int dy;
      if ((x>=67)&&(x<=115)&&(y>=101)&&(y<=149))    //  save button
      {
        touchWaitTime = LONG_WAIT; // return to normal delays between touch events
        screenResyncLights(); // show that we are working

        // setup eeprom rgbw variables
        int e1, e2, e3, e4, e5, e6;

        // save current light mode
        if (currentLightMode==0)
        {
          e1=400; // eeprom location to save M1 red
          e2=401; // eeprom location to save M1 green
          e3=402; // eeprom location to save M1 blue
          e4=403; // eeprom location to save M1 cool white
          e5=404;
          e6=405;
          if (lightCSP==true)irsend.sendNEC(M1,32); // save values to position 1 on lights
          if (lightCSP==true)irsend.sendNEC(0xFFFFFFFF,32); // start sending footer to save
        }
        else if (currentLightMode==1)
        {
          e1=410; // eeprom location to save M2 red
          e2=411; // eeprom location to save M2 green
          e3=412; // eeprom location to save M2 blue
          e4=413; // eeprom location to save M2 cool white
          e5=414;
          e6=415;
          if (lightCSP==true)irsend.sendNEC(M2,32); // save values to position 2 on lights
          if (lightCSP==true)irsend.sendNEC(0xFFFFFFFF,32); // blast footer to save
        }
        else if (currentLightMode==2)
        {
          e1=420; // eeprom location to save M3 red
          e2=421; // eeprom location to save M3 green
          e3=422; // eeprom location to save M3 blue
          e4=423; // eeprom location to save M3 cool white
          e5=424;
          e6=425;
          if (lightCSP==true)irsend.sendNEC(M3,32); // save values to position 3 on lights
          if (lightCSP==true)irsend.sendNEC(0xFFFFFFFF,32); //  start sending footer to save
        }
        else if (currentLightMode==3)
        {
          e1=430; // eeprom location to save M4 red
          e2=431; // eeprom location to save M4 green
          e3=432; // eeprom location to save M4 blue
          e4=433; // eeprom location to save M4 cool white
          e5=434;
          e6=435;
          if (lightCSP==true)irsend.sendNEC(M4,32); // save values to position 4 on lights
          if (lightCSP==true)irsend.sendNEC(0xFFFFFFFF,32); //  start sending footer to save
        }
        if (lightCSP==true) 
        {
          // blast the footer for 3 seconds to save the memory position in the light
          unsigned long currentMillis = millis(); // get current millis
          unsigned long blastMillis = millis(); // get current millis
          while ((blastMillis-currentMillis)<5000)
          {
            irsend.sendNEC(0xFFFFFFFF,32); // blast footer to save
            blastMillis = millis(); // get current millis
          }
        }
        Serial.print(F("LED values before saving: \n"));
        Serial.print(F("currentColor.chan1: "));
        Serial.println(currentColor.chan1);
        Serial.print(F("currentColor.chan2: "));
        Serial.println(currentColor.chan2);
        Serial.print(F("currentColor.chan3: "));
        Serial.println(currentColor.chan3);
        Serial.print(F("currentColor.chan4: "));
        Serial.println(currentColor.chan4);
        Serial.print(F("currentColor.chan5: "));
        Serial.println(currentColor.chan5);
        Serial.print(F("currentColor.chan6: "));
        Serial.println(currentColor.chan6);
        Serial.print(F("currentLightMode: "));
        Serial.println(currentLightMode);
        
        // save new values to eeprom locations
        EEPROM.write(e1,currentColor.chan1);
        EEPROM.write(e2,currentColor.chan2);
        EEPROM.write(e3,currentColor.chan3);
        EEPROM.write(e4,currentColor.chan4);
        EEPROM.write(e5,0);
        EEPROM.write(e6,0);

        lightEditing = 0; // disable editing
        int prevMode = currentLightMode; // keep track of what mode we are in
        resyncLights(); // we resync the lights after saving
        currentLightMode = prevMode; // return to the saved mode 

        // switch back to the lighting mode you saved
        if (lightCSP==true) 
        {
          if (currentLightMode==0) irsend.sendNEC(M1,32); // activate the mode you just saved
          else if (currentLightMode==1) irsend.sendNEC(M2,32); // activate the mode you just saved
          else if (currentLightMode==2) irsend.sendNEC(M3,32); // activate the mode you just saved
          else if (currentLightMode==3) irsend.sendNEC(M4,32); // activate the mode you just saved
          //irsend.sendNEC(0xFFFFFFFF,32); // send footer
        }
        setStartupLighting();
        screenLightsIR(); // redraw the screen
      }
      else if ((x>=124)&&(x<=172)&&(y>=101)&&(y<=149))      //  cancel button
      {
        lightEditing=0;
        touchWaitTime = LONG_WAIT;
        // switch back to current light mode
        if (currentLightMode==0) 
        {
          currentColor=lightHighSun;
          if (lightCSP==true) irsend.sendNEC(M1,32);
        }
        else if (currentLightMode==1) 
        {
          currentColor=lightMidSun;
          if (lightCSP==true) irsend.sendNEC(M2,32);
        }
        else if (currentLightMode==2) 
        {
          currentColor=lightLowSun;
          if (lightCSP==true) irsend.sendNEC(M3,32);
        }
        else if (currentLightMode==3) 
        {
          currentColor=lightMoon;
          if (lightCSP==true) irsend.sendNEC(M4,32);
        }
        screenLightsIR(); // redraw screen
      }
      else if ((x>=10)&&(x<=58)&&(y>=175)&&(y<=223))        //  red up
      {
        if (currentColor.chan1 < maxIR)
        {
          currentColor.chan1++;
          //Clear old values
          myGLCD.setColor(0,0,0);
          myGLCD.fillRect(26,228,50,236);
          //Write new value
          myGLCD.setFont(Sinclair_S);
          myGLCD.setColor(255, 255, 255);
          byte dx = 25;
          if(currentColor.chan1 < 9)  dx += 4;
          if(currentColor.chan1 < 99) dx += 4;
          itoa(currentColor.chan1, char3, 10);
          myGLCD.print(char3, dx, 228);
          irsend.sendNEC(REDUP,32);  // send value to light
          Alarm.delay(333);
        }
      }
      else if ((x>=10)&&(x<=58)&&(y>=241)&&(y<=289))   //  red down
      {
        if (currentColor.chan1 > 0)
        {
          currentColor.chan1--;
          //Clear old values
          myGLCD.setColor(0,0,0);
          myGLCD.fillRect(26,228,50,236);
          //Write new value
          myGLCD.setFont(Sinclair_S);
          myGLCD.setColor(255, 255, 255);
          byte dx = 26;
          if(currentColor.chan1 < 9)  dx += 4;
          if(currentColor.chan1 < 99) dx += 4;
          itoa(currentColor.chan1, char3, 10);
          myGLCD.print(char3, dx, 228);
          irsend.sendNEC(REDDOWN,32);  // send value to light
          Alarm.delay(333);
        }
      }
      else if ((x>=67)&&(x<=115)&&(y>=175)&&(y<=223))  //  green up
      {
        if (currentColor.chan2 < maxIR)
        {
          currentColor.chan2++;
          //Clear old values
          myGLCD.setColor(0,0,0);
          myGLCD.fillRect(80,228,104,236);
          //Write new value
          myGLCD.setFont(Sinclair_S);
          myGLCD.setColor(255, 255, 255);
          byte dx = 80;
          if(currentColor.chan2 < 9)  dx += 4;
          if(currentColor.chan2 < 99) dx += 4;
          itoa(currentColor.chan2, char3, 10);
          myGLCD.print(char3, dx, 228);
          irsend.sendNEC(GREENUP,32);  // send value to light
          Alarm.delay(333);
        }
      }
      else if ((x>=67)&&(x<=115)&&(y>=241)&&(y<=289))  // green down
      {
        if (currentColor.chan2 > 0)
        {
          currentColor.chan2--;
          //Clear old values
          myGLCD.setColor(0,0,0);
          myGLCD.fillRect(80,228,104,236);
          //Write new value
          myGLCD.setFont(Sinclair_S);
          myGLCD.setColor(255, 255, 255);
          byte dx = 80;
          if(currentColor.chan2 < 9)  dx += 4;
          if(currentColor.chan2 < 99) dx += 4;
          itoa(currentColor.chan2, char3, 10);
          myGLCD.print(char3, dx, 228);
          irsend.sendNEC(GREENDOWN,32);  // send value to light
          Alarm.delay(333);
        }
      }
      else if ((x>=124)&&(x<=172)&&(y>=175)&&(y<=223)) //  blue up
      {
        if (currentColor.chan3 < maxIR)
        {
          currentColor.chan3++;
          //Clear old values
          myGLCD.setColor(0,0,0);
          myGLCD.fillRect(138,228,162,236);
          //Write new value
          myGLCD.setFont(Sinclair_S);
          myGLCD.setColor(255, 255, 255);
          byte dx = 138;
          if(currentColor.chan3 < 9)  dx += 4;
          if(currentColor.chan3 < 99) dx += 4;
          itoa(currentColor.chan3, char3, 10);
          myGLCD.print(char3, dx, 228);
          irsend.sendNEC(BLUEUP,32);  // send value to light
          Alarm.delay(333);
        }
      }
      else if ((x>=124)&&(x<=172)&&(y>=241)&&(y<=289)) //  blue down
      {
        if (currentColor.chan3 > 0)
        {
          currentColor.chan3--;
          //Clear old values
          myGLCD.setColor(0,0,0);
          myGLCD.fillRect(138,228,162,236);
          //Write new value
          myGLCD.setFont(Sinclair_S);
          myGLCD.setColor(255, 255, 255);
          byte dx = 138;
          if(currentColor.chan3 < 9)  dx += 4;
          if(currentColor.chan3 < 99) dx += 4;
          itoa(currentColor.chan3, char3, 10);
          myGLCD.print(char3, dx, 228);
          irsend.sendNEC(BLUEDOWN,32);  // send value to light
          Alarm.delay(333);
        }
      }
      else if ((x>=181)&&(x<=229)&&(y>=175)&&(y<=223)) //  white up
      {
        if (currentColor.chan4 < maxIR)
        {
          currentColor.chan4++;
          //Clear old values
          myGLCD.setColor(0,0,0);
          myGLCD.fillRect(195,228,219,236);
          //Write new value
          myGLCD.setFont(Sinclair_S);
          myGLCD.setColor(255, 255, 255);
          byte dx = 195;
          if(currentColor.chan4 < 9)  dx += 4;
          if(currentColor.chan4 < 99) dx += 4;
          itoa(currentColor.chan4, char3, 10);
          myGLCD.print(char3, dx, 228);
          irsend.sendNEC(WHITEUP,32);  // send value to light
          Alarm.delay(333);
        }
      }
      else if ((x>=181)&&(x<=229)&&(y>=241)&&(y<=289)) //  white down
      {
        if (currentColor.chan4 > 0)
        {
          currentColor.chan4--;
          //Clear old value
          myGLCD.setColor(0,0,0);
          myGLCD.fillRect(195,228,219,236);
          //Write new value
          myGLCD.setFont(Sinclair_S);
          myGLCD.setColor(255, 255, 255);
          byte dx = 195;
          if(currentColor.chan4 < 9)  dx += 4;
          if(currentColor.chan4 < 99) dx += 4;
          itoa(currentColor.chan4, char3, 10);
          myGLCD.print(char3, dx, 228);
          irsend.sendNEC(WHITEDOWN,32);  // send value to light
          Alarm.delay(333);
        }
      }
    }
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // settings button 
    {
      touchWaitTime = LONG_WAIT;
      //determine which light mode we should return to before leaving lighting screen
      smartStartupRamp();
      setStartupLighting();
      screenSettings();
    }
    
  case 25:    // power item TIMER schedule screen

    myGLCD.setFont(arial_bold);
    myGLCD.setColor(255, 77, 0);
    touchWaitTime = MEDIUM_WAIT;
    
    if ((x>=107)&&(x<=129)&&(y>=294)&&(y<=318))  // schedule button  
    {
      screenPwrSchedule();
    }
    else if ((x>=108)&&(x<=132)&&(y>=90)&&(y<=114)) // on hour up
    {
      int onHour;
      if (scheduleItem==5)
      {
        if (schedAux1.onHour==23) schedAux1.onHour=0;
        else schedAux1.onHour=schedAux1.onHour+1;
        onHour=schedAux1.onHour;
        EEPROM.write(121,onHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.onHour==23) schedAux2.onHour=0;
        else schedAux2.onHour=schedAux2.onHour+1;
        onHour=schedAux2.onHour;
        EEPROM.write(126,onHour); // save to memory
      }

      // print to screen
      itoa(onHour, char3, 10);
      if (onHour>=0 && onHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 137, 109);
    }
    else if ((x>=108)&&(x<=132)&&(y>=120)&&(y<=144)) // on hour down
    {
      int onHour;
      if (scheduleItem==5)
      {
        if (schedAux1.onHour==0) schedAux1.onHour=23;
        else schedAux1.onHour=schedAux1.onHour-1;
        onHour=schedAux1.onHour;
        EEPROM.write(121,onHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.onHour==0) schedAux2.onHour=23;
        else schedAux2.onHour=schedAux2.onHour-1;
        onHour=schedAux2.onHour;
        EEPROM.write(126,onHour); // save to memory
      }

      // print to screen
      itoa(onHour, char3, 10);
      if (onHour>=0 && onHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 137, 109);
    }
    else if ((x>=174)&&(x<=198)&&(y>=90)&&(y<=114)) // on min up
    {
      int onMinute;
      if (scheduleItem==5)
      {
        if (schedAux1.onMinute==59) schedAux1.onMinute=0;
        else schedAux1.onMinute=schedAux1.onMinute+1;
        onMinute=schedAux1.onMinute;
        EEPROM.write(122,onMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.onMinute==59) schedAux2.onMinute=0;
        else schedAux2.onMinute=schedAux2.onMinute+1;
        onMinute=schedAux2.onMinute;
        EEPROM.write(127,onMinute); // save to memory
      }

      // print to screen
      itoa(onMinute, char3, 10);
      if (onMinute>=0 && onMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 203, 109);
    }
    else if ((x>=174)&&(x<=198)&&(y>=120)&&(y<=144)) // on min down
    {
      int onMinute;
      if (scheduleItem==5)
      {
        if (schedAux1.onMinute==0) schedAux1.onMinute=59;
        else schedAux1.onMinute=schedAux1.onMinute-1;
        onMinute=schedAux1.onMinute;
        EEPROM.write(122,onMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.onMinute==0) schedAux2.onMinute=59;
        else schedAux2.onMinute=schedAux2.onMinute-1;
        onMinute=schedAux2.onMinute;
        EEPROM.write(127,onMinute); // save to memory
      }

      // print to screen
      itoa(onMinute, char3, 10);
      if (onMinute>=0 && onMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 203, 109);
    }
    else if ((x>=108)&&(x<=132)&&(y>=166)&&(y<=190)) // off hour up
    {
      int offHour;
      if (scheduleItem==5)
      {
        if (schedAux1.offHour==23) schedAux1.offHour=0;
        else schedAux1.offHour=schedAux1.offHour+1;
        offHour=schedAux1.offHour;
        EEPROM.write(123,offHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.offHour==23) schedAux2.offHour=0;
        else schedAux2.offHour=schedAux2.offHour+1;
        offHour=schedAux2.offHour;
        EEPROM.write(128,offHour); // save to memory
      }

      // print to screen
      itoa(offHour, char3, 10);
      if (offHour>=0 && offHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 137, 185);  
    }
    else if ((x>=108)&&(x<=132)&&(y>=196)&&(y<=220)) // off hour down
    {
      int offHour;
      if (scheduleItem==5)
      {
        if (schedAux1.offHour==0) schedAux1.offHour=23;
        else schedAux1.offHour=schedAux1.offHour-1;
        offHour=schedAux1.offHour;
        EEPROM.write(123,offHour); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.offHour==0) schedAux2.offHour=23;
        else schedAux2.offHour=schedAux2.offHour-1;
        offHour=schedAux2.offHour;
        EEPROM.write(128,offHour); // save to memory
      }

      // print to screen
      itoa(offHour, char3, 10);
      if (offHour>=0 && offHour<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 137, 185);  
    }
    else if ((x>=174)&&(x<=198)&&(y>=166)&&(y<=190)) // off min up
    {
      int offMinute;
      if (scheduleItem==5)
      {
        if (schedAux1.offMinute==59) schedAux1.offMinute=0;
        else schedAux1.offMinute=schedAux1.offMinute+1;
        offMinute=schedAux1.offMinute;
        EEPROM.write(124,offMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.offMinute==59) schedAux2.offMinute=0;
        else schedAux2.offMinute=schedAux2.offMinute+1;
        offMinute=schedAux2.offMinute;
        EEPROM.write(129,offMinute); // save to memory
      }

      // print to screen
      itoa(offMinute, char3, 10);
      if (offMinute>=0 && offMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 203, 185);
    }
    else if ((x>=174)&&(x<=198)&&(y>=196)&&(y<=220)) // off min down
    {
      int offMinute;
      if (scheduleItem==5)
      {
        if (schedAux1.offMinute==0) schedAux1.offMinute=59;
        else schedAux1.offMinute=schedAux1.offMinute-1;
        offMinute=schedAux1.offMinute;
        EEPROM.write(124,offMinute); // save to memory
      }
      else if (scheduleItem==6)
      {
        if (schedAux2.offMinute==0) schedAux2.offMinute=59;
        else schedAux2.offMinute=schedAux2.offMinute-1;
        offMinute=schedAux2.offMinute;
        EEPROM.write(129,offMinute); // save to memory
      }

      // print to screen
      itoa(offMinute, char3, 10);
      if (offMinute>=0 && offMinute<=9) // add a zero
      {
        //itoa(0, char3t, 10); //make char3t 0
        strcat(char3t, char3);
        strcpy (char3,char3t);
      }
      myGLCD.print(char3, 203, 185);
    }
    else if ((x>=153)&&(x<=199)&&(y>=232)&&(y<=254)) // active button
    {
      touchWaitTime = LONG_WAIT;
      int isActive;
      if (scheduleItem==5)
      {
        if (schedAux1.active==1) schedAux1.active=0;
        else schedAux1.active=1;
        isActive=schedAux1.active;
        EEPROM.write(120,isActive); // save to memory
      }
      if (scheduleItem==6)
      {
        if (schedAux2.active==1) schedAux2.active=0;
        else schedAux2.active=1;
        isActive=schedAux2.active;
        EEPROM.write(125,isActive); // save to memory
      }
      //myFiles.load(161, 228, 30, 30, schedActiveB[isActive]);
      myFiles.load(153, 232, 46, 22, schedOnOff[isActive],2);
    }
    else if ((x>=153)&&(x<=199)&&(y>=266)&&(y<=288)) // Timer button
    {
      touchWaitTime = LONG_WAIT;
      int isTimer;
	  
      if (scheduleItem==5)
      {
        if (schedAux1.timer==1) schedAux1.timer=0;
        else schedAux1.timer=1;
        isTimer=schedAux1.timer;
        EEPROM.write(140,isTimer); // save to memory
      }
      if (scheduleItem==6)
      {
        if (schedAux2.timer==1) schedAux2.timer=0;
        else schedAux2.timer=1;
        isTimer=schedAux2.timer;
        EEPROM.write(141,isTimer); // save to memory
      }
      myGLCD.setColor(255, 255, 255);
      if(isTimer)
      {
        // print on/off/active and buttons
        myGLCD.print("H", 112, 73);
        myGLCD.print("M", 178, 73);
        myGLCD.print("M", 112, 148);
        myGLCD.print("S", 178, 148);
        myGLCD.print(F("REPEAT"), 5, 109);
        myGLCD.print(F("DUR-"), 5, 177);
        myGLCD.print(F("ATION"), 5, 193);
      }else
      {
        myGLCD.print("H", 112, 73);
        myGLCD.print("M", 178, 73);
        myGLCD.print("H", 112, 148);
        myGLCD.print("M", 178, 148);
        myGLCD.print(F("     "), 5, 177);
        myGLCD.print(F("     "), 5, 193);
        myGLCD.print(F("ON    "), 5, 109);
        myGLCD.print(F("OFF"), 5, 185);
      }
      myFiles.load(153, 266, 46, 22, schedOnOff[isTimer],2);
    }

    break;
    
  }
}
