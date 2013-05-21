#pragma once

#include "BpValue.h"

class BpReader
{
public:
	static bool Init();
	static void Terminate();

	static void Load(const char* _Path);
	// Does not work with nested values. (e.g. weapons = { weapon1 = { damage = 3 } }
	//static void Save(const char* _Path);
	static void ParseLine( std::string _Line, int _LineNumber );
	template<typename _T> static _T ParseType( std::string _ValStr, _T (*_ConversionFunc)(const char*) )
	{
		_T val = _ConversionFunc(_ValStr.c_str());
		return val;
	}
	template<typename _ReturnType, typename _ConversionType>
	static _ReturnType ParseVecType( std::string _ValStr, int _Num, _ConversionType (*_ConversionFunc)(const char*) )
	{
		_ReturnType val = _ReturnType(0);
		typedef decltype(_ReturnType::x) _Type;
		// Extract parts
		for(int i = 0; i < _Num; ++i)
		{
			std::string subValStr = _ValStr.substr(0, _ValStr.find(", "));
			if(subValStr.length() == 0)
				subValStr = _ValStr;
			else
				_ValStr = _ValStr.substr(_ValStr.find(", ")+2);

			val.data[i] = (_Type)_ConversionFunc(subValStr.c_str());

		}
		return val;
	}
	template<typename _T> static std::string StringifyIntType( _T _Val )
	{
		char buffer[128];
		_itoa_s(_Val, buffer, 128, 10);
		return std::string(buffer);
	}
	template<typename _T> static std::string StringifyFloatType( _T _Val )
	{
		char buffer[128];
		_gcvt_s(buffer, 128, _Val, 10);
		return std::string(buffer);
	}
	template<typename _T>
	static std::string StringifyIntVecType( _T _Val, int _Num)
	{
		std::string retStr = "";

		char buffer[128];
		_itoa_s(_Val.data[0], buffer, 128, 10);
		retStr += std::string(buffer);
		for(int i = 1; i < _Num; ++i)
		{
			retStr += std::string(", ");
			_itoa_s(_Val.data[i], buffer, 128, 10);
			retStr += std::string(buffer);
		}
		return retStr;
	}
	template<typename _T>
	static std::string StringifyFloatVecType( _T _Val, int _Num)
	{
		std::string retStr = "";

		char buffer[128];
		_gcvt_s(buffer, 128, _Val.data[0], 10);
		retStr += std::string(buffer);
		for(int i = 1; i < _Num; ++i)
		{
			retStr += std::string(", ");
			_gcvt_s(buffer, 128, _Val.data[i], 10);
			retStr += std::string(buffer);
		}
		return retStr;
	}

	template<typename _T> static _T GetBpValue(char* _Name)
	{
		return GetBpValue<_T>(std::string(_Name));
	}
	template<typename _T> static _T GetBpValue(std::string _Name)
	{
		StringBpValueMap::iterator settingIt = m_BpValues.find(_Name);
		if(settingIt == m_BpValues.end())
		{
			Warn("Invalid setting \"%s\" requested.\n", _Name.c_str());
			return _T();
		}
		BpValue* setting = settingIt->second;

		return setting->GetValue<_T>();
	}
	template<typename _T> static void SetBpValue(std::string _Name, const _T& _Value, const BpValue::Type _Type )
	{
		StringBpValueMap::iterator settingIt = m_BpValues.find(_Name);
		BpValue* setting;
		if(settingIt == m_BpValues.end())
		{
			setting = new BpValue();
			m_BpValues.insert(StringBpValuePair(_Name, setting));
		}
		else
			setting = settingIt->second;

		setting->SetValue<_T>(_Value, _Type);
	}
private:
	static StringBpValueMap m_BpValues;
};