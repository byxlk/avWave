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
#include "AvDevice/AvDevice.h"
#include "AvConfigs/AvConfigCapture.h"
#include "AvConfigs/AvConfigNetService.h"
#include "AvLua/AvLua.h"

SINGLETON_IMPLEMENT(CAvDevice);


C_DeviceFactoryInfo CAvDevice::m_FactoryInfo;
std::string CAvDevice::m_SStartGUID;

av_bool CAvDevice::Initialize()
{
	av_msg("%s Started\n", __FUNCTION__);
	AvSystemInit();
	

	{//FACTOORY
		C_DeviceFactoryInfo FactoryInfo = { 0 };
		GetDeviceInfo(FactoryInfo);
	}

	{//һ��Ҫ����fac ���棬��Ϊlua �����п�����auto ��ѡ���ʱ��ҪFAC ���� ��ϡ�
		InitializeLua();
	}

	{// GPIO
		AvGpioInit();
	}
	

	{// RTC
		AvRtcInit();
		AvTimeRtc2System();
	}

	{//GUID
		av_timeval timeval;
		AvGetTimeOfDay(&timeval);
		char guid[128];
		srand((unsigned int)timeval.tv_usec);
		sprintf(guid, "%s-%04X-%04X-%08X", m_FactoryInfo.ProductMacAddr, timeval.tv_sec, timeval.tv_usec, rand());
		m_SStartGUID.clear();
		m_SStartGUID.assign(guid);
	}


	return av_true;
}
av_bool CAvDevice::InitializeLua()
{
	CAvLua initLua;
	std::string Value;
	initLua.LuaLoadfile("init.lua");
	Value = initLua.LuaGlobal("avWare_configs_path");
	if (Value.empty() == false){
		SetEnv(std::string(EKey_ConfigsPath), Value);
	}
	
	Value = initLua.LuaGlobal("avWare_webroot");
	if (Value.empty() == false){
		SetEnv(std::string(EKey_WebRoot), Value);
	}

	Value = initLua.LuaGlobal("avWare_webindex");
	if (Value.empty() == false){
		SetEnv(std::string(EKey_WebIndex), Value);
	}
	
	return av_true;
}
av_bool CAvDevice::InitializeConfigs()
{
	Start();
	return av_true;
}
CAvDevice::~CAvDevice()
{
}
CAvDevice::CAvDevice()
{
}


static int GetCompileDateTime(char *szDateTime)
{

	#define MONTH_PRE_YEAR 12
	const char szEnglishMonth[MONTH_PRE_YEAR][6] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	char szMonth[12] = { 0 };
	int iYear, iMonth, iDay, iHour, iMin, iSec;

	sscanf(__DATE__, "%s %d %d", szMonth, &iDay, &iYear);
	sscanf(__TIME__, "%d:%d:%d", &iHour, &iMin, &iSec);

	for (int i = 0; i < MONTH_PRE_YEAR; i++)
	{
		if (strncmp(szMonth, szEnglishMonth[i], 3) == 0)
		{
			iMonth = i + 1;
			break;
		}
	}
	sprintf(szDateTime, "%02d%02d%02d", iYear%100, iMonth, iDay);
	return 0;
}

std::string CAvDevice::GetSoftVersionString()
{
	std::string Version;
	av_char ver[128];
	av_char _complileDate[128];
	GetCompileDateTime(_complileDate);

	sprintf(ver, "%d.%d.%d.%s_%s", _AV_WARE_VERSION_MAJOR, _AV_WARE_VERSION_MINOR,_AV_WARE_VERSION_PATCH,
		_complileDate, _AV_WARE_VERSION_RUNTIME);
	if (0 != strlen(_AV_WARE_VERSION_OEM)){
		strcat(ver, "_");
		strcat(ver, _AV_WARE_VERSION_OEM);
}

	Version.assign(ver);
	return Version;
}
av_u32      CAvDevice::GetSoftVersionU32()
{
	return _AV_WARE_VERSION_MAJOR << 16 | _AV_WARE_VERSION_MINOR << 8 | _AV_WARE_VERSION_PATCH;
}



CMutex CAvDevice::m_SEnvMutex;
std::map<std::string, std::string> CAvDevice::m_SEnv;
av_bool CAvDevice::GetEnv(std::string key, std::string &value)
{
	CGuard m(m_SEnvMutex);
	if (key.size() == 0){
		return av_false;
	}
	if (m_SEnv[key].size() == 0){
		value.clear();
		return av_false;
	}
	value = m_SEnv[key];
	return av_true;
}
av_bool CAvDevice::SetEnv(std::string key, std::string &value)
{
	CGuard m(m_SEnvMutex);
	if (key.size() == 0){
		return av_false;
	}
	
	if (value == std::string("")){
		std::map<std::string, std::string>::iterator i;
		i = m_SEnv.find(key);
		if (i != m_SEnv.end()){
			m_SEnv.erase(i);
		}
	}
	else{
		m_SEnv[key] = value;
	}
	return av_true;
}


av_bool CAvDevice::Start()
{

	{
		//## Set NetWork
		m_ConfigNetComm.Update();
		m_ConfigNetComm.Attach(this, (AvConfigCallBack)&CAvDevice::OnConfigsNetComm);

		C_NetCommCaps NetCommCaps;
		GetNetCommCaps(NetCommCaps);
		for (int i = 0; i < NetCommT_Nr; i++)
		{
			if (AvMask(i) & NetCommCaps.NetCommMask){
		
				ConfigNetComm &Formats = m_ConfigNetComm.GetConfig(i);
				C_NetCommAttribute NetCommAttr;
				NetCommAttr.Enable = Formats.Enable;
				switch ((E_NetComm_Type)i)
				{
				case NetCommT_Lan0:
				case NetCommT_Lan1:
					NetCommAttr.LanAttr = Formats.LanAttr;
					break;
				case NetCommT_Wireless:
					NetCommAttr.WirelessAttr = Formats.WirelessAttr.RouterLinkInfo[0];
					break;
				case NetCommT_SIM:
					NetCommAttr.SimAttr = Formats.SimAttr;
					break;

				default:
					break;
				}
				av_bool ret = avNetCommSet(Formats.type, &NetCommAttr);
				if (ret != av_true){
					av_error("Set %d NetCommDev Error\n", i);
				}
			}
		}
	}

	return av_true;
}
av_bool CAvDevice::Stop()
{
	AvSystemDeInit();

	AvTimeSystem2Rtc();



	return av_true;
}

av_bool CAvDevice::GetDspCaps(C_DspCaps &DspCaps)
{
	memset(&DspCaps, 0x00, sizeof(C_DspCaps));
	return AvGetDspCaps(&DspCaps);
}
av_bool CAvDevice::GetCaptureCaps(av_ushort Channel, C_EncodeCaps &EncodeCaps)
{
	memset(&EncodeCaps, 0x00, sizeof(C_EncodeCaps));
	av_bool ret = AvCaptureGetCaps((av_uchar)Channel, &EncodeCaps);
	return ret;
}
av_bool CAvDevice::GetDecodeCaps(av_ushort Channel)
{
	return av_true;
}
av_bool CAvDevice::GetSerialCaps(C_SerialCaps &SerialCaps)
{
	memset(&SerialCaps, 0x00, sizeof(C_SerialCaps));
	return AvSerialCaps(&SerialCaps);
}

av_bool CAvDevice::GetNetCommCaps(C_NetCommCaps &NetCommCaps)
{
	memset(&NetCommCaps, 0x00, sizeof(C_NetCommCaps));
	return avNetCommCaps(&NetCommCaps);
}
av_bool CAvDevice::GetImageCaps(av_ushort Channel, C_ImageQualityCaps &ImageCaps)
{
	memset(&ImageCaps, 0x00, sizeof(C_ImageQualityCaps));
	return AvImageCaps((av_char)Channel, &ImageCaps);
}
av_bool CAvDevice::GetCaputreInCaps(av_ushort Channel, C_CaptureInCaps &CaptureInCaps)
{
	memset(&CaptureInCaps, 0x00, sizeof(C_CaptureInCaps));
	return AvCaptureInCaps((av_char)Channel, &CaptureInCaps);
}
av_bool CAvDevice::GetACaptureCaps(E_AUDIO_CHL Chl, C_AudioCaps &AudioCaps)
{
	memset(&AudioCaps, 0x00, sizeof(C_AudioCaps));
	return AvACaptureCaps(Chl, &AudioCaps);
}
av_void CAvDevice::OnConfigsNetComm(CAvConfigNetComm *NetComm, int &result)
{
	int cmpRet = 0;
	C_NetCommAttribute NetCommAttr;
	for (int i = 0; i < NetCommT_Nr; i++)
	{
		ConfigNetComm &newConf = NetComm->GetConfig(i);
		ConfigNetComm &oldConf = m_ConfigNetComm.GetConfig(i);
		switch (i)
		{
		case NetCommT_Lan0:
			cmpRet = memcmp(&newConf.LanAttr, &oldConf.LanAttr, sizeof(ConfigLanAttribute));
			if (newConf.Enable != oldConf.Enable || cmpRet != 0){
				NetCommAttr.Enable = newConf.Enable;
				NetCommAttr.LanAttr = newConf.LanAttr;
				avNetCommSet(NetCommT_Lan0, &NetCommAttr);
				oldConf.Enable = newConf.Enable;
				oldConf.LanAttr = newConf.LanAttr;
			}
			break;
		case NetCommT_Lan1:
			cmpRet = memcmp(&newConf.LanAttr, &oldConf.LanAttr, sizeof(ConfigLanAttribute));
			if (newConf.Enable != oldConf.Enable || cmpRet != 0){
				NetCommAttr.Enable = newConf.Enable;
				NetCommAttr.LanAttr = newConf.LanAttr;
				avNetCommSet(NetCommT_Lan1, &NetCommAttr);
				oldConf.Enable = newConf.Enable;
				oldConf.LanAttr = newConf.LanAttr;
			}
			break;
		case NetCommT_Wireless:
			cmpRet = memcmp(&newConf.WirelessAttr, &oldConf.WirelessAttr, sizeof(ConfigWirelessAttribute));
			if (newConf.Enable != oldConf.Enable || cmpRet != 0){
				NetCommAttr.Enable = newConf.Enable;
				NetCommAttr.WirelessAttr = newConf.WirelessAttr.RouterLinkInfo[0];
				avNetCommSet(NetCommT_Wireless, &NetCommAttr);
				oldConf.Enable = newConf.Enable;
				oldConf.WirelessAttr = newConf.WirelessAttr;
			}
			break;
		case NetCommT_SIM:
			cmpRet = memcmp(&newConf.SimAttr, &oldConf.SimAttr, sizeof(ConfigSimAttribute));
			if (newConf.Enable != oldConf.Enable || cmpRet != 0){
				NetCommAttr.Enable = newConf.Enable;
				NetCommAttr.SimAttr = newConf.SimAttr;
				avNetCommSet(NetCommT_SIM, &NetCommAttr);
				oldConf.Enable = newConf.Enable;
				oldConf.SimAttr = newConf.SimAttr;
			}
			break;
		case NetCommT_BlueTooth:
			cmpRet = memcmp(&newConf.BlueToothAttr, &oldConf.BlueToothAttr, sizeof(ConfigBlueTooth));
			if (newConf.Enable != oldConf.Enable || cmpRet != 0){
				NetCommAttr.Enable = newConf.Enable;
				NetCommAttr.BluteToothAttr = newConf.BlueToothAttr;
				avNetCommSet(NetCommT_BlueTooth, &NetCommAttr);
				oldConf.Enable = newConf.Enable;
				oldConf.BlueToothAttr = newConf.BlueToothAttr;
			}
			break;
		default:
			break;
		}
	}
}
av_bool CAvDevice::Reboot()
{
	g_AvDevice.Stop();

	AvReboot();
	return av_true;
}

av_bool CAvDevice::GetSysTime(av_timeval &tv)
{
	return AvGetTimeOfDay(&tv);
}

av_bool CAvDevice::SetSysTime(av_timeval &tv)
{
	AvSetTimeofDay(&tv);
	return AvTimeSystem2Rtc();
}

av_bool CAvDevice::GetDeviceInfo(C_DeviceFactoryInfo &FactoryInfo)
{
	if (0 == strlen(m_FactoryInfo.SerialNumber)){
		if (av_true != AvGetDeviceInfo(&m_FactoryInfo)){
			memset(&m_FactoryInfo, 0x00, sizeof(C_DeviceFactoryInfo));
			sprintf(m_FactoryInfo.FactoryName, "%s", "aVware Factory");
			sprintf(m_FactoryInfo.SerialNumber, "%s", "AV-0001-0002-0003-0004");
			sprintf(m_FactoryInfo.ProductMacAddr, "%s", "00:1A:2B:3C:4D:5E");
			sprintf(m_FactoryInfo.HardWareVersion, "%s", "AV-HardWare-00-00-01");
			sprintf(m_FactoryInfo.ProductModel, "%s", "AV-Product-Model-A");
		}
		else{
// 			memset(&m_FactoryInfo, 0x00, sizeof(C_DeviceFactoryInfo));
// 			sprintf(m_FactoryInfo.FactoryName, "%s", "aVware Factory");
// 			sprintf(m_FactoryInfo.SerialNumber, "%s", "AV-0001-0002-0003-0004");
// 			sprintf(m_FactoryInfo.ProductMacAddr, "%s", "00:1A:2B:3C:4D:5E");
// 			sprintf(m_FactoryInfo.HardWareVersion, "%s", "AV-HardWare-00-00-01");
// 			sprintf(m_FactoryInfo.ProductModel, "%s", "AV-Product-Model-A");
		}

	}
	FactoryInfo = m_FactoryInfo;
	return av_true;
}
av_bool CAvDevice::SetDeviceInfo(C_DeviceFactoryInfo &FactoryInfo)
{
	m_FactoryInfo = FactoryInfo;
	av_msg("SetDeviceInfo \nFactoryName[%s]MaxChannel[%d]\nSerialNumber[%s]\n", 
		m_FactoryInfo.FactoryName,  m_FactoryInfo.MaxChannel, m_FactoryInfo.SerialNumber);
	return AvSetDeviceInfo(&m_FactoryInfo);
	return av_true;
}

av_uint CAvDevice::GetDeviceStartUp()
{
	return AvGetDeviceStartUp();
}
av_bool CAvDevice::SystemBeep()
{
	return AvSystemBeep(0xff, 100);
}

C_UpgradeProgress CAvDevice::m_SystemUpgradeProgress;

av_bool CAvDevice::SystemUpgrade(std::string UpgradeFilePath)
{
	av_bool ret = AvSystemUpgradeFile(UpgradeFilePath.c_str(), &m_SystemUpgradeProgress);
	return ret;
}
av_bool CAvDevice::SystemUpgrade(av_uchar *ptr, av_uint length)
{
	return av_true;
}
av_u32  CAvDevice::SystemUpgradeProgress()
{
	av_msg("ProgressCmd = %d  Value =  %d\n", m_SystemUpgradeProgress.ProgressCmd, m_SystemUpgradeProgress.ProgressValue);
	return (av_u32)(m_SystemUpgradeProgress.ProgressCmd << 16 | m_SystemUpgradeProgress.ProgressValue);
}

av_bool CAvDevice::GetMemLoadInfo(C_MemoryLoadInfo &MemLoadInfo)
{
	return AvGetMemLoadInfo(&MemLoadInfo);
}
av_bool CAvDevice::GetNetLoadInfo(C_NetLoadInfo &NetLoadInfo)
{
	return AvGetNetLoadInfo(&NetLoadInfo);
}
av_bool CAvDevice::GetCpuLoadInfo(C_CpuLoadInfo &CpuLoadInfo)
{
	return AvGetCpuLoadInfo(&CpuLoadInfo);
}

av_bool CAvDevice::GetStartUpGuid(std::string &guid)
{
	guid = m_SStartGUID;
	return av_true;
}