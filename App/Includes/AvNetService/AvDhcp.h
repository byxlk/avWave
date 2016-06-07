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
#ifndef _AV_DHCP_H_
#define _AV_DHCP_H_

#include "Apis/AvWareType.h"


class CAvDhcp
{
public:
	CAvDhcp();
	~CAvDhcp();

	av_bool Start();
	av_bool Stop();
	
	av_bool GetResult(std::string &IpAddr, std::string &SubMask, std::string &GateWay, std::string &Dns1, std::string &Dns2);

private:

};



#endif