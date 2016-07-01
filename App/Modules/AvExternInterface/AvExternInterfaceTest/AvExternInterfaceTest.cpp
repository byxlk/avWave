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
#include "AvExternInterfaceTest.h"
#include "AvCapture/AvManCapture.h"
SINGLETON_IMPLEMENT(CAvExtInterFaceTest)


av_bool CAvExtInterFaceTest::Start()
{
	Capture *pCapture = g_AvManCapture.GetAvCaptureInstance(0);
	pCapture->Start(CHL_MAIN_T, this, (Capture::SIG_PROC_ONDATA)&CAvExtInterFaceTest::OnStream);
	return av_true;
}
av_bool CAvExtInterFaceTest::Stop()
{
	return av_true;
}

av_void CAvExtInterFaceTest::OnStream(av_uchar Channel, av_uchar Slave, CAvPacket *AvPacket)
{
	av_msg("CAvExtInterFaceTest::OnStream have data %d %d\n", Channel, Slave);
	if (0 && AvPacket->Slave() == CHL_MAIN_T){
		static int cnt = 0;
		cnt++;
		if (cnt < 200) return;
		static FILE *fp = NULL;
		if (fp == NULL) fp = fopen("/tmp/avExtinterText.h264", "wb");
		fwrite(AvPacket->GetRawBuffer(), AvPacket->GetRawLength(), 1, fp);

		if (cnt > 500){
			fclose(fp);
			av_error("avExtinterText write over\n");
		}
	}


	return ;
}


CAvExtInterFaceTest::CAvExtInterFaceTest()
{

}
CAvExtInterFaceTest::~CAvExtInterFaceTest()
{

}