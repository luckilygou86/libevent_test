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
#include "XFtpTask.h"
#include <map>
class XFtpServerCMD :public XFtpTask
{
public:
	//��ʼ������
	virtual bool Init();
	virtual void Read(struct bufferevent *bev);
	virtual void Event(struct bufferevent *bev, short what);
	//ע���������� ����Ҫ�����̰߳�ȫ������ʱ��δ�ַ����߳�
	void Reg(std::string, XFtpTask *call);

	XFtpServerCMD();
	~XFtpServerCMD();
private:
	//ע��Ĵ������
	std::map<std::string, XFtpTask*>calls;
	//�������ռ�����
	std::map< XFtpTask*, int>calls_del;
};

