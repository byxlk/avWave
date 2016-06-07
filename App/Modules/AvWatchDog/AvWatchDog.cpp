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
#include "AvWatchDog/AvWatchDog.h"
#include "Apis/AvWareType.h"
#include "Apis/LibSystem.h"

PATTERN_SINGLETON_IMPLEMENT(CWatchDog);

CWatchDog::CWatchDog() :CThread(__FUNCTION__)
{

}
CWatchDog::~CWatchDog()
{
}
av_bool CWatchDog::Initialize()
{
	av_msg("%s Started\n", __FUNCTION__);
	Open();
	CThread::run();
	return av_true;
}

void CWatchDog::ThreadProc()
{
	while (m_Loop == av_true){
		av_msleep(1000 * 3);
		Feed();
	}
}


av_bool CWatchDog::Open()
{
	return AvWatchDogInit(5);
}
av_bool CWatchDog::Close()
{
	AvWatchDogDeInit();
	return CThread::stop();
}
av_bool CWatchDog::Feed()
{
	return AvWatchDogFeed();
}
