#include "logger.hpp"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

static void logMessage(const std::string& level,
                       const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::cout << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
              << "] [" << level << "] " << message << "\n";
}

void Logger::info(const std::string& message) {
    logMessage("INFO", message);
}

void Logger::error(const std::string& message) {
    logMessage("ERROR", message);
}
