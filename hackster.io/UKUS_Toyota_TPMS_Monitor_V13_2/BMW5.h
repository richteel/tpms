
//Audi E-tron


#ifdef UK_433MHz


    #define EXPECTEDBITCOUNT 88
    #define EXPECTEDBASEBITCOUNT 190  //Manchester coding so double number of 25us bits
    #define EXPECTEDBYTECOUNT 11
    #define SYNCBITS 11
  
    #define CDWIDTH_MIN 5400
    #define CDWIDTH_MAX 7000 //10500
  
    #define SHORTTIMING_MIN 20
    #define SHORTTIMING_NOM 25
    #define SHORTTIMING_MAX 39
    #define LONGTIMING_MIN 40
    #define LONGTIMING_MAX 60
    #define SYNCTIMING_MIN 175
    #define SYNCTIMING_MAX 1200
  
    #define ENDTIMING_MIN  0
    #define ENDTIMING_MAX  250


    #define CC1101_DEFVAL_IOCFG2     0x4C        // GDO2 Output Pin Configuration - Serial out (synchronous)
    #define CC1101_DEFVAL_IOCFG1     0x2E        // GDO1 Output Pin Configuration - not used
    #define CC1101_DEFVAL_IOCFG0     0x0E        // GDO0 Output Pin Configuration - Carrier Sense output
    #define CC1101_DEFVAL_FIFOTHR    0x0F        // RX FIFO and TX FIFO Thresholds - 64 bytes in FIFO
    #define CC1101_DEFVAL_SYNC1      0xD5        // Synchronization word, high byte  11010101 01001111
    #define CC1101_DEFVAL_SYNC0      0x4F        // Synchronization word, low byte
    #define CC1101_DEFVAL_PKTLEN     0x09        // Packet Length
    #define CC1101_DEFVAL_PKTCTRL1   0x00        // Packet Automation Control
    #define CC1101_DEFVAL_PKTCTRL0   0x12 //0x30        // Packet Automation Control - synchronous data
    #define CC1101_DEFVAL_ADDR       0x00        // Device Address
    #define CC1101_DEFVAL_CHANNR     0x00        // Channel Number
    #define CC1101_DEFVAL_FSCTRL1    0x0F        // Frequency Synthesizer Control (was 0x06)
    #define CC1101_DEFVAL_FSCTRL0    0x00        // Frequency Synthesizer Control
    
    // Carrier frequency = 433.919830 MHz
    #define CC1101_DEFVAL_FREQ2  0x10        // Frequency Control Word, High Byte
    #define CC1101_DEFVAL_FREQ1  0xB0        // Frequency Control Word, Middle Byte
    #define CC1101_DEFVAL_FREQ0  0x71        // Frequency Control Word, Low Byte

    #define CC1101_DEFVAL_DEVIATN    0x40      // Modem Deviation Setting (+/-25.390625kHz)

    #define CC1101_DEFVAL_MDMCFG4    0x5A        // Modem Configuration (59 = data rate = 40kHz RX bandwidth 325kHz)
    #define CC1101_DEFVAL_MDMCFG3    0x93        // Modem Configuration (now 93 = data rate = 40kHz)
    #define CC1101_DEFVAL_MDMCFG2    0x10        // Modem Configuration (GFSK, No Sync or Manchester coding)
    #define CC1101_DEFVAL_MDMCFG1    0x21        // Modem Configuration Channel spacing 100kHz
    #define CC1101_DEFVAL_MDMCFG0    0xF8        // Modem Configuration      
    #define CC1101_DEFVAL_AGCCTRL2   0x87       // AGC Control
    #define CC1101_DEFVAL_AGCCTRL1   0x58        // AGC Control
    #define CC1101_DEFVAL_AGCCTRL0   0x80        // AGC Control
    
    #define CC1101_DEFVAL_MCSM2      0x07        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_MCSM1      0x3C        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_MCSM0      0x18 //0x18       // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_FOCCFG     0x16        // Frequency Offset Compensation Configuration
    #define CC1101_DEFVAL_BSCFG      0x6C        // Bit Synchronization Configuration

    
    #define CC1101_DEFVAL_WOREVT1    0x87        // High Byte Event0 Timeout
    #define CC1101_DEFVAL_WOREVT0    0x6B        // Low Byte Event0 Timeout
    #define CC1101_DEFVAL_WORCTRL    0xFB        // Wake On Radio Control
    #define CC1101_DEFVAL_FREND1     0x56        // Front End RX Configuration
    #define CC1101_DEFVAL_FREND0     0x10        // Front End TX Configuration
    
    #define CC1101_DEFVAL_FSCAL3     0xE9        // Frequency Synthesizer Calibration
    #define CC1101_DEFVAL_FSCAL2     0x2A        // Frequency Synthesizer Calibration
    #define CC1101_DEFVAL_FSCAL1     0x00        // Frequency Synthesizer Calibration
    #define CC1101_DEFVAL_FSCAL0     0x1F        // Frequency Synthesizer Calibration
    
    #define CC1101_DEFVAL_RCCTRL1    0x41        // RC Oscillator Configuration
    #define CC1101_DEFVAL_RCCTRL0    0x00        // RC Oscillator Configuration
    
    #define CC1101_DEFVAL_FSTEST     0x59        // Frequency Synthesizer Calibration Control
    
    #define CC1101_DEFVAL_PTEST      0x7F        // Production Test
    #define CC1101_DEFVAL_AGCTEST    0x3F        // AGC Test
    
    #define CC1101_DEFVAL_TEST2      0x81        // Various Test Settings
    #define CC1101_DEFVAL_TEST1      0x35        // Various Test Settings
    #define CC1101_DEFVAL_TEST0      0x09        // Various Test Settings



      
 
#elif US_315MHz


  #error Audi E-tron timings not defined for 315MHz 


#endif

void DecodeTPMS()
{
  int16_t i;
  uint8_t ManufacturerID, Flags1, Flags2, Flags3;
  uint32_t id = 0;
  uint16_t status, pressure1, pressure2, temp;
  double realpressure;
  float realtemp;

  ManufacturerID = RXBytes[0];

  
  
  for (i = 1; i <= 4; i++)
  {
    id = id << 8;
    id = id + RXBytes[i];

  }

  id = id & 0xFFFFFFFF;

  GetPreferredIndexStr(id, Ref);

  pressure1 = RXBytes[5];

  temp = RXBytes[6];

  Flags1 = RXBytes[7];
  Flags2 = RXBytes[8];
  Flags3 = RXBytes[9];


  realpressure = (double)pressure1;
  realpressure = (realpressure * 0.35534); //kpa to PSI: (2.45 /6.895 = 0.35534)
  if (realpressure < 0) 
     realpressure = 0.0;
  realtemp = (float)temp;
  realtemp = realtemp - 52.0;



#ifdef SHOWVALIDTPMS
  Serial.print(F("Pos: "));
  Serial.print(Ref);
  Serial.print(F("   Manuf ID: "));
  switch(ManufacturerID)
  {
    case 0x00: Serial.print(F("Audi"));
               break;
    case 0x03: Serial.print(F("HUF/Beru"));
               break;
    case 0x23: Serial.print(F("Schrader/Sensata"));
               break;
    case 0x80: Serial.print(F("Continental"));
               break;
    default:   Serial.print(F("Undefined(0x"));
               Serial.print(ManufacturerID,HEX);
               Serial.print(F(")"));
  }
  Serial.print(F("   ID: "));
  Serial.print(id, HEX);
  Serial.print(F("   Flags1: 0x"));
  Serial.print(Flags1,HEX);
  Serial.print(F("   Flags2: 0x"));
  Serial.print(Flags2,HEX);
  Serial.print(F("   Flags3: 0x"));
  Serial.print(Flags3,HEX);
  Serial.print(F("   Temperature: "));
  Serial.print(realtemp);
  Serial.print(F("   Tyre Pressure: "));
  Serial.print(realpressure);
  Serial.print(F(" (psi)  "));
  Serial.print(realpressure * KPA2PSI);
  Serial.print(F(" (kpa)"));
  Serial.println(F(""));
#endif

  MatchIDandUpdate(id,status, realtemp, realpressure);

  #ifdef SHOWVALIDTPMS
     Serial.println(F(""));
  #endif


}


bool ValidateTimingsFast()
{
  int16_t ByteCount = 0;
  uint8_t crcResult = 0;
  int16_t ManchesterStartPos = -1;

  BitCount = BaseBitCount;
  
  if (BaseBitCount >= EXPECTEDBASEBITCOUNT)
  {
      const uint8_t pattern[] = {0xAA, 0x59};
      ManchesterStartPos = FindManchesterStart(pattern, 16);
      StartDataIndex = ManchesterStartPos;
    
      if (ManchesterStartPos == -1 )
      {
        #ifdef SHOWDEBUGINFO
           Serial.println(F("BMW header not found"));
        #endif
    
        return(false);   

      }
    
      ByteCount = ManchesterDecode_ZeroBit(ManchesterStartPos);
      if (ByteCount == EXPECTEDBYTECOUNT)
      {
           //debug purposes only!
           PrintBytes(EXPECTEDBYTECOUNT);
           
           crcResult = Compute_CRC8(10,0x2F, 0xAA);  //Checksum
           if (crcResult != RXBytes[10])
          {
             Serial.println(F("CRC Check failed"));
            #ifdef IGNORECHECKSUMERRORS
              DecodeTPMS();
              TPMS_Changed = false;  //don't update display for csum error
            #endif
            return(false);
          }
          else
          {
            Serial.println(F("CRC Check OK"));
            //decode the message...
            DecodeTPMS();
            TPMS_Changed = true;  //indicates the display needs to be updated.
            return(true);
          }
         
      }
      else
      {
        return(false);
      }
  }
  else
  {
    return(false);
  }
  

}
