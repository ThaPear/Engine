#include "DllAPIs\Game.h"
#include "DllAPIs\Renderer.h"
#include "DllAPIs\Input.h"

#define DllExport
#include "DllAPIs\UI.h"

#include "UI.h"
#include "UIUtil.h"

#include "Element.h"
#include "UIImpl.h"

namespace UI
{
	UI::Element* m_RootElement;
}

///////////////////////////////////////////////////////////
//        ///  //////  /        ///  ///////  ///        //
//  //////  /  //////  /  //////  /  ///////  /  //////////
//        ///  //////  /        ///  ///////  /  //////////
//  /////////  //////  /  //////  /  ///////  /  //////////
//  ///////////      ///        ///        /  ///        //
///////////////////////////////////////////////////////////
bool UI::Init()
{
	PrintFuncEntry();

	UI::m_RootElement = new UI::Element(nullptr);
	UI::m_RootElement->m_Left = [](){	return 0.0f;					};
	UI::m_RootElement->m_Top = [](){	return 0.0f;					};
	UI::m_RootElement->m_Width = [](){	return (float)g_ScreenSize.x;	};
	UI::m_RootElement->m_Height = [](){	return (float)g_ScreenSize.y;	};

	UIImpl::Init(UI::m_RootElement);
		
	return true;
}

void UI::Terminate()
{
	PrintFuncEntry();
	
	UI::m_RootElement->Destroy();

	UIImpl::Terminate();
}

void UI::Render(float _LastFrameTime)
{
	//PrintFuncEntry();
	UI::m_RootElement->Render(_LastFrameTime);
}

void UI::HandleKeyDown(Key _Key)
{
	UIImpl::HandleKeyDown(_Key);
}

void UI::HandleKeyUp(Key _Key)
{
	UIImpl::HandleKeyUp(_Key);
}

void UI::HandleMouseBtnDown(MouseBtn _MouseBtn, short2 _MousePos)
{
	if(!UI::m_RootElement->HandleMouseBtnDown(_MouseBtn))
		UIImpl::HandleMouseBtnDown(_MouseBtn, _MousePos);
}

void UI::HandleMouseBtnUp(MouseBtn _MouseBtn, short2 _MousePos)
{
	if(!UI::m_RootElement->HandleMouseBtnUp(_MouseBtn))
		UIImpl::HandleMouseBtnUp(_MouseBtn, _MousePos);
}

void UI::HandleMouseMove(short2 _MousePos)
{
	UI::m_RootElement->HandleMouseMove(_MousePos);
	UIImpl::HandleMouseMove(_MousePos);
}

////////////////////////////////////////////////////////////////
//      ///      ///  /  //////  ///    ///          /        //
//  ////  /  ////  /  /  //////  /  ////  /////  /////  ////////
//      ///      ///  ///  //  ///        /////  /////      ////
//  ///////  ///  //  ///  //  ///  ////  /////  /////  ////////
//  ///////  ////  /  /////  /////  ////  /////  /////        //
////////////////////////////////////////////////////////////////

UI::Element* UI::GetRootElement()
{
	return m_RootElement;
}

//////////////////////////////////////////////////////
////      ///          /  ////  /        /        ////
//  //////  /////  /////  ////  /  ///////  //////  //
//  //////  /////  /////        /      ///        ////
//  //////  /////  /////  ////  /  ///////  //  //////
////      ///////  /////  ////  /        /  ////  ////
//////////////////////////////////////////////////////

