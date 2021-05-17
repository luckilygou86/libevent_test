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
#include <event2/event.h>
#include <list>
#include <mutex>
class XTask;
class XThread
{
public:

	//启动线程
	void Start();

	//线程入口函数
	void Main();

	//安装线程，初始化event_base和管道监听事件用于激活
	bool Setup();

	//收到主线程发出的激活消息（线程池的分发）
	void Notify(evutil_socket_t fd, short which);

	//线程激活
	void Activate();

	//添加处理的任务，一个线程同时可以处理多个任务，共用一个event_base
	void AddTask(XTask *t);
	XThread();
	~XThread();

	//线程编号
	int id = 0;
private:
	int notify_send_fd = 0;
	struct event_base *base = 0;

	//任务列表
	std::list<XTask*> tasks;
	//线程安全 互斥
	std::mutex tasks_mutex;

};

