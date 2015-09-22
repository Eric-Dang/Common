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

char* default_alloc(unsigned int nSize);
void  default_free(char* pBuf);


// ���ݿ�
class Block : public deque_node<Block>
{
public:
	/*
	* nSize is the bytes of block can store
	* pAllocFun: alloc store data buf
	* pFreeFun: free buff
	*/
	Block(unsigned int nSize, AllocBufferFun pAllocFun = default_alloc, FreeBufferFun pFreeFun = default_free);
	~Block();

public:
	// character of deque
	/*
	* add the pNew after self
	*/
	void	Add(Block* pNew);
	/*
	* delete self from the deque
	*/
	void	Delete();

public:
	// �ڶ��߳���ʹ�ã���������д������������ͬһ���̣߳����Ա�֤��д������һ�¡�	
	/*
	* ��ȡ�ɶ�ȡ�����ݳ���
	* character of buffer block
	* get the size of data can be read from the block
	*/
	unsigned int GetCanReadDataSize();
	/*
	* ���洢�����ݶ���pDest�У����ɶ�nReadSize������ֵΪ��ʵ��ȡ�Ĵ�С
	* read up to nReadSize bytes from block into the buffer starting at pDest
	* return the number of bytes read
	*/
	unsigned int ReadData(char* pDest, unsigned int nReadSize);
	/*
	* ��ȡblock�п��Զ�ȡ���ݵĿ�ʼλ�ã� nReadSize���ؿɶ�ȡ�ĳ���
	* if there is no free data, NULL is returned, otherwise, the point starting at block data that can be read is returned, 
	* and nReadsize is set to the size of free data
	*/
	char* GetReadData(unsigned int& nReadSize);
	/*
	* ����Ѷ�nSize���ȵ�buffer
	* mark block had been read into data of nSize bytes
	*/
	void MarkReadData(unsigned int nSize);


	/*
	* get the size of free data that can be wrote into block
	*/
	unsigned int GetCanWriteDataSize();
	/*
	* write data into block
	* write the pData into block, and size of pData is nSize, return value is the number of bytes has wrote into block	
	* д�����ݣ�����Ϊ��ʵд��ĳ���
	*/
	unsigned int WriteData(char* pData, unsigned int nSize);

	/*
	* GetWriteBuffer �� MarkWriteData ��Ҫ��ͬһ��ԭ���е���, ����һ��������WriteData
	* 1: ����GetWriteBuffer��ȡ��дָ���Լ���д����
	* 2: ʹ�ÿ�дָ�룬��buffer��д������
	* 3: ����MarkWriteData�����ǰ��д�볤��nSize������
	* GetWriteBuffer and MarkWriteData must call together, same as call WriteData
	* call step 1: call GetWriteBuffer, get point of free data and the nFreeSize
	* call step 2: write data into block by using free data point
	* call step 3: call MarkWriteData, nSize is the size that had wrote into block in step 2
	* get point of free data and the size
	*/
	char* GetWriteBuffer(unsigned int& nFreeSize);
	/*
	* mark block had been wrote into data of nSize bytes
	*/
	void MarkWriteData(unsigned int nSize);

	/*
	* �������
	*/
	void Clear();

	/*
	* ����buffer�������Ƿ����
	*/
	bool IsReadAll() { return (m_pTail == m_pRead); };
	/*
	* ����buffer�Ѿ��Ƿ�д��
	*/
	bool IsWriteAll() { return (m_pTail == m_pWrite); };


private:
	/*	
	* ���ݴ������
	* the buffer of block store data starting at pDest
	*/
	char*	m_pData;
	/*
	* ��ָ��λ��
	* the point for the data will be read
	*/
	char*	m_pRead;
	/*
	* дָ��λ��
	* the point for the data will be wrote
	*/
	char*	m_pWrite;
	/*
	* buf��ֹλ��
	* the point is the end of m_pData
	*/
	char*	m_pTail;
	/*
	* buf��С
	* size of m_pData
	*/
	unsigned int m_nSize;

	/*
	* free m_pData
	* buffer �ͷź���
	*/
	FreeBufferFun	m_fnFreeBuf;
};


class Buffer
{
public:
	Buffer(unsigned int nLimit = 0, unsigned int nBlockSize = ALLOC_BUFFER_SIZE, AllocBufferFun pAllocFun = default_alloc, FreeBufferFun pFreeFun = default_free);
	~Buffer();

public:
	// set buffer config
	/*
	* the max number of buffer can new block
	*/
	void SetBlockLimit(unsigned int nLimit);
	/*
	* set functions block alloc buffer and free buffer
	*/
	void SetAllocAndFreeFuns(AllocBufferFun pAllocFun, FreeBufferFun pFreeFun);
	/*
	* set the block buffer size
	*/
	void SetBlockSize(unsigned int nBlockSize);

	// Read Data
	/*
	* ��ȡ�ɶ����ݵĴ�С
	* get the size of data can be read
	*/
	unsigned int GetCanReadSize();
	/*
	* ��buffer�ж�ȡ���ݣ����ɶ�ȡnSize. ����ֵΪ�ܶ�ȡֵ
	*/
	unsigned int ReadData(char* pDest, unsigned int nSize);
	/*
	* ��ȡ�ɶ�����ָ���Լ��ɶ����ȣ���������Ϊm_pReadBlock�Ŀɶ����ݼ����ȣ����������еĿɶ�Block������
	*/
	char* GetReadData(unsigned int& nSize);
	/*
	* ��������Ѷ���ֻ���m_pReadBlock
	*/
	void MarkReadData(unsigned int nSize);


	// Write Data
	/*
	* ������д��buffer,���block�����ޣ����п���дʧ��
	*/
	bool WriteData(char* pData, unsigned int nSize);
	/*
	* ��ȡ��дָ���Լ����ȣ����ﷵ�ص�ֻ��m_pWriteBlock�Ŀ�дָ��ͳ���
	*/
	char* GetWriteBuffer(unsigned int& nSize);
	/*
	* ���д����nSize�����ݣ�ֻ���m_pWriteBlock
	* �����ȫ��ǣ�m_pWriteBlockָ����һ���������һ��block��m_pReadBlock��
	* ����Ҫ����һ��block����m_pWriteBlockָ���½���block���������ʧ���򷵻�flase
	*/
	bool MarkWriteData(unsigned int nSize);

private:
	/*
	* ������һ��block
	*/
	void Init();

	/*
	* ����һ���µ�block, ֻ����д��ʱ��Żᴴ��
	*/
	Block*	NewBlock();

public:
	/*
	* ���ڶ���block
	*/
	Block*		m_pReadBlock;
	/*
	* ����д��block
	*/
	Block*		m_pWriteBlock;

	/*
	* Block������
	*/
	unsigned int m_nBlockCount;
	/*
	* Block������, 0 ��ʾ��������
	*/
	unsigned int m_nBlockLimit;
	/*
	* block�����ݿ�Ĵ�С
	*/
	unsigned int m_nBlockSize;
	/*
	* alloc function
	*/
	AllocBufferFun	m_pAllocFun;
	/*
	* free function
	*/
	FreeBufferFun	m_pFreeFun;
};