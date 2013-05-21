#pragma once

#define DllByLib "Renderer.lib"
#	include "DllAPI.h"
#undef DllByLib

class Image;
namespace Renderer
{
	StartDllFuncs(
		DllFunc(Renderer, bool, Init, DllArgs(HWND _HWND),
		DllFunc(Renderer, void, Terminate, DllArgs(),
		
		DllFunc(Renderer, void, Resize, DllArgs(int _SizeX, int _SizeY),

		DllFunc(Renderer, void, DisplayBuffer, DllArgs(),

		DllFunc(Renderer, void, RenderImage, DllArgs(Image* _Image, unsigned int _Frame, float2 _Pos, float2 _Size),
		DllFunc(Renderer, void, RenderImage, DllArgs(Image* _Image, unsigned int _Frame, float2 _Pos, float2 _Size, float _Rotation),
		
		DllFunc(Renderer, Image*, LoadImageFromFile, DllArgs(const char* _FilePath, int _NumFrames),
		DllFunc(Renderer, int2, GetImageDimensions, DllArgs(Image* _Image),
		DllFunc(Renderer, void, SetNearestMinMagFilters, DllArgs(Image* _Image),
	EndDllFuncs(Renderer)
	))))))))));
}