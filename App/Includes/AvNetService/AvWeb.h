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
#ifndef AVWARE_AVNETSERVICE_AVWEB_H_
#define AVWARE_AVNETSERVICE_AVWEB_H_

#include <map>
#include <list>
#include "Apis/AvWareType.h"
#include "CAvObject.h"
#include "WebService/LibWebService.h"
#include "AvNetService/AvWebProcess.h"

class CAvPacket;
class CAvWebSnap;

class CAvWebSer:public CWebService
{
public:
	SINGLETON_DECLARE(CAvWebSer);
	av_bool Start();
	av_bool Stop();

private:
	CAvWebSer();
	~CAvWebSer();

private:

	int WebCallBackDataProc(std::string InBuf, std::string &OutBuf);
	int WebCallBackGetSnap(int Channel, std::string &SnapData);

	void RegisterMsgProc();
	typedef std::map<std::string, WebMsgProc> MAP_LIST;
	MAP_LIST map_webmsgproc_;
};

#define g_AvWebSer (*CAvWebSer::instance())

#endif //AVWARE_AVNETSERVICE_AVWEB_H_
