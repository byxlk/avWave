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
#ifndef _PROTOPLAYCTRL_H_
#define _PROTOPLAYCTRL_H_


#include "Proto.h"
#ifdef __MOONPROTO_ //FOR VFWARE
#include "system/Object.h"
#include "system/SignalS.h"
#else
#include "Object.h"
#include "SignalS.h"
#endif


typedef struct {
	CProtoMoon *ProtoMoon;
	std::list <CStreamPacket *> StreamPacketList[PROTO_MAX_CHANNEL][Proto_MAX_SLAVE];
	unsigned int status;
	CNetUvMutex_t PacketManageMutex;
}PacketManage_t;


class CPlayCtrl
{
public:
	CPlayCtrl();
	~CPlayCtrl();
public:
	int CPlayCtrlStart(CProtoMoon *ProtoMoon);
	int CPlayCtrlStop();
	int CPlayCtrlStream(CStreamPacket *StreamPacket);
private:
	PacketManage_t m_PacketManage;
};










#endif