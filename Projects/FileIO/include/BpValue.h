#pragma once

class BpValue
{
	// All private, only accessible by BpReader.
private:
	BpValue()
	{
		m_Value = 0;
	}
	~BpValue()
	{
		delete m_Value;
	}
	enum class Type
	{
		Color_t,
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Char, Char2, Char3, Char4,
		Short, Short2, Short3, Short4,
		Bool,
		String,
		List
	};
	typedef std::map<std::string, BpValue::Type> StringToBpValueTypeMap;
	typedef std::pair<std::string, BpValue::Type> StringToBpValueTypePair;
	typedef std::map<BpValue::Type, std::string> BpValueTypeToStringMap;
	typedef std::pair<BpValue::Type, std::string> BpValueTypeToStringPair;
	static StringToBpValueTypeMap m_StringToBpValueTypeMap;
	static BpValueTypeToStringMap m_BpValueTypeToStringMap;


	friend class BpReader;
			
	template<typename _T> _T GetValue()
	{
		_T val;
		memcpy_s(&val, sizeof(_T), m_Value, sizeof(_T));
		return val;
	}
	template<> std::string GetValue<std::string>()
	{
		// It's stored as a char*, so just return it in an std::string.
		return std::string(m_Value);
	}
	template<typename _T> void SetValue(const _T& _Value, const BpValue::Type _Type)
	{
		if(m_Value != NULL)
		{
			delete m_Value;
		}
		m_Value = (char*)malloc(sizeof(_T));
		memcpy_s(m_Value, sizeof(_T), &_Value, sizeof(_T));

		m_Type = _Type;
	}
	template<> void SetValue<std::string>(const std::string& _Value, const BpValue::Type _Type)
	{
		if(m_Value != NULL)
		{
			delete m_Value;
		}
		// Just store it as a char*.
		m_Value = (char*)malloc(_Value.length() + 1);
		strcpy_s(m_Value, _Value.length()+1, _Value.c_str());

		m_Type = _Type;
	}
	BpValue::Type GetType()	{	return m_Type;	}
			
	char* m_Value;
	BpValue::Type m_Type;
};

__declspec(selectany) BpValue::StringToBpValueTypeMap BpValue::m_StringToBpValueTypeMap;
__declspec(selectany) BpValue::BpValueTypeToStringMap BpValue::m_BpValueTypeToStringMap;

typedef std::pair<std::string, BpValue*> StringBpValuePair;
typedef std::map <std::string, BpValue*> StringBpValueMap;