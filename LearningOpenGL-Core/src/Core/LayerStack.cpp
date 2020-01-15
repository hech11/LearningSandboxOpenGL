#include "pch.h"
#include "LayerStack.h"


namespace LSO {



	LayerStack::LayerStack() : m_LayerIndex(0) {

	}

	LayerStack::~LayerStack() {
		for (auto & layer : m_LayerStack) {
			layer->OnDetach();
			delete layer;
		}
		m_LayerStack.clear();
	}

	void LayerStack::PushLayer(Layer* layer) {
		layer->OnAttach();
		m_LayerStack.insert(m_LayerStack.begin() + m_LayerIndex, layer);
		m_LayerIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		overlay->OnAttach();
		m_LayerStack.push_back(overlay);
	}



	void LayerStack::PopLayer() {
		m_LayerStack.erase(m_LayerStack.begin() + m_LayerIndex, m_LayerStack.end());
		m_LayerIndex--;
	}

	void LayerStack::PopOverlayer() {
		m_LayerStack.pop_back();
	}

	void LayerStack::PopLayer(Layer* layer) {
		const auto& index = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (index != m_LayerStack.end()) {
			m_LayerStack.erase(index);
			m_LayerIndex--;

		}
	}
	void LayerStack::PopOverlayer(Layer* layer) {
		const auto& index = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (index != m_LayerStack.end()) {
			m_LayerStack.erase(index);
		}
	}

}