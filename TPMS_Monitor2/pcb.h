#ifndef CONFIG_H
#define CONFIG_H

#define DISPLAY_1_INCH_YB_I2C_DISPLAY_ADAFRUIT 8192    // 0.96in SSD1306 I2C 64x128 OLED display Adafruit
#define DISPLAY_1_INCH_YB_I2C_DISPLAY          8193    // 0.96in SSD1306 I2C 64x128 OLED display
#define DISPLAY_2_INCH_ST7735_DISPLAY         20480    // 1.8in ST7735 SPI 160x128 TFT display
#define DISPLAY_2_INCH_ST7789_DISPLAY         57600    // 1.28in ST7789 SPI 240x240 TFT round display
#define DISPLAY_24_INCH_ILI9341_DISPLAY       76800    // 2.4in ILI9341 SPI 240x320 TFT display

/*****************************************************************************
 *                        Board and Module Parameters                        *
 *****************************************************************************/
#define PCB_VERSION_MAJ     1
#define PCB_VERSION_MIN     0
#define SER                 Serial
#define DEBUG               true
#define USE_HW_CD           true
#define USE_FIFO            false

#if PCB_VERSION_MAJ == 1
  #define PROC_TYPE         "Raspberry Pi Pico RP2040"
  #define USE_DISPLAY       DISPLAY_2_INCH_ST7735_DISPLAY

  /*************/
  /*    PINS   */
  /*************/

  /**** SPI ****/
  // CC1101
  #define CC1101_SPI        SPI
  #define CC1101_SCK        2
  #define CC1101_MOSI       3
  #define CC1101_MISO       4

  // LCD
  #define LCD_SPI           SPI1
  #define LCD_SCK           10
  #define LCD_MOSI          11
  #define LCD_MISO          12

  /**** CC1101 ****/
  #define CC1101_CD         26    //Comment line if not wired, otherwise CD pin status is received over SPI
  #define CC1101_RX         27    //must be an ext interrupt pin
  #define CC1101_CS         28    // Define the Chip Select pin

  /**** LCD/SD CARD ****/
  #define LCD_DC            6     // D/C
  #define LCD_CS            7     // LCD_CS
  #define LCD_LITE          20    // Backlight
  #define LCD_RESET         21    // Reset
  #define SDCARD_CS         22    // Card_CS

  /**** LEDS ****/
  #define LED_DEFAULT       25    // Built in LED
  #define LED_RX            17    // RX LED  - Red
  #define LED_AUX           16    // AUX LED - Yellow
  #define LED_DBUG          18    // Debug LED - Green

  /**** BUZZER ****/
  #define BUZZER            1

  /**** SWICHES ****/
  #define SW_BACK           13
  #define SW_SELECT         14
  #define SW_NEXT           15

  /*****************/
  /* ACTIVE LEVELS */
  /*****************/
  #define ACTIVE_BUZZER     HIGH    // Logic level to sound the buzzer
  #define ACTIVE_SW         LOW     // Logic level when button is pressed
  #define ACTIVE_LED        HIGH    // Logic level to light LED

#else
  #error No configuration set up for this PCB Version in config.h
#endif  // PCB_VERSION == 1



/*****************/
/*   MAX VALUES  */
/*****************/
#define MAXBITS             1000
#define MAXTIMINGS          900


/******************************************/
/*    End Configuration Perform Checks    */
/******************************************/
#ifndef DEBUG
  #define DEBUG             false
#endif

#ifndef USE_DISPLAY
  #define USE_DISPLAY       0
#endif

#ifndef PROC_TYPE
  #error PROC_TYPE not defined in config.h
#endif

#ifndef CC1101_SPI
  #error No configuration set up for CC1101 in config.h
#elif !defined(CC1101_RX) || !defined(CC1101_CS)
  #error CC1101 RX and CS pins not defined in config.h
#endif

#if defined(LCD_SPI) && (!defined(LCD_SCK) || !defined(LCD_MOSI) || !defined(LCD_MISO) || !defined(LCD_DC) || !defined(LCD_CS) || !defined(LCD_RESET) || !defined(LCD_LITE))
  #error LCD SCK, MOSI, MISO, LCD_DC, LCD_CS, LCD_RESET, and LCD_LITE pins not defined in config.h
#endif

#if (defined(LED_DEFAULT) || defined(LED_RX) || defined(LED_AUX)) && !defined(ACTIVE_LED)
  #error Must define ACTIVE_LED when LED_DEFAULT, LED_RX, or LED_AUX are defined in config.h
#endif

#if defined(BUZZER) && !defined(ACTIVE_BUZZER)
  #error Must define ACTIVE_BUZZER when BUZZER is defined in config.h
#endif

#if (defined(SW_BACK) || defined(SW_SELECT) || defined(SW_NEXT)) && !defined(ACTIVE_SW)
  #error Must define ACTIVE_SW when SW_BACK, SW_SELECT, or SW_NEXT are defined in config.h
#endif

#endif    // CONFIG_H