#include "HttpServer.h"
#include "Config.h"
#include <iostream>

int main() {
    try {
        
        // 加载配置
        Config::load("config/server_config.yaml");
        
        // 创建并启动服务器
        HttpServer server(6379);
        std::cout << "Server created" << std::endl;
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 