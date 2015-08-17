//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   19:52
//	File Name:	System.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	����linux��windowsͨ�õ�ͷ�ļ�
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <list>
#include <map>
#include <vector>
#include <assert.h>


#ifdef _WIN32
#include <windows.h>
#include <time.h>
#endif	// _WIN32

#ifdef linux
#include <stdarg.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>

#endif // linux