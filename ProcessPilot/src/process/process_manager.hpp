#ifndef PROCESS_MANAGER_HPP
#define PROCESS_MANAGER_HPP

#include <string>
#include <sys/types.h>

class ProcessManager {
public:
    ProcessManager();

    bool start(const std::string& command);
    bool stop();
    bool isRunning() const;
    pid_t getPid() const;

private:
    pid_t pid;
};

#endif
