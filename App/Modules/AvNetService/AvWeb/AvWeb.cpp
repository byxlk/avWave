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
#include "AvNetService/AvWeb.h"

SINGLETON_IMPLEMENT(CAvWebSer)

CAvWebSer::CAvWebSer()
{
}

CAvWebSer::~CAvWebSer()
{
}

av_bool CAvWebSer::Start()
{
	WebStart();
	return av_true;
}
av_bool CAvWebSer::Stop()
{
	WebStop();
	return av_true;
}



int CAvWebSer::WebCallBackProc(std::string InBuf, std::string &OutBuf)
{
	av_msg("CAvWebSer::WebCallBackProc\n");
	puts(InBuf.c_str());
	return 0;
}
