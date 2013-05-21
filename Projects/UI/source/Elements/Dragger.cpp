#include "UI.h"
#include "Elements\Dragger.h"

UI::Elements::Dragger::Dragger( MouseBtn _MouseBtn )
	: Element(UI::GetRootElement())
{
	m_MouseOver = true;
	OnMouseUp = [=](MouseBtn _Btn)
	{
		DebugCheck(!OnRelease)
			Error("Dragger OnRelease not set.\n");
		if(_Btn == _MouseBtn)
		{
			OnRelease();
			this->Destroy();
			return true;
		}
		return false;
	};
	OnMouseMove = nullptr;
}

void UI::Elements::Dragger::HandleMouseMove( short2 _MousePos )
{
	//if(OnMouseMove)
		OnMouseMove(_MousePos);
}