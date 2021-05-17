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
#pragma once
#include "XTask.h"
#include <string>
class XFtpTask :public XTask
{
public:

	std::string curDir = "/";
	std::string rootDir = ".";

	//PORT 数据通道的IP和端口
	std::string ip = "";
	int port = 0;
	
	//命令通道
	XFtpTask *cmdTask = 0;

	//解析协议
	virtual void Parse(std::string type, std::string msg) {}
	//回复cmd消息
	void ResCMD(std::string msg);


	//用来发送建立了连接的数据通道
	void Send(std::string data);
	void Send(const char*data,int datasize);

	//连接数据通道
	void ConnectPORT();
	void Close();
	virtual void Read(struct bufferevent *bev) {}
	virtual void Write(struct bufferevent *bev) {}
	virtual void Event(struct bufferevent *bev,short what) {}
	void SetCallback(struct bufferevent *bev);
	bool Init() { return true; }
protected:
	static void ReadCB(bufferevent * bev, void *arg);
	static void WriteCB(bufferevent * bev, void *arg);
	static void EventCB(struct bufferevent *bev, short what, void *arg);
	//命令bev
	struct bufferevent *bev = 0;
	FILE *fp = 0;


};

