#include "DllAPIs\Renderer.h"
#include "Elements\RotatableBitmap.h"


UI::Elements::RotatableBitmap::RotatableBitmap( UI::Element* _Parent, const char* _ImagePath, unsigned int _NumFrames /*= 1*/ )
	: Bitmap(_Parent, _ImagePath, _NumFrames)
{
	m_Rotation = [](){	return 0.0f;	};
}

void UI::Elements::RotatableBitmap::_Render()
{
	Renderer::RenderImage(	m_Image, m_CurFrame,
							float2(	m_Left(), 
									m_Top()),
							float2(	m_Width(), 
									m_Height()),
							m_Rotation()
						 );
}