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
#include "XFtpPORT.h"
#include <vector>
#include <iostream>
using namespace std;
void XFtpPORT::Parse(std::string type, std::string msg)
{
	//PORT 127,0,0,1,70,96\r\n
	//PORT n1,n2,n3,n4,n5,n6\r\n
	//port = n5*256 + n6

	//ֻ��ȡip�Ͷ˿ڣ�������
	//ȡ��ip
	vector<string> vals;
	string tmp = "";
	for (int i = 5; i < msg.size(); i++)
	{
		if (msg[i] == ',' || msg[i] == '\r')
		{
			vals.push_back(tmp);
			tmp = "";
			continue;
		}
		tmp += msg[i];
	}
	if (vals.size() != 6)
	{
		//PORT��ʽ����
		ResCMD("501 Syntax error in parameters or arguments.");
		return;
	}
	//for (int i = 0; i < vals.size(); i++)
	//{
	//	cout << vals[i] << endl;
	//}
	ip = vals[0]+"."+vals[1] + "." + vals[2] + "." + vals[3];
	////port = n5*256 + n6
	port = atoi(vals[4].c_str()) * 256 + atoi(vals[5].c_str());
	cout << "PORT ip is " << ip << endl;
	cout << "PORT port is " << port << endl;
	ResCMD("200 PORT command successful.\r\n");

}