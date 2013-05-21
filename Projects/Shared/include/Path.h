#pragma once

class Path
{
public:
	Path() : m_CurPosition(0)	{}

	std::vector<float2> m_Positions;
	int m_CurPosition;

	float m_NodeRadius;
};