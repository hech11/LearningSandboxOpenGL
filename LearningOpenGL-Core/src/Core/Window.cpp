#include "pch.h"
#include "Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Utility/Log.h"

#include "Event.h"


namespace LSO {



	Window::Window(const WindowProperties& props) {
		StartUp(props);
	}

	Window::~Window() {
		Shutdown();
	}

	void Window::StartUp(const WindowProperties& props) {
		m_Data.Props = props;
		
		int glfwValidation = glfwInit();
		LSO_ASSERT(glfwValidation, "Failed to init glfw!");

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
		LSO_ASSERT(m_Window, "Failed to create the window!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		glfwMakeContextCurrent(m_Window);
		// init glad here
		int gladValidation = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LSO_ASSERT(gladValidation, "Falied to init glad!");

		LSO_CORE_INFO("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
		LSO_CORE_INFO("OpenGL Version: %s\n", glGetString(GL_VERSION));

		// init glfw events here
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent e((int)xpos, (int)ypos);
			data.EventCallback(e);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xscroll, double yscroll) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent e((int)xscroll, (int)yscroll);
			data.EventCallback(e);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mod) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS :
				{
					MouseButtonPressedEvent e(button, 0);
					data.EventCallback(e);
					break;
				}

				case GLFW_REPEAT :
				{
					MouseButtonPressedEvent e(button, 1);
					data.EventCallback(e);
					break;
				}

				case GLFW_RELEASE :
				{
					MouseButtonReleasedEvent e(button);
					data.EventCallback(e);
					break;
				}
			}
		});


		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowClosedEvent e;
			data.EventCallback(e);
		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Props.xPos = xpos;
			data.Props.yPos = ypos;

			WindowMovedEvent e(xpos, ypos);
			data.EventCallback(e);
		});
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Props.Width = width;
			data.Props.Height = height;

			WindowResizeEvent e(width, height);
			data.EventCallback(e);
		});


		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancoode, int action, int mod) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data.EventCallback(e);
					break;
				}

				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1);
					data.EventCallback(e);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.EventCallback(e);
					break;
				}
			}
		});


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
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}


}