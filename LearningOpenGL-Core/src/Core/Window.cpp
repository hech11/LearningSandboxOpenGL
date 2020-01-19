#include "pch.h"
#include "Window.h"

#include <GLFW/include/GLFW/glfw3.h>
#include "Utility/Log.h"


namespace LSO {



	Window::Window(const WindowProperties& props) {
		StartUp(props);
	}

	Window::~Window() {
		Shutdown();
	}

	void Window::StartUp(const WindowProperties& props) {
		m_Data.props = props;
		
		int glfwValidation = glfwInit();
		LSO_ASSERT(glfwValidation, "Failed to init glfw!");

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
		LSO_ASSERT(m_Window, "Failed to create the window!");

		glfwMakeContextCurrent(m_Window);
		// init glad here

		// init glfw events here

	}

	void Window::Shutdown() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::SetVsync(bool enable) {
		m_Data.Vsync = enable;
		if (enable) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
	}

	void Window::OnUpdate() {
		glfwSwapBuffers(m_Window);
	}


}