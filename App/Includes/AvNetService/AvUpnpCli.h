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
#ifndef __AV_UPNPCLI_H__
#define __AV_UPNPCLI_H__

#include "AvThread/AvTimer.h"
#include "AvConfigs/AvConfigNetService.h"
//#include "AvConfigs/AvConfigsNetWork.h"


class CAvUpnpCli : public CTimer
{
public:
	PATTERN_SINGLETON_DECLARE(CAvUpnpCli);
private:
	CAvUpnpCli();
	virtual ~CAvUpnpCli();

public:
	av_bool Start();
	av_bool Stop();
private:
	av_void OnTime();
	av_bool UpnpUpdateConfig();
	av_void AvConfigUpnp(CAvConfigNetUpnp* obj, int &num);

	int m_AvConfigChanged;
	CMutex m_Mutex;
	CAvConfigNetUpnp m_AvConfigNetUpnp;

	char m_LocalIP[16];
	int m_InternalPort[Mapping_NR];
};

#define g_AvDdnsCli (*CAvUpnpCli::instance())


#endif /*__AV_UPNPCLI_H__*/
