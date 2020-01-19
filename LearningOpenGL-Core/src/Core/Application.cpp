#include "pch.h"
#include "Application.h"

#include <GLFW/include/GLFW/glfw3.h>

namespace LSO {


	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
		
		Log::Init();

		m_Window = std::make_unique<Window>();
		m_Window->SetVsync(false);
	}



	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::PopLayer() {
		m_LayerStack.PopLayer();
	}

	void Application::PopLayer(Layer* layer) {
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay() {
		m_LayerStack.PopOverlayer();
	}

	void Application::PopOverlay(Layer* overlay) {
		m_LayerStack.PopOverlayer(overlay);
	}


	void Application::OnEvent(Event& event) {


		for (auto it = m_LayerStack.GetLayerStack().rbegin(); it != m_LayerStack.GetLayerStack().rend(); ++it)
		{
			(*it)->OnEvent(event);
			if (event.Handled)
				break;
		}

		for (const auto& layer : m_LayerStack.GetLayerStack()) {
			layer->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	void Application::Run() {


		while (m_IsRunning) {

			float time = 0.0f; // temp
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			//Update loop
			for (const auto& layer : m_LayerStack.GetLayerStack()) {
				layer->OnUpdate(ts);
			}




			m_Window->OnUpdate();

		}
	}


}