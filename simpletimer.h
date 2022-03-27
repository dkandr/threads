#pragma once
#include <iostream>
#include <chrono>

class SimpleTimer
{
public:
	SimpleTimer();
	~SimpleTimer();

private:
	std::chrono::system_clock::time_point start, end;
    std::chrono::duration<float> duration;
};