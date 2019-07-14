#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <MyoController.h>
#include <Servo.h> 

#define FIREBASE_HOST "mxhacksv-8944c.firebaseio.com"
#define FIREBASE_AUTH "kVJUsoSwofmeteJyZLWIRv0waxaIiRyGmBtSLV1l"


const char* ssid = "AndroidAPM";
const char* passwd = "llea34242222";
String state;

#define servosuperior 2
#define servoinferior 0


MyoController myo = MyoController();

Servo myservo;

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
    Firebase.setString("recepcion", "on");
    

  pinMode(servoinferior, OUTPUT);
  pinMode(servosuperior, OUTPUT);

}

void loop(){
  state = Firebase.getString("status");
  Serial.println(state);
  while(state == "fist"){
    digitalWrite(servosuperior,HIGH); 
    delay(13);
    digitalWrite(servosuperior,LOW); 
    delay(10);
    state = Firebase.getString("status");
    Serial.println(state);
  }
  while(state == "finger"){
    digitalWrite(servosuperior,HIGH); 
    delay(13);
    digitalWrite(servosuperior,LOW); 
    delay(10);
    state = Firebase.getString("status");
    Serial.println(state);
    
  }    
  while(state == "waveout"){
    digitalWrite(servoinferior,HIGH); 
    delay(13);
    digitalWrite(servoinferior,LOW); 
    delay(10);
    state = Firebase.getString("status");
    Serial.println(state);


  }
  while(state == "wavein"){
    digitalWrite(servoinferior,HIGH); 
    delay(13);
    digitalWrite(servoinferior,LOW); 
    delay(10);
    state = Firebase.getString("status");
    Serial.println(state);
  }
}
