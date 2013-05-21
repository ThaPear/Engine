#pragma once

// Prints specified value using specified tag (e.g. %i, %f).
#define PrintValue(_ValueName, _Tag)	printf(#_ValueName" = "_Tag".\n", _ValueName)
#define PrintFuncEntry()				printf(__FUNCTION__"().\n")

template <typename _T> inline _T Clamp(const _T& _Low, const _T& _Val, const _T& a_High) 
{
  return _Val < _Low ? _Low : (_Val > a_High ? a_High : _Val); 
}
#define PI 3.1415926535f
#define clamp(a, b, c) Clamp(a, b, c)
#define cosd(a)		( cos((a)  * (PI/180)))
#define sind(a)		( sin((a)  * (PI/180)))
#define acosd(a)	(acos((a)) * (180/PI) )
#define asind(a)	(acos((a)) * (180/PI) )
#define FromRadians(a)	 ((a)  * (180/PI) )

#ifdef _DEBUG
#	define DebugCheck(condition)	if(condition)
#else
#	define DebugCheck(condition)	if(false)
#endif

namespace Utility
{
	// Compare function for use with map. Allows searching through a map using const char*.
	struct _ConstCharPtrCmp	{   
		bool operator() (char const *_A, char const *_B)   {  return std::strcmp(_A, _B) < 0;   }
	};

	static bool FileExists( const char* _FileName )
	{
		FILE* file;
		fopen_s(&file, _FileName, "rb" );
		if(file == NULL)
		{
			Log("Could not open file %s.\n", _FileName);
			return false;
		}
		else
		{
			fclose(file);
			return true;
		}
	}
};

template<typename _Type>
struct ValueWithSquare
{
public:
	ValueWithSquare(){}
	void operator = (const _Type& _V)	{	v = _V; sq = _V*_V;	}
	_Type v, sq;
};

typedef ValueWithSquare<int				> intSq;
typedef ValueWithSquare<short			> shortSq;
typedef ValueWithSquare<char			> charSq;
typedef ValueWithSquare<unsigned int	> uintSq;
typedef ValueWithSquare<unsigned short	> ushortSq;
typedef ValueWithSquare<unsigned char	> ucharSq;
typedef ValueWithSquare<float			> floatSq;
typedef ValueWithSquare<double			> doubleSq;

struct MatterEnergy
{
	int energy;
	int matter;
};

_declspec(selectany) int2 g_ScreenSize = int2(0, 0);