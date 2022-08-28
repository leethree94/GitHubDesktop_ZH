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
	* @brief myReplace �滻�ؼ���
	* @param Src
	* @param Out
	* @param Eng
	* @param Ch
	* @return
	*/
	int myReplace(std::string Src, std::string Out, std::string eng, std::string ch);

	/**
	* @brief myReplace �滻�ؼ���
	* @param Src
	* @param Out
	*/
	int myReplace(std::string Src, std::string Out);
	/*
	* ���ļ���ȡ�ֵ�
	*/
	int readMap(std::string EngZh);
	/*
	* ���ļ���ȡ�ֵ�
	*/
	int readMap(std::string eng, std::string ch);
	/*
	* ���ļ���ȡ�ֵ�
	*/
	bool getMap(std::string Src, std::string Out, std::string Mark, bool isClear);



	// ���ļ���ȡӢ�Ĵ����������2048��
	// Src��Դ�ļ�����out:����ļ�����Mark�����˴ʣ�
	bool getFileEng(std::string Src, std::string Mark,char cs[]);

	// ���ֵ�ȡӢ�Ĵ�����ʹ�ðٶ�API���з��룬���滻�ֵ��������������
	// isClearZh���Ƿ��ֵ��ڵ�����ȫ�������
	int EngtoZh(BDfanyi &fy,int retry ,bool isClearZh = 0);

	//��ӡ�ֵ����������
	void printf();
	//����д,���ַ���strд���ļ�Out����
	bool testWrite(std::string str, std::string Out);

	//����д,���ֵ�EngtoZh outд���ļ�Out����
	bool testWrite(std::string Out);
	std::map<std::string, std::string> mp =
	{
		{"\"Add &local repository��\"" , "\"���&���ش洢��...\""},
		{"\"Clo&ne repository��\"" , "\"��¡�洢��\""},
		{"\"&Options��\""  ,  "\"ѡ�\""},
		{"\"Select &all\""  ,  "\"ȫѡ\""},
		{"\"&History\""  ,  "\"����ʷ\""},
		{"\"Repository &list\""  ,  "\"�洢���б�\""},
		{"\"Go to &Summary\""  ,  "\"ת��ժҪ\""},
		{"\"Toggle &full screen\""  ,  "\"�л�ȫ��\""},
		{"\"Reset zoom\""  ,  "\"��������\""},
		{"\"Zoom in\""  ,  "\"�Ŵ�\""},
	};
	//may

private:
	EngtoZhMap out;
	std::string Engstr[2048];
	std::string Chstr[2048];
	int Eline = 0;
	int Cline = 0;
};

