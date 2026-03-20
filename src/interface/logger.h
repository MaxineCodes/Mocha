//
// Created by maxin on 03/12/2025.
//

#ifndef MOCHA_LOGGER_H
#define MOCHA_LOGGER_H
#include <string>
#include <vector>

/*
 *  logger.h
 *
 *  logger.h contains the logging system, it's a very simple logger for the bare essentials.
 *  You might wonder, 'why not just use a library that gives you a better, faster, and easier to use logger?'
 *  Good question, the answer is an unsatisfactory 'because I want to learn how to make a logger.'
 *  This is an educational project for myself. Inefficiency is fine.
 *
 */

namespace Mocha
{
    class logger
    {
    public:
        enum logLevel
        {
            DEBUG, INFO, WARN, ERROR, GLERROR
        };
        enum logType
        {
            DEFAULT, FRAME, INPUT
        };

        static bool printDebug;
        static bool useCout;

        static std::vector<std::string> logMessages;
        static std::vector<std::string> frameLogMessages;
        static std::vector<std::string> inputLogMessages;

    public:
        static void log(logLevel level, logType type, const char* message);
        static void log(logLevel level, logType type, const std::string& message) { log(level, type, message.c_str()); }

        // Default logging functions & string overloads
        static void logInfo     (const char* message)   { log(logLevel::INFO, DEFAULT,  message); }
        static void logDebug    (const char* message)   { log(logLevel::DEBUG, DEFAULT, message); }
        static void logWarn     (const char* message)   { log(logLevel::WARN, DEFAULT,  message); }
        static void logError    (const char* message)   { log(logLevel::ERROR, DEFAULT, message); }
        static void logGLError  (const char* message)   { log(logLevel::GLERROR, DEFAULT, message); }
        static void logInfo     (const std::string& message)   { logInfo    (message.c_str()); }
        static void logDebug    (const std::string& message)   { logDebug   (message.c_str()); }
        static void logWarn     (const std::string& message)   { logWarn    (message.c_str()); }
        static void logError    (const std::string& message)   { logError   (message.c_str()); }
        static void logGLError  (const std::string& message)   { logGLError (message.c_str()); }

        // Frame logging functions & string overloads
        static void logInfoFrame    (const char* message)   { log(logLevel::INFO, FRAME,  message); }
        static void logDebugFrame   (const char* message)   { log(logLevel::DEBUG, FRAME, message); }
        static void logWarnFrame    (const char* message)   { log(logLevel::WARN, FRAME,  message); }
        static void logErrorFrame   (const char* message)   { log(logLevel::ERROR, FRAME, message); }
        static void logGLErrorFrame (const char* message)   { log(logLevel::GLERROR, FRAME, message); }
        static void logInfoFrame    (const std::string& message)   { logInfoFrame    (message.c_str()); }
        static void logDebugFrame   (const std::string& message)   { logDebugFrame   (message.c_str()); }
        static void logWarnFrame    (const std::string& message)   { logWarnFrame    (message.c_str()); }
        static void logErrorFrame   (const std::string& message)   { logErrorFrame   (message.c_str()); }
        static void logGLErrorFrame (const std::string& message)   { logGLErrorFrame (message.c_str()); }

        // Input event logging functions & string overloads
        static void logInfoInput    (const char* message)   { log(logLevel::INFO, INPUT,  message); }
        static void logDebugInput   (const char* message)   { log(logLevel::DEBUG, INPUT, message); }
        static void logErrorInput   (const char* message)   { log(logLevel::ERROR, INPUT,  message); }
        static void logInfoInput    (const std::string& message)   { logInfoInput    (message.c_str()); }
        static void logDebugInput   (const std::string& message)   { logDebugInput   (message.c_str()); }
        static void logErrorInput   (const std::string& message)   { logErrorInput   (message.c_str()); }

        // ---
        static void setUseCout(const bool enabled)  { useCout = enabled; }
        static void setPrintDebug(const bool enabled) { printDebug = enabled; }

        static std::vector<std::string> getLogMessages() { return logMessages; }
        static std::vector<std::string> getFrameLogMessages() { return frameLogMessages; }
        static std::vector<std::string> getInputLogMessages() { return inputLogMessages; }

        static bool getUseCout() { return useCout; }
        static bool getPrintDebug() { return printDebug; }

    private:
        static const char* determineLogLevelPrefix(logLevel level);




    };

} // Mocha

#endif //MOCHA_LOGGER_H