// src/common/logger.cpp
#include "logger.h"
#include <iostream>
#include <cstdio>
#include <filesystem>
#include <algorithm>
#include <unistd.h>
#include <fmt/format.h>
#include <sys/stat.h>

using namespace std::chrono;

// 静态成员初始化
std::ofstream Logger::log_file_;
std::mutex Logger::log_mutex_;
std::atomic<LogLevel> Logger::current_level_(INFO);
Logger::Config Logger::current_config_;

void Logger::Init(const Config& config) {
    current_config_ = config;

    // 设置日志级别
    std::string level = config.level;
    std::transform(level.begin(), level.end(), level.begin(), ::tolower);
    if (level == "debug") current_level_ = DEBUG;
    else if (level == "warn") current_level_ = WARN;
    else if (level == "error") current_level_ = ERROR;
    else current_level_ = INFO;

    // 处理日志路径
    std::filesystem::path log_path(config.path);
    if (log_path.is_relative()) {
        log_path = std::filesystem::absolute(log_path);
    }

    // 创建日志目录
    std::filesystem::create_directories(log_path.parent_path());

    // 检查日志轮转
    RotateLogs();

    // 打开日志文件
    log_file_.open(log_path, std::ios::app);
    if (!log_file_.is_open()) {
        throw std::runtime_error("Cannot open log file: " + log_path.string());
    }

    // 初始日志
    Log(INFO, "Logger initialized (Level: " + config.level + ")");

    // 守护进程模式处理
    if (config.daemon_mode) Daemonize();
}

void Logger::Log(LogLevel level, const std::string& message) {
    if (level < current_level_.load()) return;

    std::lock_guard<std::mutex> lock(log_mutex_); 

    // 非守护模式输出到控制台
    if (!current_config_.daemon_mode) {
        std::cout << entry << std::endl;
    }

    // 写入文件
    if (log_file_.is_open()) {
        log_file_ << entry << std::endl;
        
        // 检查文件大小
        log_file_.flush();
        size_t current_size = log_file_.tellp();
        if (current_size > ConvertSize(current_config_.max_size)) {
            RotateLogs();
            log_file_.open(current_config_.path, std::ios::app);
        }
    }
}

// 私有方法实现
void Logger::Daemonize() {
    pid_t pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    setsid();
    umask(0);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void Logger::RotateLogs() {
    std::string base_path = current_config_.path;
    
    // 删除最旧的日志
    std::string oldest = base_path + "." + std::to_string(current_config_.backup_count);
    if (std::filesystem::exists(oldest)) {
        std::filesystem::remove(oldest);
    }

    // 轮转现有日志
    for (int i = current_config_.backup_count - 1; i > 0; --i) {
        std::string old_name = base_path + "." + std::to_string(i);
        std::string new_name = base_path + "." + std::to_string(i + 1);
        if (std::filesystem::exists(old_name)) {
            std::filesystem::rename(old_name, new_name);
        }
    }

    // 重命名当前日志
    if (std::filesystem::exists(base_path)) {
        std::filesystem::rename(base_path, base_path + ".1");
    }
}

size_t Logger::ConvertSize(const std::string& size_str) {
    size_t multiplier = 1;
    std::string num_str;

    if (size_str.find("MB") != std::string::npos) {
        multiplier = 1024 * 1024;
        num_str = size_str.substr(0, size_str.size()-2);
    } else if (size_str.find("KB") != std::string::npos) {
        multiplier = 1024;
        num_str = size_str.substr(0, size_str.size()-2);
    } else {
        num_str = size_str;
    }

    return std::stoul(num_str) * multiplier;
}

const char* Logger::LevelToString(LogLevel level) {
    switch(level) {
        case DEBUG: return "DEBUG";
        case INFO:  return "INFO";
        case WARN:  return "WARN";
        case ERROR: return "ERROR";
        default:    return "UNKNOWN";
    }
}

std::string Logger::GetTimestamp() {
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    
    auto timer = system_clock::to_time_t(now);
    std::tm bt = *std::localtime(&timer);
    
    std::ostringstream oss;
    oss << std::put_time(&bt, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

std::string Logger::FormatMessage(const std::string& message, const char* file, int line) {
    try {
        return fmt::format("[{}:{}] {}", file, line, message);
    } catch (const fmt::format_error& e) {
        return "Invalid log format: " + std::string(e.what());
    }
}