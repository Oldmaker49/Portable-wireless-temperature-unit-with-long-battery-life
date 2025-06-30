/*
THIS VERSION
NRF24_Rx_XIAO_Released_V1
TO DO: to this version:  Display battery voltage
This is a the receiver/base station for the remote temperature sender
Based on NRF24_Rx_RC3_XIAO_Version_copy

FEATURES:
1) MPU - SEED XIAO SAMD21

2) 1.3inch OLED 128 x 64 display I2C (white)
   SSH 1106 driver
   I2C Adress 0x3C
   Adafruit_GFX.h
   Adafruit_SH110X.h


3) NRF2401 radio module LA + PA
   NRF24.h

PIN MAP

NRF Module            MPU
SCK                   D8
MISO                  D9
MOSI                  D10
CSN                   D2
CE                    D3
Vcc                   Vcc (3.3v) (10uF cap )
GND                   GND

OLED Display
SCL                   D5
SDA                   D4
GND                   GND
VCC                   Battery 

*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeMonoBold18pt7b.h>

#define CE_PIN   3
#define CSN_PIN  2


RF24 radio(CE_PIN, CSN_PIN);
float lastTemp;
const uint64_t pipeIn = 0xE8E8F0F0E1LL;// same for Tx

struct Mydata 
{ 
   uint8_t sender_ID;
   float temp;
   uint16_t battery;
   //float value;
}; 
struct Mydata data;
int DecodePacket(struct Mydata *object, char *ptr)
{

    memcpy(&object->sender_ID, ptr, sizeof object->sender_ID);
    ptr += sizeof object->sender_ID;

    memcpy(&object->temp, ptr, sizeof object->temp);
    ptr += sizeof object->temp;

    memcpy(&object->battery, ptr, sizeof object->battery);
    //ptr += sizeof object->battery;

    //memcpy(&object->value, ptr, sizeof object->value);

    return 1;
}
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
 
  Serial.begin(9600);
  
  radio.begin();   
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_MAX,1);//Low Noise Amplifier Enabled
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(110);
  radio.openReadingPipe(1, pipeIn);   //Setting the address at received the data
  radio.startListening();             //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  //radio.stopListening(); 
  display.begin(i2c_Address, true); // Address 0x3C default
  display.clearDisplay();
  display.display();
  display.setFont(&FreeMonoBold18pt7b);
  lastTemp = 9999.9;
  
}
//int16_t x1, y1;
uint16_t w, h;
const int16_t x_pos = 40, y_pos = 40;

void loop() {
                   //This sets the module as receiver
  String stringLastTemp = String (lastTemp,1);
  if (radio.available())
  {
      
      uint16_t x , y;
      char data_received[7];
      radio.read(&data_received, sizeof(data_received));
      DecodePacket(&data, data_received);
      
      Serial.println("Data Received:  ");
      Serial.print("Sender ID:  "); Serial.println(data.sender_ID);
      Serial.print("temp:  "); Serial.println(data.temp);
      Serial.print("Temperature:  "); Serial.println(data.temp,1);
      Serial.print("Battery:  "); Serial.println(data.battery);
      Serial.print("lastTemp: "); Serial.println(stringLastTemp);
      Serial.print("Size of Data: "); Serial.println(sizeof(data));

      String stringTemp = String (data.temp,1);
      float battVolts = 4.74 * data.battery / 1023; ;
      String stringBattVolts = String(battVolts,2);
      Serial.print("Battery Volts:  "); Serial.println(battVolts);
      if (stringTemp != stringLastTemp){
        display.clearDisplay();
        display.display();
        lastTemp = data.temp;
      if (data.temp > 9.9 || data.temp < 0){
        x = x_pos - 20;
        y = y_pos ;
      }
      else { x = x_pos; y = y_pos;}
      
      display.setCursor(x, y);
      display.setTextColor(SH110X_WHITE);
      display.println(stringTemp);
      display.display();

      }
      
  }
    
}