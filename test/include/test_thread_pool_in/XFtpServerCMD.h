/*
 * @Description: 
 * @version: 
 * @Author: sql
 * @Date: 2021-05-13 09:55:31
 * @LastEditors: sql
 * @LastEditTime: 2021-05-13 11:41:26
 */

#pragma once
#include "XTask.h"
class XFtpServerCMD :public XTask
{
public:
	//��ʼ������ �������ʵ��XTask�����еĴ��麯���������������Ҳ��Ϊ�˳�����
	virtual bool Init();
	XFtpServerCMD();
	~XFtpServerCMD();
};

