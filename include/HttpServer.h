#pragma once
#include <string>
#include <memory>
#include <thread>
#include <functional>
#include <netinet/in.h>
#include <iostream>

class HttpServer {
public:
    explicit HttpServer(uint16_t port = 6379);
    ~HttpServer();

    void start();
    void stop();

private:
    void acceptLoop();
    void handleClient(int clientSocket);
    
    // 静态文件处理
    void serveFile(int client, const std::string& filename);
    void sendHeaders(int client, const std::string& filename);
    void sendFile(int client, FILE* resource);
    
    // CGI处理
    void executeCgi(int client, const std::string& path,
                   const std::string& method, const std::string& queryString);
    
    // HTTP请求处理
    void handleRequest(int client);
    std::string getLine(int sock);
    void sendError(int client, int errorCode, const std::string& message);
    
    bool running_;
    int serverSocket_;
    uint16_t port_;
    static constexpr int BUFFER_SIZE = 1024;
    static constexpr const char* SERVER_STRING = "Server: CPP-HttpServer/1.0\r\n";
}; 