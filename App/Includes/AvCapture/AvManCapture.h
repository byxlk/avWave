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
#ifndef _AV_MANCAPTURE_H_
#define _AV_MANCAPTURE_H_
#include "AvCapture/AvCapture.h"
#include "AvCapture/AvDevCapture.h"
#include "AvCapture/AvNetCapture.h"


class CManCapture
{
public:
	SINGLETON_DECLARE(CManCapture);
private:
	CManCapture();
	~CManCapture();
public:
	av_bool Initialize();
	Capture *GetAvCaptureInstance(av_int iChannel);
	av_u32   GetAvCaptureTotal();
private:
	std::map <av_int, Capture *>  m_ManCaptureMap;
	av_int m_MaxCaptureChannels;
};

#define g_AvManCapture (*CManCapture::instance())




#endif



