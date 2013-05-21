#pragma once

namespace UI
{
	class Element;
};
namespace UIUtil
{
	// Reset all properties to default.
	void ResetLayout(UI::Element* _Element);
	// Reset a certain property to default.
	void ResetLeft	(UI::Element* _Element);
	void ResetTop	(UI::Element* _Element);
	void ResetRight	(UI::Element* _Element);
	void ResetBottom(UI::Element* _Element);
	void ResetWidth	(UI::Element* _Element);
	void ResetHeight(UI::Element* _Element);
	
	// Builds a window out of the "tl, t, tr, r, br, b, bl, l, c".png images in specified folder.
	void BuildWindow(UI::Element* _Parent, const char* _ImageFolder);

	// Fill target element completely.
	void FillElement(UI::Element* _Element, UI::Element* _ToFill);
	// Fill target element, but without changing aspect ratio.
	void FillElementMaintainAspectRatio(UI::Element* _Element, UI::Element* _ToFill);
	
	// Place a specified distance from specified corner of target element.
	void AtLeftTopIn	 (UI::Element* _ElementToMove, UI::Element* _TargetElement, float _LeftOffset , float _TopOffset);
	void AtRightTopIn	 (UI::Element* _ElementToMove, UI::Element* _TargetElement, float _RightOffset, float _TopOffset);
	void AtLeftBottomIn	 (UI::Element* _ElementToMove, UI::Element* _TargetElement, float _LeftOffset , float _BottomOffset);
	void AtRightBottomIn (UI::Element* _ElementToMove, UI::Element* _TargetElement, float _RightOffset, float _BottomOffset);

	// Place a specified distance from specified side of target element.
	void AtCenterTopIn	 (UI::Element* _ElementToMove, UI::Element* _TargetElement, float _TopOffset);
	void AtCenterBottomIn(UI::Element* _ElementToMove, UI::Element* _TargetElement, float _BottomOffset);
	void AtLeftCenterIn	 (UI::Element* _ElementToMove, UI::Element* _TargetElement, float _LeftOffset);
	void AtRightCenterIn (UI::Element* _ElementToMove, UI::Element* _TargetElement, float _RightOffset);

	// Place in the center of target element.
	void AtCenterIn		 (UI::Element* _ElementToMove, UI::Element* _TargetElement);

	// Set depth to _Amount over parent.
	void DepthOver (UI::Element* _ElementToMove, UI::Element* _TargetElement, int _Amount = 1);
};