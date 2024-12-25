cmake_minimum_required(VERSION 3.10)
project(cpp_http_server VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加spdlog依赖
find_package(spdlog REQUIRED)
# 添加yaml-cpp依赖
find_package(yaml-cpp REQUIRED)

# 添加头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 收集源文件
file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# 如果文件没有被自动收集，可以手动添加
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/HttpServer.cpp
    ${PROJECT_SOURCE_DIR}/src/Logger.cpp
    ${PROJECT_SOURCE_DIR}/src/Config.cpp
)

# 创建可执行文件
add_executable(http_server ${SOURCES})

# 链接依赖库
target_link_libraries(http_server 
    PRIVATE 
    pthread
    spdlog::spdlog
    yaml-cpp
)

# 配置文件安装
configure_file(
    ${CMAKE_SOURCE_DIR}/config/server_config.yaml
    ${CMAKE_BINARY_DIR}/config/server_config.yaml
    COPYONLY
) 