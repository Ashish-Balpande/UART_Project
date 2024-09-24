import serial
import time

# Configure the serial connection
port = 'COM6'  # For Windows
# port = '/dev/ttyUSB0'  # For Linux
baudrate = 9600

try:
    with serial.Serial(port, baudrate, timeout=1) as ser:
        print(f"Connected to {port} at {baudrate} baud.")
        time.sleep(2)  # Wait for the connection to establish

        while True:
            if ser.in_waiting > 0:  # Check if there is data available
                data = ser.readline().decode('utf-8').rstrip()  # Read a line and decode
                print(f"Received: {data}")

except serial.SerialException as e:
    print(f"Error: {e}")

except KeyboardInterrupt:
    print("Program interrupted.")
