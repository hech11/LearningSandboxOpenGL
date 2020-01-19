#pragma once

#include "Core/LayerStack.h"



namespace LSO {

	class ImGuiLayer : public Layer {
		public:
			ImGuiLayer();

			virtual void OnAttach() override;
			virtual void OnDetach() override;


			void Start();
			void End();
	};

}