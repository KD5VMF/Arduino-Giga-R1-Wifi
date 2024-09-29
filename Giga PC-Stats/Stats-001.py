import serial
import serial.tools.list_ports
import time
import socket

# Set debug mode: True for detailed logs, False for essential only
DEBUG_MODE = False

# List all available COM ports
ports = list(serial.tools.list_ports.comports())
print("Available ports:")
for i, port in enumerate(ports):
    print(f"{i + 1}: {port.device}")

# Ask user to select a port
selected_port_index = int(input("Select the port number to use: ")) - 1
if selected_port_index < 0 or selected_port_index >= len(ports):
    print("Invalid port selection.")
    exit()

SERIAL_PORT = ports[selected_port_index].device
BAUD_RATE = 115200

# Attempt to open the selected port
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Give time for Arduino to reset
    if DEBUG_MODE:
        print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
except serial.SerialException as e:
    print(f"Could not open port {SERIAL_PORT}: {e}")
    exit()

# Example loop to send data to the Arduino
while True:
    # Get the local IP address
    ip_address = socket.gethostbyname(socket.gethostname())

    # Example additional data
    ram_total = "16GB"  # Replace with actual system query if possible
    storage_total = "512GB"  # Replace with actual system query if possible

    # Example data format with additional fields
    data_to_send = f"<CPU:20.3,RAM:45.0,RAM_TOTAL:{ram_total},DISK:67.5,DISK_TOTAL:{storage_total},NET:120MB/300MB,UPTIME:2h45m,TEMP:55.0,IP:{ip_address}>"

    # Debug: print the data being sent
    if DEBUG_MODE:
        print(f"Sending data: {data_to_send}")

    # Send data to Arduino
    ser.write(data_to_send.encode())

    # Wait for acknowledgment from Arduino
    ack = ser.readline().decode().strip()
    if ack == "ACK":
        if DEBUG_MODE:
            print("Data acknowledged by Arduino, sending next packet...")
    else:
        if DEBUG_MODE:
            print("No acknowledgment received, retrying...")
        time.sleep(1)

    time.sleep(2)  # Send data every 2 seconds
