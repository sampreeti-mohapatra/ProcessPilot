cmake_minimum_required(VERSION 3.10)

project(ProcessPilot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

add_executable(processpilot
    src/main.cpp
    src/daemon/daemon.cpp
    src/process/process_manager.cpp
    src/config/config_parser.cpp
    src/monitor/resource_monitor.cpp
    src/dependency/dependency_graph.cpp
    src/ipc/unix_socket.cpp
    src/logging/logger.cpp
)

add_executable(processpilot-cli
    cli/processpilot_cli.cpp
    src/ipc/unix_socket.cpp
)

add_executable(process_tests
    tests/process_tests.cpp
    src/process/process_manager.cpp
)

add_executable(config_tests
    tests/config_tests.cpp
    src/config/config_parser.cpp
)

add_executable(dependency_tests
    tests/dependency_tests.cpp
    src/dependency/dependency_graph.cpp
)
