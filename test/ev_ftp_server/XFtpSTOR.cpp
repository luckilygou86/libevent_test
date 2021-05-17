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
#include "XFtpSTOR.h"
#include <iostream>
#include <event2/bufferevent.h>
#include <event2/event.h>
using namespace std;

//����Э��
void XFtpSTOR::Parse(std::string type, std::string msg)
{
	//�ļ���
	int pos = msg.rfind(" ") + 1;
	string filename = msg.substr(pos, msg.size() - pos - 2);
	string path = cmdTask->rootDir;
	path += cmdTask->curDir;
	path += filename;
	fp = fopen(path.c_str(), "wb");
	if (fp)
	{
		//��������ͨ��
		ConnectPORT();

		//���Ϳ�ʼ�����ļ���ָ��
		ResCMD("125 File OK\r\n");
		//������ȡ�¼�
		bufferevent_trigger(bev, EV_READ, 0);
	}
	else
	{
		ResCMD("450 file open failed!\r\n");
	}
}
void XFtpSTOR::Read(struct bufferevent *bev)
{
	if (!fp)return;
	for (;;)
	{
		int len = bufferevent_read(bev, buf, sizeof(buf));
		if (len <= 0)
			return;
		int size = fwrite(buf, 1, len, fp);
		cout << "<"<<len<<":"<<size << ">" << flush;
	}
}
void XFtpSTOR::Event(struct bufferevent *bev, short what)
{
	//����Է�����ϵ������߻��������п����ղ���BEV_EVENT_EOF����
	if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | BEV_EVENT_TIMEOUT))
	{
		cout << "XFtpSTOR BEV_EVENT_EOF | BEV_EVENT_ERROR |BEV_EVENT_TIMEOUT" << endl;
		Close();
		ResCMD("226 Transfer complete\r\n");
	}
	else if (what&BEV_EVENT_CONNECTED)
	{
		cout << "XFtpSTOR BEV_EVENT_CONNECTED" << endl;
	}
}