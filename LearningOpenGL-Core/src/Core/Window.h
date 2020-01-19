#pragma once

#include "pch.h"
#include "Event.h"


struct GLFWwindow;
namespace LSO {


	struct WindowProperties {
		unsigned int Width, Height, xPos, yPos;
		std::string Title;
		bool Vsync;

		WindowProperties(unsigned int width = 1280, unsigned int height = 720, unsigned int xpos = 50, unsigned int ypos = 50,
			std::string title = "Learning OpenGL", bool vsync = true)
			: Width(width), Height(height), xPos(xpos), yPos(ypos), Title(title), Vsync(vsync)
		{

		}
	};
	class Window {
		public :
			using EventCallbackFncPtr = std::function<void(Event&)>;

			Window(const WindowProperties& props = WindowProperties());
			~Window();

			void StartUp(const WindowProperties& props);
			void Shutdown();

			void SetEventCallback(const EventCallbackFncPtr& eventCallback) { m_Data.EventCallback = eventCallback; }

			void SetVsync(bool enable);

			void OnUpdate();

			unsigned int GetWidth() const { return m_Data.Props.Width; }
			unsigned int GetHeight() const { return m_Data.Props.Height; }
			std::pair<unsigned int, unsigned int>& GetDimensions() { return std::make_pair(GetWidth(), GetHeight()); }

			unsigned int GetXpos() const { return m_Data.Props.xPos; }
			unsigned int GetYpos() const { return m_Data.Props.yPos; }
			std::pair<unsigned int, unsigned int>& GetPosition() { return std::make_pair(GetXpos(), GetYpos()); }


		private :
			GLFWwindow* m_Window;

			struct WindowData {
				WindowProperties Props;
				bool Vsync;

				EventCallbackFncPtr EventCallback;
			};

			WindowData m_Data;

			
	};

}