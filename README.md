# FlowerLogger

**FlowerLogger** is a simple keylogger tool designed by me (theflowerchain). It logs all keypresses made on the system, storing them in a txt log file. This tool can be used to monitor keyboard input, providing real-time logs with timestamps

## Overview

FlowerLogger employs a low-level Windows keyboard hook to capture keypresses globally, allowing it to function across all applications on the system. The tool is built with efficiency in mind, using minimal CPU resources while running in the background

- **Global Key Logging**: Logs keypresses from any application in real-time
- **Secure Logging**: Logs are stored in a `.txt` file with timestamps for traceability
- **Timestamped Logs**: Each logged key is timestamped, providing a precise record of keypress activities
- **Escape Key to Exit**: Pressing `ESC` will stop the logger and log the exit event

## Features

- Logs all key presses (alphanumeric and special keys)
- Timestamps for every log entry
- Lightweight background process
- Customizable logging destination (default is `logs.txt`)
- Displays logs both on the console and in the log file
- Easy to use with minimal configuration

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/FlowerKeyLogger.git
