#include "system.h"

void Frame::start()
{
	/*
	currentTime = SDL_GetTicks();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
	*/
	QueryPerformanceCounter(&currentTime);
	deltaTime.QuadPart = currentTime.QuadPart - previousTime.QuadPart;
	previousTime = currentTime;
	deltaTime.QuadPart *= 1000000;
	delta = (double)(deltaTime.QuadPart / frequency.QuadPart);


}

void Frame::init()
{
	frames = 0;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previousTime);
	//previousTime = SDL_GetTicks();
	QueryPerformanceCounter(&currentTime);
	deltaTime.QuadPart = currentTime.QuadPart - previousTime.QuadPart;
	previousTime = currentTime;
	deltaTime.QuadPart *= 1000000;
	delta = (double)(deltaTime.QuadPart / frequency.QuadPart);
	//SDL_Delay(10);
	capTimer.start(true,16.6666);
}

Uint32 Frame::getFrame()
{
	return frames;
}

double Frame::getDelta()
{
	return delta / 1000.0;
}

LARGE_INTEGER Frame::getTimeRaw()
{
	return currentTime;
}

double Frame::getTime()
{
	LARGE_INTEGER temp = currentTime;
	temp.QuadPart *= 1000000;
	double t = (double)(temp.QuadPart / frequency.QuadPart);
	return t;
}

float Frame::getTime_s()
{
	return (float)(getTime() / 1000000.0);
}

void Frame::end()
{
	static int counter = 1;
	static double displayResult = 0.0;
	double result = (1.0 / (deltaTime.QuadPart / frequency.QuadPart)) * 1000000.0;

	if (counter == 1)
	{
		displayResult = result;
		counter++;
	}
	else if (counter == 30)
	{
		displayResult = displayResult + ((result - displayResult) / (double)counter);
		//res.loadText("fps", util::va("FPS: %.0f", displayResult), 32, 0, 1080 - 32);
		counter = 1;
	}
	else
	{
		displayResult = displayResult + ((result - displayResult) / (double)counter);
		counter++;
	}
	
}

void Frame::end_f()
{
	frames++;
}