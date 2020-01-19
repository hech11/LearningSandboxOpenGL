#include "OpenGL-Core.h"

class ExampleLayer : public LSO::Layer {


	public:
		virtual void OnAttach() override {
		}


		virtual void OnUpdate(const LSO::Timestep& ts) override {
			glClear(GL_COLOR_BUFFER_BIT);

			LSO_INFO("timestep: %f\n", ts.GetSeconds());
		}


		
		virtual void OnImguiRender() override {
			ImGui::Begin("Test Window");
			ImGui::Button("Test button");
			ImGui::End();
		}

private:
};

int main() {

	auto app = new LSO::Application;
	app->PushLayer(new ExampleLayer);
	app->Run();
	delete app;


	return 0;
}