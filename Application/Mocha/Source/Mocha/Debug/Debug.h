#pragma once

// std includes
#include <iostream>
#include <string>

namespace Mocha
{

	namespace Debug
	{
		// Testing functions
		void PrintHelloWorld();
		void DoGraphicsSomething();


		namespace Logging
		{
			enum LogLevel {Info, Warning, Error, None};
			void SetGlobalMinimumLogLevel(const LogLevel level);

			void Log(const LogLevel level, const std::string message);
			void Log(const LogLevel level, const char* message);
		}
	}



}