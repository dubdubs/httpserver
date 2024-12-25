#pragma once
#include <string>
#include <yaml-cpp/yaml.h>

class Config {
public:
    static void load(const std::string& configFile);
    
    static uint16_t getPort() { return instance().port_; }
    static const std::string& getDocRoot() { return instance().docRoot_; }
    static size_t getThreadPoolSize() { return instance().threadPoolSize_; }
    static const std::string& getLogFile() { return instance().logFile_; }
    static bool isCgiEnabled() { return instance().cgiEnabled_; }
    static int getCgiTimeout() { return instance().cgiTimeout_; }

private:
    Config() = default;
    static Config& instance();
    
    uint16_t port_ = 6379;
    std::string docRoot_ = "./www";
    size_t threadPoolSize_ = 4;
    std::string logFile_ = "logs/server.log";
    bool cgiEnabled_ = true;
    int cgiTimeout_ = 30;
}; 