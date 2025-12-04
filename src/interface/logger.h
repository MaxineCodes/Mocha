//
// Created by maxin on 03/12/2025.
//

#ifndef MOCHA_LOGGER_H
#define MOCHA_LOGGER_H
#include <string>

namespace Mocha
{
    class logger
    {
    public:
        enum logLevel
        {
            DEBUG, INFO, WARN, ERROR, GLERROR
        };

        static bool printDebug;
        static bool useCout;

    public:
        static void log(logLevel level, const char* message);
        static void log(logLevel level, const std::string& message) { log(level, message.c_str()); }

        static void logInfo (const char* message)   { log(logLevel::INFO,  message); }
        static void logDebug(const char* message)   { log(logLevel::DEBUG, message); }
        static void logWarn (const char* message)   { log(logLevel::WARN,  message); }
        static void logError(const char* message)   { log(logLevel::ERROR, message); }
        static void logGLError(const char* message) { log(logLevel::GLERROR, message); }

        static void setUseCout(const bool enabled)  { useCout = enabled; }
        static void setPrintDebug(const bool enabled) { printDebug = enabled; }

        static bool getUseCout() { return useCout; }
        static bool getPrintDebug() { return printDebug; }

    private:
        static const char* determineLogLevelPrefix(logLevel level);




    };

} // Mocha

#endif //MOCHA_LOGGER_H