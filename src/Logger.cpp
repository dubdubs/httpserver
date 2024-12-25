#include "Logger.h"
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/file_sinks.h>

std::shared_ptr<spdlog::logger> Logger::logger_;

void Logger::init(const std::string& logFile) {
    try {
        // Create sinks with custom formatting
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            logFile,
            5*1024*1024,  // 5MB file size
            3,            // Keep 3 rotated files
            true         // Rotate on open
        );

        // Set individual sink log patterns
        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%t] %v");
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] [%s:%#] %v");

        // Create logger with multiple sinks
        std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
        logger_ = std::make_shared<spdlog::logger>("http_server", sinks.begin(), sinks.end());

        // Set logger properties
        logger_->set_level(spdlog::level::debug);
        logger_->flush_on(spdlog::level::error);  // Immediately flush on error

        // Set as default logger
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