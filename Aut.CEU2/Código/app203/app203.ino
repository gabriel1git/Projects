#include<ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#define WIFI_SSID "TROJAN"
#define WIFI_PASSWORD "ASUSFURGRICO"
#define URL "https://app203-1f7cc-default-rtdb.firebaseio.com/"
#define secreto "MmR9uho0GyrJbdioM7W9IMehJGb86dLDt6fc373d"

FirebaseData baseData;
  int i = 0;
  int Lamp01 = 0;
  int Lamp02 = 0;

void setup(){

  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("tentativa de conexão");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("conectado a rede");
  Serial.println(WIFI_SSID);

  while(WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    delay(500);
  }

  Firebase.begin(URL, secreto); 
  Firebase.reconnectWiFi(true);
  
  Serial.println("conectado com exito");
}
void loop(){
  while(WiFi.status() == WL_CONNECTED){

    if(Lamp01 == 10){
      digitalWrite(0, LOW);
      Lamp01 = 0;
    }
    else if(Lamp01 == 5){
      digitalWrite(0, HIGH);
      Lamp01 = 0;
    }
    if(Lamp02 == 10){
      digitalWrite(2, LOW);
      Lamp02 = 0;
    }
    else if(Lamp02 == 5){
      digitalWrite(2, HIGH);
      Lamp02 = 0;
    }
    delay(250);
    
    Firebase.get(baseData, "CEU2/Apt 203/Lamp01");
    Lamp01 = baseData.intData();
    Firebase.get(baseData, "CEU2/Apt 203/Lamp02");
    Lamp02 = baseData.intData();
  }
      Lamp01 = 0;
      Lamp02 = 0;
}

  /*while(i<9){
    //Firebase.set(myFirebaseData, "Casa/Lampada", i);
    Firebase.set(baseData, "CEU2/Apt 203/Lamp01", i);
    Firebase.get(baseData, "CEU2/Apt 203/Lamp01");
    recebe = baseData.intData();
    i ++;
    Serial.println(recebe);
    delay(1000);
  }*/
