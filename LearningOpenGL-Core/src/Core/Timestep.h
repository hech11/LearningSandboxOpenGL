#pragma once

namespace LSO {

	class Timestep {

		public :
			Timestep(float time = 0.0f) : m_Timer(time){}
			operator float() const { return m_Timer; }

			float GetSeconds() const { return m_Timer; }
			float GetMilliseconds() const { return m_Timer * 1000.0f; }

		private :
			float m_Timer;
	};

}