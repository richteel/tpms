

extern void AudibleAlarmOnOff();
extern void AudibleAlarmReminder();

Ticker AudibleAlarmSoundTimer(AudibleAlarmOnOff, 1000, 1, MILLIS);
Ticker AudibleAlarmReminderTimer(AudibleAlarmReminder, AUDIBLE_ALARM_REMINDER_TIME_MS, 1, MILLIS);

boolean IsAlarmActive()
{//check if alarm is active (including reminder timer running)
   status_t ReminderStatus = AudibleAlarmReminderTimer.state();
   
   if (Audible_Alarm_Running)
      return(true);
   if (ReminderStatus == RUNNING)
      return(true);

   return(false);
}

void AudibleAlarm(bool TurnOn)
{
  if (TurnOn)
  {
     digitalWrite(AUDIBLE_ALARM_PIN, Audible_AlarmPin_Active);
     Audible_Alarm_On = true;
  }
  else
  {
     digitalWrite(AUDIBLE_ALARM_PIN, !Audible_AlarmPin_Active);
     Audible_Alarm_On = false;
  }
}

void StopAlarm()
{
  AudibleAlarm(false);
  AudibleAlarmSoundTimer.stop();
  AudibleAlarmReminderTimer.stop();
  Audible_Alarm_Running = false;
  //Serial.println("###Alarm Stopped");
}

void StartAlarm()
{
   AudibleAlarmSoundTimer.stop(); //just in case!
   AudibleAlarm(true);
   AudibleAlarmSoundTimer.interval(AUDIBLE_ALARM_ON_TIME_MS);
   Audible_Alarm_Cycle_Countdown = AUDIBLE_ALARM_ONOFF_COUNT;
   AudibleAlarmSoundTimer.start();
   Audible_Alarm_Running = true;
   //Serial.println("###Alarm Started");
   
}

void AudibleAlarmReminder()
{
   //Serial.println("###Alarm reminder");
   AudibleAlarmReminderTimer.stop();
   if (Pressure_Alarm_Active || Temperature_Alarm_Active)
   {
      StartAlarm();  //start the alarm cycle again
   }
   
}

void AudibleAlarmOnOff()
{//AudibleAlarmSoundTimer callback function
  //Serial.println("###Alarm on/off tone");
  if ((Pressure_Alarm_Active == false) && ( Temperature_Alarm_Active == false)) 
  {//cancel further timers, turn off alarm
     StopAlarm();
  }
  else
  {//if alarm is on, turn it off and set the off time
     if (Audible_Alarm_On) 
     {
        AudibleAlarm(false);  //turn off alarm
        Audible_Alarm_Cycle_Countdown--;
        if (Audible_Alarm_Cycle_Countdown <= 0)
        {//alarm cycle finished - start the reminder timeout
           AudibleAlarmSoundTimer.stop();
           if (AUDIBLE_ALARM_REMINDER_TIME_MS != 0)
           {
              AudibleAlarmReminderTimer.start();    //start the remibnder timeout    
           }      
        }
        else
        {//off timings
            AudibleAlarmSoundTimer.interval(AUDIBLE_ALARM_OFF_TIME_MS);
            AudibleAlarmSoundTimer.start();   //start the off time                       
        }
     }
     else
     {
         AudibleAlarm(true);  //turn on alarm
         AudibleAlarmSoundTimer.interval(AUDIBLE_ALARM_ON_TIME_MS);
         AudibleAlarmSoundTimer.start();   //start the on time
     }
  }   
}
