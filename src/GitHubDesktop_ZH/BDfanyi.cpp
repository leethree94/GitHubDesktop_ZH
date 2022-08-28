#include "BDfanyi.h"
#include "MD5.h" 
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <Random>
#include <ctime>

//解决中文乱码问题，先将*.cpp文件格式改为“UTF-8 带签名”然后加入以下预编译内容
#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
//以上解决中文乱码

using namespace std;
/*
* curl/curl.h使用须知
* 1. 加入预编译选项：项目右键--》属性--》配置属性--》C/C++--》预处理器--》预处理器，
*     写入 UILDING_LIBCURL或CURL_STATICLIB
* 2. 加入附件依赖项，把 ws2_32.lib、 winmm.lib、 wldap32.lib写进去
*/
#ifdef _DEBUG
#pragma comment(lib,"libcurld.lib")
#else
#pragma comment(lib,"libcurl.lib")
#endif // DEBUG
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"wldap32.lib")

size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream)
{
    string data((const char*)ptr, (size_t)size * nmemb);
    *((stringstream*)stream) << data << endl;
    return size * nmemb;
}
BDfanyi::BDfanyi()
{
}
BDfanyi::BDfanyi(std::string myappid, std::string mysecret_key)
{
    this->appid = myappid;
    this->secret_key = mysecret_key;
}
BDfanyi::~BDfanyi()
{}
bool BDfanyi::Open()
{
    return false;
}
void BDfanyi::setappid(std::string myappid, std::string mysecret_key)
{
    this->appid = myappid;
    this->secret_key = mysecret_key;
}

string BDfanyi::Send(string q)
{
    if (appid.empty() || secret_key.empty())
    {
        cout << "error: baidu appid is empty or secret_key empty " << endl;
        return string();
    }
    CURL* curl = 0;
    CURLcode res;
    curl = curl_easy_init();

 //   string q = ""; //replace apple with your own text to be translate, ensure that the input text is encoded with UTF-8!
    string from = "en";          //replace en with your own language type of input text
    string to = "zh";            //replace zh with your own language type of output text

    string salt1 = "14346618"; //随机数
    salt1 += rand();    

    MD5 md;
    md.update(appid + q + salt1 + secret_key);
    string sign = md.toString();
//    cout << "sign= " << appid + q + salt1 + secret_key << endl;
    //http://api.fanyi.baidu.com/api/trans/vip/translate?q=apple&from=en&to=zh&appid=2015063000000001&salt=1435660288&sign=f89f9594663708c1605f3d736d01d2d4
    string url = "http://api.fanyi.baidu.com/api/trans/vip/translate?";
    //对待翻译字符串进行转义
    string q2 = curl_escape(q.c_str(), q.length());

    url += "q=" + q2;
    url += "&from=" + from;
    url += "&to=" + to;
    url += "&appid=" + appid;
    url += "&salt=" + salt1;
    url += "&sign=" + sign;
 //   cout << "myur= " << url << endl;

    //设置访问的地址,string需要进行转换
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    //设置接收数据的处理函数和存放变量
    std::stringstream out;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

    //执行HTTP GET操作
    res = curl_easy_perform(curl);
    /* Check for errors 检查错误*/
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        string error;
        return error;
    }     

    // 接受数据存放在out中，输出之
    //   cout << endl <<"out.str: " << out.str() << endl;
    string str_json = out.str();
    /* always cleanup总是清理 */
    curl_easy_cleanup(curl);

    string ss;
    string Mark = "\"dst\":\"";
    int len = Mark.length();
    size_t pos = 0; size_t cur = 0;
    pos = str_json.find(Mark, pos);//7位
    if (pos != string::npos)
    {
        cur = str_json.find('"', pos + len + 1);
        if (cur != string::npos)
        {
            string s1(str_json, pos + len, cur - pos - len);
            ss = s1;
        }           
    }   
    return ss;
}

