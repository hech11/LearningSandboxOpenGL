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
		template<typename T>
		using EventFnc = std::function<bool(T&)>;

		public :
			EventDispatcher(Event& event) : m_Event(event) {}


			template<typename T, typename F>
			bool Dispatch(EventFnc<T> func) {
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


	
	class MouseButtonEvent : public Event {
		protected :
			MouseButtonEvent(unsigned int button) : m_Button(button) {}
			unsigned int m_Button;
	};



	class MouseButtonPressedEvent : public MouseButtonEvent {
		public :
			MouseButtonPressedEvent(unsigned int button, unsigned int repeatCount) : MouseButtonEvent(button), m_RepeatCount(repeatCount) {}
			inline int GetRepeatCount() const { return m_RepeatCount; }

			EVENT_CLASS_TYPE(MouseButtonPressed);
		private :
			unsigned int m_RepeatCount;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
		public :
			MouseButtonReleasedEvent(unsigned int button) : MouseButtonEvent(button){}

			EVENT_CLASS_TYPE(KeyReleased);
	};



	
	class WindowClosedEvent : public Event {
		public :
			WindowClosedEvent(){}

			EVENT_CLASS_TYPE(WindowClosed)
	};


	class WindowResizeEvent : public Event {
		public:
			WindowResizeEvent(unsigned int width, unsigned int height) {}

			inline unsigned int GetWidth() const { return m_Width; }
			inline unsigned int GetHeight() const { return m_Height; }

			EVENT_CLASS_TYPE(WindowClosed)
		private :
			unsigned int m_Width, m_Height;
	};

	class WindowMovedEvent : public Event {
		public :
			WindowMovedEvent(){}

			inline unsigned int GetXPos() const { return m_xPos; }
			inline unsigned int GetYPos() const { return m_yPos; }

			EVENT_CLASS_TYPE(WindowMoved)
		private :
			unsigned int m_xPos, m_yPos;
	};

	class KeyEvent : public Event {
		protected :
			KeyEvent(unsigned int keycode) : m_KeyCode(keycode) {}
			unsigned int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
		public :
			KeyPressedEvent(unsigned int keycode, unsigned int repeatCount) : KeyEvent(m_KeyCode), m_RepeatCount(repeatCount) {}
			inline int GetRepeatCount() const { return m_RepeatCount; }

			EVENT_CLASS_TYPE(KeyPressed);
		private :
			unsigned int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
		public :
			KeyReleasedEvent(unsigned int keycode) : KeyEvent(m_KeyCode){}

			EVENT_CLASS_TYPE(KeyReleased);
		private :
	};


}