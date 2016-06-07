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
#ifndef _AVDECODE_H_
#define _AVDECODE_H_
#include "Apis/AvWareType.h"
#include "CObject.h"

class CAvDecode
{
public:
	PATTERN_SINGLETON_DECLARE(CAvDecode);
	~CAvDecode();
	av_bool Initialize();

private:
	CAvDecode();
};

#define g_AvDecode (*CAvDecode::instance())


#endif


