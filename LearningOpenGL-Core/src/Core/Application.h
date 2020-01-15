#pragma once


#include "Utility/Log.h"

namespace LSO {

	class Application {
		public:
			Application();

			void Run();

		private: 
			bool m_IsRunning = true;
	};

}