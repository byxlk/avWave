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
#ifndef _AVCONFIGCAPTURE_H_
#define _AVCONFIGCAPTURE_H_
#include "Apis/AvWareType.h"
#include "AvConfigs/AvConfigTable.h"
#include "Apis/LibEncode.h"



typedef struct {
	av_bool Enable;
	C_EncodeFormats Formats;
}C_CHLEncodeFormats;

typedef struct{
	C_CHLEncodeFormats CHLFormats[CHL_NR_T];
}ConfigEncodeFormats;


typedef struct {
	C_CoverFormats CHLFormats[ConfMaxCover];
}ConfigCoverFormats;

typedef struct{
	C_WaterMarkingFormats CHLFormats[ConfMaxWaterMarking];
}ConfigWaterMarkingFormats;


typedef C_ImageFormats ConfigImageFormats;

typedef C_CaptureInFormats ConfigCaptureFormats;


typedef TAvConfig<ConfigEncodeFormats, 0, ConfMaxCaptureChn> CAvConfigEncode;

typedef TAvConfig<ConfigImageFormats, 0, ConfMaxCaptureChn> CAvConfigImage;

typedef TAvConfig<ConfigCaptureFormats, 0, ConfMaxCaptureChn> CAvConfigCapture;

typedef TAvConfig<ConfigCoverFormats, 0, ConfMaxCaptureChn>CAvConfigCover;

typedef TAvConfig<ConfigWaterMarkingFormats, 0, ConfMaxCaptureChn>CAvConfigWaterMarking;










#endif


