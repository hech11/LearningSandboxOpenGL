#include "pch.h"
#include "ShaderUtils.h"
#include "FileUtils.h"

#include <glad/glad.h>

#include "Log.h"

namespace LSO {
	
	Shader::Shader(const std::initializer_list<ShaderFiles>& shaderFiles)
		: m_ShaderFiles(shaderFiles) 
	{
		m_RendererID = GenerateProgram();
	}

	unsigned int Shader::GenerateShader(const std::string& shaderFilepath, unsigned int type) {
		unsigned int shader = glCreateShader(type);
		const char* shaderSource = shaderFilepath.c_str();
		glShaderSource(shader, 1, &shaderSource, nullptr);
		glCompileShader(shader);

		int validation;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &validation);

		if (!validation) {

			int logLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			char* message = (char*)alloca(logLength);
			glGetShaderInfoLog(shader, logLength, &logLength, message);

			std::string shaderType;
			switch (type) {
				case GL_VERTEX_SHADER:
					shaderType.append("Vertex");
					break;
				case GL_FRAGMENT_SHADER:
					shaderType.append("Fragment");
					break;

				case GL_GEOMETRY_SHADER:
					shaderType.append("Geometry");
					break;

				case GL_TESS_CONTROL_SHADER:
					shaderType.append("Tess Control");
					break;

				case GL_TESS_EVALUATION_SHADER:
					shaderType.append("Tess Evaluation");
					break;

				case GL_COMPUTE_SHADER:
					shaderType.append("Compute");
					break;


			}
			LSO_CORE_ERROR("OpenGL (%s) Error! MESSAGE :\n %s\n\n", shaderType.c_str(), message);

			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}

	unsigned int Shader::GenerateProgram() {
		unsigned int program = glCreateProgram();
		for (auto & ShaderFile : m_ShaderFiles) {
			ShaderFile.m_ShaderID = GenerateShader(LSO::ReadFile(ShaderFile.Filepath), ShaderFile.Type);
			glAttachShader(program, ShaderFile.m_ShaderID);
			
		}

		glLinkProgram(program);
		glValidateProgram(program);

		for (auto & ShaderFile : m_ShaderFiles) {
			glDeleteShader(ShaderFile.m_ShaderID);
		}

		return program;
	}

}