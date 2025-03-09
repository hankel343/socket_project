# Socket Programming

I created this project to do something with the Raspberry Pi 4B I have had sitting around for three years. It is a simple client-server program. The server runs on the Raspberry Pi and sends a message to the connecting client.

## Features

- Server listens for incoming connections and executes commands sent by the client.
- Client connects to the server and sends commands to be executed.
- The server returns the output of the executed command to the client.

## Requirements

- Raspberry Pi 4B (or any other Linux-based system)
- GCC (GNU Compiler Collection)
- Make

## Setup

1. Clone the repository:
    ```sh
    git clone <repository_url>
    cd socket_project
    ```

2. Build the project using `make`:
    ```sh
    make
    ```

## Usage

### Running the Server

1. On the Raspberry Pi (or server machine), start the server:
    ```sh
    ./build/server
    ```

### Running the Client

1. On the client machine, run the client with the server's IP address and the command to be executed:
    ```sh
    ./build/client <server_ip> <command>
    ```

    For example, to run the `top -b -n 1` command on the server with IP `192.168.1.122`:
    ```sh
    ./build/client 192.168.1.122 "top -b -n 1"
    ```

## Example

1. Start the server on the Raspberry Pi:
    ```sh
    ./build/server
    ```

2. Run the client from another machine:
    ```sh
    ./build/client 192.168.1.122 "top -b -n 1"
    ```

3. The client will display the output of the `top` command executed on the server.

## License

This project is licensed under the MIT License.

MIT License

Copyright (c) 2025 Hankel Haldin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
