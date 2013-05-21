#pragma once
#include "Element.h"

class Image;
namespace UI
{
	namespace Elements
	{
		class Bitmap : public UI::Element
		{
		public:
			Bitmap(Element* _Parent, const char* _ImagePath, unsigned int _NumFrames = 1);

			void SetImage(const char* _ImagePath, unsigned int _NumFrames = 1);
			void SetImage(Image* _Image);

			virtual void _Render();

			Image* m_Image;
			unsigned int m_CurFrame;
		};
	};
};