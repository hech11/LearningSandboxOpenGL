#include "OpenGL-Core.h"

class ExampleLayer : public LSO::Layer {


	public:
		virtual void OnAttach() override {
			glm::vec2 test1(1, 2);
			glm::vec2 test2(1, 2);
			glm::vec2 test3 = test1 + test2;

			LSO_INFO("%f, %f\n", test3.x, test3.y);

		}


		virtual void OnUpdate(const LSO::Timestep& ts) override {
			glClear(GL_COLOR_BUFFER_BIT);

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