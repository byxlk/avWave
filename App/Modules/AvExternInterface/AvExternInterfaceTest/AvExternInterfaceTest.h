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
#ifndef _AVEXTERNINTERFACETEST_H_
#define _AVEXTERNINTERFACETEST_H_


#include "AvPacket/AvPacket.h"
#include "Apis/AvWareType.h"
#include "CObject.h"
class CAvExtInterFaceTest :public CObject
{
public:
	PATTERN_SINGLETON_DECLARE(CAvExtInterFaceTest);
	
	av_bool Start();
	av_bool Stop();
private:
	av_void OnStream(av_uchar Channel, av_uchar Slave, CPacket &packet);

private:
	CAvExtInterFaceTest();
	~CAvExtInterFaceTest();
};

#define g_AvExtInterFaceTest (*CAvExtInterFaceTest::instance())







#endif



