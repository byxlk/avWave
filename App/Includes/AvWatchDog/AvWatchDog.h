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
#ifndef _AVWATCHDOG_H_
#define _AVWATCHDOG_H_

#include "Apis/AvWareType.h"
#include "CAvObject.h"
#include "AvThread/AvThread.h"
class CWatchDog :public CThread
{
public:
	SINGLETON_DECLARE(CWatchDog);
	
	av_bool Initialize();
	void ThreadProc();
	av_bool Open();
	av_bool Close();
	av_bool Feed();

private:
	CWatchDog();
	~CWatchDog();
};

#define g_AvWatchDog (*CWatchDog::instance())

#endif

