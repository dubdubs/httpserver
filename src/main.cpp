#include "HttpServer.h"
#include "Logger.h"
#include "Config.h"
#include <iostream>
#include <spdlog/spdlog.h>

int main() {
    try {
        // 初始化日志
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%t] %v");
        spdlog::set_level(spdlog::level::debug);

        // 加载配置
        Config::load("config/server_config.yaml");
        
        // 创建并启动服务器
        HttpServer server(6379);
        server.start();
    } catch (const std::exception& e) {
        spdlog::error("Fatal error: {}", e.what());
        return 1;
    }
    
    return 0;
} 