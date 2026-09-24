#ifndef PROCESSPILOT_DAEMON_HPP
#define PROCESSPILOT_DAEMON_HPP

#include "../process/process_manager.hpp"
#include "../config/config_parser.hpp"
#include "../ipc/unix_socket.hpp"

class ProcessPilotDaemon {
public:
    bool run();

private:
    ProcessManager processManager;
    ConfigParser config;
    UnixSocketServer server;
};

#endif
