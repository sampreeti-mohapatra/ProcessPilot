#ifndef UNIX_SOCKET_HPP
#define UNIX_SOCKET_HPP

#include <string>

class UnixSocketServer {
public:
    UnixSocketServer();
    ~UnixSocketServer();

    bool start(const std::string& path);
    std::string receive();
    bool send(const std::string& message);
    void stop();

private:
    int serverFd;
    int clientFd;
    std::string socketPath;
};

class UnixSocketClient {
public:
    bool connectTo(const std::string& path);
    std::string request(const std::string& message);
    void closeConnection();

private:
    int fd = -1;
};

#endif
