
/* 
THIS VERSION
NRF24_TX_Released_V1
This version deals with the problem of sending data stucture fiom one MPU to another

CHANGES:
BMP Vcc supplied from Digital output pin - not needed but kept
BMP280 used in FORCED_MODE
Measured current during powerdown is 7uA

PREVIOUS VERSION
NRF24_Temperature_Sender_TX_RC3_XIAO_V3_16s
ISSUES
Supply current mesure Min 6uA power down with periodic increases to 0.22mA
It is thought that this is due to the BMP280 regularly reading the temperature.

           

FEATURES
1) BMP280 Temperature Sensor I2C
   Address:  0x76
   SensorID: 0x58
   Adafruit_BMP280.h
   Vcc      D6


2) NRF 24 + PA TRANSMITTER

  Module // Arduino PRO-MINI
    GND    ->   GND
    Vcc    ->   3.3V
    CE     ->   D7
    CSN    ->   D8
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "LowPower.h"
#include <Wire.h>
#include <Adafruit_BMP280.h>
/*Create a unique pipe out. The receiver has to
  wear the same unique code*/
const uint64_t pipeOut = 0xE8E8F0F0E1LL; //IMPORTANT: The same as in the receiver!!!

/*Create the data struct we will send
  The sizeof this struct should not exceed 32 bytes
  This gives us up to 32 8 bits channals */
RF24 radio(7, 8); // select  CSN and CE  pins
struct MyData 
{ 
   uint8_t sender_ID;// 1 byte
   float temp;//4 bytes
   uint16_t battery;//2 byte
   
   // total = 7
}; 
struct MyData data;


size_t EncodePacket(unsigned char *dst, const struct MyData *object)
{
    size_t i = 0;

    memcpy(&dst[i], &object->sender_ID, sizeof object->sender_ID);
    i += sizeof object->sender_ID;

    memcpy(&dst[i], &object->temp, sizeof object->temp);
    i += sizeof object->temp;

    memcpy(&dst[i], &object->battery, sizeof object->battery);
    i += sizeof object->battery;

    //memcpy(&dst[i], &object->value, sizeof object->value);
    //i += sizeof object->value;

    return i;
}


#define BMP280_VCC 6 // BMP280 supplied from GPIO 6
Adafruit_BMP280 bmp; // I2C

void setup()
{
  //Start everything up
  Serial.begin(9600);
  analogReference(INTERNAL);
  radio.begin();
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(110);
  radio.openWritingPipe(pipeOut);
  radio.stopListening();

  //pinMode(BMP280_VCC, OUTPUT);
  //digitalWrite(BMP280_VCC, HIGH);
 // delay(100);

 bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
 bmp.setSampling(Adafruit_BMP280::MODE_FORCED,   // Operating Mode. 
                  Adafruit_BMP280::SAMPLING_X1,     // Temp. oversampling 
                  Adafruit_BMP280::SAMPLING_X1,    // Pressure oversampling 
                  Adafruit_BMP280::FILTER_OFF,      // Filtering.
                  Adafruit_BMP280::STANDBY_MS_1); // Standby time. 

}



void loop()
{
  bmp.takeForcedMeasurement();
  data.sender_ID = 9;//dummy data
  data.temp = bmp.readTemperature();
  //delay(50);
  data.battery = analogRead(A1);//battery voltage
  //Serial.print("data.temp :  "); Serial.println(data.temp);
  //Serial.print("data.battery :  "); Serial.println(data.battery);
  //delay(10);
  radio.powerUp();
  
    char data_to_send[7];
    EncodePacket(data_to_send, &data);
    radio.write(&data_to_send, sizeof(data_to_send));

  radio.powerDown();

  for (int i = 0; i < 2; i++){ //powerdown period = 8s * i max  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  //delay(1000);
  }
  delay(5);//to allow time for forced measurement of temperature
           // and analogue measurement of battery voltage
}