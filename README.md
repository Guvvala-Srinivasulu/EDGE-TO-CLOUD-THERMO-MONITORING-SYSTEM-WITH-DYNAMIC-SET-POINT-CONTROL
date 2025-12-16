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
|Interrupt|P0.14|Interrupt Rising|
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

