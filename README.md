
# Earthquake Sensor V1

## Overview
The Earthquake Sensor V1 project aims to develop a low-cost, simple device for monitoring vibrations in structures. By detecting early signs of instability, this system provides a proactive solution for assessing structural health where affordable options are currently lacking.

## Motivation
Existing structural monitoring solutions are often expensive or overly complex, making them inaccessible for widespread use. Our goal is to create a straightforward and cost-effective device that leverages affordable hardware and open-source software to:
- Monitor real-time vibrational data.
- Identify anomalous vibrations that may indicate potential structural instability.
- Provide an accessible means of maintaining structural safety.

## Hardware Components
- **STM32 G474RE Board:** The main microcontroller platform for processing sensor data.
- **Accelerometer:** Used to measure vibrations in the monitored structure. (The specific model can be adapted based on availability and requirements.)

## Features
- **Real-time Vibration Monitoring:** Constantly samples vibrational data to detect potential issues.
- **Early Warning System:** Alerts when the structure shows signs of instability.
- **Low-Cost & Accessible:** Designed to be cost-effective and easy to deploy in various environments.

## Project Structure
```
earthquak_sensv1/
├── doc/              # Documentation and design notes
├── inc/              # Header files and configuration definitions
├── src/              # Source code (including main.c)
└── README.md         # Project overview and instructions
```

## Getting Started

### Prerequisites
- **STM32CubeIDE:** Ensure you have the latest version installed.
- **Hardware:** STM32 G474RE board and the selected accelerometer sensor.
- **ST-Link or Similar Debugger:** For programming and debugging the board.

### Setup Instructions
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/earthquak_sensv1.git
   ```
2. **Import the Project in STM32CubeIDE:**
   - Open STM32CubeIDE.
   - Select **File → Import → Existing Projects into Workspace**.
   - Browse to the cloned repository and import the project.
3. **Configure the Hardware:**
   - Use the integrated CubeMX tool in STM32CubeIDE to set up the pin configurations, clocks, and peripherals (e.g., ADC for the accelerometer).
4. **Build the Project:**
   - Click the build (hammer) icon to compile the project.
5. **Flash the Firmware:**
   - Connect your STM32 G474RE board via ST-Link.
   - Right-click the project and select **Debug As → STM32 Cortex-M C/C++ Application** to program and start debugging the firmware.

## Usage
Once the device is programmed and running:
- **Monitoring:** The system will continuously capture vibrational data from the accelerometer.
- **Alerts:** Software algorithms analyze the data to detect abnormal vibrations that may indicate structural issues.
- **Data Output:** The results can be monitored via serial output or other communication interfaces, as configured in your project.

## Contributing
Contributions are welcome! If you have ideas for improvements or find issues, please:
- Fork the repository.
- Create a feature branch.
- Submit a pull request with detailed explanations.

## License
This project is open-source and available under the [MIT License](LICENSE).

## Contact
For more information or any inquiries, please reach out to:
- **Your Name/Team Name**
- **Email:** [your.email@example.com]

```

Feel free to customize this README to better suit your project's specific needs and details!
