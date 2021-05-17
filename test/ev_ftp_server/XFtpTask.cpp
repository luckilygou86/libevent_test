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
#include "XFtpTask.h"
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <iostream>
#include <string.h>
using namespace std;
void XFtpTask::Send(std::string data)
{
	Send(data.c_str(), data.size());
}
void XFtpTask::Send(const char*data, int datasize)
{
	if (!bev)return;
	bufferevent_write(bev, data, datasize);
}
void XFtpTask::Close()
{
	if (bev)
	{
		bufferevent_free(bev);
		bev = 0;
	}
	if (fp)
	{
		fclose(fp);
		fp = 0;
	}
}
//连接数据通道
void XFtpTask::ConnectPORT()
{
	if (ip.empty() || port <= 0 || !base)
	{
		cout << "ConnectPORT failed ip or port or base is null" << endl;
		return;
	}
	Close();
	bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	evutil_inet_pton(AF_INET, ip.c_str(), &sin.sin_addr.s_addr);
	//设置回调和权限
	SetCallback(bev);
	//添加超时 
	timeval rt = { 60,0 };
	bufferevent_set_timeouts(bev, &rt, 0);
	bufferevent_socket_connect(bev, (sockaddr*)&sin, sizeof(sin));
}
//回复cmd消息
void XFtpTask::ResCMD(string msg)
{
	if (!cmdTask || !cmdTask->bev)return;
	cout << "ResCMD:" << msg << endl;
	if (msg[msg.size() - 1] != '\n')
		msg += "\r\n";
	bufferevent_write(cmdTask->bev, msg.c_str(), msg.size());
}
void XFtpTask::SetCallback(struct bufferevent *bev)
{
	bufferevent_setcb(bev, ReadCB, WriteCB, EventCB, this);
	bufferevent_enable(bev, EV_READ | EV_WRITE);
}

void XFtpTask::ReadCB(bufferevent * bev, void *arg)
{
	XFtpTask *t = (XFtpTask *)arg;
	t->Read(bev);
}
void XFtpTask::WriteCB(bufferevent * bev, void *arg)
{
	XFtpTask *t = (XFtpTask *)arg;
	t->Write(bev);
}
void XFtpTask::EventCB(struct bufferevent *bev, short what, void *arg)
{
	XFtpTask *t = (XFtpTask *)arg;
	t->Event(bev,what);
}