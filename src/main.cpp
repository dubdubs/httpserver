#include "HttpServer.h"
#include "Logger.h"
#include "Config.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/file_sinks.h>

int main() {
    try {
        // 创建日志目录
        std::filesystem::create_directories("logs");

        // 创建控制台sink
        auto console_sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%t] %v");

        // 创建文件sink
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
            "logs/server.log"
        );
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] %v");

        // 创建logger
        auto logger = std::make_shared<spdlog::logger>("server_logger", 
            spdlog::sinks_init_list{console_sink, file_sink}
        );
        spdlog::set_default_logger(logger);

        spdlog::info("Logger initialized");

        // 加载配置
        Config::load("config/server_config.yaml");
        
        // 创建并启动服务器
        HttpServer server(6379);
        spdlog::info("Server created");
        server.start();
    } catch (const std::exception& e) {
        spdlog::error("Fatal error: {}", e.what());
        return 1;
    }
    
    return 0;
} 