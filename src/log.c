//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   20:54
//	File Name:	log.c
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include "system.h"
#include "log.h"
#include "logfile.h"

typedef std::map<_FILE_HANDLE, CLogFile*> _ALL_LOG_FILE;
static _ALL_LOG_FILE log_files;
//-------------------------------------------------------------------------------------------------

/*
CreateNewLogFile:
parameter: the log file name, max length if LOG_FILE_PATH_LEN
*/
LOG_API _FILE_HANDLE CreateNewLogFile(const char* szName)
{

}