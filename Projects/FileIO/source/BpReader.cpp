
#include "BpReader.h"

#define DefaultBpValueFileHeader \
"// Capitalization is very important.\n\
// Spaces are very important.\n\
// Just... Formatting is very important.\n\
// Colors are char4 rgba (0-255)."

#define STBVTP StringToBpValueTypePair
#define BVTTSP BpValueTypeToStringPair

#define AddBpValueType(a)		BpValue::m_StringToBpValueTypeMap.insert(BpValue::STBVTP(std::string(#a), BpValue::Type::a));		\
								BpValue::m_BpValueTypeToStringMap.insert(BpValue::BVTTSP(BpValue::Type::a, std::string(#a)))
#define AddVecBpValueType(a)	BpValue::m_StringToBpValueTypeMap.insert(BpValue::STBVTP(std::string(#a), BpValue::Type::a));		\
								BpValue::m_BpValueTypeToStringMap.insert(BpValue::BVTTSP(BpValue::Type::a, std::string(#a)));		\
								BpValue::m_StringToBpValueTypeMap.insert(BpValue::STBVTP(std::string(#a"2"), BpValue::Type::a##2));	\
								BpValue::m_BpValueTypeToStringMap.insert(BpValue::BVTTSP(BpValue::Type::a##2, std::string(#a"2")));	\
								BpValue::m_StringToBpValueTypeMap.insert(BpValue::STBVTP(std::string(#a"3"), BpValue::Type::a##3));	\
								BpValue::m_BpValueTypeToStringMap.insert(BpValue::BVTTSP(BpValue::Type::a##3, std::string(#a"3")));	\
								BpValue::m_StringToBpValueTypeMap.insert(BpValue::STBVTP(std::string(#a"4"), BpValue::Type::a##4));	\
								BpValue::m_BpValueTypeToStringMap.insert(BpValue::BVTTSP(BpValue::Type::a##4, std::string(#a"4")))

#define AddBpValueTypeLoadSwitch(_BpValueType, _Type, _ConversionFuncType, _ConversionFunc)				\
	case BpValue::Type::_BpValueType:																	\
	{																									\
		_Type val = (_Type)BpReader::ParseType<_ConversionFuncType>(valStr, _ConversionFunc);			\
		BpReader::SetBpValue<_Type>(name, val, BpValue::Type::_BpValueType);							\
	}																									\
	break
#define AddVecBpValueTypeLoadSwitch(_BpValueType, _Type, _Num, _ConversionFuncType, _ConversionFunc)	\
	case BpValue::Type::_BpValueType:																	\
	{																									\
		_Type val = BpReader::ParseVecType<_Type, _ConversionFuncType>(valStr, _Num, _ConversionFunc);	\
		BpReader::SetBpValue<_Type>(name, val, BpValue::Type::_BpValueType);							\
	}																									\
	break
#define AddBpValueTypeSaveSwitch(_BpValueType, _Type, _FloatOrInt)										\
	case BpValue::Type::_BpValueType:																	\
	{																									\
		valueStr = BpReader::Stringify##_FloatOrInt##Type<_Type>(setting->GetValue<_Type>());			\
	}																									\
	break
#define AddVecBpValueTypeSaveSwitch(_BpValueType, _Type, _Num, _FloatOrInt)								\
	case BpValue::Type::_BpValueType:																	\
	{																									\
		valueStr = BpReader::Stringify##_FloatOrInt##VecType<_Type>(setting->GetValue<_Type>(), _Num);	\
	}																									\
	break

#define DefaultCfgFileName "defaultCfg.cfg"

int g_BpListDepth = 0;
std::vector<std::string> g_BpPrefixes;
std::string g_BpPrefixTotal;

///////////////////////////////////////////////////////////
//        ///  //////  /        ///  ///////  ///        //
//  //////  /  //////  /  //////  /  ///////  /  //////////
//        ///  //////  /        ///  ///////  /  //////////
//  /////////  //////  /  //////  /  ///////  /  //////////
//  ///////////      ///        ///        /  ///        //
///////////////////////////////////////////////////////////

bool BpReader::Init()
{
	AddBpValueType(Color_t);
	AddVecBpValueType(Int);
	AddVecBpValueType(Float);
	AddVecBpValueType(Char);
	AddVecBpValueType(Short);
	AddBpValueType(Bool);
	AddBpValueType(String);
	AddBpValueType(List);

	return true;
}

void BpReader::Terminate()
{

}

void BpReader::Load( const char* _BpFilePath )
{
	// If there's already bp values in here.
	if(BpReader::m_BpValues.size() != 0)
	{
		// Delete the values.
		for(auto settingPairIt = BpReader::m_BpValues.begin(); settingPairIt != BpReader::m_BpValues.end(); ++settingPairIt)
		{
			delete settingPairIt->second;
		}
		// Clear the map.
		BpReader::m_BpValues.clear();
	}


	char filePath[256];
	sprintf_s(filePath, "../%s", _BpFilePath);
	Log("Loading config from file \"%s\".\n", filePath);
	if(!Utility::FileExists(filePath))
	{
		Warn("Specified file not found (%s).\n", filePath);
		return;
	}
	std::ifstream file(filePath);
	if(file.is_open())
	{
		std::string line;
		int lineNumber = 0;
		while(!file.eof())
		{
			getline(file, line);
			BpReader::ParseLine(line, lineNumber);
			lineNumber++;
		}
		// Close file.
		file.close();
	}
	else
	{
		Error("Specified config file could not be opened.\n");
	}

	//for(std::pair<std::string, BpValue*> val : m_BpValues)
	//{
	//	printf("val.first = %s.\n", val.first.c_str());
	//}
}

//void BpReader::Save( const char* _BpFilePath )
//{
//	char filePath[256];
//	sprintf_s(filePath, "../%s", _BpFilePath);
//	Log("Saving config to file \"%s\".\n", filePath);
//	std::ofstream file(filePath);
//	if(file.is_open())
//	{
//		file << DefaultBpValueFileHeader << std::endl;
//		for(StringBpValueMap::iterator settingIt = m_BpValues.begin(); settingIt != m_BpValues.end(); ++settingIt)
//		{
//			BpValue* setting = settingIt->second;
//			std::string settingName = settingIt->first;
//
//			BpValue::BpValueTypeToStringMap::iterator typeToStrIt = BpValue::m_BpValueTypeToStringMap.find(setting->GetType());
//			if(typeToStrIt == BpValue::m_BpValueTypeToStringMap.end())
//			{
//				Warn("BpValue \"%s\" has invalid setting type.\n", settingName);
//				continue;
//			}
//			std::string typeStr = typeToStrIt->second;
//
//			std::string valueStr = "";
//			switch(setting->GetType())
//			{
//			AddVecBpValueTypeSaveSwitch(Color_t, Color, 4, Int);
//			AddBpValueTypeSaveSwitch(Int, int, Int);
//			AddVecBpValueTypeSaveSwitch(Int2, int2, 2, Int);
//			AddVecBpValueTypeSaveSwitch(Int3, int3, 3, Int);
//			AddVecBpValueTypeSaveSwitch(Int4, int4, 4, Int);
//			AddBpValueTypeSaveSwitch(Float, float, Float);
//			AddVecBpValueTypeSaveSwitch(Float2, float2, 2, Float);
//			AddVecBpValueTypeSaveSwitch(Float3, float3, 3, Float);
//			AddVecBpValueTypeSaveSwitch(Float4, float4, 4, Float);
//			AddBpValueTypeSaveSwitch(Char, char, Int);
//			AddVecBpValueTypeSaveSwitch(Char2, char2, 2, Int);
//			AddVecBpValueTypeSaveSwitch(Char3, char3, 3, Int);
//			AddVecBpValueTypeSaveSwitch(Char4, char4, 4, Int);
//			AddBpValueTypeSaveSwitch(Short, char, Int);
//			AddVecBpValueTypeSaveSwitch(Short2, short2, 2, Int);
//			AddVecBpValueTypeSaveSwitch(Short3, short3, 3, Int);
//			AddVecBpValueTypeSaveSwitch(Short4, short4, 4, Int);
//			case BpValue::Type::String:
//				{
//					valueStr = setting->GetValue<std::string>();
//				}
//				break;
//			}
//			file << typeStr << " " << settingName << " = " << valueStr << std::endl;
//		}
//	}
//	else
//	{
//		Error("Specified config file could not be opened.\n");
//	}
//}

void RegeneratePrefixTotal()
{
	g_BpPrefixTotal.clear();
	for(unsigned int i = 0; i < g_BpPrefixes.size(); ++i)
	{
		g_BpPrefixTotal = g_BpPrefixTotal.append(g_BpPrefixes[i]);
		g_BpPrefixTotal.push_back('.');
	}
}

void BpReader::ParseLine( std::string _Line, int _LineNumber )
{
	if(_Line[0] == '/' && _Line[1] == '/' || _Line.length() < 1)
		return;
	
	if(g_BpListDepth > 0 && _Line[g_BpListDepth-1] == '}')
	{
		g_BpListDepth -= 1;
		g_BpPrefixes.pop_back();
		RegeneratePrefixTotal();
		return;
	}
	
	_Line = _Line.substr(g_BpListDepth);

	if(_Line[0] == '/' && _Line[1] == '/' || _Line.length() < 1)
		return;

	std::string typeStr = _Line.substr(0, _Line.find(' '));
	BpValue::StringToBpValueTypeMap::iterator typeIt = BpValue::m_StringToBpValueTypeMap.find(typeStr);
	if(typeIt == BpValue::m_StringToBpValueTypeMap.end())
	{
		Warn("Unknown setting type found in config file: \"%s\" on line %i.\n", typeStr.c_str(), _LineNumber);
		Warn("Line: %s.\n", _Line.c_str());
		return;
	}
	BpValue::Type type = typeIt->second;
	std::string valStr = _Line.substr(_Line.find("= ")+2);
	std::string nameStr = _Line.substr(0, _Line.find(" = "));
	nameStr = nameStr.substr(_Line.find(' ')+1);

	std::string name = g_BpPrefixTotal;
	name.append(nameStr);

	switch(type)
	{
	AddVecBpValueTypeLoadSwitch(Color_t, Color, 4, int, atoi);
	AddBpValueTypeLoadSwitch(Int, int, int, atoi);
	AddVecBpValueTypeLoadSwitch(Int2, int2, 2, int, atoi);
	AddVecBpValueTypeLoadSwitch(Int3, int3, 3, int, atoi);
	AddVecBpValueTypeLoadSwitch(Int4, int4, 4, int, atoi);
	AddBpValueTypeLoadSwitch(Float, float, double, atof);
	AddVecBpValueTypeLoadSwitch(Float2, float2, 2, double, atof);
	AddVecBpValueTypeLoadSwitch(Float3, float3, 3, double, atof);
	AddVecBpValueTypeLoadSwitch(Float4, float4, 4, double, atof);
	AddBpValueTypeLoadSwitch(Char, char, int, atoi);
	AddVecBpValueTypeLoadSwitch(Char2, char2, 2, int, atoi);
	AddVecBpValueTypeLoadSwitch(Char3, char3, 3, int, atoi);
	AddVecBpValueTypeLoadSwitch(Char4, char4, 4, int, atoi);
	AddBpValueTypeLoadSwitch(Short, char, int, atoi);
	AddVecBpValueTypeLoadSwitch(Short2, short2, 2, int, atoi);
	AddVecBpValueTypeLoadSwitch(Short3, short3, 3, int, atoi);
	AddVecBpValueTypeLoadSwitch(Short4, short4, 4, int, atoi);
	case BpValue::Type::Bool:
		{
			bool val = (strcmp(valStr.c_str(), "true") == 0);
			BpReader::SetBpValue<bool>(name, val, BpValue::Type::String);
		}
		break;
	case BpValue::Type::String:
		{
			BpReader::SetBpValue<std::string>(name, valStr, BpValue::Type::String);
		}
		break;
	case BpValue::Type::List:
		{
			g_BpListDepth += 1;
			g_BpPrefixes.push_back(nameStr);
			RegeneratePrefixTotal();
		}
		break;
	}
}
////////////////////////////////////////////////////////////////
//      ///      ///  /  //////  ///    ///          /        //
//  ////  /  ////  /  /  //////  /  ////  /////  /////  ////////
//      ///      ///  ///  //  ///        /////  /////      ////
//  ///////  //  ///  ///  //  ///  ////  /////  /////  ////////
//  ///////  ////  /  /////  /////  ////  /////  /////        //
////////////////////////////////////////////////////////////////

StringBpValueMap BpReader::m_BpValues;
