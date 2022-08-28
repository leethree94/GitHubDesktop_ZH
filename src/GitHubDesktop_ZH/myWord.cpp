#include "myWord.h"
#include <iostream>
#include <fstream>
#include "MyEnco.h"
//解决中文乱码问题，先将*.cpp文件格式改为“UTF-8 带签名”然后加入以下预编译内容
#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
    #pragma execution_character_set("utf-8")    
#endif
//以上解决中文乱码
using namespace std;
myWord::myWord()
{

}
myWord::~myWord()
{

}
bool myWord::testWrite(std::string Out)
{
    ofstream out(Out);
    map<string, string>::iterator iter;
    iter = this->out.mp.begin();
    while (iter != this->out.mp.end()) 
    {
        out << iter->first  << endl;
        out << iter->second << endl;
        iter++;
    }
    return true;
}

bool myWord::testWrite(std::string str, std::string Out)
{
    ofstream out(Out);
        out << str << endl;
    out.close();
    return true;
}
int myWord::myReplace(std::string Src, std::string Out, std::string eng, std::string ch)
{
    ifstream fix(Src);
    ifstream Eng(eng);
    ifstream Zh(ch);
    if (!fix.is_open() || !Eng.is_open() || !Zh.is_open())
        return 0;
    ofstream out(Out);
    string str;
    size_t pos = 0;   
   
    while (getline(fix, str))
    {
        for (int i = 0; i < Eline; i++)
        {
            string Estr = Engstr[i];
            string Cstr = Chstr[i];
            if (Estr.length() > 2)
            {
                pos = str.find(Estr);
                if (pos != string::npos)
                {
                    //将当前字符串从pos索引开始的n个字符，替换成字符串s
                    str = str.replace(pos, Estr.length(), Cstr);
                }
            }
        }
        out << str;
    }
    return true;
}
int myWord::myReplace(std::string Src, std::string Out)
{
    ifstream fix(Src);
    if (!fix.is_open())
        return 0;
    ofstream out(Out);
    string str;
    size_t pos = 0;
    while (getline(fix, str))
    {
        map<string, string>::iterator iter;
        iter = this->out.mp.begin();
        while (iter != this->out.mp.end()) 
        {
            string Estr = "\"" + iter->first + "\"";
            string Cstr = "\"" + iter->second + "\"";
            while (pos != string::npos)
            {            
                pos = str.find(Estr);
                if (pos != string::npos)
                {
                    //将当前字符串从pos索引开始的n个字符，替换成字符串s
                    str = str.replace(pos, Estr.length(), Cstr);
                    cout << Src << "  " << Estr << " ->Replace to-> " << Cstr << endl;
                }
            }
            iter++; 
            pos = 0;
        }
        out << str;
    }
    return true;
}
/*
* 从文件获取字典
*/
int myWord::readMap(std::string eng, std::string ch)
{
    ifstream Eng(eng);
    ifstream Zh(ch);
    if (!Eng.is_open() || !Zh.is_open())
        return 0;
    string str;
    size_t pos = 0;
    while (getline(Eng, Engstr[Eline]) && Eline < 2047)
    {
        //cout <<  Engstr[Eline] << endl;
        Eline++;
    }
    while (getline(Zh, Chstr[Cline]) && Cline < 2047)
    {
        Cline++;
    }
    cout << "getline  " << Eline << " * " << Cline << endl;
    if (Eline != Cline)
        return 0;
    else
        return Eline;
}
/*
* 从文件获取字典
*/
int myWord::readMap(std::string EngZh)
{
    ifstream Eng(EngZh);
    if (!Eng.is_open())
        return 0;
    string Engstr;
    string Zhstr;
    size_t pos = 0;
    while (getline(Eng, Engstr))
    {
        getline(Eng, Zhstr);
        if(!Engstr.empty())
        out.mp.insert(pair<string, string>(Engstr, Zhstr));
        out.Cline++; out.Eline++;
    }
    Eng.close();
    return true;

}
bool myWord::getMap(string Src, string Out, string Mark, bool isClear)
{
    ifstream fix(Src);
    ofstream out;
    if (!fix.is_open()) return false;
    if (isClear)
        out.open(Out);
    else
        out.open(Out, ios::app);
    string str;
    int len = Mark.length();
    int count = 0;
    //string Mark = "label:\""; //7位
    while (getline(fix, str))
    {
        size_t pos = 0;
        size_t cur = 0;
        while (pos != string::npos)
        {
            pos = str.find(Mark, pos);
            if (pos != string::npos)
            {
                cur = str.find('"', pos + len + 1);
                if (cur != string::npos)
                {
                    string ss(str, pos + len - 1, cur - pos - len + 2);

                    cout << count + 1 << "pos: " << pos << " * " << ss << endl;
                    if (ss.length() > 6)
                    {
                        out << ss << endl;
                        count++;
                    }
                }
                pos = cur;
            }
        }
    }
    fix.close();
    out.close();
    return true;
}

bool myWord::getFileEng(std::string Src, std::string Mark, char cs[])
{
    ifstream fix(Src);
    if (!fix.is_open()) return false;
    string str;
    int len = Mark.length();
    int count = 0;
    //string Mark = "label:\""; //7位
    size_t pos = 0;
    size_t cur = 0;
    while (getline(fix, str))
    {
        while (pos != string::npos)
        {
            pos = str.find(Mark, pos);//查找关键词
            if (pos != string::npos)
            {
                cur = str.find('"', pos + len + 1);//查找关键词后面的'"'号
                if (cur != string::npos)
                {
                    //提取目标词
                    string ss(str, pos + len, cur - pos - len);
                    for (int i = 0; i < sizeof(cs); i++)
                    {
                        if (ss.find(cs[i]) != string::npos)
                            ss = "0";
                    }
                    if (ss.length() > 6 && ss.length() < 80)
                    {
                        out.mp.insert(pair<string, string>(ss, "0"));
                       // cout << "pos: " << pos << " * " << ss << endl;
                    }                   
                }     
            pos += len;
            }           
        }
        pos = 0;cur = 0;
    }
    fix.close();
    return true;
}
void myWord::printf()
{
    map<string, string>::iterator iter;
    iter = out.mp.begin();
    while (iter != out.mp.end()) {
        string eng = iter->first;    
        cout << " " << iter->first <<" --> " << MyEnco::UTF8ToGBK(iter->second) << endl;
        iter++;
    }
}

// 从字典取英文词条，使用百度API进行翻译，再替换字典里面的中文内容
// isClearZh：是否将字典内的中文全部清掉，
int myWord::EngtoZh(BDfanyi &fy,int retry ,bool isClearZh)
{
    map<string, string>::iterator iter;
    iter = out.mp.begin();
    int re = 0;
    while (iter != out.mp.end()) 
    {
        string eng = iter->first;
        //检查删掉英文字段里面的'&'
        size_t pos = eng.find('&');
        if (pos != string::npos) eng.erase(pos, 1);
        //当对应的中文不存在或要替换全部中文时
        if (iter->second.length() < 3 || isClearZh)
        {        
            for (int i = 0; i < retry; i++)
            {            
                string UnZh = fy.Send(eng);
                if (!UnZh.empty())
                {
                    string Zh = MyEnco::Unicode_stringToUTF8(UnZh);
                    iter->second = Zh;
                    i = retry + 1;
                }
                else
                    if (i == retry - 1)
                        re++;
            }
        }
        cout << " " << eng << " --> " << MyEnco::UTF8ToGBK(iter->second) << endl;
        iter++;
    }
    return re;
}