#pragma once

// Define this to make the image retain the raw image pixel data.
#define Image_RetainPixelBuffer

typedef unsigned int GLuint;

class Image
{
public:
	Image();

#ifdef Image_RetainPixelBuffer
	unsigned int* m_PixelBuffer;
#endif // Image_RetainPixelBuffer
	uint2 m_Size;
	unsigned int m_NumFrames;
	unsigned int m_FrameSizeX;

	GLuint m_GLTexture;
};