/*
 * @Description: 
 * @version: 
 * @Author: sql
 * @Date: 2021-05-13 09:55:31
 * @LastEditors: sql
 * @LastEditTime: 2021-05-13 11:06:08
 */
#include "XThreadPool.h"
#include "XThread.h"
#include <thread>
#include <iostream>
#include <unistd.h>

#include "XTask.h"
using namespace std;
//�ַ��߳�
void XThreadPool::Dispatch(XTask *task)
{
	//��ѯ
	if (!task)return;
	int tid = (lastThread + 1) % threadCount;
	lastThread = tid;
	XThread *t = threads[tid];

	t->AddTask(task);

	//�����߳�
	t->Activate();


}
//��ʼ�������̲߳������߳�
void XThreadPool::Init(int threadCount)
{
	this->threadCount = threadCount;
	this->lastThread = -1;
	for (int i = 0; i < threadCount; i++)
	{
		XThread *t = new XThread();
		t->id = i + 1;
		cout << "Create thread " << i << endl;
		//�����߳�
		t->Start();
		threads.push_back(t);
		//this_thread::sleep_for(10ms);
		usleep(10000);
	}
}