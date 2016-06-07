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
#ifndef _AVQUEUE_H_
#define _AVQUEUE_H_
#include "Apis/AvWareType.h"
#include "AvThread/AvThread.h"

class CQueue
{
public:
	CQueue(av_u32 QueueSize = 8);
	virtual ~CQueue();

	av_bool Empty();
	av_bool Full();

	av_bool PushBackPointer(av_void *data, av_u32 len = 0);
	av_bool PushFrontPointer(av_void *data, av_u32 len = 0);
	av_bool PopBackPointer(av_void *&data, av_u32 &len);
	av_bool PopFrontPointer(av_void *&data, av_u32 &len);

	av_u32	Size();
	av_bool Size(av_u32 size);

	av_u32  Length();

private:
	std::list<av_void *> m_Queue;
	CMutex		m_Mutex;
	av_u32      m_QueueSize;
};



#endif