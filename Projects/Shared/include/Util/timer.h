#pragma once

//#pragma message("Timer.h")

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include <winbase.h>
#include <winnt.h>

class Timer
{
public:
	Timer()	{
				LARGE_INTEGER temp_ticksPS;
				m_StartTime = 0;
				QueryPerformanceFrequency( &temp_ticksPS );
				m_ticksPS = (float) temp_ticksPS.QuadPart / 1000;
				Start();
			}
	void Start()	{
						LARGE_INTEGER startTime;
						QueryPerformanceCounter( &startTime );
						m_StartTime = (float)startTime.QuadPart;
					}
	void Restart()	{	return Start();	}
	float GetPassedTime()	{
								LARGE_INTEGER endTime;
								QueryPerformanceCounter( &endTime );
								return float( endTime.QuadPart - m_StartTime ) / m_ticksPS;
							}

private:
	float m_StartTime, m_ticksPS;
};