# Portable-Long-range-Low-Power-Temperature-Monitor
Sends temperature via 2.4Ghz radio link to display device at 16s intervals.  
Remote temperature transmitter unit optimized for low power consumption for long battery life.  
Estimated battery life greater that 3 years with 3xAAA batteries.  


LOW POWER WIRELESS TEMPERATURE TX-RX
Temperature Sensor: BMP280  

![TX_RX](https://github.com/user-attachments/assets/b56367e7-31a7-442e-a9d5-376dda5b670c)

OVERVIEW
Send temerature reading using 2.4Mhz wireless link to receiver with temperature display

TRANSMITTER  

 ![TX_inside_annotated](https://github.com/user-attachments/assets/4cded369-e629-4aa9-8bef-5d520a85768e)

MPU: Arduino Pro-Mini 3.3v Modified as follows:- 




MPU power led removed, onboard voltage regulator replaced with HT7333 Low drop-out low quiecent current 3,3v voltage regulator  
See Wiring.docx below:
See voltage regulator specification below:

Wireless transmiiter: NRF24 + PA - Channel 110

Battery 3xAAA
Data sent 16s intervals

RECEIVER  
![RX_insdide_annotated](https://github.com/user-attachments/assets/d483b803-9c29-44d7-9a22-e13f7696d73d)

MPU: SEEED XIAO SAMD21
Wireless Receiver : NRF24 + PA - Channel 110
Display: OLED 1.3inch I2C SSH1106
Battery: NOKIA LiPo + TP4056 charging module  
on/off slide switch

3xAAA batteries  
  
![image](https://github.com/user-attachments/assets/e2c76261-1232-4d48-8082-a891044f0df6)

![image](https://github.com/user-attachments/assets/b15cd078-ba87-47cb-afa7-ac98e6563985)  

![image](https://github.com/user-attachments/assets/280e2b2f-677c-40ac-84d2-bf7488752700)    

![image](https://github.com/user-attachments/assets/812b92f5-e23f-49f8-b10e-fa21c75316e0)  

[MPU_Wiring.docx](https://github.com/user-attachments/files/21076624/MPU_Wiring.docx)  

Tx Low power Performance:
TX low power consumption - e.g new batteries July 2023 4.75v  - continuous running transmit temperature reading 16s intervals
Battery voltage as of 20 MAR 2024 4.374v.
Current taken in powerdown phase about 7uA for approx 16 seconds (mpu + wireless off)
Current taken mpu active = 3.5mA for 5ms
Current taken mpu active + wireless transmit = 93.5 mA for 2ms  
4 July 2025 Battery voltage 4.08v - 2 years of continouous operation so far!  
average current during 16s cycle about 20uA  



Assume 900mAh for AAA battery
Battery lifetime = 0.9Ah/20uA = 45.665 hours = 5.7 years

SOFTWARE VERSIONS
NRF24_Rx_XIAO_Released_V1
NRF24_TX_Released_V1

