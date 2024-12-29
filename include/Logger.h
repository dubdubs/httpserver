#pragma once
#include <spdlog/spdlog.h>
#include <memory>
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

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