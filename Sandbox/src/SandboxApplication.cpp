#include "OpenGL-Core.h"
#include "Utility/ShaderUtils.h"


class ExampleLayer : public LSO::Layer {


	public:
		virtual void OnAttach() override {
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
			proj = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
		}


		virtual void OnDetach() override {
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ibo);
		}

		virtual void OnUpdate(const LSO::Timestep& ts) override {
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

			glUseProgram(shader);
			glUniformMatrix4fv(glGetUniformLocation(shader, "u_Model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(shader, "u_Proj"), 1, GL_FALSE, glm::value_ptr(proj));
			glUniform4f(glGetUniformLocation(shader, "u_Color"), color.x, color.y, color.z, color.w);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		}


		
		virtual void OnImguiRender() override {
			ImGui::Begin("Test Window");
			ImGui::Button("Test button");
			ImGui::ColorEdit4("Square color", &color.x);
			ImGui::End();
		}

	private :
		unsigned int vao, vbo, ibo, shader;
		glm::mat4 model, proj;

		glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

int main() {

	auto app = new LSO::Application;
	app->PushLayer(new ExampleLayer);
	app->Run();
	delete app;


	return 0;
}