//TRANSMITTER CODE
#include <esp_now.h>
#include <WiFi.h>

/* connect the red pin to 3.3 V and black/brown pin to gnd */


//choose any pins as anolog pot values
int thumbpot = 4; 
int indexpot = 12; 
int middlepot = 34; 
int ringpot = 21; 
int pinkypot = 15;

//pot values are stored in these variables
int analogthumb;
int analogindex;
int analogmiddle;
int analogring;
int analogpinky; 

int ADC_Max = 4096; 

// REPLACE WITH YOUR RECEIVER MAC Address
/* the last address marked 48 should be used as reciever and its adress should be written below */
uint8_t broadcastAddress[] = {0x3C, 0x71, 0xBF, 0x52, 0xBF, 0x60};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
int a;
int b;
int c;
int d;
int e;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback when data is sent (espnowprotocol)
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
Serial.print("\r\nLast Packet Send Status:\t");
Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
// Init Serial Monitor
Serial.begin(115200);

// Set device as a Wi-Fi Station
WiFi.mode(WIFI_STA); (espnow protocol)

// Init ESP-NOW (espnowprotocol)
if (esp_now_init() != ESP_OK) {
Serial.println("Error initializing ESP-NOW");
return;
}

// Once ESPNow is successfully Init, we will register for Send CB to
// get the status of Trasnmitted packet(espnowprotocol)
esp_now_register_send_cb(OnDataSent);

// Register peer (espnow protocol)
esp_now_peer_info_t peerInfo;
memcpy(peerInfo.peer_addr, broadcastAddress, 6);
peerInfo.channel = 0;
peerInfo.encrypt = false;

// Add peer ( espnowprotocol)
if (esp_now_add_peer(&peerInfo) != ESP_OK){
Serial.println("Failed to add peer");
return;
}
}

void loop() {{
analogthumb = analogRead(thumbpot);            // read the value of the potentiometer (value between 0 and 1023)
analogthumb = map(analogthumb, 0, ADC_Max, 0, 180);

analogindex = analogRead(indexpot);            // read the value of the potentiometer (value between 0 and 1023)
analogindex = map(analogindex, 0, ADC_Max, 0, 180);

analogmiddle = analogRead(middlepot);            // read the value of the potentiometer (value between 0 and 1023)
analogmiddle = map(analogmiddle, 0, ADC_Max, 0, 180);

analogring = analogRead(ringpot);            // read the value of the potentiometer (value between 0 and 1023)
analogring = map(analogring, 0, ADC_Max, 0, 180);

analogpinky = analogRead(pinkypot);            // read the value of the potentiometer (value between 0 and 1023)
analogpinky = map(analogpinky, 0, ADC_Max, 0, 180);

}

// Set values to send
myData.a = analogthumb;
myData.b = analogindex;
myData.c = analogmiddle;
myData.d = analogring;
myData.e = analogpinky;

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
