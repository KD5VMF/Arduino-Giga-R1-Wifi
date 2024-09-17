#include <Arduino_GigaDisplay_GFX.h>
#include <WiFi.h>  // Use the standard WiFi library
#include <ArduinoJson.h>  // Include ArduinoJson for parsing JSON
#include "secrets.h"  // Include the secrets file

GigaDisplay_GFX tft;  // Initialize GIGA Display

WiFiClient client;

// Define colors
#define GC9A01A_CYAN    0x07FF
#define GC9A01A_RED     0xf800
#define GC9A01A_BLUE    0x001F
#define GC9A01A_GREEN   0x07E0
#define GC9A01A_MAGENTA 0xF81F
#define GC9A01A_WHITE   0xffff
#define GC9A01A_BLACK   0x0000
#define GC9A01A_YELLOW  0xFFE0

// ----- Customizable Text Color Based on Status ----- //
uint16_t textColor = GC9A01A_WHITE;  // Default text color (green = good)
uint16_t timestampColor = GC9A01A_CYAN;  // Color for the "Updated:" label and timestamp

const char* server = "api.weatherapi.com";
const String zipCode = "75081";  // Set the ZIP code to Richardson, TX (75081)
const String apiEndpoint = "/v1/current.json?key=" + String(WEATHER_API_KEY) + "&q=" + zipCode;  // Request weather for Dallas

// ----- Display and Text Settings ----- //
uint16_t bgColor = GC9A01A_BLUE;  // Background color (black)
unsigned long lastUpdateTimeMillis = 0;  // Track the time of the last update
const unsigned long updateInterval = 600000;  // Update interval (10 minutes)
const unsigned long wifiRetryInterval = 30000;  // Retry WiFi every 30 seconds if lost
String lastUpdateTime = "";  // To store the time of the last update (HH:MM)

// Track WiFi status
bool wifiConnected = false;
bool updatingWeather = false;

// Function prototypes
void connectToWiFi();
void fetchWeatherData();
void rotateDisplay();
void parseAndDisplayWeather(String payload);

void setup() {
  Serial.begin(115200);

  tft.begin();
  rotateDisplay();  // Rotate the display for landscape mode
  tft.fillScreen(bgColor);

  // Attempt to connect to WiFi initially
  connectToWiFi();
}

void loop() {
  // Handle WiFi connection state
  if (WiFi.status() != WL_CONNECTED) {
    wifiConnected = false;
    textColor = GC9A01A_RED;  // Set text to red if WiFi is lost
    Serial.println("WiFi Lost. Retrying...");
    connectToWiFi();
  }

  // Check if it's time to fetch new weather data
  if (wifiConnected && millis() - lastUpdateTimeMillis > updateInterval) {
    fetchWeatherData();  // Fetch new weather data every 10 minutes
  }

  delay(1000);  // Small delay between checks
}

// Function to connect to WiFi with retry logic
void connectToWiFi() {
  tft.setCursor(0, 0);
  tft.setTextColor(GC9A01A_YELLOW);  // Yellow text during connection attempts
  tft.setTextSize(3);
  tft.println("Connecting to WiFi...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Retry to connect to WiFi every 30 seconds if lost
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < wifiRetryInterval) {
    delay(500);
    Serial.println("Attempting to connect to WiFi...");
  }

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    textColor = GC9A01A_WHITE;  // Set text to green when WiFi is connected
    tft.fillScreen(bgColor);  // Clear the screen
    tft.setTextColor(textColor);
    tft.setTextSize(3);
    tft.println("WiFi Connected!");
    Serial.println("WiFi Connected!");

    // Fetch the weather data immediately after connecting
    fetchWeatherData();
  } else {
    wifiConnected = false;
    textColor = GC9A01A_RED;  // Set text to red if unable to connect
    Serial.println("Failed to connect to WiFi.");
    delay(wifiRetryInterval);  // Retry after 30 seconds
  }
}

// Function to fetch weather data
void fetchWeatherData() {
  if (!wifiConnected) {
    Serial.println("Cannot fetch weather data: No WiFi connection.");
    return;
  }

  updatingWeather = true;
  textColor = GC9A01A_YELLOW;  // Set text to yellow while updating
  tft.fillScreen(bgColor);
  tft.setCursor(0, 0);
  tft.setTextColor(textColor);
  tft.println("Updating Weather...");

  String url = "GET " + apiEndpoint + " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" +
               "Connection: close\r\n\r\n";

  if (client.connect(server, 80)) {
    Serial.println("Connected to weather server");
    client.print(url);

    // Read and parse the response
    String payload = "";
    bool jsonStarted = false;
    while (client.connected() || client.available()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {  // The line after the headers is an empty line (just "\r")
          jsonStarted = true;
        } else if (jsonStarted) {
          payload += line;  // Start adding lines after headers are skipped
        }
      }
    }
    client.stop();
    Serial.println("Weather data received");

    // Clean the response (remove any content before '{' and ensure it ends with '}')
    int jsonStartIndex = payload.indexOf('{');
    int jsonEndIndex = payload.lastIndexOf('}');
    if (jsonStartIndex >= 0 && jsonEndIndex >= 0) {
      payload = payload.substring(jsonStartIndex, jsonEndIndex + 1);
    } else {
      Serial.println("Error: Could not find JSON start or end");
      return;
    }

    // Debug: Print the cleaned JSON response to Serial Monitor
    Serial.println("Cleaned JSON Response:");
    Serial.println(payload);  // Print the cleaned JSON data

    // Parse and display the weather data
    parseAndDisplayWeather(payload);

    // Update the last update time
    lastUpdateTimeMillis = millis();
    updatingWeather = false;
    textColor = GC9A01A_WHITE;  // Set text to green after successful update
  } else {
    Serial.println("Connection to weather server failed.");
    textColor = GC9A01A_RED;  // Set text to red if update fails
  }
}

// Function to parse and display weather data neatly
void parseAndDisplayWeather(String payload) {
  // Parse weather data using ArduinoJson
  DynamicJsonDocument doc(4096);  // Create a JSON document with larger buffer
  DeserializationError error = deserializeJson(doc, payload);  // Deserialize the JSON data
  
  // Debug: Check for JSON parsing errors
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  String location = doc["location"]["name"] | "N/A";
  String region = doc["location"]["region"] | "N/A";
  String country = doc["location"]["country"] | "N/A";
  float tempF = doc["current"]["temp_f"] | 0.0;  // Use Fahrenheit
  String condition = doc["current"]["condition"]["text"] | "N/A";
  int humidity = doc["current"]["humidity"] | 0;
  float windMph = doc["current"]["wind_mph"] | 0.0;
  
  // New: Display Precipitation or Weather Alert
  float precip_mm = doc["current"]["precip_mm"] | 0.0;
  String weatherAlert = "None";  // Initialize as none
  if (precip_mm > 0) {
    weatherAlert = String(precip_mm) + " mm precipitation";  // Rain/Snow/etc.
  } else if (condition == "Tornado" || condition == "Hurricane") {
    weatherAlert = condition + " Alert!";
  }

  // Get the local time for the last update in HH:MM format
  String localTime = doc["location"]["localtime"] | "00:00";
  lastUpdateTime = localTime.substring(11, 16);  // Extract the time (HH:MM) from the localtime

  // Clear the screen and display the weather like news
  tft.fillScreen(bgColor);
  tft.setCursor(0, 0);
  tft.setTextColor(textColor);  // Use the customizable text color
  tft.setTextSize(3);  // Larger text for readability
  
  // Display weather report like news
  tft.println("Today's Weather Report:");
  tft.println("-----------------------");

  // Display the location at the top with the ZIP code (Richardson, TX)
  tft.println("Location: Richardson, TX (ZIP: " + zipCode + ")");
  tft.println("-----------------------");

  // Display temperature with small spacing between label and value
  tft.println("Temperature:");
  tft.setCursor(tft.getCursorX(), tft.getCursorY() + 15);  // Slightly reduce the space between label and value
  tft.println(String(tempF) + " F");  // Display in Fahrenheit
  tft.println("-----------------------");

  // Display condition with small spacing
  tft.println("Condition:");
  tft.setCursor(tft.getCursorX(), tft.getCursorY() + 15);  // Slightly reduce the space between label and value
  tft.println(condition);
  tft.println("-----------------------");

  // Display humidity with small spacing
  tft.println("Humidity:");
  tft.setCursor(tft.getCursorX(), tft.getCursorY() + 15);  // Slightly reduce the space between label and value
  tft.println(String(humidity) + "%");
  tft.println("-----------------------");

  // New: Display precipitation or weather alert
  tft.println("Weather Alert:");
  tft.setCursor(tft.getCursorX(), tft.getCursorY() + 15);
  tft.println(weatherAlert);  // Display precipitation or weather condition alert
  tft.println("-----------------------");

  // Display "Updated:" and the last updated time (HH:MM) in the top-right corner
  tft.setTextColor(timestampColor);  // Use the customizable timestamp color

  tft.setCursor(tft.width() - 100, 0);  // Position for the "Updated:" label
  tft.setTextSize(2);  // Slightly larger text for the "Updated:" label
  tft.println("Updated:");
  
  tft.setCursor(tft.width() - 100, 20);  // Position for the time (below "Updated:")
  tft.setTextSize(2);  // Same text size for the timestamp (HH:MM)
  tft.println(lastUpdateTime);  // Display the last update time
}

// Function to rotate the display
void rotateDisplay() {
  tft.setRotation(1);  // Set the display to landscape mode (1 = 90 degrees rotation)
}
