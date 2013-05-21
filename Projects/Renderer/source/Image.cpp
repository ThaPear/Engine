#include "Image.h"

Image::Image()
	: m_Size(0, 0)
	, m_GLTexture(0)
#ifdef Image_RetainPixelBuffer
	, m_PixelBuffer(NULL)
#endif // Image_RetainPixelBuffer
{

}