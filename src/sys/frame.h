#pragma once

class Frame
{
private:
	LARGE_INTEGER currentTime, previousTime, deltaTime;
	LARGE_INTEGER frequency;
	Uint32 frames;
	double delta;
public:
	void start();
	void end();
	void end_f();
	void init();
	double getDelta();
	LARGE_INTEGER getTimeRaw();
	double getTime();
	float getTime_s();
	Uint32 getFrame();
	Timer capTimer;
};