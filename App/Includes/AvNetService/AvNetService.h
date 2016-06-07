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
#ifndef _AVNETSERVICE_H_
#define _AVNETSERVICE_H_
#include "Apis/AvWareType.h"

#include "CObject.h"


class CAvNetService
{
public:
	PATTERN_SINGLETON_DECLARE(CAvNetService);

	av_bool Initialize();
	av_bool Start();
	av_bool Stop();
	av_bool Restart();

private:
	CAvNetService();
	~CAvNetService();
};
#define g_AvNetService (*CAvNetService::instance())

#endif
