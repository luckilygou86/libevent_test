/*/*******************************************************************************
**                                                                            **
**                     Jiedi(China nanjing)Ltd.                               **
**	               ������������ �Ĳܿ����˴��������Ϊѧϰ�ο�                **
*******************************************************************************/

/*****************************FILE INFOMATION***********************************
**
** Project       : Libevent C�����߲���������
** Contact       : xiacaojun@qq.com
**  ����   : http://blog.csdn.net/jiedichina
**	��Ƶ�γ� : �����ƿ���	http://study.163.com/u/xiacaojun		
			   ��Ѷ����		https://jiedi.ke.qq.com/				
			   csdnѧԺ		http://edu.csdn.net/lecturer/lecturer_detail?lecturer_id=961	
**             51ctoѧԺ	http://edu.51cto.com/lecturer/index/user_id-12016059.html	
** 			   ���Ŀ���		http://www.laoxiaketang.com 
**                 
**  Libevent C�����߲��������� �γ�Ⱥ ��1003847950 ����Ⱥ���ش���ͽ���
**   ΢�Ź��ں�  : jiedi2007
**		ͷ����	 : �Ĳܿ�
**
*****************************************************************************
//������������������ Libevent C�����߲��������� �γ�  QQȺ��1003847950 ���ش���ͽ���*/
#pragma once
#include "XTask.h"
#include <string>
class XFtpTask :public XTask
{
public:

	std::string curDir = "/";
	std::string rootDir = ".";

	//PORT ����ͨ����IP�Ͷ˿�
	std::string ip = "";
	int port = 0;
	
	//����ͨ��
	XFtpTask *cmdTask = 0;

	//����Э��
	virtual void Parse(std::string type, std::string msg) {}
	//�ظ�cmd��Ϣ
	void ResCMD(std::string msg);


	//�������ͽ��������ӵ�����ͨ��
	void Send(std::string data);
	void Send(const char*data,int datasize);

	//��������ͨ��
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
	//����bev
	struct bufferevent *bev = 0;
	FILE *fp = 0;


};

