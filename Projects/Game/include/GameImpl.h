#pragma once

namespace GameImpl
{
	bool Init();
	void Terminate();
	void Tick();
	void Render(float _TickPercent);
};