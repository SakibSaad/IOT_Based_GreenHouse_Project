#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define pins
#define SOIL_SENSOR_PIN 34   // Analog input pin for soil moisture sensor
#define PUMP_RELAY_PIN 4     // Relay for water pump
#define GAS_SENSOR_PIN 35    // Analog input pin for gas sensor
#define FAN_RELAY_PIN 14     // Relay for gas control fans
#define LDR_PIN 33           // Analog pin for LDR
#define LED_PIN 5            // Digital pin connected to LED

// WiFi credentials
const char* ssid = "OPPO A53";
const char* password = "11111111";

// OLED display width and height, typically 128x64
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create an OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

WiFiServer server(80);

int moistureThreshold = 50;  // Moisture level threshold (percentage)
int gasThreshold = 1500;     // Gas level threshold
int ldrThreshold = 2000;     // Updated threshold for LDR

void setup() {
  Serial.begin(115200);

  // Initialize WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  Serial.println(WiFi.localIP());

  // Start server
  server.begin();

  // Initialize pins
  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(PUMP_RELAY_PIN, OUTPUT);
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(FAN_RELAY_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Ensure relays and LED are off initially
  digitalWrite(PUMP_RELAY_PIN, LOW);
  digitalWrite(FAN_RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println("SSD1306 allocation failed");
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  // Show startup message
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Smart Greenhouse");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // Read sensor values
  int soilSensorValue = analogRead(SOIL_SENSOR_PIN);
  int moistureLevel = map(soilSensorValue, 0, 4095, 0, 100);
  int gasLevel = analogRead(GAS_SENSOR_PIN);
  int ldrValue = analogRead(LDR_PIN);

  // Control water pump based on soil moisture
  digitalWrite(PUMP_RELAY_PIN, moistureLevel < moistureThreshold ? HIGH : LOW);

  // Control fan based on gas level
  digitalWrite(FAN_RELAY_PIN, gasLevel > gasThreshold ? LOW : HIGH);

  // Control LED based on LDR reading (updated logic)
  digitalWrite(LED_PIN, ldrValue >= ldrThreshold ? HIGH : LOW);

  // Display data on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Moisture: ");
  display.print(moistureLevel);
  display.print("%");
  display.setCursor(0, 10);
  display.print("Gas Level: ");
  display.print(gasLevel);
  display.setCursor(0, 20);
  display.print("LDR: ");
  display.print(ldrValue);
  display.setCursor(0, 30);
  display.print((moistureLevel < moistureThreshold) ? "Pump: OFF" : "Pump: ON");
  display.setCursor(0, 40);
  display.print((gasLevel > gasThreshold) ? "Fans: ON" : "Fans: OFF");
  display.setCursor(0, 50);
  display.print((ldrValue < ldrThreshold) ? "LED: OFF" : "LED: ON");
  display.display();

  // Handle client requests
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/data") >= 0) {
      // Serve sensor data as JSON
      String json = "{";
      json += "\"moisture\": " + String(moistureLevel) + ",";
      json += "\"gas\": " + String(gasLevel) + ",";
      json += "\"ldr\": " + String(ldrValue) + ",";
      json += "\"pump\": \"" + String(digitalRead(PUMP_RELAY_PIN) == HIGH ? "OFF" : "ON") + "\",";
      json += "\"fans\": \"" + String(digitalRead(FAN_RELAY_PIN) == HIGH ? "OFF" : "ON") + "\",";
      json += "\"led\": \"" + String(digitalRead(LED_PIN) == HIGH ? "ON" : "OFF") + "\"";
      json += "}";

      client.print("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
      client.print(json);
    } else {
      // Serve the HTML page
       String html = 
      "<!DOCTYPE html>"
      "<html lang='en'>"
      "<head>"
      "<meta charset='UTF-8'>"
      "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
      "<title>Smart Greenhouse Dashboard</title>"
      "<style>"
      "body { font-family: Arial, sans-serif; background-color: #f0f4f8; margin: 0; padding: 0; }"
      "h1 { background-color: #4CAF50; color: white; text-align: center; padding: 10px 0; margin: 0; }"
      ".container { max-width: 600px; margin: 30px auto; padding: 20px; background-color: white; "
      "box-shadow: 0 0 10px rgba(0,0,0,0.1); border-radius: 8px; }"
      ".card { margin: 15px 0; padding: 15px; border-radius: 8px; background-color: #e8f5e9; "
      "box-shadow: 0 2px 5px rgba(0,0,0,0.1); }"
      ".card h2 { margin: 0; font-size: 18px; color: #388e3c; }"
      ".status { font-size: 16px; color: #333; margin-top: 5px; }"
      ".footer { text-align: center; margin-top: 20px; font-size: 12px; color: #777; }"
      "</style>"
      "</head>"
      "<body>"
      "<h1>Smart Greenhouse Dashboard</h1>"
      "<div class='container'>"
      "<div class='card'><h2>Soil Moisture</h2><p class='status'><span id='moisture'>--</span>%</p></div>"
      "<div class='card'><h2>Gas Level</h2><p class='status'><span id='gas'>--</span></p></div>"
      "<div class='card'><h2>Light Level</h2><p class='status'><span id='light'>--</span></p></div>"
      "<div class='card'><h2>Pump Status</h2><p class='status'><span id='pump'>--</span></p></div>"
      "<div class='card'><h2>Fans Status</h2><p class='status'><span id='fans'>--</span></p></div>"
      "<div class='card'><h2>LED Status</h2><p class='status'><span id='led'>--</span></p></div>"
      "<div class='footer'>Updated every 5 seconds</div>"
      "</div>"
      "<script>"
      "function fetchData() {"
      "  fetch('/data').then(response => response.json()).then(data => {"
      "    document.getElementById('moisture').textContent = data.moisture;"
      "    document.getElementById('gas').textContent = data.gas;"
      "    document.getElementById('light').textContent = data.ldr;"
      "    document.getElementById('pump').textContent = data.pump;"
      "    document.getElementById('fans').textContent = data.fans;"
      "    document.getElementById('led').textContent = data.led;"
      "  });"
      "}"
      "setInterval(fetchData, 5000);"
      "</script>"
      "</body></html>";

      client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
      client.print(html);
    }
    client.stop();
  }

  delay(5000);  // Wait 5 seconds before next reading
}