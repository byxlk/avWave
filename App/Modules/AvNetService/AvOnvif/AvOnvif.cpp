/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: FootMan [FootMan@graceport.cn]
|  ����: 2016��6��6��
|  ˵��:
|
|  �汾: 1.1
|  ����:
|  ����:
|  ˵��:
******************************************************************/

/*************************************
Company Name:�����ж��ۿƼ��������޹�˾(GracePort)
Function	:ONVIFCallback
Author		:FootMan
Email		:FootMan@graceport.cn
BugList:
1.���ñ���û������ѡ�� 
2.û��DHCPʹ��
3.������Э��NetProtocol(RTSP/ONVIF/HTTP) �˿����ñ�û���ҵ�,URL����û���ҵ�
4.Onvif��H265�ı���������ʱ�õ�H264,���뷽ʽĬ��ΪBaseline
5.ȱ�ٱ���PROFILE����:HIGHT BASELINE  MAIN,���ڻ�ȡ��д��Baseline
6.ȱ��VBR�л�������ѡ��
7.δ�ҵ���Ƶ������������(����BITRATE/GOP/QULITY/RESLUTION/PROFILE/ENCODING,ȡֵ��Χ)
8.δ�ҵ���Ƶ��������(������Ƶ BITRATE,SampleRate,encoding)
9.δ�ҵ�ʱ����������(CST/UTC�ȵ�),NTP�е�GMʱ���Ƿ����UTCת��
10.���õ�ǰʱ�����ʱ�� ϵͳ����ʵ�֣���������ʵ��?
11.δ�ҵ�ϵͳ�û���������(�����û��� ���� Ȩ�޵�����)
12.δ�ҵ�ͼ���������ѡ�����(Brightness/ColorSaturation/Contrast/Sharpness)
13.δ�ҵ�ͼ���������ѡ�����(Brightness/ColorSaturation/Contrast/Sharpness)��Χ
14.δ�ҵ��豸��Ϣ���� �����豸����, ֧��ͨ������(IPC����1),ÿ��ͨ����stream·��
	�Ƿ�֧����Ƶ����/��Ƶ����/��̨/��Ƶ����(һ��ָ�ƶ����)
**************************************/
#include "Apis/AvWareType.h"
#include "AvNetService/AvOnvif.h"
#include "Apis/LibEncode.h"

//	AvComp_G711A,
//	AvComp_G711U,
//	AvComp_AAC,
static VideoEncoding_E AVCompToOnvifEncoding(av_comp_t		Comp)
{
	switch(Comp){
		case AvComp_H264:  return VideoEncoding__H264;
		case AvComp_H265:  return VideoEncoding__H265;
		case AvComp_MJPEG: return VideoEncoding__JPEG;
		case AvComp_NR:
		default:
			return VideoEncoding__NULL;
	}
}

static av_comp_t OnvifEncodingToAV(VideoEncoding_E		encoding)
{
	switch(encoding){
		case VideoEncoding__H264: return AvComp_H264;
		case VideoEncoding__H265: return AvComp_H265;
		case VideoEncoding__JPEG: return AvComp_MJPEG;
		case VideoEncoding__NULL:
		default:
			return AvComp_NR;
	}
}

static av_capture_size GetResEnum(av_32 width, av_32 hight)
{
	if (width == 480 && hight == 240)
		return CaptureSize_QVGAEX;
	else if (width == 480 && hight == 360)
		return CaptureSize_QVGA;
	else if (width == 640 && hight == 360)
		return CaptureSize_VGAEX;
	else if (width == 640 && hight == 480)
		return CaptureSize_VGA;
	else if (width == 720 && hight == 576)
		return CaptureSize_D1;
	else if (width == 1280 && hight == 720)
		return CaptureSize_720P;
	else if (width == 1280 && hight == 960)
		return CaptureSize_960P;
	else if (width == 1920 && hight == 1080)
		return CaptureSize_1080P;
	else if (width == 2048 && hight == 1536)
		return CaptureSize_300W;
	else if (width == 2688 && hight == 1520)
		return CaptureSize_400W;
	else if (width == 2592 && hight == 1944)
		return CaptureSize_500W;
	else if (width == 3072 && hight == 2048)
		return CaptureSize_600W;
	else if (width == 3840 && hight == 2160)
		return CaptureSize_800W;
	else if (width == 4096 && hight == 2160)
		return CaptureSize_4K;
	else if (width == 7680 && hight == 4320)
		return CaptureSize_8K;
	else {
		return CaptureSize_Self;
	}
	return CaptureSize_NR;
}

static int GetResWidthAndHight(av_capture_size ImageSize, int *width, int *height)
{
	switch (ImageSize)
	{
		case CaptureSize_QVGAEX:
			*height = 160;
			*width = 320;
			break;

		case CaptureSize_QVGA://	//480*360
			*height = 360;
			*width = 480;
			break;
		case CaptureSize_VGAEX:	//640*360
			*height = 360;
			*width = 640;
			break;

		case CaptureSize_VGA:	//640*480
			*height = 480;
			*width = 640;
			break;
		case CaptureSize_D1:		//720*576
			*height = 576;
			*width = 720;
			break;
		case CaptureSize_720P:
			*height = 720;
			*width = 1280;
			break;
		case CaptureSize_960P:
			*height = 960;
			*width = 1280;
			break;
		case CaptureSize_1080P:
		case DisplaySize_1920_1080:
			*height = 1080;
			*width = 1920;
			break;
		default:
			*height = 0;
			*width = 0;
			break;
	}
	return 0;
}
static int	GetDeviceInfo(DeviceInfo_S *info)
{
	//δ�ҵ��豸��Ϣ����
	strcat(info->city,"shenzhen");
	strcat(info->country,"china");
	strcat(info->name,"IPC");
	strcat(info->facturer,"EnGang");
	strcat(info->model,"IPCAM");
	strcat(info->SerialNumber,"IPCAM-HDMI-00112233");
	strcat(info->softwareVer,"Build V1.0");
	info->devType = ENUM_DEVTYPE_IPC;
	return 0;
}

static int	SetDeviceInfo(DeviceInfo_S *info)
{
	
	return 0;
}

static int	GetDeviceCab(DeviceCab_S *info)
{
	//δ��������
	printf("GetDeviceCab\r\n");
	info->chnelCount = 1;
	info->streamCount= 2;
	info->AnalyticsEnable = 1;
	info->AudioEnable = 1;
	info->PtzEnable = 1;
	info->VideoEnable = 1;
	return 0;
}

static int	GetNetWorkInfo(NetWorkInfo_S *info)
{
	//��������д��
	//DHCPд��
// 	CAvConfigsNetWork ConfigNet;
// 	ConfigNet.Update();
// 	snprintf(info->mac,sizeof(info->mac),"%s",ConfigNet.m_network.mac);
// 	AvAddr2StrAddr(ConfigNet.m_network.ipaddr,	info->ip);
// 	AvAddr2StrAddr(ConfigNet.m_network.dns1,	info->dns);
// 	AvAddr2StrAddr(ConfigNet.m_network.gateway,	info->gateway);
// 	snprintf(info->hostName,sizeof(info->hostName),"%s",ConfigNet.m_network.host);
// 	strcat(info->ethernetName,"eth0");
// 	info->DhcpEnable = ENUM_ENABLED_FALSE;
	return 0;
}

static int	SetNetWorkInfo(NetWorkInfo_S *info)
{
	//����δ����
	//DHCPδ����
// 	CAvConfigsNetWork ConfigNet;
// 	ConfigNet.Update();
// 	snprintf(ConfigNet.m_network.mac,sizeof(ConfigNet.m_network.mac),"%s",info->mac);
// 	StrAddr2AvAddr(info->ip,ConfigNet.m_network.ipaddr);
// 	StrAddr2AvAddr(info->dns,ConfigNet.m_network.dns1);
// 	StrAddr2AvAddr(info->gateway,ConfigNet.m_network.gateway);
// 	snprintf(ConfigNet.m_network.host,sizeof(ConfigNet.m_network.host),"%s",info->hostName);
// 	ConfigNet.Submit();
	return 0;
}


static int	GetNetProtocolInfo(NetProtocolInfo *info)
{
	//����ȫ��д��
	//netprotocol û������
// 	CAvConfigsNetWork ConfigNet;
// 	ConfigNet.Update();
// 	char address[16] = {0};
// 	info->rtspPort = 554;
// 	info->onvifPort = 80;
// 
// 	AvAddr2StrAddr(ConfigNet.m_network.ipaddr, address);
// 	sprintf(info->rtspUrl[0][0],"rtsp://%s:%d/channel/1",address,info->rtspPort);
// 	sprintf(info->rtspUrl[0][1],"rtsp://%s:%d/channel/2",address,info->rtspPort);
	return 0;
}
static int	SetNetProtocolInfo(NetProtocolInfo *info)
{	
	//�޷����� 
	printf("rtsp port = %d\r\n",info->rtspPort);
	return 0;
}
static int	GetVideoEncode(int chn, int streamId, VedioEncode_S *info)
{
	//profile �� ���ʲ���д��
// 	CAvConfigsCapture ConfigCaputure;
// 	ConfigCaputure.Update(chn,streamId);
// 	memset(info,0,sizeof(VedioEncode_S));
// 	info->bitrate =  (int)ConfigCaputure.m_ConfigFormats.BitRateValue;
// 	info->cvbrMode = (int)ConfigCaputure.m_ConfigFormats.BitRateCtrl;
// 	info->encoding = AVCompToOnvifEncoding(ConfigCaputure.m_ConfigFormats.Comp);//VideoEncoding__H264;
// 	info->frameRate = (int)ConfigCaputure.m_ConfigFormats.FrameRate;
// 	info->gop = (int)ConfigCaputure.m_ConfigFormats.Gop;
// 	info->h264Profile = H264Profile__Main;//д��
// 	info->qulity = 10;//д��
// 	av_msg("ConfigCaputure.m_ConfigFormats.ImageSelfHeigh = %d",ConfigCaputure.m_ConfigFormats.ImageSelfHeigh);
// 	av_msg("ConfigCaputure.m_ConfigFormats.ImageSelfWidth = %d",ConfigCaputure.m_ConfigFormats.ImageSelfWidth);
// 	av_msg("ConfigCaputure.m_ConfigFormats.ImageSize = %d",ConfigCaputure.m_ConfigFormats.ImageSize);
// 	if(CaptureSize_Self != ConfigCaputure.m_ConfigFormats.ImageSize){
// 		GetResWidthAndHight(ConfigCaputure.m_ConfigFormats.ImageSize,&info->reslution.width,&info->reslution.height);
// 	}else{
// 		info->reslution.width = ConfigCaputure.m_ConfigFormats.ImageSelfWidth;
// 		info->reslution.height =  ConfigCaputure.m_ConfigFormats.ImageSelfHeigh;
// 	}
		
	return 0;
}

static int	SetVideoEncode(int chn, int streamId, VedioEncode_S *info)
{

	//profile �� ���ʲ���δ����	
// 	CAvConfigsCapture ConfigCaputure;
// 	ConfigCaputure.Update(chn,streamId);
// 	ConfigCaputure.m_ConfigFormats.BitRateValue = (av_u32)info->bitrate;
// 	ConfigCaputure.m_ConfigFormats.BitRateCtrl = (av_bitrate_ctrl)info->cvbrMode;
// 	ConfigCaputure.m_ConfigFormats.FrameRate = info->frameRate;
// 	ConfigCaputure.m_ConfigFormats.Gop = info->gop;
// 	ConfigCaputure.m_ConfigFormats.ImageSize = GetResEnum(info->reslution.width,info->reslution.height);
// 	if(CaptureSize_Self ==  ConfigCaputure.m_ConfigFormats.ImageSize){
// 		ConfigCaputure.m_ConfigFormats.ImageSelfHeigh = info->reslution.height;
// 		ConfigCaputure.m_ConfigFormats.ImageSelfWidth =  info->reslution.width;
// 	}
// 	ConfigCaputure.m_ConfigFormats.Comp = OnvifEncodingToAV(info->encoding);
// 	ConfigCaputure.Submit();
	return 0;
}

static int	GetVideoEncodeCab(int chn, int streamId, VedioEncodeCab_S *info)
{
	//δ�ҵ���������ѡ��
	info->bitrateRange.max = 8192;
	info->bitrateRange.min = 512;
	info->encodingCab = (VideoEncoding_E)(VideoEncoding__JPEG | VideoEncoding__H264 | VideoEncoding__H265);
	info->frameRateRange.max = 30;
	info->frameRateRange.min = 1;
	info->gopRange.max = 50;
	info->gopRange.min = 10;
	info->h264ProfileCab = (H264Profile_E)(H264Profile__Baseline | H264Profile__Main | H264Profile__High);
	info->qulityRange.max = 10;
	info->qulityRange.min = 1;
	
	info->resSupport[0].width = 1920;
	info->resSupport[0].height = 1080;
	
	info->resSupport[1].width = 1920;
	info->resSupport[1].height = 960;

	info->resSupport[2].width = 1280;
	info->resSupport[2].height = 720;
	info->resSupportNum = 3;
	info->maxReslution.width = 1920;
	info->maxReslution.height = 1080;
	info->defaultReslution.height = 1080;
	info->defaultReslution.width = 1920;
	return 0;
}

static int	GetAudioEncode(int chn, int streamId, AudioEncode_S *info)
{
	//��Ƶ����д��,δ��ȡ������
// 	CAvConfigsAudio ConfigsAudio;
// 	ConfigsAudio.Update((av_uchar)chn,(av_uchar)streamId);
// 	info->Bitrate = 8;
// 	info->Encoding = AudioEncoding__G711;
// 	info->SampleRate = 8000;
	return 0;
}

static int	SetAudioEncode(int chn, int streamId, AudioEncode_S *info)
{
	//��Ƶ������������
	return 0;
}

static int	GetSystemTime(SystemTime_S *info)
{
	//δ�ҵ�ʱ����������
	time_t timer;   
	struct tm* t_tm;   
	time(&timer);   
	t_tm = localtime(&timer);   
	info->timeZone = -1;
	info->year =  t_tm->tm_year+1900;
	info->month = t_tm->tm_mon+1;
	info->day = t_tm->tm_mday;
	info->hour = t_tm->tm_hour;
	info->min =  t_tm->tm_min;
	info->sec =  t_tm->tm_sec;
	return 0;   
}

static int	SetSystemTime(SystemTime_S *info)
{
	//ϵͳ����ʵ�֣���������ʵ��?
	return 0;
}

static int	GetUsrInfo(int *usrNum, UsrInfo_S *info)//���50��
{
	//δ�ҵ��������,д��
	*usrNum = 3;
	info[0].userLevel = ENUM_USRLEVEL_Operator;
	sprintf(info[0].usrname,"test1");
	info[1].userLevel = ENUM_USRLEVEL_Operator;
	sprintf(info[1].usrname,"test2");
	info[2].userLevel = ENUM_USRLEVEL_Administrator;
	sprintf(info[2].usrname,"admin");
	return 0;
}

static int	GetImagingParam(ImagingParam_S *info)
{
	//δ�ҵ�ͼ���������ѡ��
	info->Brightness = 30;
	info->ColorSaturation = 40;
	info->Contrast = 50;
	info->Sharpness = 60;
	return 0;
}

static int	SetImagingParam(ImagingParam_S *info)
{
	//δ�ҵ�ͼ���������ѡ��
	printf("info->Brightness = %d",info->Brightness);
	return 0;
}

static int	GetImagingCab(ImagingCab_S *info)
{
	//δ�ҵ�ͼ���������ѡ��
	info->Brightness.max = 100;
	info->Brightness.min = 0;
	info->ColorSaturation.max = 100;
	info->ColorSaturation.min = 0;
	info->Contrast.max = 100;
	info->Contrast.min = 0;
	info->Sharpness.max = 100;
	info->Sharpness.min = 0;
	return 0;
}

PATTERN_SINGLETON_IMPLEMENT(CAvOnvifSer)

av_bool CAvOnvifSer::InitCbfun()
{
	memset(&m_OnvifSerHandle,0,sizeof(OnvifSerHandle_S));
	m_OnvifSerHandle.pGetDeviceInfo			= GetDeviceInfo;
	m_OnvifSerHandle.pSetDeviceInfo			= SetDeviceInfo;
	m_OnvifSerHandle.pGetDeviceCab			= GetDeviceCab;
	m_OnvifSerHandle.pGetNetWorkInfo		= GetNetWorkInfo;
	m_OnvifSerHandle.pSetNetWorkInfo		= SetNetWorkInfo;
	m_OnvifSerHandle.pGetNetProtocolInfo	= GetNetProtocolInfo;
	m_OnvifSerHandle.pSetNetProtocolInfo	= SetNetProtocolInfo;
	m_OnvifSerHandle.pGetVideoEncode		= GetVideoEncode;
	m_OnvifSerHandle.pSetVideoEncode		= SetVideoEncode;
	m_OnvifSerHandle.pGetVideoEncodeCab		= GetVideoEncodeCab;
	m_OnvifSerHandle.pGetAudioEncode		= GetAudioEncode;
	m_OnvifSerHandle.pSetAudioEncode		= SetAudioEncode;
	m_OnvifSerHandle.pGetSystemTime			= GetSystemTime;
	m_OnvifSerHandle.pSetSystemTime			= SetSystemTime;
	m_OnvifSerHandle.pGetUsrInfo			= GetUsrInfo;
	m_OnvifSerHandle.pSetImagingParam		= SetImagingParam;
	m_OnvifSerHandle.pGetImagingParam		= GetImagingParam;
	m_OnvifSerHandle.pGetImagingCab			= GetImagingCab;
	return av_true;
}

CAvOnvifSer::CAvOnvifSer()
{

}

CAvOnvifSer::~CAvOnvifSer()
{

}

av_bool CAvOnvifSer::Start()
{
	int ret = 0;
	InitCbfun();
	ONVIFAPI_Init(&m_OnvifSerHandle);
	ret = ONVIFAPI_SerStart(8080);
	return ret == 0 ? av_true : av_false;
}

av_bool CAvOnvifSer::ReStart()
{
	int ret = 0;
	ret = Stop();
	ret = Start();
	return ret == 0 ? av_true : av_false;
}

av_bool CAvOnvifSer::Stop()
{
	int ret = 0;
	ret = ONVIFAPI_ServerStop();
	return ret == 0 ? av_true : av_false;
}
