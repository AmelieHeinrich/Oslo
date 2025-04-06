//
// > Notice: Amélie Heinrich @ 2025
// > Create Time: 2025-03-27 14:28:34
//

#include "ConsoleLogger.hpp"

#include <Windows.h>
#include <iostream>

#undef ERROR

void ConsoleLogger::Output(LogLevel level, const std::string& format)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD color = 7; // Default gray/white
    
    switch (level)
    {
        case LogLevel::INFO: color = 10; break;     // Green
        case LogLevel::WARN: color = 14; break;     // Yellow
        case LogLevel::ERROR: color = 12; break;    // Red
        case LogLevel::CRITICAL: color = 13; break; // Magenta
        case LogLevel::DEBUG: color = 11; break;    // Cyan
    }
    
    SetConsoleTextAttribute(hConsole, color);
    std::cout << format << std::endl;
    SetConsoleTextAttribute(hConsole, 7); // Reset to default
}
