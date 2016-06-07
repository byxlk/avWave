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
#ifndef _AVEXTERNINTERFACE_H_
#define _AVEXTERNINTERFACE_H_

#include "CObject.h"
#include "Apis/AvWareType.h"

class CAvExtInterFace
{
public:
	PATTERN_SINGLETON_DECLARE(CAvExtInterFace);
	
public:
	av_bool Initialize();
	av_bool Start();
	av_bool Stop();
	av_bool Restart();
	
private:
	CAvExtInterFace();
	~CAvExtInterFace();
};

#define g_AvExtInterFace (*CAvExtInterFace::instance())







#endif

