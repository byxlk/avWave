/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: Knight [knight@graceport.cn]
|  ����: 2016��6��6��
|  ˵��: ��ģ�������Ƕ��ʽ�豸����linux ϵͳ�е�/proc/avWare/Ŀ¼��������ϵͳ
|		����ģ�������״̬��
|
|  �汾: 1.1
|  ����:
|  ����:
|  ˵��:
******************************************************************/
#ifndef _AV_PROC_H_
#define _AV_PROC_H_
#include "Apis/AvWareType.h"
#include "CAvObject.h"
#include "logAvWareExport.h"

#define logAvWarePath "/dev/logAvWare"

class CAvProc:public CAvObject
{
public:
	SINGLETON_DECLARE(CAvProc);
	av_bool Initialize();
	av_bool avProcSet(IOCTRL_CMD cmd, av_void *data, av_u32 datalen);

private:
	CAvProc();
	~CAvProc();

private:
	av_int m_ProcHandle;

};


#define g_AvProc (*CAvProc::instance())


#endif