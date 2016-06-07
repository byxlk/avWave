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
#include "AvExternInterface/AvExternInterface.h"
#include "AvExternInterfaceTest/AvExternInterfaceTest.h"
#include "AvMoon/AvMoon.h"

PATTERN_SINGLETON_IMPLEMENT(CAvExtInterFace)

av_bool CAvExtInterFace::Initialize()
{
	av_msg("%s Started\n", __FUNCTION__);
	av_bool ret = Start();
	return ret;
}
av_bool CAvExtInterFace::Start()
{
	//g_AvExtInterFaceTest.Start();
	g_CAvMoon.StartMoon();

	return av_true;
}
av_bool CAvExtInterFace::Stop()
{
	//g_AvExtInterFaceTest.Stop();
	g_CAvMoon.StopMoon();
	return av_true;
}
av_bool CAvExtInterFace::Restart()
{
	Stop();

	Start();

	return av_true;
}


CAvExtInterFace::CAvExtInterFace()
{

}
CAvExtInterFace::~CAvExtInterFace()
{

}