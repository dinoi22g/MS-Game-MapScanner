//--------------------------------------------------------------------------
#include <windows.h>
//#include <time.h>
//#include <string>
#include <vcl.h>
//---------------------------------------------------------------------------

//**************************************************************************
//get maplestory process a data.
HWND hWnd;
DWORD pID ;
HANDLE hProcess;
bool GetMapleStoryByWindowName(){
   hWnd = ::FindWindowA(NULL,"MapleStory");
   ::GetWindowThreadProcessId(hWnd,&pID);
   hProcess = ::OpenProcess(PROCESS_ALL_ACCESS,0,pID);
   return hWnd;
}

bool GetMapleStoryDelhProcessByWindowName(){
   hWnd = ::FindWindowA(NULL,"MapleStory");
   ::GetWindowThreadProcessId(hWnd,&pID);
   return hWnd;
}
//**************************************************************************
bool MyPostMessage(unsigned int SendKey)
{
PostMessageA(hWnd, WM_KEYDOWN,SendKey, (MapVirtualKey(SendKey, 0)) << 16);
PostMessageA(hWnd, WM_KEYUP,SendKey, (MapVirtualKey(SendKey, 0)) << 16);
return true;
}

int ReadLong(HANDLE hprocess,DWORD lpAddress){
	int value;
	::ReadProcessMemory(hprocess, (void*)lpAddress, &value, sizeof(value),0);
	return value;
}

int ReadPointer(DWORD lpAddress,DWORD lpOffest){
	return ReadLong(hProcess,ReadLong(hProcess,lpAddress)+lpOffest);
}

int WriteMemory(int lpAddress,int lpBuffer){
 //	return ::WriteProcessMemory()
   //	return ::WriteProcessMemory(hProcess, (LPVOID)lpAddress,&lpBuffer,sizeof(lpBuffer),false);
}
/*
	Public Function WriteMemory(ByVal hprocess As Integer, ByVal lpAddress As Long, ByVal lpBuffer As Long, ByVal lpSize As Long) As Long
        WriteMemory = WriteProcessMemoryAPI(hprocess, lpAddress, lpBuffer, lpSize, False)
    End Function
    Public Function WritePointer(ByVal hprocess As Integer, ByVal lpAddress As Long, ByVal lpOffset As Long, ByVal lpValue As Long) As Long
        WritePointer = WriteMemory(hprocess, ReadLong(hprocess, lpAddress) + lpOffset, lpValue, 4)
	End Function
*/
