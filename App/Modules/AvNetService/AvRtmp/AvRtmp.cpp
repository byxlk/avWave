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
#include "AvNetService/AvRtmp.h"
#include "AvCapture/AvCapture.h"


PATTERN_SINGLETON_IMPLEMENT(AvRtmp)

AvRtmp::AvRtmp() :CThread(__FUNCTION__)
{

}
AvRtmp::~AvRtmp()
{

}
av_bool AvRtmp::Start()
{
	CAvCapture *pAvCapture = g_MCapture.GetAvCaptureInstance(0);
	pAvCapture->StreamStart(CHL_MAIN_T, this, (CAvCapture::OnStreamSigNalFunc)&AvRtmp::OnStream);
	pAvCapture->StreamStart(CHL_SUB1_T, this, (CAvCapture::OnStreamSigNalFunc)&AvRtmp::OnStream);

	CThread::run();
	return av_true;
}
av_bool AvRtmp::Stop()
{
	CAvCapture *pAvCapture = g_MCapture.GetAvCaptureInstance(0);
	pAvCapture->StreamStop(CHL_MAIN_T, this, (CAvCapture::OnStreamSigNalFunc)&AvRtmp::OnStream);
	pAvCapture->StreamStop(CHL_SUB1_T, this, (CAvCapture::OnStreamSigNalFunc)&AvRtmp::OnStream);
	
	CThread::stop(av_true);
	return av_true;
}

av_void AvRtmp::OnStream(av_uchar Channel, av_uchar Slave, CPacket &packet)
{

}

av_void AvRtmp::ThreadProc()
{
	while (m_Loop == av_true)
	{

		av_msleep(200);
	}

	av_error("%s Task Exit\n", __FUNCTION__);
}