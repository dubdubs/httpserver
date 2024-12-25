#pragma once
#include <spdlog/spdlog.h>
#include <memory>
#include <string>
#include <filesystem>

class Logger {
public:
    static void init(const std::string& logDir = "logs", 
                    const std::string& logFile = "server.log",
                    spdlog::level::level_enum level = spdlog::level::debug);
    static std::shared_ptr<spdlog::logger>& get();
    static void setLevel(spdlog::level::level_enum level);

private:
    static std::shared_ptr<spdlog::logger> logger_;
};

// 使用Logger类的get()方法来记录日志
#define LOG_INFO(...) Logger::get()->info(__VA_ARGS__)
#define LOG_ERROR(...) Logger::get()->error(__VA_ARGS__)
#define LOG_WARN(...) Logger::get()->warn(__VA_ARGS__)
#define LOG_DEBUG(...) Logger::get()->debug(__VA_ARGS__) 