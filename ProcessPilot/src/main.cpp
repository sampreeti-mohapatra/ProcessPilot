#include "daemon/daemon.hpp"
#include <iostream>

int main() {
    std::cout << "Starting ProcessPilot daemon...\n";
    ProcessPilotDaemon daemon;
    return daemon.run() ? 0 : 1;
}
