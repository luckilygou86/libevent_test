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
#include "XFtpRETR.h"
#include <iostream>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <string>
using namespace std;


void XFtpRETR::Write(struct bufferevent *bev)
{
	if (!fp)return;
	int len = fread(buf, 1, sizeof(buf), fp);
	if (len <= 0)
	{
		ResCMD("226 Transfer complete\r\n");
		Close();
		return;
	}
		
	cout << "[" << len << "]" << flush;
	Send(buf, len);
}

void XFtpRETR::Event(struct bufferevent *bev, short what)
{
	//����Է�����ϵ������߻��������п����ղ���BEV_EVENT_EOF����
	if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | BEV_EVENT_TIMEOUT))
	{
		cout << "BEV_EVENT_EOF | BEV_EVENT_ERROR |BEV_EVENT_TIMEOUT" << endl;
		Close();
	}
	else if (what&BEV_EVENT_CONNECTED)
	{
		cout << "XFtpRETR BEV_EVENT_CONNECTED" << endl;
	}
}
//����Э��
void XFtpRETR::Parse(std::string type, std::string msg)
{
	//�ļ���
	int pos = msg.rfind(" ") + 1;
	string filename = msg.substr(pos, msg.size() - pos - 2);
	string path = cmdTask->rootDir;
	path += cmdTask->curDir;
	path += filename;
	fp = fopen(path.c_str(), "rb");
	if (fp)
	{
		//��������ͨ��
		ConnectPORT();
		
		//���Ϳ�ʼ�����ļ���ָ��
		ResCMD("150 File OK\r\n");
		//����д���¼�
		bufferevent_trigger(bev, EV_WRITE, 0);
	}
	else
	{
		ResCMD("450 file open failed!\r\n");
	}
}