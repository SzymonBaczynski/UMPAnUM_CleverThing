# Embedded code for ESP32 - CleverThing device.

This repository contains the code written in for the ESP32 microcontroller. The code is designed to run on an ESP32 development board and perform communication with the MQTT server. 

## Getting Started

To use this code, you'll need the following prerequisites:

1. ESP32 Development Board
2. PlatformIO installed on your development machine

## Installation

1. Clone this repository to your local machine using the following command: `git clone https://github.com/SzymonBaczynski/UMPAnUM_CleverThing.git`

2. Open the PlatformIO project in your preferred code editor.

3. Connect your ESP32 development board to your computer using a USB cable.

4. Build and upload the code to your ESP32 by clicking on the "Upload" button in the PlatformIO interface.

## Project Structure

The main code files and directories in this repository are organized as follows:

- `src/`: This directory contains the main source code files for the ESP32 project.
- `platformio.ini`: This file is the PlatformIO project configuration, where you can specify the board type, upload settings, and other project-specific configurations.

## Usage

To run code you will need to put credentials inside `src/credentials.h` file:
```
#ifndef credentials_h
#define credentials_h

#define WIFI_PASS "***"
#define WIFI_SSID "***"

#define BROKER_PASS "***"
#define BROKER_USER "CleverUser"

#endif 
```
