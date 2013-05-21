#pragma once
#include "Elements\Bitmap.h"

namespace UI
{
	namespace Elements
	{
		class Dragger;
		class Button : public UI::Elements::Bitmap
		{
		public:
			// _ImagePath should be an image with 3 frames: Normal, MouseOver, MouseDown
			Button(UI::Element* _Parent, const char* _ImagePath);

			std::function<void(MouseBtn _MouseBtn)> OnClick;

			UI::Elements::Dragger* m_Dragger;
		};
	};
};