<p align="center">
  <img src="./img.png" alt="Project Banner" width="100%">
</p>

# Knock SOS 🎯

##A safety alert system using ESP32 that monitors environmental conditions and triggers alerts when a push button is pressed for 3 seconds. It also tracks temperature, gas levels, and location via GPS.

### Team Name: Ophelia

### Team Members
- Member 1: Parvathy Priyalal- TIST
- Member 2: Grania Ani Thomas- TIST

### Hosted Project Link
[mention your project hosted link here]

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

## Implementation

### For Software:

#### Installation
```bash
[Installation commands - e.g., npm install, pip install -r requirements.txt]
```

#### Run
```bash
[Run commands - e.g., npm start, python app.py]
```

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


### For Software:

#### Screenshots (Add at least 3)

![Screenshot1](Add screenshot 1 here with proper name)
*Add caption explaining what this shows*

![Screenshot2](Add screenshot 2 here with proper name)
*Add caption explaining what this shows*

![Screenshot3](Add screenshot 3 here with proper name)
*Add caption explaining what this shows*

#### Diagrams

**System Architecture:**

![Architecture Diagram](docs/architecture.png)
*Explain your system architecture - components, data flow, tech stack interaction*

**Application Workflow:**

![Workflow](docs/workflow.png)
*Add caption explaining your workflow*

---

### For Hardware:

#### Schematic & Circuit

https://drive.google.com/drive/folders/1_FkJ1QAbVFkNsDT0Wrse6zhrHdDefT9j
#### Build Photos

![Team](Add photo of your team here)

![Components](Add photo of your components here)
*List out all components shown*

![Build](Add photos of build process here)
*Explain the build steps*

![Final](Add photo of final product here)
*Explain the final build*

---

## Additional Documentation

### For Web Projects with Backend:

#### API Documentation

**Base URL:** `https://api.yourproject.com`

##### Endpoints

**GET /api/endpoint**
- **Description:** [What it does]
- **Parameters:**
  - `param1` (string): [Description]
  - `param2` (integer): [Description]
- **Response:**
```json
{
  "status": "success",
  "data": {}
}
```

**POST /api/endpoint**
- **Description:** [What it does]
- **Request Body:**
```json
{
  "field1": "value1",
  "field2": "value2"
}
```
- **Response:**
```json
{
  "status": "success",
  "message": "Operation completed"
}
```

[Add more endpoints as needed...]

---

### For Mobile Apps:

#### App Flow Diagram

![App Flow](docs/app-flow.png)
*Explain the user flow through your application*

#### Installation Guide

**For Android (APK):**
1. Download the APK from [Release Link]
2. Enable "Install from Unknown Sources" in your device settings:
   - Go to Settings > Security
   - Enable "Unknown Sources"
3. Open the downloaded APK file
4. Follow the installation prompts
5. Open the app and enjoy!

**For iOS (IPA) - TestFlight:**
1. Download TestFlight from the App Store
2. Open this TestFlight link: [Your TestFlight Link]
3. Click "Install" or "Accept"
4. Wait for the app to install
5. Open the app from your home screen

**Building from Source:**
```bash
# For Android
flutter build apk
# or
./gradlew assembleDebug

# For iOS
flutter build ios
# or
xcodebuild -workspace App.xcworkspace -scheme App -configuration Debug
```

---

### For Hardware Projects:

#### Bill of Materials (BOM)

| Component | Quantity | Specifications | Price | Link/Source |
|-----------|----------|----------------|-------|-------------|
| Arduino Uno | 1 | ATmega328P, 16MHz | ₹450 | [Link] |
| LED | 5 | Red, 5mm, 20mA | ₹5 each | [Link] |
| Resistor | 5 | 220Ω, 1/4W | ₹1 each | [Link] |
| Breadboard | 1 | 830 points | ₹100 | [Link] |
| Jumper Wires | 20 | Male-to-Male | ₹50 | [Link] |
| [Add more...] | | | | |

**Total Estimated Cost:** ₹[Amount]

#### Assembly Instructions

**Step 1: Prepare Components**
1. Gather all components listed in the BOM
2. Check component specifications
3. Prepare your workspace
![Step 1](images/assembly-step1.jpg)
*Caption: All components laid out*

**Step 2: Build the Power Supply**
1. Connect the power rails on the breadboard
2. Connect Arduino 5V to breadboard positive rail
3. Connect Arduino GND to breadboard negative rail
![Step 2](images/assembly-step2.jpg)
*Caption: Power connections completed*

**Step 3: Add Components**
1. Place LEDs on breadboard
2. Connect resistors in series with LEDs
3. Connect LED cathodes to GND
4. Connect LED anodes to Arduino digital pins (2-6)
![Step 3](images/assembly-step3.jpg)
*Caption: LED circuit assembled*

**Step 4: [Continue for all steps...]**

**Final Assembly:**
![Final Build](images/final-build.jpg)
*Caption: Completed project ready for testing*

---

### For Scripts/CLI Tools:

#### Command Reference

**Basic Usage:**
```bash
python script.py [options] [arguments]
```

**Available Commands:**
- `command1 [args]` - Description of what command1 does
- `command2 [args]` - Description of what command2 does
- `command3 [args]` - Description of what command3 does

**Options:**
- `-h, --help` - Show help message and exit
- `-v, --verbose` - Enable verbose output
- `-o, --output FILE` - Specify output file path
- `-c, --config FILE` - Specify configuration file
- `--version` - Show version information

**Examples:**

```bash
# Example 1: Basic usage
python script.py input.txt

# Example 2: With verbose output
python script.py -v input.txt

# Example 3: Specify output file
python script.py -o output.txt input.txt

# Example 4: Using configuration
python script.py -c config.json --verbose input.txt
```

#### Demo Output

**Example 1: Basic Processing**

**Input:**
```
This is a sample input file
with multiple lines of text
for demonstration purposes
```

**Command:**
```bash
python script.py sample.txt
```

**Output:**
```
Processing: sample.txt
Lines processed: 3
Characters counted: 86
Status: Success
Output saved to: output.txt
```

**Example 2: Advanced Usage**

**Input:**
```json
{
  "name": "test",
  "value": 123
}
```

**Command:**
```bash
python script.py -v --format json data.json
```

**Output:**
```
[VERBOSE] Loading configuration...
[VERBOSE] Parsing JSON input...
[VERBOSE] Processing data...
{
  "status": "success",
  "processed": true,
  "result": {
    "name": "test",
    "value": 123,
    "timestamp": "2024-02-07T10:30:00"
  }
}
[VERBOSE] Operation completed in 0.23s
```

---

## Project Demo

### Video
[Add your demo video link here - YouTube, Google Drive, etc.]

*Explain what the video demonstrates - key features, user flow, technical highlights*

### Additional Demos
[Add any extra demo materials/links - Live site, APK download, online demo, etc.]

---

## AI Tools Used (Optional - For Transparency Bonus)

If you used AI tools during development, document them here for transparency:

**Tool Used:** [e.g., GitHub Copilot, v0.dev, Cursor, ChatGPT, Claude]

**Purpose:** [What you used it for]
- Example: "Generated boilerplate React components"
- Example: "Debugging assistance for async functions"
- Example: "Code review and optimization suggestions"

**Key Prompts Used:**
- "Create a REST API endpoint for user authentication"
- "Debug this async function that's causing race conditions"
- "Optimize this database query for better performance"

**Percentage of AI-generated code:** [Approximately X%]

**Human Contributions:**
- Architecture design and planning
- Custom business logic implementation
- Integration and testing
- UI/UX design decisions

*Note: Proper documentation of AI usage demonstrates transparency and earns bonus points in evaluation!*

---

## Team Contributions

- [Name 1]: [Specific contributions - e.g., Frontend development, API integration, etc.]
- [Name 2]: [Specific contributions - e.g., Backend development, Database design, etc.]
- [Name 3]: [Specific contributions - e.g., UI/UX design, Testing, Documentation, etc.]

---

## License

This project is licensed under the [LICENSE_NAME] License - see the [LICENSE](LICENSE) file for details.

**Common License Options:**
- MIT License (Permissive, widely used)
- Apache 2.0 (Permissive with patent grant)
- GPL v3 (Copyleft, requires derivative works to be open source)

---

Made with ❤️ at TinkerHub
