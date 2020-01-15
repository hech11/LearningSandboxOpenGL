#pragma once


#include "Utility/Log.h"
#include "Core/LayerStack.h"
#include "Core/Event.h"

namespace LSO {

	class Application {
		public:
			Application();

			static Application& Get() { return *s_Instance; }
			void OnEvent(Event& event);

			void Run();



			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);


			void PopLayer();
			void PopOverlay();

			void PopLayer(Layer* layer);
			void PopOverlay(Layer* overlay);


		private:
			static Application* s_Instance;

			bool m_IsRunning = true;
			LayerStack m_LayerStack;
	};

}