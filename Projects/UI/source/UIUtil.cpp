#include "UIUtil.h"
#include "Elements\Bitmap.h"
#include "Element.h"


void UIUtil::ResetLayout( UI::Element* _Element )
{
	UIUtil::ResetLeft(_Element);
	UIUtil::ResetTop(_Element);
	UIUtil::ResetRight(_Element);
	UIUtil::ResetBottom(_Element);
	UIUtil::ResetWidth(_Element);
	UIUtil::ResetHeight(_Element);
}

void UIUtil::ResetLeft(UI::Element* _Element)		{	_Element->m_Left =		[_Element](){	return _Element->m_Right() - _Element->m_Width();	};	}
void UIUtil::ResetTop(UI::Element* _Element)		{	_Element->m_Top =		[_Element](){	return _Element->m_Bottom() - _Element->m_Height();	};	}
void UIUtil::ResetRight(UI::Element* _Element)	{	_Element->m_Right =		[_Element](){	return _Element->m_Left() + _Element->m_Width();	};	}
void UIUtil::ResetBottom(UI::Element* _Element)	{	_Element->m_Bottom =	[_Element](){	return _Element->m_Top() + _Element->m_Height();	};	}
void UIUtil::ResetWidth(UI::Element* _Element)	{	_Element->m_Width =		[_Element](){	return _Element->m_Right() - _Element->m_Left();	};	}
void UIUtil::ResetHeight(UI::Element* _Element)	{	_Element->m_Height =	[_Element](){	return _Element->m_Bottom() - _Element->m_Top();	};	}

void UIUtil::FillElement( UI::Element* _Element, UI::Element* _ToFill )
{
	UIUtil::ResetWidth(_Element);
	UIUtil::ResetHeight(_Element);
	_Element->m_Left =		[_ToFill](){	return _ToFill->m_Left();	};
	_Element->m_Top =		[_ToFill](){	return _ToFill->m_Top();	};
	_Element->m_Right =		[_ToFill](){	return _ToFill->m_Right();	};
	_Element->m_Bottom =	[_ToFill](){	return _ToFill->m_Bottom();	};
}

void UIUtil::FillElementMaintainAspectRatio( UI::Element* _Element, UI::Element* _ToFill )
{

}

void UIUtil::BuildWindow(UI::Element* _Parent, const char* _ImageFolder)
{
	char path[128];
	sprintf_s(path, "%s/tl.png", _ImageFolder);
	UI::Elements::Bitmap* tl = new UI::Elements::Bitmap(_Parent, path);
	tl->m_Left =	[=](){	return _Parent->m_Left();		};
	tl->m_Top =		[=](){	return _Parent->m_Top();		};
	sprintf_s(path, "%s/tr.png", _ImageFolder);
	UI::Elements::Bitmap* tr = new UI::Elements::Bitmap(_Parent, path);
	tr->m_Right =	[=](){	return _Parent->m_Right();		};
	tr->m_Top =		[=](){	return _Parent->m_Top();		};
	sprintf_s(path, "%s/bl.png", _ImageFolder);
	UI::Elements::Bitmap* bl = new UI::Elements::Bitmap(_Parent, path);
	bl->m_Left =	[=](){	return _Parent->m_Left();		};
	bl->m_Bottom =	[=](){	return _Parent->m_Bottom();		};
	sprintf_s(path, "%s/br.png", _ImageFolder);
	UI::Elements::Bitmap* br = new UI::Elements::Bitmap(_Parent, path);
	br->m_Right =	[=](){	return _Parent->m_Right();		};
	br->m_Bottom =	[=](){	return _Parent->m_Bottom();		};
	sprintf_s(path, "%s/l.png", _ImageFolder);
	UI::Elements::Bitmap* l = new UI::Elements::Bitmap(_Parent, path);
	l->m_Left =		[=](){	return _Parent->m_Left();		};
	l->m_Top =		[=](){	return tl->m_Bottom();			};
	l->m_Bottom =	[=](){	return bl->m_Top();				};
	UIUtil::ResetHeight(l);
	
	sprintf_s(path, "%s/r.png", _ImageFolder);
	UI::Elements::Bitmap* r = new UI::Elements::Bitmap(_Parent, path);
	r->m_Right =	[=](){	return _Parent->m_Right();		};
	r->m_Top =		[=](){	return tr->m_Bottom();			};
	r->m_Bottom =	[=](){	return br->m_Top();				};
	UIUtil::ResetHeight(r);
	sprintf_s(path, "%s/t.png", _ImageFolder);
	UI::Elements::Bitmap* t = new UI::Elements::Bitmap(_Parent, path);
	t->m_Top =		[=](){	return _Parent->m_Top();		};
	t->m_Left =		[=](){	return tl->m_Right();			};
	t->m_Right =	[=](){	return tr->m_Left();			};
	UIUtil::ResetWidth(t);
	sprintf_s(path, "%s/b.png", _ImageFolder);
	UI::Elements::Bitmap* b = new UI::Elements::Bitmap(_Parent, path);
	b->m_Bottom =	[=](){	return _Parent->m_Bottom();		};
	b->m_Left =		[=](){	return bl->m_Right();			};
	b->m_Right =	[=](){	return br->m_Left();			};
	UIUtil::ResetWidth(b);
	
	sprintf_s(path, "%s/c.png", _ImageFolder);
	UI::Elements::Bitmap* c = new UI::Elements::Bitmap(_Parent, path);
	c->m_Left =		[=](){	return l->m_Right();			};
	c->m_Top =		[=](){	return t->m_Bottom();			};
	c->m_Right =	[=](){	return r->m_Left();				};
	c->m_Bottom =	[=](){	return b->m_Top();				};
	UIUtil::ResetWidth(c); UIUtil::ResetHeight(c);
}

void UIUtil::AtLeftTopIn( UI::Element* _ElementToMove, UI::Element* _TargetElement, float _LeftOffset, float _TopOffset )
{
	_ElementToMove->m_Left =	[=](){	return _TargetElement->m_Left() + _LeftOffset;		};
	_ElementToMove->m_Top =		[=](){	return _TargetElement->m_Top() + _TopOffset;		};
}

void UIUtil::AtRightTopIn( UI::Element* _ElementToMove, UI::Element* _TargetElement, float _RightOffset, float _TopOffset )
{
	_ElementToMove->m_Right =	[=](){	return _TargetElement->m_Right() - _RightOffset;	};
	_ElementToMove->m_Top =		[=](){	return _TargetElement->m_Top() + _TopOffset;		};
}

void UIUtil::AtLeftBottomIn( UI::Element* _ElementToMove, UI::Element* _TargetElement, float _LeftOffset, float _BottomOffset )
{
	_ElementToMove->m_Left =	[=](){	return _TargetElement->m_Left() + _LeftOffset;		};
	_ElementToMove->m_Bottom =	[=](){	return _TargetElement->m_Bottom() - _BottomOffset;	};
}

void UIUtil::AtRightBottomIn( UI::Element* _ElementToMove, UI::Element* _TargetElement, float _RightOffset, float _BottomOffset )
{
	_ElementToMove->m_Right =	[=](){	return _TargetElement->m_Right() - _RightOffset;	};
	_ElementToMove->m_Bottom =	[=](){	return _TargetElement->m_Bottom() - _BottomOffset;	};
}

void UIUtil::AtCenterTopIn( UI::Element* _ElementToMove, UI::Element* _TargetElement, float _TopOffset )
{
	_ElementToMove->m_Left =	[=](){	return _TargetElement->m_Left() + _TargetElement->m_Width()/2 - _ElementToMove->m_Width()/2;	};
	_ElementToMove->m_Top =		[=](){	return _TargetElement->m_Top() + _TopOffset;													};
}

void UIUtil::AtCenterBottomIn( UI::Element* _ElementToMove, UI::Element* _TargetElement, float _BottomOffset )
{
	_ElementToMove->m_Left =	[=](){	return _TargetElement->m_Left() + _TargetElement->m_Width()/2 - _ElementToMove->m_Width()/2;	};
	_ElementToMove->m_Bottom =	[=](){	return _TargetElement->m_Bottom() - _BottomOffset;												};
}

void UIUtil::AtLeftCenterIn( UI::Element* _ElementToMove, UI::Element* _TargetElement, float _LeftOffset )
{
	_ElementToMove->m_Left =	[=](){	return _TargetElement->m_Left() + _LeftOffset;													};
	_ElementToMove->m_Top =		[=](){	return _TargetElement->m_Top() + _TargetElement->m_Height()/2 - _ElementToMove->m_Height()/2;	};
}

void UIUtil::AtRightCenterIn( UI::Element* _ElementToMove, UI::Element* _TargetElement, float _RightOffset )
{
	_ElementToMove->m_Right =	[=](){	return _TargetElement->m_Right() - _RightOffset;												};
	_ElementToMove->m_Top =		[=](){	return _TargetElement->m_Top() + _TargetElement->m_Height()/2 - _ElementToMove->m_Height()/2;	};
}

void UIUtil::AtCenterIn( UI::Element* _ElementToMove, UI::Element* _TargetElement )
{
	_ElementToMove->m_Left =	[=](){	return _TargetElement->m_Left() + _TargetElement->m_Width()/2 - _ElementToMove->m_Width()/2;	};
	_ElementToMove->m_Top =		[=](){	return _TargetElement->m_Top() + _TargetElement->m_Height()/2 - _ElementToMove->m_Height()/2;	};
}

void UIUtil::DepthOver( UI::Element* _ElementToMove, UI::Element* _TargetElement, int _Amount /* = 1 */ )
{
	_ElementToMove->m_Depth =	[=](){	return _TargetElement->m_Depth() + _Amount;	};
}