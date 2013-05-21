#pragma once
#include "Element.h"

namespace UI
{
	namespace Elements
	{
		class Dragger : public UI::Element
		{
		public:
			Dragger(MouseBtn _MouseBtn);

			virtual void HandleMouseMove(short2 _MousePos);

			std::function<void(short2 _MousePos)> OnMouseMove;
			std::function<void()> OnRelease;
		};
	};
};