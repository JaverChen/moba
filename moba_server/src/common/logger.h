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

#define LOG_DEBUG(...) Logger::Log(DEBUG, fmt::format("[{}:{}] {}", __FILE__, __LINE__, fmt::format(__VA_ARGS__)))
#define LOG_INFO(...)  Logger::Log(INFO,  fmt::format("[{}:{}] {}", __FILE__, __LINE__, fmt::format(__VA_ARGS__)))
#define LOG_WARN(...)  Logger::Log(WARN,  fmt::format("[{}:{}] {}", __FILE__, __LINE__, fmt::format(__VA_ARGS__)))
#define LOG_ERROR(...) Logger::Log(ERROR, fmt::format("[{}:{}] {}", __FILE__, __LINE__, fmt::format(__VA_ARGS__)))

enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3
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
    static std::string FormatMessage(const std::string& message, const char* file, int line);
};