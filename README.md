# Portable Long Range Wireless Temperature Unit and Monitor with Long Battery Life #
Sends temperature via 2.4Ghz radio link to display device at 16s intervals.  
Remote temperature transmitter unit optimized for low power consumption for long battery life.  
Estimated battery life greater that 3 years with 3xAAA batteries.  
Tranmitter range 100m (estimated).  

Code compiled using Arduino IDE


## LOW POWER WIRELESS TEMPERATURE TX-RX ##
 

![TX_RX](https://github.com/user-attachments/assets/b56367e7-31a7-442e-a9d5-376dda5b670c)

OVERVIEW
Send temerature reading using 2.4Mhz wireless link to receiver with temperature display

## TRANSMITTER  ##



MPU: Arduino Pro-Mini 3.3v Modified as follows:-   
MPU power led removed, onboard voltage regulator replaced with MCP1700 3.3v Low drop-out low quiecent current 3,3v voltage regulator.  
Regulator quiescent current 1.6uA, Droppout voltage typically 0.15V.  
Wireless transmiiter: NRF24 + PA - Channel 110  
Battery 3xAAA  
100uF electrolytic capacitor  
Data sent 16s intervals  
See Wiring.docx below:      
[MPU_Wiring.docx](https://github.com/user-attachments/files/21166246/MPU_Wiring.docx)  

![TX_inside_annotated](https://github.com/user-attachments/assets/fa08e3d8-2043-4f14-9871-b44c54c929a8)
![image](https://github.com/user-attachments/assets/280e2b2f-677c-40ac-84d2-bf7488752700)     

![image](https://github.com/user-attachments/assets/812b92f5-e23f-49f8-b10e-fa21c75316e0)  

## RECEIVER ##  

![RX_insdide_annotated](https://github.com/user-attachments/assets/dcb7a164-0e59-460b-9ab6-fcbdbd87bff9)  

MPU: SEEED XIAO SAMD21 (chosen for small size could be any other MPU)    
Wireless Receiver : NRF24 + PA - Channel 110  
Display: OLED 1.3inch I2C SSH1106  
Battery: NOKIA LiPo  (or any other LiPo battery)  
TP4056 charging module    
on/off slide switch.  






<img width="431" height="408" alt="image" src="https://github.com/user-attachments/assets/f58a898f-5e5f-44ec-af8b-9b07b7c1087b" />


## Tx Low power consumption performance: ##
TX current consumption:   
Current taken in powerdown phase about 7uA for approx 16 seconds (mpu + wireless off)  
Current taken mpu active = 3.5mA for 5ms  
Current taken mpu active + wireless transmit = 93.5 mA for 2ms  
Average current during 16s cycle: 20uA  
Battery life test:  
July 2023 4.75v  - continuous running transmit temperature reading 16s intervals
March 2024 4.374v.
July 2025 4.08v - so far 2 years continuous operation  
Assume 900mAh for AAA battery
Battery lifetime = 0.9Ah/20uA = 45.665 hours = 5.7 years

## SOFTWARE VERSIONS ##
Receiver: NRF24_Rx_XIAO_Released_V1   
Transmitter: NRF24_TX_Released_V1  

