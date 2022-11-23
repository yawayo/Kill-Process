//---------------------------------------------------------------------------

#pragma hdrstop

#include "ThreadClass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

ThreadClass::ThreadClass()
{
	m_hThread = CreateEvent(NULL, false, false, L"");
	m_hEvent = NULL;
}
void ThreadClass::start_thread(unsigned (__stdcall * __start)(void *), void*__arg)
{
	m_hThread = (HANDLE)_beginthreadex((void*)NULL, (unsigned)NULL, __start, __arg, (unsigned)NULL, (unsigned*)NULL);
}
