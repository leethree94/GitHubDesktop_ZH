//解决中文乱码问题，先将*.cpp文件格式改为“UTF-8 带签名”然后加入以下预编译内容
#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
//# pragma execution_character_set("utf-8")    
#endif
//以上解决中文乱码
#include "MyEnco.h"
#include "BDfanyi.h"
#include "myWord.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    bool isExit=false;
    string ch;
    cout << "首先从 GitHubDesktop\\app-3.0.x\\resources\\app 拷贝 renderer.js和main.js到本软件的Eng_SRC文件夹" << endl
        << endl;
    while (!isExit)
    {
        cout << "1: 从文件夹 Eng_SRC 获得英文词条,存放在EngtoZh文件夹" << endl
            << "2: 将文件夹 EngtoZh 的英文词条使用百度翻译api进行翻译" << endl
            << "3: 从文件夹 EngtoZh 获得中英对照,通过Eng_SRC输出结果至文件夹Zh_OUT" << endl
            << "4: 退出" << endl;
        cin >> ch;
        switch (ch[0])
        {
        case '1':
        {
            myWord mw;
            char cr[10] = { '-','\'','\"','+',':','\.','[' ,'*' };
            mw.getFileEng("./Eng_SRC/renderer.js", "label:\"", cr);
            mw.getFileEng("./Eng_SRC/renderer.js", "error(\"", cr);
            mw.getFileEng("./Eng_SRC/renderer.js", "null,\"", cr);
            mw.getFileEng("./Eng_SRC/main.js", "label:\"", cr);
            mw.getFileEng("./Eng_SRC/main.js", "error(\"", cr);
            mw.getFileEng("./Eng_SRC/main.js", "null,\"", cr);
            mw.printf();
            mw.testWrite("./EngtoZh/baidujieguo.txt");
            
        }break;
        case '2':
        {
            myWord mw2;
            string appid,key;
            cout << "输入百度翻译的APPID " << endl;
            cin >> appid;
            cout << "APPID： "<< appid << endl;
            cout << "输入百度翻译的密钥 " << endl;
            cin >> key;
            cout << "密钥： " << key << endl;
            BDfanyi ss(appid, key);
            mw2.readMap("./EngtoZh/baidujieguo.txt");                      
            mw2.EngtoZh(ss,3,1);
            mw2.testWrite("./EngtoZh/baidujieguo.txt");
        }break;
        case '3':
        {
            myWord mw3;
            mw3.readMap("./EngtoZh/baidujieguo.txt");
            mw3.printf();
            mw3.myReplace("./Eng_SRC/renderer.js", "./Zh_OUT/renderer.js");
            mw3.myReplace("./Eng_SRC/main.js", "./Zh_OUT/main.js");
        }break;
        case '4':
        {
            isExit = true;
        }break;
        default:
            break;
        }

    }
    std::cout << "Hello World!\n";
}

