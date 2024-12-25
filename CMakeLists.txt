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

# 如果系统没有安装spdlog，使用FetchContent
if(NOT spdlog_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.x
    )
    FetchContent_MakeAvailable(spdlog)
endif()

# 检查C++版本并添加filesystem支持
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.1)
        link_libraries(stdc++fs)
    endif()
endif()

# 创建可执行文件
add_executable(http_server ${SOURCES})

# 链接依赖库
target_link_libraries(http_server 
    PRIVATE 
    pthread
    spdlog::spdlog
    yaml-cpp
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.1>>:stdc++fs>
)

# 配置文件安装
configure_file(
    ${CMAKE_SOURCE_DIR}/config/server_config.yaml
    ${CMAKE_BINARY_DIR}/config/server_config.yaml
    COPYONLY
) 