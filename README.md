# ESP32-Surveillance-Bot
#  ESP32-Based Smart Surveillance Robot (Embedded Systems Project)

##  Overview

This project presents the design and development of an ESP32-based smart robotic system capable of motion control, laser aiming, video streaming, GPS tracking, and secure communication. The system integrates multiple hardware modules with embedded firmware to create a scalable and real-time surveillance platform.

The robot operates using differential drive motors, supports remote monitoring via Wi-Fi, and ensures secure access using BLE authentication.

---

##  Objectives

The main objective of this project is to design a complete embedded system including:

* Real-time motor control using PWM
* Laser aiming using servo motor
* GPS-based location tracking
* Wireless communication via Wi-Fi
* Secure access using BLE authentication
* Camera-based monitoring (simulated/extendable)

---

##  System Architecture

The system consists of the following major blocks:

* ESP32 microcontroller (central controller)
* Motor driver (TB6612FNG)
* DC motors for movement
* Servo motor for laser aiming
* GPS module (UART-based)
* Wi-Fi communication module (ESP32 inbuilt)
* BLE authentication system
* Power regulation using AMS1117

---

##  Hardware Components

* ESP32-WROOM-32
* TB6612FNG Motor Driver
* 2 × DC Motors
* 1 × Servo Motor
* GPS Module (NEO-6M or similar)
* AMS1117 Voltage Regulator (3.3V)
* Capacitors (10µF)
* Resistors (220Ω, 10kΩ)
* Push Buttons (Reset & Boot)
* LED Indicator
* Connectors (Pin Headers & Terminal Blocks)

---

##  PCB Design

A custom PCB was designed using KiCad with the following considerations:

* Proper component placement (power, control, communication separation)
* Wide traces for motor power lines
* Ground plane for noise reduction
* Keep-out zone for ESP32 antenna
* Decoupling capacitors near power pins
* Separate connectors for GPS, UART, motors, and servo

---

##  Firmware Features

The firmware is developed using Arduino IDE for ESP32 and includes:

* Motor control (forward, backward, left, right)
* PWM-based speed control
* Servo control for laser positioning
* GPS data parsing (latitude & longitude)
* Wi-Fi connectivity and server communication
* BLE-based authentication (simulated)
* Safety mechanism (motor stop on disconnection)

---

##  Communication

* Wi-Fi: Used for data transmission and remote monitoring
* BLE: Used for authentication before granting control
* UART: Used for GPS communication

---

##  Testing & Output

The system was tested using Serial Monitor:

* Verified motor control commands
* GPS data updated every 5 seconds
* Simulated authentication process
* Safety stop triggered on connection loss

---

##  Safety Features

* Motors automatically stop on Wi-Fi disconnect
* Controlled access using BLE authentication
* Power regulation to avoid voltage fluctuations

---

##  Project Structure

```
ESP32_Surveillance_Bot/
│── firmware/
│   └── main.ino
│
│── hardware/
│   ├── schematic.kicad_sch
│   ├── pcb_layout.kicad_pcb
│   ├── gerber_files/
│
│── docs/
│   └── images/
│
│── README.md
```

---

##  Future Improvements

* Real-time camera streaming using ESP32-CAM
* Mobile app integration
* Autonomous navigation using sensors
* AI-based object detection

---

##  Conclusion

This project demonstrates the integration of embedded systems, PCB design, and communication protocols into a single functional robotic platform. It showcases practical implementation skills in hardware-software co-design and real-time system development.

---

## Author

**Monika**
M.Sc. Tech Engineering Physics (Electronics)
NIT Warangal

---

## 🔗 GitHub

(Add your GitHub repo link here)

---
