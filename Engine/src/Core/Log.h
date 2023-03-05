#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine3D
{
	class Log
	{
	public:
		static Log& GetInstance();
		inline std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engineLogger; }
		inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
	private:
		Log();
		static Log* instance;
		static std::mutex mutex;

		std::shared_ptr<spdlog::logger> engineLogger;
		std::shared_ptr<spdlog::logger> clientLogger;
	};



	#define EN_CORE_ERROR(...) Engine3D::Log::GetInstance().GetEngineLogger()->error(__VA_ARGS__);
	#define EN_CORE_WARN(...) Engine3D::Log::GetInstance().GetEngineLogger()->warn(__VA_ARGS__);
	#define EN_CORE_INFO(...) Engine3D::Log::GetInstance().GetEngineLogger()->info(__VA_ARGS__);
	#define EN_CORE_INFO(...) Engine3D::Log::GetInstance().GetEngineLogger()->trace(__VA_ARGS__);

	#define EN_ERROR(...)Engine3D::Log::GetInstance().GetEngineLogger()->error(__VA_ARGS__);
	#define EN_WARN(...) Engine3D::Log::GetInstance().GetEngineLogger()->warn(__VA_ARGS__);
	#define EN_INFO(...) Engine3D::Log::GetInstance().GetEngineLogger()->info(__VA_ARGS__);
	#define EN_TRACE(...) Engine3D::Log::GetInstance().GetEngineLogger()->trace(__VA_ARGS__);
}