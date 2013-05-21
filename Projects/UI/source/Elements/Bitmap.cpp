#include "DllAPIs\Renderer.h"
#include "Elements\Bitmap.h"

UI::Elements::Bitmap::Bitmap( Element* _Parent, const char* _ImagePath, unsigned int _NumFrames /* = 1*/ )
	: Element(_Parent)
	, m_CurFrame(0)
{
	if(_ImagePath != nullptr)
	{
		this->SetImage(_ImagePath, _NumFrames);
	}
	else
	{
		m_Width =  [=](){	return 0.0f;	};
		m_Height = [=](){	return 0.0f;	};
	}
}

void UI::Elements::Bitmap::SetImage( const char* _ImagePath, unsigned int _NumFrames /* = 1*/ )
{
	Image* image = Renderer::LoadImageFromFile(_ImagePath, _NumFrames);
	Renderer::SetNearestMinMagFilters(image);
	this->SetImage(image);
}

void UI::Elements::Bitmap::SetImage( Image* _Image )
{
	m_Image = _Image;
	float2 dimensions = (float2)Renderer::GetImageDimensions(m_Image);
	m_Width = [=](){	return dimensions.x;	};
	m_Height = [=](){	return dimensions.y;	};
}

void UI::Elements::Bitmap::_Render()
{
	Renderer::RenderImage(	m_Image, m_CurFrame,
							float2(	m_Left(), 
									m_Top()),
							float2(	m_Width(), 
									m_Height())
						 );
}