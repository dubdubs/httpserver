#include "Config.h"
#include <stdexcept>

void Config::load(const std::string& configFile) {
    try {
        YAML::Node config = YAML::LoadFile(configFile);
        
        auto& inst = instance();
        
        if (auto server = config["server"]) {
            inst.port_ = server["port"].as<uint16_t>();
            inst.docRoot_ = server["doc_root"].as<std::string>();
            inst.threadPoolSize_ = server["thread_pool_size"].as<size_t>();
        }
        
        if (auto logging = config["logging"]) {
            inst.logFile_ = logging["filename"].as<std::string>();
        }
        
        if (auto cgi = config["cgi"]) {
            inst.cgiEnabled_ = cgi["enabled"].as<bool>();
            inst.cgiTimeout_ = cgi["timeout"].as<int>();
        }
    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Failed to load config: " + std::string(e.what()));
    }
}

Config& Config::instance() {
    static Config instance;
    return instance;
} 