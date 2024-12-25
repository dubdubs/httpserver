#include "Logger.h"
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Logger::logger_;

void Logger::init(const std::string& logFile) {
    try {
        // 创建控制台sink和文件sink
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            logFile, 5*1024*1024, 3
        );

        // 创建多个sink的logger
        std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
        logger_ = std::make_shared<spdlog::logger>("http_server", sinks.begin(), sinks.end());

        // 设置日志格式
        logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%t] %v");
        
        // 设置日志级别
        logger_->set_level(spdlog::level::debug);
        
        // 设置为默认logger
        spdlog::set_default_logger(logger_);
        
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Log initialization failed: " << ex.what() << std::endl;
        throw;
    }
}

std::shared_ptr<spdlog::logger>& Logger::get() {
    if (!logger_) {
        throw std::runtime_error("Logger not initialized");
    }
    return logger_;
} 