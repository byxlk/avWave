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
#include "AvUser/AvUser.h"


SINGLETON_IMPLEMENT(CAvUser);

CAvUser::CAvUser()
{

}

CAvUser::~CAvUser()
{
}

av_bool CAvUser::AddGroup()
{
	return av_true;
}
av_bool CAvUser::DelGroup()
{
	return av_true;
}
av_bool CAvUser::ModifyGroup()
{
	return av_true;
}
av_bool CAvUser::GroupList()
{
	return av_true;
}

av_bool CAvUser::AddUser()
{
	return av_true;
}
av_bool CAvUser::DelUser()
{
	return av_true;
}
av_bool CAvUser::ModifyUser()
{
	return av_true;
}
av_bool CAvUser::CheckOut()
{
	return av_true;
}
