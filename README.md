<p align="center">
  <img src="./img.png" alt="Project Banner" width="100%">
</p>

# Knock SOS 🎯

##A safety alert system using ESP32 that monitors environmental conditions and triggers alerts when a push button is pressed for 3 seconds. It also tracks temperature, gas levels, and location via GPS.

### Team Name: Ophelia

### Team Members
- Member 1: Parvathy Priyalal- TIST
- Member 2: Grania Ani Thomas- TIST


### Project Description
This system uses an ESP32 with a DHT11 temperature sensor, an MQ gas sensor, and a GPS NEO-M8N to monitor environmental conditions. When the push button is pressed for 3 seconds, a buzzer alerts nearby people, and the GPS provides the current location. A web interface displays real-time sensor data, button status, and GPS location, making it a complete solution for personal safety and emergency monitoring.
.
### The Problem statement
Problem: Accidents or emergencies can happen suddenly, and nearby people may not be aware in time. Monitoring environmental hazards like high temperature, gas leaks, or locating someone in danger is challenging.

### The Solution
Solution: This system uses an ESP32 with a DHT11, MQ gas sensor, and GPS NEO-M8N to monitor temperature, gas, and location. When a push button is pressed for 3 seconds, a buzzer alerts nearby people, and the GPS provides the location, enabling a fast response during emergencies.

---

## Technical Details

### Technologies/Components Used

**For Software:**
- Tools used: claude,arduino ide,antigravity

**For Hardware:**
- Main components: esp32,dht 11 sensor,mq gas sensor,push button,buzzer,power 5v supply by USB
- Specifications: monitors environment by sensing gas and temperature.when push button pressed for 3 sec the buzzer gets trigged for sos alert.esp32 is the main controller to read sensors and send signals.
- Tools required: multimeter,jumper wires ,breadboard,computer,usb cable.

---

## Features

List the key features of your project:
Feature 1: Emergency Alert via Button Press

Pressing the switch triggers an immediate alert on the website interface and sounds the buzzer.

Feature 2: Real-Time Environmental Monitoring

DHT11 sensor measures temperature and humidity.

MQ sensor detects harmful gases or smoke.

All values are sent live to the website dashboard for monitoring.

Feature 3: Audible Alert

Buzzer sounds whenever the button is pressed or when gas levels cross a threshold, providing instant local notification.

Feature 4: Wireless Web Dashboard

ESP32 sends sensor data via Wi-Fi to the website, allowing remote real-time monitoring from any device.

Feature 5: User-Friendly Interface

Simple button and visual alerts on the dashboard make it easy for anyone to use in an emergency.

Feature 6: Low-Power Operation & Portability

Can run on a small battery or USB power, making it portable and wearable

---

### For Hardware:

#### Components Required
ESP32 development board

DHT11 temperature and humidity sensor

MQ gas sensor (e.g., MQ-2 or MQ-135)

Push button / switch

Buzzer (3–5V)

LEDs (optional, 3mm or 5mm)

Resistors (220Ω for LEDs, 10kΩ for button)

Jumper wires / connecting wires

Breadboard or PCB

Power supply (5V USB or 3.7–5V battery)

Capacitor (optional, 100–470 µF)

#### Circuit Setup
Here’s a clear explanation of how your ESP32 circuit setup works, component by component:


---

🔌 Overall Circuit Concept

Your ESP32 acts as the main controller.

It reads sensors (DHT11, MQ gas sensor, GPS).

It takes input (push button).

It gives output (buzzer).

All components share a common GND.



---

1️⃣ DHT11 Temperature & Humidity Sensor

Connections:

Data → GPIO4

VCC → 3.3V

GND → GND


How It Works:

The DHT11 measures:

Temperature

Humidity


It sends digital data through GPIO4 to the ESP32.

Important:

If it’s a bare DHT11 (not module), you need a 10kΩ pull-up resistor between DATA and 3.3V.

If it’s a 3-pin module, pull-up is usually already built-in.



---

2️⃣ MQ Gas Sensor

Connections:

VCC → 5V

GND → GND

A0 → GPIO34


How It Works:

The MQ gas sensor detects gases like smoke/LPG.

The analog voltage at A0 changes based on gas concentration.

GPIO34 reads this analog voltage using ESP32 ADC.


⚠ Important Safety Note:

ESP32 pins are 3.3V max. Many MQ modules output up to 5V analog.

If your module outputs 5V: ➡ You must use a voltage divider before GPIO34 to avoid damaging the ESP32.

GPIO34 is good choice because:

It is input-only

Supports analog reading



---

3️⃣ Buzzer

Connections:

Positive → GPIO25

GND → GND


How It Works:

The ESP32 sends HIGH signal to GPIO25:

Current flows

Buzzer makes sound


If:

Active buzzer → Just HIGH/LOW works

Passive buzzer → Needs PWM signal


GPIO25 supports PWM, so it’s a good choice.


---

4️⃣ NEO-M8N GPS Module

Connections:

VCC → 3.3V

GND → GND

TX → GPIO16

RX → GPIO17


How It Works:

The NEO-M8N sends:

Latitude

Longitude

Time

Speed


Communication is done using UART:

GPS TX → ESP32 RX (GPIO16)

GPS RX → ESP32 TX (GPIO17)


GPIO16 & 17 are commonly used as UART2 on ESP32.


---

5️⃣ Push Button

Connections:

One pin → GND

Other pin → GPIO14


How It Works:

When button is pressed:

GPIO14 connects to GND

ESP32 reads LOW


You must enable internal pull-up:

pinMode(14, INPUT_PULLUP);

So:

Not pressed → HIGH

Pressed → LOW



---

🔁 Complete Circuit Logic Flow

1. ESP32 reads:

Temperature & humidity from DHT11

Gas level from MQ sensor

GPS location from NEO-M8N

Button state from GPIO14



2. If condition matches (example):

Gas level high

Button pressed

Temperature high



3. ESP32 activates buzzer on GPIO25.




---

⚡ Power Distribution Summary

Device	Voltage Used

ESP32	3.3V logic
DHT11	3.3V
MQ Sensor	5V
GPS	3.3V
Buzzer	3.3V logic


All components share common GND.


---

🚨 Important Checks Before Powering

✔ Common ground connected
✔ MQ analog output not exceeding 3.3V
✔ GPS voltage compatible
✔ Pull-up enabled for button


---

If you want, I can:

Draw a clean connection diagram

Explain how this works as a complete project system

Provide full working ESP32 code


What is your project? Gas detection with location tracking? 🚀

---

## Project Documentation



### For Hardware:

#### Schematic & Circuit

https://github.com/graahhhhh/knockSOS/blob/main/WhatsApp%20Image%202026-02-22%20at%2011.39.58%20AM%20(2).jpeg

https://drive.google.com/drive/folders/1_FkJ1QAbVFkNsDT0Wrse6zhrHdDefT9j
#### Build Photos

![Team](https://github.com/graahhhhh/knockSOS/blob/main/WhatsApp%20Image%202026-02-22%20at%2011.39.58%20AM.jpeg)

![Components](Add photo of your components here)
*List out all components shown*

![Build](https://github.com/graahhhhh/knockSOS/blob/main/WhatsApp%20Image%202026-02-22%20at%2011.39.58%20AM%20(1).jpeg)
*Explain the build steps*

![Final](https://github.com/graahhhhh/knockSOS/blob/main/WhatsApp%20Image%202026-02-22%20at%2011.39.58%20AM%20(1).jpeg)
*Explain the final build*

---

## Project Demo

### Video
[Add your demo video link here - YouTube, Google Drive, etc.]

*Explain what the video demonstrates - key features, user flow, technical highlights*


---

## Team Contributions

- [Name 1]: [Specific contributions - e.g., Frontend development, API integration, etc.]
- [Name 2]: [Specific contributions - e.g., Backend development, Database design, etc.]
- [Name 3]: [Specific contributions - e.g., UI/UX design, Testing, Documentation, etc.]


---

Made with ❤️ at TinkerHub
