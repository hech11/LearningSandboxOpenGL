#pragma once


#include "pch.h"

namespace LSO {

	enum class EventType {
		None = -1,
		MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,
		WindowClosed, WindowMoved, WindowResize,
		KeyPressed, KeyReleased
	};



#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }


	class Event {
		public :
			bool Handled = false;

			virtual EventType GetEventType() const = 0;
			virtual const char* GetName() const = 0;
			virtual std::string ToString() const { return GetName(); }

	};

	class EventDispatcher {

		public :
			EventDispatcher(Event& event) : m_Event(event) {}


			template<typename T, typename F>
			bool Dispatch(const F& func) {
				if (m_Event.GetEventType() == T::GetStaticType()) {
					m_Event.Handled = func(static_cast<T&>(m_Event));
					return true;
				}

				return false;
			}

		private :
			Event& m_Event;
	};



	// All events \\

	class MouseMovedEvent : public Event {
		public :
			MouseMovedEvent(unsigned int xpos, unsigned int ypos) : m_xPos(xpos), m_yPos(ypos) {}

			unsigned int GetXPos() const { return m_xPos; }
			unsigned int GetYPos() const { return m_yPos; }


			std::string ToString() const override {
				std::stringstream ss;
				ss << "MouseMovedEvent: xPos: " << m_xPos << ", yPos: " << m_yPos;
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseMoved)

		private :
			unsigned int m_xPos, m_yPos;
	};


	class MouseScrolledEvent : public Event {
		public :
			MouseScrolledEvent(int xscroll, int yscroll) : m_xScroll(xscroll), m_yScroll(yscroll) {}

			float GetXScroll() const { return m_xScroll; }
			float GetYScroll() const { return m_yScroll; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "MouseScrolledEvent: xScroll: " << m_xScroll << ", yScroll: " << m_yScroll;
				return ss.str();
			}


			EVENT_CLASS_TYPE(MouseScrolled)



		private :
			int m_xScroll, m_yScroll;
	};
	
	class MouseButtonEvent : public Event {
		protected :
			MouseButtonEvent(unsigned int button) : m_Button(button) {}
			unsigned int m_Button;
	};



	class MouseButtonPressedEvent : public MouseButtonEvent {
		public :
			MouseButtonPressedEvent(unsigned int button, unsigned int repeatCount) : MouseButtonEvent(button), m_RepeatCount(repeatCount) {}
			inline int GetRepeatCount() const { return m_RepeatCount; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "MouseButtonPressedEvent: Button: " << m_Button << ", RepeatCount: " << m_RepeatCount;
				return ss.str();
			}


			EVENT_CLASS_TYPE(MouseButtonPressed);
		private :
			unsigned int m_RepeatCount;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
		public :
			MouseButtonReleasedEvent(unsigned int button) : MouseButtonEvent(button){}

			std::string ToString() const override {
				std::stringstream ss;
				ss << "MouseButtonReleasedEvent: Button: " << m_Button;
				return ss.str();
			}


			EVENT_CLASS_TYPE(MouseButtonReleased);

		
	};



	
	class WindowClosedEvent : public Event {
		public :
			WindowClosedEvent(){}

			EVENT_CLASS_TYPE(WindowClosed)
	};


	class WindowResizeEvent : public Event {
		public:
			WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

			inline unsigned int GetWidth() const { return m_Width; }
			inline unsigned int GetHeight() const { return m_Height; }


			std::string ToString() const override {
				std::stringstream ss;
				ss << "WindowResizeEvent: Width: " << m_Width << ", Height: " << m_Height;
				return ss.str();
			}


			EVENT_CLASS_TYPE(WindowResize)
		private :
			unsigned int m_Width, m_Height;
	};

	class WindowMovedEvent : public Event {
		public :
			WindowMovedEvent(unsigned int xpos, unsigned int ypos) : m_xPos(xpos), m_yPos(ypos) {}

			inline unsigned int GetXPos() const { return m_xPos; }
			inline unsigned int GetYPos() const { return m_yPos; }


			std::string ToString() const override {
				std::stringstream ss;
				ss << "WindowMovedEvent: xPos: " << m_xPos << ", yPos: " << m_yPos;
				return ss.str();
			}

			EVENT_CLASS_TYPE(WindowMoved)
		private :
			unsigned int m_xPos, m_yPos;
	};

	class KeyEvent : public Event {
		public :
			inline int GetKeyCode() const { return m_KeyCode; }
		protected :
			KeyEvent(int keycode) : m_KeyCode(keycode) {}
			int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
		public :
			KeyPressedEvent(int keycode, unsigned int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
			inline int GetRepeatCount() const { return m_RepeatCount; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "KeyPressedEvent: Button: " << m_KeyCode << ", RepeatCount: " << m_RepeatCount;
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyPressed);
		private :
			unsigned int m_RepeatCount = 0;
	};

	class KeyReleasedEvent : public KeyEvent {
		public :
			KeyReleasedEvent(int keycode) : KeyEvent(keycode){}

			std::string ToString() const override {
				std::stringstream ss;
				ss << "KeyReleasedEvent: Button: " << m_KeyCode;
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyReleased);
	};


}