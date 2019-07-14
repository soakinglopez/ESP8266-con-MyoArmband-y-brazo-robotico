#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <MyoController.h>

#define FIREBASE_HOST "mxhacksv-8944c.firebaseio.com"
#define FIREBASE_AUTH "kVJUsoSwofmeteJyZLWIRv0waxaIiRyGmBtSLV1l"


const char* ssid = "mxhacks_esquina3";
const char* passwd = "5805hack";

#define FIST_PIN 4
#define WAVEIN_PIN 5
#define WAVEOUT_PIN 0
#define FINGERSSPREAD_PIN 2
#define DOUBLETAP_PIN 14

MyoController myo = MyoController();

void setup() {
    Serial.begin(115200);
    // Connect to WPA/WPA2 network
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passwd);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        // wait 5 seconds for connection:
        Serial.print("Status = ");
        Serial.println(WiFi.status());
        delay(500);
    }
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.setString("hack", "finger");
    

  pinMode(FIST_PIN, OUTPUT);
  pinMode(WAVEIN_PIN, OUTPUT);
  pinMode(WAVEOUT_PIN, OUTPUT);
  pinMode(FINGERSSPREAD_PIN, OUTPUT);
  pinMode(DOUBLETAP_PIN, OUTPUT);
  
  myo.initMyo();
}

void loop()
{
   //Serial.println("HI");
   myo.updatePose();
   switch ( myo.getCurrentPose() ) {
    case rest:
      digitalWrite(FIST_PIN,LOW); 
      digitalWrite(WAVEIN_PIN,LOW);
      digitalWrite(WAVEOUT_PIN,LOW);
      digitalWrite(FINGERSSPREAD_PIN,LOW);
      digitalWrite(DOUBLETAP_PIN,LOW);
      Firebase.setString("status", "none");
      break;
    case fist:
      digitalWrite(FIST_PIN,HIGH);
      Firebase.setString("status", "fist");
      break;
    case waveIn:
      digitalWrite(WAVEIN_PIN,HIGH);
      Firebase.setString("status", "wavein");
      break;
    case waveOut:
      digitalWrite(WAVEOUT_PIN,HIGH);
      Firebase.setString("status", "waveout");
      break;
    case fingersSpread:
      digitalWrite(FINGERSSPREAD_PIN,HIGH);
      Firebase.setString("status", "finger");
      break;
    case doubleTap:
      digitalWrite(DOUBLETAP_PIN,HIGH);
      Firebase.setString("status", "none");
      break;
   } 
   // delay(100);
}
