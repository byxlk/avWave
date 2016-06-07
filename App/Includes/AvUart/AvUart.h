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
#ifndef _AVUART_H_
#define _AVUART_H_
#include "Apis/AvWareType.h"
#include "Apis/LibSystem.h"
#include "AvConfigs/AvConfigDevice.h"
#include "CObject.h"


typedef struct {
	av_u32	 Cmd;
	av_uchar HSpeed;
	av_uchar VSpeed;
	av_uchar arg1[2];
}PtzCmd;

class CAvUart
{
public:
	PATTERN_SINGLETON_DECLARE(CAvUart)
public:
	av_bool Initialize();
	av_bool Write(av_uchar index, av_buf &buf);
	av_bool Read(av_uchar index, av_buf &buf);
public:
	av_bool PtzStart(PtzCmd &cmd);

private:
	av_bool UartOpen(av_uchar index);
	av_bool UartClose(av_uchar index);
	av_bool UartCaps();
	av_bool SetAttr(av_uchar index, C_SerialAttr &Attr);
	av_void OnConfigsModify(CAvConfigUart *Config, int &result);
private:
	C_SerialCaps m_SerialCaps;

private:
	CAvConfigUart m_Config;

private:
	CAvUart();
	~CAvUart();

public:
	enum PtzCommand {
		PtzCommand_NONE = 0,
		PtzCommand_PTZ_STOP = 1,
		PtzCommand_LEFT_START = 2,
		PtzCommand_LEFT_STOP = 3,
		PtzCommand_RIGHT_START = 4,
		PtzCommand_RIGHT_STOP = 5,
		PtzCommand_UP_START = 6,
		PtzCommand_UP_STOP = 7,
		PtzCommand_DOWN_START = 8,
		PtzCommand_DOWN_STOP = 9,
		////
		PtzCommand_LEFT_UP_START = 10,
		PtzCommand_LEFT_UP_STOP = 11,
		PtzCommand_RIGHT_UP_START = 12,
		PtzCommand_RIGHT_UP_STOP = 13,
		PtzCommand_LEFT_DOWN_START = 14,
		PtzCommand_LEFT_DOWN_STOP = 15,
		PtzCommand_RIGHT_DOWN_START = 16,
		PtzCommand_RIGHT_DOWN_STOP = 17,
		//// ��ɨ�迪
		PtzCommand_SCAN_ON = 18,
		PtzCommand_SCAN_OFF = 19,
		//// �켣ɨ�迪
		PtzCommand_TRACK_ON = 20,
		PtzCommand_TRACK_OFF = 21,
		//// �����˶�
		PtzCommand_ABSOLUTE_MOVE = 22,
		//// ����˶�
		PtzCommand_RELATIVE_MOVE = 23,
		//// ���Ա佹
		PtzCommand_ABSOLUTE_FOCUS = 24,
		//// ����Ȧ��ʼ
		PtzCommand_IRIS_OPEN_START = 100,
		//// ����Ȧֹͣ
		PtzCommand_IRIS_OPEN_STOP = 101,
		//// �ع�Ȧ��ʼ
		PtzCommand_IRIS_CLOSE_START = 102,
		//// �ع�Ȧֹͣ
		PtzCommand_IRIS_CLOSE_STOP = 103,
		//// �������ʼ
		PtzCommand_FOCUS_NEAR_START = 104,
		//// �����ֹͣ
		PtzCommand_FOCUS_NEAR_STOP = 105,
		//// ����Զ��ʼ
		PtzCommand_FOCUS_FAR_START = 106,
		//// ����Զֹͣ
		PtzCommand_FOCUS_FAR_STOP = 107,
		//// ͼ���С��ʼ
		PtzCommand_ZOOM_WIDE_START = 108,
		//// ͼ���Сֹͣ
		PtzCommand_ZOOM_WIDE_STOP = 109,
		//// ͼ����ʼ
		PtzCommand_ZOOM_TELE_START = 110,
		//// ͼ����ֹͣ
		PtzCommand_ZOOM_TELE_STOP = 111,
		//// �������Դ��
		PtzCommand_CAMERA_ON = 200,
		//// �������Դ��
		PtzCommand_CAMERA_OFF = 201,
		//// �ƹ⿪
		PtzCommand_LAMP_ON = 202,
		//// �ƹ��
		PtzCommand_LAMP_OFF = 203,
		//// ��ˢ��
		PtzCommand_WIPER_ON = 204,
		//// ��ˢ��
		PtzCommand_WIPER_OFF = 205,
		//// �򿪼̵������
		PtzCommand_IO_ON = 206,
		//// �رռ̵������
		PtzCommand_IO_OFF = 207,
		//// ����Ԥ��λ
		PtzCommand_PRESET_POINT = 300,
		//// ����Ԥ��λ
		PtzCommand_SET_POINT = 301,
		//// ���Ԥ��λ	
		PtzCommand_CLEAR_POINT = 302
	};

};

#define g_AvUart (*CAvUart::instance())






#endif