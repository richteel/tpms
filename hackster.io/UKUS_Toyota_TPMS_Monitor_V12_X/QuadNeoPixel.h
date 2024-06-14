#define NUMPIXELS 4

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

extern bool IsOutOfPressureLimits(int16_t TyreIndex);
extern bool IsOutOfTemperatureLimits(int16_t TyreIndex);

Adafruit_NeoPixel pixels(NUMPIXELS, QUADLEDPIN, NEO_GRB + NEO_KHZ800);

void InitQuadLED()
{
     pixels.begin();
     pixels.clear();
     pixels.setBrightness(30);
     pixels.show();
}

uint8_t TranslateIndex2LED(uint8_t index)
{
   if (index <= 1)
      return(index);
   if (index == 2)
      return(3);
   if (index == 3)
      return(2);
   return(index);
}

void UpdateQuadLED()
{
   uint8_t i;
   uint32_t TimeSinceLastUpdate_ms;
   uint8_t RedLevel, BlueLevel, GreenLevel;
   
    
  //clear any data not updated in the last 15 minutes
  for (i = 0; i < 4; i++)
  {

   if (IsOutOfPressureLimits(i))
   {
      RedLevel = 255;
      GreenLevel = 0;
      BlueLevel = 0;
      pixels.setPixelColor(TranslateIndex2LED(i),RedLevel,GreenLevel,BlueLevel);  
   }
   else
   {
      if (IsOutOfTemperatureLimits(i))
      {
         RedLevel = 128;
         GreenLevel = 128;
         BlueLevel = 0; 
         pixels.setPixelColor(TranslateIndex2LED(i),RedLevel,GreenLevel,BlueLevel);       
      }
      else
      {
        TimeSinceLastUpdate_ms = millis() - TPMS[i].lastupdated;
        if ((TPMS[i].TPMS_ID != 0) && (TimeSinceLastUpdate_ms > TPMS_TIMEOUT))
        {
           pixels.setPixelColor(TranslateIndex2LED(i),0,0,0);  //turn off led
        }
        else
        {
           if (TPMS[i].TPMS_ID != 0)
           {

              //GreenLevel = map(millis() - TPMS[i].lastupdated, TPMS_TIMEOUT,0 ,0,255);
              if (TimeSinceLastUpdate_ms < 240000)
              {
                GreenLevel = 255;
                BlueLevel = 0;
              }
              else
              {
                if (TimeSinceLastUpdate_ms > 480000)
                {
                   GreenLevel = 0;
                   BlueLevel = 255;              
                }
                else
                {
                   BlueLevel = map(TimeSinceLastUpdate_ms, QUADNEOLED_T1,QUADNEOLED_T2,0,255);
                   GreenLevel = map(TimeSinceLastUpdate_ms, QUADNEOLED_T1,QUADNEOLED_T2,255,0);            
                }
                
              }
              pixels.setPixelColor(TranslateIndex2LED(i),0,GreenLevel,BlueLevel);  //set LED green 
           }
           else
           {
              pixels.setPixelColor(TranslateIndex2LED(i),0,0,0);  //turn off led   
           }
        }

      }
   }

 }
  pixels.show();  
}
