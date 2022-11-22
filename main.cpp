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

	const wchar_t *strExeName = L"Project1.exe"; //����͸� �ϰ��� �ϴ� �������� �̸�

	HANDLE hSnapShot;
	while(1)
	{
		hSnapShot=CreateToolhelp32Snapshot (TH32CS_SNAPALL,NULL); //Ư�� ���μ���(��,���μ���,���,������ ����) �� ���� ������ ������ ���´�.
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

					HWND HWnd = ::FindWindow(NULL,_T("Form1")); //ĸ�Ǹ��� test �� ������ �ڵ��� ���´�
					DWORD pid, tid;
					HANDLE hnd;

					//10�ʾȿ� ������ �ִ����� �Ǵ��� ����.
					if (SendMessageTimeout(HWnd,NULL,NULL,NULL,SMTO_NORMAL,3000,&dw))
					{
						continue; //���������� ������ �ִ� ���
					}
					else
					{
						TCHAR* szErrMsg = NULL;
						FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&szErrMsg, 0, NULL); //�߻��� ���� ������ ���´�.
						LocalFree(szErrMsg);

						tid = ::GetWindowThreadProcessId(HWnd, &pid);
						hnd = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
						::TerminateProcess(hnd,0); //�ش� ���μ����� ������ ������ ������.
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