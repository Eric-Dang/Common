//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   21:47
//	File Name:	logfile.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include "system.h"
#include "lock.h"


class CLogFile
{
public:
	CLogFile();
	~CLogFile();

public:
	// ʹ�ö��߳���
	// new mult thread lock, check the lock state when write log 
	void OpenLock();

	// write log info into m_pLogFile
	bool WriteLog(const char* szFormat, va_list vlArgs);

	// write log info and the call stack info into m_pLogFile
	bool WriteCallStackLog(const char* szFormat, va_list vlArgs);

	// close file
	void Close();

private:
	// log file
	FILE*	m_pLogFile;
	// mult thread lock, it will new in function OpenLock
	CLock*	m_pLock;
	// file path
	char*	m_szFileName;
};
