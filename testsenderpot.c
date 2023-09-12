//TRANSMITTER CODE
#include <esp_now.h>
#include <WiFi.h>

//choose potentiometer pin as 34
int pot = 34; 


//variable to store analog value
int analog;

int ADC_Max = 4096; 

// REPLACE WITH YOUR RECEIVER MAC Address  last number 48 
uint8_t broadcastAddress[] = {0x3C, 0x71, 0xBF, 0x52, 0xBF, 0x60};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
int a;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
Serial.print("\r\nLast Packet Send Status:\t");
Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
// Init Serial Monitor
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
esp_now_peer_info_t peerInfo;
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
analog = analogRead(pot);            // read the value of the potentiometer (value between 0 and 1023)
analog = map(analog, 0, ADC_Max, 0, 180);




// Set values to send
myData.a = analog;


// Send message via ESP-NOW
esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

if (result == ESP_OK) {
Serial.println("Sent with success");
}
else {
Serial.println("Error sending the data");
}
delay(100);

}