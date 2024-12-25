#include "HttpServer.h"
#include "Logger.h"
#include "Config.h"
#include <stdexcept>
#include <system_error>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

HttpServer::HttpServer(uint16_t port) 
    : running_(false), 
      serverSocket_(-1), 
      port_(port) {
    
    try {
        serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket_ < 0) {
            throw std::system_error(errno, std::system_category(), "Failed to create socket");
        }

        int opt = 1;
        if (setsockopt(serverSocket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            throw std::system_error(errno, std::system_category(), "Failed to set socket options");
        }

        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port_);

        if (bind(serverSocket_, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            throw std::system_error(errno, std::system_category(), "Failed to bind");
        }

        if (listen(serverSocket_, SOMAXCONN) < 0) {
            throw std::system_error(errno, std::system_category(), "Failed to listen");
        }

        LOG_INFO("Server initialized on port {}", port_);
    } catch (const std::exception& e) {
        if (serverSocket_ >= 0) {
            close(serverSocket_);
        }
        LOG_ERROR("Server initialization failed: {}", e.what());
        throw;
    }
}

HttpServer::~HttpServer() {
    if (serverSocket_ >= 0) {
        close(serverSocket_);
    }
}

void HttpServer::acceptLoop() {
    while (running_) {
        sockaddr_in clientAddr{};
        socklen_t clientLen = sizeof(clientAddr);
        
        int clientSocket = accept(serverSocket_, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        // 处理新连接
        try {
            handleClient(clientSocket);
        } catch (const std::exception& e) {
            std::cerr << "Error handling client: " << e.what() << std::endl;
            close(clientSocket);
        }
    }
}

void HttpServer::start() {
    running_ = true;
    LOG_INFO("Server starting on port {}", port_);
    acceptLoop();
}

void HttpServer::stop() {
    running_ = false;
    if (serverSocket_ >= 0) {
        close(serverSocket_);
        serverSocket_ = -1;
    }
}

// ... 其他方法的实现 ... 