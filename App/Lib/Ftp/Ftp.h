#ifndef __FTP_H__
#define __FTP_H__

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#ifdef __linux__
#include <sys/types.h>          
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>


#else
#include <winsock2.h>
#endif


/**������**/
#define FTP_SEND_NOT_OVER	1	//�ļ�δ����
#define FTP_OK	0
#define FTP_ERROR -1
#define FTP_CONNECT_FAILED -2
#define FTP_AUTH_FAILED	-3
#define FTP_RECV_TIMEOUT	-4
#define FTP_SEND_TIMEOUT	-5
#define FTP_STR_NULL		-6

#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif

#define FTP_MAX_LEN 		1500
#define FTP_RECV_TIME 		5000
#define FTP_SEND_TIME		2000


#ifdef FTP_DBG_PROTOCOL
#define FTP_ASSERT_RETURN(x, y)	\
	do							\
	{							\
		if( !(x) )				\
			{					\
				printf("assert :%s:%d, error code :%d\n", __FILE__, __LINE__, y);	\
				exit(-1);		\
			}					\
	} while(0);
#else
#define FTP_ASSERT_RETURN(x, y)	\
	do							\
	{							\
	if( !(x) )				\
			{					\
			return y;		\
			}					\
	} while(0);
#endif

typedef enum
{
	FTT_BINEARY,	//�����ƴ��䷽ʽ
	FTT_ANSC	//ansc �봫�䷽ʽ
}FTP_TRAN_TYPE_E;


class CFtp
{
public:
	CFtp();
	virtual ~CFtp();

	int FtpLogin();
	int FtpQuit();

	int FtpSetConf(std::string Server, int Port, std::string Usrname, std::string Passwd);

	int FtpSendData(const char * buf, int& buflen);
	int FtpRecvData(char * buf, int& buflen);
	int FtpCloseData();

	int FtpChangePath(char * szPath);
	int FtpMkDir(char * szDir);
	int FtpMkDirRecursion(char * szDir);//�ݹ齨��Ŀ¼�ṹ
	int FtpList();//��ӡftp�������ļ��б�, ����ʹ��
	int FtpReturnRoot();//���ص��յ�¼��ʱ������Ŀ¼

	int FtpSize(const char *filename);//�����ļ��Ĵ�С�� ���ߴ���
	int FtpRename(const char * sourc, const char * dst);
	int FtpRest(int offset);

	int FtpAppend(const char *filename);/*����׷���ļ�*/
	int FtpStor(const char *filename);/*�����ϴ��ļ�*/
	int FtpRetr(const char *filename);//���������ļ�
	int FtpType(const FTP_TRAN_TYPE_E type_in);
	int FtpPassive();
	int FtpPwd( char * cur_dir );

private:

	int FtpConnect();
	int FtpSend(char * buf, int buflen);
	int FtpRecv(char * buf, int &buflen, int timeout);//timeout:��λΪ����
	int FtpRecv(int ftp_sock, char * buf, int &buflen, int timeout);//timeout:��λΪ����
	int FtpSendAndGet( const char * strCommand, const char * param, char * Response, int &ReponseState );

	int m_Ctrlsocket;
	int m_Datasocket;
	int login_success;
	
	std::string m_ServerIP;
	int m_ServerPort;
	std::string m_Username;
	std::string m_Passwd;

	std::string m_Filename;

	std::string Initial_dir;
};

#endif /*__FTP_H__*/
