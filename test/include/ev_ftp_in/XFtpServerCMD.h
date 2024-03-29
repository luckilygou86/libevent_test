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
#include "XFtpTask.h"
#include <map>
class XFtpServerCMD :public XFtpTask
{
public:
	//初始化任务
	virtual bool Init();
	virtual void Read(struct bufferevent *bev);
	virtual void Event(struct bufferevent *bev, short what);
	//注册命令处理对象 不需要考虑线程安全，调用时还未分发到线程
	void Reg(std::string, XFtpTask *call);

	XFtpServerCMD();
	~XFtpServerCMD();
private:
	//注册的处理对象
	std::map<std::string, XFtpTask*>calls;
	//用来做空间清理
	std::map< XFtpTask*, int>calls_del;
};

