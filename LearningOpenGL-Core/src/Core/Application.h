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
			LayerStack m_LayerStack;

			bool m_IsRunning = true;
			float m_LastFrameTime = 0.0f;

	};

}