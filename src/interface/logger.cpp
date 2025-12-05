//
// Created by maxin on 03/12/2025.
//

#include "logger.h"

#include <stdio.h>
#include <iostream>

namespace Mocha
{
    bool logger::useCout;
    bool logger::printDebug;
    std::vector<std::string> Mocha::logger::logMessages;

    const char* logger::determineLogLevelPrefix(const logLevel level)
    {
        switch (level)
        {
            case logLevel::INFO:    return "[INFO]  ";
            case logLevel::WARN:    return "[WARN]  ";
            case logLevel::ERROR:   return "[ERROR] ";
            case logLevel::GLERROR: return "[GL_ERROR] ";
            case logLevel::DEBUG:   return "[DEBUG] ";
            default:              return   "[DEBUG] ";
        }
    }

    void logger::log(const logLevel level, const char *message)
    {
        if (level == logLevel::DEBUG && !printDebug) return;

        const char* prefix = determineLogLevelPrefix(level);

        // Store message to a log string
        logMessages.push_back(std::string(prefix) + message);

        if (useCout)
        {
            std::cout << prefix << message << std::endl;
        }

    }
} // Mocha