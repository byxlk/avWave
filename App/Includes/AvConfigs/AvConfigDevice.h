/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: Xman [xman@graceport.cn]
|  ����: 2016��6��6��
|  ˵��:
|
|  �汾: 1.1
|  ����:
|  ����:
|  ˵��:
******************************************************************/
#ifndef AVWARE_AVCONFIG_AVCONFIGDEVICE_H_
#define AVWARE_AVCONFIG_AVCONFIGDEVICE_H_

#include "Apis/AvWareType.h"
#include "AvConfigs/AvConfigTable.h"
#include "Apis/LibSystem.h"


typedef struct {
	av_bool			Enable;
	av_com_type		Type;
	C_SerialAttr	Attribute;
}ConfigUart;
typedef TAvConfig<ConfigUart, 0, ConfMaxSerial> CAvConfigUart;

#endif //AVWARE_AVCONFIG_AVCONFIGDEVICE_H_