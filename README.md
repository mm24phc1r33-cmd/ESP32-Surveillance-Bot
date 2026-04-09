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
<img width="1093" height="680" alt="Screenshot 2026-04-09 120329" src="https://github.com/user-attachments/assets/ecbd9885-251d-40df-ba64-7fa490809403" />
<img width="1920" height="1080" alt="Screenshot 2026-04-09 130713" src="https://github.com/user-attachments/assets/804cd295-aa10-4b69-8888-83427fede998" />
<img width="1920" height="1080" alt="Screenshot 2026-04-09 130849" src="https://github.com/user-attachments/assets/4275a5ca-4664-4c7c-95aa-99ee244deacd" />
<img width="1920" height="1080" alt="Screenshot 2026-04-09 150811" src="https://github.com/user-attachments/assets/71833612-3d9d-43ef-9ddc-b41cfd09bf3e" />
<img width="729" height="726" alt="Screenshot 2026-04-09 152431" src="https://github.com/user-attachments/assets/a80b8d06-f489-423f-a3cd-99c6b375158d" />
<img width="684" height="574" alt="Screenshot 2026-04-09 152606" src="https://github.com/user-attachments/assets/44d3ba45-a9e3-45a4-8ba6-28bbdb499d5c" />
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/d5c138ed-3a9c-46e6-a313-f41117b33504" />
<img width="1145" height="903" alt="Screenshot 2026-04-09 181805" src="https://github.com/user-attachments/assets/18054583-90c2-4a6f-b829-75576ee0000d" />
<img width="1920" height="1080" alt="Screenshot 2026-04-09 182627" src="https://github.com/user-attachments/assets/1c2b147a-2b4f-461e-8f92-f3d677e85eda" />



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
<img width="1920" height="1080" alt="Screenshot 2026-04-08 182722" src="https://github.com/user-attachments/assets/558810be-2c2a-49c4-b332-7c3522b2c343" />
<img width="1920" height="1080" alt="Screenshot 2026-04-08 200231" src="https://github.com/user-attachments/assets/126740f2-352f-418e-a688-f50483abeb5b" />
<img width="1920" height="1080" alt="Screenshot 2026-04-08 202225" src="https://github.com/user-attachments/assets/12a87dbb-25a7-4ef5-bc41-4e0f316817f5" />
<img width="1920" height="1080" alt="Screenshot 2026-04-08 202836" src="https://github.com/user-attachments/assets/f1fb4b99-dac8-4dc3-8df7-959bee923972" />
<img width="1920" height="1080" alt="Screenshot 2026-04-08 202846" src="https://github.com/user-attachments/assets/8ad0ed98-b6c2-47e8-b4e3-d2b7e556b871" />

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

[(Add your GitHub repo link here)](https://github.com/mm24phc1r33-cmd/ESP32-Surveillance-Bot)

---
