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
#ifndef _AVGUI_H_
#define _AVGUI_H_

#include "Apis/AvWareType.h"
#include "Apis/LibSystem.h"
#include "CAvObject.h"


class CAvGui
{
public:
	SINGLETON_DECLARE(CAvGui);
	CAvGui();
	av_bool Initialize();
	av_bool exec();
private:
	~CAvGui();

private:

};

#define g_AvGui (*CAvGui::instance())







#endif