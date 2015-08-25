//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-25   11:04
//	File Name:	deque.h
//	Author:		Eric(ɳӥ)
//	PS:			�������˵�����󣬴���������߼������⣬������⣬������ҡ�лл��
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------

template<class T>
class deque
{
public:
	deque();
	~deque();

public:
	// ��ȡ��һ��Ԫ��
	// get the next element
	T*	GetNext();
	// ��ȡǰһ��Ԫ��
	// get the previous element
	T*	GetPrev();

	// ���һ��Ԫ��
	// add new element
	void Add(T* pNew);

	// ɾ��һ��Ԫ��
	// ɾ����ǰԪ��
	// delete current element
	void Remove();
	// ɾ��ָ��Ԫ��
	// delete specific element pDel
	void Remove(T* pDel);

private:
	T*	m_pNext;
	T*	m_pPrev;
};