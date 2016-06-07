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
#include "AvNetService/AvDdnsCli.h"
#include "AvNetService/AvDdns.h"


PATTERN_SINGLETON_IMPLEMENT(CAvDdnsCli)

CAvDdnsCli::CAvDdnsCli():CTimer("AvDdnsCli")
{
	m_AvConfigChanged = 0;
}

CAvDdnsCli::~CAvDdnsCli()
{

}

av_bool CAvDdnsCli::Start()
{
	int ret = 0;
	//m_AvConfigsDdns.Update();
	m_AvConfigsDdns.Attach(this, (AvConfigCallBack)&CAvDdnsCli::AvConfigDdns);
	AvConfigDdns(&m_AvConfigsDdns, ret);
	StartTimer(1*1000, 5*1000, av_true, av_true);
	
	return av_true;
}

av_bool CAvDdnsCli::Stop()
{
	StopTimer();
	m_AvConfigsDdns.Detach(this, (AvConfigCallBack)&CAvDdnsCli::AvConfigDdns);	
	return av_true;
}

av_void CAvDdnsCli::OnTime()
{
	if (m_AvConfigChanged > 0)
	{
		m_Mutex.Enter();
		m_AvConfigChanged = 0;//�˴�Ҫ����
		m_Mutex.Leave();
		DdnsUpdateConfig();
	}
}

av_bool CAvDdnsCli::DdnsUpdateConfig()
{
	CAvDdns AvDdns;
	
	m_AvConfigsDdns.Update();
	ConfigNetDdns ddns_config;
	ddns_config = m_AvConfigsDdns.GetConfig();

	if (AvDdns.SetConf(ddns_config.Server, ddns_config.UsrName,ddns_config.Passwd) != av_true)
	{
		av_error("avddns setconf error...\n");
		return av_false;
	}
	AvDdns.Start();

	return av_true;
}

av_void CAvDdnsCli::AvConfigDdns(CAvConfigNetDdns* obj, int &num)
{
	m_Mutex.Enter();
	m_AvConfigChanged++;	//�˴�Ҫ����
	m_Mutex.Leave();
	av_msg("CAvDdnsCli m_AvConfigChanged = %d\n", m_AvConfigChanged);
}
