#ifndef CC1101_H
#define CC1101_H

#include "cc1101_init_vars.h"

/*****************************************************************************
 *                              CC1101 Constants                             *
 *****************************************************************************/
/**
 * Type of register
 */
#define CC1101_CONFIG_REGISTER READ_SINGLE
#define CC1101_STATUS_REGISTER READ_BURST

/**
 * Buffer and data lengths
 */
#define CCPACKET_BUFFER_LEN 64
#define CCPACKET_DATA_LEN CCPACKET_BUFFER_LEN - 3

/**
 * PATABLE & FIFO's
 */
#define CC1101_PATABLE 0x3E  // PATABLE address
#define CC1101_TXFIFO 0x3F   // TX FIFO address
#define CC1101_RXFIFO 0x3F   // RX FIFO address

/**
 * Command strobes
 */
#define CC1101_SRES 0x30     // Reset CC1101 chip
#define CC1101_SFSTXON 0x31  // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1). If in RX (with CCA): \
                             // Go to a wait state where only the synthesizer is running (for quick RX / TX turnaround).
#define CC1101_SXOFF 0x32    // Turn off crystal oscillator
#define CC1101_SCAL 0x33     // Calibrate frequency synthesizer and turn it off. SCAL can be strobed from IDLE mode without \
                             // setting manual calibration mode (MCSM0.FS_AUTOCAL=0)
#define CC1101_SRX 0x34      // Enable RX. Perform calibration first if coming from IDLE and MCSM0.FS_AUTOCAL=1
#define CC1101_STX 0x35      // In IDLE state: Enable TX. Perform calibration first if MCSM0.FS_AUTOCAL=1. \
                             // If in RX state and CCA is enabled: Only go to TX if channel is clear
#define CC1101_SIDLE 0x36    // Exit RX / TX, turn off frequency synthesizer and exit Wake-On-Radio mode if applicable
#define CC1101_SWOR 0x38     // Start automatic RX polling sequence (Wake-on-Radio) as described in Section 19.5 if \
                             // WORCTRL.RC_PD=0
#define CC1101_SPWD 0x39     // Enter power down mode when CSn goes high
#define CC1101_SFRX 0x3A     // Flush the RX FIFO buffer. Only issue SFRX in IDLE or RXFIFO_OVERFLOW states
#define CC1101_SFTX 0x3B     // Flush the TX FIFO buffer. Only issue SFTX in IDLE or TXFIFO_UNDERFLOW states
#define CC1101_SWORRST 0x3C  // Reset real time clock to Event1 value
#define CC1101_SNOP 0x3D     // No operation. May be used to get access to the chip status byte

/**
 * CC1101 configuration registers
 */
#define CC1101_IOCFG2 0x00    // GDO2 Output Pin Configuration
#define CC1101_IOCFG1 0x01    // GDO1 Output Pin Configuration
#define CC1101_IOCFG0 0x02    // GDO0 Output Pin Configuration
#define CC1101_FIFOTHR 0x03   // RX FIFO and TX FIFO Thresholds
#define CC1101_SYNC1 0x04     // Sync Word, High Byte
#define CC1101_SYNC0 0x05     // Sync Word, Low Byte
#define CC1101_PKTLEN 0x06    // Packet Length
#define CC1101_PKTCTRL1 0x07  // Packet Automation Control
#define CC1101_PKTCTRL0 0x08  // Packet Automation Control
#define CC1101_ADDR 0x09      // Device Address
#define CC1101_CHANNR 0x0A    // Channel Number
#define CC1101_FSCTRL1 0x0B   // Frequency Synthesizer Control
#define CC1101_FSCTRL0 0x0C   // Frequency Synthesizer Control
#define CC1101_FREQ2 0x0D     // Frequency Control Word, High Byte
#define CC1101_FREQ1 0x0E     // Frequency Control Word, Middle Byte
#define CC1101_FREQ0 0x0F     // Frequency Control Word, Low Byte
#define CC1101_MDMCFG4 0x10   // Modem Configuration
#define CC1101_MDMCFG3 0x11   // Modem Configuration
#define CC1101_MDMCFG2 0x12   // Modem Configuration
#define CC1101_MDMCFG1 0x13   // Modem Configuration
#define CC1101_MDMCFG0 0x14   // Modem Configuration
#define CC1101_DEVIATN 0x15   // Modem Deviation Setting
#define CC1101_MCSM2 0x16     // Main Radio Control State Machine Configuration
#define CC1101_MCSM1 0x17     // Main Radio Control State Machine Configuration
#define CC1101_MCSM0 0x18     // Main Radio Control State Machine Configuration
#define CC1101_FOCCFG 0x19    // Frequency Offset Compensation Configuration
#define CC1101_BSCFG 0x1A     // Bit Synchronization Configuration
#define CC1101_AGCCTRL2 0x1B  // AGC Control
#define CC1101_AGCCTRL1 0x1C  // AGC Control
#define CC1101_AGCCTRL0 0x1D  // AGC Control
#define CC1101_WOREVT1 0x1E   // High Byte Event0 Timeout
#define CC1101_WOREVT0 0x1F   // Low Byte Event0 Timeout
#define CC1101_WORCTRL 0x20   // Wake On Radio Control
#define CC1101_FREND1 0x21    // Front End RX Configuration
#define CC1101_FREND0 0x22    // Front End TX Configuration
#define CC1101_FSCAL3 0x23    // Frequency Synthesizer Calibration
#define CC1101_FSCAL2 0x24    // Frequency Synthesizer Calibration
#define CC1101_FSCAL1 0x25    // Frequency Synthesizer Calibration
#define CC1101_FSCAL0 0x26    // Frequency Synthesizer Calibration
#define CC1101_RCCTRL1 0x27   // RC Oscillator Configuration
#define CC1101_RCCTRL0 0x28   // RC Oscillator Configuration
#define CC1101_FSTEST 0x29    // Frequency Synthesizer Calibration Control
#define CC1101_PTEST 0x2A     // Production Test
#define CC1101_AGCTEST 0x2B   // AGC Test
#define CC1101_TEST2 0x2C     // Various Test Settings
#define CC1101_TEST1 0x2D     // Various Test Settings
#define CC1101_TEST0 0x2E     // Various Test Settings

/**
 * Status registers
 */
#define CC1101_PARTNUM 0x30         // Chip ID
#define CC1101_VERSION 0x31         // Chip ID
#define CC1101_FREQEST 0x32         // Frequency Offset Estimate from Demodulator
#define CC1101_LQI 0x33             // Demodulator Estimate for Link Quality
#define CC1101_RSSI 0x34            // Received Signal Strength Indication
#define CC1101_MARCSTATE 0x35       // Main Radio Control State Machine State
#define CC1101_WORTIME1 0x36        // High Byte of WOR Time
#define CC1101_WORTIME0 0x37        // Low Byte of WOR Time
#define CC1101_PKTSTATUS 0x38       // Current GDOx Status and Packet Status
#define CC1101_VCO_VC_DAC 0x39      // Current Setting from PLL Calibration Module
#define CC1101_TXBYTES 0x3A         // Underflow and Number of Bytes
#define CC1101_RXBYTES 0x3B         // Overflow and Number of Bytes
#define CC1101_RCCTRL1_STATUS 0x3C  // Last RC Oscillator Calibration Result
#define CC1101_RCCTRL0_STATUS 0x3D  // Last RC Oscillator Calibration Result

/**
 * Alias for some default values
 */
#define CCDEF_CHANNR CC1101_DEFVAL_CHANNR
#define CCDEF_SYNC0 CC1101_DEFVAL_SYNC0
#define CCDEF_SYNC1 CC1101_DEFVAL_SYNC1
#define CCDEF_ADDR CC1101_DEFVAL_ADDR

// // Carrier frequency = 868 MHz(not used)
// #define CC1101_DEFVAL_FREQ2_868 0x21  // Frequency Control Word, High Byte
// #define CC1101_DEFVAL_FREQ1_868 0x65  // Frequency Control Word, Middle Byte
// #define CC1101_DEFVAL_FREQ0_868 0xCC  // Frequency Control Word, Low Byte

// // Carrier frequency = 433.8798 MHz
// #define CC1101_DEFVAL_FREQ2_433 0x10    // Frequency Control Word, High Byte
// #define CC1101_DEFVAL_FREQ1_433 0xB0    // Frequency Control Word, Middle Byte
// #define CC1101_DEFVAL_FREQ0_433 0x71    // Frequency Control Word, Low Byte
// #define CC1101_DEFVAL_MDMCFG4_433 0x59  // Modem Configuration (59 = data rate = 20kHz - actual data rate is 10kHz but due to bi-phase coding need to double the rate, RX bandwidth 325kHz)
// #define CC1101_DEFVAL_MDMCFG3_433 0x93  // Modem Configuration (now 93 = data rate = 20kHz)
// #define CC1101_DEFVAL_DEVIATN_433 0x41  // Modem Deviation Setting (+/-28.56kHz)

// // Carrier frequency = 315MHz MHz
// #define CC1101_DEFVAL_FREQ2_315 0x0C    // Frequency Control Word, High Byte
// #define CC1101_DEFVAL_FREQ1_315 0x1D    // Frequency Control Word, Middle Byte
// #define CC1101_DEFVAL_FREQ0_315 0x57    // Frequency Control Word, Low Byte
// #define CC1101_DEFVAL_MDMCFG4_315 0x59  // Modem Configuration (59 = data rate = 20kHz - actual data rate is 10kHz but due to bi-phase coding need to double the rate, RX bandwidth 325kHz)
// #define CC1101_DEFVAL_MDMCFG3_315 0x93  // Modem Configuration (now 93 = data rate = 20kHz)
// #define CC1101_DEFVAL_DEVIATN_315 0x40  // Modem Deviation Setting (+/-25.390625)

/*****************************************************************************
 *                              Other Constants                              *
 *****************************************************************************/
/**
 * Frequency channels
 */
#define NUMBER_OF_FCHANNELS 10

/**
 * Type of transfers
 */
#define WRITE_BURST 0x40
#define READ_SINGLE 0x80
#define READ_BURST 0xC0

/*****************************************************************************
 *                                   Enums                                   *
 *****************************************************************************/
enum RFSTATE {
  RFSTATE_IDLE = 0,
  RFSTATE_RX,
  RFSTATE_TX
};

/*****************************************************************************
 *                                  Structs                                  *
 *****************************************************************************/
/**
 * Class: CCPACKET
 * 
 * Description:
 * CC1101 data packet class
 */
struct CCPACKET {
public:
  //Data length
  uint8_t length;
  // Data buffer
  uint8_t data[CCPACKET_DATA_LEN];
  //* CRC OK flag
  bool crc_ok;
  // Received Strength Signal Indication
  uint8_t rssi;
  // Link Quality Index
  uint8_t lqi;
};

void wait_Miso() {
  uint32_t st = micros();
  while (digitalRead(CC1101_MISO) == HIGH) {
    if (micros() - st > 500)
      break;
  }
}

/*****************************************************************************
 *                                   Macros                                  *
 *****************************************************************************/
// Read CC1101 Config register
#define readConfigReg(regAddr) readReg(regAddr, CC1101_CONFIG_REGISTER)
// Read CC1101 Status register
#define readStatusReg(regAddr) readReg(regAddr, CC1101_STATUS_REGISTER)
// Enter IDLE state
#define setIdleState() cmdStrobe(CC1101_SIDLE)
#define StartCalibration() cmdStrobe(CC1101_SCAL)
// Flush Rx FIFO
#define flushRxFifo() cmdStrobe(CC1101_SFRX)
// Flush Tx FIFO
#define flushTxFifo() cmdStrobe(CC1101_SFTX)
// Disable address check
#define disableAddressCheck() writeReg(CC1101_PKTCTRL1, 0x04)
// Enable address check
#define enableAddressCheck() writeReg(CC1101_PKTCTRL1, 0x06)
// Disable CCA
#define disableCCA() writeReg(CC1101_MCSM1, 0)
// Enable CCA
#define enableCCA() writeReg(CC1101_MCSM1, cc1101_settings.cc1101_defval_mcsm1)
// Set PATABLE single byte
#define setTxPowerAmp(setting) paTableByte = setting
// PATABLE values
#define PA_LowPower 0x60
#define PA_LongDistance 0xC0

// Select (SPI) CC1101
void cc1101_Select() {
  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CC1101_CS, LOW);
}

void cc1101_Deselect() {
  digitalWrite(CC1101_CS, HIGH);
  SPI.endTransaction();
}

/**
 * wakeUp
 * 
 * Wake up CC1101 from Power Down state
 */
void wakeUp(void) {
  cc1101_Select();    // Select CC1101
  wait_Miso();        // Wait until MISO goes low
  cc1101_Deselect();  // Deselect CC1101
}

/**
 * writeReg
 * 
 * Write single register into the CC1101 IC via SPI
 * 
 * 'regAddr'  Register address
 * 'value'  Value to be writen
 */
void writeReg(uint8_t regAddr, uint8_t value) {
  cc1101_Select();        // Select CC1101
  SPI.transfer(regAddr);  // Send register address
  SPI.transfer(value);    // Send value
  cc1101_Deselect();      // Deselect CC1101
}

/**
 * readReg
 * 
 * Read CC1101 register via SPI
 * 
 * 'regAddr'  Register address
 * 'regType'  Type of register: CC1101_CONFIG_REGISTER or CC1101_STATUS_REGISTER
 * 
 * Return:
 *  Data byte returned by the CC1101 IC
 */
uint8_t readReg(uint8_t regAddr, uint8_t regType) {
  uint8_t addr, val;

  addr = regAddr | regType;
  cc1101_Select();           // Select CC1101
  SPI.transfer(addr);        // Send register address
  val = SPI.transfer(0x00);  // Read result
  cc1101_Deselect();         // Deselect CC1101

  return val;
}

/**
 * setCCregs
 * 
 * Configure CC1101 registers
 */
void setCCregs(void) {
  writeReg(CC1101_IOCFG2, cc1101_settings.cc1101_defval_iocfg2);
  writeReg(CC1101_IOCFG1, cc1101_settings.cc1101_defval_iocfg1);
  writeReg(CC1101_IOCFG0, cc1101_settings.cc1101_defval_iocfg0);
  writeReg(CC1101_FIFOTHR, cc1101_settings.cc1101_defval_fifothr);
  writeReg(CC1101_SYNC1, cc1101_settings.cc1101_defval_sync1);
  writeReg(CC1101_SYNC0, cc1101_settings.cc1101_defval_sync0);
  writeReg(CC1101_PKTLEN, cc1101_settings.cc1101_defval_pktlen);
  writeReg(CC1101_PKTCTRL1, cc1101_settings.cc1101_defval_pktctrl1);
  writeReg(CC1101_PKTCTRL0, cc1101_settings.cc1101_defval_pktctrl0);
  writeReg(CC1101_ADDR, cc1101_settings.cc1101_defval_addr);
  writeReg(CC1101_CHANNR, cc1101_settings.cc1101_defval_channr);
  writeReg(CC1101_FSCTRL1, cc1101_settings.cc1101_defval_fsctrl1);
  writeReg(CC1101_FSCTRL0, cc1101_settings.cc1101_defval_fsctrl0);

  writeReg(CC1101_FREQ2, cc1101_settings.cc1101_defval_freq2);
  writeReg(CC1101_FREQ1, cc1101_settings.cc1101_defval_freq1);
  writeReg(CC1101_FREQ0, cc1101_settings.cc1101_defval_freq0);
  writeReg(CC1101_DEVIATN, cc1101_settings.cc1101_defval_deviatn);
  writeReg(CC1101_MDMCFG4, cc1101_settings.cc1101_defval_mdmcfg4);
  writeReg(CC1101_MDMCFG3, cc1101_settings.cc1101_defval_mdmcfg3);

  writeReg(CC1101_MDMCFG2, cc1101_settings.cc1101_defval_mdmcfg2);
  writeReg(CC1101_MDMCFG1, cc1101_settings.cc1101_defval_mdmcfg1);
  writeReg(CC1101_MDMCFG0, cc1101_settings.cc1101_defval_mdmcfg0);

  writeReg(CC1101_MCSM2, cc1101_settings.cc1101_defval_mcsm2);
  writeReg(CC1101_MCSM1, cc1101_settings.cc1101_defval_mcsm1);
  writeReg(CC1101_MCSM0, cc1101_settings.cc1101_defval_mcsm0);
  writeReg(CC1101_FOCCFG, cc1101_settings.cc1101_defval_foccfg);
  writeReg(CC1101_BSCFG, cc1101_settings.cc1101_defval_bscfg);
  writeReg(CC1101_AGCCTRL2, cc1101_settings.cc1101_defval_agcctrl2);
  writeReg(CC1101_AGCCTRL1, cc1101_settings.cc1101_defval_agcctrl1);
  writeReg(CC1101_AGCCTRL0, cc1101_settings.cc1101_defval_agcctrl0);
  writeReg(CC1101_WOREVT1, cc1101_settings.cc1101_defval_worevt1);
  writeReg(CC1101_WOREVT0, cc1101_settings.cc1101_defval_worevt0);
  writeReg(CC1101_WORCTRL, cc1101_settings.cc1101_defval_worctrl);
  writeReg(CC1101_FREND1, cc1101_settings.cc1101_defval_frend1);
  writeReg(CC1101_FREND0, cc1101_settings.cc1101_defval_frend0);
  writeReg(CC1101_FSCAL3, cc1101_settings.cc1101_defval_fscal3);
  writeReg(CC1101_FSCAL2, cc1101_settings.cc1101_defval_fscal2);
  writeReg(CC1101_FSCAL1, cc1101_settings.cc1101_defval_fscal1);
  writeReg(CC1101_FSCAL0, cc1101_settings.cc1101_defval_fscal0);
  writeReg(CC1101_RCCTRL1, cc1101_settings.cc1101_defval_rcctrl1);
  writeReg(CC1101_RCCTRL0, cc1101_settings.cc1101_defval_rcctrl0);
  writeReg(CC1101_FSTEST, cc1101_settings.cc1101_defval_fstest);
  writeReg(CC1101_PTEST, cc1101_settings.cc1101_defval_ptest);
  writeReg(CC1101_AGCTEST, cc1101_settings.cc1101_defval_agctest);
  writeReg(CC1101_TEST2, cc1101_settings.cc1101_defval_test2);
  writeReg(CC1101_TEST1, cc1101_settings.cc1101_defval_test1);
  writeReg(CC1101_TEST0, cc1101_settings.cc1101_defval_test0);
}

/**
 * cmdStrobe
 * 
 * Send command strobe to the CC1101 IC via SPI
 * 
 * 'cmd'  Command strobe
 */
void cmdStrobe(uint8_t cmd) {
  cc1101_Select();    // Select CC1101
  SPI.transfer(cmd);  // Send strobe command
  cc1101_Deselect();  // Deselect CC1101
}

/**
 * setRxState
 * 
 * Enter Rx state
 */
void setRxState() {
  cmdStrobe(CC1101_SRX);
}

void setTxState() {
  cmdStrobe(CC1101_STX);
}

/**
 * reset
 * 
 * Reset CC1101
 */
void CC1101_reset(void) {
  cc1101_Deselect();  // Deselect CC1101
  delay(1);
  cc1101_Select();  // Select CC1101
  delay(1);
  cc1101_Deselect();  // Deselect CC1101
  delay(1);
  cc1101_Select();  // Select CC1101

  wait_Miso();                // Wait until MISO goes low
  SPI.transfer(CC1101_SRES);  // Send reset command strobe
  wait_Miso();                // Wait until MISO goes low

  cc1101_Deselect();  // Deselect CC1101
}

void ConfigureCC1101() {
  setCCregs();  // Reconfigure CC1101
}

uint8_t VerifyCC1101Config() {
  if (readReg(CC1101_IOCFG2, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_iocfg2) {
    Serial.println(readReg(CC1101_IOCFG2, CC1101_CONFIG_REGISTER), HEX);
    return (1);
  }
  if (readReg(CC1101_IOCFG1, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_iocfg1)
    return (2);
  if (readReg(CC1101_IOCFG0, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_iocfg0)
    return (3);
  if (readReg(CC1101_FIFOTHR, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_fifothr)
    return (4);
  if (readReg(CC1101_PKTLEN, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_pktlen)
    return (5);
  if (readReg(CC1101_PKTCTRL1, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_pktctrl1)
    return (6);
  if (readReg(CC1101_PKTCTRL0, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_pktctrl0)
    return (7);
  if (readReg(CC1101_FSCTRL1, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_fsctrl1)
    return (8);
  if (readReg(CC1101_FSCTRL0, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_fsctrl0)
    return (9);
  if (readReg(CC1101_FREQ2, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_freq2)
    return (10);
  if (readReg(CC1101_FREQ1, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_freq1)
    return (11);
  if (readReg(CC1101_FREQ0, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_freq0)
    return (12);
  if (readReg(CC1101_DEVIATN, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_deviatn)
    return (13);
  if (readReg(CC1101_MDMCFG4, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_mdmcfg4)
    return (14);
  if (readReg(CC1101_MDMCFG3, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_mdmcfg3)
    return (15);
  if (readReg(CC1101_MDMCFG2, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_mdmcfg2)
    return (16);
  if (readReg(CC1101_MDMCFG1, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_mdmcfg1)
    return (17);
  if (readReg(CC1101_MDMCFG0, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_mdmcfg0)
    return (18);
  if (readReg(CC1101_MCSM2, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_mcsm2)
    return (19);
  if (readReg(CC1101_MCSM1, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_mcsm1)
    return (20);
  if (readReg(CC1101_MCSM0, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_mcsm0)
    return (21);
  if (readReg(CC1101_FOCCFG, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_foccfg)
    return (22);
  if (readReg(CC1101_BSCFG, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_bscfg)
    return (23);
  if (readReg(CC1101_AGCCTRL2, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_agcctrl2)
    return (24);
  if (readReg(CC1101_AGCCTRL1, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_agcctrl1)
    return (25);
  if (readReg(CC1101_AGCCTRL0, CC1101_CONFIG_REGISTER) != cc1101_settings.cc1101_defval_agcctrl0)
    return (26);

  return (0);
}

boolean GetCarrierStatus() {
#ifndef USE_HW_CD
  uint8_t ret;

  ret = readStatusReg(CC1101_PKTSTATUS);

  if ((ret & 0x40) == 0) {
    return (false);
  } else {
    return (true);
  }
#else
  if (digitalRead(CC1101_CD) == HIGH) {
    return (true);
  } else {
    return (false);
  }
#endif
}

void WaitCarrierEnd() {
  while (GetCarrierStatus() == true) {
    //wait for carrier detect to change to low state
    delayMicroseconds(100);
  }
}

uint8_t GetState() {
  uint8_t ret;
  ret = readStatusReg(CC1101_MARCSTATE);
  return (ret);
}

bool CC1101_IsInRX() {
  const uint8_t CC1101STATE_RX = 0x0D;

  if (GetState() == CC1101STATE_RX) {
    return (true);
  }
  return (false);
}

void ManualCalibrate() {
  uint32_t ts = micros();
  const uint32_t CalTimeout = 500;
  //Serial.println(F("Calibrating..."));
  setIdleState();
  StartCalibration();
  delayMicroseconds(100);
  while ((GetState() != 0x01) && (micros() - ts < CalTimeout)) {};  //wait for idle state
                                                                    //Serial.println(F("Calibration complete"));
}

uint8_t Get_RX_FIFO_Count() {
  return (readStatusReg(CC1101_RXBYTES));
}

void Flush_RX_FIFO(bool ReEnableRXMode) {
  setIdleState();
  flushRxFifo();
  if (ReEnableRXMode) {
    setRxState();
  }
}
bool IsRX_FIFO_Overflow() {
  if ((Get_RX_FIFO_Count() & 0x80) == 0x80) {
    return (true);
  } else {
    return (false);
  }
}

uint8_t ReadFIFO() {
  return (readStatusReg(CC1101_RXFIFO));
}

#endif  // CC1101_H
