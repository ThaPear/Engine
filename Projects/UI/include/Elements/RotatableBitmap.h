#pragma once
#include "Elements\Bitmap.h"

namespace UI
{
	namespace Elements
	{
		class RotatableBitmap : public UI::Elements::Bitmap
		{
		public:
			RotatableBitmap(UI::Element* _Parent, const char* _ImagePath, unsigned int _NumFrames = 1);

			virtual void _Render();

			std::function<float()> m_Rotation;
		};
	};
};