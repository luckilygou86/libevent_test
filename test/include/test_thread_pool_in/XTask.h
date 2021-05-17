/*
 * @Description: 
 * @version: 
 * @Author: sql
 * @Date: 2021-05-13 09:55:31
 * @LastEditors: sql
 * @LastEditTime: 2021-05-13 12:12:43
 */

#pragma once
class XTask
{
public:
	struct event_base *base = 0;
	int sock = 0;
	int thread_id = 0;
	//初始化任务 纯虚函数，没有函数体，在声明的时候加个=0，含有纯虚函数的类为抽象类，实现动态多样性，
	//抽象类不能定义对象，当能定义指针，基类指针指向派生类的对象，抽象类既可以包含数据成员又可以包含方法
	virtual bool Init() = 0;
};

