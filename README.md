# Portable-Long-range-Low-Power-Temperature-Monitor
Sends temperature via 2.4Ghz radio link to display device. Remote unit optimized for low power consumption for long battery life
LOW POWER WIRELESS TEMPERATURE TX-RX

OVERVIEW
Send temerature reading using 2.4Mhz wireless link to receiver with temperature display

TRANSMITTER
MPU: Arduino Pro-Mini 3.3v - power led removed, voltage regulator replaced with HT7333
Wireless: NRF24 + PA - Channel 110
Temperature Sensor: BMP280
Battery 3xAAA
Data sent per 16s

RECEIVER
MPU: SEEED XIAO SAMD21
Wireless: NRF24 + PA - Channel 110
Display: OLED 1.3inch I2C SSH1106
Battery: NOKIA LiPo + TP4056 charging module

Performance:
TX low power consumption - e.g new batteries July 2023 4.75v  - continuous running 
Battery voltage as of 20 MAR 2024 4.374v.
Current taken in powerdown phase about 7uA for approx 16 seconds (mpu + wireless off)
Current taken mpu active = 3.5mA for 5ms
Current taken mpu active + wireless transmit = 93.5 mA for 2ms

average current during 16s cycle about 20uA
Assume 900mAh for AAA battery
Battery lifetime = 0.9Ah/20uA = 45.665 hours = 5.7 years

SOFTWARE VERSIONS
NRF24_Rx_XIAO_Released_V1
NRF24_TX_Released_V1

