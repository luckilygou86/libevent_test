/*/*******************************************************************************
**                                                                            **
**                     Jiedi(China nanjing)Ltd.                               **
**	               创建：丁宋涛 夏曹俊，此代码可用作为学习参考                **
*******************************************************************************/

/*****************************FILE INFOMATION***********************************
**
** Project       : Libevent C＋＋高并发网络编程
** Contact       : xiacaojun@qq.com
**  博客   : http://blog.csdn.net/jiedichina
**	视频课程 : 网易云课堂	http://study.163.com/u/xiacaojun		
			   腾讯课堂		https://jiedi.ke.qq.com/				
			   csdn学院		http://edu.csdn.net/lecturer/lecturer_detail?lecturer_id=961	
**             51cto学院	http://edu.51cto.com/lecturer/index/user_id-12016059.html	
** 			   老夏课堂		http://www.laoxiaketang.com 
**                 
**  Libevent C＋＋高并发网络编程 课程群 ：1003847950 加入群下载代码和交流
**   微信公众号  : jiedi2007
**		头条号	 : 夏曹俊
**
*****************************************************************************
//！！！！！！！！！ Libevent C＋＋高并发网络编程 课程  QQ群：1003847950 下载代码和交流*/
#include "XFtpPORT.h"
#include <vector>
#include <iostream>
using namespace std;
void XFtpPORT::Parse(std::string type, std::string msg)
{
	//PORT 127,0,0,1,70,96\r\n
	//PORT n1,n2,n3,n4,n5,n6\r\n
	//port = n5*256 + n6

	//只获取ip和端口，不连接
	//取出ip
	vector<string> vals;
	string tmp = "";
	for (int i = 5; i < msg.size(); i++)
	{
		if (msg[i] == ',' || msg[i] == '\r')
		{
			vals.push_back(tmp);
			tmp = "";
			continue;
		}
		tmp += msg[i];
	}
	if (vals.size() != 6)
	{
		//PORT格式有误
		ResCMD("501 Syntax error in parameters or arguments.");
		return;
	}
	//for (int i = 0; i < vals.size(); i++)
	//{
	//	cout << vals[i] << endl;
	//}
	ip = vals[0]+"."+vals[1] + "." + vals[2] + "." + vals[3];
	////port = n5*256 + n6
	port = atoi(vals[4].c_str()) * 256 + atoi(vals[5].c_str());
	cout << "PORT ip is " << ip << endl;
	cout << "PORT port is " << port << endl;
	ResCMD("200 PORT command successful.\r\n");

}