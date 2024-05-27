//Changes:
//V1.0 - Originally published version
//V2.0 - Altered to allow support for spare tyre reporting (although not displayed on LCD display)
//V3.0 - Added #define in globals.h to switch between BAR and PSI
//V4.0 - Now uses synchronous data from CC1101 and option of using either the SPI or the hardware pin for the CD signal (#define USE_HW_CD in globals.h). Also tideied up debug information if required (globals.h #defines)
//V5.0 - Corrected possible sync error when looking for start of data stream. Fix should improve hit rate on valid TPMS detection
//V5.1 - Added freq offset updates (SWRA159) - removed again(makes it worse!)
//V5.1.1 - Added functions for extracting RSSI as dbm
//V6.0 - Added code for options for US (315MHz) or UK (433MHz), also for different sensor types (PMV-C210, PMV-107J)
//V6.1 - Added support for Seeeduino Xiao
//V6.2 - Included support for Renault (Renault Clio, Renault Captur and maybe Dacia Sandero?) as an option (to be verified)
//V6.3 - Included support for Citroen (possibly also includes Peugeot and likely Fiat, Mitsubishi, VDO-types) as an option (to be verified)
//V6.4 - Some code rationalisation, all sensor timings now in Configs.h
//V6.5 - Tried to improve PMV-107J decode by starting at the end of the buffer and working forwards
//V6.6 - Added other car types (under development), changed PMV-107J frequency deviation, added #define as option to only detect specified IDs, stripped leading 4 bits from ID (as per 'Glopes' comment) for Toyota, moved some globals settings to Config.h, changed AGC settings 
//V6.7 - Adjusted PMV_C210 presure calculation to lower PSI by 0.3 (as suggested by Steven Andrews by comparing with Autel programmer). 
//     - Added option for displaying Fahrenheit (#ifdef DISPLAY_TEMP_AS_FAHRENHEIT in configs.h) rather than centigrade.
//     - Re-introduced flashing display if pressures outside of pre-set limits (enabled by #define ENABLE_PRESSURE_ALARMS in configs.h. PressureLowLimits and PressureHighLimits in config.h should be set as required)
//V7.0 - Included option for 1.8" TFT display (requires Seeeduino Xiao for extra memory)
//V8.0 - Added optional audible alarm for pressure alarms. Improved display flashing. Tested with Nissan Leaf 433MHz OK
//V9.0 - Added Pontiac (US) decoder option, moved all CC1101 configs to sensor-spcific include files, improved timer handling. Added temperature compensation for pressure limits (set pressure limits reference temperature in configs.h). Added kPA pressure display option.
//       Pressures always stored locally as psi and temperatures as deg C - including limits (converted if required for the display).
//       Tyre pressure and temperature limits are assumed to be in the required units e.g. bar, kpa, psi, degC, degF depending on config choice.
//       Added support for 240x240 round display (Steven Andrews' display code)
//V9.1 - Added provisional support for Arduino Nano 33 IOT board
//V9.2 - Fixed bugs in audible alarm for temperatures.. Fixed missing F/C for round display.
//V9.3 - Corrected some title positioning for display.h, Added support for Renault Zoe (pre 07/2019)
//V9.4 - Corrected compile error when not using display - thanks Zaran on Hackster.io
//V9.5 - Changes to cope with multiple tyre sets (Summer/Winter). Corrected bug in ID matching (IDs were allocated to PROGMEM but referenced as SRAM for lookups), this meant tyre position was not being reported correctly. Moved Ref[3] to globals.
//V9.6 - Fixed bug where lcd display was partially obliterated if TYRECOUNT > 4 (the default is now 5)
//V9.7 - Fixed bug in Ford.h which caused out of range temperture values to be displayed on screen when temperture below 0C. 
//       Changes to support new larger screen type (supplied by Steven Andrews' - thank you!). 2.4inch LCD Display Module 65K RGB Colors, ILI9341 2.4" TFT 240×320. Requires Adafruit ILI9341 library.
//V9.8 - Added support for Truck Solar TPMS and Mega256 build
//V9.9 - Added support for Ford strange Ford E-series (Tom Logan). It appears temperature format is reported in 2 ways depending upon whether or not the sensor was manually triggered (or not)
//V10.0 - Improved Ford incoming message handling
//V10.1 - Changed Ford pressure decode in line with actual E-series Schrader sensor feedback. This sensor also seems to delay sending temperatures after sleeping and sends a counter instead.
//V10.2 - Missing conditional for 2.4" screen in setup in .ino file (line 350) preventing initialisation of display (USE_24_INCH_ILI9341_DISPLAY). Causes screen to continually display white.
//V10.3 - Changed PMV-107J & PMV-C210 to try to improve detections. Code now walks through the received bit stream until a valid checksum match is found (or runs out of data)
//        This avoids the need to look for sync bits which may not be reliable at the start of the bit stream (includes change to common.h)
//V10.4 - Added trial for Toyota Sienna (TRW C070 sensor)
//V10.5 - Improvements to Toyota Sienna TRW C070 detection/validation. Added Hyundai I35 as option for this same sensor. 
//        Fixed temperature display bug (thanks Larry on Hackster for pointing this out.) - it would overflow/underflow with certain readings
//        Feedback from Alistair Clark on Hackster indicates that the C210 decode also works for Toyota Corolla (2019-22 PMV-C215 sensor)
//V10.6 - Corrected slight bug in display.h for Hyundai (should have been newline print)/ Thanks to grigata on Hackster for pointing this out.
//        Reported by gamer765 that PMV-107J also works for PMV-C11A sensors.
//        Added support for Hyundai Tucson TL/TLE (2015) using Schrader C1100/C8000 sensor. Many thanks to RM for helping on this one.
//V10.7 - Correct bug in CC1101.h in ReadFIFO function - it was missing the return statement (but worked for Xiao without it???)! Thanks to Nomake Wan for helping out on this one.
//        Added possible support for Xiao RP2040 (TBC)
//        Added support for Schrader A0009054100 senosr used on Smart Fortwo 01/2007-02/2014 (433MHz) - OOK
//V10.8 - Debugged to get Xiao RP2040 working. Same schematic as previous Xiao
//V11.0 - Added Winter tyre pressure limits (optionally). These could be easily be missed and cause an indexing outside of the array if INCLUDE_WINTER_SET enabled.
//        Added suport for Summer/Winter tyres on the displays (previously only available on serial output). Basically, if so configured, the
//        Summer and Winter tyre IDs will be recognised and displayed in their position on the display - user should make sure the other tyre set is out of range!
//V11.1 - Abandonded (not published)
//V11.2 - Changed handling of CD in main routine. Need to configure a valid ENDTIMING_MAX for each sensor type. This is used to exit the CD loop early if a reasonable number of bits have been received and it's been > ENDTIMING_MAX since the last edge (i.e. an ivalid bit timing - probably only valid for Manchester coded data)
//V11.3 - Added processor option for Adafruit 3v itsybitsy
//      - Put in conditionals for the TFT display include files to handle different GPIO formats (e.g. D1 vs just 1) depending on processor selected
//V11.4 - Changes from 10.8 affected CDWidth timings causing some sensors not to be detected. Fixed.
//      - Added software version to serial print out at startup
//V11.5 - Added LCD type to serial print out at startup. Debugged Jansite Solar code. Corrected bug in CRC routines. Changed all general declarations to width-specific types e.g. int to int16_t
//V11.6 - Trial of Subaru Impreza sensors code, both 433MHz and 315MHz (the two frequencies have different protocols)
//V11.7 - Tidied sloppy coding as much as possible in order to remove compiler warnings 
//V11.8 - Corrected bug in Manchester decoding under cetain circumstances when the number of leading 'short' timings before a 'long' timing is an odd number.
//        My thanks to Andrey Oleynik for pointing this out. Affected Toyota PMV_C210 and PMV107J
//        Fixed bug in Toyota_PMV_C210 around line 426,, DecodeBitArray call was missing a parameter and therefore calling the wrong instance. 
//        This caused the search for possible alternative valid checksum somewhere in the sequence to have always failed
//        Adjusted Deviation, data rate, AGC settings for PMV107J (US - 315MHz) as recommended by Andrey Oleynik to improve reception


#define VERSION "11.8"


#include <SPI.h>

#include "configs.h"
#include "globals.h"
#include <Ticker.h>


#include "CommonFunctionDeclarations.h"

#ifdef USE_LCDDISPLAY
   #ifdef USE_1_INCH_YB_I2C_DISPLAY 
      #include <Wire.h>
      #include "display.h"
   #elif USE_2_INCH_ST7735_DISPLAY 
      #include "display_128x160.h"
   #elif USE_2_INCH_ST7789_DISPLAY
      #include "display_240x240round.h"
   #elif USE_24_INCH_ILI9341_DISPLAY
      #include "display_240x320.h"
   #endif
#endif

#ifdef ENABLE_AUDIBLE_ALARM
   #include "AudibleAlarm.h"
#endif

#ifdef Toyota_PMV_C210
   #include "Toyota_PMV_C210.h"
#elif Toyota_PMV_107J
   #include "Toyota_PMV_107J.h"
#elif defined(Toyota_TRW_C070) || defined(Hyundai_i35)
   #include "Toyota_TRW_C070.h"
#elif defined Schrader_C1100
   #include "Schrader_C1100.h"
#elif defined Schrader_A9054100
   #include "Schrader_A9054100.h"
#elif NissanLeaf
   #include "Renault.h"
#elif Dacia
   #include "Renault.h"
#elif  Renault
   #include "Renault.h"
#elif Citroen
   #include "Citroen.h"
#elif Ford
   #include "Ford.h"
#elif  Jansite
   #include "Jansite.h"
#elif  JansiteSolar
   #include "JansiteSolar.h"
#elif PontiacG82009
   #include "PontiacG82009.h"
#elif TruckSolar
   #include "TruckSolar.h"
#elif Subaru
   #include "Subaru.h"
#endif

#include "cc1101.h"
#include "Common.h"

Ticker displayflashtimer(DisplayTimerExpired,NOBLANK_MS, 0, MILLIS);
Ticker SignalRefreshTimer(SignalRefreshRequired, SIGNALREFRESHTIMING, 0, MILLIS);

void UpdateTimers()
{
  #ifdef USE_LCDDISPLAY
     SignalRefreshTimer.update();
  #endif
  
  #if defined(ENABLE_PRESSURE_ALARMS) || defined(ENABLE_TEMPERATURE_ALARMS)
     displayflashtimer.update();
     #ifdef ENABLE_AUDIBLE_ALARM
      if (Audible_Alarm_Running)
      {
         AudibleAlarmSoundTimer.update();  //check the timers
         AudibleAlarmReminderTimer.update();
      }

     #endif
     
  #endif

}

void CheckForScreenUpdates()
{
  UpdateTimers();
  #ifdef USE_LCDDISPLAY


    #if defined(ENABLE_PRESSURE_ALARMS) || defined(ENABLE_TEMPERATURE_ALARMS)
     if (DisplayFlashExpired || (TPMS_Changed == true) || Check_TPMS_Timeouts() || SignalRefreshNeeded )
      {//display update required

          UpdateDisplay();
          if (DisplayFlashExpired)
          {
              DisplayFlashExpired = false;
          }
          TPMS_Changed = false;
          if (SignalRefreshNeeded == true)
          {
             SignalRefreshNeeded = false;
          }
      }
    #else

        if ((TPMS_Changed == true) || Check_TPMS_Timeouts() || SignalRefreshNeeded )
        {
          UpdateDisplay();
          TPMS_Changed = false;
          if (SignalRefreshNeeded == true)
          {
             SignalRefreshNeeded = false;
          }
        } 
          

    #endif


    
  #endif
}

void SendDebug(String Mess)
{
  Serial.println(Mess);
}




void setup() {

  uint8_t resp;
  uint8_t regfail;

  //SPI CC1101 chip select set up
  pinMode(CC1101_CS, OUTPUT);
  digitalWrite(CC1101_CS, HIGH);


  Serial.begin(115200);




  pinMode(LED_RX, OUTPUT);
  pinMode(RXPin, INPUT);
  pinMode(CDPin, INPUT);

  delay(2000);

  #ifdef ENABLE_AUDIBLE_ALARM
    pinMode(AUDIBLE_ALARM_PIN, OUTPUT);
    digitalWrite(AUDIBLE_ALARM_PIN,!Audible_AlarmPin_Active);
    SPI.begin();

     AudibleAlarm(true);  //audible alarm test
     delay(200);
     AudibleAlarm(false);
     delay(300);
     AudibleAlarm(true);  //audible alarm test
     delay(200);
     AudibleAlarm(false);
     delay(500);
     AudibleAlarmReminderTimer.stop();
     delay(800);
  #else
     SPI.begin();
     delay(2000);
  #endif



  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F("########################################################################"));
  Serial.println(F(""));
  Serial.println(F("STARTING..."));
  Serial.print(F("Software version "));
  Serial.println(VERSION);
  Serial.print(F("Configured for processor type "));
  Serial.println(PROC_TYPE);

#ifdef USE_TEST_TIMINGS
   Serial.println(F("Warning: *****   BUILD FOR RUNNING HARD CODED TEST TIMES ONLY - NOT FOR REAL-TIME USE *****"));
#endif


#ifdef USE_LCDDISPLAY
   #ifdef USE_1_INCH_YB_I2C_DISPLAY 
      Serial.println(F("Configured for 0.96in SSD1306 I2C 64x128 OLED display"));
   #elif USE_2_INCH_ST7735_DISPLAY
      Serial.println(F("Configured for 1.8in ST7735 SPI 160x128 TFT display"));
   #elif USE_2_INCH_ST7789_DISPLAY
      Serial.println(F("Configured for 1.28in ST7789 SPI 240x240 TFT round display"));
   #elif USE_24_INCH_ILI9341_DISPLAY
      Serial.println(F("Configured for 2.4in ILI9341 SPI 240x320 TFT display"));
   #else
      Serial.println(F("Warning: LCD selected but no type defined"));
   #endif
#else
   Serial.println(F("No LCD display configured - Serial output only"));
#endif


#ifdef USE_LCDDISPLAY 
  #ifdef USE_1_INCH_YB_I2C_DISPLAY 
    #if USE_ADAFRUIT
      if (!display.begin(SSD1306_EXTERNALVCC, I2C_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        while(1)
        {
          delay(10);// Don't proceed, loop forever
        }
      }
      display.clearDisplay();
      display.display();
    #else
      Wire.begin();
      Wire.setClock(400000L);
      display.begin(&Adafruit128x64, I2C_ADDRESS);
      display.setFont(Adafruit5x7);
      display.clear();
      ShowTitle();
    #endif
    Serial.println(F("SSD1306 initialised OK"));
   #else

   #endif
#endif

  //initialise the CC1101

  Serial.print(F("Resetting CC1101 "));
  uint8_t retrycount = 0;
  while (retrycount < 5)
  {
     Serial.print(F("."));
     CC1101_reset();
     if (readConfigReg(0) == 0x29)
        break;
     retrycount++;
     delay(5);
  }
  Serial.println(F(""));

  if (readConfigReg(0) == 0x29)
  {
    Serial.println(F("CC1101 reset successful"));
  }
  else
  {
    Serial.println(F("CC1101 reset failed. Try rebooting"));
    #ifdef USE_LCDDISPLAY 
       #ifdef USE_2_INCH_ST7735_DISPLAY
          DisplayInit();
          DrawTitle(); 
          DisplayWarning((char *) "CC1101 reset failed", 0, 64);
          DisplayWarning((char *) "Power off/on", 0,80); 
          while(1)
          {
            delay(10);// Don't proceed, loop forever
          }
       #endif
    #endif   
  }


  ConfigureCC1101();
  Serial.print(F("CC1101 configured for "));
  #ifdef US_315MHz
     Serial.print (F("US (315MHz)"));
  #else
     Serial.print (F("UK (433MHz)"));
  #endif

  #ifdef Toyota_PMV_C210
     Serial.println (F(" and PMV-C210 TPMS sensor"));
  #elif Toyota_PMV_107J
     Serial.println (F(" and PMV-107J TPMS sensor"));
  #elif Toyota_TRW_C070
     Serial.println (F(" and TRW-C070 TPMS sensor"));
  #elif Hyundai_i35
     Serial.println (F(" and Hyundai i35 (TRW-C070) TPMS sensor"));
  #elif NissanLeaf
     Serial.println (F(" and Nissan Leaf(Renault) TPMS sensor"));
  #elif Dacia
     Serial.println (F(" and Dacia (Renault) TPMS sensor"));    
  #elif Renault
       #ifdef Zoe
          Serial.println("and Renault Zoe(pre 07/2019 X10) TPMS sensor");
       #else
          Serial.println("and Renault TPMS sensor");
       #endif
  #elif Citroen
     Serial.println (F(" and Citroen TPMS sensor"));
  #elif Ford
     Serial.println (F(" and Ford TPMS sensor"));
  #elif Jansite
     Serial.println (F(" and Jansite TPMS sensor"));
  #elif JansiteSolar
     Serial.println (F(" and Jansite-Solar TPMS sensor"));
  #elif PontiacG82009
     Serial.println (F(" and Pontiac TPMS sensor"));
  #endif

  setIdleState();
  digitalWrite(LED_RX, LED_OFF);

  resp = readStatusReg(CC1101_PARTNUM);
  Serial.print(F("CC1101 Part no: "));
  Serial.println(resp, HEX);

  resp = readStatusReg(CC1101_VERSION);
  Serial.print(F("CC1101 Version: "));
  Serial.println(resp, HEX);

  regfail = VerifyCC1101Config();
  if (regfail > 0)
  {
     Serial.print(F("Config verification fail #"));
     Serial.println(regfail);
  }
  else
  {
     Serial.println(F("Config verification OK"));
  }

  #ifdef USE_LCDDISPLAY 
    #ifdef USE_2_INCH_ST7735_DISPLAY
      ScreenSetup();
    #elif USE_2_INCH_ST7789_DISPLAY
      ScreenSetup();
    #elif USE_24_INCH_ILI9341_DISPLAY
      ScreenSetup();
    #endif
  #endif 





  digitalWrite(LED_RX, LED_ON);

  pinMode(DEBUGPIN, OUTPUT);
  digitalWrite(DEBUGPIN, LOW);




  InitTPMS();

  PrintIDs();


  digitalWrite(LED_RX, LED_OFF);


  //Calibrate();
  LastCalTime = millis();
  DisplayTimer = millis();
  DisplayFlash  = false;
  
  setRxState();
  Flush_RX_FIFO(true);

   #if defined(ENABLE_PRESSURE_ALARMS) || defined(ENABLE_TEMPERATURE_ALARMS)
     displayflashtimer.start();
  #else
     displayflashtimer.stop();
  #endif

  #ifdef USE_LCDDISPLAY
      SignalRefreshTimer.start();
  #endif
}



void loop() {

#ifdef USE_TEST_TIMINGS
  static uint32_t lastts = millis();
#endif


  if (millis() - LastCalTime > CAL_PERIOD_MS)
  {
      setIdleState();  //configuration is set to auto-cal when goimg from Idle to RX
      Calibrate();
      LastCalTime = millis();
      setRxState();      
  }

// check timers...
  UpdateTimers(); 


  InitDataBuffer();


#ifdef USE_TEST_TIMINGS
 
    //Used for hard-coded test time testing only
    if ((millis() - lastts) >= 10000)
    {//run test every 10 seconds
       ReceiveMessage();
       lastts = millis();  //reset 10 second timer
    }
    CheckForScreenUpdates();

#else
  //normal usage

  //wait for carrier status to go low
  while (GetCarrierStatus() == true)
  {
     CheckForScreenUpdates();
  }

  //wait for carrier status to go high  looking for rising edge
  while (GetCarrierStatus() == false)
  {
       //UpdateTimers();
       if (Get_RX_FIFO_Count() > 0)
       {
          //Serial.println("Flushing FIFO");
          Flush_RX_FIFO(true);
       }
       CheckForScreenUpdates();
       delay(1);
  }

  if (GetCarrierStatus() == true)
  { //looks like some data coming in...
    
    ReceiveMessage();

    #ifdef USE_LCDDISPLAY
       CheckForScreenUpdates();
    #endif

  }


#endif



}
