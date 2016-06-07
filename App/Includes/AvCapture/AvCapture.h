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
#ifndef _AVCAPTURE_H_
#define _AVCAPTURE_H_
#include <map>
#include "AvPacket/AvPacket.h"
#include "Apis/AvWareType.h"
#include "Apis/LibEncode.h"
#include "CObject.h"
#include "Signals.h"
#include "AvConfigs/AvConfigCapture.h"


class CAvCapture:public CThread
{
public:

	CAvCapture();
	~CAvCapture();
	av_bool Initialize(av_char Channel);

	av_bool CaptureCreate();
	av_bool CaptureDestroy();

	av_bool CaptureStart(av_uchar Slave);
	av_bool CaptureStop(av_uchar Slave);
	
	
	av_bool CaptureGetDspInfo();
	av_bool CaptureGetCaps();
	av_u32  CaptureGetChanannels();
	
	//�������������ַ�����
public:
	typedef TSignal3<av_uchar, av_uchar, CPacket &>::SigProc OnStreamSigNalFunc;
	av_bool StreamStart(av_uchar Slave, CObject *obj, OnStreamSigNalFunc proc);
	av_bool StreamStop(av_uchar Slave, CObject *obj, OnStreamSigNalFunc proc);
private:
	TSignal3<av_uchar, av_uchar, CPacket &> m_StreamSignal[CHL_NR_T];

private:
	av_bool StartEnv();
	av_bool StartConf(av_bool loadDefault = av_false);
	av_void OnConfigEncodeModify(CAvConfigEncode *ConfigEncode, int &result);
	av_void OnConfigImageModify(CAvConfigImage *ConfigImage, int &result);
	av_void OnConfigCoverModify(CAvConfigCover *ConfigCover, int &result);
	av_void OnConfigWaterMarkingModify(CAvConfigWaterMarking *ConfigWaterMarking, int &result);
	av_void OnConfigCaptureModify(CAvConfigCapture *ConfigCapture, int &result);
private:
	void ThreadProc();


private:
	C_EncodeCaps			 m_EncodeCaps;
	C_CaptureInCaps			 m_CaptureInCaps;
	av_uchar				 m_Channel;
	E_CaptureSynchronizeStat m_LastCaptureSyncStat;

	CAvConfigEncode			m_ConfigEncode;
	CAvConfigImage			m_ConfigImage;
	CAvConfigCover			m_ConfigCover;
	CAvConfigWaterMarking	m_ConfigWaterMark;
	CAvConfigCapture		m_ConfigCapture;
};

class CMCapture
{
public:
	PATTERN_SINGLETON_DECLARE(CMCapture);
private:
	CMCapture();
	~CMCapture();
public:
	av_bool Initialize();
	CAvCapture *GetAvCaptureInstance(av_uchar iChannel);

private:
	std::map <av_uchar, CAvCapture *>  m_MCaptureMap;
	av_uchar m_MaxCaptureChannels;
};

#define g_MCapture (*CMCapture::instance())

#endif


