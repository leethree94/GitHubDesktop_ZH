#pragma once
#include "BDfanyi.h"
#include <string>
#include <map>
#include <list>

struct EngtoZhMap
{
	std::map<std::string, std::string> mp;
	std::string Engstr[2048];
	std::string Chstr[2048];
	int Eline = 0;
	int Cline = 0;
};

class myWord
{
public:
	myWord();
	~myWord();
	/**
	* @brief myReplace 替换关键词
	* @param Src
	* @param Out
	* @param Eng
	* @param Ch
	* @return
	*/
	int myReplace(std::string Src, std::string Out, std::string eng, std::string ch);

	/**
	* @brief myReplace 替换关键词
	* @param Src
	* @param Out
	*/
	int myReplace(std::string Src, std::string Out);
	/*
	* 从文件读取字典
	*/
	int readMap(std::string EngZh);
	/*
	* 从文件读取字典
	*/
	int readMap(std::string eng, std::string ch);
	/*
	* 从文件读取字典
	*/
	bool getMap(std::string Src, std::string Out, std::string Mark, bool isClear);



	// 从文件读取英文词条，最多存放2048个
	// Src：源文件名；out:输出文件名，Mark：过滤词，
	bool getFileEng(std::string Src, std::string Mark,char cs[]);

	// 从字典取英文词条，使用百度API进行翻译，再替换字典里面的中文内容
	// isClearZh：是否将字典内的中文全部清掉，
	int EngtoZh(BDfanyi &fy,int retry ,bool isClearZh = 0);

	//打印字典里面的文字
	void printf();
	//测试写,将字符串str写到文件Out里面
	bool testWrite(std::string str, std::string Out);

	//测试写,将字典EngtoZh out写到文件Out里面
	bool testWrite(std::string Out);
	std::map<std::string, std::string> mp =
	{
		{"\"Add &local repository…\"" , "\"添加&本地存储库...\""},
		{"\"Clo&ne repository…\"" , "\"克隆存储库\""},
		{"\"&Options…\""  ,  "\"选项…\""},
		{"\"Select &all\""  ,  "\"全选\""},
		{"\"&History\""  ,  "\"＆历史\""},
		{"\"Repository &list\""  ,  "\"存储库列表\""},
		{"\"Go to &Summary\""  ,  "\"转到摘要\""},
		{"\"Toggle &full screen\""  ,  "\"切换全屏\""},
		{"\"Reset zoom\""  ,  "\"重置缩放\""},
		{"\"Zoom in\""  ,  "\"放大\""},
	};
	//may

private:
	EngtoZhMap out;
	std::string Engstr[2048];
	std::string Chstr[2048];
	int Eline = 0;
	int Cline = 0;
};

