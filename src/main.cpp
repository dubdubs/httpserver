#include "HttpServer.h"
#include "Logger.h"
#include "Config.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        // 加载配置
        Config::load("config/server_config.yaml");
        
        // 初始化日志
        Logger::init(Config::getLogFile());
        
        // 创建并启动服务器
        HttpServer server;
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 