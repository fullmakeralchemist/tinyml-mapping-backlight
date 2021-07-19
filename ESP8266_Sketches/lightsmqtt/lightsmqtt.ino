#include <ESP8266WiFi.h>
#include <PubSubClient.h>


// Change the credentials below, so your ESP8266 connects to your router
const char* ssid = "GalaxyA80";
const char* password = "olof8228";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.29.4";

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient espClient;
PubSubClient client(espClient);


// Lights: will change on GPIO depending on the ESP8266 board used
// LED - GPIO 14 = D5 on ESP-12E NodeMCU board
// LED - GPIO 12 = D6 on ESP-12E NodeMCU board
// LED - GPIO 13 = D7 on ESP-12E NodeMCU board
// LED - GPIO 15 = D8 on ESP-12E NodeMCU board
// LED - GPIO 5 = D1 on ESP-12E NodeMCU board
// LED - GPIO 4 = D2 on ESP-12E NodeMCU board
const int ledonepositive = 14;
const int ledonenegative = 12;
const int ledtwopositive = 13;
const int ledtwonegative = 15;
const int ledthreepositive = 5;
const int ledthreenegative = 4;



// Timers auxiliar variables
long now = millis();

// Don't change the function below. This functions connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that 
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic dance/lights, you check if the message is either on or off. Turns the lamp GPIO according to the message
  //Fell free to change the statements on,on2,on3 to any LED combinations, or for some LED stripes statements to make it better
  if(topic=="dance/lights"){
      Serial.print("Changing lights to ");
      if(messageTemp == "on"){
        digitalWrite(ledonepositive, HIGH);
        digitalWrite(ledonenegative, LOW);
        
        digitalWrite(ledtwopositive, HIGH);
        digitalWrite(ledtwonegative, LOW);

        digitalWrite(ledthreepositive, HIGH);
        digitalWrite(ledthreenegative, LOW);
        Serial.print("On");
      }
      else if(messageTemp == "on2"){
        digitalWrite(ledonepositive, HIGH);
        digitalWrite(ledonenegative, LOW);
        
        digitalWrite(ledtwopositive, LOW);
        digitalWrite(ledtwonegative, LOW);

        digitalWrite(ledthreepositive, HIGH);
        digitalWrite(ledthreenegative, LOW);
        delay(600);
        digitalWrite(ledonepositive, LOW);
        digitalWrite(ledonenegative, LOW);
        
        digitalWrite(ledtwopositive, HIGH);
        digitalWrite(ledtwonegative, LOW);

        digitalWrite(ledthreepositive, LOW);
        digitalWrite(ledthreenegative, LOW);
        delay(600);
        digitalWrite(ledonepositive, LOW);
        digitalWrite(ledonenegative, LOW);
        
        digitalWrite(ledtwopositive, HIGH);
        digitalWrite(ledtwonegative, LOW);

        digitalWrite(ledthreepositive, LOW);
        digitalWrite(ledthreenegative, LOW);
        Serial.print("On2");
      }
      else if(messageTemp == "on3"){
        digitalWrite(ledonepositive, HIGH);
        digitalWrite(ledonenegative, LOW);
        
        digitalWrite(ledtwopositive, LOW);
        digitalWrite(ledtwonegative, LOW);

        digitalWrite(ledthreepositive, LOW);
        digitalWrite(ledthreenegative, LOW);
        delay(600);
        digitalWrite(ledonepositive, HIGH);
        digitalWrite(ledonenegative, LOW);
        
        digitalWrite(ledtwopositive, HIGH);
        digitalWrite(ledtwonegative, LOW);

        digitalWrite(ledthreepositive, LOW);
        digitalWrite(ledthreenegative, LOW);
        delay(600);
        digitalWrite(ledonepositive, HIGH);
        digitalWrite(ledonenegative, LOW);
        
        digitalWrite(ledtwopositive, HIGH);
        digitalWrite(ledtwonegative, LOW);

        digitalWrite(ledthreepositive, HIGH);
        digitalWrite(ledthreenegative, LOW);
        
        Serial.print("On3");
      }
      else if(messageTemp == "off"){
        digitalWrite(ledonepositive, LOW);
        digitalWrite(ledonenegative, LOW);
        
        digitalWrite(ledtwopositive, LOW);
        digitalWrite(ledtwonegative, LOW);

        digitalWrite(ledthreepositive, LOW);
        digitalWrite(ledthreenegative, LOW);
        Serial.print("Off");
      }
  }
  Serial.println();
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    /*
     YOU MIGHT NEED TO CHANGE THIS LINE, IF YOU'RE HAVING PROBLEMS WITH MQTT MULTIPLE CONNECTIONS
     To change the ESP device ID, you will have to give a new name to the ESP8266.
     Here's how it looks:
       if (client.connect("ESP8266Client")) {
     You can do it like this:
       if (client.connect("ESP1_Office")) {
     Then, for the other ESP:
       if (client.connect("ESP2_Garage")) {
      That should solve your MQTT multiple connections problem
    */
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("dance/lights");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// The setup function sets your ESP GPIOs to Outputs, starts the serial communication at a baud rate of 115200
// Sets your mqtt broker and sets the callback function
// The callback function is what receives messages and actually controls the LEDs
void setup() {
  pinMode(ledonepositive, OUTPUT);
  pinMode(ledonenegative, OUTPUT);
  pinMode(ledtwopositive, OUTPUT);
  pinMode(ledtwonegative, OUTPUT);
  pinMode(ledthreepositive, OUTPUT);
  pinMode(ledthreenegative, OUTPUT);
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

// For this project, you don't need to change anything in the loop function. Basically it ensures that you ESP is connected to your broker
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

  now = millis();
} 
