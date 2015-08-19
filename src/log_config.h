//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   21:01
//	File Name:	log_config.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	config of log
//-------------------------------------------------------------------------------------------------
#pragma once
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

// ������ɫ������stdout
// font color can only be used on stdout
enum FontColor {
	FC_BLACK	= 0,
	FC_RED		= 1,
	FC_GREEN	= 2,
	FC_YELLOW	= 3,
	FC_BLUE		= 4,
	FC_MAGENTA	= 5,
	FC_CYAN		= 6,
	FC_WHITE	= 7,
};

// stdout 
#define STDOUT_FILE_HANDLE 0