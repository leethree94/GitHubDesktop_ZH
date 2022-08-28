#pragma once
#include <string>
#include <curl/curl.h>

class BDfanyi
{
public:
	BDfanyi();
	BDfanyi(std::string myappid, std::string mysecret_key);
	~BDfanyi();
	//设置账号密码；
	void setappid(std::string myappid, std::string mysecret_key);
	static bool Open();
	//发送英文给百度翻译，获得unicode编码格式的字符串的中文结果
	//\\u5199\\u4fe1\\u7ed9\\u75c5\\u623f 
	std::string Send(std::string q);
	
private:
	std::string appid;// = ;    //replace myAppid with your own appid
	std::string secret_key;// = ;  //ZsHggpmIXEhgAu_iA0Gz //replace mySecretKey with your own mySecretKey
};

