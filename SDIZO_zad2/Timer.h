#pragma once
class Timer
{
private:
	double frequenct = 0.0;
	__int64 counterstart = 0;
public:
	void startCounter();

	double getCounter();

	Timer();

	~Timer();
};

