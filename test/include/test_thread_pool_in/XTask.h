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
	//��ʼ������ ���麯����û�к����壬��������ʱ��Ӹ�=0�����д��麯������Ϊ�����࣬ʵ�ֶ�̬�����ԣ�
	//�����಻�ܶ�����󣬵��ܶ���ָ�룬����ָ��ָ��������Ķ��󣬳�����ȿ��԰������ݳ�Ա�ֿ��԰�������
	virtual bool Init() = 0;
};

