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
#include <cstdio>
#include "Apis/AvWareType.h"
#include "Apis/LibEncode.h"
#include "Apis/LibSystem.h"

#include "AvThread/AvQueue.h"
#include "AvThread/AvQmsg.h"
#include "AvThread/AvThreadPool.h"
#include "AvThread/AvTimer.h"

#include "AvNetService/AvSmtp.h"
#include "AvNetService/AvUpnp.h"
#include "AvNetService/AvDdns.h"
#include "AvNetService/AvFtp.h"
#include "AvNetService/AvNetService.h"

#include "AvPacket/AvPacket.h"
#include "AvDevice/AvDevice.h"
#include "AvWatchDog/AvWatchDog.h"
#include "AvGui/AvGui.h"
#include "AvCapture/AvManCapture.h"

#include "AvUart/AvUart.h"
#include "AvExternInterface/AvExternInterface.h"
#include "AvLog/AvLog.h"
#include "AvAudio/AvAudio.h"
#include "AvAlarm/AvAlarm.h"
#include "AvMemoryPool/AvMemoryPool.h"
#include "AvThread/AvTask.h"
#include "AvConfigs/AvConfigManager.h"
#include "AvRecord/AvRecord.h"
#include "AvLua/AvLua.h"
#include "AvProc/AvProc.h"

int main(int argc, char *argv[])
{
#if defined( WIN32)
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2,2),&wsa);
#else
	signal(SIGPIPE, SIG_IGN);
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGALRM);
	sigprocmask(SIG_BLOCK, &set, NULL);

#endif
	/*
		���º����������У��������е�����
	*/
	av_msg("AvWare Runing Start\n");
	g_AvProc.Initialize();
	g_AvDevice.Initialize();
	g_AvThreadPool.Initialize(10, av_true);
	g_AvConfigManager.Initialize();
	g_AvDevice.InitializeConfigs();
	g_AvMemoryPool.Initialize();
	g_AvTimerManager.Initialize();
	g_AvPacketManager.Initialize();

	g_AvGui.Initialize();
	g_AvLog.Initialize();
	g_AvUart.Initialize();
	g_AvManCapture.Initialize();
	//g_AvRecordMan.Initialize();
	g_AvAlarm.Initialize();
	g_AvNetService.Initialize();
	g_AvExtInterFace.Initialize();
	av_msg("AvWare Service Start Succeed\n");

	g_AvThreadPool.Dump();
	
	g_AvGui.exec();
	while (1) av_msleep(1000);

	return 0;

}

