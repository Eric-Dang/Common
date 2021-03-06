//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-24   16:05
//	File Name:	buffer.cpp
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include "buffer.h"
#include "liblog.h"
#include "common_sys_fun.h"
//-------------------------------------------------------------------------------------------------
char* default_alloc(unsigned int nSize)
{
	return ((char*)(malloc(nSize)));
}

void  default_free(char* pBuf)
{
	free((void*)pBuf);
}
//-------------------------------------------------------------------------------------------------
#define _PRINT_DETIAL
//-------------------------------------------------------------------------------------------------
Block::Block(unsigned int nSize, AllocBufferFun pAllocFun, FreeBufferFun pFreeFun)
{
	m_pData = pAllocFun(nSize);
	m_pRead = m_pWrite = m_pData;
	m_pTail = m_pData + nSize;
	m_nSize = nSize;

	m_fnFreeBuf = pFreeFun;

	m_pNext = this;
	m_pPrev = this;
}

#ifdef _DEBUG
void Block::SetBlockName(char* szName)
{ 
	memset(m_sName, 0, BLOCK_NAME_LEN);
	strncpy(m_sName, szName, BLOCK_NAME_LEN);
	m_sName[BLOCK_NAME_LEN-1] = '\0';
}
#endif // _DEBUG

Block::~Block()
{
	Delete();

	if (m_pData)
		m_fnFreeBuf(m_pData);

	m_pData = m_pRead = m_pWrite = m_pTail = NULL;
}

unsigned int Block::GetCanReadDataSize()
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	// 在多线程下，m_pWrite其他地方使用，为了防止函数内部不一致，因此先取出
	char* pWrite = m_pWrite;
	if (m_pRead > pWrite)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "GetReadDataSize m_pRead(0x%08x) > m_pWrite(0x%08x), block buffer(0x%08x), size(%d).", m_pRead, pWrite, m_pData, m_nSize);
		assert(false);
	}

	return pWrite - m_pRead;
}

char* Block::GetReadData(unsigned int& nReadSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);

	char* pWrite = m_pWrite;
	if (m_pRead > pWrite)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "ReadData m_pRead(0x%08x) > m_pWrite(0x%08x), block buffer(), size(%d).", m_pRead, pWrite, m_pData, m_nSize);
		assert(false);
	}

	nReadSize = pWrite - m_pRead;
	return m_pRead;
}

void Block::MarkReadData(unsigned int nSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	unsigned int nFree = GetCanReadDataSize();

	if (nSize > nFree)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "MarkReadData nSize(%d) > nFree(%d).", nSize, nFree);
		assert(false);
	}

	m_pRead += nSize;
}

unsigned int Block::ReadData(char* pDest, unsigned int nReadSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	assert(pDest != NULL && nReadSize > 0);

	unsigned int nFree = GetCanReadDataSize();
#if defined(_DEBUG) && defined(_PRINT_DETIAL)
	printf("Block(%s) Read Data(%d)->(%d).\n", m_sName, nFree, nReadSize);
#endif

	if (nReadSize < nFree)
	{
		memcpy(pDest, m_pRead, nReadSize);
		m_pRead += nReadSize;
		return nReadSize;
	}
	else
	{
		memcpy(pDest, m_pRead, nFree);
		m_pRead += nFree;
		return nFree;
	}
}

unsigned int Block::GetCanWriteDataSize()
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	if (m_pWrite > m_pTail)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "GetWriteSize m_pWrite(0x%08x) > m_pTail(0x%08x).", m_pWrite, m_pTail);
		assert(false);
	}
	
	return m_pTail - m_pWrite;
}

unsigned int Block::WriteData(char* pData, unsigned int nSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);
#if defined(_DEBUG) && defined(_PRINT_DETIAL)
	printf("Block(%s) Write Data(%d).\n", m_sName, nSize);
#endif

	unsigned int nFree = GetCanWriteDataSize();

	if (nSize > nFree)
	{
		memcpy(m_pWrite, pData, nFree);
		m_pWrite += nFree;
		return nFree;
	}
	else
	{
		memcpy(m_pWrite, pData, nSize);
		m_pWrite += nSize;
		return nSize;
	}
}

char* Block::GetWriteBuffer(unsigned int& nFreeSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	nFreeSize = GetCanWriteDataSize();

	return m_pWrite;
}

void Block::MarkWriteData(unsigned int nSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);	
	unsigned int nFreeSize = GetCanWriteDataSize();

	if (nSize > nFreeSize)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "MarkWriteData nSize(%d) > nFree(%d).", nSize, nFreeSize);
		assert(false);
	}

	m_pWrite += nSize;
}

void Block::Add(Block* pNew)
{
	pNew->m_pNext = m_pNext;
	pNew->m_pPrev = this;

	m_pNext->m_pPrev = pNew;
	m_pNext = pNew;
}

void Block::Delete()
{
	m_pNext->m_pPrev = m_pPrev;
	m_pPrev->m_pNext = m_pNext;
}

void Block::Clear()
{
	m_pRead = m_pWrite = m_pData;
}

//-------------------------------------------------------------------------------------------------
// Buffer 
//-------------------------------------------------------------------------------------------------

Buffer::Buffer(unsigned int nLimit, unsigned int nBlockSize, AllocBufferFun pAllocFun, FreeBufferFun pFreeFun)
{
	m_nBlockLimit = nLimit;
	m_nBlockCount = 0;

	m_pReadBlock  = NULL;
	m_pWriteBlock = NULL;

	m_nBlockSize = nBlockSize;

	m_pAllocFun = pAllocFun;
	m_pFreeFun  = pFreeFun;

#ifdef _DEBUG
	SetName("buffer");
	m_nTotalBlockCount = 0;
#endif // _DEBUG

	Init();
}

Buffer::~Buffer()
{
	Block* pTmp = m_pWriteBlock;
	m_pReadBlock = m_pWriteBlock->m_pPrev;
	while (pTmp)
	{
		pTmp = m_pWriteBlock->m_pNext;
		delete m_pWriteBlock;
		
		// 删除最后一个
		if (pTmp == m_pReadBlock)
		{
			delete m_pReadBlock;
			break;
		}
		else
			m_pWriteBlock = pTmp;
	}

	m_pReadBlock = NULL;
	m_pWriteBlock = NULL;

	m_nBlockCount = 0;
}


void Buffer::Init()
{
	m_pWriteBlock = new Block(m_nBlockSize, m_pAllocFun, m_pFreeFun);
	//// 第一个块需要自己
	//m_pWriteBlock->m_pNext = m_pWriteBlock;
	//m_pWriteBlock->m_pPrev = m_pWriteBlock;
	m_pReadBlock = m_pWriteBlock;
	m_nBlockCount ++;
#ifdef _DEBUG
	SetBlcokName(m_pWriteBlock);
#endif // _DEBUG
}

Block* Buffer::NewBlock()
{
	if (m_nBlockLimit > 0 && m_nBlockLimit <= m_nBlockCount)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "NewBlock error m_nBlockLimit(%d) <= m_nBlockCount(%d).", m_nBlockLimit, m_nBlockCount);
		return NULL;
	}

	Block* pNew = new Block(m_nBlockSize, m_pAllocFun, m_pFreeFun);
	m_pWriteBlock->Add(pNew);
	m_nBlockCount++;
	WriteLog(FC_GREEN, STDOUT_FILE_HANDLE, "NewBlock m_nBlockCount(%d).", m_nBlockCount);
	m_pWriteBlock = m_pWriteBlock->m_pNext;
#ifdef _DEBUG
	SetBlcokName(pNew);
#endif // _DEBUG
	return pNew;
}

void Buffer::SetAllocAndFreeFuns(AllocBufferFun pAllocFun, FreeBufferFun pFreeFun)
{
	m_pAllocFun = pAllocFun;
	m_pFreeFun  = pFreeFun;
}

void Buffer::SetBlockLimit(unsigned int nLimit)
{	
	m_nBlockLimit = nLimit;
}

void Buffer::SetBlockSize(unsigned int nBlockSize)
{
	m_nBlockSize = nBlockSize;
}

unsigned int Buffer::GetCanReadSize()
{	
	Block* pTmp = m_pReadBlock;
	unsigned int nTotalSize = 0;
	while (pTmp != m_pWriteBlock)
	{
		nTotalSize += pTmp->GetCanReadDataSize();
		pTmp = pTmp->m_pNext;
	}	

	nTotalSize += m_pWriteBlock->GetCanReadDataSize();
	return nTotalSize;
}

unsigned int Buffer::ReadData(char* pDest, unsigned int nSize)
{
	char* pTmp = pDest;
	unsigned int nTotalRead = 0;
	Block* pWrite = m_pWriteBlock;
	while (m_pReadBlock != pWrite)
	{
		unsigned int nRealReadSize = m_pReadBlock->ReadData(pTmp, nSize);
		pTmp		+= nRealReadSize;
		nTotalRead	+= nRealReadSize;
		nSize		-= nRealReadSize;

		if (nSize > 0)
		{
			// 读完一个块
			m_pReadBlock->Clear();
			m_pReadBlock = m_pReadBlock->m_pNext;
		}
		else
		{
			if (m_pReadBlock->IsReadAll())
				m_pReadBlock = m_pReadBlock->m_pNext;
			break;
		}
	}
	
	// 当前读写在同一个block
	if (nSize > 0)
		nTotalRead += m_pReadBlock->ReadData(pTmp, nSize);

	return nTotalRead;
}

char* Buffer::GetReadData(unsigned int& nSize)
{
	return m_pReadBlock->GetReadData(nSize);
}

void Buffer::MarkReadData(unsigned int nSize)
{
	m_pReadBlock->MarkReadData(nSize);
	// m_pReadBlock标记后，已经完全读完，m_pReadBlock指向下一个block, 如果是同读写同一个块则不跳到下一个
	if (m_pReadBlock->IsReadAll() && m_pReadBlock != m_pWriteBlock)
		m_pReadBlock = m_pReadBlock->m_pNext;
}


bool Buffer::WriteData(char* pData, unsigned int nSize)
{
	char* pTmp = pData;
	Block* pRead = m_pReadBlock;
	do
	{
		unsigned int nRealSize = m_pWriteBlock->WriteData(pTmp, nSize);
		pTmp += nRealSize;
		nSize -= nRealSize;

		if (nSize > 0)
			m_pWriteBlock = m_pWriteBlock->m_pNext;
		else
		{
			if (m_pWriteBlock->IsWriteAll())
			{
				if (m_pWriteBlock->m_pNext == m_pReadBlock)
					NewBlock();
				else
					m_pWriteBlock = m_pWriteBlock->m_pNext;
			}
			return true;
		}
	} while (m_pWriteBlock != pRead);

	// 添加新的block
	while (nSize > 0)
	{
		if(NewBlock() == NULL)
			return false;

		unsigned int nRealSize = m_pWriteBlock->WriteData(pTmp, nSize);
		pTmp += nRealSize;
		nSize -= nRealSize;
	}

	return true;
}

char* Buffer::GetWriteBuffer(unsigned int& nSize)
{
	return m_pWriteBlock->GetWriteBuffer(nSize);
}

bool Buffer::MarkWriteData(unsigned int nSize)
{
	m_pWriteBlock->MarkWriteData(nSize);
	if (m_pWriteBlock->IsWriteAll())
	{
		if (m_pWriteBlock->m_pNext == m_pReadBlock)
		{
			if (NewBlock() == NULL)
				return false;
		}
		else
			m_pWriteBlock = m_pWriteBlock->m_pNext;
	}
	
	return true;
}

#ifdef _DEBUG
void Buffer::SetName(char* szName)
{
	memset(m_szName, 0, BLOCK_OWNER_NAME);
	strncpy(m_szName, szName, BLOCK_OWNER_NAME);
	m_szName[BLOCK_OWNER_NAME - 1] = '\0';
}

void Buffer::SetBlcokName(Block* pBlock)
{
	char szBlock[BLOCK_NAME_LEN];
	memset(szBlock, 0, BLOCK_NAME_LEN);
	csf_sprintf(szBlock, BLOCK_NAME_LEN, "%s-block-%05d", m_szName, m_nTotalBlockCount++);
	pBlock->SetBlockName(szBlock);
}
#endif // _DEBUG
