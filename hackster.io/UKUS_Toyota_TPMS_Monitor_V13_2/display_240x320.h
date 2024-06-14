
#include "bitmap.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h>


#if USE_GPIO_Dx == 1
  #define TFT_CS D5  //or gpio 7
  #define TFT_RST D3  //or gpio 29
  #define TFT_DC D4  //or gpio 6
#else
  #ifdef ISARDUINO_ESP32
    #define TFT_CS 22
    #define TFT_RST 27
    #define TFT_DC 21

  #else
    #define TFT_CS 5
    #define TFT_RST 3
    #define TFT_DC 4
  #endif
#endif

//Display Pixel Buffer
#define DB 3

//Tweak Colors
#define ILI9341_ORANGEM 0xF300
#define ILI9341_GREENM  0x129B
//#define ILI9341_GREENM  0x06C5

// Hardware SPI on Feather or other boards
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);


  uint8_t DisplayTimeoutBar(uint32_t TimeSinceLastUpdate)
  {
      int HowCloseToTimeout;
      HowCloseToTimeout = (int16_t)((TimeSinceLastUpdate)/(TPMS_TIMEOUT/5));

      switch(HowCloseToTimeout)
      {
        case 0: 
           //return(FONTBAR_7);
           return(5);
           break;
        case 1: 
           //return(FONTBAR_5);
           return(4);
           break;
        case 2: 
           //return(FONTBAR_3);
           return(3);
           break;
        case 3: 
           //return(FONTBAR_2);
           return(2);
           break;
        case 4: 
           //return(FONTBAR_1);
           return(1);
           break;
        default: 
           //return(FONTBAR_0);
           return(0);
           break;
                      
      }
  }

void PrintFreq()
{
  //display.fillRect(0,0,240,320,ILI9341_BLACK);
  //display.setCursor(118,0);
  display.setCursor(275,18);
  #ifdef US_315MHz
     display.setTextSize(1);
     display.print(F("315 MHz"));
  #else
     display.print(F("433 MHz"));
  #endif
}


  void DrawTitle()
{
  //background header
  display.fillRect(0, 0,320,25 + DB, ILI9341_GREENM);
  //display.fillRect(0, 215,320,25 + DB, ILI9341_GREENM);
    
  //display.setCursor(2,0);
 // display.setCursor(2,0 + DB);
  display.setCursor(80,4 + DB);
  display.setTextColor(ILI9341_BLACK);
  display.setTextSize(2);
    #ifdef NissanLeaf
       display.print(F("Nissan Leaf TPMS"));
    #elif Dacia
       display.print(F("Dacia TPMS"));
    #elif Renault
       #ifdef Zoe
          display.println(F("Ren Zoe(early) TPMS"));
       #else
          display.println(F("Renault TPMS"));
       #endif
    #elif Citroen
       display.print(F("Citroen TPMS"));
    #elif Jansite
       display.print(F("Jansite TPMS"));
    #elif JansiteSolar
       display.print(F("JSolar TPMS"));
    #elif Ford
       display.print(F("Ford F250 TPMS"));
    #elif PontiacG82009
       display.print(F("Porsche Carerra"));
    #elif Hyundai_i35
       display.print(F("Hyundai i35"));
    #elif Schrader_C1100
       display.print(F("Hyundai Tucson"));
    #elif Schrader_A9054100
       display.print(F("Smart ForTwo"));
    #elif Subaru
       display.print(F("Subaru TPMS")); 
    #elif Mazda3
       display.print(F("Mazda 3 TPMS")); 
    #elif Audi_Etron
       display.println(F("Audi E-tron"));
    #elif BMW5
       display.println(F("BMW 5"));
    #else
       display.print(F("Undefined TPMS"));
    #endif
  PrintFreq();  
  display.setCursor(56,8 + DB);
  display.setTextColor(ILI9341_BLACK);
  display.setTextSize(1);
  display.print(" ");
  //display.print(VERSION);
}

void DrawBackground()
{
     int LineSplitCol = 136;
     
     //display.drawBitmap(0, 0, car_bmp_240x240_car, 240, 240, ILI9341_WHITE);
     //display.drawLine(8,LineSplitCol,115,LineSplitCol,ILI9341_ORANGEM);
     //display.drawLine(125,LineSplitCol,232,LineSplitCol,ILI9341_ORANGEM);
     display.drawLine(5,LineSplitCol,150,LineSplitCol,ILI9341_ORANGEM);
     display.drawLine(170,LineSplitCol,315,LineSplitCol,ILI9341_ORANGEM);

}

void DrawSignal(uint8_t Level, int16_t x, int16_t y)
{
 
       
  if (Level >=1)
  {
     display.fillRect(x+8, y ,4,4, ILI9341_GREENM);
  }
  else
  {
     display.fillRect(x+8, y ,4,4, ILI9341_BLACK);
     display.drawRect(x+8, y ,4,4, ILI9341_GREENM);
  }
       
  if (Level >=2)
  {
     display.fillRect(x+11, y -2,4,6, ILI9341_GREENM);
  }
  else
  {
     display.fillRect(x+11, y -2,4,6, ILI9341_BLACK);
     display.drawRect(x+11, y -2,4,6, ILI9341_GREENM);
  }
       
  if (Level >=3)
  {
     display.fillRect(x+14, y -4,4,8, ILI9341_GREENM);
  }
  else
  {
     display.fillRect(x+14, y -4,4,8, ILI9341_BLACK);
     display.drawRect(x+14, y -4,4,8, ILI9341_GREENM);
  }
  
       
  if (Level >=4)
  {
     display.fillRect(x+17, y-6,4,10, ILI9341_GREENM);
  }
  else
  {
     display.fillRect(x+17, y -6,4,10, ILI9341_BLACK);
     display.drawRect(x+17, y -6,4,10, ILI9341_GREENM);
  }
       
  if (Level >=5)
  {
     display.fillRect(x+20, y -8,4,12, ILI9341_GREENM);
  }
  else
  {
     display.fillRect(x+20, y -8,4,12, ILI9341_BLACK);
     display.drawRect(x+20, y -8,4,12, ILI9341_GREENM);
  }  
      
}

uint32_t testText()
{
  display.fillScreen(ILI9341_BLACK);
  uint32_t start = micros();
  display.setCursor(0, 0);
  display.setTextColor(ILI9341_WHITE);
  display.setTextSize(1);
  display.println("Hello World!");
  display.setTextColor(ILI9341_YELLOW);
  display.setTextSize(2);
  display.println(1234.56);
  display.setTextColor(ILI9341_RED);
  display.setTextSize(3);
  display.println(0xDEADBEEF, HEX);
  display.println();
  display.setTextColor(ILI9341_GREEN);
  display.setTextSize(5);
  display.println("Groop");
  display.setTextSize(2);
  display.println("I implore thee,");
  display.setTextSize(1);
  display.println("my foonting turlingdromes.");
  display.println("And hooptiously drangle me");
  display.println("with crinkly bindlewurdles,");
  display.println("Or I will rend thee");
  display.println("in the gobberwarts");
  display.println("with my blurglecruncheon,");
  display.println("see if I don't!");

  delay(5000);
  return micros() - start;
}

void DisplayInit()
{
    
  //display.initR(INITR_BLACKTAB);   // initialize a ILI9341S chip, black tab
  //display.setRotation(3);

  //writeRegister (0x51, 0);
  //testText();
  display.setTextWrap(false);
  display.begin();
  display.invertDisplay(0);
  display.setRotation(3);
  display.fillScreen(ILI9341_BLACK);

}




  int GetBlockStartX(int DisplayIndex)
  {
  

      switch (DisplayIndex)
      {
        case 0:
          return(5);
          break;
        case 1:
          return(170);
          break;
        case 2:
          return(5);
          break;
        case 3:
          return(170);
          break;
      }
  }

  
  int GetBlockStartY(int DisplayIndex)
  {
  

      switch (DisplayIndex)
      {
        case 0:
          return(38);
          break;
        case 1:
          return(38);
          break;
        case 2:
          return(144);
          break;
        case 3:
          return(144);
          break;
          
      }
  }



  void WheelShow(int16_t DisplayIndex,bool Warning)
  {
     int16_t x, y;
     uint16_t col;
     
     switch (DisplayIndex)
     {
        case 0:
                x = 89;
                y = 74;
                break;
        case 1:
                x = 152;
                y = 74;
                break;
        case 2:
                x = 89;
                y = 141;
                break;
        case 3:
                x = 152;
                y = 141;
                break;
        default:
                x = 340;
                y = 240;
                break;               
     }
     

     if (Warning == true)
     {
        col = ILI9341_RED;   
     }
     else
     {
        col = ILI9341_WHITE;   
     }

     //display.fillRect(x,y,7,19,col);
     

     
     
  }

    void ClearDisplayBlock(int16_t DisplayIndex)
  {
     int16_t x,y;

     x = GetBlockStartX(DisplayIndex);
     y = GetBlockStartY(DisplayIndex);

     //display.fillRect(x,y,56,8,ILI9341_BLACK);
     display.fillRect(x+0,y+8,144,85,ILI9341_BLACK);
     WheelShow(DisplayIndex,false);
     
  }

  void UpdateBlock(int16_t DisplayIndex,int16_t i)
  {
        int16_t x,y;
        char s[6], sID[9];
        uint8_t sig;
        char t;


        if ((TPMS[i].LowPressure == true) || (TPMS[i].HighPressure == true))
        {
          if (DisplayFlash)
          {
             strcpy(s,"    ");
             WheelShow(DisplayIndex,true);
          }
          else
          {
             #ifdef DISPLAY_PRESSURE_AS_BAR
                dtostrf(PSI_To_BAR(TPMS[i].TPMS_Pressure), 4, 2, s);
             #elif DISPLAY_PRESSURE_AS_KPA
                dtostrf(PSI_To_KPA(TPMS[i].TPMS_Pressure), 4, 0, s);  //rounded to integer value
             #else
                dtostrf(TPMS[i].TPMS_Pressure, 3, 1, s);
             #endif
             WheelShow(DisplayIndex,true);  
          }
        }
        else
        {
           #ifdef DISPLAY_PRESSURE_AS_BAR
              dtostrf(PSI_To_BAR(TPMS[i].TPMS_Pressure), 4, 2, s);
           #elif DISPLAY_PRESSURE_AS_KPA
              dtostrf(PSI_To_KPA(TPMS[i].TPMS_Pressure), 4, 0, s);  //rounded to integer value
           #else
              dtostrf(TPMS[i].TPMS_Pressure, 3, 1, s);
           #endif
           WheelShow(DisplayIndex,false);
        }

        
        x = GetBlockStartX(DisplayIndex);
        y = GetBlockStartY(DisplayIndex);
        
        //ID first
        display.setCursor(x+50, y);
        display.setTextSize(1);
        display.setTextColor(ILI9341_GREENM,ILI9341_BLACK );
        sprintf(sID,"%08lX",TPMS[i].TPMS_ID);
        //display.print(TPMS[i].TPMS_ID,HEX);
        display.print(sID);
                        
        //tyre pressure
        display.setCursor(x,y + 18);
        display.setTextSize(6);
        display.setTextColor(ILI9341_ORANGEM,ILI9341_BLACK);
        display.print(s);

        //temperature
        display.setCursor(x + 30, y + 67);
        display.setTextSize(3);
        display.setTextColor(ILI9341_ORANGEM,ILI9341_BLACK);

        #ifdef DISPLAY_TEMP_AS_FAHRENHEIT
           t = 'F';
        #else
           t = 'C';
        #endif

        
        if (TPMS[i].TPMS_Temperature == NO_VALID_TEMPERATURE)
        {
           display.print("  ---  ");
        }
        else
        {
          if ((TPMS[i].LowTemperature == true) || (TPMS[i].HighTemperature == true))
          {
            if (DisplayFlash)
            {
               strcpy(s,"     ");
               display.print(s); 
            }
            else
            {
               #ifdef DISPLAY_TEMP_AS_FAHRENHEIT
                  dtostrf(DegC_To_DegF(TPMS[i].TPMS_Temperature), 2, 1, s);
               #else
                  dtostrf(TPMS[i].TPMS_Temperature, 2, 1, s);
               #endif
               display.print(s); 
               display.print(t);
            }
          }
          else
          {
               #ifdef DISPLAY_TEMP_AS_FAHRENHEIT
                  dtostrf(DegC_To_DegF(TPMS[i].TPMS_Temperature), 2, 1, s);
               #else
                  dtostrf(TPMS[i].TPMS_Temperature, 2, 1, s);
               #endif
               display.print(s); 
               display.print(t);
          }
        }
        
        //display vertical bars showing how long since last update 5 bars = recent 1 bar = nearing timeout (at timeout it will be removed from display altogether)        
        sig = DisplayTimeoutBar(millis() - TPMS[i].lastupdated);
        DrawSignal(sig, x+15,y+4);

  }

  void UpdateDisplay()
  {
    int16_t i;

    int16_t DisplayIndex;

        


    //for (i = 0; i < 4; i++)
    for (i = 0; i < TYRECOUNT; i++)   
    {
     
      if (TPMS[i].TPMS_ID != 0)
      {
          //Only update the areas which need it to keep the timing overheads down
         DisplayIndex = GetDisplayIndexFromTyreIndex(i);
         if (DisplayIndex >= 0)
         {
           UpdateBlock(DisplayIndex,i);
           if ((bitRead(TPMSChangeBits,i) == 1))
           {
              bitClear(TPMSChangeBits,i);
           }
         }

      }


    }


  }

  void DisplayWarning(char* msg, int16_t x, int16_t y)
  {
        display.setCursor(x ,y);
        display.setTextSize(1);
        display.print(msg);
    
  }

  void ScreenSetup()
  {
      DisplayInit();
      DrawBackground();
      DrawTitle();  
  }
