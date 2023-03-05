#include "enpch.h"
#include "Log.h"

namespace Engine3D
{

	Log* Log::instance = nullptr;
	std::mutex Log::mutex;

	Log::Log()
	{
		// Initialize loggers

		spdlog::set_level(spdlog::level::trace);
		engineLogger = spdlog::stdout_color_mt("Engine");
		clientLogger = spdlog::stdout_color_mt("Client");

		engineLogger->set_pattern("%^[%T] %n: %v%$");
		clientLogger->set_pattern("%^[%T] %n: %v%$");

	}

	Log& Log::GetInstance()
	{
		if (instance == nullptr)
		{
			std::cout << "A" << std::endl;
			instance = new Log();
			return *instance;
		}
		return *instance;
	}
}
