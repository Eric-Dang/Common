//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-24   16:05
//	File Name:	buffer.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include <stdio.h>

#include "buffer_config.h"
#include "deque.h"


// ���ݿ�
class Block : public deque_node<Block>
{
public:
	// nSize is the bytes of block can store
	// pAllocFun: alloc store data buf
	// pFreeFun: free buff
	Block(unsigned int nSize, AllocBufferFun pAllocFun, FreeBufferFun pFreeFun);
	~Block();

public:
	// character of deque
	// add the pNew after self
	void	Add(Block* pNew);
	// delete self from the deque
	void	Delete();

public:
	// �ڶ��߳���ʹ�ã���������д������������ͬһ���̣߳����Ա�֤��д������һ�¡�	

	// ��ȡ�ɶ�ȡ�����ݳ���
	// character of buffer block
	// get the size of data can be read from the block
	unsigned int GetCanReadDataSize();
	// ���洢�����ݶ���pDest�У����ɶ�nReadSize������ֵΪ��ʵ��ȡ�Ĵ�С
	// read up to nReadSize bytes from block into the buffer starting at pDest
	// return the number of bytes read
	unsigned int ReadData(char* pDest, unsigned int nReadSize);
	// ��ȡblock�п��Զ�ȡ���ݵĿ�ʼλ�ã� nReadSize���ؿɶ�ȡ�ĳ���
	// if there is no free data, NULL is returned, otherwise, the point starting at block data that can be read is returned, 
	// and nReadsize is set to the size of free data
	char* GetReadData(unsigned int& nReadSize);
	// ����Ѷ�nSize���ȵ�buffer
	// mark block had been read into data of nSize bytes
	void MarkReadData(unsigned int nSize);


	// get the size of free data that can be wrote into block	
	unsigned int GetCanWriteDataSize();
	// write data into block
	// write the pData into block, and size of pData is nSize, return value is the number of bytes has wrote into block	
	unsigned int WriteData(char* pData, unsigned int nSize);
	// GetWriteBuffer and MarkWriteData must call together, same as call WriteData
	// call step 1: call GetWriteBuffer, get point of free data and the nFreeSize
	// call step 2: write data into block by using free data point
	// call step 3: call MarkWriteData, nSize is the size that had wrote into block in step 2
	// get point of free data and the size
	char* GetWriteBuffer(unsigned int& nFreeSize);
	// mark block had been wrote into data of nSize bytes
	void MarkWriteData(unsigned int nSize);

private:
	// ���ݴ������	
	// the buffer of block store data starting at pDest
	char*	m_pData;
	// ��ָ��λ��
	// the point for the data will be read
	char*	m_pRead;
	// дָ��λ��
	// the point for the data will be wrote
	char*	m_pWrite;
	// buf��ֹλ��
	// the point is the end of m_pData
	char*	m_pTail;
	//  buf��С
	// size of m_pData
	unsigned int m_nSize;

	// free m_pData
	FreeBufferFun	m_fnFreeBuf;
};


class Buffer
{

};