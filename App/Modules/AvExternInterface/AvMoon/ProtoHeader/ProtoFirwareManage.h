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
#ifndef _PROTOFIRWAREMANAGE_H_
#define _PROTOFIRWAREMANAGE_H_

#include "ProtoStruct.h"

#ifdef __MOONPROTO_ //FOR VFWARE
#include "system/Object.h"
#include "system/SignalS.h"
#else
#include "Object.h"
#include "SignalS.h"
#endif


#ifdef PROTOSHARE_EXPORTS

#if defined (WIN32)

#if defined (USE_STATIC_LIB)
#define PROTOSHARE_API
#else
#define PROTOSHARE_API __declspec(dllexport)
#endif

#else //else define win32
#define PROTOSHARE_API __attribute__((visibility("default")))
#endif //end define win32

#else //else PROTOSHARE_EXPORTS

#if defined(WIN32)
#if defined (USE_STATIC_LIB)
#define PROTOSHARE_API
#else
#define PROTOSHARE_API __declspec(dllimport)
#endif

#else
#define PROTOSHARE_API
#endif

#endif //end PROTOSHARE_EXPORTS

typedef struct{
	char FirmWarePath[128];
	char FirmWareName[64];
	C_FirmwareInfo FirmwareInfo;
	int  FirmwareSize;
	unsigned char *FirmwareAddr;
}C_FirmWareManageMem;

class PROTOSHARE_API CFirmWareManage
{
public:
	CFirmWareManage();
	~CFirmWareManage();
	SINGLETON_DECLARE(CFirmWareManage);
public:
	//�ⲿʹ��
	int FirmWareManageReSet();
	int FirmWareManageAdd(const char *Path);
	int FirmWareManageDel(const char *Path);
	int FirmWareManageGetFirmWareInfo(C_FirmwareInfo &FirmwareInfo, const char *FileName);
	//Э���ڲ�ʹ��
	int FirmWareManageGetFirmWareInfoList(std::list <C_FirmWareManageMem> FirmWaremanageList);

private:
	std::list <C_FirmWareManageMem> m_FirmWaremanageMem;
};


#define g_StreamManager (*CFirmWareManage::instance())











#endif