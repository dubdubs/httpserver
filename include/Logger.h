#pragma once
#include <spdlog/spdlog.h>
#include <memory>

class Logger {
public:
    static void init(const std::string& logFile);
    static std::shared_ptr<spdlog::logger>& get();

private:
    static std::shared_ptr<spdlog::logger> logger_;
};

#define LOG_INFO(...) Logger::get()->info(__VA_ARGS__)
#define LOG_ERROR(...) Logger::get()->error(__VA_ARGS__)
#define LOG_WARN(...) Logger::get()->warn(__VA_ARGS__)
#define LOG_DEBUG(...) Logger::get()->debug(__VA_ARGS__) 