/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: Knight [knight@graceport.cn]
|  ����: 2016��6��6��
|  ˵��:
|
|  �汾: 1.1
|  ����:
|  ����:
|  ˵��:
******************************************************************/
#ifndef _AVUSER_H_
#define _AVUSER_H_
#include "Apis/AvWareType.h"
#include "CAvObject.h"

class CAvUser
{
public:
	SINGLETON_DECLARE(CAvUser)
private:
	CAvUser();
	~CAvUser();

public:
	av_bool AddGroup();
	av_bool DelGroup();
	av_bool ModifyGroup();
	av_bool GroupList();

	av_bool AddUser();
	av_bool DelUser();
	av_bool ModifyUser();
	av_bool CheckOut();
private:

};


#define g_AvUser (*CAvUser::instance())



#endif