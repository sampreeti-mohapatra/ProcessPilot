#include "daemon.hpp"
#include "../logging/logger.hpp"
#include "../monitor/resource_monitor.hpp"
#include <iostream>
#include <sstream>

bool ProcessPilotDaemon::run() {
    Logger::info("ProcessPilot daemon starting");

    if (!server.start("/tmp/processpilot.sock")) {
        Logger::error("Could not start Unix socket server");
        return false;
    }

    Logger::info("Listening on /tmp/processpilot.sock");
    std::cout << "ProcessPilot daemon is running. Press Ctrl+C to stop.\n";

    while (true) {
        std::string request = server.receive();
        if (request.empty()) {
            continue;
        }

        std::istringstream input(request);
        std::string command;
        input >> command;

        if (command == "start") {
            std::string serviceFile;
            input >> serviceFile;

            if (serviceFile.empty()) {
                server.send("ERROR Missing service file");
                continue;
            }

            if (!config.load(serviceFile)) {
                server.send("ERROR Could not load configuration");
                continue;
            }

            std::string serviceName = config.get("Name");
            std::string processCommand = config.get("Command");

            if (processCommand.empty()) {
                server.send("ERROR Command missing in configuration");
                continue;
            }

            if (processManager.start(processCommand)) {
                server.send("OK STARTED " + serviceName +
                            " PID=" + std::to_string(processManager.getPid()));
            } else {
                server.send("ERROR Process could not be started");
            }
        }
        else if (command == "stop") {
            if (processManager.stop()) {
                server.send("OK STOPPED");
            } else {
                server.send("ERROR Process is not running");
            }
        }
        else if (command == "status") {
            if (processManager.isRunning()) {
                long pid = processManager.getPid();
                auto stats = ResourceMonitor::readProcess(pid);

                std::ostringstream response;
                response << "RUNNING PID=" << pid
                         << " MEMORY_KB=" << stats.memoryKb;

                server.send(response.str());
            } else {
                server.send("STOPPED");
            }
        }
        else if (command == "shutdown") {
            server.send("OK SHUTTING_DOWN");
            server.stop();
            break;
        }
        else {
            server.send("ERROR Unknown command");
        }
    }

    Logger::info("ProcessPilot daemon stopped");
    return true;
}
