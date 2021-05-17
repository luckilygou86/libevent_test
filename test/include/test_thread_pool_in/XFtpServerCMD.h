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
	//初始化任务 如果不能实现XTask中所有的纯虚函数，则这个派生类也成为了抽象类
	virtual bool Init();
	XFtpServerCMD();
	~XFtpServerCMD();
};

