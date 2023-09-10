/*ADC1_CH0 (GPIO 36)
ADC1_CH1 (GPIO 37)
ADC1_CH2 (GPIO 38)
ADC1_CH3 (GPIO 39)
ADC1_CH4 (GPIO 32)
ADC1_CH5 (GPIO 33)
ADC1_CH6 (GPIO 34)
ADC1_CH7 (GPIO 35)
ADC2_CH0 (GPIO 4)
ADC2_CH1 (GPIO 0)
ADC2_CH2 (GPIO 2)
ADC2_CH3 (GPIO 15)
ADC2_CH4 (GPIO 13)
ADC2_CH5 (GPIO 12)
ADC2_CH6 (GPIO 14)
ADC2_CH7 (GPIO 27)
ADC2_CH8 (GPIO 25)
ADC2_CH9 (GPIO 26)*/



#include <esp_now.h>


    

#define THUMB_PIN_POTENTIOMETER 33
#define INDEX_PIN_POTENTIOMETER 34
#define MIDDLE_PIN_POTENTIOMETER 35
#define RING_PIN_POTENTIOMETER 36
#define PINKY_PIN_POTENTIOMETER 37 



uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}




void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  
}

void loop() {
  // reads the value of the potentiometer (value between 0 and 4095)
  int analogValue1 = analogRead(THUMB_PIN_POTENTIOMETER);
  int analogValue2 = analogRead(INDEX_PIN_POTENTIOMETER);
  int analogValue3 = analogRead(MIDDLE_PIN_POTENTIOMETER);
  int analogValue4 = analogRead(RING_PIN_POTENTIOMETER);
  int analogValue5 = analogRead(PINKY_PIN_POTENTIOMETER);

  // scales it to use it with the servo (value between 0 and 180)
  int angle1 = map(analogValue1, 0, 4095, 0, 180);
  int angle2 = map(analogValue2, 0, 4095, 0, 180);
  int angle3 = map(analogValue3, 0, 4095, 0, 180);
  int angle4 = map(analogValue4, 0, 4095, 0, 180);
  int angle5 = map(analogValue5, 0, 4095, 0, 180);

  int anglesend[5] = {angle1,angle2,angle3,angle4,angle5 };

  esp_err_t result = esp_now_send(broadcastAddress, &anglesend, sizeof(anglesend));
     if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);

  
}