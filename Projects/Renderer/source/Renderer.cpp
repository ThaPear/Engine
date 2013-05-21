#include "DllAPIs/FileIO.h"

#include "Image.h"

#include "Renderer.h"


#define DllExport
#include "DllAPIs\Renderer.h"

void GetOpenGLError();

///////////////////////////////////////////////////////////
//        ///  //////  /        ///  ///////  ///        //
//  //////  /  //////  /  //////  /  ///////  /  //////////
//        ///  //////  /        ///  ///////  /  //////////
//  /////////  //////  /  //////  /  ///////  /  //////////
//  ///////////      ///        ///        /  ///        //
///////////////////////////////////////////////////////////
bool Renderer::Init(HWND _HWND)
{
	PrintFuncEntry();

	Renderer::m_HWND = _HWND;

	// Set up the pixel format.
	static const PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,											// Select Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		0,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};


	// Get device context.
	Renderer::m_DC = GetDC(Renderer::m_HWND);
		
	// Set pixel format.
	GLuint pixelFormat = ChoosePixelFormat(Renderer::m_DC, &pfd);
	SetPixelFormat(Renderer::m_DC, pixelFormat, &pfd);

	// Create render context.
	Renderer::m_RC = wglCreateContext(Renderer::m_DC);
	wglMakeCurrent(Renderer::m_DC, Renderer::m_RC);

	// Clear to black.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glViewport(0, 0, Renderer::m_SizeX, Renderer::m_SizeY);

	// Projection matrix.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0, Renderer::m_SizeX, Renderer::m_SizeY, 0, 0, 1024 );

	// Reset the Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glGenTextures( 1, &Renderer::m_GLTexture );

	glBindTexture( GL_TEXTURE_2D, Renderer::m_GLTexture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );


	GetOpenGLError();
	
	Renderer::m_PixelBuffer = (unsigned int*)malloc(Renderer::m_SizeX * Renderer::m_SizeY * 4);

	return true;
}

void Renderer::Terminate()
{
	PrintFuncEntry();
}

void Renderer::Resize(int _SizeX, int _SizeY)
{
	printf("Renderer::Resize(%i, %i).\n", _SizeX, _SizeY);
	Renderer::m_SizeX = _SizeX;
	Renderer::m_SizeY = _SizeY;
	
	glViewport(0, 0, Renderer::m_SizeX, Renderer::m_SizeY);

	// Projection matrix.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0, Renderer::m_SizeX, Renderer::m_SizeY, 0, 0, 1024 );
	glMatrixMode( GL_MODELVIEW );

	free(Renderer::m_PixelBuffer);
	Renderer::m_PixelBuffer = (unsigned int*)malloc(Renderer::m_SizeX * Renderer::m_SizeY * 4);
}

void Renderer::DisplayBuffer()
{
	if(Renderer::m_PixelBuffer == NULL)
		return;

	for(unsigned int i = 0; i < Renderer::m_SizeX * Renderer::m_SizeY; ++i)
		*(Renderer::m_PixelBuffer + i) = rand();
		
	glBindTexture( GL_TEXTURE_2D, 0 );

	SwapBuffers(Renderer::m_DC);

	// Clear the screen.
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Bind texture.
	glBindTexture(GL_TEXTURE_2D, Renderer::m_GLTexture);
	// Upload pixel data to GPU.
	glTexImage2D(	GL_TEXTURE_2D, 0, 4, Renderer::m_SizeX, Renderer::m_SizeY, 0,
					GL_RGBA, GL_UNSIGNED_BYTE, Renderer::m_PixelBuffer);

	//// Render texture to a quad.
	//glBegin( GL_QUADS );
	//	glVertex2i(0				, 0					);	glTexCoord2f(0, 1);
	//	glVertex2i(Renderer::m_SizeX, 0					);	glTexCoord2f(1, 1);
	//	glVertex2i(Renderer::m_SizeX, Renderer::m_SizeY	);	glTexCoord2f(1, 0);
	//	glVertex2i(0				, Renderer::m_SizeY	);	glTexCoord2f(0, 0);
	//glEnd();
	GetOpenGLError();
}

void Renderer::RenderImage(Image* _Image, unsigned int _Frame, float2 _Pos, float2 _Size)
{
	printf("Image at %f, %f of %f by %f.\n", _Pos.x, _Pos.y, _Size.x, _Size.y);
	DebugCheck(_Frame >= _Image->m_NumFrames)
	{
		printf("Renderer::RenderImage: Specified frame (%i) higher than existing amount in image (%i) (0-based).\n", _Frame, _Image->m_NumFrames);
		return;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, _Image->m_GLTexture);

	const float u1 = (float)(_Image->m_FrameSizeX * (_Frame    )) / (float)_Image->m_Size.x;
	const float u2 = (float)(_Image->m_FrameSizeX * (_Frame + 1)) / (float)_Image->m_Size.x;

	const float2 p1 = _Pos;
	const float2 p2 = _Pos + _Size;
	// TODO: Displaylists or something.
	glBegin( GL_QUADS );
		glTexCoord2f(u1, 0);	glVertex2f(p1.x, p1.y);
		glTexCoord2f(u2, 0);	glVertex2f(p2.x, p1.y);
		glTexCoord2f(u2, 1);	glVertex2f(p2.x, p2.y);
		glTexCoord2f(u1, 1);	glVertex2f(p1.x, p2.y);
	glEnd();
}

void Renderer::RenderImage(Image* _Image, unsigned int _Frame, float2 _Pos, float2 _Size, float _Rotation)
{
	DebugCheck(_Frame >= _Image->m_NumFrames)
	{
		printf("Renderer::RenderImage: Specified frame (%i) higher than existing amount in image (%i) (0-based).\n", _Frame, _Image->m_NumFrames);
		return;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glRotatef(_Rotation, 0, 0, 1);
	glTranslatef(	_Pos.x + _Size.x * 0.5f,
					_Pos.y + _Size.y * 0.5f, 0);
	//glTranslatef((float)_Image->m_SizeX * 0.5f, (float)_Image->m_SizeY * 0.5f, 0);
	glRotatef(_Rotation, 0, 0, 1);

	glBindTexture(GL_TEXTURE_2D, _Image->m_GLTexture);

	const float u1 = (float)(_Image->m_FrameSizeX * (_Frame    )) / (float)_Image->m_Size.x;
	const float u2 = (float)(_Image->m_FrameSizeX * (_Frame + 1)) / (float)_Image->m_Size.x;

	const float2 p1 = _Size * -0.5f;
	const float2 p2 = _Size *  0.5f;

	// TODO: Displaylists or something.
	glBegin( GL_QUADS );
		glTexCoord2f(u1, 0);	glVertex2f(p1.x, p1.y);
		glTexCoord2f(u2, 0);	glVertex2f(p2.x, p1.y);
		glTexCoord2f(u2, 1);	glVertex2f(p2.x, p2.y);
		glTexCoord2f(u1, 1);	glVertex2f(p1.x, p2.y);
	glEnd();
}

Image* Renderer::LoadImageFromFile( const char* _ImagePath, int _NumFrames )
{
	Image* image = new Image();
	
	unsigned int* pixelBuffer = FileIO::GetImageData(_ImagePath, image->m_Size.x, image->m_Size.y);
	
	image->m_NumFrames = max(1, _NumFrames);
	image->m_FrameSizeX = image->m_Size.x / image->m_NumFrames;

	//  ////////////////////////////////////||\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//  ||						  Load image into OpenGL						||
	//  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\||////////////////////////////////////
	glGenTextures( 1, &image->m_GLTexture );
    glBindTexture( GL_TEXTURE_2D, image->m_GLTexture );
	
	glTexImage2D(	GL_TEXTURE_2D, 0, 4, image->m_Size.x, image->m_Size.y, 0,
					GL_BGRA, GL_UNSIGNED_BYTE, pixelBuffer);

	// Set parameters.
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	//// Mipmap it.
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->m_SizeX, image->m_SizeY,
	//					GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer );
	glBindTexture(GL_TEXTURE_2D, 0);
	

#ifdef Image_RetainPixelBuffer
	image->m_PixelBuffer = pixelBuffer;
#else  // Image_RetainPixelBuffer
	free(pixelBuffer);
#endif // Image_RetainPixelBuffer

	return image;
}

int2 Renderer::GetImageDimensions(Image* _Image)
{
	return int2(_Image->m_Size.x / _Image->m_NumFrames, _Image->m_Size.y);
}

void Renderer::SetNearestMinMagFilters(Image* _Image)
{
    glBindTexture( GL_TEXTURE_2D, _Image->m_GLTexture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glBindTexture(GL_TEXTURE_2D, 0);
}

////////////////////////////////////////////////////////////////
//      ///      ///  /  //////  ///    ///          /        //
//  ////  /  ////  /  /  //////  /  ////  /////  /////  ////////
//      ///      ///  ///  //  ///        /////  /////      ////
//  ///////  ///  //  ///  //  ///  ////  /////  /////  ////////
//  ///////  ////  /  /////  /////  ////  /////  /////        //
////////////////////////////////////////////////////////////////
void GetOpenGLError()
{
	const int error = glGetError();
	if (error)
	{
		switch(error)
		{
		case GL_INVALID_ENUM:
			printf("GL_INVALID_ENUM.\n");
			__asm int 3;
			break;
		case GL_INVALID_VALUE:
			printf("GL_INVALID_VALUE.\n");
			__asm int 3;
			break;
		case GL_INVALID_OPERATION:
			printf("GL_INVALID_OPERATION.\n");
			__asm int 3;
			break;
		case GL_STACK_OVERFLOW:
			printf("GL_STACK_OVERFLOW.\n");
			__asm int 3;
			break;
		case GL_STACK_UNDERFLOW:
			printf("GL_STACK_UNDERFLOW.\n");
			__asm int 3;
			break;
		case GL_OUT_OF_MEMORY:
			printf("GL_OUT_OF_MEMORY.\n");
			__asm int 3;
			break;
		default:
			__asm int 3;
			break;
		}
	}
}