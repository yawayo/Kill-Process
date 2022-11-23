//---------------------------------------------------------------------------

#ifndef ThreadClassH
#define ThreadClassH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <process.h>

typedef unsigned(__stdcall* PTHREAD_START) (void*);
class ThreadClass
{
private:
public:
	ThreadClass();
	HANDLE m_hThread;
	HANDLE m_hEvent;

	void start_thread(unsigned (__stdcall * __start)(void *), void*__arg);
	static void WINAPI CallThreadFunc(LPVOID IpParam);
};
#endif
