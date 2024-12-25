#pragma once
#include <spdlog/spdlog.h>
#include <memory>
#include <string>

class Logger {
public:
    static void init(const std::string& logFile);
    static std::shared_ptr<spdlog::logger>& get();

private:
    static std::shared_ptr<spdlog::logger> logger_;
};

// 定义日志宏
#define LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define LOG_WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__) 