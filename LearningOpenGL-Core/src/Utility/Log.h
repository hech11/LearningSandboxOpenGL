#pragma once

#include "pch.h"

namespace LSO {

	enum class LSOLogLevels {
		LNone = -1,
		LTrace,
		LInfo,
		LWarn,
		LError,
		LAll
	};

	class Logger {
		public :
			void Trace(const char* message, ...);
			void Info(const char* message, ...);
			void Warn(const char* message, ...);
			void Error(const char* message, ...);
			void Fatal(const char* message, ...);

			void SetName(const std::string& name) { m_Name = name; }
			void SetLogLevel(LSOLogLevels level) { m_Level = level; }

			std::string& GetName() { return m_Name; }
			const std::string& GetName() const { return m_Name; }
		private :
			std::string m_Name;
			LSOLogLevels m_Level = LSOLogLevels::LAll;
	};

	class Log {

		public :

			static void Init() {
				m_Client->SetName("Client");
				m_Core->SetName("Core");
			}

			inline static const std::unique_ptr<Logger>& GetCore()  { return m_Core; }
			inline static const std::unique_ptr<Logger>& GetClient()  { return m_Client; }

		private :
			static std::unique_ptr<Logger> m_Client, m_Core;
	};

}

#define LSO_CORE_TRACE(message, ...) LSO::Log::GetCore()->Trace(message, __VA_ARGS__)
#define LSO_CORE_INFO(message, ...) LSO::Log::GetCore()->Info(message, __VA_ARGS__)
#define LSO_CORE_WARN(message, ...) LSO::Log::GetCore()->Warn(message, __VA_ARGS__)
#define LSO_CORE_ERROR(message, ...) LSO::Log::GetCore()->Error(message, __VA_ARGS__)
#define LSO_CORE_FATAL(message, ...) LSO::Log::GetCore()->Fatal(message, __VA_ARGS__)
#define LSO_CORE_SET_LOG_LEVEL(level) LSO::Log::GetCore()->SetLogLevel(level)


#define LSO_TRACE(message, ...) LSO::Log::GetClient()->Trace(message, __VA_ARGS__)
#define LSO_INFO(message, ...) LSO::Log::GetClient()->Info(message, __VA_ARGS__)
#define LSO_WARN(message, ...) LSO::Log::GetClient()->Warn(message, __VA_ARGS__)
#define LSO_ERROR(message, ...) LSO::Log::GetClient()->Error(message, __VA_ARGS__)
#define LSO_FATAL(message, ...) LSO::Log::GetClient()->Fatal(message, __VA_ARGS__)
#define LSO_SET_LOG_LEVEL(level) LSO::Log::GetClient()->SetLogLevel(level)


#define LSO_ASSERT(x, message, ...) if(!(x)){\
LSO::Log::GetCore()->Fatal(message, __VA_ARGS__ );\
__debugbreak();}