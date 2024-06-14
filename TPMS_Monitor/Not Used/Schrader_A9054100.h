
#define CD_END_DELAY_TIME  2500
#ifdef UK_433MHz

   

    #define EXPECTEDBITCOUNT 64
    #define EXPECTEDBYTECOUNT 8
    
    #define SYNCBITS 4
    
    #define CDWIDTH_MIN 12000
    #define CDWIDTH_MAX 30000
    
    #define SHORTTIMING_MIN 80
    #define SHORTTIMING_NOM 120
    #define SHORTTIMING_MAX 160
    #define LONGTIMING_MIN 180
    #define LONGTIMING_MAX 260
    #define SYNCTIMING_MIN 260
    #define SYNCTIMING_MAX 160
    
    #define ENDTIMING_MIN  0
    #define ENDTIMING_MAX  500
    

    #define CC1101_DEFVAL_IOCFG2     0x0C        // GDO2 Output Pin Configuration - Serial out (synchronous)
    #define CC1101_DEFVAL_IOCFG1     0x2E        // GDO1 Output Pin Configuration - not used
    #define CC1101_DEFVAL_IOCFG0     0x0E        // GDO0 Output Pin Configuration - Carrier Sense output
    #define CC1101_DEFVAL_FIFOTHR    0x47        // RX FIFO and TX FIFO Thresholds - 64 bytes in FIFO
    #define CC1101_DEFVAL_SYNC1      0xD5        // Synchronization word, high byte  11010101 01001111
    #define CC1101_DEFVAL_SYNC0      0x4F        // Synchronization word, low byte
    #define CC1101_DEFVAL_PKTLEN     0x00        // Packet Length
    #define CC1101_DEFVAL_PKTCTRL1   0x00        // Packet Automation Control
    #define CC1101_DEFVAL_PKTCTRL0   0x12 //0x30        // Packet Automation Control - synchronous data
    #define CC1101_DEFVAL_ADDR       0x00        // Device Address
    #define CC1101_DEFVAL_CHANNR     0x00        // Channel Number
    #define CC1101_DEFVAL_FSCTRL1    0x06        // Frequency Synthesizer Control (was 0x06)
    #define CC1101_DEFVAL_FSCTRL0    0x00        // Frequency Synthesizer Control
    
    // Carrier frequency = 433.919830 MHz
    #define CC1101_DEFVAL_FREQ2  0x10        // Frequency Control Word, High Byte
    #define CC1101_DEFVAL_FREQ1  0xB0        // Frequency Control Word, Middle Byte
    #define CC1101_DEFVAL_FREQ0  0x71        // Frequency Control Word, Low Byte

    #define CC1101_DEFVAL_DEVIATN    0x40      // Modem Deviation Setting (+/-25.390625kHz)

    #define CC1101_DEFVAL_MDMCFG4    0xC8        // Modem Configuration (C8 = data rate 8kHz, bandwidth 116kHz)
    #define CC1101_DEFVAL_MDMCFG3    0x43        // Modem Configuration (now 93 = data rate = 8kHz)
    #define CC1101_DEFVAL_MDMCFG2    0x34       // Modem Configuration (ASK, no sync + no Manchester coding)
    #define CC1101_DEFVAL_MDMCFG1    0x21        // Modem Configuration Channel spacing 100kHz
    #define CC1101_DEFVAL_MDMCFG0    0xF8        // Modem Configuration      
    #define CC1101_DEFVAL_AGCCTRL2   0x64 //0x64       // AGC Control
    #define CC1101_DEFVAL_AGCCTRL1   0x78 //0x78        // AGC Control
    #define CC1101_DEFVAL_AGCCTRL0   0xB3 //0xB3        // AGC Control
    
    #define CC1101_DEFVAL_MCSM2      0x07        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_MCSM1      0x3C        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_MCSM0      0x18        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_FOCCFG     0x14        // Frequency Offset Compensation Configuration
    #define CC1101_DEFVAL_BSCFG      0x6C        // Bit Synchronization Configuration

    
    #define CC1101_DEFVAL_WOREVT1    0x87        // High Byte Event0 Timeout
    #define CC1101_DEFVAL_WOREVT0    0x6B        // Low Byte Event0 Timeout
    #define CC1101_DEFVAL_WORCTRL    0xFB        // Wake On Radio Control
    #define CC1101_DEFVAL_FREND1     0xB6        // Front End RX Configuration
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

    
  #error Schrader_A9054100 timings not defined for 315MHz 

#endif

void DecodeTPMS()
{
  int16_t i;
  uint32_t id = 0;
  uint16_t status, pressure1, temp;
  double realpressure;
  float realtemp;
  char ID[8];

  id = RXBytes[1] & 0x0F;
  for (i = 2; i <= 4; i++)
  {
    id = id << 8;
    id = id + RXBytes[i];

  }

 // id = ((uint32_t)RXBytes[1] & 0x0F) << 24 | (uint32_t)RXBytes[2] << 16 | (uint32_t)RXBytes[3] << 8 | (uint32_t)RXBytes[3];

  GetPreferredIndexStr(id, Ref);

 
  status = (RXBytes[0] & 0x0F);
  status = status << 4;
  status = status + (RXBytes[1] >> 4);

  


  temp = RXBytes[6];
  realtemp = (float)temp;
  realtemp = realtemp - 50;
  //pressure1 = RXBytes[5];
  pressure1 = RXBytes[5];
  realpressure =  (((double)(pressure1) * 0.362) - 0.05);



  if (realpressure < 0)
     realpressure = 0.0;




#ifdef SHOWVALIDTPMS
  Serial.print(F("Pos: "));
  Serial.print(Ref);
  Serial.print(F("   ID: "));
  sprintf(ID,"%07lX", id);
  Serial.print(ID);
  //Serial.print(id, HEX);
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

#endif



   MatchIDandUpdate(id,status, realtemp, realpressure);
   

  #ifdef SHOWVALIDTPMS
     Serial.println(F(""));
  #endif


}



void ConvertTimingsToBits()
{
   int16_t i,x;
   
   //bool CurrentState = FirstEdgeState;
   bool CurrentState = FirstEdgeIsHighToLow?true:false;
   BitCount = 0;
   ValidTimingsStart = 0;

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
          if (IsTooLong(Timings[i] ))
          {
            if (i < 30)
            {//expand any leading long pulses (may be syncs)
              for (x = 1;x<= (int)((((float)Timings[i]/SHORTTIMING_NOM)) + 0.5);x++)
              {
                  IncomingBits[BitCount++] = CurrentState;
              }
            }
            else
            {//assume an end bit, end the conversion
              IncomingBits[BitCount++] = CurrentState;
              return;
            }
           
          }
          else
          {
         
            if (IsTooShort(Timings[i] ))
            {
            
               if (i < TimingsIndex/2)  //enough bits in the buffer to continue trying?
               { //invalid bit timing, reset
                   
                   BitCount = 0;
                   ValidTimingsStart = i+1;
               }
               else
               {// end the conversion
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



bool ValidateBits()
{
  uint8_t crcResult;
  uint8_t ByteCount = 0;
  int16_t ManchesterStartPos = -1;
  int16_t Attempts;
  int16_t Tries;
  int16_t StartPoint;

  //const uint8_t pattern[] = {0xAB, 0x40};
  const uint8_t pattern[] = {0xD5};


  
  ManchesterStartPos = FindManchesterStart(pattern, 8);
  if (ManchesterStartPos >= 0)
  {
    StartDataIndex = ManchesterStartPos - 0;
    StartPoint = StartDataIndex;
    ByteCount = ManchesterDecode_ZeroBit(StartPoint );
    if (ByteCount >= EXPECTEDBYTECOUNT)
    {     
        //PrintBytes(ByteCount);
        RXBytes[0] = RXBytes[0] & 0x0F;  //ignore upper nibble - thisis a sync nibble and not used in the crc

        //check the checksum...
        crcResult = Compute_CRC8(7,0x07,  0x00);  
        //crcResult = Compute_CRC_SUM(0, 8, 0);
        if (crcResult == RXBytes[7]) 
        {
          return(true);
        }
    }
    StartDataIndex = 0;
    StartPoint = 0;  //shift start point
    ClearRXBuffer();
    

    
  }
  else
  {

    #ifdef SHOWDEBUGINFO
        Serial.println(F("Header pattern not found"));
    #endif
  }

  StartPoint = 0;
  Tries = 1;

  Attempts = (BitCount - (EXPECTEDBITCOUNT*2))+1;
  if (Attempts < 0)
     Attempts = 0;


//ManchesterDecode_ZeroBit(StartPoint );
// PrintData(0,StartPoint);
// PrintData(StartPoint,ByteCount * 8 *2);
  
  while (Attempts > 0)
  {
    ByteCount = ManchesterDecode_ZeroBit(StartPoint );
    //Serial.println(ByteCount);

    if (ByteCount >= EXPECTEDBYTECOUNT)
    {     
        //PrintBytes(ByteCount);
        RXBytes[0] = RXBytes[0] & 0x0F;  //ignore upper nibble - thisis a sync nibble and not used in the crc

        //check the checksum...
        crcResult = Compute_CRC8(7,0x07,  0x00);  
        //crcResult = Compute_CRC_SUM(0, 8, 0);
        if (crcResult == RXBytes[7]) 
        {
           StartDataIndex = StartPoint;
           #ifdef SHOWDEBUGINFO
              Serial.print("Tries = ");
              Serial.println(Tries);
           #endif
           return(true);
        }
        else
        {
//           StartDataIndex = StartPoint;
//           return(true);
           StartPoint++;
           Attempts--; 
        }
    }
    else
    {
       StartPoint++;
       Attempts--; 
    }
    Tries++;
    ClearRXBuffer();
  
  }

  return(false);

}

bool ValidateTimings()
{


  bool GoodCSUM = false;

  StartDataIndex = 0;
  ClearRXBuffer();

  if (TimingsIndex < EXPECTEDBITCOUNT ) //header + valid data (minimum)
  { //not enough in the buffer to consider a valid message
    #ifdef SHOWDEBUGINFO
       Serial.println(F("Insufficient data in buffer"));
    #endif
    return (false);
  }

  if (TimingsIndex > 200)  //header + valid data (minimum)
  { //not enough in the buffer to consider a valid message
    #ifdef SHOWDEBUGINFO
       Serial.println(F("Excessive data in buffer"));
    #endif
    return (false);
  }



  ConvertTimingsToBits();

  if (BitCount < (EXPECTEDBITCOUNT*2) ) //2 incoming (Manchester) bits = 1 expected bit
  { //not enough in the buffer to consider a valid message
    #ifdef SHOWDEBUGINFO
       Serial.print(F("Insufficient decoded bit count ="));
       Serial.println(BitCount);
    #endif
    return (false);
  }

  GoodCSUM = ValidateBits();
  

  if (GoodCSUM == false)
  {
     #ifdef SHOWDEBUGINFO
       Serial.println(F("No valid data found"));
       Serial.print(F("Bit count: "));
       Serial.print(BitCount);
       Serial.print(F("  Attempts: "));
       Serial.println((BitCount - (EXPECTEDBITCOUNT*2))+1);
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
