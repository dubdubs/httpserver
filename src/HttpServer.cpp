#include "HttpServer.h"
#include "Logger.h"
#include "Config.h"
#include <stdexcept>

HttpServer::HttpServer() 
    : running_(false), 
      serverSocket_(-1), 
      port_(Config::getPort()),
      threadPool_(std::make_unique<ThreadPool>(Config::getThreadPoolSize())) {
    
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

void HttpServer::start() {
    running_ = true;
    LOG_INFO("Server starting...");
    
    try {
        acceptLoop();
    } catch (const std::exception& e) {
        LOG_ERROR("Server error: {}", e.what());
        stop();
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

        // 创建新线程处理客户端请求
        std::thread([this, clientSocket]() {
            handleClient(clientSocket);
        }).detach();
    }
}

// ... 其他方法的实现 ... 