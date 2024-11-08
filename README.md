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
