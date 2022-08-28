#pragma once
#include <string>

//�����ʽת��������
class MyEnco
{
public:
	//��GBK�����Ϊutf8
	static std::string GBKToUTF8(const std::string& gbkData);

	//��utf8����ת��ΪCHS����
	static std::string UTF8ToGBK(const std::string& utf8Data);

	//unicode�����ʽ���ַ���תutf8���ġ�
	//��\\u5199\\u4fe1\\u7ed9\\u75c5\\u623f  �� > "д�Ÿ�����
	static std::string Unicode_stringToUTF8(const std::string& str);

	// unicode �ֽ�����ת����
	// 0x89 0x7F 0x5B 0x89 0x8D 0xEF ---> ����·
	static std::string Unicode_CharToUTF8(unsigned char* s_src, int len);

	//unicode��Ӣ��תunicode���ַ���  
	//asd��ð�---- > 0061007300644f60597d963f 
	//stringToUnicode(stringStr).c_str())
	static std::string GBKToUnicode_string(const std::string& str);

};

