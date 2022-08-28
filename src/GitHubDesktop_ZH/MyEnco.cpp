#define _CRT_SECURE_NO_WARNINGS

#include "MyEnco.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <codecvt>
#include <math.h>
#include <wchar.h>

//参考https://blog.csdn.net/wanggao_1990/article/details/113973730
//将GBK编码改为utf8
std::string MyEnco::GBKToUTF8(const std::string& gbkData)
{
    const char* GBK_LOCALE_NAME = "CHS";  //GBK在windows下的locale name(.936, CHS ), linux下的locale名可能是"zh_CN.GBK"

    std::wstring_convert<std::codecvt<wchar_t, char, mbstate_t>>
        conv(new std::codecvt<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
    std::wstring wString = conv.from_bytes(gbkData);    // string => wstring

    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::string utf8str = convert.to_bytes(wString);     // wstring => utf-8
    return utf8str;
}

//将utf8编码转换为CHS编码
std::string MyEnco::UTF8ToGBK(const std::string& utf8Data)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring wString = conv.from_bytes(utf8Data);    // utf-8 => wstring

    std::wstring_convert<std::codecvt< wchar_t, char, std::mbstate_t>>
        convert(new std::codecvt< wchar_t, char, std::mbstate_t>("CHS"));
    std::string str = convert.to_bytes(wString);     // wstring => string

    return str;
}

//参考 https://blog.csdn.net/fozhishuiyue/article/details/106729245?utm_medium=distribute.pc_feed_404.none-task-blog-2~default~BlogCommendFromBaidu~Rate-13-106729245-blog-null.pc_404_mixedpudn&depth_1-utm_source=distribute.pc_feed_404.none-task-blog-2~default~BlogCommendFromBaidu~Rate-13-106729245-blog-null.pc_404_mixedpud
/**/
//unicode编码字符串转utf8中文。例\\u5199\\u4fe1\\u7ed9\\u75c5\\u623f — > "写信给病房
std::string MyEnco::Unicode_stringToUTF8(const std::string& str)
{
    std::string u8str;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
/*  for (size_t i = 2; i < str.length(); )//只能接收处理纯中文，下面的代码识别把中文摘出来处理
    {
        char32_t uhan = strtol(str.substr(i, 4).c_str(), nullptr, 16);
        u8str += converter.to_bytes(uhan);
        i += 6;
    }  */
    for (size_t i = 0; i < str.length(); )
    {
        size_t pos = str.find("\\u",i);
        if (pos == i)
        {
            char32_t uhan = strtol(str.substr(i+2, 4).c_str(), nullptr, 16);
            u8str += converter.to_bytes(uhan);
            i += 6;
            pos = i;
        }
        else
        {
            u8str += std::string(str, i, pos - i);
            i = pos;
        }
    }  
    return u8str;
}

// unicode 字节数组转中文
// 0x89 0x7F 0x5B 0x89 0x8D 0xEF ---> 西安路
std::string MyEnco::Unicode_CharToUTF8(unsigned char* s_src, int len)
{
    std::string u8str;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

    for (int i = 0; i < len; ) {
        char32_t uhan = s_src[i] << 8 | s_src[i + 1];
        u8str += converter.to_bytes(uhan);
        i += 2;
    }
    return u8str;
}

//unicode中英文转unicode的字符串
//asd你好阿---- > 0061007300644f60597d963f 
//stringToUnicode(stringStr).c_str())
std::string MyEnco::GBKToUnicode_string(const std::string& str)
{
    std::string unicodeStr;
    size_t length = strlen(str.c_str()) + 1;

    // char * setlocale ( int category, const char * locale );
    // 本函数用来配置地域的信息，设置当前程序使用的本地化信息.参数 locale 若是空字符串 ""，则会使用系统环境变量的 locale
    // 说明string中的字符编码是本机默认字符集，即GB字符集
    setlocale(LC_ALL, "");
    wchar_t wstr[1024];
    mbstowcs(wstr, str.c_str(), length);
    char charUnicode[5];

    for (size_t i = 0; i < wcslen(wstr); i++) {
        memset(charUnicode, '\0', 5);
        sprintf(charUnicode, "%04x", wstr[i]);
        unicodeStr.append(charUnicode);
    }
    return unicodeStr;
}
