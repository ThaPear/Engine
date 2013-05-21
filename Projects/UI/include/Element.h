#pragma once

namespace UI
{
	class Element
	{
	public:
		Element(UI::Element* _Parent);
		void Destroy();

		void Render(float _LastFrameTime);
		virtual void _Render();

		void SetParent(UI::Element* _Parent);
		void AddChild(UI::Element* _Child);
		void RemoveChild(UI::Element* _Child);
		UI::Element* GetParent();
		const std::vector<UI::Element*>& GetChildren();

		void SetNeedsFrameUpdate(bool _NeedsFrameUpdate);
		void DisableHitTest();
		void EnableHitTest();

		void Hide();
		void Show();
		bool IsHidden();


		
		bool HandleMouseBtnDown(MouseBtn _MouseBtn);
		bool HandleMouseBtnUp(MouseBtn _MouseBtn);
		virtual void HandleMouseMove(short2 _MousePos);
		
		std::function<float()> m_Left, m_Top, m_Right, m_Bottom, m_Width, m_Height;
		std::function<int()> m_Depth;
		std::function<void(float _DT)> m_FrameUpdate;

		std::function<bool(MouseBtn _MouseBtn)> OnMouseDown;
		std::function<bool(MouseBtn _MouseBtn)> OnMouseUp;
		std::function<void()> OnMouseExit;
		std::function<void()> OnMouseEnter;
	protected:
		UI::Element* m_Parent;
		std::vector<UI::Element*> m_Children;

		bool m_NeedsFrameUpdate;
		bool m_NeedsHitTest;
		bool m_MouseOver;
		bool m_Hidden;
	};
};