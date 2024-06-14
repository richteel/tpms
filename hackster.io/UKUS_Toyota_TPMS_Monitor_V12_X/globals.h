
#define USE_HW_CD 1
//#define USE_TEST_TIMINGS 1

//#define WIFI_ENABLED 1  //for ESP32 only
//#define MQTT_ENABLED 1  //for ESP32 only


#define SHOWVALIDTPMS 1
//#define SHOWDEBUGINFO 1
//#define IGNORECHECKSUMERRORS 1
//#define ALWAYSSHOWTIMINGS 1
//#define SPECIFIC_IDS_ONLY 1


#define I2C_ADDRESS 0x3C




#define TPMS_TIMEOUT 900000 //(15 * 60 * 1000)  15 minutes
#define CAL_PERIOD_MS 3600000 //60 * 60 * 1000  60 minutes

#define FONTBAR_7 123
#define FONTBAR_5 124
#define FONTBAR_3 125
#define FONTBAR_2 126
#define FONTBAR_1 127
#define FONTBAR_0 32


//#ifdef INCLUDESPARETYRE  - nolonger used. If no spare with TPMS, just set the ID to 0xFFFFFFF
//  #define TYRECOUNT 5
//#else
//  #define TYRECOUNT 4
//#endif

#ifdef INCLUDE_WINTER_SET
   #define TYRECOUNT 10
#else
   #define TYRECOUNT 5
#endif

#define PSI2BAR 14.504
#define KPA2PSI 6.895

#define DEGC_TO_KELVIN 273.15

#define NO_VALID_TEMPERATURE -99

#define BITISLONG 1
#define BITISSHORT 0
#define BITISSYNC 2
#define BITISUNDEFINED -1

// hardware pin configuration

#if defined(ARDUINO_ESP32_DEV) || defined(ARDUINO_FEATHER_ESP32) || defined(ARDUINO_CoreESP32) || defined(ARDUINO_FEATHER_ESP32)
  #define ISARDUINO_ESP32 1
#endif

#ifdef ARDUINO_AVR_PROMICRO
   #define PROC_TYPE "Arduino Pro Micro"
   #define USE_GPIO_Dx 0
   const int16_t RXPin = 7;   //must be an ext interrupt pin
   const int16_t CDPin = 9;  //if wired, define 'USE_HW_CD' above, otherwise CD pin status is received over SPI
   const int16_t CC1101_CS = 10;  // Define the Chip Select pin
   const int16_t AUDIBLE_ALARM_PIN = 8;
   const int16_t DEBUGPIN = 6;
   const int16_t LED_RX = LED_BUILTIN;
   const int16_t MAXBITS =200;
   const int16_t MAXTIMINGS = 255;
   #define LED_OFF HIGH
   #define LED_ON LOW
#elif ARDUINO_AVR_NANO
   #define PROC_TYPE "Arduino Nano"
   #define USE_GPIO_Dx 0
   #error Arduino Nano has insufficient RAM (only 2k) to run this program. Switch to another board type e.g. Arduino Nano 33 IOT. 
//   const int RXPin = 2;   //must be an ext interrupt pin
//   const int CDPin = 9;  //if wired, define 'USE_HW_CD' above, otherwise CD pin status is received over SPI
//   const int CC1101_CS = 10;  // Define the Chip Select pin
//   const int AUDIBLE_ALARM_PIN = 8;
//   const int DEBUGPIN = 6;
//   const int LED_RX = LED_BUILTIN;
//   const int MAXBITS = 200;
//   const int MAXTIMINGS = 255;
#elif ARDUINO_SEEED_XIAO_M0
   #define PROC_TYPE "Seeeduino Xiao"
   #define USE_GPIO_Dx 0
   const int16_t RXPin = 1;   //must be an ext interrupt pin
   const int16_t CDPin = 0;  //if wired, define 'USE_HW_CD' above, otherwise CD pin status is received over SPI
   const int16_t CC1101_CS = 2;  // Define the Chip Select pin
   const int16_t AUDIBLE_ALARM_PIN = 7;
   const int16_t DEBUGPIN = 12;  //use the RX LED pin
   const int16_t LED_RX = LED_BUILTIN;
   const int16_t MAXBITS = 1000;
   const int16_t MAXTIMINGS = 900;
   #define LED_OFF HIGH
   #define LED_ON LOW
#elif ARDUINO_SEEED_XIAO_RP2040
   #define PROC_TYPE "Seeeduino Xiao RP2040"
   #define USE_GPIO_Dx 1
   const int16_t RXPin = D1;   //must be an ext interrupt pin
   const int16_t CDPin = D0;  //if wired, define 'USE_HW_CD' above, otherwise CD pin status is received over SPI
   const int16_t CC1101_CS = D2;  // Define the Chip Select pin
   const int16_t AUDIBLE_ALARM_PIN = D7;
   const int16_t DEBUGPIN = 16;  //use the TX LED pin
   const int16_t LED_RX = 17;
   const int16_t MAXBITS = 1000;
   const int16_t MAXTIMINGS = 900;
   #define LED_OFF HIGH
   #define LED_ON LOW
#elif ARDUINO_SAMD_NANO_33_IOT
   #define PROC_TYPE "Arduino Nano 33 IOT"
   #define USE_GPIO_Dx 0
   const int16_t RXPin = 2;   //must be an ext interrupt pin
   const int16_t CDPin = 9;  //if wired, define 'USE_HW_CD' above, otherwise CD pin status is received over SPI
   const int16_t CC1101_CS = 10;  // Define the Chip Select pin
   const int16_t AUDIBLE_ALARM_PIN = 8;
   const int16_t DEBUGPIN = 6;
   const int16_t LED_RX = LED_BUILTIN;
   const int16_t MAXBITS = 1000;
   const int16_t MAXTIMINGS = 900;
   #define LED_OFF HIGH
   #define LED_ON LOW
   #include <avr/dtostrf.h>
#elif ARDUINO_AVR_MEGA2560
   #define PROC_TYPE "Mega 256"
   #define USE_GPIO_Dx 0
   const int16_t RXPin = 2;   //must be an ext interrupt pin
   const int16_t CDPin = 3;  //if wired, define 'USE_HW_CD' above, otherwise CD pin status is received over SPI
   const int16_t CC1101_CS = 4;  // Define the Chip Select pin
   const int16_t AUDIBLE_ALARM_PIN = 5;
   const int16_t DEBUGPIN = 6;  //use the TX LED pin
   const int16_t LED_RX = LED_BUILTIN;
   const int16_t MAXBITS = 1000;
   const int16_t MAXTIMINGS = 900;
   #define LED_OFF HIGH
   #define LED_ON LOW
#elif ARDUINO_AVR_ITSYBITSY32U4_3V
   #define PROC_TYPE "ITSYBITSY32U4_3V"
   #define USE_GPIO_Dx 0
   const int16_t RXPin = 7;   //must be an ext interrupt pin
   const int16_t CDPin = 9;  //if wired, define 'USE_HW_CD' above, otherwise CD pin status is received over SPI
   const int16_t CC1101_CS = 10;  // Define the Chip Select pin
   const int16_t AUDIBLE_ALARM_PIN = 8;
   const int16_t DEBUGPIN = 6;  //use the TX LED pin
   const int16_t LED_RX = LED_BUILTIN;
   const int16_t MAXBITS = 200;
   const int16_t MAXTIMINGS = 255;
   #define LED_OFF HIGH
   #define LED_ON LOW
#elif ISARDUINO_ESP32
   #define PROC_TYPE "ESP32 Board"
   //#define USE_GPIO_Dx 1
   const int16_t RXPin = 33;   //must be an ext interrupt pin
   const int16_t CDPin = 25;  //if wired, define 'USE_HW_CD' above, otherwise CD pin status is received over SPI
   const int16_t CC1101_CS = 26;  // Define the Chip Select pin
   const int16_t AUDIBLE_ALARM_PIN = 16;
   const int16_t DEBUGPIN = 32;  
   const int16_t LED_RX = 2;
   #define ENABLE_QUADLED 1  //requires quad neo pixel hardware
   const int16_t QUADLEDPIN = 13;
   const int16_t MAXBITS = 1000;
   const int16_t MAXTIMINGS = 900;
   #define LED_OFF LOW
   #define LED_ON HIGH
   //portMUX_TYPE synch = portMUX_INITIALIZER_UNLOCKED;
#else
   #error No configuration set up for this processor type in globals.h
#endif

#define AUDIBLE_ALARM_ON_TIME_MS 500
#define AUDIBLE_ALARM_OFF_TIME_MS 1000
#define AUDIBLE_ALARM_ONOFF_COUNT 5
#define AUDIBLE_ALARM_REMINDER_TIME_MS 1800000L //30 x 60 x 1000 (repeat alarm after 30 minutes) - Set to zero for no reminders. Note: value must be > (AUDIBLE_ALARM_ON_TIME_MS + AUDIBLE_ALARM_OFF_TIME_MS) * AUDIBLE_ALARM_ONOFF_COUNT




volatile static uint32_t LastEdgeTime_us = 0;

volatile static bool ValidBlock = false;
volatile static bool WaitingFirstEdge = true;
volatile uint16_t Timings[MAXTIMINGS+1];
volatile bool FirstEdgeIsHighToLow;
volatile uint16_t BaseBitCount = 0;
volatile bool TimingsAreValid = false;
uint16_t ValidTimingsStart;


volatile uint16_t TimingsIndex = 0;
uint16_t CheckIndex = 0;
bool SyncFound = false;
uint32_t CD_Width;
int16_t StartDataIndex = 0;
bool TPMS_Changed = false;
bool Pressure_Alarm_Active = false;
bool Temperature_Alarm_Active = false;
bool Audible_Alarm_On = false;
bool Audible_AlarmPin_Active = LOW;
int16_t Audible_Alarm_Cycle_Countdown = 0;
bool Audible_Alarm_Running = false;

uint32_t DisplayTimer =0;
boolean DisplayFlash  = false;
boolean DisplayFlashExpired = false;
boolean SignalRefreshNeeded = false;
//const uint32_t  DISPLAYFLASHREFRESHTIMING = 1000;  //pressures warning flash rate
const uint16_t NOBLANK_MS = 1500;  //pressures warning flash rate (on time)
const uint16_t BLANK_MS = 500;  //pressures warning flash rate (off time)
const uint32_t  SIGNALREFRESHTIMING = 20000;  //force screen update so that signal bar can be updated if needed
const uint32_t QUADLEDREFRESHTIMING = 5000;
int8_t TPMSChangeBits = 0;


bool IncomingBits[MAXBITS]; 
bool IntIncomingBits[MAXBITS]; 
bool ManchesterDecodedBits[MAXBITS/2 + 2];
uint16_t ManchesterBitCount = 0;
uint16_t BitIndex = 0;
uint16_t IntBitIndex = 0;
int16_t BitCount = 0;


uint16_t FreqOffset;
uint16_t DemodLinkQuality;
int16_t RSSIvalue;
uint16_t FreqOffsetAcc = 0;
uint32_t LastCalTime;
char Ref[3];

int16_t RawCount = 0;
//byte ManchesterRX[64];  //holds received Manchester byte message (converted from the rawdata)
uint8_t RXBytes[20];  //holds the raw incoming databytes from the CC1101 serial port
int16_t RXByteCount;
uint32_t IncomingAddress;

//function declataions
extern bool ValidateTimings();
extern bool ReceiveMessage();
extern void DecodeTPMS();



//this table (and its order define known TPMS IDs so that they their values are always displayed in the same order
const uint32_t  IDLookup[] =
{
  FRONT_LEFT, FRONT_RIGHT, 
  REAR_LEFT, REAR_RIGHT, 
  SPARE,
  WINTER_FRONT_LEFT, WINTER_FRONT_RIGHT, 
  WINTER_REAR_LEFT, WINTER_REAR_RIGHT, 
  WINTER_SPARE,  
};





  ////CRCTable
  const unsigned char PROGMEM CRC8_Poly_07_crctable2[] =
  {
  
      0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15, 0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
      0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65, 0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
      0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5, 0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
      0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85, 0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
      0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2, 0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
      0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2, 0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
      0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32, 0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
      0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42, 0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
      0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C, 0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
      0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC, 0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
      0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C, 0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
      0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C, 0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
      0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B, 0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
      0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B, 0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
      0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB, 0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
      0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB, 0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
  };

  const unsigned char PROGMEM CRC8_Poly_13_crctable2[] =
  {
  
        0x00, 0x13, 0x26, 0x35, 0x4C, 0x5F, 0x6A, 0x79, 0x98, 0x8B, 0xBE, 0xAD, 0xD4, 0xC7, 0xF2, 0xE1,
        0x23, 0x30, 0x05, 0x16, 0x6F, 0x7C, 0x49, 0x5A, 0xBB, 0xA8, 0x9D, 0x8E, 0xF7, 0xE4, 0xD1, 0xC2,
        0x46, 0x55, 0x60, 0x73, 0x0A, 0x19, 0x2C, 0x3F, 0xDE, 0xCD, 0xF8, 0xEB, 0x92, 0x81, 0xB4, 0xA7,
        0x65, 0x76, 0x43, 0x50, 0x29, 0x3A, 0x0F, 0x1C, 0xFD, 0xEE, 0xDB, 0xC8, 0xB1, 0xA2, 0x97, 0x84,
        0x8C, 0x9F, 0xAA, 0xB9, 0xC0, 0xD3, 0xE6, 0xF5, 0x14, 0x07, 0x32, 0x21, 0x58, 0x4B, 0x7E, 0x6D,
        0xAF, 0xBC, 0x89, 0x9A, 0xE3, 0xF0, 0xC5, 0xD6, 0x37, 0x24, 0x11, 0x02, 0x7B, 0x68, 0x5D, 0x4E,
        0xCA, 0xD9, 0xEC, 0xFF, 0x86, 0x95, 0xA0, 0xB3, 0x52, 0x41, 0x74, 0x67, 0x1E, 0x0D, 0x38, 0x2B,
        0xE9, 0xFA, 0xCF, 0xDC, 0xA5, 0xB6, 0x83, 0x90, 0x71, 0x62, 0x57, 0x44, 0x3D, 0x2E, 0x1B, 0x08,
        0x0B, 0x18, 0x2D, 0x3E, 0x47, 0x54, 0x61, 0x72, 0x93, 0x80, 0xB5, 0xA6, 0xDF, 0xCC, 0xF9, 0xEA,
        0x28, 0x3B, 0x0E, 0x1D, 0x64, 0x77, 0x42, 0x51, 0xB0, 0xA3, 0x96, 0x85, 0xFC, 0xEF, 0xDA, 0xC9,
        0x4D, 0x5E, 0x6B, 0x78, 0x01, 0x12, 0x27, 0x34, 0xD5, 0xC6, 0xF3, 0xE0, 0x99, 0x8A, 0xBF, 0xAC,
        0x6E, 0x7D, 0x48, 0x5B, 0x22, 0x31, 0x04, 0x17, 0xF6, 0xE5, 0xD0, 0xC3, 0xBA, 0xA9, 0x9C, 0x8F,
        0x87, 0x94, 0xA1, 0xB2, 0xCB, 0xD8, 0xED, 0xFE, 0x1F, 0x0C, 0x39, 0x2A, 0x53, 0x40, 0x75, 0x66,
        0xA4, 0xB7, 0x82, 0x91, 0xE8, 0xFB, 0xCE, 0xDD, 0x3C, 0x2F, 0x1A, 0x09, 0x70, 0x63, 0x56, 0x45,
        0xC1, 0xD2, 0xE7, 0xF4, 0x8D, 0x9E, 0xAB, 0xB8, 0x59, 0x4A, 0x7F, 0x6C, 0x15, 0x06, 0x33, 0x20,
        0xE2, 0xF1, 0xC4, 0xD7, 0xAE, 0xBD, 0x88, 0x9B, 0x7A, 0x69, 0x5C, 0x4F, 0x36, 0x25, 0x10, 0x03
  };

struct TPMS_entry
{
  uint32_t TPMS_ID;
  uint32_t lastupdated;
  uint16_t TPMS_Status;
  double TPMS_Pressure;
  float TPMS_Temperature;
  float TPMS_LowTemperatureLimit;
  float TPMS_HighTemperatureLimit;
  double TPMS_LowPressureLimit;
  double TPMS_HighPressureLimit;
  boolean LowPressure;
  boolean HighPressure;
  boolean LowTemperature;
  boolean HighTemperature;
  int16_t RSSIdBm;
  boolean AudibleAlarmActive;
} TPMS[TYRECOUNT];


enum RXStates
{
  Waiting_Byte33 = 0,
  Got_Byte33,
  Got_Byte55,
  Got_Byte53,
  Manch1,
  Manch2
};


//following tables useful for testing/debugging the software without the need to receive actual hardware data
//can be turned on/off using the #define USE_TEST_TIMINGS at the top of this include file

#ifdef Toyota_PMV_C210 

   #ifdef UK_433MHz
//    const uint16_t TestTimings[] =
//      {
//        24,264,104,448,48,200,96,104,96,96,56,48,48,48,56,48,96,48,56,96,96,104,48,48,48,56,96,48,
//        48,56,56,40,48,56,48,96,96,104,96,48,56,96,48,48,56,48,96,104,48,48,96,56,48,96,104,48,48,
//        48,48,104,96,104,96,96,56,48,96,56,48,48,48,48,48,104,96,56,48,48,48,48,56,48,48,48,48,56,
//        48,48,56,40,56,48,48,96,104,48,48,48,56,48,48,48,56,48,48,96,104,96,48,56,96,104,56,56,104,
//        96,408
//      };

      const uint16_t TestTimings[] =
      {
      52,56,44,56,44,52,48,52,100,196,96,100,104,96,56,40,60,40,60,44,52,44,108,44,52,92,112,88,56,44,52,48,104,96,96,100,104,44,56,92,104,48,52,96,104,44,56,92,56,44,104,44,56,92,104,48,52,44,60,40,60,92,104,92,48,52,100,52,44,52,56,100,92,100,52,52,48,48,104,48,48,100,92,56,52,48,52,44,52,48,52,96,100,100,48,48,52,56,48,44,100,56,48,44,56,92,48,52,56,44,96,52,56,44,56,44,52
      };
      
       const bool FirstTimingIsLow = true;
   #endif


   
#elif Renault 

   #ifdef UK_433MHz
//    const uint16_t TestTimings[] =
//      {
//       
//        350,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,100,50,
//        50,50,50,100,100,50,50,100,50,50,100,100,
//        100,100,50,50,50,50,100,100,100,100,
//        50,50,100,50,50,100,100,100,50,50,50,50,
//        100,50,50,50,50,50,50,100,50,50,100,50,
//        50,50,50,100,100,100,100,50,50,50,50,100,
//        100,50,50,50,50,50,50,100,100,100,100,
//        50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,
//        50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,
//        50,100,100,50,50,50,50,50,50,50,50,50,50,50,
//        300,50,50,50,50,50
//      };
//    const bool FirstTimingIsLow = true;
//   #endif



    const uint16_t TestTimings[] =
      {
          364,60,44,56,52,52,52,52,52,52,52,52,52,52,52,56,52,
          52,52,52,52,52,52,52,52,52,52,52,52,104,52,52,52,52,
          104,108,52,52,104,52,52,104,104,104,104,104,52,52,52,
          52,108,52,52,52,52,52,52,104,52,52,104,104,52,52,104,
          52,56,104,52,52,104,52,52,104,52,52,52,52,104,52,52,
          104,108,104,52,52,52,52,52,52,104,52,52,52,52,104,108,
          100,108,52,52,104,52,52,52,52,52,52,52,52,52,52,52,
          52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,
          52,52,104,52,56,104,52,52,104,52,52,52,52,104,264      
      };
       const bool FirstTimingIsLow = true;
   #endif


   
#elif Citroen 

   #ifdef UK_433MHz
    const uint16_t TestTimings[] =
      {
         350,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,100,
         100,50,50,50,50,100,50,50,50,50,100,50,50,
         100,100,50,50,50,50,100,50,50,100,50,50,50,
         50,50,50,50,50,50,50,50,50,100,100,100,100,
         50,50,50,50,50,50,50,50,100,100,50,50,50,50,
         100,100,50,50,50,50,100,100,100,50,50,100,
         100,100,50,50,50,50,50,50,50,50,50,50,50,50,
         100,100,50,50,50,50,50,50,50,50,50,50,100,
         100,50,50,50,50,100,50,50,50,50,100,50,50,
         50,50,50,50,50,50,50,50,50,50,100,100,50,
         50,50,50,50,50,100,50,50,50,50,100,50,
         300,50,50,50,50,50
      };
       const bool FirstTimingIsLow = true;
   #endif

   
      
#elif Toyota_PMV_107J

   #ifdef US_315MHz
//    const uint16_t TestTimings[] =
//      {
//        32,52,152,52,100,708,556,200,204,204,100,100,204,200,104,100,200,204,200,204,204,100,100,
//        100,100,204,204,100,100,100,100,204,100,100,204,204,100,100,200,204,100,104,200,100,104,
//        100,100,100,100,104,100,204,100,100,100,104,100,100,104,100,200,100,104,100,100,100,104,
//        200,100,104,200,204,100,100,200,204,204,100,100,204,100,100,104,100,200,104,100,100,100,
//        104,100,100,100,100,104,200,104,100,200,104,100,100,100,204,100,104,100,104,100,100,152,
//        932,52,0
//       }; 
//    const uint16_t TestTimings[] =
//      {
//          36,1452,204,200,104,100,200,204,100,100,204,200,204,204,200,100,100,104,100,204,200,100,
//          100,104,100,204,100,100,200,204,100,100,204,204,100,100,204,100,100,100,104,100,100,100,
//          100,204,204,200,100,104,100,100,100,104,200,100,104,200,100,104,200,100,104,200,204,100,
//          100,204,100,100,204,100,100,200,104,100,204,100,100,100,104,100,100,100,104,200,204,200,
//          200,204,204,200,104,100,204,200,152,100
//
//      }; 
//     const uint16_t TestTimings[] =
//      {
//
//            628,612,200,100,104,200,200,204,200,100,104,100,100,200,204,200,204,100,100,100,104,100,
//            100,100,100,204,100,100,204,100,100,204,200,100,104,200,100,100,104,100,100,100,100,104,
//            100,100,100,100,204,200,104,100,100,100,100,104,200,100,100,104,100,100,100,104,100,100,
//            100,204,100,100,100,100,204,200,204,200,204,100,100,200,104,100,200,100,104,100,100,100,
//            104,100,100,100,100,104,100,200,204,100,100,204,100,100,100,100,204,100,100,164,740
//      };

     const uint16_t TestTimings[] =
      {
            72,200,200,1172,104,104,104,104,104,200,200,200,104, 96,200,200,104, 96,208,200,200, 96,
            104, 96,104,200,208,200,200, 96,104, 96,104,104, 96,200,104, 96,104, 96,208, 96,104,200,
            200,104, 96,104,104, 96,104,200, 96,104, 96,104, 96,104, 96,104,200,200,200,208,200,200,
            104, 96,200,104, 96,104, 96,104,104, 96,104, 96,104, 96,104,200, 96,104,104, 96,200,208,
            200,200,104, 96, 96,104,104, 96,104, 96,200,104,104, 96, 96,192,104, 96,192,200,1096,896,
            112,184, 96 

      };
    const bool FirstTimingIsLow = true;
   #endif 


  
#elif Ford 

   #ifdef UK_433MHz

    const uint16_t TestTimings[] =
      {
            52,56,48,56,48,56,48,56,48,56,48,56,52,52,48,56,48,56,48,56,48,56,48,52,52,52,52,52,
            52,104,104,104,104,52,52,52,52,104,104,104,52,52,52,52,104,104,104,52,52,104,52,52,
            100,52,52,52,52,52,52,104,104,104,52,52,104,104,52,52,104,104,104,52,52,104,52,52,
            100,56,48,52,52,104,104,104,104,104,52,52,104,52,52,52,52,52,52,52,52,104,104,104,
            104,52,52,52,52,104,48,52,104,52,52,52,52,52,52,104,52,52,52,52,104,104,80
      };

    
       const bool FirstTimingIsLow = true;
   #endif

  #ifdef US_315MHz

    const uint16_t TestTimings[] =
//      {
//            53,52,51,52,53,52,53,52,53,51,52,53,52,53,52,52,52,52,53,51,51,51,53,52,52,52,108,106,102,
//            105,53,53,52,50,52,51,52,52,53,55,106,101,103,54,55,54,51,102,103,52,55,54,51,51,52,111,48,
//            51,102,53,51,52,52,104,105,105,104,104,108,106,102,106,53,52,52,51,53,53,52,52,52,51,52,53,
//            54,53,49,53,106,52,52,104,52,53,51,52,53,51,52,51,53,54,54,52,101,104,53,54,54,53,101,105,
//            54,52,52,50,103,53,54,55,52,104,107,56,50,52,55,55,619
//      };


      {
            52,53,51,52,52,52,51,53,52,52,52,53,51,51,52,53,51,51,52,52,51,53,51,106,106,
            100,105,54,52,51,52,50,51,52,52,52,53,106,101,102,52,55,53,51,102,104,51,53,53,51,
            52,51,108,51,50,100,53,52,52,53,104,104,102,104,103,109,104,104,104,51,51,52,52,53,
            52,51,53,51,52,52,53,55,52,49,49,52,51,106,106,100,107,53,52,100,106,53,52,101,107,
            50,54,53,51,103,104,51,51,53,51,52,51,54,55,52,50,99,93,47,46,97,150,597    
      };
       const bool FirstTimingIsLow = true;
   #endif
   


#elif Jansite

   #ifdef UK_433MHz

//    const uint16_t TestTimings[] =
//      {
//            52,56,48,56,48,56,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,
//            52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,
//            52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,
//            52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,
//            52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,
//            52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,
//            52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,
//            52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,
//            52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,
//            52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,
//            52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,
//            52,56,52,52,52,104,104,104,104,104,108,104,104,104,52,52,104,104,104,108,52,52,104,
//            104,52,52,52,52,52,52,104,56,52,104,52,52,52,52,104,52,52,104,52,56,104,52,52,104,
//            104,52,52,52,52,108,52,52,104,104,104,52,52,52,52,104,108,52,52,104,104,52,52,52,
//            52,52,52,104,52,56,104,52,52,104,104,52,52,52,52,104,56,52,52,52,52,52,52,52,52,
//            52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,
//            52,52,52,52,52,52,52,56,52,104,104,104,104,104,104,108,104,104,52,52,104,104,104,
//            104,56,52,104,104,52,52,52,52,52,52,104,56,52,104,52,52,52,52,104,52,52,104,56,48,
//            108,52,52,104,104,52,52,52,52,104,56,52,104,104,104,52,52,52,52,104,104,56,52,104,
//            104,52,52,52,52,52,52,104,56,52,104,52,52,104,104,52,52,52,52
//      };

    const uint16_t TestTimings[] =
      {
            52,64,40,64,44,52,52,52,52,56,48,56,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,
52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,
52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,
52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,
52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,
52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,
52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,
52,56,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,
52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,
52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,
52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,108,104,52,52,52,
52,104,104,104,108,104,52,52,104,52,52,52,52,104,52,52,108,104,104,52,52,52,52,52,52,104,108,104,
104,104,104,52,52,104,108,104,104,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,
52,104,104,56,52,52,52,104,52,52,104,104,104,108,104,104,104,104,104,52,52,104,56,52,52,52,52,52,
52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,
52,52,52,52,52,56,52,52,52,52,52,104,104,52,52,52,52,108,104,104,104,104,52,52,104,52,52,56,
52,104,52,52,104,104,104,52,52,52,56,52,52,104,104,104,104,104,104,56,52,104,104,104,104,52,52,52,
52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,104,104,52,52,52,52,104,52,52,108,104,
104,104,104,104,104,108,104,52,52,160 
       
       };     
       const bool FirstTimingIsLow = false;
   #endif


#elif JansiteSolar
    #ifdef UK_433MHz

    const uint16_t TestTimings[] =
      {
        //53,40,48,56,48,56,48,56,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,
        //52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,
        //52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,
        //52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,48,56,52,52,52,52,52,52,52,52,
        //52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,
        //52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,
        //52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,
        //52,52,52,52,52,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,52,
        //52,52,52,52,52,52,52,52,52,56,48,56,52,52,52,52,52,52,52,52,52,52,52,52,52,52,56,52,
        //52,52,52,52,52,52,52,52,104,104,52,52,56,52,104,104,104,52,52,104,52,52,104,56,52,104,52,52,
        //52,52,52,52,104,104,52,56,100,108,52,52,104,52,52,52,52,104,104,104,108,104,104,52,52,52,52,52,
        //52,52,56,48,52,108,104,52,52,52,52,52,52,52,52,52,52,52,52,56,52,52,52,52,52,104,104,52,
        //52,104,52,56,104,52,52,52,52,104,104,104,104,104,108,52,52,52,52,52,52,52,52,52,52,52,52,52,
        //52,52,56,52,52,104,104,104,52,52,104,52,52,108,52,52,52,52,104,104,104,52,52,52,52,52,52,108,
        //748,32
        
        53, 52, 52, 53, 52, 52, 53, 52, 52, 52, 53, 53, 51, 53, 52, 52, 52, 53, 52, 52, 52, 54, 
        51, 52, 53, 52, 52, 52, 53, 52, 52, 53, 52, 52, 52, 53, 52, 53, 53, 51, 52, 53, 52, 52, 53, 
        52, 52, 53, 55, 49, 53, 52, 52, 52, 53, 53, 51, 53, 52, 52, 53, 52, 52, 53, 52, 53, 52, 52, 
        52, 52, 53, 52, 53, 52, 52, 52, 53, 52, 52, 53, 52, 52, 53, 52, 52, 52, 53, 52, 52, 52, 53, 
        52, 52, 53, 52, 52, 52, 53, 52, 52, 53, 52, 52, 53, 52, 52, 53, 52, 52, 53, 52, 52, 52, 52, 
        53, 52, 53, 52, 52, 52, 53, 52, 53, 52, 52, 52, 52, 53, 52, 53, 54, 50, 53, 52, 52, 53, 52, 
        52, 52, 53, 52, 53, 52, 52, 53, 53, 51, 52, 53, 52, 52, 53, 52, 52, 54, 51, 52, 52, 53, 52, 
        52, 52, 53, 52, 52, 53, 52, 52, 52, 54, 51, 52, 52, 53, 52, 52, 53, 52, 52, 53, 52, 52, 53, 
        52, 53, 51, 52, 53, 52, 53, 52, 52, 52, 52, 53, 52, 52, 53, 52, 53, 52, 53, 51, 53, 52, 52, 
        52, 53, 52, 52, 53, 52, 52, 53, 52, 52, 52, 53, 52, 52, 52, 53, 52, 52, 54, 51, 52, 52, 53, 
        52, 52, 53, 52, 52, 52, 53, 52, 52, 53, 52, 52, 52, 53, 52, 52, 53, 50, 53, 50, 52, 53, 54, 
        53,104,102, 52, 53, 51, 53,106,105,104, 52, 53,104, 52, 53,106, 53, 51,104, 53, 53, 52, 51,
        104, 51, 51, 52, 52,106,105,103,103, 52, 54,109,105,103, 53, 53, 52, 53,103, 51, 51, 52, 53, 
        54, 51,103,105, 54, 53,106,105, 52, 53, 51, 53, 52, 51, 51, 51, 52, 51, 53, 51,104,103,107,
        106,106,107, 52, 51,109, 49, 53, 52, 52,105, 52, 53, 52, 53, 52, 52, 53, 52, 52, 52, 52, 53, 
        52, 52, 53, 52, 52, 51, 53, 50, 52, 53, 53, 54,105,103, 52, 52, 53, 52, 51, 51,106, 53, 51,
        103,106, 54, 53,107,103, 52, 51, 52, 53, 53, 51, 51, 51,101, 46, 46, 93, 92, 48, 47,898


       };     
       const bool FirstTimingIsLow = false;
   #endif   

#elif Hyundai_i35
    #ifdef UK_433MHz

    const uint16_t TestTimings[] =
      {

      104, 56, 52,440,152, 48, 48, 52, 48, 52, 48, 48, 52, 48, 48,100,
      100,100, 52, 48, 48, 48,100, 48, 52, 96, 52, 48,100, 52, 48,100,
      100, 96,100,100,100, 96, 52, 48,104, 48, 48, 48, 52, 48, 48,104, 
      96, 48, 52,100, 96, 52, 48,100, 48, 52, 96, 52, 48, 52, 48, 48, 
      48,104, 48, 52, 96, 48, 52, 48, 52, 48, 52, 96,100,100,100, 96,
      100, 48, 48,100,104, 48, 52, 96,100,100, 48, 52, 48, 48, 52, 48, 
      48, 52, 52, 48,100, 48, 48, 44, 52, 48, 48, 92, 48,348, 52,216,108, 52
       
       
       };     
       const bool FirstTimingIsLow = true;
   #endif 

#elif Schrader_C1100
    #ifdef UK_433MHz

    const uint16_t TestTimings[] =
      {

      54, 51, 53, 52, 52, 52, 53, 52, 52, 52, 53, 52, 52, 53, 52, 53, 52, 51, 
      51, 54, 54, 51, 51, 53,106, 52, 51,105, 53, 52, 52, 53, 51, 51, 52, 54, 
      54, 58, 46, 50,104, 51, 52, 53, 52,104,108,105,102,104, 52, 51,108, 54, 
      52,102,103, 52, 52, 53, 51, 53, 52,107,108,100,106, 54, 52, 51, 51,103, 
      52, 55, 54, 53,103,104, 54, 51, 51, 51,103, 53, 55,107,102,105, 53, 52, 
      52, 52, 52, 53, 52, 51, 52, 51, 53, 54, 55, 52,101,106, 54, 51, 51, 52,
      107, 52, 52,103, 53, 53, 53, 51, 52, 53, 52, 51, 52, 51, 53, 51, 54, 51,
      108,106,102,104, 52, 52, 52, 55, 52, 50,103,111, 53

       
       
       };     
       const bool FirstTimingIsLow = false;
   #endif 

#elif Subaru
    #ifdef UK_433MHz

    const uint16_t TestTimings[] =
      {
         //derived from Subaru.sr RTL433 capture
         208, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 
         212,104,50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
         104,100, 50, 50,100, 50, 50, 50, 50,100, 50, 50,100, 50, 50,100, 50, 50, 50, 50,100,100, 50, 50, 50, 50, 50, 50,100,100,
         50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,100,100, 50, 50,100,100, 50, 50, 50, 50, 50, 50, 50, 50,
         100,100, 50, 50, 50, 50, 50, 50, 50, 50,100, 50, 50,100, 50, 50,100,100, 50, 50, 50, 50,100,500

       
       
       };     
       const bool FirstTimingIsLow = false;
       
   #elif US_315MHz

    const uint16_t TestTimings[] =
      {

          553,246,122,122,124,121,123,123,123,123,124,122,123,124,121,123,123,122,
          123,123,123,123,126,124,125,122,123,123,120,489,246,123,123,121,123,247,
          124,122,123,124,123,124,244,121,122,247,247,123,124,120,124,246,244,123,
          123,247,122,124,123,122,246,123,122,245,122,126,246,124,121,122,121,246,
          245,123,124,124,124,124,122,122,121,244,245,123,125,126,124,125,125,125,
          3036
      
       };     
       const bool FirstTimingIsLow = true;
       
   #endif 
#endif




#ifdef USE_TEST_TIMINGS
      const int16_t TestTimings_len = sizeof(TestTimings)/sizeof(TestTimings[0]);
#endif
