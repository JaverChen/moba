// src/common/logger.cpp
#include "logger.h"
#include <iostream>

void Logger::Info(const std::string& message) {
    std::cout << "[INFO] " << message << std::endl;  // 简单实现
}