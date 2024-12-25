#pragma once
#include <string>
#include <map>

class HttpRequest {
public:
    enum class Method { GET, POST, UNKNOWN };
    
    HttpRequest() = default;
    
    Method getMethod() const { return method_; }
    const std::string& getPath() const { return path_; }
    const std::string& getQueryString() const { return queryString_; }
    
    void parse(const std::string& requestLine);
    
private:
    Method method_ = Method::UNKNOWN;
    std::string path_;
    std::string queryString_;
    std::map<std::string, std::string> headers_;
}; 