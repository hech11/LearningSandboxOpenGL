#pragma once

#include "GLFW/glfw3.h"
#include "Application.h"


namespace LSO {

	class Input {
		public :
		static bool GetKey(int keycode)
		{
			auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
			return (glfwGetKey(window, keycode) == GLFW_PRESS);
		}

		static bool GetMouseButton(int button)
		{
			auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
			return (glfwGetMouseButton(window, button) == GLFW_PRESS);
		}

		static std::pair<double, double> GetMousePosition()
		{
			auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			return std::make_pair(x, y);
		}

	};
}