#define WIFI_SSID "xxxxxxx"
#define WIFI_PASS "xxxxxxx"

#define mqtt_server "192.168.0.XXX"
#define mqtt_user "xxxxxx"
#define mqtt_password "xxxxxx"

#define MYHOSTNAME "ESP32TPMS"



const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

const char* mqttTopicTPMSToyota = "home/TPMS/Toyota/";   // MQTT topic


WiFiClient espClient;
PubSubClient MQTTclient(espClient);

void reconnect() {
  // Loop until we're reconnected
  while (!MQTTclient.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (MQTTclient.connect("ESP32ClientTPMS", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  wl_status_t WiFiStatus;
  // Set WIFI module to STA mode
  WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", ssid);
        WiFiStatus = WiFi.status();
    if (WiFiStatus != WL_CONNECTED) {
       WiFiStatus = WiFi.begin(ssid, password);
    }

    WiFiStatus = WiFi.status();

    // Wait
    while (WiFiStatus != WL_CONNECTED) {
        Serial.print(WiFiStatus);
        Serial.print(".");
        //WiFi.begin(ssid, password);
        delay(300);
        WiFiStatus = WiFi.status();
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

  
    ArduinoOTA.setHostname(MYHOSTNAME);
    ArduinoOTA.onStart([]() {
      Serial.println("Start");
    });

    ArduinoOTA.onEnd([]() {
      Serial.println("\nEnd");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
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

}


void UpdateMQTTData(int16_t index, uint32_t ID, uint16_t TPMSstatus, float Temperature, double Pressure)
{
   char MQTTPathBase[100];
   char MQTTPath[100];
   char MQTTData[50];
   char strWhichTyre[4];
  
   if (!MQTTclient.connected()) 
   {
      reconnect();
   }
   
   GetPreferredIndexStr(ID,strWhichTyre);  //get FL,FR,RL,RR
   strWhichTyre[2] = '/'; //separator
   strWhichTyre[3] = '\0';   //null terminate

   strcpy(MQTTPathBase, mqttTopicTPMSToyota);   //"home/TPMS/Toyota/"
   strcat(MQTTPathBase, strWhichTyre);          //"home/TPMS/Toyota/XX/"

   //ID
   strcpy(MQTTPath, MQTTPathBase);
   strcat(MQTTPath, "ID");                      //"home/TPMS/Toyota/XX/ID"
   sprintf(MQTTData,"%08X",ID);
   MQTTclient.publish(MQTTPath,MQTTData); 
//   Serial.print(MQTTPath);
//   Serial.print("   ");
//   Serial.println(MQTTData);

   //Pressure - in psi
   strcpy(MQTTPath, MQTTPathBase);
   strcat(MQTTPath, "Pressure_PSI");                      //"home/TPMS/Toyota/XX/Pressure"
   dtostrf(Pressure, 0, 2, MQTTData);
   MQTTclient.publish(MQTTPath,MQTTData);  
//   Serial.print(MQTTPath);
//   Serial.print("   ");
//   Serial.println(MQTTData);
   
   //Temperature - in degC
   strcpy(MQTTPath, MQTTPathBase);
   strcat(MQTTPath, "Temperature_DegC");                      //"home/TPMS/Toyota/XX/Temperature"
   dtostrf(Temperature, 0, 1, MQTTData);
   MQTTclient.publish(MQTTPath,MQTTData);
//   Serial.print(MQTTPath);
//   Serial.print("   ");
//   Serial.println(MQTTData);
   
   //Status
   strcpy(MQTTPath, MQTTPathBase);
   strcat(MQTTPath, "Status");                      //"home/TPMS/Toyota/XX/Status"
   sprintf(MQTTData,"%02X",TPMSstatus);
   MQTTclient.publish(MQTTPath,MQTTData);  
//   Serial.print(MQTTPath);
//   Serial.print("   ");
//   Serial.println(MQTTData);  
}
