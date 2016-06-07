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
#ifndef _AV_RTSP_H_
#define _AV_RTSP_H_
#include "Apis/AvWareType.h"
#include "CObject.h"
#include "Rtsp/LibRtspServer.h"
#include "AvPacket/AvPacket.h"


class CAvRtspServerMedia:public CRtspMediaSer
{
public:
	CAvRtspServerMedia();
	~CAvRtspServerMedia();

	bool StartMedia();
	bool StopMedia();


private:
	av_void OnStream(av_uchar Channel, av_uchar Slave, CPacket &packet);
};

class CAvRtspServer:public CRtspServer
{
public:
	PATTERN_SINGLETON_DECLARE(CAvRtspServer)
	CAvRtspServer();
	~CAvRtspServer();
	av_bool Start(int ServicePort = 554);
	av_bool Stop();

private:

};


#define g_AvRtspServer (*CAvRtspServer::instance())




#endif
