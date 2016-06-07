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
#ifndef __DH_WEB_HTTP_TASK_H__
#define __DH_WEB_HTTP_TASK_H__


#include "Apis/AvWareType.h"
#include "CObject.h"
#define WebPrintf av_msg
#define WebPerror av_error

#include <pthread.h>
#include <vector>
#include <string>
#include <semaphore.h>
#include <errno.h>



#include "CObject.h"
#define RECV_BUF_SIZE 2*1024



typedef enum __EnFileType
{
	EnFileType_Html,
	EnFileType_Text,
	EnFileType_Jpeg,
	EnFileType_Gif,
	EnFileType_Binary,
	EnFileType_Png,
	EnFileType_Cgi,
	EnFileType_Json,
	EnFileType_Xml,
	EnFileType_Default,
} EnFileType;

typedef int(CObject::*WebCallBack)(std::string InBuf, std::string &OutBuf);

class CWorkTask:public CObject
{   
public:   
 	CWorkTask();
	~CWorkTask();
	int Run();
	int SetSocket(int fdSock);//��socket������
	int SetWebAttr(std::string WebRoot, std::string WebIndex);

	int SetCallBack(CObject *obj, WebCallBack proc);
	int GetSocket();
	int HandleConnect(int fdSock,int iTimeout = 5000000);
	int ParseAndHandReq(int fdSock, char *pData, int iLen);
	int PacketHttpHeader(EnFileType content_type,std::string &strBuf,int fileLength);
	int SendNoBlock(int sockfd, char *buf,int len,unsigned int iTimeout = 5000000);
	int DoDir(int fdSock, char *name);
	int DoScriptFile(int fdSock, char *name, EnFileType EnFileType);
	int DoStaticFile(int fdsock, char *name, EnFileType EnFileType);
	int DoDataFile(int fdSock, std::string jsondata);
	int cpFile(int fdSock,char *name, EnFileType EnFileType);
	int CheckValidMsg(char* bufMsg,int lenMsg);

	int RunLongCon();
	int HandleLongConnect(int fdSock,int iTimeout = 5000000);


private:
	char m_chRecvBuf[RECV_BUF_SIZE];
	int m_ProcSock;//Ҫ�����socket

	std::string m_WebRoot;
	std::string m_IndexHtml;

	CObject *m_CbObj;
	WebCallBack  m_CbProc;
};   


/**  
//�̳߳�
**/  
   

class CWebThreadPool
{  
public:  
	CWebThreadPool();
	CWebThreadPool(int threadNum);
	void InitPool(int threadNum);
	int AddTask(CWorkTask *task);      //��������ӵ��̳߳���   
	int StopAll(); 
	int Create();          //�������е��߳� 
	static void* ThreadProc(void * arg); //���̵߳��̺߳���
	void ProcessTaskProc();
private:   
	std::vector <CWorkTask*> m_vecTaskList;         //�����б�   
	int m_iThreadNum;                            //�̳߳����������߳��� 
	pthread_mutex_t m_pthreadMutex;    //�߳�ͬ����   
	sem_t m_Semaphore;

  	
};  
#endif

