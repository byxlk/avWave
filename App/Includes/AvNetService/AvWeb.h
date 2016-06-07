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
#include "Apis/AvWareType.h"
#include "CObject.h"
#include "WebService/LibWebService.h"

class CAvWebSer:public CWebService
{
public:
	PATTERN_SINGLETON_DECLARE(CAvWebSer);
	av_bool Start();
	av_bool Stop();

private:
	CAvWebSer();
	~CAvWebSer();

private:
	int WebCallBackProc(std::string InBuf, std::string &OutBuf);

};


#define g_AvWebSer (*CAvWebSer::instance())

