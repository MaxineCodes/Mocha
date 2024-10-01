#include "Mocha/Mocha.h"

int main()
{
	//Mocha::Debug::EnableDebug();
	//Mocha::Debug::DisableDebug();


	// Testing functions
	Mocha::Debug::PrintHelloWorld();
	Mocha::Debug::DoGraphicsSomething();


	//if (Mocha::InitiateWindow())
	//{
	//	std::cout << "Success" << std::endl;
	//}

	Mocha::Debug::Logging::SetGlobalMinimumLogLevel(Mocha::Debug::Logging::Info);

	Mocha::Debug::Logging::Log(Mocha::Debug::Logging::Warning, "test");
}