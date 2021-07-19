#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

BLEService sensorService("16150f38-e7a9-4fe1-ae08-48464baf25b2");
BLEStringCharacteristic  gxSensorLevel("ff99948c-18ff-4ed8-942e-512b9b24b6da", 
    BLERead | BLENotify,15);
BLEStringCharacteristic  gySensorLevel("8084aa6b-6cae-461f-9540-e1a5768de49d", 
    BLERead | BLENotify,15);
BLEStringCharacteristic  gzSensorLevel("ab80cb77-fe74-40d8-9757-96f8a54c16d9", 
    BLERead | BLENotify,15);     
BLEStringCharacteristic  axSensorLevel("ff99948c-18ff-4ed8-942e-512b9b24b6dc", 
    BLERead | BLENotify,15);
BLEStringCharacteristic  aySensorLevel("8084aa6b-6cae-461f-9540-e1a5768de49t", 
    BLERead | BLENotify,15);
BLEStringCharacteristic  azSensorLevel("ab80cb77-fe74-40d8-9757-96f8a54c16d7", 
    BLERead | BLENotify,15);     

// last sensor data    
float oldgXLevel = 0; 
float oldgYLevel = 0; 
float oldgZLevel = 0; 
float oldaXLevel = 0; 
float oldaYLevel = 0; 
float oldaZLevel = 0; 
long previousMillis = 0;  

void setup() {
  Serial.begin(115200);  
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  pinMode(LED_BUILTIN, OUTPUT); 
  
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Gyroscope");
  BLE.setAdvertisedService(sensorService);
  
  sensorService.addCharacteristic(gxSensorLevel);
  sensorService.addCharacteristic(gySensorLevel);
  sensorService.addCharacteristic(gzSensorLevel);
  sensorService.addCharacteristic(axSensorLevel);
  sensorService.addCharacteristic(aySensorLevel);
  sensorService.addCharacteristic(azSensorLevel);
  BLE.addService(sensorService); 

  // initialize default data
  gxSensorLevel.writeValue(String(0)); 
  gySensorLevel.writeValue(String(0)); 
  gzSensorLevel.writeValue(String(0)); 
  axSensorLevel.writeValue(String(0)); 
  aySensorLevel.writeValue(String(0)); 
  azSensorLevel.writeValue(String(0));

  // start advertising
  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  // wait for a BLE central
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);

    while (central.connected()) {
      //long currentMillis = millis();
      updateGyroscopeLevel();
      delay(300);
    }

    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}

void updateGyroscopeLevel() {
  float aX, aY, aZ, gX, gY, gZ;

  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    IMU.readAcceleration(aX, aY, aZ);
    IMU.readGyroscope(gX, gY, gZ);

    if (gX != oldgXLevel) {
       gxSensorLevel.writeValue(String(gX)); 
       oldgXLevel = gX;
    }
    if (gY != oldgYLevel) {
       gySensorLevel.writeValue(String(gY)); 
       oldgYLevel = gY;
    }
    if (gZ != oldgZLevel) {
       gzSensorLevel.writeValue(String(gZ)); 
       oldgZLevel = gZ;
    }
    if (aX != oldaXLevel) {
       axSensorLevel.writeValue(String(aX)); 
       oldaXLevel = aX;
    }
    if (aY != oldaYLevel) {
       aySensorLevel.writeValue(String(aY)); 
       oldaYLevel = aY;
    }
    if (aZ != oldaZLevel) {
       azSensorLevel.writeValue(String(aZ)); 
       oldaZLevel = aZ;
    }
    Serial.print(gX);
    Serial.print('\t');
    Serial.print(gY);
    Serial.print('\t');
    Serial.print(gZ);
    Serial.print('\t');
    Serial.print(aX);
    Serial.print('\t');
    Serial.print(aY);
    Serial.print('\t');
    Serial.println(aZ);

  }
}
