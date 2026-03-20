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
    std::vector<std::string> Mocha::logger::frameLogMessages;
    std::vector<std::string> Mocha::logger::inputLogMessages;

    const char* logger::determineLogLevelPrefix(const logLevel level)
    {
        switch (level)
        {
            case logLevel::INFO:    return "[INFO]  ";
            case logLevel::WARN:    return "[WARN]  ";
            case logLevel::ERROR:   return "[ERROR] ";
            case logLevel::GLERROR: return "[GL_ERROR] ";
            case logLevel::DEBUG:   return "[DEBUG] ";
            default:                return "[DEBUG] ";
        }
    }

    void logger::log(const logLevel level, logType type, const char *message)
    {
        if (level == logLevel::DEBUG && !printDebug) return;

        const char* prefix = determineLogLevelPrefix(level);

        // Just std::cout the whole thing who cares lol
        // surely this won't ever cause issues down the line
        if (useCout) std::cout << prefix << message << std::endl;

        // Store message to the correct log vector
        if      (type == DEFAULT) logMessages.push_back(std::string(prefix) + message);
        else if (type == FRAME) frameLogMessages.push_back(std::string(prefix) + message);
        else if (type == INPUT) inputLogMessages.push_back(std::string(prefix) + message);

    }
} // Mocha