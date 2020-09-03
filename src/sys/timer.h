#pragma once

class Timer
{
public:
	Timer();
	void start(bool repeat, double tickTime);
	bool tick();
	void stop();
	bool isActive();
private:
	bool repeat;
	double startTime;
	double tickTime;
	bool active;
};