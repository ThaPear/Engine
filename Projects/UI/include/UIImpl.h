#pragma once

namespace UI
{
	class Element;
};
namespace UIImpl
{
	void Init(UI::Element* _RootElement);
	void Terminate();

	void HandleKeyDown(Key _Key);
	void HandleKeyUp(Key _Key);
	void HandleMouseBtnDown(MouseBtn _MouseBtn, short2 _MousePos);
	void HandleMouseBtnUp(MouseBtn _MouseBtn, short2 _MousePos);
	void HandleMouseMove(short2 _MousePos);
};