#ifndef RESOURCE_MONITOR_HPP
#define RESOURCE_MONITOR_HPP

#include <sys/types.h>

struct ProcessStats {
    long memoryKb = 0;
};

class ResourceMonitor {
public:
    static ProcessStats readProcess(pid_t pid);
};

#endif
