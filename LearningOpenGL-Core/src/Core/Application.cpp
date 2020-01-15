#include "pch.h"
#include "Application.h"



namespace LSO {


	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		Log::Init();
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


	void Application::Run() {
		while (m_IsRunning) {

			//Update loop
			for (const auto& layer : m_LayerStack.GetLayerStack()) {
				layer->OnUpdate();
			}

		}
	}



}