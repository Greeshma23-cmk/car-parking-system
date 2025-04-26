# Reverse Car Parking Assistance System

This project is an Embedded C-based Reverse Car Parking Assistance System developed using the CAN (Controller Area Network) protocol.  
It is designed to assist drivers by detecting obstacles while reversing the vehicle and alerting them.

## Features
- Obstacle detection using sensors.
- CAN Protocol communication between ECUs.
- Audio and visual alerts for proximity warning.
- Real-time data transmission.

## Tools & Technologies Used
- Embedded C
- CAN Protocol
- Microcontroller (example: STM32 / LPC2148 / any MCU)
- Sensor Modules (example: Ultrasonic sensors)

## Project Structure
- main.c - Main application code
- NODEArev_gear.c - CAN protocol communication handler for node a
- NODEBREV.c - handler for node b
- README.md - project documentation
## How to Run
1. Flash the code into the microcontroller.
2. Connect sensor modules and buzzer/display.
3. Simulate or test obstacle detection while reversing.

## Future Improvements
- Integrate camera-based detection.
- Add Bluetooth/Wi-Fi connectivity for alerts on mobile devices.
- Implement adaptive learning for different vehicle sizes.

## Author
Gollapalli Greeshma
## Project Link
- [GitHub Repository Link]()

