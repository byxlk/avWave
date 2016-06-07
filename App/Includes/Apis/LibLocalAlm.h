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
#ifndef _LIB_LOCALALM_H_
#define _LIB_LOCALALM_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "AvWareType.h"

	typedef struct {
		av_uchar MaxAlmOutNum;
		av_uchar MaxAlmInNum;
	}C_AlmIoCaps;

	typedef struct{
		av_u32 AlmIoCount;
		av_u32 AlmIoStatusMask;
	}C_AlmIoResult;

	av_bool AvGetIoAlmCaps(C_AlmIoCaps *Caps);
	av_bool AvGetIoAlmStatus(av_u32 AlmInNoMask, C_AlmIoResult *result);
	av_bool avSetIoAlmOut(av_uchar AlmOutNo, av_bool bOpen);

	typedef struct{
		av_uchar MaxRow;//���16
		av_uchar MaxLine;//���16
		av_uchar Maxlevel;
	}C_AlmMdCaps;

	typedef struct{
		av_u16 AlmAreaCount;
		av_u16 result[16];
	}C_AlmMdResult;
	av_bool avGetMdAlmCaps(C_AlmMdCaps *AlmMdCaps);
	av_bool avGetMdAlmStatus(C_AlmMdResult *result);

#ifdef __cplusplus
}
#endif

#endif