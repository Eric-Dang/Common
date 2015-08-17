//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   20:52
//	File Name:	log.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	����ӿڡ�
//-------------------------------------------------------------------------------------------------
#include "log_config.h"
//-------------------------------------------------------------------------------------------------
// write into file
//-------------------------------------------------------------------------------------------------
// ����һ��log�ļ�
LOG_API _FILE_HANDLE OpenNewLogFile(const char* szName);

// �����־
LOG_API bool WriteLog(_FILE_HANDLE hLogFile, const char* szFormat, ...);

// �����־�Լ����ö�ջ
LOG_API bool WriteCallStackLog(_FILE_HANDLE hLogFile, const char* szFormat, ...);

// �ر���־�ļ�
LOG_API void CloseLogFile(_FILE_HANDLE hLogFile);

//-------------------------------------------------------------------------------------------------
// write into stdout
//-------------------------------------------------------------------------------------------------
// �������׼���, write log info into stdout
LOG_API void WriteStdLog(const char* szFormat, ...);

// �������׼����������flush��flush stdout after write log info into stdout 
LOG_API void WriteStdLogAndFlush(const char* szFormat, ...);


