#include "UIImpl.h"
#include "Elements\Button.h"
#include "UIUtil.h"

// Implement this file to setup the UI in your fork.

void UIImpl::Init(UI::Element* _RootElement)
{
	//UI::Elements::Button* button = new UI::Elements::Button(_RootElement, "UI/Button.png");
	//UIUtil::AtLeftTopIn(button, _RootElement, 100, 100);
	//UIUtil::DepthOverParent(button, _RootElement);
}

void UIImpl::Terminate()
{
}

void UIImpl::HandleKeyDown(Key _Key)
{
}

void UIImpl::HandleKeyUp(Key _Key)
{
}

void UIImpl::HandleMouseBtnDown(MouseBtn _MouseBtn, short2 _MousePos)
{
}

void UIImpl::HandleMouseBtnUp(MouseBtn _MouseBtn, short2 _MousePos)
{
}

void UIImpl::HandleMouseMove(short2 _MousePos)
{
}