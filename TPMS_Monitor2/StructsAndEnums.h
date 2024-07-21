#ifndef STRUCTSANDENUMS_H
#define STRUCTSANDENUMS_H

#include <map>

/*****************************************************************************
 *                                   ENUMS                                   *
 *****************************************************************************/
enum class Display_ST7735_Tabs {
  GreenTab,
  RedTab,
  BlackTab
};

enum class Pressure_Units {
  Bar,
  KG_CM,
  KPA,
  PSI
};

enum class Temperature_Units {
  Celsius,
  Fahrenheit,
  Kelvin
};

enum class Tire_Positions {
  FrontLeft,
  FrontRight,
  RearLeft,
  RearRight,
  Spare
};

enum class TPMS_Frequencies {
  US_315MHz,
  UK_433MHz
};

enum class TPMS_Sensors {
  Citroen,
  Dacia,
  Ford,
  Hyundai_i35,
  Jansite,
  JansiteSolar,
  Mercedes_AMG_GT,
  NissanLeaf,
  PontiacG82009,
  Renault,
  Schrader_A9054100,
  Schrader_C1100,
  Subaru,
  Toyota_PMV_107J,
  Toyota_PMV_C210,
  Toyota_TRW_C070,
  TruckSolar,
  Zoe
};


/*****************************************************************************
 *                                  MAPPINGS                                 *
 *****************************************************************************/
static std::map<Display_ST7735_Tabs, const char*> ST7735TabName{
  { Display_ST7735_Tabs::GreenTab, "Green" },
  { Display_ST7735_Tabs::RedTab, "Red" },
  { Display_ST7735_Tabs::BlackTab, "Black" }
};

static std::map<Pressure_Units, const char*> pressureUnitName{
  { Pressure_Units::Bar, "Bar" },
  { Pressure_Units::KG_CM, "KG/CM2" },
  { Pressure_Units::KPA, "KPA" },
  { Pressure_Units::PSI, "PSI" }
};

static std::map<Pressure_Units, float> pressureUnitMultiplierFromBars{
  { Pressure_Units::Bar, 1.0 },
  { Pressure_Units::KG_CM, 1.02 },
  { Pressure_Units::KPA, 100.0 },
  { Pressure_Units::PSI, 14.504 }
};

static std::map<Temperature_Units, const char*> temperatureUnitName{
  { Temperature_Units::Celsius, "Celsius" },
  { Temperature_Units::Fahrenheit, "Fahrenheit" },
  { Temperature_Units::Kelvin, "Kelvin" }
};

static std::map<Temperature_Units, const char*> temperatureUnitSymbol{
  { Temperature_Units::Celsius, "C" },     // °C
  { Temperature_Units::Fahrenheit, "F" },  // °F
  { Temperature_Units::Kelvin, "K" }       // °K
};

static std::map<Tire_Positions, const char*> tirePositionName{
  { Tire_Positions::FrontLeft, "Front Left" },
  { Tire_Positions::FrontRight, "Front Right" },
  { Tire_Positions::RearLeft, "Rear Left" },
  { Tire_Positions::RearRight, "Rear Right" },
  { Tire_Positions::Spare, "Spare" }
};

static std::map<Tire_Positions, int> tirePositionArrayIndex{
  { Tire_Positions::FrontLeft, 0 },
  { Tire_Positions::FrontRight, 1 },
  { Tire_Positions::RearLeft, 2 },
  { Tire_Positions::RearRight, 3 },
  { Tire_Positions::Spare, 4 }
};

static std::map<TPMS_Frequencies, const char*> tpmsFrequencyName{
  { TPMS_Frequencies::US_315MHz, "315 MHz" },
  { TPMS_Frequencies::UK_433MHz, "433 MHz" }
};

static std::map<TPMS_Sensors, const char*> tpmsSensorName{
  { TPMS_Sensors::Citroen, "Citroen TPMS" },
  { TPMS_Sensors::Dacia, "Dacia TPMS" },
  { TPMS_Sensors::Ford, "Ford TPMS" },
  { TPMS_Sensors::Hyundai_i35, "Hyundai i35" },
  { TPMS_Sensors::Jansite, "Jansite TPMS" },
  { TPMS_Sensors::JansiteSolar, "JSolar TPMS" },
  { TPMS_Sensors::Mercedes_AMG_GT, "Mercedes AMG GT" },
  { TPMS_Sensors::NissanLeaf, "Nissan Leaf TPMS" },
  { TPMS_Sensors::PontiacG82009, "Pontiac G8 TPMS" },
  { TPMS_Sensors::Renault, "Renault TPMS" },
  { TPMS_Sensors::Schrader_A9054100, "Smart ForTwo" },
  { TPMS_Sensors::Schrader_C1100, "Hyundai Tucson" },
  { TPMS_Sensors::Subaru, "Subaru TPMS" },
  { TPMS_Sensors::Toyota_PMV_107J, "Toyota TPMS 107J" },
  { TPMS_Sensors::Toyota_PMV_C210, "Toyota TPMS C210" },
  { TPMS_Sensors::Toyota_TRW_C070, "Toyota TPMS C070" },
  { TPMS_Sensors::TruckSolar, "Truck Solar" },
  { TPMS_Sensors::Zoe, "Ren Zoe(early) TPMS" }
};


/*****************************************************************************
 *                                  STRUCTS                                  *
 *****************************************************************************/
struct CC1101_Parameters {
  int expectedbitcount = 72;
  int expectedbytecount = 9;
  int expectedfifobytecount = 21;
  int syncbits = 16;
  int cdwidth_min = 5500;
  int cdwidth_max = 11500;
  int shorttiming_min = 35;
  int shorttiming_nom = 50;
  int shorttiming_max = 79;
  int longtiming_min = 80;
  int longtiming_max = 120;
  int synctiming_min = 175;
  int synctiming_max = 1200;
  int endtiming_min = 0;
  int endtiming_max = 500;
};  // CC1101_Parameters

struct CC1101_Settings {
  byte cc1101_defval_iocfg2 = 0x0C;    // GDO2 Output Pin Configuration - Serial out (synchronous)
  byte cc1101_defval_iocfg1 = 0x2E;    // GDO1 Output Pin Configuration - not used
  byte cc1101_defval_iocfg0 = 0x0E;    // GDO0 Output Pin Configuration - Carrier Sense output
  byte cc1101_defval_fifothr = 0x0F;   // RX FIFO and TX FIFO Thresholds - 64 bytes in FIFO
  byte cc1101_defval_sync1 = 0xD5;     // Synchronization word, high byte  11010101 01001111
  byte cc1101_defval_sync0 = 0x4F;     // Synchronization word, low byte
  byte cc1101_defval_pktlen = 0x09;    // Packet Length
  byte cc1101_defval_pktctrl1 = 0x00;  // Packet Automation Control
  byte cc1101_defval_pktctrl0 = 0x12;  // Packet Automation Control - synchronous data
  byte cc1101_defval_addr = 0x00;      // Device Address
  byte cc1101_defval_channr = 0x00;    // Channel Number
  byte cc1101_defval_fsctrl1 = 0x0F;   // Frequency Synthesizer Control
  byte cc1101_defval_fsctrl0 = 0x00;   // Frequency Synthesizer Control
  byte cc1101_defval_freq2 = 0x10;     // Frequency Control Word, High Byte
  byte cc1101_defval_freq1 = 0xB0;     // Frequency Control Word, Middle Byte
  byte cc1101_defval_freq0 = 0x71;     // Frequency Control Word, Low Byte
  byte cc1101_defval_deviatn = 0x40;   // Modem Deviation Setting (+/-25.390625kHz)
  byte cc1101_defval_mdmcfg4 = 0x59;   // Modem Configuration (59 = data rate = 20kHz, RX bw 325kHz)
  byte cc1101_defval_mdmcfg3 = 0x93;   // Modem Configuration (now 93 = data rate = 20kHz)
  byte cc1101_defval_mdmcfg2 = 0x10;   // Modem Configuration (GFSK, No Sync or Manchester coding)
  byte cc1101_defval_mdmcfg1 = 0x21;   // Modem Configuration Channel spacing 100kHz
  byte cc1101_defval_mdmcfg0 = 0xF8;   // Modem Configuration
  byte cc1101_defval_agcctrl2 = 0x87;  // AGC Control
  byte cc1101_defval_agcctrl1 = 0x58;  // AGC Control
  byte cc1101_defval_agcctrl0 = 0x80;  // AGC Control
  byte cc1101_defval_mcsm2 = 0x07;     // Main Radio Control State Machine Configuration
  byte cc1101_defval_mcsm1 = 0x3C;     // Main Radio Control State Machine Configuration
  byte cc1101_defval_mcsm0 = 0x18;     // Main Radio Control State Machine Configuration
  byte cc1101_defval_foccfg = 0x16;    // Frequency Offset Compensation Configuration
  byte cc1101_defval_bscfg = 0x6C;     // Bit Synchronization Configuration
  byte cc1101_defval_worevt1 = 0x87;   // High Byte Event0 Timeout
  byte cc1101_defval_worevt0 = 0x6B;   // Low Byte Event0 Timeout
  byte cc1101_defval_worctrl = 0xFB;   // Wake On Radio Control
  byte cc1101_defval_frend1 = 0x56;    // Front End RX Configuration
  byte cc1101_defval_frend0 = 0x10;    // Front End TX Configuration
  byte cc1101_defval_fscal3 = 0xE9;    // Frequency Synthesizer Calibration
  byte cc1101_defval_fscal2 = 0x2A;    // Frequency Synthesizer Calibration
  byte cc1101_defval_fscal1 = 0x00;    // Frequency Synthesizer Calibration
  byte cc1101_defval_fscal0 = 0x1F;    // Frequency Synthesizer Calibration
  byte cc1101_defval_rcctrl1 = 0x41;   // RC Oscillator Configuration
  byte cc1101_defval_rcctrl0 = 0x00;   // RC Oscillator Configuration
  byte cc1101_defval_fstest = 0x59;    // Frequency Synthesizer Calibration Control
  byte cc1101_defval_ptest = 0x7F;     // Production Test
  byte cc1101_defval_agctest = 0x3F;   // AGC Test
  byte cc1101_defval_test2 = 0x81;     // Various Test Settings
  byte cc1101_defval_test1 = 0x35;     // Various Test Settings
  byte cc1101_defval_test0 = 0x09;     // Various Test Settings
};                                     // CC1101_Settings

struct TireInfo {
  long sensorId;
  Tire_Positions position;
  float temperature;
  double pressure;
  uint16_t status;
  uint16_t battery;
  uint16_t counter;
  unsigned long lastReadMillis;
};  // TireInfo

struct Car_Settings {
  TPMS_Frequencies freq;
  TPMS_Sensors tpmsSensorType;

  TireInfo tires[5];
};  // Car_Settings

struct Unit_Settings {
  Display_ST7735_Tabs st7735Tab;
  bool debug;
  bool alarmEnabled;
  Pressure_Units pressureUnit;
  Temperature_Units temperatureUnit;
};  // Unit_Settings




#endif  // STRUCTSANDENUMS_H