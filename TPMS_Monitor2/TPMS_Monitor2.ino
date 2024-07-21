#define VERSION "0.1"

/*****************************************************************************
 *                              FreeRTOS Setup                               *
 *****************************************************************************/
#if !defined(ESP_PLATFORM) && !defined(ARDUINO_ARCH_MBED_RP2040) && !defined(ARDUINO_ARCH_RP2040)
#pragma message("Unsupported platform")
#endif

// ESP32:
#if defined(ESP_PLATFORM)
TaskHandle_t task_loop1;
void esploop1(void *pvParameters) {
  setup1();

  for (;;)
    loop1();
}
#endif

#if defined(ARDUINO_ARCH_MBED_RP2040) || defined(ARDUINO_ARCH_RP2040)
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#define xPortGetCoreID get_core_num
#endif

/*****************************************************************************
 *                               Include Files                               *
 *****************************************************************************/
#include <Dictionary.h>
#include <SPI.h>

/*****************************************************************************
 *                               Project Files                               *
 *****************************************************************************/
#include "pcb.h"
#include "StructsAndEnums.h"
#include "globals.h"
#include "DebugLogging.h"
#include "cc1101.h"

#if USE_DISPLAY == DISPLAY_2_INCH_ST7735_DISPLAY
#include "display_128x160.h"
#endif

// For debugging should be removed
#include "types.h"


/*****************************************************************************
 *                                  GLOBALS                                  *
 *****************************************************************************/



/*****************************************************************************
 *                                 LOG FILES                                 *
 *****************************************************************************/
char logDebug[] = "/logs/debug.log";
char logDebugArchive[] = "/logs/debug_1.log";

/*****************************************************************************
 *                                DEBUG LEVEL                                *
 *****************************************************************************/
DebugLevels debugLevel = DebugLevels::Verbose;
// DebugLevels debugLevel = DebugLevels::Info;
// DebugLevels debugLevel = DebugLevels::Warning;
// DebugLevels debugLevel = DebugLevels::Error;

int waitLoopsToPrintTaskInfo = 100;

/*****************************************************************************
 *                                   QUEUES                                  *
 *****************************************************************************/
static const uint8_t log_queue_len = 10;
static QueueHandle_t log_queue;

static const uint8_t remote_queue_len = 5;
static QueueHandle_t remote_queue;

/*****************************************************************************
 *                                   MUTEX                                   *
 *****************************************************************************/
static SemaphoreHandle_t sdcard_mutex;
static SemaphoreHandle_t rtc_mutex;

/*****************************************************************************
 *                               INO FUNCTIONS                               *
 *****************************************************************************/
void init_display() {
  switch (USE_DISPLAY) {
    case DISPLAY_1_INCH_YB_I2C_DISPLAY_ADAFRUIT:
      // if (!display.begin(SSD1306_EXTERNALVCC, I2C_ADDRESS)) {
      //   SER.println(F("SSD1306 allocation failed"));
      //   while(1)
      //   {
      //     delay(10);// Don't proceed, loop forever
      //   }
      // }
      // display.clearDisplay();
      // display.display();
      // SER.println(F("Adafruit SSD1306 initialised OK"));
      SER.println(F("ERROR: Adafruit SSD1306 Not Implemented"));
      break;
    case DISPLAY_1_INCH_YB_I2C_DISPLAY:
      // Wire.begin();
      // Wire.setClock(400000L);
      // display.begin(&Adafruit128x64, I2C_ADDRESS);
      // display.setFont(Adafruit5x7);
      // display.clear();
      // ShowTitle();
      // SER.println(F("SSD1306 initialised OK"));
      SER.println(F("ERROR: Generic SSD1306 Not Implemented"));
      break;
    default:
#if defined(LCD_SPI)
      ScreenSetup();
#else
#error Display not found in intialization setion of Setup()
#endif
      break;
  }
}

void init_hardware() {
  // Setup SPI
  CC1101_SPI.setSCK(CC1101_SCK);
  CC1101_SPI.setMOSI(CC1101_MOSI);
  CC1101_SPI.setMISO(CC1101_MISO);
  CC1101_SPI.begin();

#if defined(LCD_SPI)
  if (&LCD_SPI != &CC1101_SPI) {
    LCD_SPI.setSCK(LCD_SCK);
    LCD_SPI.setMOSI(LCD_MOSI);
    LCD_SPI.setMISO(LCD_MISO);
    LCD_SPI.begin();

    delay(2000);
  }
#endif

// Setup hardware
/**** CC1101 ****/
#ifdef CC1101_CD
  pinMode(CC1101_CD, INPUT);
#endif
  pinMode(CC1101_RX, INPUT);
  pinMode(CC1101_CS, OUTPUT);

  digitalWrite(CC1101_CS, HIGH);

/**** LCD/SD CARD ****/
#ifdef LCD_LITE
  pinMode(LCD_LITE, OUTPUT);
  digitalWrite(LCD_LITE, HIGH);
#endif

/**** LEDS ****/
#ifdef LED_DEFAULT
  pinMode(LED_DEFAULT, OUTPUT);
  digitalWrite(LED_DEFAULT, !ACTIVE_LED);
#endif
#ifdef LED_RX
  pinMode(LED_RX, OUTPUT);
  digitalWrite(LED_RX, !ACTIVE_LED);
#endif
#ifdef LED_AUX
  pinMode(LED_AUX, OUTPUT);
  digitalWrite(LED_AUX, !ACTIVE_LED);
#endif
#ifdef LED_DBUG
  pinMode(LED_DBUG, OUTPUT);
  digitalWrite(LED_DBUG, !ACTIVE_LED);
#endif

/**** BUZZER ****/
#ifdef BUZZER
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, !ACTIVE_BUZZER);
#endif

/**** SWICHES ****/
#ifdef SW_BACK
#if ACTIVE_SW == LOW
  pinMode(SW_BACK, INPUT_PULLUP);
#else
  pinMode(SW_BACK, INPUT);
#endif
#endif
#ifdef SW_SELECT
#if ACTIVE_SW == LOW
  pinMode(SW_SELECT, INPUT_PULLUP);
#else
  pinMode(SW_SELECT, INPUT);
#endif
#endif
#ifdef SW_NEXT
#if ACTIVE_SW == LOW
  pinMode(SW_NEXT, INPUT_PULLUP);
#else
  pinMode(SW_NEXT, INPUT);
#endif
#endif
}

void init_serial() {
#ifdef SER
  long intervalSerial = 7000;
  unsigned long previousMillisSerial = millis();
  SER.begin(115200);

  // Wait for the serial port to connect
  while (!SER && ((millis() - previousMillisSerial) < intervalSerial)) {
    delay(1);  // wait for serial port to connect.
  }

  // Print 5 blank lines on startup
  for (int i = 0; i < 5; i++) {
    SER.println("");
  }
  delay(500);
#endif
}



/*****************************************************************************
 *                                   TASKS                                   *
 *****************************************************************************/



/*****************************************************************************
 *                                   SETUP                                   *
 *****************************************************************************/
void setup() {
  init_serial();

  init_hardware();

  init_globals();

  if (unitSettings.alarmEnabled) {
    digitalWrite(BUZZER, ACTIVE_BUZZER);  //audible alarm test
    delay(200);
    digitalWrite(BUZZER, !ACTIVE_BUZZER);
    delay(300);
    digitalWrite(BUZZER, ACTIVE_BUZZER);  //audible alarm test
    delay(200);
    digitalWrite(BUZZER, !ACTIVE_BUZZER);
    delay(500);
  }

#ifdef SER
  SER.println(F("########################################################################"));
  SER.println(F(""));
  SER.println(F("STARTING..."));
  SER.print(F("Software version "));
  SER.println(VERSION);
  SER.print(F("Hardware version "));
  SER.printf("%d.%d\n", PCB_VERSION_MAJ, PCB_VERSION_MIN);
  SER.print(F("Processor: "));
  SER.println(PROC_TYPE);
#else
#define SER Serial
#endif

  init_display();

  //initialise the CC1101

  SER.print(F("Resetting CC1101 "));
  uint8_t retrycount = 0;
  while (retrycount < 5) {
    SER.print(F("."));
    CC1101_reset();
    if (readConfigReg(0) == 0x29)
      break;
    retrycount++;
    delay(5);
  }
  SER.println(F(""));

  if (readConfigReg(0) == 0x29) {
    SER.println(F("CC1101 reset successful"));
  } else {
    SER.println(F("CC1101 reset failed. Try rebooting"));
#ifdef USE_LCDDISPLAY
#ifdef USE_2_INCH_ST7735_DISPLAY
    DisplayWarning((char *)"CC1101 reset failed", 0, 64);
    DisplayWarning((char *)"Power off/on", 0, 80);
    while (1) {
      delay(10);  // Don't proceed, loop forever
    }
#endif
#endif
  }


  cc1101_init_vars();
  ConfigureCC1101();
  SER.print(F("CC1101 configured for "));
  if(carSettings.freq == TPMS_Frequencies::US_315MHz) {
     SER.print (F("US (315MHz)"));
  } else {
     SER.print (F("UK (433MHz)"));
  }
  SER.printf(" and %s sensor\n", tpmsSensorName[carSettings.tpmsSensorType]);

  //
}

/*****************************************************************************
 *                                    LOOP                                   *
 *****************************************************************************/
long intervalSerial = 1000;
unsigned long previousMillisSerial = millis();

void loop() {

  if (SER && ((millis() - previousMillisSerial) >= intervalSerial)) {
    digitalWrite(LED_AUX, !digitalRead(LED_AUX));
    previousMillisSerial = millis();
  }
}