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
#include "AvNetService/AvDhcp.h"

CAvDhcp::CAvDhcp()
{
}

CAvDhcp::~CAvDhcp()
{
}



av_bool CAvDhcp::Start()
{
	return av_true;
}
av_bool CAvDhcp::Stop()
{
	return av_true;
}

av_bool CAvDhcp::GetResult(std::string &IpAddr, std::string &SubMask, std::string &GateWay, std::string &Dns1, std::string &Dns2)
{
	return av_true;
}