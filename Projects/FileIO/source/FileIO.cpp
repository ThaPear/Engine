#include "FileIO.h"

#define DllExport
#include "DllAPIs\FileIO.h"
#include "BpReader.h"

bool FileIO::Init()
{
	PrintFuncEntry();

	BpReader::Init();

	return true;
}

void FileIO::Terminate()
{

}

unsigned int* FileIO::GetImageData(const char* _ImagePath, unsigned int& o_SizeX, unsigned int& o_SizeY)
{
	char imagePath[1024];
	sprintf_s(imagePath, "../Images/%s", _ImagePath);


	// Check if file exists.
#pragma warning(push)
#pragma warning(disable : 4996)
	FILE* file = fopen( imagePath, "rb" );
#pragma warning(pop)
	if (!file) 
	{
		printf("File not found: %s", imagePath );
		return NULL;
	}
	else fclose( file );

	// Load the file using FreeImage.
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType( imagePath, 0 );
	if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename( imagePath );
	FIBITMAP* tmp = FreeImage_Load( fif, imagePath );
	FIBITMAP* dib = FreeImage_ConvertTo32Bits( tmp );
	FreeImage_Unload( tmp );
	unsigned char* bits = FreeImage_GetBits( dib );
	o_SizeX = FreeImage_GetWidth( dib );
	o_SizeY = FreeImage_GetHeight( dib );
	unsigned int* pixelBuffer = (unsigned int*)malloc( o_SizeX * o_SizeY * sizeof( unsigned int ) );
	for(unsigned int y = 0; y < o_SizeY; y++) 
	{
		unsigned char* line = FreeImage_GetScanLine( dib, o_SizeY - 1 - y );
		memcpy( pixelBuffer + y * o_SizeX, line, o_SizeX * sizeof( unsigned int ) );
	}
	FreeImage_Unload( dib );

	return pixelBuffer;
}

void FileIO::LoadBp(const char* _BpPath)
{
	BpReader::Load(_BpPath);
}

#define ImplementGetFunc(_Type, _FakeType)	_Type FileIO::BpGet##_FakeType(const char* _ValueName)	\
											{														\
												return BpReader::GetBpValue<_Type>(_ValueName);		\
											}

ImplementGetFunc(Color, Color)
ImplementGetFunc(int, Int)
ImplementGetFunc(int2, Int2)
ImplementGetFunc(int3, Int3)
ImplementGetFunc(int4, Int4)
ImplementGetFunc(float, Float)
ImplementGetFunc(float2, Float2)
ImplementGetFunc(float3, Float3)
ImplementGetFunc(float4, Float4)
ImplementGetFunc(char, Char)
ImplementGetFunc(char2, Char2)
ImplementGetFunc(char3, Char3)
ImplementGetFunc(char4, Char4)
ImplementGetFunc(short, Short)
ImplementGetFunc(short2, Short2)
ImplementGetFunc(short3, Short3)
ImplementGetFunc(short4, Short4)
ImplementGetFunc(bool, Bool)
ImplementGetFunc(std::string, String)