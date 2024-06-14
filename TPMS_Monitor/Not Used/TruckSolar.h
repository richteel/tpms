

#define CD_END_DELAY_TIME  2500
#ifdef UK_433MHz


    #define EXPECTEDBITCOUNT 80
    #define EXPECTEDBYTECOUNT 9
    #define SYNCBITS 16
  
    #define CDWIDTH_MIN 18500
    #define CDWIDTH_MAX 24000
  
    #define SHORTTIMING_MIN 40
    #define SHORTTIMING_NOM 50
    #define SHORTTIMING_MAX 79
    #define LONGTIMING_MIN 80
    #define LONGTIMING_MAX 120
    #define SYNCTIMING_MIN 175
    #define SYNCTIMING_MAX 1200
  
    #define ENDTIMING_MIN  0
    #define ENDTIMING_MAX   500


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


   #error Truck Solar timings not defined for 315MHz


#endif

void DecodeTPMS()
{
  int16_t i;
  uint32_t id = 0;
  uint16_t status, pressure1, pressure2, temp, Wheel;
  double realpressure;
  float realtemp;



  for (i = 0; i < 4; i++)
  {
    id = id << 8;
    id = id + RXBytes[i];

  }

  id = id & 0xFFFFFFFF;

  GetPreferredIndexStr(id, Ref);

  Wheel = RXBytes[4];

  status = RXBytes[5] >> 4;

  pressure1 =  ((uint16_t)RXBytes[5] & 0x0f) << 8 | RXBytes[6];

  temp = RXBytes[7];

  pressure2 = pressure1;



  if (pressure1 != pressure2)
  {
    Serial.println(F("Pressure check mis-match"));
    return;
  }

  realpressure = KPA_To_PSI((double)pressure1); 
  realtemp = (float)temp;



#ifdef SHOWVALIDTPMS
  Serial.print(F("Pos: "));
  Serial.print(Ref);
  Serial.print(F("   Wheel: "));
  Serial.print(Wheel);
  Serial.print(F("   ID: "));
  Serial.print(id, HEX);
  Serial.print(F("   Status: 0x"));
  Serial.print(status,HEX);
  Serial.print(F("   Temperature: "));
  Serial.print(realtemp);
  Serial.print(F("   Tyre Pressure: "));
  Serial.print(realpressure);
  Serial.print(F(" (psi)  "));
  Serial.print(realpressure/PSI2BAR);
  Serial.print(F(" (bar)"));
  Serial.println(F(""));
#endif

  //DisplayStatusInfo();

  MatchIDandUpdate(id,status, realtemp, realpressure);

//  //update the array of tyres data
//  for (i = 0; i < TYRECOUNT; i++)
//  { //find a matching ID if it already exists
//    if (id == TPMS[i].TPMS_ID)
//    {
//      UpdateTPMSData(i, id, status, realtemp, realpressure);
//      IDFound = true;
//      break;
//    }
//
//  }
//
//  //no matching IDs in the array, so see if there is an empty slot to add it into, otherwise, ignore it.
//  if (IDFound == false)
//  {
//
//    prefindex = GetPreferredIndex(id);
//    if (prefindex == -1)
//    { //not found a specified index, so use the next available one..
//      #ifndef SPECIFIC_IDS_ONLY 
//        for (i = 0; i < TYRECOUNT; i++)
//        {
//          if (TPMS[i].TPMS_ID == 0)
//          {
//            UpdateTPMSData(i, id, status, realtemp, realpressure);
//            break;
//          }
//        }
//      #endif
//    }
//    else
//    { //found a match in the known ID list...
//      UpdateTPMSData(prefindex, id, status, realtemp, realpressure);
//    }
//
//  }


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
            Serial.println(F("Exited ConvertTimingsToBits with bitcount > MAXBITS-1"));
         #endif
         return;
      }
   }
  
}


bool ValidateTimings()
{


  int16_t ManchesterStartPos = -1;
  uint8_t ByteCount = 0;
  uint8_t crcResult;

  StartDataIndex = 0;

  if (TimingsIndex < (SYNCBITS + (EXPECTEDBITCOUNT * 2)) ) //header + valid data (minimum) doubled for Mnachester coding
  { //not enough in the buffer to consider a valid message
    #ifdef SHOWDEBUGINFO
       Serial.println(F("Insufficient data in buffer"));
    #endif
    return (false);
  }


  //Serial.print("Timings index = ");
  //Serial.println(TimingsIndex);

  ConvertTimingsToBits();

  InvertBitBuffer();


   
  const uint8_t pattern[] = {0xAA, 0xAA, 0xA9};
  ManchesterStartPos = FindManchesterStart(pattern,24);
  StartDataIndex = ManchesterStartPos;


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

  ByteCount = ManchesterDecode(ManchesterStartPos + 8);
  if (ByteCount >= EXPECTEDBYTECOUNT)
  {
      
      //check the checksum...
      crcResult = Compute_CRC_XOR(0,8,  0x00);
      if (crcResult != RXBytes[8])
      {
         #ifdef SHOWDEBUGINFO
          Serial.print(F("CRC calc: "));
          Serial.print(crcResult, HEX);
          Serial.print(F("  CRC rcvd: "));
          Serial.println(RXBytes[7], HEX);
          Serial.println(F("CRC Check failed"));
        #endif
        #ifdef IGNORECHECKSUMERRORS
          DecodeTPMS();
          TPMS_Changed = false;  //don't update display for csum error
        #endif
        return(false);
      }
      else
      {
         #ifdef SHOWDEBUGINFO
           Serial.println(F("CRC Check OK"));
         #endif
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
