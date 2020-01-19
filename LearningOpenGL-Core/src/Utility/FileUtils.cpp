#include "pch.h"
#include "FileUtils.h"

#include "Log.h"

namespace LSO {



	std::string& ReadFile(const std::string& filepath)
	{
		std::string line;
		std::ifstream file(filepath, std::ios::binary);

		if (!file.fail()) {
			LSO_CORE_WARN("File at '%s' does not exist!", filepath.c_str());
			return std::string("File does not exist!");
		}

		std::stringstream ss;

		while (getline(file, line)) {
			ss << line << '\n';
		}

		return ss.str();

	}

}