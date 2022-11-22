//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

/*Test*/	if (!handle)
/*Test*/	{
/*Test*/		AllocConsole();
/*Test*/		handle = GetStdHandle(STD_OUTPUT_HANDLE);
/*Test*/	}

	const wchar_t *strExeName = L"Project1.exe"; //모니터링 하고자 하는 실행파일 이름

	HANDLE hSnapShot;
	while(1)
	{
		hSnapShot=CreateToolhelp32Snapshot (TH32CS_SNAPALL,NULL); //특정 프로세스(힙,프로세스,모듈,쓰레드 포함) 에 대한 스냅샷 정보를 얻어온다.
		PROCESSENTRY32 pEntry;
		pEntry.dwSize =sizeof(pEntry);

		if(Process32First (hSnapShot,&pEntry))
		{
			do
			{
//				String text = String(pEntry.szExeFile) + "\n";
//				WriteConsole(handle, text.c_str(), text.Length(), 0, 0);

				if((_wcsicmp(pEntry.szExeFile, strExeName) == 0 ) &&  pEntry.cntThreads >= 1)
				{
					DWORD dw = 0;

					HWND HWnd = ::FindWindow(NULL,_T("Form1")); //캡션명이 test 인 윈도우 핸들을 얻어온다
					DWORD pid, tid;
					HANDLE hnd;

					//10초안에 응답이 있는지를 판단해 본다.
					if (SendMessageTimeout(HWnd,NULL,NULL,NULL,SMTO_NORMAL,3000,&dw))
					{
						continue; //정상적으로 응답이 있는 경우
					}
					else
					{
						TCHAR* szErrMsg = NULL;
						FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&szErrMsg, 0, NULL); //발생한 에러 정보를 얻어온다.
						LocalFree(szErrMsg);

						tid = ::GetWindowThreadProcessId(HWnd, &pid);
						hnd = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
						::TerminateProcess(hnd,0); //해당 프로세스를 강제로 종료해 버린다.
						::CloseHandle(hnd);

						break;
					}
				}
			}
			while(Process32Next(hSnapShot,&pEntry));
		}
	}
	CloseHandle (hSnapShot);
}
//---------------------------------------------------------------------------
