#include "../src/ipc/unix_socket.hpp"
#include <iostream>
#include <string>

void usage() {
    std::cout
        << "ProcessPilot CLI\n\n"
        << "Usage:\n"
        << "  processpilot-cli start <service-file>\n"
        << "  processpilot-cli stop\n"
        << "  processpilot-cli status\n"
        << "  processpilot-cli shutdown\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage();
        return 1;
    }

    UnixSocketClient client;

    if (!client.connectTo("/tmp/processpilot.sock")) {
        std::cerr << "Could not connect to ProcessPilot daemon.\n";
        std::cerr << "Start the daemon first.\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "start") {
        if (argc < 3) {
            std::cerr << "Missing service file.\n";
            return 1;
        }
        command += " " + std::string(argv[2]);
    }

    std::cout << client.request(command) << "\n";
    return 0;
}
