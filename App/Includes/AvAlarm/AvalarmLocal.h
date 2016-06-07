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
#ifndef _AV_ALARMLOCAL_H_
#define _AV_ALARMLOCAL_H_



#include "AvThread/AvThread.h"
#include "Apis/LibSystem.h"
#include "AvThread/AvQmsg.h"
#include "Apis/LibLocalAlm.h"
#include "AvAlarm/AvAlarm.h"

class CAvAlmLocal:public CThread
{

public:
	PATTERN_SINGLETON_DECLARE(CAvAlmLocal);
	av_bool Initialize();
	av_bool AlarmOutCtrl(av_bool bOpen = av_true);
private:
	CAvAlmLocal();
	~CAvAlmLocal();

private:
	av_bool CheckConfIo();
	av_bool CheckConfMd();




private:
	av_bool SendAlmMsg(CAvAlarm::AlmMsg  &msg);
	av_bool PacketAlmIo(C_AlmIoResult *Result);
	av_bool PacketAlmMd(C_AlmMdResult *Result);


public:
	C_AlmIoCaps m_AlmIoCaps;
	C_AlmMdCaps m_AlmMdCaps;


private:
	void ThreadProc();
};


#define g_AvAlmLocal (*CAvAlmLocal::instance())

#endif
