#include <ESP32_Servo.h>

//Receiver Code
#include <esp_now.h>
#include <WiFi.h>

//Servo objects
Servo Servomotor1;
Servo Servomotor3;
Servo Servomotor4;
Servo Servomotor2;
Servo Servomotor5;

// servo pin declaration
int thumbservopin = 35; 
int indexservopin = 34; 
int middleservopin = 33; 
int ringservopin = 32; 
int pinkyservopin = 25;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
int a;
int b;
int c;
int d;
int e;
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
Serial.print("int: ");
Serial.println(myData.b);
Serial.print("int: ");
Serial.println(myData.c);
Serial.print("int: ");
Serial.println(myData.d);
Serial.print("int: ");
Serial.println(myData.e);
Serial.println();
}



int analogthumb = myData.a;
int analogindex = myData.b;
int analogmiddle = myData.c;
int analogring = myData.d;
int analogpinky = myData.e;

void setup() {

//Naampies servo motor input pins INPUT PINS AANPASSEN VANWEGE VERANDERINGEN
Servomotor1.attach(18); //A1 D18
Servomotor2.attach(4); //A2 D4
Servomotor3.attach(5); //A3 D5
Servomotor4.attach(21); //A4 D21
Servomotor5.attach(19); //A5 D19

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

Servomotor1.write(analogthumb); 
Servomotor2.write(analogindex)); 
Servomotor3.write(analogmiddle));
Servomotor4.write(analogring));
Servomotor5.write(analogpinky)); 
}
