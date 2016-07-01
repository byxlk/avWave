/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: ironman [ironman@graceport.cn]
|  ����: 2016��6��6��
|  ˵��:
|
|  �汾: 1.1
|  ����:
|  ����:
|  ˵��:
******************************************************************/
#ifndef __AV_NTPCLI_H__
#define __AV_NTPCLI_H__

#include "AvThread/AvTimer.h"
#include "AvConfigs/AvConfigNetService.h"

class CAvNtpCli:public CTimer
{
public:
	SINGLETON_DECLARE(CAvNtpCli);
private:
	CAvNtpCli();
	virtual ~CAvNtpCli();

public:
	av_bool Start();
	av_bool Stop();
private:
	av_void OnTime();
	av_void AvConfigNtp(CAvConfigNetNtp* obj, int &num);

	CAvConfigNetNtp m_AvConfigNetNtp;
};

#define g_AvNtpCli (*CAvNtpCli::instance())

#endif /*__AV_NTPCLI_H__*/