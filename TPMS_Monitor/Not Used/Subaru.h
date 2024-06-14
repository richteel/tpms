


#define CD_END_DELAY_TIME  2500
#ifdef UK_433MHz
    //Subaru Impreza 09/2016-12/2022 Sensor: Schrader PN 28103FL000/28103FL00A
    //Uses FSK with 50us pulse widths (different protocol from 315MHz)
    
    #define EXPECTEDBITCOUNT 72
    #define EXPECTEDBYTECOUNT 9
    
    #define SYNCBITS 24
    
    #define CDWIDTH_MIN 8500
    #define CDWIDTH_MAX 20000
    
    #define SHORTTIMING_MIN 35
    #define SHORTTIMING_NOM 50
    #define SHORTTIMING_MAX 79
    #define LONGTIMING_MIN 80
    #define LONGTIMING_MAX 160
    #define SYNCTIMING_MIN 175
    #define SYNCTIMING_MAX 1200
    
    #define ENDTIMING_MIN  0
    #define ENDTIMING_MAX  500


    #define CC1101_DEFVAL_IOCFG2     0x0C        // GDO2 Output Pin Configuration - Serial out (synchronous)
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

    #define CC1101_DEFVAL_MDMCFG4    0x59        // Modem Configuration (59 = data rate = 20kHz - actual data rate is 10kHz but due to bi-phase coding need to double the rate, RX bandwidth 325kHz)
    #define CC1101_DEFVAL_MDMCFG3    0x93        // Modem Configuration (now 93 = data rate = 20kHz)
    #define CC1101_DEFVAL_MDMCFG2    0x10        // Modem Configuration (GFSK, No Sync or Manchester coding)
    #define CC1101_DEFVAL_MDMCFG1    0x21        // Modem Configuration Channel spacing 100kHz
    #define CC1101_DEFVAL_MDMCFG0    0xF8        // Modem Configuration      
    #define CC1101_DEFVAL_AGCCTRL2   0x87       // AGC Control
    #define CC1101_DEFVAL_AGCCTRL1   0x58        // AGC Control
    #define CC1101_DEFVAL_AGCCTRL0   0x80        // AGC Control
    
    #define CC1101_DEFVAL_MCSM2      0x07        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_MCSM1      0x3C        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_MCSM0      0x18        // Main Radio Control State Machine Configuration
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
     //Subaru Impreza 07/2013-12/2022 Sensor: Schrader PN 28103SG000/28103AJ00A
     //Uses ASK with 100us pulse widths (different protocol from 433MHz), looks to be same as RTL433 Schrader SMD3MA4

    #define EXPECTEDBITCOUNT 42
    #define EXPECTEDBYTECOUNT 5 //4 + 2 bits)
    
    #define SYNCBITS 24
    
    #define CDWIDTH_MIN 10000
    #define CDWIDTH_MAX 23000
    
    #define SHORTTIMING_MIN 70
    #define SHORTTIMING_NOM 100
    #define SHORTTIMING_MAX 159
    #define LONGTIMING_MIN 160
    #define LONGTIMING_MAX 300
    #define SYNCTIMING_MIN 175
    #define SYNCTIMING_MAX 1200
    
    #define ENDTIMING_MIN  0
    #define ENDTIMING_MAX  500


    #define CC1101_DEFVAL_IOCFG2     0x0C        // GDO2 Output Pin Configuration - Serial out (synchronous)
    #define CC1101_DEFVAL_IOCFG1     0x2E        // GDO1 Output Pin Configuration - not used
    #define CC1101_DEFVAL_IOCFG0     0x0E        // GDO0 Output Pin Configuration - Carrier Sense output
    #define CC1101_DEFVAL_FIFOTHR    0x4F        // RX FIFO and TX FIFO Thresholds - 64 bytes in FIFO
    #define CC1101_DEFVAL_SYNC1      0xD5        // Synchronization word, high byte  11010101 01001111
    #define CC1101_DEFVAL_SYNC0      0x4F        // Synchronization word, low byte
    #define CC1101_DEFVAL_PKTLEN     0x09        // Packet Length
    #define CC1101_DEFVAL_PKTCTRL1   0x00        // Packet Automation Control
    #define CC1101_DEFVAL_PKTCTRL0   0x12 //0x30        // Packet Automation Control - synchronous data
    #define CC1101_DEFVAL_ADDR       0x00        // Device Address
    #define CC1101_DEFVAL_CHANNR     0x00        // Channel Number
    #define CC1101_DEFVAL_FSCTRL1    0x0F        // Frequency Synthesizer Control (was 0x06)
    #define CC1101_DEFVAL_FSCTRL0    0x00        // Frequency Synthesizer Control
    
    // Carrier frequency = 314.979828 MHz
    #define CC1101_DEFVAL_FREQ2  0x0C        // Frequency Control Word, High Byte
    #define CC1101_DEFVAL_FREQ1  0x1D        // Frequency Control Word, Middle Byte
    #define CC1101_DEFVAL_FREQ0  0x57        // Frequency Control Word, Low 

    #define CC1101_DEFVAL_DEVIATN    0x40      // Modem Deviation Setting (+/-25.390625kHz)

    #define CC1101_DEFVAL_MDMCFG4    0x58        // Modem Configuration (59 = data rate = 8kHz - actual data rate is 4kHz but due to bi-phase coding need to double the rate, RX bandwidth 325kHz)
    #define CC1101_DEFVAL_MDMCFG3    0x43        // Modem Configuration (now 43 = data rate = 8kHz)
    #define CC1101_DEFVAL_MDMCFG2    0x34        // Modem Configuration (ASK, no preamble, No Sync or Manchester coding)
    #define CC1101_DEFVAL_MDMCFG1    0x21        // Modem Configuration Channel spacing 100kHz
    #define CC1101_DEFVAL_MDMCFG0    0xF8        // Modem Configuration      
    #define CC1101_DEFVAL_AGCCTRL2   0x64 //0x64       // AGC Control
    #define CC1101_DEFVAL_AGCCTRL1   0x78 //0x78        // AGC Control
    #define CC1101_DEFVAL_AGCCTRL0   0xB3 //0xB3        // AGC Control
    
    #define CC1101_DEFVAL_MCSM2      0x07        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_MCSM1      0x3C        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_MCSM0      0x18        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_FOCCFG     0x14   //0x16        // Frequency Offset Compensation Configuration
    #define CC1101_DEFVAL_BSCFG      0x6C        // Bit Synchronization Configuration

    
    #define CC1101_DEFVAL_WOREVT1    0x87        // High Byte Event0 Timeout
    #define CC1101_DEFVAL_WOREVT0    0x6B        // Low Byte Event0 Timeout
    #define CC1101_DEFVAL_WORCTRL    0xFB        // Wake On Radio Control
    #define CC1101_DEFVAL_FREND1     0xB6  //0x56        // Front End RX Configuration
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


#else
     #error Subaru timings not defined,, choose 433MHz or 325MHz


#endif


void ConvertTimingsToBits()
{
   int16_t i,x;
   
   //bool CurrentState = FirstEdgeState;
   bool CurrentState = FirstEdgeIsHighToLow?true:false;
   BitCount = 0;
   

   for (i=0;i<= TimingsIndex;i++)
   {
      if (IsValidShort(Timings[i]) )
      {
         IncomingBits[BitCount++] = CurrentState;
      }
      else
      {
        if (IsValidLong(Timings[i]) )
        {
           IncomingBits[BitCount++] = CurrentState;
           IncomingBits[BitCount++] = CurrentState;
        }
        else
        {
          if (IsTooLong(Timings[i] ) && (i< 40))
          {
             for (x = 1;x<= (int)((((float)Timings[i]/SHORTTIMING_NOM)) + 0.5);x++)
             {
                IncomingBits[BitCount++] = CurrentState;
             }           
          }
          else
          {
          
          
            if (IsTooShort(Timings[i] ) || IsTooLong(Timings[i] ) )
            {
            
               if (i < TimingsIndex/2)  //enough bits in the buffer to continue trying?
               { //invalid bit timing, reset
                   
                   BitCount = 0;
                   ValidTimingsStart = i+1;
               }
               else
               {// end the conversion
                  //assume an end bit
                  if (IsTooLong(Timings[i]) )
                  {
                    IncomingBits[BitCount++] = CurrentState;
                  }
//                  #ifdef SHOWDEBUGINFO
//                     Serial.print(F("ConvertTimingsToBits exited at index: "));
//                     Serial.print(i);
//                     Serial.print(F(" bitcount: "));
//                     Serial.print(BitCount);
//                     Serial.print(F("  Timing value = "));
//                     Serial.println(Timings[i]);
//                  #endif
                  return;
               }
            }
          }
        }

      }
      CurrentState = !CurrentState;

      if (BitCount >= MAXBITS-1) 
      {
         #ifdef SHOWDEBUGINFO
            Serial.println(F("Exited ConvertTimingsToBits with botcount > MAXBITS-1"));
         #endif
         return;
      }
   }
  
}


#ifdef UK_433MHz
  void DecodeTPMS()
  {
    int16_t i;
    uint32_t id = 0;
    uint16_t status, pressure1,  temp;
    double realpressure;
    float realtemp;
    bool BatteryIsLow = false;
  
  
    for (i = 0; i <= 3; i++)
    {
      id = id << 8;
      id = id + RXBytes[i];
  
    }
  
    GetPreferredIndexStr(id, Ref);
  
    // id = (unsigned)RXBytes[0] << 24 | RXBytes[1] << 16 | RXBytes[2] << 8 | RXBytes[3];
  
    status = RXBytes[7];
    if (status && 0x80 == 0x80)
    {
      BatteryIsLow = true;
    }
    
  
  
    temp = RXBytes[6];
    realtemp = (float)temp;
    realtemp = realtemp - 52;
    pressure1 = RXBytes[4];
    realpressure =  ((double)(pressure1) * 0.4) + 0.1 ;
  
  
  
    if (realpressure < 0)
       realpressure = 0.0;
  
  
  
  
  #ifdef SHOWVALIDTPMS
    Serial.print(F("Pos: "));
    Serial.print(Ref);
    Serial.print(F("   ID: "));
    Serial.print(id, HEX);
    Serial.print(F("   Status: 0x"));
    Serial.print(status,HEX);
    Serial.print(F("   Temperature: "));
    if (realtemp == NO_VALID_TEMPERATURE)
    {
       Serial.print("---");
    }
    else
    {
       Serial.print(realtemp);
    }
    Serial.print(F("   Tyre Pressure: "));
    Serial.print(realpressure);
  //  Serial.print(F("   Sudden pressure change?: "));
  //  if (status & 0x10)
  //  {
  //    Serial.print(F("Yes"));
  //  }
  //  else
  //  {
  //    Serial.print(F("No"));
  //  }
  //  Serial.print(F("   Manual trigger (LF)?: "));
  //  if (status & 0x01)
  //  {
  //    Serial.print(F("Yes"));
  //  }
  //  else
  //  {
  //    Serial.print(F("No"));
  //  }
  //  Serial.println(F(""));
  #endif
  
    //DisplayStatusInfo();
  
     MatchIDandUpdate(id,status, realtemp, realpressure);
     
  
    #ifdef SHOWVALIDTPMS
       Serial.println(F(""));
    #endif
  }
  

  bool ValidateTimings()
  {
  

    int16_t ManchesterStartPos = -1;
    uint8_t ByteCount = 0;
    uint8_t crcResult;
    uint8_t ReceivedCRC = 0;
  
    StartDataIndex = 0;
  
    if (TimingsIndex < (SYNCBITS + EXPECTEDBITCOUNT) ) //header + valid data (minimum)
    { //not enough in the buffer to consider a valid message
      #ifdef SHOWDEBUGINFO
         Serial.println(F("Insufficient data in buffer"));
      #endif
      return (false);
    }
  
  //  if (TimingsIndex > 200)  //header + valid data (minimum)
  //  { //not enough in the buffer to consider a valid message
  //    #ifdef SHOWDEBUGINFO
  //       Serial.println(F("Excessive data in buffer"));
  //    #endif
  //    return (false);
  //  }
  
    //Serial.print("Timings index = ");
    //Serial.println(TimingsIndex);
  
    ConvertTimingsToBits();
    
  //  Serial.println("Incoming raw bit stream...");
  //  PrintData(0,BitCount, false);
  
  
    InvertBitBuffer();
    
  //  Serial.println("Inverted raw bits..");
  //  PrintData(0,BitCount, false);
  
    //const uint8_t pattern[] = {0xA6,0xA6, 0x5A};
    const uint8_t pattern[] = {0xAA,0xAA,0xA1};
    ManchesterStartPos = FindManchesterStart(pattern, 24) ;
    if (ManchesterStartPos < 0) ManchesterStartPos = 0;
    
    StartDataIndex = ManchesterStartPos;
  
  //  Serial.println("Bits for Manchester decoding..");
  //  PrintData(ManchesterStartPos,BitCount-ManchesterStartPos, false);
  
  
  
  
    if (ManchesterStartPos == -1 )
    {
      #ifdef SHOWDEBUGINFO
         Serial.println(F("Header not found"));
      #endif
  
      return (false);   
  //  }
  //  else
  //  {
  //     #ifdef SHOWDEBUGINFO
  //       Serial.print("Timings index = ");
  //       Serial.println(TimingsIndex);
  //       Serial.print("CD Width = ");
  //       Serial.println(CD_Width);
  //       Serial.print("Bit count = ");
  //       Serial.println(BitCount);
  //       PrintTimings(0,TimingsIndex);
  //       PrintData(BitCount);
  //    #endif 
    }
  
  
  
    ByteCount = ManchesterDecode(ManchesterStartPos);
  
  //  Serial.println("Manchester decoded bits..");
  //  PrintManchesterData(0,  ManchesterBitCount,false);
  //
  //  Serial.print(F("Byte count = "));
  //  Serial.println(ByteCount);
  //  PrintBytes(ByteCount);
    
    if (ByteCount >= EXPECTEDBYTECOUNT)
    {
  
        
        
        //checksum unknown...
        crcResult = Compute_CRC_SUM(0, 8, 0);
        if (crcResult != RXBytes[8])
        {
           #ifdef SHOWDEBUGINFO
            Serial.print(F("CRC calc: "));
            Serial.print(crcResult, HEX);
            Serial.print(F("  CRC rcvd: "));
            Serial.println(ReceivedCRC, HEX);
            Serial.println(F("CRC Check failed"));
            PrintBytes(ByteCount);
            #endif
          #ifdef IGNORECHECKSUMERRORS
            DecodeTPMS();
            TPMS_Changed = false;  //don't update display for csum error
          #endif
          return(false);
        }
        else
        {
          //decode the message...
          DecodeTPMS();
          TPMS_Changed = true;  //indicates the display needs to be updated.
          return(true);
        }
  
  
    }
    else
    {
      #ifdef SHOWDEBUGINFO
         Serial.print(F("Insufficient bytes: "));
         Serial.print(ByteCount);
         Serial.print(F(" received, expected at least: "));
         Serial.println(EXPECTEDBYTECOUNT);
         PrintTimings(0,ByteCount * 8);
      #endif
      return (false);
    }
  
  
  }

#else

  //US 315MHz
  //  ^^^^_^_^_^_^_^_^_^_^_^_^_^_^_^ _^^^^^_FFFFFFIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIPPPPPPPPPPPPPPPPCCCC
  //inverted....
  //  ____^_^_^_^_^_^_^_^_^_^_^_^_^_ ^_____^ FFFFFFII IIIIIIII IIIIIIII IIIIIIII IIIIIIII IIIIIIII IIIIIIPP PPPPPPPP PPPPPPCC CC

  void DecodeTPMS()
  {
    int16_t i;
    uint32_t id = 0;
    uint16_t status, pressure1, pressure2, temp;
    double realpressure;
    float realtemp;
    bool IDFound = false;
    uint8_t SensorType;
    bool BatteryIsLow = false;
  
  
    for (i = 0; i <= 3; i++)
    {
      id = id << 8;
      id = id + RXBytes[i];
  
    }

    id = RXBytes[0] & 0x1F;
    id = (id << 8) + RXBytes[1];
    id = (id << 8) + RXBytes[2];
    id = id << 3;
    id = id + (RXBytes[3] >>5);
    
    
  
    GetPreferredIndexStr(id, Ref);
  
    // id = (unsigned)RXBytes[0] << 24 | RXBytes[1] << 16 | RXBytes[2] << 8 | RXBytes[3];
  
    status = RXBytes[0] >> 5;
//    if (status && 0x80 == 0x80)
//    {
//      BatteryIsLow = true;
//    }
    
  
  
    temp = 0;  //no temperature transmitted!!
    realtemp = (float)temp;
    realtemp = realtemp - 52;
    realtemp = NO_VALID_TEMPERATURE;
    //pressure1 = RXBytes[5];
    pressure1 = ((RXBytes[3] & 0x1F) << 3)  + (RXBytes[4] >> 5) ;
    Serial.print(F("Pressure byte = 0x"));
    Serial.println(pressure1,HEX);
    realpressure =  ((double)(pressure1) * 0.2) ;
  
  
  
    if (realpressure < 0)
       realpressure = 0.0;
  
  
  
  
  #ifdef SHOWVALIDTPMS
    Serial.print(F("Pos: "));
    Serial.print(Ref);
    Serial.print(F("   ID: "));
    Serial.print(id, HEX);
    Serial.print(F("   Status: 0x"));
    Serial.print(status,HEX);
    Serial.print(F("   No Temperatures Transmitted "));
    if (realtemp == NO_VALID_TEMPERATURE)
    {
       Serial.print("---");
    }
    else
    {
       Serial.print(realtemp);
    }
    Serial.print(F("   Tyre Pressure: "));
    Serial.print(realpressure);
  //  Serial.print(F("   Sudden pressure change?: "));
  //  if (status & 0x10)
  //  {
  //    Serial.print(F("Yes"));
  //  }
  //  else
  //  {
  //    Serial.print(F("No"));
  //  }
  //  Serial.print(F("   Manual trigger (LF)?: "));
  //  if (status & 0x01)
  //  {
  //    Serial.print(F("Yes"));
  //  }
  //  else
  //  {
  //    Serial.print(F("No"));
  //  }
  //  Serial.println(F(""));
  #endif
  
    //DisplayStatusInfo();
  
     MatchIDandUpdate(id,status, realtemp, realpressure);
     
  
    #ifdef SHOWVALIDTPMS
       Serial.println(F(""));
    #endif
  }
  

  bool ValidateTimings()
  {
  
  
    uint8_t BitWidth;
    uint8_t BitWidthNext;
    uint8_t BitWidthNextPlus1;
    uint8_t BitWidthPrevious;
    uint8_t diff = TimingsIndex - CheckIndex;
    //uint32_t tmp;
    bool WaitingTrailingZeroEdge = false;
    int16_t ret;
    int16_t ManchesterStartPos = -1;
    uint8_t ByteCount = 0;
    uint8_t crcResult;
    uint8_t ReceivedCRC = 0;
  
    StartDataIndex = 0;
  
    if (TimingsIndex < (SYNCBITS + EXPECTEDBITCOUNT) ) //header + valid data (minimum)
    { //not enough in the buffer to consider a valid message
      #ifdef SHOWDEBUGINFO
         Serial.println(F("Insufficient data in buffer"));
         Serial.print("Timings index = ");
         Serial.println(TimingsIndex);
      #endif
      return (false);
    }
  
  //  if (TimingsIndex > 200)  //header + valid data (minimum)
  //  { //not enough in the buffer to consider a valid message
  //    #ifdef SHOWDEBUGINFO
  //       Serial.println(F("Excessive data in buffer"));
  //    #endif
  //    return (false);
  //  }
  
    Serial.print("Timings index = ");
    Serial.println(TimingsIndex);
  
    ConvertTimingsToBits();
    
//    Serial.println("Incoming raw bit stream...");
//    PrintData(0,BitCount, false);
  
  
    InvertBitBuffer();
    
//    Serial.println("Inverted raw bits..");
//    PrintData(0,BitCount, false);
  
    //const uint8_t pattern[] = {0xA6,0xA6, 0x5A};
    const uint8_t pattern[] = {0x55,0x55,0x41};
    ManchesterStartPos = FindManchesterStart(pattern, 24) ;
    if (ManchesterStartPos < 0) ManchesterStartPos = 0;
    
    StartDataIndex = ManchesterStartPos;
  
//    Serial.println("Bits for Manchester decoding..");
//    PrintData(ManchesterStartPos,BitCount-ManchesterStartPos, false);
  
  
  
  
    if (ManchesterStartPos == -1 )
    {
      #ifdef SHOWDEBUGINFO
         Serial.println(F("Header not found"));
      #endif
  
      return (false);   
  //  }
  //  else
  //  {
  //     #ifdef SHOWDEBUGINFO
  //       Serial.print("Timings index = ");
  //       Serial.println(TimingsIndex);
  //       Serial.print("CD Width = ");
  //       Serial.println(CD_Width);
  //       Serial.print("Bit count = ");
  //       Serial.println(BitCount);
  //       PrintTimings(0,TimingsIndex);
  //       PrintData(BitCount);
  //    #endif 
    }
  
  
  
    ByteCount = ManchesterDecode(ManchesterStartPos);
  
//    Serial.println("Manchester decoded bits..");
//    PrintManchesterData(0,  ManchesterBitCount,false);
  
    Serial.print(F("Byte count = "));
    Serial.println(ByteCount);
    PrintBytes(ByteCount);
    
    if (ByteCount >= EXPECTEDBYTECOUNT)
    {
     
        //checksum unknown...
        crcResult = Compute_CRC_SUM(0, 4, 0);
            Serial.print(F("CRC calc: "));
            Serial.println(crcResult, HEX);        
        if (crcResult != crcResult )
        {
           #ifdef SHOWDEBUGINFO
            Serial.print(F("CRC calc: "));
            Serial.print(crcResult, HEX);
            Serial.print(F("  CRC rcvd: "));
            Serial.println(ReceivedCRC, HEX);
            Serial.println(F("CRC Check failed"));
            PrintBytes(ByteCount);
            #endif
          #ifdef IGNORECHECKSUMERRORS
            DecodeTPMS();
            TPMS_Changed = false;  //don't update display for csum error
          #endif
          return(false);
        }
        else
        {
          //decode the message...
          Serial.println(F("Checksum check unknown - treat data with caution!!"));
          DecodeTPMS();
          TPMS_Changed = true;  //indicates the display needs to be updated.
          return(true);
        }
  
  
    }
    else
    {
      #ifdef SHOWDEBUGINFO
         Serial.print(F("Insufficient bytes: "));
         Serial.print(ByteCount);
         Serial.print(F(" received, expected at least: "));
         Serial.println(EXPECTEDBYTECOUNT);
         PrintTimings(0,ByteCount * 8);
      #endif
      return (false);
    }
  
  
  }



#endif
