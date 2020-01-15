#include "pch.h"
#include "Log.h"

#include <Windows.h>

namespace LSO {

	#define CHANGE_CONSOLE_COLOR(colorID) SetConsoleTextAttribute(s_Handle, colorID)
	static HANDLE s_Handle = GetStdHandle(STD_OUTPUT_HANDLE);


	std::unique_ptr<Logger> Log::m_Client = std::make_unique<Logger>();
	std::unique_ptr<Logger> Log::m_Core = std::make_unique<Logger>();


#define PRINT_MSG(FuncName, SysTime, message, ...) va_list args;\
											  va_start(args, message);\
											  printf("[%s][%s][%s]:\t", SysTime.c_str(), m_Name.c_str(), FuncName);\
											  vprintf(message, args);\



	static const std::string GetSystemTime() { // This function is created because the "logger" will print the system's time.

		std::time_t time = std::time(0);
		std::tm* now = std::localtime(&time);

		std::stringstream ss;
		ss << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
		return ss.str();
	}


	void Logger::Trace(const char* message, ...)
	{
		if ((m_Level != LSOLogLevels::LAll && m_Level != LSOLogLevels::LTrace) || m_Level == LSOLogLevels::LNone)
			return;

		CHANGE_CONSOLE_COLOR(10);
		PRINT_MSG("Trace", GetSystemTime(), message);
	}

	void Logger::Info(const char* message, ...)
	{
		if ((m_Level != LSOLogLevels::LAll && m_Level != LSOLogLevels::LMessage) || m_Level == LSOLogLevels::LNone)
			return;

		CHANGE_CONSOLE_COLOR(15);
		PRINT_MSG("Infomation", GetSystemTime(), message);
	}

	void Logger::Warn(const char* message, ...)
	{
		if ((m_Level != LSOLogLevels::LAll && m_Level != LSOLogLevels::LWarn) || m_Level == LSOLogLevels::LNone)
			return;

		CHANGE_CONSOLE_COLOR(14);
		PRINT_MSG("Warning", GetSystemTime(), message);
	}

	void Logger::Error(const char* message, ...)
	{
		if ((m_Level != LSOLogLevels::LAll && m_Level != LSOLogLevels::LError) || m_Level == LSOLogLevels::LNone)
			return;

		CHANGE_CONSOLE_COLOR(12);
		PRINT_MSG("Error", GetSystemTime(), message);
	}

	void Logger::Fatal(const char* message, ...)
	{
		CHANGE_CONSOLE_COLOR(12);
		PRINT_MSG("CRITICAL", GetSystemTime(), message);

	}

}