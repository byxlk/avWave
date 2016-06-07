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
#ifndef _AVQMSG_H_
#define _AVQMSG_H_
#include "Apis/AvWareType.h"
#include "AvThread/AvThread.h"
#include "AvThread/AvQueue.h"

//�ͷ� �����ܽ���Ϣ�����ͷŵ����ͷ���Ϣһ��Ҫʹ��QmRelease
//֮����Ϊʲô����QmRelease���� ���������Ҳ������Ϊ���
class CAvQmsg:public CObject
{
public:
	CAvQmsg(std::string QmsgName, av_u32 QmsgSize = 8);
	~CAvQmsg();
	av_bool QmRcv(av_char *msg, av_u32 &len,av_bool wait = av_true);
	av_bool QmSnd(av_char *msg, av_u32 &len);
	av_u32  QmCount();
	av_bool QmClear();
	av_bool QmRelease();

	static av_void QmDebug(std::string QmsgName = NULL);
private:
	CQueue			*m_Queue;
	std::string		m_QmsgName;
private:
	static std::map<std::string, CQueue *> s_QueueHandle;
	static CMutex s_QueueMutex;
};




#endif