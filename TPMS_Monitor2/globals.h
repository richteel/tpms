#ifndef GLOBALS_H
#define GLOBALS_H

Car_Settings carSettings;
Unit_Settings unitSettings;

void init_globals() {
  unitSettings.st7735Tab = Display_ST7735_Tabs::BlackTab;
  unitSettings.debug = DEBUG;
  unitSettings.pressureUnit = Pressure_Units::PSI;
  unitSettings.temperatureUnit = Temperature_Units::Fahrenheit;
  #if defined(BUZZER)
    unitSettings.alarmEnabled = true;
  #else
    unitSettings.alarmEnabled = false;
  #endif

  
  carSettings.freq = TPMS_Frequencies::US_315MHz;
  carSettings.tpmsSensorType = TPMS_Sensors::Toyota_PMV_107J;
  carSettings.tires[tirePositionArrayIndex[Tire_Positions::FrontLeft]].position = Tire_Positions::FrontLeft;
  carSettings.tires[tirePositionArrayIndex[Tire_Positions::FrontLeft]].sensorId = 0x0D97C8E3L;
  carSettings.tires[tirePositionArrayIndex[Tire_Positions::FrontRight]].position = Tire_Positions::FrontRight;
  carSettings.tires[tirePositionArrayIndex[Tire_Positions::FrontRight]].sensorId = 0x05555262L;
  carSettings.tires[tirePositionArrayIndex[Tire_Positions::RearLeft]].position = Tire_Positions::RearLeft;
  carSettings.tires[tirePositionArrayIndex[Tire_Positions::RearLeft]].sensorId = 0x03A3515AL;
  carSettings.tires[tirePositionArrayIndex[Tire_Positions::RearRight]].position = Tire_Positions::RearRight;
  carSettings.tires[tirePositionArrayIndex[Tire_Positions::RearRight]].sensorId = 0x0E90614AL;
  carSettings.tires[tirePositionArrayIndex[Tire_Positions::Spare]].position = Tire_Positions::Spare;
  carSettings.tires[tirePositionArrayIndex[Tire_Positions::Spare]].sensorId = 0x0L;
}


#endif    // GLOBALS_H