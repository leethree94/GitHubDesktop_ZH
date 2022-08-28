#pragma once
#include <string>

//编码格式转换处理类
class MyEnco
{
public:
	//将GBK编码改为utf8
	static std::string GBKToUTF8(const std::string& gbkData);

	//将utf8编码转换为CHS编码
	static std::string UTF8ToGBK(const std::string& utf8Data);

	//unicode编码格式的字符串转utf8中文。
	//例\\u5199\\u4fe1\\u7ed9\\u75c5\\u623f  — > "写信给病房
	static std::string Unicode_stringToUTF8(const std::string& str);

	// unicode 字节数组转中文
	// 0x89 0x7F 0x5B 0x89 0x8D 0xEF ---> 西安路
	static std::string Unicode_CharToUTF8(unsigned char* s_src, int len);

	//unicode中英文转unicode的字符串  
	//asd你好阿---- > 0061007300644f60597d963f 
	//stringToUnicode(stringStr).c_str())
	static std::string GBKToUnicode_string(const std::string& str);

};

