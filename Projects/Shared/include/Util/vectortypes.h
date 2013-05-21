#pragma once

#ifndef _vectortypes_H
#define _vectortypes_H
#pragma push_macro("PI")
#define PI 3.1415926535f

//  ////////////////////////////////////||\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//  ||							   Vector Types								||
//  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\||////////////////////////////////////

template<typename _Type>
class vector2template
{
	typedef vector2template<_Type> v2type;
public:
	template<typename _T>
	v2type(const vector2template<_T>& _V)			{	x = _Type(_V.x), y = _Type(_V.y);	}
	v2type(_Type _X, _Type _Y)						{	x = _X,			 y = _Y;			}
	v2type(_Type _Val)								{	x =				 y = _Val;			}
	v2type()										{	x =				 y = 0;				}

	v2type operator +  (const v2type& _V)	const	{	return v2type(x + _V.x, y + _V.y);	}
	v2type operator -  (const v2type& _V)	const	{	return v2type(x - _V.x, y - _V.y);	}
	v2type operator /  (const v2type& _V)	const	{	return v2type(x / _V.x, y / _V.y);	}
	v2type operator *  (const v2type& _V)	const	{	return v2type(x * _V.x, y * _V.y);	}

	void   operator += (const v2type& _V)			{	x += _V.x,		 y += _V.y;			}
	void   operator -= (const v2type& _V)			{	x -= _V.x,		 y -= _V.y;			}
	void   operator /= (const v2type& _V)			{	x /= _V.x,		 y /= _V.y;			}
	void   operator *= (const v2type& _V)			{	x *= _V.x,		 y *= _V.y;			}

	union
	{
		struct { _Type x, y;	};
		struct { _Type data[2];	};
	};
};

template<typename _Type>
class vector3template
{
	typedef vector3template<_Type> v3type;

public:

	template<typename _T>
	v3type(const vector2template<_T>& _V, const _T& _Z)	{	x = _Type(_V.x), y = _Type(_V.y), z = _Type(_Z);	}
	template<typename _T>
	v3type(const vector3template<_T>& _V)				{	x = _Type(_V.x), y = _Type(_V.y), z = _Type(_V.z);	}
	v3type(_Type _X, _Type _Y, _Type _Z)				{	x = _X,			 y = _Y,		  z = _Z;			}
	v3type(_Type _Val)									{	x =				 y =			  z = _Val;			}
	v3type()											{	x =				 y =			  z = 0;			}

	v3type operator +  (const v3type& _V)	const		{	return v3type(x + _V.x, y + _V.y, z + _V.z);		}
	v3type operator -  (const v3type& _V)	const		{	return v3type(x - _V.x, y - _V.y, z - _V.z);		}
	v3type operator /  (const v3type& _V)	const		{	return v3type(x / _V.x, y / _V.y, z / _V.z);		}
	v3type operator *  (const v3type& _V)	const		{	return v3type(x * _V.x, y * _V.y, z * _V.z);		}

	void   operator += (const v3type& _V)				{	x += _V.x,		 y += _V.y,		  z += _V.z;		}
	void   operator -= (const v3type& _V)				{	x -= _V.x,		 y -= _V.y,		  z -= _V.z;		}
	void   operator /= (const v3type& _V)				{	x /= _V.x,		 y /= _V.y,		  z /= _V.z;		}
	void   operator *= (const v3type& _V)				{	x *= _V.x,		 y *= _V.y,		  z *= _V.z;		}

	union
	{
		struct { _Type r, g, b;	};
		struct { _Type x, y, z;	};
		struct { _Type data[3];	};
	};
};

template<typename _Type>
class vector4template
{
	typedef vector4template<_Type> v4type;
	typedef _Type Type;
public:

	template<typename _T>
	v4type(const vector2template<_T>& _V, const _T& _Z, const _T& _W)		{	x = _Type(_V.x), y = _Type(_V.y), z = _Type(_Z)	, w = _Type(_W);	}
	template<typename _T>
	v4type(const vector2template<_T>& _V1, const vector2template<_T>& _V2)	{	x = _Type(_V1.x), y = _Type(_V1.y), z = _Type(_V2.x), w = _Type(_V2.y);	}
	template<typename _T>
	v4type(const vector3template<_T>& _V)			{	x = _Type(_V.x), y = _Type(_V.y), z = _Type(_V.z), w = _Type(_V.z);	}
	v4type(_Type _X, _Type _Y, _Type _Z, _Type _W)	{	x = _X,			 y = _Y,		  z = _Z,		   w = _W;			}
	v4type(_Type _Val)								{	x =				 y =			  z =			   w = _Val;		}
	v4type()										{	x =				 y =			  z =			   w = 0;			}


	v4type operator +  (const v4type& _V)	const	{	return v4type(x + _V.x, y + _V.y, z + _V.z,		   w + _V.w);		}
	v4type operator -  (const v4type& _V)	const	{	return v4type(x - _V.x, y - _V.y, z - _V.z,		   w - _V.w);		}
	v4type operator /  (const v4type& _V)	const	{	return v4type(x / _V.x, y / _V.y, z / _V.z,		   w / _V.w);		}
	v4type operator *  (const v4type& _V)	const	{	return v4type(x * _V.x, y * _V.y, z * _V.z,		   w * _V.w);		}

	void   operator += (const v4type& _V)			{	x += _V.x,		 y += _V.y,		  z += _V.z,	   w += _V.w;		}
	void   operator -= (const v4type& _V)			{	x -= _V.x,		 y -= _V.y,		  z -= _V.z,	   w -= _V.w;		}
	void   operator /= (const v4type& _V)			{	x /= _V.x,		 y /= _V.y,		  z /= _V.z,	   w /= _V.w;		}
	void   operator *= (const v4type& _V)			{	x *= _V.x,		 y *= _V.y,		  z *= _V.z,	   w *= _V.w;		}

	union
	{
		struct { _Type r, g, b, a;	};
		struct { _Type x, y, z, w;	};
		struct { _Type data[4];		};
	};
};

class Color : public vector4template<unsigned char>
{
public:
	//template<typename _T>
	//Color(const _T& _Val)												{	x = y = z = w = _Val;								}
	//template<typename _T>
	//Color(const vector2template<_T>& _V, const _T& _Z, const _T& _W)	{	x = unsigned char(_V.x), y = unsigned char(_V.y),
	//																		z = unsigned char(_Z), w = unsigned char(_W);		}
	//template<typename _T>
	//Color(const vector3template<_T>& _V)								{	x = unsigned char(_V.x), y = unsigned char(_V.y),
	//																		z = unsigned char(_V.z), w = unsigned char(255);	}
	//Color(unsigned char _X, unsigned char _Y,
	//		unsigned char _Z, unsigned char _W)							{	x = _X, y = _Y, z = _Z, w = _W;						}
	//Color(unsigned char _Val)											{	x = y = z = w = _Val;								}
	Color(unsigned int _Val)											{	*(unsigned int*)data = _Val;						}
	Color()																{	x = y = z = w = 0;									}
	unsigned int ToUint()
	{
		return *(unsigned int*)data;
	};
};

//  ////////////////////////////////////||\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//  ||							 Vector Typedefs							||
//  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\||////////////////////////////////////

typedef vector2template<int				> int2;
typedef vector2template<short			> short2;
typedef vector2template<char			> char2;
typedef vector2template<unsigned int	> uint2;
typedef vector2template<unsigned short	> ushort2;
typedef vector2template<unsigned char	> uchar2;
typedef vector2template<float			> float2;
typedef vector2template<double			> double2;

typedef vector3template<int				> int3;
typedef vector3template<short			> short3;
typedef vector3template<char			> char3;
typedef vector3template<unsigned int	> uint3;
typedef vector3template<unsigned short	> ushort3;
typedef vector3template<unsigned char	> uchar3;
typedef vector3template<float			> float3;
typedef vector3template<double			> double3;

typedef vector4template<int				> int4;
typedef vector4template<short			> short4;
typedef vector4template<char			> char4;
typedef vector4template<unsigned int	> uint4;
typedef vector4template<unsigned short	> ushort4;
typedef vector4template<unsigned char	> uchar4;
typedef vector4template<float			> float4;
typedef vector4template<double			> double4;

//  ////////////////////////////////////||\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//  ||							 Vector functions							||
//  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\||////////////////////////////////////
template<typename _T>
_T Dot(vector2template<_T> _V1, vector2template<_T> _V2)
{
	return (_V1.x * _V2.x + _V1.y * _V2.y);
}
template<typename _T>
_T Dot(vector3template<_T> _V1, vector3template<_T> _V2)
{
	return (_V1.x * _V2.x + _V1.y * _V2.y + _V1.z * _V2.z);
}
template<typename _T>
_T Dot(vector4template<_T> _V1, vector4template<_T> _V2)
{
	return (_V1.x * _V2.x + _V1.y * _V2.y + _V1.z * _V2.z + _V1.w * _V2.w);
}
template<typename _T>
vector3template<_T> Cross(vector3template<_T> _V1, vector3template<_T> _V2)
{
	return vector3template<_T> (_V1.y * _V2.z - _V1.z * _V2.y,
								_V1.z * _V2.x - _V1.x * _V2.z,
								_V1.x * _V2.y - _V1.y * _V2.x);
}

template<typename _T> inline _T LengthSq(const vector2template<_T>& _V)	{	return (_V.x*_V.x + _V.y*_V.y);									}
template<typename _T> inline _T LengthSq(const vector3template<_T>& _V)	{	return (_V.x*_V.x + _V.y*_V.y + _V.z*_V.z);						}
template<typename _T> inline _T LengthSq(const vector4template<_T>& _V)	{	return (_V.x*_V.x + _V.y*_V.y + _V.z*_V.z + _V.w*_V.w);			}
template<typename _T> inline _T Length  (const vector2template<_T>& _V)	{	return sqrtf(_V.x*_V.x + _V.y*_V.y);							}
template<typename _T> inline _T Length  (const vector3template<_T>& _V)	{	return sqrtf(_V.x*_V.x + _V.y*_V.y + _V.z*_V.z);				}
template<typename _T> inline _T Length  (const vector4template<_T>& _V)	{	return sqrtf(_V.x*_V.x + _V.y*_V.y + _V.z*_V.z + _V.w*_V.w);	}


//  ////////////////////////////////////||\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//  ||								 Matrices								||
//  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\||////////////////////////////////////

template<typename _Type>
class matrix22template
{
	typedef vector2template<_Type> v2type;
	typedef matrix22template<_Type> m22type;
public:

	template<typename _T>
	m22type(const vector2template<_T>& _V1, const vector2template<_T>& _V2)	{	x1 = _Type(_V1.x), y1 = _Type(_V1.y);
																				x2 = _Type(_V2.x), y2 = _Type(_V2.y);	}
	m22type(_Type _X1, _Type _Y1, _Type _X2, _Type _Y2)						{	x1 = _X1, y1 = _Y1, x2 = _X2, y2 = _Y2;	}

	static m22type Identity()						{	return m22type(	1, 0,
																		0, 1);							}
	static m22type Scale(const v2type& _V)			{	return m22type(	_V.x, 0   ,
																		0	, _V.y);					}
	static m22type Rotation(float _Angle)			{	const float sinVal = sin(_Angle * (PI/180)); const float cosVal = cos(_Angle * (PI/180));
														return m22type(	cosVal, -sinVal,
																		sinVal,  cosVal	);	}

	 v2type operator *  (const  v2type& _V)	const	{	return  v2type(	x1 * _V.x + y1 * _V.y,
																		x2 * _V.x + y2 * _V.y);	}
	m22type operator *  (const m22type& _M)	const	{	return m22type(	x1 * _M.x1 + y1 * _M.x2, x1 * _M.y1 + y1 * _M.y2,
																		x2 * _M.x1 + y2 * _M.x2, x2 * _M.y1 + y2 * _M.y2	);	}

	union
	{
		struct { _Type x1, y1,
					   x2, y2;	};
		struct { v2type v1, v2;	};
		struct { _Type data[2];	};
	};
};

template<typename _Type>
class matrix33template
{
	typedef vector3template<_Type> v3type;
	typedef matrix33template<_Type> m33type;
public:

	template<typename _T>
	m33type(const vector3template<_T>& _V1, const vector3template<_T>& _V2, const vector3template<_T>& _V3)
	{
		x1 = _Type(_V1.x), y1 = _Type(_V1.y), z1 = _Type(_V1.z);
		x2 = _Type(_V2.x), y2 = _Type(_V2.y), z2 = _Type(_V2.z);
		x3 = _Type(_V2.x), y3 = _Type(_V3.y), y3 = _Type(_V3.z);
	}

	m33type(_Type _X1, _Type _Y1, _Type _Z1,
			_Type _X2, _Type _Y2, _Type _Z2,
			_Type _X3, _Type _Y3, _Type _Z3)	{	x1 = _X1, y1 = _Y1, z1 = _Z1;
													x2 = _X2, y2 = _Y2, z2 = _Z2;
													x3 = _X3, y3 = _Y3, z3 = _Z3;		}

	static m33type Identity()					{	return m33type(	1, 0, 0,
																	0, 1, 0,
																	0, 0, 1);			}
	static m33type Scale(const v3type& _V)		{	return m33type(	_V.x, 0   , 0   ,
																	0	, _V.y, 0   ,
																	0	, 0   , _V.z);	}
	// TODO: Test 3d rotation matrices.
	static m33type Rotation(float _Angle, v3type _Ax)
	{
		const float sinVal = sin(_Angle * (PI/180));
		const float cosVal = cos(_Angle * (PI/180));
		const float /*oneMinusCosVal*/ oMCV = (1 - cosVal);
		return m33type(	_Ax.x * _Ax.x * oMCV +		   cosVal, /**/	_Ax.x * _Ax.y * oMCV - _Ax.z * sinVal, /**/	_Ax.x * _Ax.z * oMCV + _Ax.y * sinVal,	
						_Ax.y * _Ax.x * oMCV + _Ax.z * sinVal, /**/	_Ax.y * _Ax.y * oMCV +		   cosVal, /**/	_Ax.y * _Ax.z * oMCV - _Ax.x * sinVal,	
						_Ax.z * _Ax.x * oMCV - _Ax.y * sinVal, /**/	_Ax.z * _Ax.y * oMCV + _Ax.x * cosVal, /**/	_Ax.z * _Ax.z * oMCV +		   cosVal	);
	}

	 v3type operator *  (const  v3type& _V)	const	{	return  v3type(	x1 * _V.x + y1 * _V.y + z1 * _V.z,
																		x2 * _V.x + y2 * _V.y + z2 * _V.z,
																		x3 * _V.x + y3 * _V.y + z3 * _V.z);	}
	m33type operator *  (const m33type& _M)	const	{	return m33type(	x1 * _M.x1 + y1 * _M.x2 + z1 * _M.x3, /**/ x1 * _M.y1 + y1 * _M.y2 + z1 * _M.y3, /**/ x1 * _M.z1 + y1 * _M.z2 + z1 * _M.z3,
																		x2 * _M.x1 + y2 * _M.x2 + z2 * _M.x3, /**/ x2 * _M.y1 + y2 * _M.y2 + z2 * _M.y3, /**/ x2 * _M.z1 + y2 * _M.z2 + z2 * _M.z3,
																		x3 * _M.x1 + y3 * _M.x2 + z3 * _M.x3, /**/ x3 * _M.y1 + y3 * _M.y2 + z3 * _M.y3, /**/ x3 * _M.z1 + y3 * _M.z2 + z3 * _M.z3	);	}

	union
	{
		struct { _Type x1, y1, z1,
					   x2, y2, z2,
					   x3, y3, z3;	};
		struct { v3type v1, v2, v3;	};
		struct { _Type data[2];	};
	};
};

//  ////////////////////////////////////||\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//  ||							 Matrix Typedefs							||
//  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\||////////////////////////////////////

typedef matrix22template<int			> int22;
typedef matrix22template<short			> short22;
typedef matrix22template<char			> char22;
typedef matrix22template<unsigned int	> uint22;
typedef matrix22template<unsigned short	> ushort22;
typedef matrix22template<unsigned char	> uchar22;
typedef matrix22template<float			> float22;
typedef matrix22template<double			> double22;

typedef matrix33template<int			> int33;
typedef matrix33template<short			> short33;
typedef matrix33template<char			> char33;
typedef matrix33template<unsigned int	> uint33;
typedef matrix33template<unsigned short	> ushort33;
typedef matrix33template<unsigned char	> uchar33;
typedef matrix33template<float			> float33;
typedef matrix33template<double			> double33;

#pragma pop_macro("PI")
#endif // _vectortypes_H