#include "resource_monitor.hpp"

#include <fstream>
#include <string>

ProcessStats ResourceMonitor::readProcess(pid_t pid) {
    ProcessStats stats;

    std::ifstream file("/proc/" + std::to_string(pid) + "/status");
    std::string line;

    while (std::getline(file, line)) {
        if (line.rfind("VmRSS:", 0) == 0) {
            auto pos = line.find_first_of("0123456789");
            if (pos != std::string::npos) {
                stats.memoryKb = std::stol(line.substr(pos));
            }
            break;
        }
    }

    return stats;
}
