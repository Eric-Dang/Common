//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-24   16:07
//	File Name:	buffer_config.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
// allocate buffer which size is n
typedef char* (*AllocBufferFun)(unsigned int n);
// free the allocated buffer
typedef void  (*FreeBufferFun)(char* pBuffer);


// default value for allocate buffer
#define ALLOC_BUFFER_SIZE 8192

