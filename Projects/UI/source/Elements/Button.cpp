#include "DllAPIs\Renderer.h"
#include "Elements\Dragger.h"
#include "Elements\Button.h"


UI::Elements::Button::Button( UI::Element* _Parent, const char* _ImagePath )
	: Bitmap(_Parent, _ImagePath, 3)
	, m_Dragger(nullptr)
{
	OnMouseEnter =	[this]()
	{
		if(m_Dragger == nullptr)
		{
			m_CurFrame = 1;
		}
	};
	OnMouseExit =	[this]()
	{
		if(m_Dragger == nullptr)
		{
			m_CurFrame = 0;
		}
	};
	OnMouseDown =	[this](MouseBtn _MouseBtn)
	{
		m_CurFrame = 2;
		m_Dragger = new UI::Elements::Dragger(_MouseBtn);
		m_Dragger->OnRelease = [_MouseBtn,this]()
		{
			if(m_MouseOver)
			{
				this->OnClick(_MouseBtn);
				m_CurFrame = 1;
			}
			m_Dragger = nullptr;
		};
		m_Dragger->OnMouseMove = [this](short2 _MousePos)
		{
			m_CurFrame = m_MouseOver?2:0;
		};
		return true;
	};

	OnClick = [](MouseBtn _MouseBtn){};
}