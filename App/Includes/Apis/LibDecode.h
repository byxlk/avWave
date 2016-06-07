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
#ifndef _LIBDECODE_H_
#define _LIBDECODE_H_

#ifdef __cplusplus
extern "C" {
#endif


//��Ƶ����
av_bool AvAudioDecodeCreate();
av_bool AvAudioDecodeDestroy();
av_bool AvAudioDecodeStart();
av_bool AvAudioDecodeStop();
av_bool AvAudioDecodeSetFormat();
av_bool AvAudioDecodeBuffer();


typedef struct{
	av_u32	 CompMask;
	av_u32	 ImageSizeMask;// CHL_MAIN_T
	av_uchar ExtChannel;
	av_u32   ExtImageSizeMask[DisplaySize_NR];
	av_uchar MaxOutFrameRate;
}C_DecodeCaps;

av_bool AvGetDecodeCaps(av_uchar Channel, C_DecodeCaps *DecodeCaps);





#ifdef __cplusplus
}
#endif

#endif
