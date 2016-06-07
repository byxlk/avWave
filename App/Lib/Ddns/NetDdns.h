
#ifndef _DDNS_ENABLE_H
#define _DDNS_ENABLE_H

typedef enum
{
	DDNS_3322,
	DDNS_DYNDNS,
	DDNS_DNSDYNMAIC,
	DDNS_BUTT,
}ENU_DDNS;

/* ===================================================================
** ������  ��DDNS_Enable
** �������ܣ�����ip��,ddns
** ����    ��
**           nType-------����     [in]
**           pDoamain----����     [in]
**           pName-------�û���   [in]
**           Pwd---------����     [in]
** ����ֵ  ��0----���³ɹ� 
**           1----����ipû�仯�������
**          -1---������������ʧ��
** ˵��    ��
**          while(1)
**          {
**              DDNS_Enable(nType, pDoamain, pName, Pwd);
**              sleep(120);
**          }
** ===================================================================*/
#ifdef __cplusplus
		extern "C" {
#endif
int DDNS_Enable(ENU_DDNS nType, char *pDoamain, char *pName, char *Pwd);
#ifdef __cplusplus
}
#endif 

#endif  //_DDNS_ENABLE_H

