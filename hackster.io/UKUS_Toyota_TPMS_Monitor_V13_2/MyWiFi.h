


#define mqtt_server "192.168.0.XXX"
#define mqtt_user "xxxxxx"
#define mqtt_password "xxxxxx"

#ifdef TESTING
  #define OTA_NETWORK_NAME "TPMS01_TEST"
  #define WIFI_MANAGER_AP "TPMS01_TEST"
  #define MQTT_NETWORK_NAME "ESPMQTT01TEST"
#else
  #define OTA_NETWORK_NAME "TPMS_01"
  #define WIFI_MANAGER_AP "TPMS01_AP"
  #define MQTT_NETWORK_NAME "ESPMQTT01"
#endif

WiFiManager wm;

const char* mqttTopicTPMS = "home/TPMS/";   // MQTT topic


WiFiClient espClient;
PubSubClient MQTTclient(espClient);

void configModeCallback(WiFiManager *myWiFiManager)
{

   Serial.println("Entered Access Point config mode. Connect to 'TPMS_XX_AP' using phone/iPad and configure WiFi");
}

boolean MQTTreconnect() 
{
  Serial.print("Attempting MQTT reconnection...");
  if (MQTTclient.connect(MQTT_NETWORK_NAME, mqtt_user, mqtt_password)) 
  {
     Serial.println("MQTT reconnected");
  }
  else
  {
    Serial.println("MQTT reconnection failed, retry in 5 secs");
  }
  return (MQTTclient.connected());
}

void MQTT_Setup()
{
  MQTTclient.setServer(mqtt_server, 1883);
  //MQTTclient.setCallback(callback);
  Serial.println("Connecting to MQTT server...");
  if (!MQTTclient.connected()) 
  {
    MQTTreconnect();
  }
}

void setup_wifi()
{
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);

  // make sure the ESP WiFi functions are enabled
  WiFi.mode(WIFI_STA);                  // use only the WiFi 'station' mode

  bool res;
  Serial.println("Connecting to WiFi...");

  //wm.setConfigPortalBlocking(false);
  //wm.setAPCallback(configModeCallback);
  wm.setTimeout(600);
  
  res = wm.autoConnect(WIFI_MANAGER_AP);
  if (res == false)
  {
    Serial.println("Failed to connect and hit the timeout. Restarting...");
    delay(1000);
    ESP.restart();
  }

  while (WiFi.status() != WL_CONNECTED) // wait for connection
  {
    //delay(500);
    Serial.print(".");
    delay(300);
  } 
 
  Serial.println("\nWifi Connected OK");

  // Connected!
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

  MQTT_Setup();
  //MQTTclient.setServer(mqtt_server, 1883);
  //MQTTclient.setCallback(mqttCallback);

}

void OTA_Setup()
{
  ArduinoOTA.setHostname(OTA_NETWORK_NAME);

  
  ArduinoOTA.onStart([]() {

    Serial.println("Starting OTA update");

    detachInterrupt(digitalPinToInterrupt(RXPin));
  });
  
  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA finished");   
  });
  
  
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    unsigned int OTA_Percent;
    OTA_Percent = (progress / (total / 100));
    Serial.printf("Progress: %u%%\r",OTA_Percent );
    if (OTA_Percent >= 100)
    {
       Serial.println("OTA Update complete");
    }
  });
  ArduinoOTA.onError([](ota_error_t error) {

    Serial.printf("Error[%u]: ", error);
    if      (error == OTA_AUTH_ERROR   ) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR  ) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR    ) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  yield();
}






void UpdateMQTTData(int16_t index, uint32_t ID, uint16_t TPMSstatus, float Temperature, double Pressure)
{
   char MQTTPathBase[100];
   char MQTTPath[100];
   char MQTTData[50];
   char strWhichTyre[4];
  
   if (!MQTTclient.connected()) 
   {
      if (MQTTreconnect() == false)
      {
        Serial.println("No MQTT connection. MQTT update will be lost");
        return;
      }
   }
   
   GetPreferredIndexStr(ID,strWhichTyre);  //get FL,FR,RL,RR
   strWhichTyre[2] = '/'; //separator
   strWhichTyre[3] = '\0';   //null terminate

   strcpy(MQTTPathBase, mqttTopicTPMS);   
   strcat(MQTTPathBase, strWhichTyre);        

   //ID
   strcpy(MQTTPath, MQTTPathBase);
   strcat(MQTTPath, "ID");                      //"home/TPMS/XX/ID"
   sprintf(MQTTData,"%08lX",(unsigned long)ID);
   MQTTclient.publish(MQTTPath,MQTTData); 
//   Serial.print(MQTTPath);
//   Serial.print("   ");
//   Serial.println(MQTTData);

   //Pressure - in psi
   strcpy(MQTTPath, MQTTPathBase);
   strcat(MQTTPath, "Pressure_PSI");                      //""home/TPMS/XX/Pressure"
   dtostrf(Pressure, 0, 2, MQTTData);
   MQTTclient.publish(MQTTPath,MQTTData);  
//   Serial.print(MQTTPath);
//   Serial.print("   ");
//   Serial.println(MQTTData);
   
   //Temperature - in degC
   strcpy(MQTTPath, MQTTPathBase);
   strcat(MQTTPath, "Temperature_DegC");                      //""home/TPMS/XX//Temperature"
   dtostrf(Temperature, 0, 1, MQTTData);
   MQTTclient.publish(MQTTPath,MQTTData);
//   Serial.print(MQTTPath);
//   Serial.print("   ");
//   Serial.println(MQTTData);
   
   //Status
   strcpy(MQTTPath, MQTTPathBase);
   strcat(MQTTPath, "Status");                      //"home/TPMS/XX/Status"
   sprintf(MQTTData,"%02X",TPMSstatus);
   MQTTclient.publish(MQTTPath,MQTTData);  
//   Serial.print(MQTTPath);
//   Serial.print("   ");
//   Serial.println(MQTTData);  
}
