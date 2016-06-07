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
#ifndef _AV_DDNS_H_
#define _AV_DDNS_H_
#include "Apis/AvWareType.h"

typedef enum
{
	DDNS_3322_TYPE,
}DDNS_TYPE;

class CAvDdns
{
public:	
	CAvDdns();
	~CAvDdns();

	av_bool Start();
	av_bool Stop();
	
	av_bool SetConf(std::string server, std::string usrname, std::string passwd);

private:
	std::string m_Server;
	std::string m_Usrname;
	std::string m_Passwd;
	DDNS_TYPE   m_DdnsType;
};








#endif