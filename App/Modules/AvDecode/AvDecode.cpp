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
#include "AvDecode/AvDecode.h"


PATTERN_SINGLETON_IMPLEMENT(CAvDecode);
CAvDecode::CAvDecode()
{
}
CAvDecode::~CAvDecode()
{

}
av_bool CAvDecode::Initialize()
{
	av_msg("%s Started\n", __FUNCTION__);
	return av_true;
}


