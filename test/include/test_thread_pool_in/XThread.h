/*
 * @Description: 
 * @version: 
 * @Author: sql
 * @Date: 2021-05-13 09:55:31
 * @LastEditors: sql
 * @LastEditTime: 2021-05-13 12:33:49
 */

#pragma once
#include <event2/event.h>
#include <list>
#include <mutex>
class XTask;
class XThread
{
public:

	//�����߳�
	void Start();

	//�߳���ں���
	void Main();

	//��װ�̣߳���ʼ��event_base�͹ܵ������¼����ڼ���
	bool Setup();

	//�յ����̷߳����ļ�����Ϣ���̳߳صķַ���
	void Notify(evutil_socket_t fd, short which);

	//�̼߳���
	void Activate();

	//��Ӵ��������һ���߳�ͬʱ���Դ��������񣬹���һ��event_base
	void AddTask(XTask *t);
	XThread();
	~XThread();

	//�̱߳��
	int id = 0;
private:
	int notify_send_fd = 0;
	struct event_base *base = 0;

	//�����б�
	std::list<XTask*> tasks;
	//�̰߳�ȫ ����
	std::mutex tasks_mutex;

};

