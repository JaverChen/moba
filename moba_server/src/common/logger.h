// src/common/logger.h
#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <iomanip>
#include <chrono>
#include <atomic>
#include <sys/stat.h>
#include <fmt/format.h>

//日志宏
#define LOG_TRACE(...) Logger::Log(TRACE, Logger::FormatMessage(__VA_ARGS__, __FILE__, __LINE__))
#define LOG_DEBUG(...) Logger::Log(DEBUG, Logger::FormatMessage(fmt::format(__VA_ARGS__), __FILE__, __LINE__))
#define LOG_INFO(...)  Logger::Log(INFO,  Logger::FormatMessage(fmt::format(__VA_ARGS__), __FILE__, __LINE__))
#define LOG_WARN(...)  Logger::Log(WARN,  Logger::FormatMessage(fmt::format(__VA_ARGS__), __FILE__, __LINE__))
#define LOG_ERROR(...) Logger::Log(ERROR, Logger::FormatMessage(fmt::format(__VA_ARGS__), __FILE__, __LINE__))


enum LogLevel {
    TRACE = 0,  // 详细跟踪
    DEBUG = 1,  // 调试信息
    INFO  = 2,  // 常规信息
    WARN  = 3,  // 警告信息
    ERROR = 4   // 错误信息
};

class Logger {
public:
    struct Config {
        std::string path;
        std::string level = "info";
        std::string max_size = "100MB";
        int backup_count = 3;
        bool daemon_mode = false;
    };

    static void Init(const Config& config);
    static void Log(LogLevel level, const std::string& formatted_message);
    static std::string FormatMessage(const std::string& message, const char* file, int line);
private:
    static std::ofstream log_file_;
    static std::mutex log_mutex_;
    static std::atomic<LogLevel> current_level_;
    static Config current_config_;
    
    static void Daemonize();
    static void RotateLogs();
    static size_t ConvertSize(const std::string& size_str);
    static const char* LevelToString(LogLevel level);
    static std::string GetTimestamp();
};