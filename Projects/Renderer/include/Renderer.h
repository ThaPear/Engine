#pragma once

#pragma comment(lib, "GL/OpenGL32.Lib")
#pragma comment(lib, "GL/glu32.lib")
extern "C"
{
#	include "GL/glew.h"
}

#include "GL/GL.h"
#include "GL/GLU.h"

namespace Renderer
{
	HWND m_HWND = NULL;
	HDC m_DC = NULL;
	HGLRC m_RC = NULL;
	unsigned int m_SizeX = 320, m_SizeY = 240;
	GLuint m_GLTexture = 0;
	GLuint m_PixelBufferObject = 0;
	unsigned int* m_PixelBuffer = NULL;
};