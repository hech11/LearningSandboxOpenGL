#include "OpenGL-Core.h"
#include "Utility/ShaderUtils.h"
#include "Utility/stb_image.h"


class ExampleLayer : public LSO::Layer {


	public:
		virtual void OnAttach() override {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			float vertex[] = {
				-0.5f, -0.5f,
				 0.5f, -0.5f,
				 0.5f,  0.5f,
				-0.5f,  0.5f,
			};
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(float), vertex, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

			unsigned int indicies[] = {
				0,1,2,
				2,3,0
			};
			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(float), indicies, GL_STATIC_DRAW);

			LSO::Shader shaderFiles({
				{"assets/shaders/VertexShader.vs", GL_VERTEX_SHADER },
				{"assets/shaders/FragmentShader.fs", GL_FRAGMENT_SHADER}
			});
			shader = shaderFiles.GetProgramID();

			model = glm::mat4(1.0f);

			m_CameraController = new LSO::OrthographicCameraController(1280.0f / 720.0f, true);
		}


		virtual void OnDetach() override {
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ibo);

			delete m_CameraController;
		}

		virtual void OnUpdate(const LSO::Timestep& ts) override {



			m_CameraController->OnUpdate(ts);

			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

			glUseProgram(shader);
			glUniformMatrix4fv(glGetUniformLocation(shader, "u_Model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(shader, "u_ProjView"), 1, GL_FALSE, glm::value_ptr(m_CameraController->GetCamera().GetProjView()));
			glUniform4f(glGetUniformLocation(shader, "u_Color"), color.x, color.y, color.z, color.w);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}


		
		virtual void OnImguiRender() override {
			ImGui::Begin("Window");
			ImGui::ColorEdit4("Square color", &color.x);

			static float CMoveSpeed=1.0f, CRotationSpeed = 100.0f, cZoomSpeed = 1.0f;
			
			ImGui::SliderFloat("Camera MoveSpeed", &CMoveSpeed, 0.1f, 10.0f, "%.1f");
			ImGui::SliderFloat("Camera RotationSpeed", &CRotationSpeed, 0.0f, 300.0f, "%.1f");
			ImGui::SliderFloat("Camera ZoomSpeed", &cZoomSpeed, 0.1f, 10.0f, "%.1f");

			m_CameraController->SetMoveSpeed(CMoveSpeed);
			m_CameraController->SetRotateSpeed(CRotationSpeed);
			m_CameraController->SetZoomSpeed(cZoomSpeed);

			ImGui::End();
		}


		bool OnWindowResize(LSO::WindowResizeEvent& event) {
			glViewport(0, 0, event.GetWidth(), event.GetHeight());
			return false;
		}

		virtual void OnEvent(LSO::Event& event) override
		{
			LSO::EventDispatcher dispatcher(event);
			dispatcher.Dispatch<LSO::WindowResizeEvent>(std::bind(&ExampleLayer::OnWindowResize, this, std::placeholders::_1));
			m_CameraController->OnEvent(event);
		}

private:
		unsigned int vao, vbo, ibo, shader;
		glm::mat4 model;

		glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		LSO::OrthographicCameraController* m_CameraController;
};

int main() {

	auto app = new LSO::Application;
	app->PushLayer(new ExampleLayer);
	app->Run();
	delete app;


	return 0;
}