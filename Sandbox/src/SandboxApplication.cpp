#include "Core/Application.h"

class ExampleLayer : public LSO::Layer {


	public:
		virtual void OnAttach() override
		{
			LSO_INFO("Example layer: OnAttach\n");
		}


		virtual void OnDetach() override {
			LSO_INFO("Example layer: OnDetach\n");
		}


		virtual void OnUpdate() override
		{
			LSO_WARN("Example layer: OnUpdate\n");
		}

	private :
};

int main() {

	auto app = new LSO::Application;
	app->PushLayer(new ExampleLayer);
	app->Run();
	delete app;


	return 0;
}