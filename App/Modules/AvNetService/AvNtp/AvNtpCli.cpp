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
#include "AvNetService/AvNtp.h"
#include "AvNetService/AvNtpCli.h"

SINGLETON_IMPLEMENT(CAvNtpCli)

CAvNtpCli::CAvNtpCli():CTimer("AvNtpCli")
{

}

CAvNtpCli::~CAvNtpCli()
{

}

av_bool CAvNtpCli::Start()
{
	int ret = 0;
	m_AvConfigNetNtp.Attach(this, (AvConfigCallBack)&CAvNtpCli::AvConfigNtp);
	AvConfigNtp(&m_AvConfigNetNtp, ret);
	return av_true;
}

av_bool CAvNtpCli::Stop()
{
	if (GetStatus() != UnStart)
	{
		StopTimer();
	}
	m_AvConfigNetNtp.Detach(this, (AvConfigCallBack)&CAvNtpCli::AvConfigNtp);
	return av_true;
}

av_void CAvNtpCli::OnTime()
{
	CAvNtp AvNtp;
	m_AvConfigNetNtp.Update();
	ConfigNetNtp ntp_config = m_AvConfigNetNtp.GetConfig();
	AvNtp.SetNtpServer(ntp_config.Server);
	AvNtp.SetTimeZone((av_timezone_t)ntp_config.Zone);
	AvNtp.Start();
}

av_void CAvNtpCli::AvConfigNtp(CAvConfigNetNtp* obj, int &num)
{
	ConfigNetNtp ntp_config = obj->GetConfig();
	av_msg("CAvNtpCli::AvConfigNtp Enable = %d\n", ntp_config.Enable);

	if (GetStatus() != UnStart)
	{
		StopTimer();
	}
	
	if (ntp_config.Enable == av_true)
	{		
		StartTimer(1*1000, 5*1000, av_true, av_true);
	}
	m_AvConfigNetNtp.Update();
}
