/*******************************************************************
|  Copyright(c) 2015-2016 Graceport Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0
|  ����: ironman [ironman@graceport.cn]
|  ����: 2016��6��6��
|  ˵��:
|
|  �汾: 1.1
|  ����:
|  ����:
|  ˵��:
******************************************************************/
#ifndef _AV_FTP_H_
#define _AV_FTP_H_

#include "Apis/AvWareType.h"
#include "Ftp/Ftp.h"

/*
1,SetConf
2,Start
3,Send(localfile)/Send(RawFile)
4,Stop();
*/

class CAvFtp
{
public:
	CAvFtp();
	~CAvFtp();

	av_bool Start();
	av_bool Stop();
	
	//����ģʽҪ������
	av_bool SetConf(std::string Server, std::string Port, std::string Usrname, std::string Passwd);
	
	av_bool Upload(std::string SendFile);
	av_bool Upload(std::string FileName, av_uchar *data, av_u32 datalen);

	av_bool Mkdir(std::string dirName);
	av_bool CdDir(std::string dirName);


private:
	CFtp m_Ftp;
	std::string m_ServerIP;
	std::string m_Port;
	std::string m_Usrname;
	std::string m_Passwd;

	av_bool m_login;
};






#endif