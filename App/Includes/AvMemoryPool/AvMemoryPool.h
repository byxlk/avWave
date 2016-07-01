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
#ifndef _AVMEMORYPOOL_H_
#define _AVMEMORYPOOL_H_

#include "Apis/AvWareType.h"
#include "CAvObject.h"
#include "MemPool/CMemoryPool.h"

#define D_AVMEMORYPOOL_SIZE 1024*1024*8 //8M
#define D_AVMEMORYPOOL_CHUNK_SIZE 128


class CAvMemoryPool
{
public:
	SINGLETON_DECLARE(CAvMemoryPool);
private:
	CAvMemoryPool();
	~CAvMemoryPool();


public:
	av_bool Initialize();
	av_void *malloc(size_t size);
	av_void *realloc(av_void *ptr, size_t size);
	av_void free(av_void *ptr);
	av_void dump();

private:
	av_void *GetRealAddr(av_void *ptr);
	av_u32   GetMemSize(av_void *ptr);

private:
	MemPool::CMemoryPool *ptrMemPool;
};

#define g_AvMemoryPool (*CAvMemoryPool::instance())


#ifdef __cplusplus
extern "C" {
#endif
	//next two func only for BSP 
	av_void *AvMemoryPoolMalloc(size_t size);
	av_void *AvMemoryPoolRealloc(av_void *ptr, size_t size);
	av_void  AvMemoryPoolFree(av_void *ptr);


#ifdef __cplusplus
}
#endif














#endif

