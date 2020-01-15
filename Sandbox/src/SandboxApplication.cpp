#include "Core/Application.h"

class ExampleLayer : public LSO::Layer {


	public:
		virtual void OnAttach() override {
		}


		virtual void OnDetach() override {
		}


		virtual void OnUpdate() override {
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