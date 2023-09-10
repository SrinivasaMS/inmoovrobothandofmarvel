#include <esp_now.h>
#include <WiFi.h>
#include <Servo.h>

#define THUMB_PIN_SERVO    12     
#define INDEX_PIN_SERVO    13    
#define MIDDLE_PIN_SERVO   14      
#define RING_PIN_SERVO     15   
#define PINKY_PIN_SERVO    04 

Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;
Servo myServo5;

int angles[5];

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *data, int data_len) {

    Serial.print("Recieved data: ");
    for (int i = 0; i < data_len; i++ ){
      angle[i] = data[i];
    }

}
 
void setup() {
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
  myServo1.attach(THUMB_PIN_SERVO);
  myServo2.attach(INDEX_PIN_SERVO);
  myServo3.attach(MIDDLE_PIN_SERVO);
  myServo4.attach(RING_PIN_SERVO);
  myServo5.attach(PINKY_PIN_SERVO);  // attaches ESP32 pin to the servo object


}
 
void loop() {
  // sets the servo position according to the scaled value
  myServo1.write(angle[1]);
  myServo2.write(angle[2]);
  myServo3.write(angle[3]);
  myServo4.write(angle[4]);
  myServo5.write(angle[5]);

  
  Serial.println(angle[1]);
  Serial.println(angle[2]);
  Serial.println(angle[3]);
  Serial.println(angle[4]);
  Serial.println(angle[5]);
  delay(100);

}
