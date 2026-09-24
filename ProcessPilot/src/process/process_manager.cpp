#include "process_manager.hpp"

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

ProcessManager::ProcessManager() : pid(-1) {}

bool ProcessManager::start(const std::string& command) {
    if (isRunning()) {
        return false;
    }

    pid = fork();

    if (pid < 0) {
        pid = -1;
        return false;
    }

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command.c_str(), (char*)nullptr);
        _exit(127);
    }

    return true;
}

bool ProcessManager::stop() {
    if (!isRunning()) {
        return false;
    }

    if (kill(pid, SIGTERM) != 0) {
        return false;
    }

    waitpid(pid, nullptr, 0);
    pid = -1;
    return true;
}

bool ProcessManager::isRunning() const {
    if (pid <= 0) {
        return false;
    }

    if (kill(pid, 0) == 0) {
        return true;
    }

    return false;
}

pid_t ProcessManager::getPid() const {
    return pid;
}
