// ********************************PUBCLIENT LIBRARY *******************************

#include <PubSubClient.h>
const char* mqtt_server = "mqtt3.thingspeak.com";
const char* publishTopic = "channels/2429905/publish";
const char* subscribeTopic = "channels/2429905/subscribe/fields/field1";

const char*  MQTT_USERNAME = "IRoMChAxMA8DHyUyOAQHAiY";
const char*  MQTT_CLIENT_ID = "IRoMChAxMA8DHyUyOAQHAiY";
const char*  MQTT_PASSWORD = "PxDNpIuVG79PX8ifXZ1cb0p6";

#include <WiFi.h>
#include <WiFiClient.h>
WiFiClient  wifiClient;
const char* ssid       =   "TECNO POP 5 Pro"  ; // "Israel's Galaxy S20 FE 5G";
const char* password   =  "clinton10"  ;   //"64646464.1";


PubSubClient  mqttWifi(wifiClient);

const unsigned long postingInterval = 20L * 1000L; // Post data every 20 seconds.
unsigned long lastUploadedTime = 0;


#include <ESP32Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN_USER  12
#define ECHO_PIN_USER     27
#define TRIGGER_PIN_LEVEL 23
#define ECHO_PIN_LEVEL    22

#define MAX_DISTANCE_USER  32
#define MAX_DISTANCE_LEVEL 23
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN_LEVEL, ECHO_PIN_LEVEL, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

Servo myservo;
int level_percent;
int height = 17;

#include <TinyGPS++.h>//this help to get the cordinate location
TinyGPSPlus gps;
#include <HardwareSerial.h>
HardwareSerial gpss(1);
float la,lo; 
char lat[12];
char lon[12];
float latitude = 0.0;
float longitude = 0.0;
void displayInfo();
void GPS();

void publishMessage(const char* topic, String payload , boolean retained);
void callback(char* topic, byte* payload, unsigned int length);
void WifiReconnect();
void pushMessage();
//int level_percentage();

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
//  gpss.begin(9600,SERIAL_8N1,5,18); //5 is Rx 18 is Tx
  pinMode(TRIGGER_PIN_USER, OUTPUT);
  pinMode(ECHO_PIN_USER, INPUT);
  pinMode(TRIGGER_PIN_LEVEL, OUTPUT);
  pinMode(ECHO_PIN_LEVEL, INPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println(ssid);
  myservo.setPeriodHertz(50);
  myservo.attach(25, 500, 2400);
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected\nIP address: ");
    Serial.println(WiFi.localIP());
  }
Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  
  mqttWifi.setServer(mqtt_server, 1883);
  mqttWifi.setCallback(callback);
}

void loop() {
  // User detection
  long duration_user, distance_user;
  digitalWrite(TRIGGER_PIN_USER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_USER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_USER, LOW);
  duration_user = pulseIn(ECHO_PIN_USER, HIGH);
  distance_user = duration_user * 0.034 / 2;

  if (distance_user <= MAX_DISTANCE_USER) {
    myservo.write(0); // Rotate servo to 0 degrees
    delay(3500);
    myservo.write(180); // Rotate servo to 180 degrees
    Serial.print("Open for User at Distance: ");
    Serial.print(distance_user);
    Serial.println(" cm");

    delay(1000); // Adjust delay according to your needs
  }

  // Level detection
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

float dist = sonar.ping_cm();
level_percent = ((height - (dist - 6))) * 100 / (height);
      if (level_percent > 100) {
     level_percent = 100;
      } 
      else if (level_percent < 0) {
        level_percent = 0;
      } 

  /*if (level_percentage >= 95) {
    myservo.detach(); // Turn off servo motor
    }
  */

  // Display percentage in the Serial monitor
  Serial.print("Ping: ");
  Serial.print(dist); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  Serial.print("Percentage: ");
  Serial.print(level_percent);
  Serial.println("%");
   GPS();   
  if(WiFi.status() == WL_CONNECTED) {
if (!mqttWifi.connected())
{
   WifiReconnect();  
}
pushMessage();
  mqttWifi.loop();
  }   
  delay(1000);
}


//int level_percentage(){
//   int level = ((height - (sonar.ping_cm() - 6))) * 100 / (height);
//      if (level > 100) {
//        level = 100;
//      } 
//      else if (level < 0) {
//        level = 0;
//      } 
//  return level;
//}


void pushMessage(){
if (millis() - lastUploadedTime > postingInterval){
  
   String output = String("field1=" + String(level_percent)+ "&field2=" + String(latitude)+ "&field3=" + String(longitude)+"&status=MQTTPUBLISH");  
    publishMessage(publishTopic,output,true);    
   lastUploadedTime = millis();
}
    
}




void WifiReconnect() {
  // Loop until we're reconnected
   if(!mqttWifi.connected()) {
    Serial.print("Attempting MQTT connection...");
      //client.connect("cliend ID", "username","password") Replace with your Thingspeak MQTT Device Credentials
    if (mqttWifi.connect(MQTT_USERNAME,MQTT_CLIENT_ID,MQTT_PASSWORD)) {  
      Serial.println("connected");
      mqttWifi.subscribe(subscribeTopic);   // subscribe the topics here
      //client.subscribe(command2_topic);   
//     gprs();
 
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttWifi.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(100);
    }
  }
}


void callback(char* topic, byte* payload, unsigned int length) {
  
  String incommingMessage = "";
  for (int i = 0; i < length; i++) {
    incommingMessage+=(char)payload[i];
    }
 
Serial.println("Message arrived ["+String(topic)+"]"+ incommingMessage);


}





void publishMessage(const char* topic, String payload , boolean retained){
  if (mqttWifi.publish(topic, payload.c_str())){
      Serial.println("Message published ["+String(topic)+"]: "+payload);

}


else{
  Serial.println("error in sending message");
}
}

void GPS(){ 
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
   displayInfo();
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected:A check wiring."));
    //while(true);
  }
  
  }

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    
    Serial.println(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.println(gps.location.lng(), 6); 
  }
  else
  {
    Serial.println(F("INVALID"));
    //delay(100);
  }

   
}
