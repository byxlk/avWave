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
#ifndef _AVDEVICE_H_
#define _AVDEVICE_H_

#include "Apis/AvWareType.h"
#include "CAvObject.h"
#include "Apis/LibSystem.h"
#include "Apis/LibEncode.h"
#include "AvConfigs/AvConfigNetService.h"




class CAvDevice:public CAvObject
{
public:
	SINGLETON_DECLARE(CAvDevice);
	av_bool Initialize();//�������һ��Ҫ�ڼ������ñ�֮ǰ���У�
	av_bool InitializeConfigs();//�������һ��Ҫ���ڼ��������ñ�֮�� 
public:
	static av_bool GetEnv(std::string &key, std::string &value);
	static av_bool SetEnv(std::string &key, std::string &value);

private:
	static CMutex m_SEnvMutex;
	static std::map<std::string, std::string> m_SEnv;

public:
	static av_bool GetDspCaps		(C_DspCaps &DspCaps);
	static av_bool GetCaptureCaps	(av_ushort Channel, C_EncodeCaps &EncodeCaps);
	static av_bool GetDecodeCaps	(av_ushort Channel);
	static av_bool GetSerialCaps	(C_SerialCaps &SerialCaps);
	static av_bool GetNetCommCaps	(C_NetCommCaps &NetCommCaps);
	static av_bool GetImageCaps		(av_ushort Channel, C_ImageQualityCaps &ImageCaps);
	static av_bool GetCaputreInCaps	(av_ushort Channel, C_CaptureInCaps &CaptureInCaps);
public:
	static av_bool GetACaptureCaps	(E_AUDIO_CHL Chl,C_AudioCaps &AudioCaps);

private:
	av_void OnConfigsNetComm(CAvConfigNetComm *NetComm, int &result);
	CAvConfigNetComm m_ConfigNetComm;

public:
	static av_bool Reboot();
	static av_bool GetSysTime(av_timeval &tv);
	static av_bool SetSysTime(av_timeval &tv);
	static av_bool GetDeviceInfo(C_DeviceFactoryInfo &FactoryInfo);
	static av_bool SetDeviceInfo(C_DeviceFactoryInfo &FactoryInfo);
	
	static av_uint GetDeviceStartUp();
	static av_bool SystemBeep();

	static av_bool SystemUpgrade(std::string UpgradeFilePath, av_uint &Progress);
	static av_bool SystemUpgrade(av_uchar *ptr, av_uint length, av_uint &Progress);
	

	static av_bool GetMemLoadInfo(C_MemoryLoadInfo &MemLoadInfo);
	static av_bool GetNetLoadInfo(C_NetLoadInfo &NetLoadInfo);
	static av_bool GetCpuLoadInfo(C_CpuLoadInfo &CpuLoadInfo);
	static av_bool GetStartUpGuid(std::string &guid);
private:
	CAvDevice();
	~CAvDevice();
	av_bool Start();
	av_bool Stop();


private:
	static C_DeviceFactoryInfo	m_FactoryInfo;
	static std::string			m_SStartGUID;
};

#define g_AvDevice (*CAvDevice::instance())


#endif