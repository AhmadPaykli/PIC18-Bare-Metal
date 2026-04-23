# PIC18-Bare-Metal
Bare metal C development for PIC18 microcontrollers.
# PIC18 Bare-Metal Drivers & Layered Architecture

## Overview
This repository contains a fully structured, bare-metal embedded C project for the PIC18F4620 microcontroller. The project is built from scratch without the use of external HAL code generators, demonstrating a deep understanding of microcontroller architecture, registers, and memory management.

## Software Architecture
The firmware is designed using a professional **Layered Architecture** approach, ensuring modularity, scalability, and code reusability. It is divided into the following key layers:

1. **MCAL (Microcontroller Abstraction Layer):**
   Directly interacts with the PIC18 hardware registers. Includes custom drivers for:
   - GPIO (General Purpose Input/Output)
   - ADC (Analog-to-Digital Converter)
   - Interrupts (External and Internal)
   - Timer0, Timer1, Timer2, and Timer3

2. **ECU (Electronic Control Unit) Layer:**
   Interfaces with external hardware components using the MCAL. Includes drivers for:
   - LEDs and Push Buttons
   - Relays
   - 7-Segment Displays
   - Character LCDs
   - Keypads
   - DC Motors

3. **Application Layer:**
   Contains the main application logic (`application.c` and `application.h`) utilizing the underlying ECU and MCAL functions.

## Tools & IDE
- **IDE:** MPLAB X IDE
- **Compiler:** XC8 Compiler

## Folder Structure
- `MCAL_Layer/`: Bare-metal hardware drivers and standard configuration files (`mcal_std_types.h`, `compiler.h`, etc.).
- `ECU_Layer/`: External module drivers and unified initialization routines.
- `application.c` / `application.h`: Main execution files.

---
*Developed by Ahmad Paykli - Electrical and Electronics Engineering.*
