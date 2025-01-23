# Minitalk

## Description
The Minitalk project involves creating a simple communication protocol between two programs using UNIX signals. It consists of two components: 
- a **server** (receiver)
- and a **client** (sender).
The concept of using UNIX signals for inter-process communication is inspired by classic low-level systems programming tasks.

To help me understand better bitwise operations and their potential, I wrote an additional library LIBSORT whose functions I used
to solve this task.

**Technologies Used:**
- C
- UNIX Signals

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [Acknowledgments](#acknowledgments)

## Installation
To test this project locally:

1. Clone this repository:
   ```bash
   git clone https://github.com/pepper/minitalk.git
2. Navigate into the project directory:
   ```bash
   cd Minitalk
3. Compile the server and client by running:
    ```bash
    make

## Usage
1. **Server:**
   - Open the first terminal.
   - Run the `./server` program. Its PID (SERVER_PID) will be displayed.
   - The server will display the received message in the terminal once it's fully transmitted.
   
2. **Client:**
   - Open the second terminal.
   - Run the `./client <SERVER_PID> <MESSAGE>`.
   - The message (any string) is sent to the server as a sequence of signals (binary data).

**Example:**

```bash
# Server Terminal
./server
Process ID (PID): 12345

# Client Terminal
./client 12345 "Hello 42 Nice"
```

## Features
The Minitalk project achieves communication employing the following mechanisms and protocols.
The server listens for signals (`SIGUSR1` and `SIGUSR2`) using sigaction. Each signal corresponds to a binary bit (SIGUSR1 for 0, SIGUSR2 for 1).
Characters are transmitted one at a time as binary data. Once 8 bits (1 byte) have been received, the binary string is converted into the corresponding character.
To prevent buffer overflow, the client waits for a signal from the server (acknowledging the reception of the previous bit) before sending the next one.
A small delay (usleep) is used between signal transmissions to avoid overwhelming the server.

## Contributing
This project is pretty straightforward, but if you have suggestions for improvements, bug fixes, or interesting features, feel free to contribute.

### How to Contribute:
- Fork the repository.
- Create a new branch (git checkout -b feature-branch).
- Make your changes and commit them (git commit -am 'Add new feature').
- Push to your branch (git push origin feature-branch).
- Open a pull request.

## Acknowledgments
Thanks to the 42 Nice community!
