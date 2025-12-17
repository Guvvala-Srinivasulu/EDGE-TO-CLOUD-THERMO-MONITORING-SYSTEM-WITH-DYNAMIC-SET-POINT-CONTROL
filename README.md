# 🌡️ EDGE-TO-CLOUD THERMO MONITORING SYSTEM  
## *with Dynamic Set-Point Control*

A smart **IoT-enabled embedded monitoring system** that continuously senses **temperature and humidity**, applies **dynamic threshold control at the edge**, and publishes real-time data to the **cloud for remote visualization and analysis**.

This project bridges **industrial-grade embedded control** with **cloud-based monitoring**, ensuring reliability, flexibility, and scalability.

---

## ✨ Features

- 🌡️ **Real-Time Temperature & Humidity Monitoring**  
  Continuous sensing using a digital temperature–humidity sensor.

- 🎛 **Dynamic Set-Point Configuration**  
  User-defined temperature and humidity limits via keypad input.

- 🖥 **Live LCD Display**  
  Real-time display of sensor values, set-points, and system status on a 16×2 LCD.

- ⚠ **Threshold-Based Alert System**  
  Buzzer activates automatically when temperature or humidity exceeds the configured limits.

- ☁ **Edge-to-Cloud Data Transmission**  
  Sensor data is uploaded to **ThingSpeak** using the ESP8266 Wi-Fi module.

- 📊 **Remote Visualization & Analysis**  
  Cloud dashboards enable graphical monitoring from anywhere.

- 🔁 **Continuous Autonomous Operation**  
  Operates without manual intervention once configured.

---

## 🛠 Hardware Components

- **LPC2148 (ARM7) Microcontroller**  
- **Temperature & Humidity Sensor (DHT11 / DHT22)**  
- **ESP8266 (ESP-01) Wi-Fi Module**  
- **16×2 HD44780-Compatible LCD**  
- **Matrix Keypad**  
- **Buzzer (Alert Output)**  
- **Regulated Power Supply (5V / 3.3V)**  
- **USB-UART Converter (Programming & Debugging)**  

---

## 📌 Pin Configuration

| Signal | Pin | Description |
|------|------|------------|
| LCD Data | P0.16 – P0.23 | 8-bit LCD data bus |
| LCD RS | P0.8 | Register select |
| LCD EN | P0.9 | Enable signal |
| Keypad Rows | P1.20 – P1.19 | Row scan lines |
| Keypad Columns | P1.16 – P1.23 | Column scan lines |
| Buzzer | P0.6 | Alert indication |
| ESP8266 TX/RX | UART0 | Cloud communication |
|Interrupt | P0.14 | Interrupt Rising |
---

## 🧩 Software Overview

- Entire firmware written in **Embedded C**
- Developed using **Keil µVision IDE**
- Programmed using **Flash Magic**
- Implements:
  - GPIO interfacing  
  - Keypad scanning  
  - LCD command & data routines  
  - Sensor data acquisition  
  - UART communication  
  - ESP8266 AT command handling  
  - Threshold comparison logic  
  - Cloud data upload (ThingSpeak)

---

## 🧭 System Architecture

![System Block Diagram](images/proteus_overview.png)  
*Figure 1: Complete Proteus simulation showing LPC2148, sensor, LCD, keypad, buzzer, and ESP8266.*

---

## 🧑‍💻 User Guide

1. Power on the system — LCD shows **current temperature and humidity**.
2. Press the keypad to enter **dynamic set-point configuration mode**.
3. Edit:
   - Temperature Set-Point (°C)
   - Humidity Set-Point (%)
4. Confirm inputs using `=` key.
5. System resumes **normal monitoring** with updated set-points.
6. Alerts (buzzer) trigger automatically if thresholds are exceeded.
7. Data is uploaded to **ThingSpeak** for cloud visualization.

---

## ⚠ Known Issues

- **ESP8266 Wi-Fi Connection:** Sometimes requires reset after long idle periods.
- **Threshold Edge Cases:** Setting temperature/humidity exactly at sensor min/max may not trigger alert correctly.
- **LCD Display:** Blinking may occur if multiple updates happen within milliseconds.
- **Cloud Delay:** ThingSpeak data refresh may show a 15–20 second delay.

---

## 📸 Project Images / Screenshots

### Proteus Simulation Overview
![image alt](https://github.com/Guvvala-Srinivasulu/EDGE-TO-CLOUD-THERMO-MONITORING-SYSTEM-WITH-DYNAMIC-SET-POINT-CONTROL/blob/667b06d9f471f2a672399fdc9f9af26487d01e7c/Hardware%20Look/IMG_20251217_163253_359.jpg)  
*Figure 2: LPC2148, sensor, LCD, keypad, buzzer, and ESP8266 in Proteus.*

### LCD & Keypad Interaction
![LCD & Keypad](images/proteus_lcd_keypad.png)  
*Figure 3: Display shows live sensor values; keypad used for set-point configuration.*

### ESP8266 Cloud Communication
![ESP8266 ThingSpeak Upload](images/proteus_esp8266.png)  
*Figure 4: Real-time temperature and humidity data being uploaded to ThingSpeak.*

### Cloud Visualization
![ThingSpeak Graph](images/proteus_cloud_output.png)  
*Figure 5: Graphical representation of temperature & humidity trends on ThingSpeak.*

---

## 💡 Future Enhancements

- Multi-sensor integration (multiple temperature & humidity sensors)  
- Wireless remote configuration via mobile or web interface  
- Energy optimization by triggering connected devices based on thresholds  
- Historical data logging with cloud analytics for predictive maintenance  
- Backup memory (EEPROM/Flash) to store thresholds during power loss  
- Graphical OLED or TFT display for improved UI  
- Mobile notifications (SMS/Email) on threshold violations  

---

