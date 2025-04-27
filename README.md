# 🚗 Reverse Car Parking Assistance System

This project is an **Embedded C-based Reverse Car Parking Assistance System** developed using the **CAN (Controller Area Network) protocol**.  
It is designed to assist drivers by detecting obstacles when reversing the vehicle and providing timely alerts through audio and visual signals.

---

## ✨ Features
- **Obstacle Detection**: Real-time detection of nearby obstacles using sensors.
- **CAN Communication**: Robust communication between different ECUs via CAN protocol.
- **Audio & Visual Alerts**: Warnings provided through buzzer and display systems.
- **Real-Time Data Transmission**: Immediate response and communication between modules.

---

## 🛠 Tools & Technologies Used
- **Programming Language**: Embedded C
- **Communication Protocol**: CAN (Controller Area Network)
- **Microcontrollers**: Example - STM32 / LPC2148 / any suitable MCU
- **Sensor Modules**: Example - Ultrasonic sensors (like HC-SR05)

---

## 📁 Project Structure

| File | Description |
|:-----|:------------|
| **main.c** | Main application logic for the system. |
| **can_header.h** | Contains function declarations for CAN operations. |
| **delay.c** | Includes delay functions for timing management. |
| **uart0_driver.c** | UART driver; handles communication from HC-SR05 sensor to MCU via UART. |
| **ext_intrp.c** | Handles external interrupt triggered by a switch (reverse gear simulation) and requests data from sensors. |
| **README.md** | Project documentation and usage instructions. |

---

## 🚀 How to Run
1. Flash the compiled code into the target microcontroller.
2. Connect the ultrasonic sensor modules and buzzer/display.
3. Simulate reversing by triggering the external interrupt (e.g., pressing a switch).
4. Observe obstacle detection through buzzer sounds and/or display warnings.

---

## 🌟 Future Improvements
- Integration of **camera-based obstacle detection** for enhanced accuracy.
- Addition of **Bluetooth/Wi-Fi connectivity** to send alerts directly to mobile devices.
- Implementation of **adaptive learning algorithms** for different vehicle sizes and environments.

---

## 👩‍💻 Author
**Gollapalli Greeshma**

---

## 🔗 Project Link
- [GitHub Repository Link](#) *(https://github.com/Greeshma23-cmk/car-parking-system)*

---
