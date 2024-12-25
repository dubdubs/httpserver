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

// 修改日志宏定义
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__) 