# ProcessPilot

## Linux Service Manager and Process Supervisor

ProcessPilot is a lightweight Linux service manager and process supervisor written in C++.

It demonstrates core Linux system-programming concepts including process creation,
process termination, configuration parsing, Unix domain socket IPC, resource
monitoring, dependency management and logging.

## Features

- Start and stop Linux processes
- Service configuration files
- Process status checking
- Basic memory monitoring through `/proc`
- Unix domain socket communication
- Service dependency graph
- Timestamped logging
- Command-line interface
- Basic tests
- CMake build system

## Project Structure

```text
ProcessPilot/
├── src/
│   ├── main.cpp
│   ├── daemon/
│   ├── process/
│   ├── config/
│   ├── monitor/
│   ├── dependency/
│   ├── ipc/
│   └── logging/
├── cli/
├── tests/
├── configs/
├── docs/
├── CMakeLists.txt
└── README.md
```

## Build

Linux or WSL is required.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Run

From the project root:

```bash
./build/processpilot
```

In another terminal:

```bash
./build/processpilot-cli start configs/demo.service
./build/processpilot-cli status
./build/processpilot-cli stop
```

To stop the daemon:

```bash
./build/processpilot-cli shutdown
```

## Example Service

`configs/demo.service`:

```ini
[Service]
Name=demo
Command=/bin/sleep 60
Restart=always
```

## Tests

Build the test executables and run:

```bash
./build/process_tests
./build/config_tests
./build/dependency_tests
```

## Technologies

- C++17
- Linux/POSIX APIs
- CMake
- Unix Domain Sockets
- `/proc` filesystem

## Note

This is an educational lightweight service manager. It is not intended to replace
production service managers such as systemd.
