#pragma once
#include "pch.h"


namespace LSO {
	class Random {

		public :
			static float RandonRange(float low, float high) {
				std::mt19937 eng(m_Rd());
				std::uniform_real_distribution<> dist(low, high);

				return dist(eng);
			}

			static int RandonRange(int low, int high) {
				std::mt19937 eng(m_Rd());
				std::uniform_int_distribution<> dist(low, high);

				return dist(eng);
			}

		private :
			static std::random_device m_Rd;
	};
}