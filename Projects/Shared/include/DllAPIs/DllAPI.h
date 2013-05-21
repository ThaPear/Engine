// No pragma once

// Define DllExport to export the dll.
// Define DllByLib to export/import by lib, the lib is #prama comment-ed.


#undef LoadDllFunction
#undef DllArgs
#undef EndDllFuncs
#undef StartDllFuncs
#undef DllFunc

#ifdef _DEBUG
#	define ConfigurationName "Debug"
#else // _DEBUG
#	define ConfigurationName "Release"
#endif // _DEBUG

#define LoadDllFunction(_ModuleName, _FuncName)																				\
									_ModuleName::_FuncName = (_ModuleName::p##_FuncName)GetProcAddress(hInst, #_FuncName);	\
									if(_ModuleName::_FuncName == NULL)														\
									{	printf("Failed to load "#_ModuleName"::"#_FuncName".\n");	return false;	}
#define DllArgs(...) __VA_ARGS__

#ifdef DllExport
#	pragma message("Exporting to Dll")
#	define EndDllFuncs(_ModuleName)
#	define StartDllFuncs(_NextFunction)	_NextFunction
#	define DllFunc(_ModuleName, _Type, _FuncName, _Args, _NextFunction) _NextFunction										\
																		__declspec(dllexport) _Type _FuncName(_Args);
#else // DllExport
#	ifdef DllByLib
#		pragma comment(lib, DllByLib)
#		define EndDllFuncs(_ModuleName)	static bool LoadDllFunctions()														\
										{																					\
											printf(#_ModuleName"::LoadDllFunctions call not necessary, imported by lib.\n");\
											return true;																	\
										}
#		define StartDllFuncs(_NextFunction)	_NextFunction
#		define DllFunc(_ModuleName, _Type, _FuncName, _Args, _NextFunction) _NextFunction									\
																			__declspec(dllimport) _Type _FuncName(_Args);	
#	else // DllByLib
#		pragma message("Importing from Dll")
#		define EndDllFuncs(_ModuleName)	static bool LoadDllFunctions()														\
										{																					\
											HINSTANCE hInst;																\
											if(!(hInst = LoadLibrary(ConfigurationName"\\"#_ModuleName".dll")))				\
											{																				\
												printf("Could not load "ConfigurationName"\\"#_ModuleName".dll.\n");		\
												return false;																\
											}
#		define StartDllFuncs(_NextFunction)	_NextFunction																	\
											SetLastError(0);																\
											return true;																	\
										}
#		define DllFunc(_ModuleName, _Type, _FuncName, _Args, _NextFunction) typedef _Type (*p##_FuncName)(_Args);			\
																			p##_FuncName _FuncName;							\
																			_NextFunction									\
																			LoadDllFunction(_ModuleName, _FuncName)
#	endif // DllByLib
#endif // DllExport