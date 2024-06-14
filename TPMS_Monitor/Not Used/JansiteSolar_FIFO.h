//under development!!!!!

#define CD_END_DELAY_TIME  2500
#ifdef UK_433MHz

    
    #define EXPECTEDBITCOUNT 88
    #define EXPECTEDBYTECOUNT 11
    #define EXPECTEDFIFOBYTECOUNT 18
    
    #define SYNCBITS 24
    
    #define CDWIDTH_MIN 18500
    #define CDWIDTH_MAX 25000
    
    #define SHORTTIMING_MIN 35
    #define SHORTTIMING_MAX 79
    #define LONGTIMING_MIN 80
    #define LONGTIMING_MAX 120
    #define SYNCTIMING_MIN 175
    #define SYNCTIMING_MAX 1200
    
    #define ENDTIMING_MIN  0
    #define ENDTIMING_MAX  500


    #define CC1101_DEFVAL_IOCFG2     0x16        // GDO2 Output Pin Configuration - Serial out (synchronous)
    #define CC1101_DEFVAL_IOCFG1     0x2E        // GDO1 Output Pin Configuration - not used
    #define CC1101_DEFVAL_IOCFG0     0x06        // GDO0 Output Pin Configuration - Carrier Sense output
    #define CC1101_DEFVAL_FIFOTHR    0x4F        // RX FIFO and TX FIFO Thresholds - 64 bytes in FIFO
    #define CC1101_DEFVAL_SYNC1      0xA6        // Synchronization word, high byte  10100110 10100110
    #define CC1101_DEFVAL_SYNC0      0xA6        // Synchronization word, low byte
    #define CC1101_DEFVAL_PKTLEN     0x09        // Packet Length
    #define CC1101_DEFVAL_PKTCTRL1   0x00        // Packet Automation Control
    #define CC1101_DEFVAL_PKTCTRL0   0x12 //0x30        // Packet Automation Control - synchronous data
    #define CC1101_DEFVAL_ADDR       0x5A        // Device Address
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


     #error Jansite Solar timings not defined for 315MHz


#endif

void DecodeTPMS()
{
  int16_t i;
  uint32_t id = 0;
  uint16_t status, pressure1, pressure2, temp;
   double realpressure;
  float realtemp;
  bool IDFound = false;


  for (i = 2; i <= 4; i++)
  {
    id = id << 8;
    id = id + RXBytes[i];

  }
  //id = (id >> 4) & 0xFFFFFFFL;
  GetPreferredIndexStr(id, Ref);
  

  // id = (unsigned)RXBytes[0] << 24 | RXBytes[1] << 16 | RXBytes[2] << 8 | RXBytes[3];

  status = RXBytes[5] & 0x0F;

  pressure1 = RXBytes[7];

  temp = RXBytes[6];

  pressure2 = pressure1;



  if (pressure1 != pressure2)
  {
    #ifdef SHOWDEBUGINFO
       Serial.println(F("Pressure check mis-match"));
    #endif
    return;
  }

  realpressure = (double)pressure1;
  realpressure = realpressure * 1.6;  //kpa
  realpressure = realpressure * 0.145038;  //psi

  realtemp = (float)temp;
  realtemp = realtemp - 55.0;
//  #ifdef DISPLAY_TEMP_AS_FAHRENHEIT
//     realtemp = ((realtemp * 9.0)/5.0) + 32.0;
//  #endif  
  //realtemp = (temp - 32.0) * 0.5555556;

#ifdef SHOWVALIDTPMS
  Serial.print(F("Pos: "));
  Serial.print(Ref);
  Serial.print(F("   ID: "));
  Serial.print(id, HEX);
  Serial.print(F("   Status: 0x"));
  Serial.print(status,HEX);
  Serial.print(F("   Temperature: "));
  Serial.print(realtemp);
  Serial.print(F("   Tyre Pressure: "));
  Serial.print(realpressure);
  Serial.println(F(""));
#endif

  //DisplayStatusInfo();


  MatchIDandUpdate(id,status, realtemp, realpressure);

  #ifdef SHOWVALIDTPMS
     Serial.println(F(""));
  #endif


  //UpdateDisplay();
}





void ConvertTimingsToBits()
{
   int16_t i;
   
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
          if (IsTooShort(Timings[i] ) || IsTooLong(Timings[i] ) )
          {
            
             if (i < TimingsIndex/2)  //enough bits in the buffer to continue trying?
             { //invalid bit timing, reset
                 
                 BitCount = 0;
             }
             else
             {// end the conversion
                //assume an end bit
                if (IsTooLong(Timings[i]) )
                {
                  IncomingBits[BitCount++] = CurrentState;
                }
//                #ifdef SHOWDEBUGINFO
//                   Serial.print(F("ConvertTimingsToBits exited at index: "));
//                   Serial.print(i);
//                   Serial.print(F(" bitcount: "));
//                   Serial.print(BitCount);
//                   Serial.print(F("  Timing value = "));
//                   Serial.println(Timings[i]);
//                #endif
                return;
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



//bool ValidateTimings()
//{
//
//
//  uint8_t BitWidth;
//  uint8_t BitWidthNext;
//  uint8_t BitWidthNextPlus1;
//  uint8_t BitWidthPrevious;
//  uint8_t diff = TimingsIndex - CheckIndex;
//  //uint32_t tmp;
//  bool WaitingTrailingZeroEdge = false;
//  int16_t ret;
//  int16_t ManchesterStartPos = -1;
//  uint8_t ByteCount = 0;
//  uint8_t crcResult;
//
//  StartDataIndex = 0;
//
//  if (TimingsIndex < (SYNCBITS + EXPECTEDBITCOUNT) ) //header + valid data (minimum)
//  { //not enough in the buffer to consider a valid message
//    #ifdef SHOWDEBUGINFO
//       Serial.println(F("Insufficient data in buffer"));
//    #endif
//    return (false);
//  }
//
////  if (TimingsIndex > 200)  //header + valid data (minimum)
////  { //not enough in the buffer to consider a valid message
////    #ifdef SHOWDEBUGINFO
////       Serial.println(F("Excessive data in buffer"));
////    #endif
////    return (false);
////  }
//
//  //Serial.print("Timings index = ");
//  //Serial.println(TimingsIndex);
//
//  ConvertTimingsToBits();
//
//  InvertBitBuffer();
//
//  //const uint8_t pattern[] = {0xA6,0xA6, 0x5A};
//  const uint8_t pattern[] = {0x59,0x59, 0xA5};
//  ManchesterStartPos = FindManchesterStart(pattern, 24) - 24;
//  if (ManchesterStartPos < 0) ManchesterStartPos = 0;
//  
//  StartDataIndex = ManchesterStartPos;
//
//  if (ManchesterStartPos == -1 )
//  {
//    #ifdef SHOWDEBUGINFO
//       Serial.println(F("Header not found"));
//    #endif
//
//    return (false);   
////  }
////  else
////  {
////     #ifdef SHOWDEBUGINFO
////       Serial.print("Timings index = ");
////       Serial.println(TimingsIndex);
////       Serial.print("CD Width = ");
////       Serial.println(CD_Width);
////       Serial.print("Bit count = ");
////       Serial.println(BitCount);
////       PrintTimings(0,TimingsIndex);
////       PrintData(BitCount);
////    #endif 
//  }
//
//  ByteCount = ManchesterDecode(ManchesterStartPos);
//  if (ByteCount >= EXPECTEDBYTECOUNT)
//  {
//      if ((RXBytes[0] != 0xDD) || (RXBytes[1] != 0x33))
//      {
//          #ifdef SHOWDEBUGINFO
//            Serial.print(F("Sync Check failed: Expected 0xDD 0x33, received 0x"));
//            Serial.print(RXBytes[0], HEX);
//            Serial.print(F(" 0x"));
//            Serial.println(RXBytes[1], HEX);
//            PrintBytes(ByteCount);
//          #endif
//          return(false);        
//      }
//      
//      
//      //check the checksum...
//      uint16_t ReceivedCRC = (( uint16_t)RXBytes[9] << 8) | ( uint16_t)RXBytes[10];
//      uint16_t crcResult16;
//      crcResult16 = Compute_CRC16(2,7,0x8005,0x0000  );
//      if (ReceivedCRC != crcResult16)
//      {
//         #ifdef SHOWDEBUGINFO
//          Serial.print(F("CRC calc: "));
//          Serial.print(crcResult16, HEX);
//          Serial.print(F("  CRC rcvd: "));
//          Serial.println(ReceivedCRC, HEX);
//          Serial.println(F("CRC Check failed"));
//          PrintBytes(ByteCount);
//          #endif
//        #ifdef IGNORECHECKSUMERRORS
//          DecodeTPMS();
//          TPMS_Changed = false;  //don't update display for csum error
//        #endif
//        return(false);
//      }
//      else
//      {
//         #ifdef SHOWDEBUGINFO
//           Serial.println(F("CRC Check OK"));
//         #endif
//        //decode the message...
//        DecodeTPMS();
//        TPMS_Changed = true;  //indicates the display needs to be updated.
//        return(true);
//      }
//
//
//  }
//  else
//  {
//    #ifdef SHOWDEBUGINFO
//       Serial.print(F("Insufficient bytes: "));
//       Serial.print(ByteCount);
//       Serial.print(F(" received, expected at least: "));
//       Serial.println(EXPECTEDBYTECOUNT);
//       PrintTimings(0,ByteCount * 8);
//    #endif
//    return (false);
//  }
//}


bool ValidateTimings()
{

  int16_t ret,j;
  int16_t ManchesterStartPos = -1;
  uint8_t ByteCount = 0;
  uint8_t crcResult;
  uint8_t RX_FIFO[EXPECTEDFIFOBYTECOUNT + 2];
  uint8_t RX_FIFO_Index;
  uint8_t i;
  uint8_t FIFO_Data;

  if (Get_RX_FIFO_Count() < EXPECTEDFIFOBYTECOUNT)
  {
     return(false);
  }

  StartDataIndex = 0;

  RX_FIFO_Index = 0;
  //read FIFO bytes and convert back to bits
  RX_FIFO[RX_FIFO_Index++] = CC1101_DEFVAL_SYNC1;
  RX_FIFO[RX_FIFO_Index++] = CC1101_DEFVAL_SYNC0;
  for (i=RX_FIFO_Index; i<EXPECTEDFIFOBYTECOUNT+2;i++)
  {
     RX_FIFO[i] = ReadFIFO();
  }
  #ifdef SHOWDEBUGINFO 
    Serial.println(F("FIFO Data:")); 
    for (i=0; i<EXPECTEDFIFOBYTECOUNT+2;i++)
    {
       Serial.print(RX_FIFO[i], HEX);
       Serial.print(F(" "));
    }
    Serial.println(F("")); 
  #endif
  
  //translate FIFO data to bits
  BitCount = 0;
  for (i=0; i<EXPECTEDFIFOBYTECOUNT+2;i++)
  {
     FIFO_Data = RX_FIFO[i];
     for (j=7;j>=0;j--)
     {
        IncomingBits[BitCount++] = bitRead(FIFO_Data,j);
     }
   }


  InvertBitBuffer();
  ManchesterStartPos = 0;
  StartDataIndex = ManchesterStartPos;


  ByteCount = ManchesterDecode(ManchesterStartPos);
  //PrintBytes(ByteCount);
  if (ByteCount >= EXPECTEDBYTECOUNT)
  {
      
      //check the checksum...
      crcResult = Compute_CRC_SUM(0,EXPECTEDBYTECOUNT-1, 0x00);
      if (crcResult != RXBytes[9])
      {
        #ifdef SHOWDEBUGINFO
           Serial.println(F("CRC Check failed"));
        #endif
        #ifdef IGNORECHECKSUMERRORS
          DecodeTPMS();
          TPMS_Changed = false;  //don't update display for csum error
        #endif
        return (false);
      }
      else
      {
         #ifdef SHOWDEBUGINFO
           Serial.println(F("CRC Check OK"));
         #endif
        //decode the message...
        DecodeTPMS();
        TPMS_Changed = true;  //indicates the display needs to be updated.
        return (true);
      }


  }
  else
  {
//    #ifdef SHOWDEBUGINFO
//       Serial.print(F("Insufficient bytes: "));
//       Serial.print(ByteCount);
//       Serial.print(F(" received, expected at least: "));
//       Serial.println(EXPECTEDBYTECOUNT);
//       //PrintTimings(0,ByteCount * 8);
//    #endif
    return (false);
  }


}
