#include <Arduino_GigaDisplay_GFX.h>

GigaDisplay_GFX tft;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define MAX_MESSAGE_SIZE 512

// Buffer for incoming serial data
char serial_buffer[MAX_MESSAGE_SIZE];
uint8_t buffer_index = 0;
bool data_ready = false;

// Function prototypes
void setupDisplay();
void processSerialData();
void updateMetricsDisplay(float cpu, float ram, String ram_total, float disk, String storage_total, String net, String uptime, float temp, String ip);

void setup() {
  Serial.begin(115200);

  // Initialize the display
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(tft.color565(0, 0, 0)); // Set the background to black

  setupDisplay();
}

void loop() {
  // Process incoming serial data if ready
  if (data_ready) {
    processSerialData();
    data_ready = false;

    // Send acknowledgment back to the Python script
    Serial.println("ACK");
  }

  // Continuously read from Serial to fill the buffer
  while (Serial.available()) {
    char incoming_byte = Serial.read();

    // Start character '<'
    if (incoming_byte == '<') {
      buffer_index = 0; // Reset buffer index
    }
    // End character '>'
    else if (incoming_byte == '>') {
      serial_buffer[buffer_index] = '\0'; // Null-terminate the string
      data_ready = true;
    }
    // Store the incoming byte if there's space in the buffer
    else {
      if (buffer_index < MAX_MESSAGE_SIZE - 1) {
        serial_buffer[buffer_index++] = incoming_byte;
      }
    }
  }
}

// Function to set up the initial display with labels for system metrics
void setupDisplay() {
  tft.setTextColor(tft.color565(255, 255, 255)); // White text color
  tft.setTextSize(2);

  // Static Labels for different metrics
  tft.setCursor(10, 20);
  tft.print("CPU Usage:");

  tft.setCursor(10, 70);
  tft.print("RAM Usage:");

  tft.setCursor(10, 120);
  tft.print("RAM Total:");

  tft.setCursor(10, 170);
  tft.print("Disk Usage:");

  tft.setCursor(10, 220);
  tft.print("Storage Total:");

  tft.setCursor(10, 270);
  tft.print("Network Sent/Recv:");

  tft.setCursor(10, 320);
  tft.print("System Uptime:");

  tft.setCursor(10, 370);
  tft.print("CPU Temperature:");

  tft.setCursor(10, 420);
  tft.print("IP Address:");
}

// Function to process incoming serial data
void processSerialData() {
  String data = String(serial_buffer);

  // Ensure the data follows expected format before parsing
  if (data.startsWith("CPU:")) {
    int cpuIndex = data.indexOf("CPU:");
    int ramIndex = data.indexOf(",RAM:");
    int ramTotalIndex = data.indexOf(",RAM_TOTAL:");
    int diskIndex = data.indexOf(",DISK:");
    int storageTotalIndex = data.indexOf(",DISK_TOTAL:");
    int netIndex = data.indexOf(",NET:");
    int uptimeIndex = data.indexOf(",UPTIME:");
    int tempIndex = data.indexOf(",TEMP:");
    int ipIndex = data.indexOf(",IP:");

    if (cpuIndex != -1 && ramIndex != -1 && ramTotalIndex != -1 && diskIndex != -1 &&
        storageTotalIndex != -1 && netIndex != -1 && uptimeIndex != -1 &&
        tempIndex != -1 && ipIndex != -1) {
      
      float cpu = data.substring(cpuIndex + 4, ramIndex).toFloat();
      float ram = data.substring(ramIndex + 5, ramTotalIndex).toFloat();
      String ram_total = data.substring(ramTotalIndex + 11, diskIndex);
      float disk = data.substring(diskIndex + 6, storageTotalIndex).toFloat();
      String storage_total = data.substring(storageTotalIndex + 12, netIndex);
      String net = data.substring(netIndex + 5, uptimeIndex);
      String uptime = data.substring(uptimeIndex + 8, tempIndex);
      float temp = data.substring(tempIndex + 6, ipIndex).toFloat();
      String ip = data.substring(ipIndex + 4);

      // Update the display with parsed data
      updateMetricsDisplay(cpu, ram, ram_total, disk, storage_total, net, uptime, temp, ip);
    }
  }

  // Clear buffer for next data read
  memset(serial_buffer, 0, sizeof(serial_buffer));
}

// Function to update the display with system metrics
void updateMetricsDisplay(float cpu, float ram, String ram_total, float disk, String storage_total, String net, String uptime, float temp, String ip) {
  // Clear old values by filling in the background color
  tft.fillRect(300, 20, SCREEN_WIDTH - 320, 460, tft.color565(0, 0, 0));

  tft.setTextColor(tft.color565(255, 215, 0)); // Yellow text color for values
  tft.setTextSize(2);

  // Update each metric value with extra spacing to the right
  tft.setCursor(300, 20);
  tft.print(cpu, 1);
  tft.print(" %");

  tft.setCursor(300, 70);
  tft.print(ram, 1);
  tft.print(" %");

  tft.setCursor(300, 120);
  tft.print(ram_total);

  tft.setCursor(300, 170);
  tft.print(disk, 1);
  tft.print(" %");

  tft.setCursor(300, 220);
  tft.print(storage_total);

  tft.setCursor(300, 270);
  tft.print(net);

  tft.setCursor(300, 320);
  tft.print(uptime);

  tft.setCursor(300, 370);
  tft.print(temp, 1);
  tft.print(" C");

  tft.setCursor(300, 420);
  tft.print(ip);
}
