#pragma once

namespace Input
{
	struct KeyAction
	{
		typedef std::function<void(Key)> pKeyActionFunc;
		KeyAction()													  : OnKeyDown([](Key){}), OnKeyUp([](Key){}) {}
		KeyAction(pKeyActionFunc _OnKeyDown, pKeyActionFunc _OnKeyUp) : OnKeyDown(_OnKeyDown), OnKeyUp(_OnKeyUp) {}
		pKeyActionFunc OnKeyDown;
		pKeyActionFunc OnKeyUp;
	};
	struct MouseBtnAction
	{
		typedef std::function<void(MouseBtn, short2)> pMouseBtnActionFunc;
		MouseBtnAction()	: OnMouseBtnDown([](MouseBtn, short2){}), OnMouseBtnUp([](MouseBtn, short2){}) {}
		MouseBtnAction(pMouseBtnActionFunc _OnMouseBtnDown, pMouseBtnActionFunc _OnMouseBtnUp) 
							: OnMouseBtnDown(_OnMouseBtnDown), OnMouseBtnUp(_OnMouseBtnUp) {}
		pMouseBtnActionFunc OnMouseBtnDown;
		pMouseBtnActionFunc OnMouseBtnUp;
	};

	void OnKeyDown(Key _Key);
	void OnKeyUp(Key _Key);
	void OnMouseBtnDown(MouseBtn _MouseBtn);
	void OnMouseBtnUp(MouseBtn _MouseBtn);
	void OnMouseMove(short2 _OldPos);

	KeyAction m_KeyActions[Key::KeyMax];
	bool m_KeyStates[Key::KeyMax];

	MouseBtnAction m_MouseBtnActions[MouseBtn::KeyMax];
	bool m_MouseBtnStates[MouseBtn::KeyMax];

	std::function<void(short2)> m_OnMouseMove;

	short2 m_MousePos;
};