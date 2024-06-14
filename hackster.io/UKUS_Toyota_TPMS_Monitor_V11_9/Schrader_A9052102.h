//As used on Mercedes AMG GT 11/2018-12/2023 (433MHz - 290)
//Uses Manchester coding with 25us bit widths. The ProMicro will struggle with mesuring this so using FIFO on CC1101 instead.
/*Transmission format is: 
Raw header/sync:
0xAA 0xAA 0x59 0x55 0x5A 
followed by 10 bytes of Manchester coded data (160 bits)
IIIIPT???C
The last byte is a checksum poly 2F, init EF

CC1101 set up for: minimum 2 bytes header (0xAA), sync = 0x5955, address = 0x5A (note the address is passed back in the FIFO data so total FIFO bytes = 21 (Address + 20 Manchester encoded Bytes)

Status = 0xAA when triggered for a reading manually
Status = 0x69 when deflating/inflating (automatic)
Status bit[5] = Battery status (1 = OK) - RM info



*/

#define USEFIFO 1

#define CD_END_DELAY_TIME  100

    
#ifdef UK_433MHz



    #ifdef USEFIFO
        #define EXPECTEDBITCOUNT 80  //can't tell how many bits as this is not Manchester encoded
        #define EXPECTEDBYTECOUNT 10
        #define EXPECTEDFIFOBYTECOUNT 21
        
        #define SYNCBITS 16
        
        #define CDWIDTH_MIN 3000
        #define CDWIDTH_MAX 6500 //10500
      
        #define SHORTTIMING_MIN 20
        #define SHORTTIMING_NOM 25
        #define SHORTTIMING_MAX 39
        #define LONGTIMING_MIN 40
        #define LONGTIMING_MAX 60
        #define SYNCTIMING_MIN 88
        #define SYNCTIMING_MAX 600
      
        #define ENDTIMING_MIN  0
        #define ENDTIMING_MAX  0
    
    
        #define CC1101_DEFVAL_IOCFG2     0x0E      // GDO2 Output Pin Configuration - Serial out 
        #define CC1101_DEFVAL_IOCFG1     0x2E        // GDO1 Output Pin Configuration - not used
        #define CC1101_DEFVAL_IOCFG0     0x06        // GDO0 Output Pin Configuration - Carrier Sense output
        #define CC1101_DEFVAL_FIFOTHR    0x07        // RX FIFO and TX FIFO Thresholds - 64 bytes in FIFO
        #define CC1101_DEFVAL_SYNC1      0x59        // Synchronization word, high byte  11010101 01001111
        #define CC1101_DEFVAL_SYNC0      0x55        // Synchronization word, low byte
        #define CC1101_DEFVAL_PKTLEN     0x15        // Packet Length
        #define CC1101_DEFVAL_PKTCTRL1   0x01        // Packet Automation Control
        #define CC1101_DEFVAL_PKTCTRL0   0x00 //0x30        // Packet Automation Control - synchronous data
        #define CC1101_DEFVAL_ADDR       0x5A        // Device Address
        #define CC1101_DEFVAL_CHANNR     0x00        // Channel Number
        #define CC1101_DEFVAL_FSCTRL1    0x0F        // Frequency Synthesizer Control (was 0x06)
        #define CC1101_DEFVAL_FSCTRL0    0x00        // Frequency Synthesizer Control
        
        // Carrier frequency = 433.919830 MHz
        #define CC1101_DEFVAL_FREQ2  0x10        // Frequency Control Word, High Byte
        #define CC1101_DEFVAL_FREQ1  0xB0        // Frequency Control Word, Middle Byte
        #define CC1101_DEFVAL_FREQ0  0x5D        // Frequency Control Word, Low Byte
    
        #define CC1101_DEFVAL_DEVIATN    0x41      // Modem Deviation Setting (+/-25kHz)
    
        #define CC1101_DEFVAL_MDMCFG4    0x9A        // Modem Configuration (59 = data rate = 20kHz , RX bandwidth 162kHz)
        #define CC1101_DEFVAL_MDMCFG3    0x83        // Modem Configuration (now 93 = data rate = 20kHz)
        #define CC1101_DEFVAL_MDMCFG2    0x16        // Modem Configuration (2-FSK, No Sync or Manchester coding) - 16 bit sync
        #define CC1101_DEFVAL_MDMCFG1    0x01        // Modem Configuration Channel spacing 100kHz - 8 bit preamble of AAs
        #define CC1101_DEFVAL_MDMCFG0    0xF8        // Modem Configuration      
        #define CC1101_DEFVAL_AGCCTRL2   0x07       // AGC Control
        #define CC1101_DEFVAL_AGCCTRL1   0x58        // AGC Control
        #define CC1101_DEFVAL_AGCCTRL0   0x82        // AGC Control
        
        #define CC1101_DEFVAL_MCSM2      0x07        // Main Radio Control State Machine Configuration
        #define CC1101_DEFVAL_MCSM1      0x30        // Main Radio Control State Machine Configuration
        #define CC1101_DEFVAL_MCSM0      0x08        // Main Radio Control State Machine Configuration
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
    #else
    
        #define EXPECTEDBITCOUNT 160  
        #define EXPECTEDBYTECOUNT 10
        #define EXPECTEDFIFOBYTECOUNT 20
        
        #define SYNCBITS 16
        
        #define CDWIDTH_MIN 5000
        #define CDWIDTH_MAX 7000
      
        #define SHORTTIMING_MIN 20
        #define SHORTTIMING_NOM 25
        #define SHORTTIMING_MAX 39
        #define LONGTIMING_MIN 40
        #define LONGTIMING_MAX 66
        #define SYNCTIMING_MIN 88
        #define SYNCTIMING_MAX 600
      
        #define ENDTIMING_MIN  0
        #define ENDTIMING_MAX  0

   
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
    #define CC1101_DEFVAL_FREQ0  0x5D        // Frequency Control Word, Low Byte

    #define CC1101_DEFVAL_DEVIATN    0x41      // Modem Deviation Setting (+/-25.390625kHz)

    #define CC1101_DEFVAL_MDMCFG4    0x9A        // Modem Configuration (59 = data rate = 20kHz - actual data rate is 10kHz but due to bi-phase coding need to double the rate, RX bandwidth 325kHz)
    #define CC1101_DEFVAL_MDMCFG3    0x83        // Modem Configuration (now 93 = data rate = 20kHz)
    #define CC1101_DEFVAL_MDMCFG2    0x00        // Modem Configuration (2-FSK, No Sync or Manchester coding)
    #define CC1101_DEFVAL_MDMCFG1    0x01        // Modem Configuration Channel spacing 100kHz
    #define CC1101_DEFVAL_MDMCFG0    0xF8        // Modem Configuration      
    #define CC1101_DEFVAL_AGCCTRL2   0x07       // AGC Control
    #define CC1101_DEFVAL_AGCCTRL1   0x58        // AGC Control
    #define CC1101_DEFVAL_AGCCTRL0   0x82        // AGC Control
    
    #define CC1101_DEFVAL_MCSM2      0x07        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_MCSM1      0x3C        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_MCSM0      0x08        // Main Radio Control State Machine Configuration
    #define CC1101_DEFVAL_FOCCFG     0x16        // Frequency Offset Compensation Configuration
    #define CC1101_DEFVAL_BSCFG      0x6C        // Bit Synchronization Configuration

    
    #define CC1101_DEFVAL_WOREVT1    0x87        // High Byte Event0 Timeout
    #define CC1101_DEFVAL_WOREVT0    0x6B        // Low Byte Event0 Timeout
    #define CC1101_DEFVAL_WORCTRL    0x7B        // Wake On Radio Control
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
    

    #endif
      
 
#elif US_315MHz

    
  #error Schrader_A9052102 timings not defined for 315MHz 

#endif

void DecodeTPMS()
{
  int16_t i;
  uint32_t id = 0;
  uint16_t status, pressure1, temp;
  double realpressure;
  float realtemp;
  char ID[8];
  bool BatteryOK;

  for (i = 0; i <= 3; i++)
  {
    id = id << 8;
    id = id + RXBytes[i];

  }

 // id = ((uint32_t)RXBytes[1] & 0x0F) << 24 | (uint32_t)RXBytes[2] << 16 | (uint32_t)RXBytes[3] << 8 | (uint32_t)RXBytes[3];

  GetPreferredIndexStr(id, Ref);

 
  status = RXBytes[8];
  if (status & 0b00100000)
  {
    BatteryOK = true;
  }
  else
  {
    BatteryOK = false;
  }



  temp = RXBytes[5];
  realtemp = (float)temp;
  realtemp = realtemp - 52;
  //pressure1 = RXBytes[5];
  pressure1 = RXBytes[4];
  realpressure =  (((double)(pressure1) * 2.389) - 2.260);  //in kpa
  realpressure = realpressure /  KPA2PSI;



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
  Serial.print(F("  Battery "));
  if (BatteryOK)
  {
    Serial.print(F("OK"));
  }
  else
  {
    Serial.print(F("LOW"));
  }
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



#ifdef USEFIFO
    bool ValidateTimings()
    {
    
      int16_t j;
      int16_t ManchesterStartPos = -1;
      uint8_t ByteCount = 0;
      uint8_t crcResult;
      uint8_t RX_FIFO[EXPECTEDFIFOBYTECOUNT + 2];
      uint8_t RX_FIFO_Index;
      uint8_t i;
      uint8_t FIFO_Data;
      //uint16_t SyncWord = 0;
      uint8_t AddressByte = 0;
    
      if (Get_RX_FIFO_Count() < EXPECTEDFIFOBYTECOUNT)
      {
         Serial.print(F("FIFO Count less than expected: "));
         Serial.print(Get_RX_FIFO_Count());
         return(false);
      }
    
      StartDataIndex = 0;
    
      RX_FIFO_Index = 0;
      //read FIFO bytes and convert back to bits
      //RX_FIFO[RX_FIFO_Index++] = CC1101_DEFVAL_SYNC1;
      //RX_FIFO[RX_FIFO_Index++] = CC1101_DEFVAL_SYNC0;
//      SyncWord = ReadFIFO();
//      SyncWord = (SyncWord << 8) + ReadFIFO();
//      if (SyncWord != 0x555A)
//      {
//        Serial.print(F("Sync word mismatch. Expected 0x555A, received "));
//        Serial.println(SyncWord,HEX);
//        return(false);
//      }
      AddressByte = ReadFIFO();
      for (i=RX_FIFO_Index; i<EXPECTEDFIFOBYTECOUNT-1;i++)
      {
         RX_FIFO[i] = ReadFIFO();
      }
      #ifdef SHOWDEBUGINFO 
        Serial.println(F("FIFO Data:")); 
        for (i=0; i<EXPECTEDFIFOBYTECOUNT-1;i++)
        {
           Serial.print(RX_FIFO[i], HEX);
           Serial.print(F(" "));
        }
        Serial.println(F("")); 
      #endif
      
      //translate FIFO data to bits
      BitCount = 0;
      for (i=0; i<EXPECTEDFIFOBYTECOUNT-1;i++)
      {
         FIFO_Data = RX_FIFO[i];
         for (j=7;j>=0;j--)
         {
            IncomingBits[BitCount++] = bitRead(FIFO_Data,j);
         }
       }
    
    
      //InvertBitBuffer();
    
      ManchesterStartPos = 0;
      StartDataIndex = 0;
    
      ByteCount = ManchesterDecode_ZeroBit(ManchesterStartPos);
      //PrintBytes(ByteCount);
      if (ByteCount >= EXPECTEDBYTECOUNT)
      {
          
          //check the checksum...
          crcResult = Compute_CRC8(EXPECTEDBYTECOUNT-1,0x2F,  0xE8); 
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
    
#else


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
          if (IsTooLong(Timings[i] ) && (i< 30))
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
  const uint8_t pattern[] = {0x55,0x5A};
  int16_t Attempts;
  
  ManchesterStartPos = FindManchesterStart(pattern, 16);
//  Serial.print(F("Manchester start: "));
//  Serial.println(ManchesterStartPos);
  StartDataIndex = ManchesterStartPos;

//  int Attempts = (BitCount - (EXPECTEDBITCOUNT))+1;
//  if (Attempts < 0)
//     Attempts = 0;
  int16_t StartPoint = 0;  //shift start point

  if (StartDataIndex == -1)
  {//couldn't find header
    Attempts = 0;
    StartPoint = 0;
    #ifdef SHOWDEBUGINFO
        Serial.println(F("Header not found"));
    #endif
    return(false);
  }
  else
  {
    Attempts = 1;
    StartPoint = StartDataIndex;
  }
  
  while (Attempts > 0)
  {
    ByteCount = ManchesterDecode_ZeroBit(StartPoint );
    //Serial.println(ByteCount);
    if (ByteCount >= EXPECTEDBYTECOUNT)
    {     
        //check the checksum...
        crcResult = Compute_CRC8(EXPECTEDBYTECOUNT - 1,0x2F,  0xE8);
        if (crcResult == RXBytes[9]) 
        {
           StartDataIndex = StartPoint;
           return(true);
        }
        else
        {
           StartPoint++;
           Attempts--; 
        }
    }
    else
    {
       StartPoint++;
       Attempts--; 
    }

  
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

  if (BitCount < (EXPECTEDBITCOUNT) ) 
  { //not enough in the buffer to consider a valid message
    #ifdef SHOWDEBUGINFO
       Serial.print(F("Insufficient decoded bit count ="));
       Serial.println(BitCount);
    #endif
    return (false);
  }

  GoodCSUM = ValidateBits();
  


//  if (GoodCSUM == false)
//  {
//     #ifdef SHOWDEBUGINFO
//        Serial.println(F("Inverting.."));
//     #endif
//     InvertBitBuffer();
//     GoodCSUM = ValidateBits();
//     
//  }
  

  if (GoodCSUM == false)
  {
     #ifdef SHOWDEBUGINFO
       Serial.println(F("No valid data found"));
       Serial.print(F("Bit count: "));
       Serial.println(BitCount);
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





#endif
