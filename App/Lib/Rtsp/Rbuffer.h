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
#ifndef _RBUFFER_H_
#define _RBUFFER_H_


#define DEFAULT_RBUFFER_LEN 6*1024

class CRBuffer
{
public:
	CRBuffer(int size = DEFAULT_RBUFFER_LEN);
	virtual ~CRBuffer();
	int Append(const char *buf, int len);
	char *GetBuffer();
	int   GetBufferLen();
	int	  GetbufferSize();
	int	  Reset();
	int	  Pop(int popLen);
private:
	char *m_Buffer;
	int	  m_BufSize;
	int	  m_BufLen;
};







#endif