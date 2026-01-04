# ESP32-S3-W5500-TCP-Client-to-Hercules-Server
ESP32 TCP client example using W5500 Ethernet module. Communicates with Hercules TCP Server to send and receive data over Ethernet.

# ESP32 W5500 TCP Client – Hercules Server Test

This project demonstrates TCP communication over Ethernet using ESP32 + W5500.
The ESP32 operates as a TCP client and communicates with a Hercules TCP Server running on Windows.

# Finding the W5500 IP Address on Windows (Hercules Test)

After connecting the Ethernet cable to the W5500 module and powering the ESP32, the device obtains an IP address from the local network.

To find the network information on Windows:

Open Command Prompt (CMD) on Windows

Run the following command:

ipconfig


Identify the active Ethernet adapter

Check the IPv4 Address in the same subnet as your PC

Use this IP address in Hercules TCP Server for communication

The W5500 IP address becomes available after the Ethernet cable is connected and the link is established.

# Hercules TCP Server Configuration

Protocol: TCP Server

Port: (must match the port defined in the ESP32 code)

Data Format: ASCII or HEX

Connection Mode: Listen / Open

Once connected, data exchange between Hercules and ESP32 is established over Ethernet.

# PlatformIO Configuration for ESP32-S3

When using PlatformIO with an ESP32-S3 board, the following configuration must be added to platformio.ini:

[env:esp32-s3-devkitc-1]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino
monitor_speed = 115200
board_upload.flash_size = 4MB
board_build.partitions = default.csv
build_flags =
  -DARDUINO_USB_CDC_ON_BOOT=1
  -DBOARD_HAS_PSRAM


These parameters ensure proper USB CDC behavior, serial communication, and PSRAM support for ESP32-S3 boards.
