# Real-Time Operating System (RTOS) for STM32

## Project Overview
This repository contains the code and resources necessary to build your own Real-Time Operating System (RTOS) on an STM32 microcontroller. The implementation focuses on core features of an RTOS, demonstrating task scheduling, inter-task communication, and resource management.

## Getting Started

### Prerequisites
To deploy this project onto your STM32 microcontroller, you will need:

- An STM32 microcontroller (e.g., STM32F401FE).
- STM32CubeIDE (available for download from the STMicroelectronics website).
- A USB ST-Link programmer or any compatible programmer for flashing the firmware.

### Cloning the Repository
To clone this repository, open your terminal and run:

```bash
git clone https://github.com/ypatel789/simpleRTOS.git
```
## Setting Up the Project

1. Navigate to the Project Directory

```bash
cd your_path/simpleRTOS
```

2. Open STM32CubeIDE: Launch the IDE and import the project:
    - Go to `File` -> `Import`
    - Under `General` -> `Existing Projects into Workspace` and click `Next`
    - Choose the root directory of the cloned repository and import the project

3. Build the Project:
    - Click on the build icon after selecting the project you wish to build
    - Or go to `Project` -> `Build All`