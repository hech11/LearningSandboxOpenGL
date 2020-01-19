#pragma once

#include "pch.h"

namespace LSO {

	struct ShaderFiles {
		std::string Filepath;
		unsigned int Type;

		ShaderFiles(const std::string& filepath, unsigned int type) : Filepath(filepath), Type(type)
		{
		}


		private :
			unsigned int m_ShaderID;
			friend class Shader;

	};
	class Shader {

		public :
			Shader(const std::initializer_list<ShaderFiles>& shaderFiles);
			inline const unsigned int& GetProgramID() const { return m_RendererID; }

		private :
			unsigned int GenerateProgram();
			unsigned int GenerateShader(const std::string& shaderFilepath, unsigned int type);

		private :
			unsigned int m_RendererID;
			std::vector<ShaderFiles> m_ShaderFiles;
	};

}