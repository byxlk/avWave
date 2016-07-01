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
#include "CAvObject.h"
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
	av_void OnStream(av_int Channel, av_int Slave, CAvPacket *AvPacket);
};

class CAvRtspServer:public CRtspServer
{
public:
	SINGLETON_DECLARE(CAvRtspServer)
	CAvRtspServer();
	~CAvRtspServer();
	av_bool Start(int ServicePort = 554);
	av_bool Stop();

private:

};


#define g_AvRtspServer (*CAvRtspServer::instance())




#endif
