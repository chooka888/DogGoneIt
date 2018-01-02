
/*****************************************
 * Simple Dog feeder. MQTT
 * WEMOS D1 R2 
 * 5V - Servo 5V
 * Gnd - Servo Gnd
 * D3 - Servo Signal
 ****************************************/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

//WIFI Constants
const char* ssid = "enter your SSID";            //  SSID of LAN/WLAN
const char* password = "enter your password";        //  password

//MQTT constants
const char* mqttServer = "192.168.0.XXX"; //TODO: replace with server name... 
const int mqttPort = 1883;
const char* mqttClientID = "DogGoneIt";
const char* mqttUser = "enter your MQTT user";            //  UPDATE
const char* mqttPassword = "enter your MQTT password";        //  UPDATE

//MQTT topic to subscribe to
String mqttTopicThis = "dog"; //update this one for the individual unit
const char* mqttTopicThisC = "dog";

//Define and then instantiate the wifi / MQTT Client
WiFiClient client;
PubSubClient mqttClient(client);

//Servo Global variables
Servo myservo;


//method to establish wifi ion
void setup_wifi() {

  delay(10);

  //Start the wifi
  WiFi.begin(ssid, password);

  //wait until it is up
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

}

//Callback function for reading incoming message
void callback(char* topic, byte* payload, unsigned int length){

  String sTopic(topic);
 
  //Check to see if the message is the DOG feeder topic
  if(sTopic == mqttTopicThis ){
    
    //Feed the dog - open the continious servo then shut it. 
    int pos;
    pos = 180;
 
    myservo.write(pos);

    delay(700);
  
    pos = 0;
    myservo.write(pos);
    delay(700);
    
    pos = 90;
    myservo.write(pos);    

  }  

  //double check topic is cleared
  sTopic = "";
    
}



/*******************************************************
 * Function to  the MQTT client using factory-ish pattern
 */
void reconnect(){

  //loop until reed
  while (!mqttClient.connected()){
    
    //attempt to 
    if (mqttClient.connect(mqttClientID, mqttUser, mqttPassword)){
 
 
      //Subscribe to the settings
      mqttClient.subscribe(mqttTopicThisC,1); 

    } else {

      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" , try again...");
      //Signal & wait... 
      delay(100);
    }
  }
}

//Setup method
void setup() {

 myservo.attach(D3);  // attaches the servo to the D3 pin in the servo object UPDATE
 
  Serial.begin(115200);                        //  start serial for debug
  delay(10);
  
  //Establish WIFI
  setup_wifi();

  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);

}

//Main loop
void loop() {
 
  if (!mqttClient.connected()){
    reconnect();  
  }
  mqttClient.loop(); 

}