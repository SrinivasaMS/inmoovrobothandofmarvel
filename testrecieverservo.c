#include <ESP32Servo.h>

//Receiver Code (Hand) 
#include <esp_now.h>
#include <WiFi.h>

//Servo naampies
Servo Servomotor;


int servopin = 35; 

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
int a;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
memcpy(&myData, incomingData, sizeof(myData)); 
Serial.print("Bytes received: ");
Serial.println(len);
Serial.print("int: ");
Serial.println(myData.a);
}



int analog = myData.a;


void setup() {

//servo pin gets attached to esp32
Servomotor.attach(servopin); //d35


// Initialize Serial Monitor
Serial.begin(115200);

// Set device as a Wi-Fi Station
WiFi.mode(WIFI_STA);

// Init ESP-NOW
if (esp_now_init() != ESP_OK) {
Serial.println("Error initializing ESP-NOW");
return;
}

// Once ESPNow is successfully Init, we will register for recv CB to
// get recv packer info
esp_now_register_recv_cb(OnDataRecv);
}
void loop(){

Servomotor.write(analog); 
}
