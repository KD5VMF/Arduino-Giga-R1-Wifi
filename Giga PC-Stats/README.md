
# System Monitoring Dashboard with Arduino and Python

This project is a **System Monitoring Dashboard** that displays real-time data from your computer on an Arduino-powered display. The dashboard shows metrics such as **CPU usage**, **RAM usage**, **Disk usage**, **IP address**, and other important system information.

## 📋 Features

- **Real-Time Monitoring**: Display key metrics of your system including CPU, RAM, and Disk usage.
- **Arduino Giga Display**: Data is shown on an LCD screen connected to an Arduino Giga using the `GigaDisplay_GFX` library.
- **Python Integration**: A Python script gathers system data and sends it to the Arduino via a serial connection.
- **Customizable Debugging**: Enable or disable debug information to view detailed or minimal information in the console.
- **Clear Visualization**: Metrics are well organized and aligned for easy readability.

## 🛠️ Hardware Requirements

- **Arduino Giga** with a connected LCD Display.
- **USB Cable** to connect the Arduino to the PC.
- **Computer Running Python** to gather the system metrics.

## 📦 Software Requirements

- **Arduino IDE**: Used to upload the Arduino code to your Arduino board.
- **Python 3.x**: Required for the script to gather system information.
  - **Libraries**: `serial`, `psutil`, `socket`.
  
  To install the Python dependencies:
  ```sh
  pip install pyserial psutil
  ```

## 📂 File Structure

```
- README.md
- arduino/
  - system_monitor.ino       # Arduino code for displaying system information
- python/
  - stats-001.py             # Python script for collecting and sending data
```

## 🚀 Getting Started

### 1. Clone the Repository

```sh
git clone https://github.com/yourusername/system-monitoring-dashboard.git
cd system-monitoring-dashboard
```

### 2. Arduino Setup

- Open the Arduino IDE.
- Navigate to `arduino/system_monitor.ino`.
- Connect your Arduino Giga to your computer and upload the code to the board.

### 3. Python Setup

- Navigate to the `python/` directory.
- Open `stats-001.py` in your favorite text editor and configure the following:
  - **Serial Port**: The script will prompt you to select the correct serial port for communication.
  - **Debug Mode**: Set `DEBUG_MODE` to `True` for detailed output during development or `False` for a minimal output.

### 4. Run the Python Script

To run the Python script and start gathering data:

```sh
python stats-001.py
```

### 5. Observing Data on the Arduino Display

Once both the Arduino sketch is running and the Python script has started, you should see metrics displayed on the LCD connected to your Arduino Giga.

## ⚙️ Debug Mode

To enable or disable debug messages, modify the `DEBUG_MODE` variable in `stats-001.py`:

- **Enable Debugging**: Set `DEBUG_MODE = True` to get detailed output.
- **Disable Debugging**: Set `DEBUG_MODE = False` for regular operation to avoid unnecessary console clutter.

## 📊 Metrics Displayed

- **CPU Usage (%)**: Displays the current percentage of CPU usage.
- **RAM Usage (%)**: Displays the current percentage of RAM usage.
- **RAM Total**: Displays the total RAM available in the system.
- **Disk Usage (%)**: Displays the current percentage of disk usage.
- **Storage Total**: Displays the total disk capacity.
- **Network Activity**: Shows data sent and received (e.g., "120MB/300MB").
- **System Uptime**: Displays the current system uptime in hours and minutes.
- **CPU Temperature (°C)**: Shows the CPU temperature.
- **IP Address**: Displays the current IP address of the system.

## 🖼️ Screenshots

### Example Display
![System Monitoring Dashboard Display](path/to/your/screenshot.jpg)

## 📝 Troubleshooting

### Serial Port Issues

- Ensure the correct serial port is selected in the Python script.
- Ensure that the **Arduino Giga** is properly connected to the USB port.

### Display Issues

- If no data is displayed or if there are overlapping values, ensure that the Arduino code and Python script are running in sync.
- Make sure you have installed all necessary libraries in Arduino IDE (`Arduino_GigaDisplay_GFX`).

## 🤝 Contributing

Contributions are welcome! If you'd like to help improve this project, please follow these steps:

1. Fork the repository.
2. Create a new feature branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a pull request.

## 📜 License

This project is open-source and available under the **MIT License**. Feel free to use, modify, and distribute it as you like.

Written by ChatGPT 4o---

Thank you for checking out this project! If you found it helpful, please consider starring ⭐ the repository to show your support.
