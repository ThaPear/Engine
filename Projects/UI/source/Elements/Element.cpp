#include "Element.h"
#include "UIUtil.h"

#define ExpandMacro(a) a
// TODO: Think of a way where this does not give problems when a child that hasn't been used yet is removed.
// Executes _CodePerChild for each child where m_Children[i]->m_Depth() > m_Depth().
// Then executes _CodeForSelf.
// Then executes _CodePerChild for the rest of the children.
// i is the index of the current child.
#define DeeperChildrenFirst(_CodePerChild, _CodeForSelf)	unsigned int numChildren = m_Children.size();					\
															unsigned int i = 0;												\
															for(; i < numChildren; ++i)										\
															{																\
																if(m_Children[i]->m_Depth() > m_Depth())					\
																	break;													\
																{_CodePerChild}												\
																const int childrenLost = numChildren - m_Children.size();	\
																numChildren = m_Children.size();							\
																i -= childrenLost;											\
															}																\
															_CodeForSelf													\
															for(; i < numChildren; ++i)										\
															{																\
																{_CodePerChild}												\
																const int childrenLost = numChildren - m_Children.size();	\
																numChildren = m_Children.size();							\
																i -= childrenLost;											\
															}

UI::Element::Element(Element* _Parent)
	: m_Parent(nullptr)
	, m_NeedsFrameUpdate(false)
	, m_NeedsHitTest(true)
	, m_Hidden(false)
	, m_MouseOver(false)
{
	UIUtil::ResetLayout(this);
	m_Depth =		[](){	return 0;		};

	OnMouseDown =	nullptr;
	OnMouseUp =		nullptr;
	OnMouseEnter =	nullptr;
	OnMouseExit =	nullptr;
	
	this->SetParent(_Parent);
}

void UI::Element::Destroy()
{
	int m_NumChildren = m_Children.size();
	for(int i = 0; i < m_NumChildren; ++i)
	{
		m_Children[m_Children.size() - 1]->Destroy();
	}
	if(m_Parent != nullptr)
		m_Parent->RemoveChild(this);
	delete this;
}

void UI::Element::Render( float _LastFrameTime )
{
	DeeperChildrenFirst(
		ExpandMacro(
			if(!m_Children[i]->IsHidden())
			{
				m_Children[i]->Render(_LastFrameTime);
			}),
		ExpandMacro(
			if(m_NeedsFrameUpdate)
				this->m_FrameUpdate(_LastFrameTime);
			this->_Render();
		)
	)
}

void UI::Element::_Render()
{
}

void UI::Element::SetParent( Element* _Parent )
{
	if(m_Parent != nullptr)
		m_Parent->RemoveChild(this);

	m_Parent = _Parent;

	if(m_Parent != nullptr)
		m_Parent->AddChild(this);
}

void UI::Element::AddChild( Element* _Child )
{
	m_Children.push_back(_Child);
	// TODO: Decide whether or not to sort every frame, in case of depth changes.
	std::sort(m_Children.begin(), m_Children.end(), [](const UI::Element* _Child1, const UI::Element* _Child2)	{	return _Child1->m_Depth() < _Child2->m_Depth();	});
}

void UI::Element::RemoveChild( Element* _Child )
{
	for(auto childIt = m_Children.begin(); childIt != m_Children.end(); ++childIt)
	{
		if((*childIt) == _Child)
		{
			m_Children.erase(childIt);
			return;
		}
	}
}

UI::Element* UI::Element::GetParent()							{	return m_Parent;						}
const std::vector<UI::Element*>& UI::Element::GetChildren()		{	return m_Children;						}
void UI::Element::SetNeedsFrameUpdate( bool _NeedsFrameUpdate )	{	m_NeedsFrameUpdate = _NeedsFrameUpdate;	}
void UI::Element::DisableHitTest()								{	m_NeedsHitTest = false;					}
void UI::Element::EnableHitTest()								{	m_NeedsHitTest = true;					}
void UI::Element::Hide()										{	m_Hidden = true;						}
void UI::Element::Show()										{	m_Hidden = false;						}
bool UI::Element::IsHidden()									{	return m_Hidden;						}

bool UI::Element::HandleMouseBtnDown( MouseBtn _MouseBtn )
{
	DeeperChildrenFirst(
		ExpandMacro(
			if(!m_Children[i]->IsHidden() && m_Children[i]->m_NeedsHitTest)
			{
				if(m_Children[i]->m_MouseOver)
					if(m_Children[i]->HandleMouseBtnDown(_MouseBtn))
						return true;
			}),
		ExpandMacro(
			if(this->OnMouseDown && this->OnMouseDown(_MouseBtn))
				return true;
		)
	)
	return false;
}

bool UI::Element::HandleMouseBtnUp( MouseBtn _MouseBtn )
{
	DeeperChildrenFirst(
		ExpandMacro(
			if(!m_Children[i]->IsHidden() && m_Children[i]->m_NeedsHitTest)
			{
				if(m_Children[i]->m_MouseOver)
					if(m_Children[i]->HandleMouseBtnUp(_MouseBtn))
						return true;
			}),
		ExpandMacro(
			if(this->OnMouseUp && this->OnMouseUp(_MouseBtn))
				return true;
		)
	)
	return false;
}

void UI::Element::HandleMouseMove( short2 _MousePos )
{
	DeeperChildrenFirst(
		ExpandMacro(
			if(!m_Children[i]->IsHidden() && m_Children[i]->m_NeedsHitTest)
			{
				m_Children[i]->HandleMouseMove(_MousePos);
			}),
		ExpandMacro(
			if(	_MousePos.x > m_Left() && _MousePos.x < m_Right() && 
				_MousePos.y > m_Top() && _MousePos.y < m_Bottom())
			{
				if(!m_MouseOver && OnMouseEnter)
					OnMouseEnter();
				m_MouseOver = true;
			}
			else
			{
				if(m_MouseOver && OnMouseExit)
					OnMouseExit();
				m_MouseOver = false;
			}
		)
	)
		
}