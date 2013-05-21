#pragma once

#ifndef _sdlkeycodes_H
#define _sdlkeycodes_H

enum class Key : unsigned short
{
	//enum En
	//{
		Null = 0,
		Escape = 1,
		One = 2, Two, Three, Four, Five, Six, Seven, Eight, Nine, Zero, 
		Underscore /*12*/, Equals, Backspace, Tab, 
		Q /*16*/, W, E, R, T, Y, U, I, O, P,
		LBracket /*26*/, RBracket, Enter, LCtrl,
		A /*30*/, S, D, F, G, H, J, K, L, 
		Semicolon /*39*/, QuotMark, Tilde, LShift, Backslash, 
		Z /*44*/, X, C, V, B, N, M,
		Comma /*51*/, Dot, QuestionMark, RShift, Asterisk, LAlt, Space, Capslock,
		F1 /*59*/, F2, F3, F4, F5, F6, F7, F8, F9, F10,
		Pause /*69*/, ScrollLock,
		NumpadOne /*71*/, NumpadTwo,	NumpadThree,	Minus,
		NumpadFour,		  NumpadFive,	NumpadSix,		Plus,
		NumpadSeven,	  NumpadEight,	NumpadNine,		NumpadDot,
		F11 = 87, F12,
		
		// Without extended keycode bit.
		//NumpadEnter = 28, RCtrl,
		//Slash = 53,
		//PrintScreen = 55, RAlt,
		//NumLock = 69,
		//Home = 71, ArrowUp, PageUp,
		//ArrowLeft = 75,
		//ArrowRight = 77,
		//End = 75, ArrowDown, PageDown, Insert, Delete,
		//LWindowsKey = 91, RWindowsKey
		//ContextMenuKey = 93,

		// With extended keycode bit.
		NumpadEnter = 284, RCtrl,
		Slash = 309,
		PrintScreen = 311, RAlt,
		NumLock = 325,
		Home = 327, ArrowUp, PageUp,
		ArrowLeft = 331,
		ArrowRight = 333,
		End = 335, ArrowDown, PageDown, Insert, Delete,
		LWindowsKey = 347, RWindowsKey,
		ContextMenuKey = 349,


		
		Ctrl, Alt, Shift,
		
		KeyMax


		// Unknown:
		//PrintScreen,


	//};
};

enum class MouseBtn : unsigned char
{
	//enum E
	//{
		Left = 1, Middle, Right, Btn4, Btn5,
		KeyMax
	//};
};

static bool operator < (int _I, Key _K)
{
	return _I < (int)_K;
}

static bool operator < (int _I, MouseBtn _B)
{
	return _I < (int)_B;
}

#endif // _sdlkeycodes_H