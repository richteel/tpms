
#ifdef ISARDUINO_ESP32
  extern TickTwo SignalRefreshTimer;
  extern TickTwo displayflashtimer;
#else
  extern Ticker SignalRefreshTimer;
  extern Ticker displayflashtimer;
#endif


#define CD_END_DELAY_TIME  2500

void LED_On()
{
   digitalWrite(LED_RX, LED_ON);
}

void LED_Off()
{
   digitalWrite(LED_RX, LED_OFF);
}

void PrintIDs()
{
  uint8_t i;
  Serial.print(F("Preset IDs:  "));
  for(i=0;i<TYRECOUNT;i++)
  {
    Serial.print(F(" 0x"));
    Serial.print(IDLookup[i],HEX);
    if (i == 4)
    {
      Serial.println(F(""));
      Serial.print(F("             "));
    }
    else
    {
       if (i < TYRECOUNT-1)
          Serial.print(F(","));      
    }

  }
  Serial.println(F(""));
}

double PSI_To_BAR(double Pressure_PSI)
{
   return(Pressure_PSI/PSI2BAR);
}

double PSI_To_KPA(double Pressure_PSI)
{
   return(Pressure_PSI * KPA2PSI);
}

double BAR_To_PSI(double Pressure_BAR)
{
   return(Pressure_BAR * PSI2BAR);
}

double KPA_To_PSI(double Pressure_KPA)
{
   return(Pressure_KPA/KPA2PSI);
}

float DegC_To_DegK(float DegC)
{
   return(DegC + 273.15);
}

float DegF_To_DegK(float DegF)
{
   return(DegC_To_DegK(DegF_To_DegC(DegF)));
}

float DegC_To_DegF(float DegC)
{
  return((DegC * 1.8) + 32.0);
}

float DegF_To_DegC(float DegF)
{
   return((DegF-32.0)/1.8);
}


double ConvertPressureForDisplay(double Pressure_PSI)
{
   #ifdef DISPLAY_PRESSURE_AS_BAR
      return(PSI_To_BAR(Pressure_PSI));
   #elif DISPLAY_PRESSURE_AS_KPA
      return(PSI_To_KPA(Pressure_PSI));
   #else
      return(Pressure_PSI);
   #endif
}


void ResetSignalRefreshTimer()
{
   SignalRefreshTimer.start();
}


#ifdef ISARDUINO_ESP32

  void IRAM_ATTR DebugPinHigh()
  {
    digitalWrite(DEBUGPIN, HIGH);
  }
  
  void IRAM_ATTR DebugPinLow()
  {
    digitalWrite(DEBUGPIN, LOW);
  }

  void IRAM_ATTR ResetTimings()
  {
    TimingsIndex = 0;
    BaseBitCount = 0;
    IntBitIndex = 0;
    //invalid timing so this becomes the new start edge
    if (digitalRead(RXPin) == LOW)
    {
      FirstEdgeIsHighToLow = true;
    }
    else
    {
      FirstEdgeIsHighToLow = false;
    }
    WaitingFirstEdge = false;
  }
  
  void IRAM_ATTR EdgeInterrupt()
  {
    //portENTER_CRITICAL(&synch);
    uint32_t ts = micros();  //capture entry time
    uint32_t BitWidth;
    int16_t Validation;
    bool BitState;
    

    //DebugPinHigh();
  
    if (TimingsIndex >= MAXTIMINGS)
    {
      ResetTimings();
      LastEdgeTime_us = ts;
      //DebugPinLow();
      return;
    }
    
    if (WaitingFirstEdge)
    {//first edge so start timing from now   
      ResetTimings();
      LastEdgeTime_us = ts;
      //DebugPinLow();
      return;
    }

    BitState = digitalRead(RXPin);

    BitWidth = ts - LastEdgeTime_us;
    
    Validation = ValidateBit2(BitWidth);
    if (Validation == BITISUNDEFINED)
    {
      //check if this is after the expected end of sequence...
      if (BaseBitCount >= EXPECTEDBASEBITCOUNT)
      {//no further interrupts until buffer is processed...
        detachInterrupt(digitalPinToInterrupt(RXPin)); 
        PulseDebugPin(5);
        TimingsAreValid = true;
        //DebugPinLow();
        return;
      }
      else
      {//reset buffer...
        TimingsIndex = 0;
        BaseBitCount = 0;
        IntBitIndex = 0;
        //invalid timing so this becomes the new start edge
        LastEdgeTime_us = ts;
        if (digitalRead(RXPin) == LOW)
        {
          FirstEdgeIsHighToLow = true;
        }
        else
        {
          FirstEdgeIsHighToLow = false;
        }
        WaitingFirstEdge = false;
        //DebugPinLow();
        return;
      }

    } 

    //valid short or long timing...

    IntIncomingBits[IntBitIndex++] = BitState;  
    BaseBitCount = BaseBitCount + 1;  //increment base bit count (e.g. 1 for 50us pulse)
    if (Validation == BITISLONG)
    {
       BaseBitCount = BaseBitCount + 1; //increment base bit count again (e.g. 2 for 100us pulse)
       IntIncomingBits[IntBitIndex++] = BitState;  
    }
  
    LastEdgeTime_us = ts;
    Timings[TimingsIndex] = (uint16_t)BitWidth;
    TimingsIndex = TimingsIndex + 1;

    //portEXIT_CRITICAL(&synch);
    //delayMicroseconds(5);
    //DebugPinLow();
    return;

  }

  bool IRAM_ATTR IsTooShort(uint16_t Width)
  {
    if (Width < SHORTTIMING_MIN)
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }
  
  bool IRAM_ATTR IsValidShort2(uint16_t Width)
  {
    if ((Width >= SHORTTIMING_MIN) && (Width <= SHORTTIMING_MAX))
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }

  bool  IRAM_ATTR IsValidLong2(uint16_t Width)
  {
    if ((Width >= LONGTIMING_MIN) && (Width <= LONGTIMING_MAX))
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }
  
  int16_t IRAM_ATTR  ValidateBit2(uint32_t BitWidth)
  {
  
    if (IsValidLong2(BitWidth))
    {
      return (BITISLONG);
    }
  
    if (IsValidShort2(BitWidth))
    {
      return (BITISSHORT);
    }
  
    return (BITISUNDEFINED);
  
  }

    bool IsValidShort(uint16_t Width)
  {
    if ((Width >= SHORTTIMING_MIN) && (Width <= SHORTTIMING_MAX))
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }

  bool IsValidLong(uint16_t Width)
  {
    if ((Width >= LONGTIMING_MIN) && (Width <= LONGTIMING_MAX))
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }
#else

  void DebugPinHigh()
  {
    digitalWrite(DEBUGPIN, HIGH);
  }
  
  void DebugPinLow()
  {
    digitalWrite(DEBUGPIN, LOW);
  }

  void  ResetTimings()
  {
    TimingsIndex = 0;
    BaseBitCount = 0;
    IntBitIndex = 0;
    //invalid timing so this becomes the new start edge
    if (digitalRead(RXPin) == LOW)
    {
      FirstEdgeIsHighToLow = true;
    }
    else
    {
      FirstEdgeIsHighToLow = false;
    }
    WaitingFirstEdge = false;
  }
  
  void EdgeInterrupt()
  {
     uint32_t ts = micros();  //capture entry time
    uint32_t BitWidth;
    int16_t Validation;
    bool BitState;
    

    //DebugPinHigh();
  
    if (TimingsIndex >= MAXTIMINGS)
    {
      ResetTimings();
      LastEdgeTime_us = ts;
      //DebugPinLow();
      return;
    }
    
    if (WaitingFirstEdge)
    {//first edge so start timing from now   
      ResetTimings();
      LastEdgeTime_us = ts;
      //DebugPinLow();
      return;
    }

    BitState = digitalRead(RXPin);

    BitWidth = ts - LastEdgeTime_us;
    
    Validation = ValidateBit2(BitWidth);
    if (Validation == BITISUNDEFINED)
    {
      //check if this is after the expected end of sequence...
      if (BaseBitCount >= EXPECTEDBASEBITCOUNT)
      {//no further interrupts until buffer is processed...
        detachInterrupt(digitalPinToInterrupt(RXPin)); 
        PulseDebugPin(5);
        TimingsAreValid = true;
        //DebugPinLow();
        return;
      }
      else
      {//reset buffer...
        TimingsIndex = 0;
        BaseBitCount = 0;
        IntBitIndex = 0;
        //invalid timing so this becomes the new start edge
        LastEdgeTime_us = ts;
        if (digitalRead(RXPin) == LOW)
        {
          FirstEdgeIsHighToLow = true;
        }
        else
        {
          FirstEdgeIsHighToLow = false;
        }
        WaitingFirstEdge = false;
        //DebugPinLow();
        return;
      }

    } 

    //valid short or long timing...

    IntIncomingBits[IntBitIndex++] = BitState;  
    BaseBitCount++;  //increment base bit count (e.g. 1 for 50us pulse)
    if (Validation == BITISLONG)
    {
       BaseBitCount++; //increment base bit count again (e.g. 2 for 100us pulse)
       IntIncomingBits[IntBitIndex++] = BitState;  
    }
  
    LastEdgeTime_us = ts;
    Timings[TimingsIndex++] = (uint16_t)BitWidth;

    //portEXIT_CRITICAL(&synch);
    //delayMicroseconds(5);
    //DebugPinLow();
    return;

  }

  bool  IsTooShort(uint16_t Width)
  {
    if (Width < SHORTTIMING_MIN)
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }
  
  bool  IsValidShort2(uint16_t Width)
  {
    if ((Width >= SHORTTIMING_MIN) && (Width <= SHORTTIMING_MAX))
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }

  bool   IsValidLong2(uint16_t Width)
  {
    if ((Width >= LONGTIMING_MIN) && (Width <= LONGTIMING_MAX))
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }
  
  int16_t  ATTRIBUTE   ValidateBit2(uint32_t BitWidth)
  {
  
    if (IsValidLong2(BitWidth))
    {
      return (BITISLONG);
    }
  
    if (IsValidShort2(BitWidth))
    {
      return (BITISSHORT);
    }
  
    return (BITISUNDEFINED);
  
  }

    bool IsValidShort(uint16_t Width)
  {
    if ((Width >= SHORTTIMING_MIN) && (Width <= SHORTTIMING_MAX))
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }

  bool IsValidLong(uint16_t Width)
  {
    if ((Width >= LONGTIMING_MIN) && (Width <= LONGTIMING_MAX))
    {
      return (true);
    }
    else
    {
      return (false);
    }
  }
#endif



bool IsTooLong(uint16_t Width)
{
  if (Width > LONGTIMING_MAX)
  {
    return (true);
  }
  else
  {
    return (false);
  }
}




bool IsValidSync(uint16_t Width)
{
  if ((Width >= SYNCTIMING_MIN) && (Width <= SYNCTIMING_MAX))
  {
    return (true);
  }
  else
  {
    return (false);
  }
}





bool IsEndMarker(uint16_t Width)
{
  uint16_t UpperLimit,LowerLimit;
  UpperLimit = ENDTIMING_MAX;
  LowerLimit = ENDTIMING_MIN;
  if ((Width >= LowerLimit) && (Width <= UpperLimit))
  {
     return(true);
  }
  else
  {
    return(false);
  }
}


int16_t ValidateBit()
{
  uint16_t BitWidth = Timings[CheckIndex];

  if (IsValidLong(BitWidth))
  {
    return (BITISLONG);
  }

  if (IsValidShort(BitWidth))
  {
    return (BITISSHORT);
  }

  if (IsValidSync(BitWidth))
  {
    return (BITISSYNC);
  }


  return (-1);

}

int16_t ValidateBit(int16_t Index)
{
  uint16_t BitWidth = Timings[Index];

  if (IsValidLong(BitWidth))
  {
    return (BITISLONG);
  }

  if (IsValidShort(BitWidth))
  {
    return (BITISSHORT);
  }

  if (IsValidSync(BitWidth))
  {
    return (BITISSYNC);
  }


  return (BITISUNDEFINED);

}


uint16_t Compute_CRC16( int16_t bcount,  uint16_t Poly,  uint16_t crc_init )
{
   return(Compute_CRC16(0,  bcount, Poly,   crc_init ));
}

 uint16_t Compute_CRC16(int16_t startbyte, int16_t bcount,  uint16_t Poly,   uint16_t crc_init )
{
    uint16_t remainder = crc_init;
    byte Abit;

    int16_t c;
    int16_t index = startbyte;
    for (c = 0; c < bcount; c++,index++) 
    {
        remainder ^= (( uint16_t)RXBytes[index]) << 8;
        for (Abit = 0; Abit < 8; ++Abit) 
        {
            if (remainder & 0x8000) {
                remainder = (remainder << 1) ^ Poly;
            }
            else {
                remainder = (remainder << 1);
            }
        }
    }
    return remainder;
  
}

uint8_t Compute_CRC8( int16_t bcount, uint8_t Poly, uint8_t crc_init )
{
  uint8_t crc = crc_init;
  int16_t c;
  for (c = 0; c < bcount; c++)
  {
    uint8_t b = RXBytes[c];
    /* XOR-in next input byte */
    uint8_t data = (uint8_t)(b ^ crc);
    /* get current CRC value = remainder */
    if (Poly == 0x07)
    {
      crc = (uint8_t)(pgm_read_byte(&CRC8_Poly_07_crctable2[data]));
    }
    else
    {
      if (Poly == 0x13)
      {
        crc = (uint8_t)(pgm_read_byte(&CRC8_Poly_13_crctable2[data]));
      }
      else
      {
        if (Poly == 0x2F)
        {
          crc = (uint8_t)(pgm_read_byte(&CRC8_Poly_2F_crctable2[data]));
        }
      }
    }

  }

  return crc;
}

uint8_t Compute_CRC_XOR(int16_t StartByte, int16_t bcount, uint8_t crc_init)
{
  uint8_t crc = crc_init;
  int16_t index = StartByte;
  int16_t c;

  for (c = 0; c < bcount; c++,index++)
  {
    crc = crc ^ RXBytes[index];
  }
  
  return(crc);
}

uint8_t Compute_CRC_SUM(int16_t StartByte, int16_t bcount, uint8_t crc_init)
{
  uint8_t crc = crc_init;
  int16_t c;
  int16_t index = StartByte;

  for (c = 0; c < bcount; c++,index++)
  {
    crc = crc + RXBytes[index];
  }
  
  return(crc);
}

int16_t GetRSSI_dbm()
{
  uint8_t RSSI_Read;
  uint8_t RSSI_Offset = 74;
  int16_t ret;
  
  RSSI_Read = readStatusReg(CC1101_RSSI);
  if (RSSI_Read >= 128)
  {
    ret = (int)((int)(RSSI_Read - 256) /  2) - RSSI_Offset;
  }
  else
  {
    ret = (RSSI_Read / 2) - RSSI_Offset;
  }
  return(ret);
}

void ClearRXBuffer()
{
  int16_t i;

  for (i = 0; i < (int16_t)sizeof(RXBytes); i++)
  {
    RXBytes[i] = 0;
  }
}

int16_t bitsToRXBytes(bool *bitArray, int bitArraySize, bool InvertBits) 
{
  uint8_t b = 0;
  uint8_t n = 0;
  int16_t i;
   
  ClearRXBuffer();
  for (i = 0; i < bitArraySize; i++) 
  {
    b = b << 1;
    if (InvertBits)
    {
       b = b + (bitArray[i] == true? 0:1);
    }
    else
    {
       b = b + (bitArray[i] == true? 1:0);
    }
    
    n++;
    if (n == 8)
    {
      RXBytes[RXByteCount] = b;
      RXByteCount++;
      if (RXByteCount >= (int16_t) sizeof(RXBytes))
      {
        return(RXByteCount);
      }
      n = 0;
      b = 0;
    }     
    
   }

   if (n != 0)
   {//partial bits?
      b = b << (8 - n);
      RXBytes[RXByteCount] = b;
      RXByteCount++;            
   }      
      
   return(RXByteCount);
}

int16_t BiPhaseSpaceDecode(int16_t StartIndex)
{
   int16_t i, index = 0;
   bool bit1, bit2, prevbit;

   prevbit = 0;
 
   
   for (i = StartIndex; i < BitCount-1;i+=2)
   {
      bit1 = IntIncomingBits[i];
      bit2 = IntIncomingBits[i+1];

      if (bit1 == bit2)
      {
        ManchesterDecodedBits[index++] = 1;
      }
      else
      {
        ManchesterDecodedBits[index++] = 0;
      }

      if (i > 0)
      {
         if (prevbit == bit1)
         {
            //illegal coding, so exit
            break;
         }             
      }
      prevbit = bit2;
   }

   RXByteCount = 0;
   RXByteCount = bitsToRXBytes(ManchesterDecodedBits, index, false);
          
   return RXByteCount;

}


int16_t ManchesterDecode_ZeroBit(int16_t StartIndex)
{
   int16_t i;
   bool bit1, bit2;
   uint8_t b = 0;
   uint8_t n = 0;

   RXByteCount = 0;
   for (i = StartIndex; i< BitCount-1;i+=2)
   {
      bit1 = IntIncomingBits[i];
      bit2 = IntIncomingBits[i+1];

      if (bit1 == bit2)
      {
      //  #ifdef SHOWDEBUGINFO
      //     Serial.print(F("Manchester decode exited at index: "));
      //     Serial.println(i + StartIndex);
      //  #endif
         if (n != 0)
         {//partial bits?
            b = b << (8 - n);
            RXBytes[RXByteCount] = b;
            RXByteCount++;            
         }
      
         return RXByteCount;
      }

    b = b << 1;
    b = b + (bit2 == true? 0:1);
    n++;
    if (n == 8)
    {
      RXBytes[RXByteCount] = b;
      RXByteCount++;
      if (RXByteCount >= (int16_t) sizeof(RXBytes))
      {
        return(RXByteCount);
      }
      n = 0;
      b = 0;
    }     
    
   }

   if (n != 0)
   {//partial bits?
      b = b << (8 - n);
      RXBytes[RXByteCount] = b;
      RXByteCount++;            
   }

   return RXByteCount;

}

int16_t ManchesterDecode(int16_t StartIndex)
{
   int16_t i, index = 0;
   bool bit1, bit2;
   uint8_t b = 0;
   uint8_t n = 0;
   

   RXByteCount = 0;
   ManchesterBitCount = 0;
   for (i = StartIndex; i< BitCount-1;i+=2)
   {
      bit1 = IntIncomingBits[i];
      bit2 = IntIncomingBits[i+1];

      if (bit1 == bit2)
      {
      //  #ifdef SHOWDEBUGINFO
      //     Serial.print(F("Manchester decode exited at index: "));
      //     Serial.println(i + StartIndex);
      //  #endif
         if (n != 0)
         {//partial bits?
            b = b << (8 - n);
            RXBytes[RXByteCount] = b;
            RXByteCount++;            
         }
         
      
         return RXByteCount;
      }

    b = b << 1;
    b = b + (bit2 == true? 1:0);
    ManchesterDecodedBits[index++] = (bit2 == true? 1:0);
    n++;
    if (n == 8)
    {
      RXBytes[RXByteCount] = b;
      RXByteCount++;
      if (RXByteCount >= (int16_t)sizeof(RXBytes))
      {
        ManchesterBitCount = index;
        return(RXByteCount);
      }
      n = 0;
      b = 0;
    }     
    
   }

   ManchesterBitCount = index;

   if (n != 0)
   {//partial bits?
      b = b << (8 - n);
      RXBytes[RXByteCount] = b;
      RXByteCount++;            
   }
         
   
   return RXByteCount;

}

int16_t DifferentialManchesterDecode(int16_t StartIndex)
{
   int16_t i;
   bool bit1 = 0, bit2 = 0, bit3 = 0;
   uint8_t b = 0;
   uint8_t n = 0;

   RXByteCount = 0;
   for (i = StartIndex; i< BitCount-1;i+=2)
   {
      bit1 = IntIncomingBits[i];
      bit2 = IntIncomingBits[i+1];
      bit3 = IntIncomingBits[i+2];

      if (bit1 != bit2)
      {
        if (bit2 != bit3)
        {
          b = b << 1;
          b = b + 0;
          n++;
          if (n == 8)
          {
            RXBytes[RXByteCount] = b;
            RXByteCount++;
            n = 0;
            b = 0;
          }          
        }
        else
        {
          bit2 = bit1;
          i+=1;
          break;
        }
      }
      else
      {
        bit2 = 1 - bit1;
        break;
      }
   }


   for (; i< BitCount-1;i+=2)  
   {
      bit1 = IntIncomingBits[i];

      if (bit1 == bit2)
         return RXByteCount;
      bit2 = IntIncomingBits[i+1];

      b = b << 1;
      b = b + (bit1 == bit2? 1:0);
      n++;
      if (n == 8)
      {
        RXBytes[RXByteCount] = b;
        RXByteCount++;
        n = 0;
        b = 0;
      } 

     
   }
    
   return RXByteCount;

}

void InvertBitBuffer()
{
   int16_t i;

   for (i = 0;i < BitCount;i++)
   {
      IntIncomingBits[i] = !IntIncomingBits[i];
   }
  
}

static inline uint8_t bit_at(const uint8_t *bytes, uint16_t bit)

{
    return (uint8_t)(bytes[bit >> 3] >> (7 - (bit & 7)) & 1);
}

int16_t FindManchesterStart(const uint8_t *pattern,int16_t pattern_bits_len )
{


   int16_t ipos = 0;
   int16_t ppos = 0; // cursor on init pattern

   if (BitCount < pattern_bits_len) 
      return -1;

    while ((ipos < BitCount-3) && (ppos < pattern_bits_len)) 
    {
        if (IntIncomingBits[ipos] == bit_at(pattern, ppos)) 
        {
            ppos++;
            ipos++;
            if (ppos == pattern_bits_len)
                return ipos;
        }
        else 
        {
            ipos -= ppos;
            ipos++;
            ppos = 0;
        }
    }

    // Not found
    return -1;
 
}

void InitDataBuffer()
{
  BitIndex = 0;
  BitCount = 0;
  ValidBlock = false;
  //WaitingTrailingZeroEdge = false;
  WaitingFirstEdge  = true;
  CheckIndex = 0;
  TimingsIndex = 0;
  BaseBitCount = 0;
  SyncFound = false;
  //digitalWrite(DEBUGPIN, LOW);

}


void ClearTPMSData(int16_t i)
{
  if (i > TYRECOUNT)
    return;

  TPMS[i].TPMS_ID = 0;
  TPMS[i].lastupdated = 0;
  #ifdef DISPLAY_PRESSURE_AS_BAR
     TPMS[i].TPMS_LowPressureLimit = BAR_To_PSI(PressureLowLimits[i]);
     TPMS[i].TPMS_HighPressureLimit = BAR_To_PSI(PressureHighLimits[i]);
  #elif DISPLAY_PRESSURE_AS_KPA
     TPMS[i].TPMS_LowPressureLimit = KPA_To_PSI(PressureLowLimits[i]);
     TPMS[i].TPMS_HighPressureLimit = KPA_To_PSI(PressureHighLimits[i]);
  #else
     TPMS[i].TPMS_LowPressureLimit = PressureLowLimits[i];
     TPMS[i].TPMS_HighPressureLimit = PressureHighLimits[i];
  #endif



  #ifdef DISPLAY_TEMP_AS_FAHRENHEIT
     TPMS[i].TPMS_LowTemperatureLimit = DegF_To_DegC(TemperatureLowLimits[i]);
     TPMS[i].TPMS_HighTemperatureLimit = DegF_To_DegC(TemperatureHighLimits[i]);  
  #else
     TPMS[i].TPMS_LowTemperatureLimit = TemperatureLowLimits[i];
     TPMS[i].TPMS_HighTemperatureLimit = TemperatureHighLimits[i];
  #endif
  
  TPMS[i].LowPressure = false;
  TPMS[i].HighPressure = false;
  TPMS[i].LowTemperature = false;
  TPMS[i].HighTemperature = false;
  TPMS[i].AudibleAlarmActive = false;
  #ifdef USE_LCDDISPLAY
     if (i < 4)
        ClearDisplayBlock(i);
  #endif
}


void PulseDebugPin(int16_t width_us)
{
  digitalWrite(DEBUGPIN, HIGH);
  delayMicroseconds(width_us);
  digitalWrite(DEBUGPIN, LOW);
}

void UpdateFreqOffset()
{
    FreqOffsetAcc = FreqOffsetAcc + readStatusReg(CC1101_FREQEST);
    writeReg(CC1101_FSCTRL0, FreqOffsetAcc);
    
}



int16_t GetPreferredIndex(uint32_t ID)
{
  int16_t i;

  //for (i = 0; i  < (sizeof(IDLookup) / sizeof(IDLookup[0])); i++)
  for (i = 0; i  < TYRECOUNT; i++)
  {
    if (IDLookup[i] == ID)
    {
      return (i);
    }

  }
  return (-1);
}

int16_t GetDisplayIndexFromID(uint32_t ID)
{
  //return the location on the screen where the ID should be displayed (0-3)
  int16_t tmp;
  tmp = GetPreferredIndex(ID) % 5;

  if ((tmp < 0) || (tmp > 3))
  {
     return(-1);
  }
    
  return(tmp);
}

int16_t GetDisplayIndexFromTyreIndex(int16_t i)
{
   //convert tyre index to screen position, so 0->0,, 1->1, 2->2, 3->3, 4->-1(spare not displayed),Winter tyres: 5->0, 6->1, 7->2, 8->3, 9->-1(spare not displayed)
  int16_t tmp;
  tmp = i % 5;
  if ((tmp < 0) || (tmp > 3))
  {
     return(-1);
  }
  return(tmp);
}

void GetPreferredIndexStr(uint32_t ID, char* sptr)
{
  int16_t tmp;
  tmp = GetPreferredIndex(ID);

  switch (tmp % 5)
  {
    case 0:
       strcpy(sptr, "FL");
       break;
    case 1:
       strcpy(sptr, "FR");
       break;
    case 2:
       strcpy(sptr, "RL");
       break; 
    case 3:
       strcpy(sptr, "RR");
       break;
    case 4:
       strcpy(sptr, "SP");
       break;
    default:
       sptr[0] = '\0';
       break;
    
  }
}

void PrintTimings(uint8_t StartPoint, uint16_t Count)
{
  uint16_t i;
  char c[10];
  for (i = 0; i < Count; i++)
  {
    if ((StartPoint == 0) && (i == (uint16_t)StartDataIndex))
         Serial.println();
    sprintf(c, "%3d,",Timings[StartPoint + i]);
    Serial.print(c);
    //Serial.print(Timings[StartPoint + i]);
    //Serial.print(F(","));
  }
  Serial.println(F(""));
  //    for (i = 0;i<Count;i++)
  //    {
  //          Serial.print(BitTimings[StartPoint + i]);
  //          Serial.print(",");
  //    }
  //    Serial.println("");


}

void PrintManchesterData(int16_t StartPos, uint16_t Count, bool ShowHex)
{

  uint16_t i, c;
  uint8_t hexdata = 0;
  for (i = StartPos, c = 1; c <= Count; i++, c++)
  {
    Serial.print(ManchesterDecodedBits[i]);
    if (ShowHex)
    {
      hexdata = (hexdata << 1) + ManchesterDecodedBits[i];
      if (c % 8 == 0)
      {
        Serial.print(F(" ["));
        Serial.print(hexdata, HEX);
        Serial.print(F("] "));
        hexdata = 0;
      }
    }
  }
  Serial.println(F("")); 
}

void PrintData(int16_t StartPos, uint16_t Count, bool ShowHex)
{

  uint16_t i, c;
  uint8_t hexdata = 0;
  char hexbuffer[3];
  for (i = StartPos, c = 1; c <= Count; i++, c++)
  {
    Serial.print(IncomingBits[i]);
    if (ShowHex)
    {
      hexdata = (hexdata << 1) + IncomingBits[i];
      if (c % 8 == 0)
      {
        Serial.print(F(" ["));
        sprintf (hexbuffer, "%02X", hexdata);
        //Serial.print(hexdata, HEX);
        Serial.print(hexbuffer);
        Serial.print(F("] "));
        hexdata = 0;
      }
    }
  }
  Serial.println(F(""));
}

void PrintData(int16_t StartPos, uint16_t Count)
{

   PrintData(StartPos, Count, true);
}

void PrintData(uint16_t Count)
{
   PrintData(0,Count, true);
//  uint16_t i;
//  byte hexdata;
//  for (i = 0; i < Count; i++)
//  {
//    Serial.print(IncomingBits[i]);
//    hexdata = (hexdata << 1) + IncomingBits[i];
//    if ((i + 1) % 8 == 0)
//    {
//      Serial.print(F(" ["));
//      Serial.print(hexdata, HEX);
//      Serial.print(F("] "));
//      hexdata = 0;
//    }
//  }
//  Serial.println(F(""));
}


void PrintData2(uint16_t Count)
{
   
  uint16_t i;
  uint8_t hexdata = 0;
  char hexbuffer[3];
  for (i = 0; i < Count; i++)
  {
    Serial.print(IntIncomingBits[i]);
    hexdata = (hexdata << 1) + IntIncomingBits[i];
    if ((i + 1) % 8 == 0)
    {
      Serial.print(F(" ["));
      sprintf (hexbuffer, "%02X", hexdata);
        //Serial.print(hexdata, HEX);
      Serial.print(hexbuffer);
      Serial.print(F("] "));
      hexdata = 0;
    }
  }
  Serial.println(F(""));
}


void PrintBytes(uint16_t Count)
{
  uint16_t i;

  for (i = 0; i < Count; i++)
  {
    Serial.print(F(" ["));
    Serial.print(RXBytes[i],HEX);
    Serial.print(F("] "));
  }
  Serial.println(F(""));

}
void InitTPMS()
{
  int16_t i;

  for (i = 0; i < TYRECOUNT; i++)
  {
    ClearTPMSData(i);
  }
  #ifdef USE_LCDDISPLAY 
     UpdateDisplay();
     SignalRefreshNeeded = false;
  #endif

}

double GetTempCompensatedPressureLimit(double LimitsPressure, float LimitsTemperature_DegC, float CurrentTemperature_DegC)
{
   return((CurrentTemperature_DegC + DEGC_TO_KELVIN) * (LimitsPressure / (LimitsTemperature_DegC + DEGC_TO_KELVIN)));  // T2 * (P1/T1)
}

bool PressureBelowLowPressureLimit(int16_t TyreIndex)
{
  bool ret = false;

  double RoundedPressure = round(TPMS[TyreIndex].TPMS_Pressure * 10)/10.0;
  float LowLimit = TPMS[TyreIndex].TPMS_LowPressureLimit;
  float Temperature = TPMS[TyreIndex].TPMS_Temperature;
  
  #ifdef ENABLE_PRESSURE_ALARM_TEMPERATURE_COMPENSATION
     if (Temperature != NO_VALID_TEMPERATURE)
     {
       LowLimit = GetTempCompensatedPressureLimit(LowLimit, PressureLimitsTemperature,Temperature);   //adjust the limit based on the current temperatue and the temperature defined for the limits setting T2 * (P1/T1)
       LowLimit = round(LowLimit * 10)/10.0;
     }
  #endif

  if (RoundedPressure < LowLimit)
  {
       ret = true;
  }

  return(ret);
  
}

bool PressureAboveHighPressureLimit(int16_t TyreIndex)
{
  bool ret = false;

  double RoundedPressure = round(TPMS[TyreIndex].TPMS_Pressure * 10)/10.0;
  float HighLimit = TPMS[TyreIndex].TPMS_HighPressureLimit;
  float Temperature = TPMS[TyreIndex].TPMS_Temperature;
  
  #ifdef ENABLE_PRESSURE_ALARM_TEMPERATURE_COMPENSATION
     if (Temperature != NO_VALID_TEMPERATURE)
     {     
       HighLimit = GetTempCompensatedPressureLimit(HighLimit, PressureLimitsTemperature,Temperature);   //adjust the limit based on the current temperatue and the temperature defined for the limits setting T2 * (P1/T1)
       HighLimit = round(HighLimit * 10)/10.0;
     }
  #endif

  if (RoundedPressure > HighLimit)
  {
       ret = true;
  }

  return(ret);
  
}



bool TemperatureBelowLowTemperatureLimit(int16_t TyreIndex)
{
  bool ret = false;

  float LowLimit = TPMS[TyreIndex].TPMS_LowTemperatureLimit;
  float Temperature = round(TPMS[TyreIndex].TPMS_Temperature * 10)/10.0;

  if (Temperature == NO_VALID_TEMPERATURE)
  {
    ret = false;
  }
  else
  {
    if (Temperature < LowLimit)
    {
         ret = true;
    }    
  }
  return(ret);
  
}

bool TemperatureAboveHighTemperatureLimit(int16_t TyreIndex)
{
  bool ret = false;

  float HighLimit = TPMS[TyreIndex].TPMS_HighTemperatureLimit;
  float Temperature = round(TPMS[TyreIndex].TPMS_Temperature * 10)/10.0;
  

  if (Temperature == NO_VALID_TEMPERATURE)
  {
    ret = false;
  }
  else
  {
    if (Temperature > HighLimit)
    {
         ret = true;
    }    
  }
  return(ret);
  
}

bool IsOutOfPressureLimits(int16_t TyreIndex)
{
  if (TPMS[TyreIndex].TPMS_ID == 0)
     return(false);

  if (PressureBelowLowPressureLimit(TyreIndex))
     return(true);
  if (PressureAboveHighPressureLimit(TyreIndex))
     return(true);

  return(false);
}

bool IsOutOfTemperatureLimits(int16_t TyreIndex)
{
  if (TPMS[TyreIndex].TPMS_ID == 0)
     return(false);

  if (TemperatureBelowLowTemperatureLimit(TyreIndex))
     return(true);
  if (TemperatureAboveHighTemperatureLimit(TyreIndex))
     return(true);

  return(false);
}


void UpdateTPMSData(int16_t index, uint32_t ID, uint16_t status, float Temperature, double Pressure)
{

  if (index >= TYRECOUNT)
    return;

  TPMS[index].TPMS_ID = ID;
  TPMS[index].TPMS_Status = status;
  TPMS[index].lastupdated = millis();
  TPMS[index].TPMS_Temperature = Temperature;
  TPMS[index].TPMS_Pressure = Pressure;




  #ifdef ENABLE_PRESSURE_ALARMS
      if (PressureBelowLowPressureLimit(index))
      {
       
        TPMS[index].LowPressure = true;
        #ifdef SHOWDEBUGINFO
           Serial.print(F("  Low Pressure warning."));
           Serial.print(F("  Limit: "));
           Serial.print(ConvertPressureForDisplay(TPMS[index].TPMS_LowPressureLimit));
           #ifdef ENABLE_PRESSURE_ALARM_TEMPERATURE_COMPENSATION
             if (Temperature != NO_VALID_TEMPERATURE)
             {
              Serial.print(F(" ["));
              Serial.print(ConvertPressureForDisplay(GetTempCompensatedPressureLimit(TPMS[index].TPMS_LowPressureLimit,PressureLimitsTemperature,TPMS[index].TPMS_Temperature)));
              Serial.print(F("]"));
             }
           #endif
           Serial.print(F("  Measured: "));
           Serial.println(ConvertPressureForDisplay(TPMS[index].TPMS_Pressure));
        #endif
      }
      else
      {
        TPMS[index].LowPressure = false;
      }
      
      if (PressureAboveHighPressureLimit(index))
      {
        
        TPMS[index].HighPressure = true;
       #ifdef SHOWDEBUGINFO
           Serial.print(F("  High Pressure warning."));
           Serial.print(F("  Limit: "));
           Serial.print(ConvertPressureForDisplay(TPMS[index].TPMS_HighPressureLimit));
           #ifdef ENABLE_PRESSURE_ALARM_TEMPERATURE_COMPENSATION
             if (Temperature != NO_VALID_TEMPERATURE)
             {
              Serial.print(F(" ["));
              Serial.print(ConvertPressureForDisplay(GetTempCompensatedPressureLimit(TPMS[index].TPMS_HighPressureLimit,PressureLimitsTemperature,TPMS[index].TPMS_Temperature)));
              Serial.print(F("]"));
             }
           #endif
           Serial.print(F("  Measured: "));
           Serial.println(ConvertPressureForDisplay(TPMS[index].TPMS_Pressure));
        #endif
      }
      else
      {
        TPMS[index].HighPressure = false;
      }

  #endif

  #ifdef ENABLE_TEMPERATURE_ALARMS
      if (TemperatureBelowLowTemperatureLimit(index))
      {      
        TPMS[index].LowTemperature = true;
        #ifdef SHOWDEBUGINFO
           Serial.print(F("Low Temperature warning."));
           #ifdef DISPLAY_TEMP_AS_FAHRENHEIT
             Serial.print(F("  Limit(degF): "));
             Serial.print(DegC_To_DegF(TPMS[index].TPMS_LowTemperatureLimit));
             Serial.print(F("  Measured(degF): "));
             Serial.println(DegC_To_DegF(TPMS[index].TPMS_Temperature));
           #else
             Serial.print(F("  Limit(degC): "));
             Serial.print(TPMS[index].TPMS_LowTemperatureLimit);
             Serial.print(F("  Measured(degC): "));
             Serial.println(TPMS[index].TPMS_Temperature);
           #endif
        #endif
      }
      else
      {
        TPMS[index].LowTemperature = false;
      }
      
      if (TemperatureAboveHighTemperatureLimit(index))
      {
        
       TPMS[index].HighTemperature = true;
        #ifdef SHOWDEBUGINFO
           Serial.print(F("High Temperature warning."));
           #ifdef DISPLAY_TEMP_AS_FAHRENHEIT
             Serial.print(F("  Limit(degF): "));
             Serial.print(DegC_To_DegF(TPMS[index].TPMS_HighTemperatureLimit));
             Serial.print(F("  Measured(degF): "));
             Serial.println(DegC_To_DegF(TPMS[index].TPMS_Temperature));
           #else
             Serial.print(F("  Limit(degC): "));
             Serial.print(TPMS[index].TPMS_HighTemperatureLimit);
             Serial.print(F("  Measured(degC): "));
             Serial.println(TPMS[index].TPMS_Temperature);
           #endif
        #endif
      }
      else
      {
        TPMS[index].HighTemperature = false;
      }

  #endif
  
  bitSet(TPMSChangeBits,index);
  
  TPMS[index].RSSIdBm = RSSIvalue;
}

void DisplayStatusInfo()
{
  Serial.print (F("FreqOffset: "));
  Serial.print (FreqOffset);
  Serial.print (F("  DemodLinkQuality: "));
  Serial.print (DemodLinkQuality);
  Serial.print (F("  RSSI: "));
  Serial.println (RSSIvalue);
}

bool OutOfLimitsPressureCheck()
{

  int16_t i;

  
  #ifdef ENABLE_PRESSURE_ALARMS
      Pressure_Alarm_Active = false;
      
      for (i = 0; i < TYRECOUNT; i++)
      {
    
         if ((TPMS[i].LowPressure == true) || (TPMS[i].HighPressure == true))
         {
           Pressure_Alarm_Active = true;
           #ifdef ENABLE_AUDIBLE_ALARM
              //initiate alarm (initial trigger)
              if (TPMS[i].AudibleAlarmActive == false)
              {
                 StartAlarm();
                 TPMS[i].AudibleAlarmActive = true;
              }
           #endif
         }
         else
         {
              if ((TPMS[i].LowPressure == false) && (TPMS[i].HighPressure == false) && (TPMS[i].LowTemperature == false) && (TPMS[i].HighTemperature == false)) 
              {
                 TPMS[i].AudibleAlarmActive = false;
              }
         }       
       
      }
      
      #ifdef ENABLE_AUDIBLE_ALARM
            if ((Pressure_Alarm_Active == false) && ( Temperature_Alarm_Active == false))  
            {
               if (Audible_Alarm_Running)
                  StopAlarm();
            }
      #endif
      
      return(Pressure_Alarm_Active);

  #else
     Pressure_Alarm_Active = false;
     return(false);   
  #endif

}

bool OutOfLimitsTemperatureCheck()
{

  int16_t i;


 
 
  #ifdef ENABLE_TEMPERATURE_ALARMS
      Temperature_Alarm_Active = false;

      for (i = 0; i < TYRECOUNT; i++)
      {
         if ((TPMS[i].LowTemperature == true) || (TPMS[i].HighTemperature == true))
         {
           Temperature_Alarm_Active = true;
           #ifdef ENABLE_AUDIBLE_ALARM
              
              //initiate alarm (initial trigger)
              if (TPMS[i].AudibleAlarmActive == false)
              {
                 StartAlarm();
                 TPMS[i].AudibleAlarmActive = true;
              }
           #endif
         }
         else
         {          
            if ((TPMS[i].LowPressure == false) && (TPMS[i].HighPressure == false) && (TPMS[i].LowTemperature == false) && (TPMS[i].HighTemperature == false)) 
            {
               TPMS[i].AudibleAlarmActive = false;                         
            }

         }       
       
      }
      
      #ifdef ENABLE_AUDIBLE_ALARM
        if ((Pressure_Alarm_Active == false) && ( Temperature_Alarm_Active == false))    
        {
           if (Audible_Alarm_Running)  
              StopAlarm();
        }
      #endif
      
      return(Temperature_Alarm_Active);

  #else
     Temperature_Alarm_Active = false;
     return(false);   
  #endif

}

void DisplayTimerExpired()
{
   DisplayFlashExpired = true;

   DisplayFlash = !DisplayFlash; 
   if (DisplayFlash)
   {
      displayflashtimer.interval(BLANK_MS);
   }
   else
   {
      displayflashtimer.interval(NOBLANK_MS);
   }

}

void SignalRefreshRequired()
{
   SignalRefreshNeeded = true;
}

boolean Check_TPMS_Timeouts()
{
   uint8_t i;
   boolean ret = false;
    
  //clear any data not updated in the last 15 minutes
  for (i = 0; i < TYRECOUNT; i++)
  {
    if ((TPMS[i].TPMS_ID != 0) && (millis() - TPMS[i].lastupdated > TPMS_TIMEOUT))
    {
      ClearTPMSData(i);
      OutOfLimitsPressureCheck();
      OutOfLimitsTemperatureCheck();
      ret = true;
    }

  }

  return(ret);
}


void MatchIDandUpdate(uint32_t id ,uint16_t status, float realtemp,float realpressure)
{

  bool IDFound = false;
  int16_t prefindex;
  int16_t i;
  
  //update the array of tyres data
  for (i = 0; i < TYRECOUNT; i++)
  { //find a matching ID if it already exists
    if (id == TPMS[i].TPMS_ID)
    {
      UpdateTPMSData(i, id, status, realtemp, realpressure);
      #ifdef ISARDUINO_ESP32
         #ifdef MQTT_ENABLED
            UpdateMQTTData(i, id, status, realtemp, realpressure);             
         #endif
      #endif
      #ifdef ENABLE_QUADLED
         UpdateQuadLED(); 
      #endif
      IDFound = true;
      break;
    }

  }

  //no matching IDs in the array, so see if there is an empty slot to add it into, otherwise, ignore it.
  if (IDFound == false)
  {

    prefindex = GetPreferredIndex(id);
    if (prefindex == -1)
    { //not found a specified index, so use the next available one..
      #ifndef SPECIFIC_IDS_ONLY 
        for (i = 0; i < TYRECOUNT; i++)
        {
          if (TPMS[i].TPMS_ID == 0)
          {
            UpdateTPMSData(i, id, status, realtemp, realpressure);

            break;
          }
        }
      #endif
    }
    else
    { //found a match in the known ID list...
      UpdateTPMSData(prefindex, id, status, realtemp, realpressure);
      #ifdef ISARDUINO_ESP32
         #ifdef WIFI_ENABLED
          #ifdef MQTT_ENABLED
              UpdateMQTTData(i, id, status, realtemp, realpressure);             
          #endif
        #endif
      #endif
      #ifdef ENABLE_QUADLED
         UpdateQuadLED(); 
      #endif
    }

  }
  OutOfLimitsPressureCheck();
  OutOfLimitsTemperatureCheck();
}

int16_t DecodeBitArrayFast(int16_t StartIndex, uint8_t ShiftRightBitCount)
{
  //convert 1s and 0s array to byte array
  int16_t i;
  int16_t n = 0;
  uint8_t b = 0;

  ClearRXBuffer();

  n = ShiftRightBitCount;  //pad with this number of 0s to the left
  RXByteCount = 0;
  
  for (i = StartIndex; i < BaseBitCount; i++)
  {
    b = b << 1;
    b = b + IntIncomingBits[i];
    n++;
    if (n == 8)
    {
      RXBytes[RXByteCount] = b;
      //Serial.print(RXBytes[RXByteCount],HEX);
      //Serial.print(" - ");
      RXByteCount++;
      n = 0;
      b = 0;
    }

  }
  //Serial.println("");
  return (RXByteCount);


}

int16_t DecodeBitArray(int16_t StartIndex, uint8_t ShiftRightBitCount)
{
  //convert 1s and 0s array to byte array
  int16_t i;
  int16_t n = 0;
  uint8_t b = 0;

  ClearRXBuffer();

  n = ShiftRightBitCount;  //pad with this number of 0s to the left
  RXByteCount = 0;
  
  for (i = StartIndex; i < BitCount; i++)
  {
    b = b << 1;
    b = b + IncomingBits[i];
    n++;
    if (n == 8)
    {
      RXBytes[RXByteCount] = b;
      //Serial.print(RXBytes[RXByteCount],HEX);
      //Serial.print(" - ");
      RXByteCount++;
      n = 0;
      b = 0;
    }

  }
  //Serial.println("");
  return (RXByteCount);


}

int16_t DecodeBitArray( uint8_t ShiftRightBitCount)
{
  //convert 1s and 0s array to byte array
  int16_t i;
  int16_t n = 0;
  uint8_t b = 0;

  ClearRXBuffer();

  n = ShiftRightBitCount;  //pad with this number of 0s to the left
  RXByteCount = 0;
  
  for (i = 0; i < BitCount; i++)
  {
    b = b << 1;
    b = b + IncomingBits[i];
    n++;
    if (n == 8)
    {
      RXBytes[RXByteCount] = b;
      //Serial.print(RXBytes[RXByteCount],HEX);
      //Serial.print(" - ");
      RXByteCount++;
      n = 0;
      b = 0;
    }

  }
  //Serial.println("");
  return (RXByteCount);


}

#ifdef ISARDUINO_ESP32
  bool IRAM_ATTR ReceiveMessage()
  {
  
    bool ValidMessage = false;
    bool EarlyExit = false;
        bool SW_CDExtension = false;
  
  
  #ifdef USE_TEST_TIMINGS  
    //test set up....
  
    CD_Width = CDWIDTH_MIN + ((CDWIDTH_MAX - CDWIDTH_MIN)/2);
  
    //copy timings to timings array as if they've come from the interrupt
  
    for (TimingsIndex=0;TimingsIndex<TestTimings_len;TimingsIndex++)
    {
       Timings[TimingsIndex] = TestTimings[TimingsIndex];
    }
  
    FirstEdgeIsHighToLow = !FirstTimingIsLow;
    
  #else
  
    int16_t lRSSI = 0;
    uint32_t t1;
  
    uint32_t CD_Start;
    uint32_t TimeSinceLastEdge;
    uint32_t CD_Timing = 0;
  
    //set up timing of edges using interrupts...
    LastEdgeTime_us = micros();
    //CD_Width = LastEdgeTime_us;
    CD_Start = LastEdgeTime_us;
    TimingsIndex=0;
    PulseDebugPin(10);
    
    attachInterrupt(digitalPinToInterrupt(RXPin), EdgeInterrupt, CHANGE);
    #ifdef ARDUINO_SEEED_XIAO_M0
      NVIC_SetPriority(EIC_IRQn, 2);  //!!!!! this is necessary for the Seeeduino Xiao due external interupts having a higher priority than the micros() timer rollover (by default). 
                                       // This can cause the micros() value to appear to go 'backwards' in time in the external interrupt handler and end up giving an incorrect 65536 bit width result.
    
    #elif ARDUINO_SEEED_XIAO_RP2040
       //NVIC_SetPriority(EIC_IRQn, 2);
    #endif

    RSSIvalue = -1000;
    
    while (GetCarrierStatus() == true)
    {

       
       //get the maximum RSSI value seen during data receive window
       lRSSI = GetRSSI_dbm();
       if (lRSSI > RSSIvalue)
       {
         RSSIvalue = lRSSI;
       }
       
       //rtc_wdt_feed();
  
       noInterrupts();
       t1 = micros();
       TimeSinceLastEdge = t1 - LastEdgeTime_us;
       CD_Timing = t1 - CD_Start;
       interrupts();
       if (SW_CDExtension == false)
       {
          if (CD_Timing > 2000)
          {
            SW_CDExtension = true;
          }
       }
       else
       {
          if (CD_Timing > CDWIDTH_MAX)
          {
            SW_CDExtension = false;
          }
       }

       
       
  
       //if (((t1 - CD_Width) > CDWIDTH_MAX) || ((TimingsIndex > EXPECTEDBITCOUNT) && ((t1 - LastEdgeTime_us) > ENDTIMING_MAX)))
       if (((CD_Timing) > CDWIDTH_MAX) || ((TimingsIndex > EXPECTEDBITCOUNT) && (TimeSinceLastEdge > ENDTIMING_MAX) && (ENDTIMING_MAX > 0) ))
       {
          
          #ifdef SHOWDEBUGINFO
               Serial.print(CD_Timing);
               Serial.print("   ");
               Serial.print(TimeSinceLastEdge);
               Serial.println("   Exiting CS loop");
          #endif
          EarlyExit = true;
          break;
       }
    }
  
  
    //digitalWrite(DEBUGPIN,LOW);
    if (CD_Timing >= CDWIDTH_MIN)
    {
       delayMicroseconds(CD_END_DELAY_TIME);  //there is a delay on the serial data stream so ensure we allow a bit of extra time after CD finishes to ensure all the data is captured
    }
    detachInterrupt(digitalPinToInterrupt(RXPin)); 
    EdgeInterrupt();  //force a final edge change just to be sure
    CD_Width = micros() - CD_Start;
    CD_Width = CD_Width - CD_END_DELAY_TIME;
    setIdleState();  //force carrier sense to end
    PulseDebugPin(50);
  
  
  #endif
    
  
    if (((CD_Width >= CDWIDTH_MIN) && (CD_Width <= CDWIDTH_MAX) && (TimingsIndex > EXPECTEDBITCOUNT )) || ((EarlyExit == true) && (TimingsIndex > EXPECTEDBITCOUNT )))
    {
      //PulseDebugPin(100);
      #ifdef SHOWDEBUGINFO
         Serial.println(F("******************************************************************"));
         Serial.println(F("Checking...."));
      #endif
      //digitalWrite(LED_RX,LED_ON);
      CheckIndex = 0;
      ValidMessage = ValidateTimings();
      
      #ifdef SHOWDEBUGINFO
         Serial.println(F("Timings...."));
         Serial.print(F("CD_Width="));
         Serial.println(CD_Width);
         Serial.print(F("TimingsIndex="));
         Serial.println(TimingsIndex);
         Serial.print(F("Checking complete. Bitcount: "));
         Serial.print(BitCount);
         Serial.print(F("  StartDataIndex: "));
         Serial.println(StartDataIndex);
         Serial.print(F(" RSSI(dBm):"));
         Serial.println(RSSIvalue);
         #ifdef ALWAYSSHOWTIMINGS
            PrintTimings(0,TimingsIndex+1);
            PrintData(BitCount);
  //          if (StartDataIndex > 0)
  //          {
  //            Serial.println("StartDataIndex Offset:");
  //            PrintData(StartDataIndex,BitCount);
  //          }
            PrintBytes(EXPECTEDBYTECOUNT);
         #else
         if (ValidMessage)
         {
            PrintTimings(0,TimingsIndex+1);
            PrintData(BitCount);
  //          if (StartDataIndex > 0)
  //          {
  //            Serial.println("StartDataIndex Offset:");
  //            PrintData(StartDataIndex,BitCount);
  //          }
            PrintBytes(EXPECTEDBYTECOUNT);
         }       
         #endif
  
      #endif
  
      //digitalWrite(LED_RX,LED_OFF);
      Flush_RX_FIFO(true);
      return (ValidMessage);
    }
    else
    {
      #ifdef SHOWDEBUGINFO
         if (TimingsIndex >= 50)
         {
           Serial.println(F("******************************************************************"));
           Serial.print(F("CD_Width*="));
           Serial.println(CD_Width);   
           Serial.print(F("TimingsIndex="));
           Serial.println(TimingsIndex); 
           PrintTimings(0,TimingsIndex+1);  
           PrintData(BitCount);
         }
  
  
      #endif
      Flush_RX_FIFO(true);
      return (false);
    }
    return(false);
  }
#else
  bool ReceiveMessage()
  {
  
    bool ValidMessage = false;
    bool EarlyExit = false;
    bool SW_CDExtension = false;
  
   
  
  #ifdef USE_TEST_TIMINGS  
    //test set up....
  
    CD_Width = CDWIDTH_MIN + ((CDWIDTH_MAX - CDWIDTH_MIN)/2);
  
    //copy timings to timings array as if they've come from the interrupt
  
    for (TimingsIndex=0;TimingsIndex<TestTimings_len;TimingsIndex++)
    {
       Timings[TimingsIndex] = TestTimings[TimingsIndex];
    }
  
    FirstEdgeIsHighToLow = !FirstTimingIsLow;
    
  #else
  
    int16_t lRSSI = 0;
    uint32_t t1;
  
    uint32_t CD_Start;
    uint32_t TimeSinceLastEdge;
    uint32_t CD_Timing;
  
    //set up timing of edges using interrupts...
    LastEdgeTime_us = micros();
    //CD_Width = LastEdgeTime_us;
    CD_Start = LastEdgeTime_us;
    digitalWrite(DEBUGPIN,HIGH);
    attachInterrupt(digitalPinToInterrupt(RXPin), EdgeInterrupt, CHANGE);
    #ifdef ARDUINO_SEEED_XIAO_M0
      NVIC_SetPriority(EIC_IRQn, 2);  //!!!!! this is necessary for the Seeeduino Xiao due external interupts having a higher priority than the micros() timer rollover (by default). 
                                       // This can cause the micros() value to appear to go 'backwards' in time in the external interrupt handler and end up giving an incorrect 65536 bit width result.
    
    #elif ARDUINO_SEEED_XIAO_RP2040
       //NVIC_SetPriority(EIC_IRQn, 2);
    #endif
    RSSIvalue = -1000;
   
    
    while ((GetCarrierStatus() == true) || (SW_CDExtension == true))
    {

     
       //get the maximum RSSI value seen during data receive window
       lRSSI = GetRSSI_dbm();
       if (lRSSI > RSSIvalue)
       {
         RSSIvalue = lRSSI;
       }


       noInterrupts();
       t1 = micros();
       TimeSinceLastEdge = t1 - LastEdgeTime_us;
       CD_Timing = t1 - CD_Start;
       interrupts();

       if (SW_CDExtension == false)
       {
          if (CD_Timing > 3000)
          {
            SW_CDExtension = true;
          }
       }
       else
       {
          if (CD_Timing > CDWIDTH_MAX)
          {
            SW_CDExtension = false;
          }
       }
  
       //if (((t1 - CD_Width) > CDWIDTH_MAX) || ((TimingsIndex > EXPECTEDBITCOUNT) && ((t1 - LastEdgeTime_us) > ENDTIMING_MAX)))
       if (((CD_Timing) > CDWIDTH_MAX) || ((TimingsIndex > EXPECTEDBITCOUNT) && (TimeSinceLastEdge > ENDTIMING_MAX) && (ENDTIMING_MAX > 0) ))
       {
          
          #ifdef SHOWDEBUGINFO
               Serial.print(CD_Timing);
               Serial.print("   ");
               Serial.print(TimeSinceLastEdge);
               Serial.println("   Exiting CS loop");
          #endif
          EarlyExit = true;
          break;
       }
    }
  
  
    //digitalWrite(DEBUGPIN,LOW);
  
    delayMicroseconds(CD_END_DELAY_TIME);  //there is a delay on the serial data stream so ensure we allow a bit of extra time after CD finishes to ensure all the data is captured
    detachInterrupt(digitalPinToInterrupt(RXPin)); 
    EdgeInterrupt();  //force a final edge change just to be sure
    CD_Width = micros() - CD_Start;
    CD_Width = CD_Width - CD_END_DELAY_TIME;
    setIdleState();  //force carrier sense to end
  
  
  #endif
    
  
    if (((CD_Width >= CDWIDTH_MIN) && (CD_Width <= CDWIDTH_MAX) && (TimingsIndex > EXPECTEDBITCOUNT )) || ((EarlyExit == true) && (TimingsIndex > EXPECTEDBITCOUNT )))
    {
      //PulseDebugPin(100);
      #ifdef SHOWDEBUGINFO
         Serial.println(F("******************************************************************"));
         Serial.println(F("Checking...."));
      #endif
      //digitalWrite(LED_RX,LED_ON);
      CheckIndex = 0;
      ValidMessage = ValidateTimings();
      
      #ifdef SHOWDEBUGINFO
         Serial.println(F("Timings...."));
         Serial.print(F("CD_Width="));
         Serial.println(CD_Width);
         Serial.print(F("TimingsIndex="));
         Serial.println(TimingsIndex);
         Serial.print(F("Checking complete. Bitcount: "));
         Serial.print(BitCount);
         Serial.print(F("  StartDataIndex: "));
         Serial.println(StartDataIndex);
         Serial.print(F(" RSSI(dBm):"));
         Serial.println(RSSIvalue);
         #ifdef ALWAYSSHOWTIMINGS
            PrintTimings(0,TimingsIndex+1);
            PrintData(BitCount);
  //          if (StartDataIndex > 0)
  //          {
  //            Serial.println("StartDataIndex Offset:");
  //            PrintData(StartDataIndex,BitCount);
  //          }
            PrintBytes(EXPECTEDBYTECOUNT);
         #else
         if (ValidMessage)
         {
            PrintTimings(0,TimingsIndex+1);
            PrintData(BitCount);
  //          if (StartDataIndex > 0)
  //          {
  //            Serial.println("StartDataIndex Offset:");
  //            PrintData(StartDataIndex,BitCount);
  //          }
            PrintBytes(EXPECTEDBYTECOUNT);
         }       
         #endif
  
      #endif
  
      //digitalWrite(LED_RX,LED_OFF);
      Flush_RX_FIFO(true);
      return (ValidMessage);
    }
    else
    {
      #ifdef SHOWDEBUGINFO
         if (TimingsIndex >= 50)
         {
           Serial.println(F("******************************************************************"));
           Serial.print(F("CD_Width*="));
           Serial.println(CD_Width);   
           Serial.print(F("TimingsIndex="));
           Serial.println(TimingsIndex); 
           PrintTimings(0,TimingsIndex+1);  
           PrintData(BitCount);
         }
  
  
      #endif
      Flush_RX_FIFO(true);
      return (false);
    }
    return(false);
  }
#endif
