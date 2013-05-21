#pragma once

#define DllByLib "FileIO.lib"
#	include "DllAPI.h"
#undef DllByLib

namespace FileIO
{
	StartDllFuncs(
		DllFunc(FileIO, bool, Init, DllArgs(),
		DllFunc(FileIO, void, Terminate, DllArgs(),
		
		DllFunc(FileIO, unsigned int*, GetImageData, DllArgs(const char* _ImagePath, unsigned int& o_SizeX, unsigned int& o_SizeY),
		
		DllFunc(FileIO, void, LoadBp, DllArgs(const char* _BpPath),


		DllFunc(FileIO, Color, BpGetColor, DllArgs(const char* _ValueName),
		DllFunc(FileIO, int, BpGetInt, DllArgs(const char* _ValueName),
		DllFunc(FileIO, int2, BpGetInt2, DllArgs(const char* _ValueName),
		DllFunc(FileIO, int3, BpGetInt3, DllArgs(const char* _ValueName),
		DllFunc(FileIO, int4, BpGetInt4, DllArgs(const char* _ValueName),
		DllFunc(FileIO, float, BpGetFloat, DllArgs(const char* _ValueName),
		DllFunc(FileIO, float2, BpGetFloat2, DllArgs(const char* _ValueName),
		DllFunc(FileIO, float3, BpGetFloat3, DllArgs(const char* _ValueName),
		DllFunc(FileIO, float4, BpGetFloat4, DllArgs(const char* _ValueName),
		DllFunc(FileIO, char, BpGetChar, DllArgs(const char* _ValueName),
		DllFunc(FileIO, char2, BpGetChar2, DllArgs(const char* _ValueName),
		DllFunc(FileIO, char3, BpGetChar3, DllArgs(const char* _ValueName),
		DllFunc(FileIO, char4, BpGetChar4, DllArgs(const char* _ValueName),
		DllFunc(FileIO, short, BpGetShort, DllArgs(const char* _ValueName),
		DllFunc(FileIO, short2, BpGetShort2, DllArgs(const char* _ValueName),
		DllFunc(FileIO, short3, BpGetShort3, DllArgs(const char* _ValueName),
		DllFunc(FileIO, short4, BpGetShort4, DllArgs(const char* _ValueName),
		DllFunc(FileIO, bool, BpGetBool, DllArgs(const char* _ValueName),
		DllFunc(FileIO, std::string, BpGetString, DllArgs(const char* _ValueName),
		
	EndDllFuncs(FileIO)
	))))))))))))))))))))))));
}