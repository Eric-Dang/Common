//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-24   16:00
//	File Name:	libbuffer.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include <stdio.h>

#include "buffer_config.h"
//-------------------------------------------------------------------------------------------------
class Buffer;
//-------------------------------------------------------------------------------------------------
/* 
����: ����һ��Buffer����
����1: ����buf�����������ΪNULL����Buffer����������bufferʱʹ���������������ʹ��Ĭ�ϵ����뺯��
����2: �ͷ�buf�����������ΪNULL����Buffer�������ͷ�bufferʱʹ���������������ʹ��Ĭ�ϵ��ͷź���
����ֵ: �ɹ�ʱ����Buffer�����ָ�룬ʧ���򷵻�NULL

name: create a Buffer object
param pfnAllocFun: allocate new buffer. if it is not NULL, Buffer object will allocate buffer by using 
pfnAllocFun, otherwise, using default allocate fun.
param pfnFreeFun: free the allocated buffer. if it is not NULL, Buffer object will allocate buffer by using 
pfnAllocFun, otherwise, using default free fun.
return value: On success a point for new buffer object is returned, On error NULL is returned
*/
Buffer* CreateNewBufferObj(AllocBufferFun pfnAllocFun = NULL, AllocBufferFun pfnFreeFun = NULL);

/*
����: ɾ��Buffer����
����1: Ҫɾ���Ķ���

name: delete Buffer object
param 1: object need to be deleted
*/
void DeleteBufferObj(Buffer* pObj);

/*
����: ����Buffer�����������
����1: Buffer����
����2: ÿ�������ڴ�ʱ�Ĵ�С�� Ĭ��ֵ��buffer_config.h ALLOC_BUFFER_SIZE
����3: �����������buffer������, Ĭ��ֵΪ0�� ��ʾ������

name: set config of Buffer object
param 1: the Buffer object
param 2: the size of alloc new buffer
param 3: the max times for alloc buffer. default value is 0, that mean no limit on the times for alloc buffer
*/
void SetConfigOfBufferObj(Buffer* pObj, unsigned int nAllocBufferSize, unsigned int nMaxOfAllocBuffers);

/*
����: ������ݵ�Buffer����
����1: Buffer����
����2: ��ӵ�����
����3: ��ӵ����ݵĳ���
����ֵ:�Ƿ���ӳɹ�

name: add data to Buffer object
param 1: the Buffer object
param 2: the data will add to the pObj
param 3: the length of pData
return value: return true on success, return false on error
*/
bool WriteDataToBuffer(Buffer* pObj, const char* pData, unsigned int nLen);

/*
����: ��ȡBuffer�����е�����
����1: Buffer����
����2: �������ݵĴ�ŵ�ַ
����3: ���Զ�ȡ����󳤶�
����ֵ:��ȡ�������ݳ���

name: read data from Buffer object
param 1: the Buffer object
param 2: the point of buffer will save the data is read from pObj
param 3: the length of pDest
return value: length of data is read from pObj is returned.
*/
unsigned int ReadDataFromBuffer(Buffer* pObj, char* pDest, unsigned int nDestLen);
