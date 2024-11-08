<img src="https://github.com/user-attachments/assets/f7a8f2cc-5b44-46b6-bd18-fb6d0abdf011" alt="Image 1" width="400">
<img src="https://github.com/user-attachments/assets/98612a53-307e-4458-9a4c-1876272ffe63" alt="Image 2" width="400">
<img src="https://github.com/user-attachments/assets/98c28652-95e5-45f4-b9b3-f51f5b9ef505" alt="Image 3" width="400">
<img src="https://github.com/user-attachments/assets/d4f05bd4-9c4d-410c-ad77-961e8fefed29" alt="Image 4" width="400">



# IoT-Based Smart Greenhouse Project

This project uses an ESP32 microcontroller to automate and monitor conditions within a greenhouse environment. It measures soil moisture, gas levels, and ambient light, controlling a water pump, fan, and LED based on predefined thresholds. Data is displayed on an OLED screen and can be accessed via a simple web dashboard.

## Features

- **Automatic Water Pump Control**: Waters plants based on soil moisture levels.
- **Gas Level Monitoring**: Activates a fan when gas levels exceed a set threshold.
- **Light Control**: Manages lighting based on ambient light levels using an LDR.
- **Remote Monitoring**: View real-time data and status on a web-based dashboard.
- **OLED Display**: Local display of greenhouse conditions, providing a snapshot of data.

## Components Used

- **ESP32 Microcontroller**
- **Soil Moisture Sensor** (Analog Input)
- **MQ Gas Sensor** (Analog Input)
- **Light Dependent Resistor (LDR)** (Analog Input)
- **Water Pump Relay**
- **Fan Relay**
- **LED**
- **OLED Display (SSD1306)** for local data display

## Pin Configuration

| Component            | ESP32 Pin        |
|----------------------|------------------|
| Soil Moisture Sensor | GPIO 34 (Analog) |
| Pump Relay           | GPIO 4           |
| Gas Sensor           | GPIO 35 (Analog) |
| Fan Relay            | GPIO 14          |
| LDR                  | GPIO 33 (Analog) |
| LED                  | GPIO 5           |

## Setup

### Hardware

1. Connect sensors and relays to the specified GPIO pins.
2. Attach the OLED display to the I2C pins (typically `SDA` and `SCL`).
3. Power up the ESP32 with a suitable power source.

### Software

1. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd <repository-directory>

3. Install Dependencies: Ensure you have the following libraries installed in your Arduino IDE:

WiFi.h
Wire.h
Adafruit_GFX.h
Adafruit_SSD1306.h

2. **Set WiFi Credentials:**: In the code, replace ssid and password with your WiFi network details:
   ```bash
   const char* ssid = "Your_SSID";
   const char* password = "Your_Password";

4. Upload Code: Connect the ESP32 to your computer and upload the code using the Arduino IDE.

## Usage
Once the ESP32 is powered and connected to WiFi:

- **Web Dashboard**: Open a browser and navigate to the IP address printed in the Serial Monitor to access the dashboard.
- **OLED Display**: The OLED will show real-time data on soil moisture, gas level, and light levels within the greenhouse.


## Code Explanation
- **WiFi Setup**: The ESP32 connects to the specified WiFi network and starts a server to host the dashboard.
- **Sensor Readings**: Reads values from soil moisture, gas sensor, and LDR.

**Control Logic**:
- **Water Pump**: Turns on when soil moisture drops below moistureThreshold. 
- **Fan**: Activates when gas levels exceed gasThreshold.
- **LED**: Turns on when ambient light falls below ldrThreshold.
- **OLED Display**: Displays sensor data locally on an OLED display.
- **Web Dashboard**: Provides real-time data on moisture level, gas level, light intensity, and the status of the pump, fan, and LED.

## Web Dashboard
- **URL**: Use the IP address displayed in the Serial Monitor (e.g., http://192.168.1.xxx) to access the dashboard.
- **Features**:
- Displays current readings and statuses.
- Updates every 5 seconds with the latest data from the greenhouse.

## Future Enhancements
- **Data Logging**: Store historical data to analyze trends and make better-informed decisions.
- **Dynamic Threshold**: Allow users to adjust thresholds from the web dashboard.
- **Notifications**: Send alerts via email or mobile notifications if levels exceed critical thresholds.

## Troubleshooting
- **Wifi Connection Issue**:  Ensure the SSID and password are correct and that the ESP32 is within range of the WiFi router.
- **Incorrect Sensor Reading**:Verify sensor connections, and ensure proper power supply to each sensor.
- **Dashboard Not accissible**: Confirm the IP address of the ESP32 and ensure it’s correctly entered in the browser.


