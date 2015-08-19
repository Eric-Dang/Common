//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   20:52
//	File Name:	log.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	����ӿڡ�
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "log_config.h"
//-------------------------------------------------------------------------------------------------
// write into file
//-------------------------------------------------------------------------------------------------
// ����һ��log�ļ�
// parameter: 
// szName:			��־�ļ���(the path of log file)
// bWriteToStdout:  ���bWriteToStdoutΪtrue, ��Ὣ��־��Ϣͬʱд��stdout����־�ļ��У�����ֻд����־�ļ���
//					if bWriteToStdout is true, call write log funs will write into  file and stdout, 
//					Otherwise only write into file.
// return value:    return positive number if success, otherwise return 0.
LOG_API _FILE_HANDLE OpenNewLogFile(const char* szName, bool bWriteToStdout);

// �����־
// parameter��
// wColor: ��log_config.h(see log_config.h enum FontColor)
// hLogFile: the file handle that function OpenNewLogFile return. it will write into stdout when hLogFIle is STDOUT_FILE_HANDLE,
// szFormat: a format string that specifies how subsequent arguments
// write the log info 
LOG_API bool WriteLog(FontColor wColor, _FILE_HANDLE hLogFile, const char* szFormat, ...);

// �����־�Լ����ö�ջ
// write the log info and call stack 
LOG_API bool WriteCallStackLog(FontColor wColor, _FILE_HANDLE hLogFile, const char* szFormat, ...);

// flush log file 
LOG_API void FlushLogFile(_FILE_HANDLE hLogFile);

// �ر���־�ļ�
// close the log file
LOG_API void CloseLogFile(_FILE_HANDLE hLogFile);
