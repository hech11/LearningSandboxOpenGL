#pragma once

#include "pch.h"

namespace LSO {

	class Layer {
		public :
			Layer(const std::string& debugName = "Layer") : m_Name(debugName) {}
			virtual ~Layer(){
				OnDetach();
			}

			virtual void OnAttach(){}
			virtual void OnDetach() {}

			virtual void OnUpdate() {}


			void SetName(const std::string& name) { m_Name = name; }

			const std::string& GetName() const { return m_Name; }
			std::string& GetName() { return m_Name; }


		private :
			std::string m_Name;

	};


	class LayerStack {

		public :
			LayerStack();
			~LayerStack();

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);

			void PopLayer();
			void PopOverlayer();

			void PopLayer(Layer* layer);
			void PopOverlayer(Layer* layer);


			inline const std::vector<Layer*>& GetLayerStack() const { return m_LayerStack; }
		private :
			unsigned int m_LayerIndex;
			std::vector<Layer*> m_LayerStack;
	};

}