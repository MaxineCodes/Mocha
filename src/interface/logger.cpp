//
// Created by maxin on 03/12/2025.
//

#include "../io/logger.h"

#include <stdio.h>
#include <iostream>

namespace Mocha
{
    bool logger::useCout;
    bool logger::printDebug;

    const char* logger::determineLogLevelPrefix(const logLevel level)
    {
        switch (level)
        {
            case logLevel::INFO:  return   "[INFO]  ";
            case logLevel::WARN:  return   "[WARN]  ";
            case logLevel::ERROR: return   "[ERROR] ";
            case logLevel::GLERROR: return "[GL_ERROR]";
            case logLevel::DEBUG:
            default:              return   "[DEBUG] ";
        }
    }

    void logger::log(const logLevel level, const char *message)
    {
        if (level == logLevel::DEBUG && !printDebug) return;

        const char* prefix = determineLogLevelPrefix(level);

        if (useCout)
        {
            std::cout << prefix << message << std::endl;
        }

    }
} // Mocha