#include "unix_socket.hpp"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

UnixSocketServer::UnixSocketServer()
    : serverFd(-1), clientFd(-1) {}

UnixSocketServer::~UnixSocketServer() {
    stop();
}

bool UnixSocketServer::start(const std::string& path) {
    socketPath = path;

    serverFd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (serverFd < 0) {
        return false;
    }

    unlink(socketPath.c_str());

    sockaddr_un address{};
    address.sun_family = AF_UNIX;
    std::strncpy(address.sun_path, socketPath.c_str(),
                 sizeof(address.sun_path) - 1);

    if (bind(serverFd, reinterpret_cast<sockaddr*>(&address),
             sizeof(address)) < 0) {
        ::close(serverFd);
        serverFd = -1;
        return false;
    }

    if (listen(serverFd, 5) < 0) {
        ::close(serverFd);
        serverFd = -1;
        unlink(socketPath.c_str());
        return false;
    }

    return true;
}

std::string UnixSocketServer::receive() {
    clientFd = accept(serverFd, nullptr, nullptr);
    if (clientFd < 0) {
        return "";
    }

    char buffer[4096]{};
    ssize_t bytes = read(clientFd, buffer, sizeof(buffer) - 1);

    if (bytes <= 0) {
        ::close(clientFd);
        clientFd = -1;
        return "";
    }

    buffer[bytes] = '\0';
    return std::string(buffer);
}

bool UnixSocketServer::send(const std::string& message) {
    if (clientFd < 0) {
        return false;
    }

    ssize_t result = write(clientFd, message.c_str(), message.size());
    ::close(clientFd);
    clientFd = -1;

    return result >= 0;
}

void UnixSocketServer::stop() {
    if (clientFd >= 0) {
        ::close(clientFd);
        clientFd = -1;
    }

    if (serverFd >= 0) {
        ::close(serverFd);
        serverFd = -1;
    }

    if (!socketPath.empty()) {
        unlink(socketPath.c_str());
    }
}

bool UnixSocketClient::connectTo(const std::string& path) {
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        return false;
    }

    sockaddr_un address{};
    address.sun_family = AF_UNIX;
    std::strncpy(address.sun_path, path.c_str(),
                 sizeof(address.sun_path) - 1);

    if (connect(fd, reinterpret_cast<sockaddr*>(&address),
                sizeof(address)) < 0) {
        ::close(fd);
        fd = -1;
        return false;
    }

    return true;
}

std::string UnixSocketClient::request(const std::string& message) {
    if (fd < 0) {
        return "";
    }

    write(fd, message.c_str(), message.size());

    char buffer[4096]{};
    ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes <= 0) {
        closeConnection();
        return "";
    }

    buffer[bytes] = '\0';
    closeConnection();

    return std::string(buffer);
}

void UnixSocketClient::closeConnection() {
    if (fd >= 0) {
        ::close(fd);
        fd = -1;
    }
}
