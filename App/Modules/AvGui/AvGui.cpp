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
#include "AvGui/AvGui.h"



PATTERN_SINGLETON_IMPLEMENT(CAvGui);
int m_AppArgc = 0;
CAvGui::CAvGui()
{

}
CAvGui::~CAvGui()
{

}
av_bool CAvGui::Initialize()
{
	av_msg("%s Started\n", __FUNCTION__);
	return av_true;
}

av_bool CAvGui::exec()
{
	while (1) av_msleep(1000);
	return av_true;
}