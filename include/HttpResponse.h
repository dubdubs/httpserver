#pragma once
#include <string>
#include <map>

class HttpResponse {
public:
    HttpResponse() = default;
    
    void setStatus(int code, const std::string& message);
    void setHeader(const std::string& key, const std::string& value);
    void setBody(const std::string& body);
    
    std::string toString() const;
    
private:
    int statusCode_ = 200;
    std::string statusMessage_ = "OK";
    std::map<std::string, std::string> headers_;
    std::string body_;
}; 