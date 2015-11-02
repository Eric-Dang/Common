//-------------------------------------------------------------------------------------------------
//	Created:	2015-9-25   17:02
//	File Name:	thread.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef linux
#include <pthread.h>
#endif // linux

#include "basetype.h"
#include "common_sys_fun.h"
//-------------------------------------------------------------------------------------------------
// ͳһ��������
#ifdef linux
typedef pthread_t	_THREAD_HANDLE;
typedef void*		_THREAD_START_FUN;
#endif // linux

#ifdef _WIN32
typedef HANDLE					_THREAD_HANDLE;
typedef LPTHREAD_START_ROUTINE	_THREAD_START_FUN;
#endif //_WIN32
//-------------------------------------------------------------------------------------------------
/*
* ����pthread��joinable��detached����˵��
* joinable����Ϊ���߳̿��Ա������̻߳��߽��̹رգ��߳���Դ�Ľ�������ͨ��pthread_join�����ա�
* detached���Բ���ͨ��pthread_join����ֹ�̣߳��߳̽���ʱ���߳���Դϵͳ���Զ����ա�ʹ����������ǳ�����Ҫ�����̵߳��˳�״̬��
*		  �޷�������Ϊjoinable����
*/
class CThrea
{
public:
	/*
	* pFun		 : �߳����к���
	* nStackSize : �߳�����Ķ�ջ��С��0��ʾ����Ĵ�СΪϵͳ���õ�Ĭ�ϴ�С
	* 			   linux�鿴���� ulimit -s	
	* ��ע:	1. join detach����ֻ��linux֧��
	*       2. linuxϵͳ�̴߳���Ĭ��Ϊjoinable����
	*/
	CThrea(_THREAD_START_FUN pFun, int nStackSize = 0, bool bIsJoin = true);
	~CThrea();

public:
	// ���������߳�
	bool Run();
	/*
	* ��joinable��������Ϊdetach����
	*/
	bool SetDetached();

	/*
	* �ر��߳�
	*/
	bool Join();

private:
	bool m_bHasRun;	// �߳��Ƿ��Ѿ�����
	bool m_bIsJoin;	// �߳�����

	// �߳̾��
	_THREAD_HANDLE m_Thread;
};
