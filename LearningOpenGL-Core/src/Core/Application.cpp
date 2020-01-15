#include "pch.h"
#include "Application.h"



namespace LSO {


	Application::Application()
	{
		Log::Init();


		int test = 1234;
		LSO_CORE_SET_LOG_LEVEL(LSOLogLevels::LNone);
		LSO_SET_LOG_LEVEL(LSOLogLevels::LNone);

		LSO_CORE_INFO("Message %d\n", test);
		LSO_INFO("Message %d\n", test);

		LSO_CORE_WARN("Waring %d\n", test);
		LSO_WARN("Warning %d\n", test);
		LSO_CORE_ERROR("Error %d\n", test);
		LSO_ERROR("Error %d\n", test);
		LSO_TRACE("Trace %d\n", test);
		LSO_CORE_TRACE("Trace %d\n", test);

		LSO_FATAL("FATAL %d\n", test);
		LSO_CORE_FATAL("FATAL %d\n", test);
	}

	void Application::Run() {
		while (m_IsRunning) {



		}
	}

}