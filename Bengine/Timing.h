#pragma once

#include<SDL/SDL.h>

namespace Bengine {
	class FpsLimiter {
	public:
		FpsLimiter();
		void init(float maxFPS);

		void setMaxFPS(float targetFPS);

		void begin();

		//end will return the current fps
		int end();

	private:
		void calculateFPS();

		float _fps;
		float _frameTime;
		float _maxFPS;
		unsigned int _startTicks;

	};
}
