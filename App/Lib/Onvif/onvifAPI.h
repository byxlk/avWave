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
#ifndef __ONVIF_API_H__
#define __ONVIF_API_H__

#ifdef __cplusplus
extern "C" {
#endif 

#define DF_MAX_CHN 		 			32
#define DF_MAX_STREAM 		 		3
#define DF_MAX_URLSTRLEN 			128
#define DF_MAX_SUPPORTRESLUTION		32 

#ifndef KEY_FALSE
#define KEY_FALSE				-1
#endif

#ifndef KEY_TRUE
#define KEY_TRUE				0
#endif

#ifndef KEY_PROBE
#define KEY_PROBE				1
#endif

typedef enum _ENUM_DEVTYPE_E{
	ENUM_DEVTYPE_IPC = 0x00,
	ENUM_DEVTYPE_NVR,
}ENUM_DEVTYPE_E;

typedef enum _ENUM_ENABLED_E{
	ENUM_ENABLED_FALSE = 0x00,
	ENUM_ENABLED_TRUE,
}ENUM_ENABLED_E;

typedef struct _DeviceInfo_S{
	char 				city[64];
	char 				country[64];
	char				facturer[64];//������
	char				model[64];//��Ʒ�ͺ�
	char				SerialNumber[64];//�豸���к�
	char				softwareVer[128];//����汾
	char 				name[128];//����
	ENUM_DEVTYPE_E		devType;//�豸����
}DeviceInfo_S;
//-1 �ر� 0 �� 
typedef struct _DeviceCab_S{
	int 	AnalyticsEnable;
	int 	VideoEnable;
	int 	AudioEnable;
	int 	PtzEnable;
	int		chnelCount;
	int		streamCount;
}DeviceCab_S;

typedef struct _NetWorkInfo_S{
	char				ip[16];
	char				ethernetName[16];//��������
	char				dns[16];
	char				gateway[16];
	char				mac[32];//
	char				hostName[64];//������
	char				ntpserver[64];//NTPserver
	ENUM_ENABLED_E		DhcpEnable;//DHCP IP
	ENUM_ENABLED_E		ddnsDhcpEnable;//DHCP DDNS
	ENUM_ENABLED_E		DhcpNtp;//NtpDHcp Ĭ��Ϊ10.1.1.1 DHCP�ر�
}NetWorkInfo_S;

typedef struct _VedioReslution_S{
	int width;
	int height;
}VedioReslution_S;

typedef struct _IntRange_S{
	int max;
	int min;
}IntRange_S;

typedef struct _FloatRange_S{
	float max;
	float min;
}FloatRange_S;

typedef enum _VideoEncoding_E{
	 VideoEncoding__NULL  = 0,
	 VideoEncoding__JPEG  =  1 << 0,
	 VideoEncoding__MPEG4 = 1 << 1, 
	 VideoEncoding__H264 =  1 << 2,
	 VideoEncoding__H265 =  1 << 3,
}VideoEncoding_E; 

typedef enum _H264Profile_E{
	 H264Profile__NULL 		=	 0,
	 H264Profile__Baseline 	=	1 << 0,
	 H264Profile__Main 		=	1 << 1, 
	 H264Profile__Extended	=	1 << 2,
	 H264Profile__High 		= 	1 << 3,
}H264Profile_E; 

typedef enum _AudioEncoding_E{
	 AudioEncoding__NULL,
	 AudioEncoding__G711 = 1,
	 AudioEncoding__G726,
	 AudioEncoding__AAC,
}AudioEncoding_E; 


typedef struct _VideoEncode_S{
	int					frameRate;
	int					bitrate;
	int					qulity;
	int					gop;
	int					cvbrMode;//0 CBR
	VideoEncoding_E		encoding;
	H264Profile_E		h264Profile;
	VedioReslution_S	reslution;		
}VedioEncode_S;

typedef struct _VedioEncodeCab_S{
	IntRange_S			frameRateRange;
	IntRange_S			bitrateRange;	
	IntRange_S			qulityRange;	
	IntRange_S			gopRange;	
	VideoEncoding_E		encodingCab;
	H264Profile_E		h264ProfileCab;
	VedioReslution_S	defaultReslution;
	VedioReslution_S	maxReslution;	
	VedioReslution_S	resSupport[DF_MAX_SUPPORTRESLUTION];
	int					resSupportNum;
}VedioEncodeCab_S;


typedef struct _AudioEncode_S{
	AudioEncoding_E Encoding;
	int Bitrate;
	int SampleRate;
}AudioEncode_S;



typedef struct _NetProtocolInfo_S{
	int 	onvifPort;
	int		rtspPort;
	char	rtspUrl[DF_MAX_CHN][DF_MAX_STREAM][DF_MAX_URLSTRLEN];//char *rtspUrl[chnelCount*streamCount];
	char	snapUrl[DF_MAX_CHN][DF_MAX_STREAM][DF_MAX_URLSTRLEN];
}NetProtocolInfo;


typedef struct _SystemTime_S{
	int	timeZone;
	int year;
	int	month;
	int	day;
	int hour;
	int min;
	int sec;
}SystemTime_S;

typedef enum _ENUM_USRLEVEL_E{
	ENUM_USRLEVEL_Operator = 0x01,
	ENUM_USRLEVEL_Administrator,
}ENUM_USRLEVEL_E;

typedef struct _UsrInfo_S{
	ENUM_USRLEVEL_E  userLevel;
	char 			 usrname[128];
}UsrInfo_S;

typedef struct _ImagingCab_S{
	IntRange_S			Brightness;
	IntRange_S			ColorSaturation;	
	IntRange_S			Contrast;	
	IntRange_S			Sharpness;	
//	IntRange_S			Iris;	
//	IntRange_S			Focus;		
}ImagingCab_S;

typedef struct _ImagingParam_S{
	int			Brightness;
	int			ColorSaturation;	
	int			Contrast;	
	int			Sharpness;	
//	int			Iris;	
//	int			Focus;		
}ImagingParam_S;

typedef struct _PtzMoveRange{
	FloatRange_S x;
	FloatRange_S y;
}PtzMoveRange;

typedef struct _PtzCab_S{
	PtzMoveRange	absolutePos;
	FloatRange_S	absoluteZoom;
	PtzMoveRange	relationPos;
	FloatRange_S	relationZoom;
	PtzMoveRange	continuePos;
	FloatRange_S	continueZoom;
	IntRange_S		ptzTimeOut;
	int				maxPreset;
	int				homeSupported;
	int				tourSupported;
}PtzCab_S;

typedef struct _PtzConfig_S{
	int timeOut;
}PtzConfig_S;

typedef struct _OnvifApiSerHandle_S{
	int (*pGetDeviceInfo)(DeviceInfo_S *info);
	int (*pSetDeviceInfo)(DeviceInfo_S *info);
	int (*pGetDeviceCab)(DeviceCab_S *info);
	int (*pGetNetWorkInfo)(NetWorkInfo_S *info);
	int (*pSetNetWorkInfo)(NetWorkInfo_S *info);
	int (*pGetNetProtocolInfo)(NetProtocolInfo *info);
	int (*pSetNetProtocolInfo)(NetProtocolInfo *info);
	int (*pGetVideoEncode)(int chn,int streamId,VedioEncode_S *info);
	int (*pSetVideoEncode)(int chn,int streamId,VedioEncode_S *info);
	int (*pGetVideoEncodeCab)(int chn,int streamId,VedioEncodeCab_S *info);
	int (*pGetAudioEncode)(int chn,int streamId,AudioEncode_S *info);
	int (*pSetAudioEncode)(int chn,int streamId,AudioEncode_S *info);	
	int (*pGetSystemTime)(SystemTime_S *info);
	int	(*pSetSystemTime)(SystemTime_S *info);
	int	(*pGetUsrInfo)(int *usrNum,UsrInfo_S *info);//���50��
	int	(*pGetImagingParam)(ImagingParam_S *info);	
	int	(*pSetImagingParam)(ImagingParam_S *info);
	int	(*pGetImagingCab)(ImagingCab_S *info);
	int (*pGetPtzCab)(PtzCab_S *info);
	int (*pGetPtzConfig)(PtzConfig_S *info);
	int (*pSetPtzConfig)(PtzConfig_S *info);
}OnvifSerHandle_S;

int ONVIFAPI_Init(OnvifSerHandle_S *handle);//��ʼ��
int ONVIFAPI_ServerStop();//ֹͣ
int ONVIFAPI_SerStart(int port);//����
#ifdef __cplusplus
}
#endif

#endif
