//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   21:01
//	File Name:	log_config.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	config of log
//-------------------------------------------------------------------------------------------------

// DLL��ʱ����
#if defined(LOG_DLL)

#else
#define LOG_API extern
#endif 

// ����CreateNewLogFile���ظ��û����ļ����, define file handle function CreateNewLogFile return
typedef unsigned int _FILE_HANDLE;

// �ļ����ĳ���, �ļ����ܳ���ϵͳ����������ļ�·���ĳ���
// the max length of log file path. 
// the max length must be not bigger than 256, because it is the max length of system file path.
// the log class will record the log file path
#define LOG_FILE_PATH_LEN 256

// ÿ����־����󳤶ȣ� the max length of every log info
#define LOG_INFO_MAX_LEN  10240