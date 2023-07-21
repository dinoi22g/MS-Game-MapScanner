//---------------------------------------------------------------------------

#ifndef CommonFunctionH
#define CommonFunctionH
//---------------------------------------------------------------------------

#include <Windows.h>
#include <Winternl.h>

#define ISNOTDECIMAL(x) ((double)x==(int)x)
#define AESSIZE(x) ((x+15)/16)*16

// ---------------------------------------------------------------------------
void* __memset(void *ptr, int value, size_t num);
// ---------------------------------------------------------------------------
void* __memcpy(void *dst, const void *src, unsigned int len);
// ---------------------------------------------------------------------------
void __memzero(void *ptr, size_t num);
// ---------------------------------------------------------------------------
char* __strcpy(register char *to, register const char *from);
// ---------------------------------------------------------------------------
wchar_t* __wcscpy(wchar_t* dst, const wchar_t* src);
// ---------------------------------------------------------------------------
size_t __strlen(const char *str);
// ---------------------------------------------------------------------------
size_t __wcslen(const wchar_t *s);
// ---------------------------------------------------------------------------
char* __strcat(char * s, const char * append);
// ---------------------------------------------------------------------------
wchar_t* __wcscat(wchar_t *s1, const wchar_t *s2);
// ---------------------------------------------------------------------------
char* __strncat(char * dst, const char * src, size_t n);
// ---------------------------------------------------------------------------
wchar_t* __wcsncat(wchar_t * dst, const wchar_t * src, size_t n);
// ---------------------------------------------------------------------------
int __strcmp(const char *pStr1, const char *pStr2);
// ---------------------------------------------------------------------------
int __wcscmp(const wchar_t* cs, const wchar_t * ct);
// ---------------------------------------------------------------------------
int __stricmp(const char *s1, const char *s2);
// ---------------------------------------------------------------------------
int __wcsicmp(const wchar_t* cs, const wchar_t * ct);
// ---------------------------------------------------------------------------
char* __strupr(char* a);
// ---------------------------------------------------------------------------
wchar_t *__wcsupr(wchar_t *x);
// ---------------------------------------------------------------------------
int __strncmp(register const char *s1, register const char *s2,
	register size_t n);
// ---------------------------------------------------------------------------
int __cdecl __wcsncmp(const wchar_t * first, const wchar_t * last,
	size_t count);
// ---------------------------------------------------------------------------
char * __cdecl __strstr(const char * src, const char * what);
// ---------------------------------------------------------------------------
wchar_t * __cdecl __wcsstr(const wchar_t * src, const wchar_t * what);
// ---------------------------------------------------------------------------
char* __strchr(const char *s, int ch);
// ---------------------------------------------------------------------------
wchar_t * __cdecl __wcschr(const wchar_t * string, wchar_t ch);
// ---------------------------------------------------------------------------
char* __substr(char *string, int position, int length);
// ---------------------------------------------------------------------------
unsigned long __strtoul(const char* nptr, char ** endptr, int base);
// ---------------------------------------------------------------------------
unsigned long int __strtoul2(const char* string, char ** endPtr, int base);
// ---------------------------------------------------------------------------
PTEB __stdcall __NtCurrentTeb();
// ---------------------------------------------------------------------------
PPEB __stdcall __NtCurrentPeb();
// ---------------------------------------------------------------------------
DWORD __stdcall __GetLastError();
// ---------------------------------------------------------------------------
HANDLE __stdcall __GetCurrentProcess();
// ---------------------------------------------------------------------------
DWORD __stdcall __GetCurrentThreadId();
// ---------------------------------------------------------------------------
HANDLE __stdcall __GetCurrentThread();
// ---------------------------------------------------------------------------
void* __GetProcAddress(HMODULE hModule, LPCSTR lpProcName);

// ---------------------------------------------------------------------------
typedef struct _PEB_LDR_DATA_ {
	ULONG Length;
	BOOLEAN Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA_, *PPEB_LDR_DATA_;

typedef struct _LDR_MODULE {
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	SHORT LoadCount;
	SHORT TlsIndex;
	LIST_ENTRY HashTableEntry;
	ULONG TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

HMODULE __stdcall __GetModuleHandleW(wchar_t* lpModuleName);
wchar_t* __GetModuleFullNameW(wchar_t* lpModuleName);
wchar_t* __GetImagePathName();
// ---------------------------------------------------------------------------
const wchar_t* __GetExeName();
// ---------------------------------------------------------------------------
typedef LONG(WINAPI *LPNtQueryInformationProcess)(HANDLE ProcessHandle,
	ULONG ProcessInformationClass, PVOID ProcessInformation,
	ULONG ProcessInformationLength, PULONG ReturnLength);
ULONG_PTR GetParentProcessId();
// ---------------------------------------------------------------------------
typedef NTSTATUS(NTAPI *LPZwProtectVirtualMemory)(HANDLE ProcessHandle,
	PVOID *BaseAddress, PULONG ProtectSize, ULONG NewProtect,
	PULONG OldProtect);

NTSTATUS NTAPI __ZwProtectVirtualMemory(HANDLE ProcessHandle,
	PVOID *BaseAddress, PULONG ProtectSize, ULONG NewProtect,
	PULONG OldProtect);
// ---------------------------------------------------------------------------
BOOL WINAPI __VirtualProtectEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize,
	DWORD flNewProtect, PDWORD lpflOldProtect);
// ---------------------------------------------------------------------------
typedef BOOL(WINAPI * LPCreateProcessInternalW)(HANDLE, LPCWSTR, LPWSTR,
	LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCWSTR,
	LPSTARTUPINFOW, LPPROCESS_INFORMATION, PHANDLE);
extern LPCreateProcessInternalW __CreateProcessInternalW;

/*
 __declspec(naked) BOOL WINAPI __CreateProcessInternalW_SkipHook(
 HANDLE hToken,
 LPCWSTR lpApplicationName,
 LPWSTR lpCommandLine,
 LPSECURITY_ATTRIBUTES lpProcessAttributes,
 LPSECURITY_ATTRIBUTES lpThreadAttributes,
 BOOL bInheritHandles,
 DWORD dwCreationFlags,
 LPVOID lpEnvironment,
 LPCWSTR lpCurrentDirectory,
 LPSTARTUPINFOW lpStartupInfo,
 LPPROCESS_INFORMATION lpProcessInformation,
 PHANDLE hNewToken
 )
 {
 __asm
 {
 push ebp
 mov ebp,esp
 mov eax,ds:__CreateProcessInternalW
 add eax,0x05
 jmp eax
 }
 }
 */

BOOL WINAPI __CreateProcessW(LPCWSTR lpApplicationName,
							LPWSTR lpCommandLine,
							LPSECURITY_ATTRIBUTES lpProcessAttributes,
							LPSECURITY_ATTRIBUTES lpThreadAttributes,
							BOOL bInheritHandles,
							DWORD dwCreationFlags,
							LPVOID lpEnvironment,
							LPCWSTR lpCurrentDirectory,
							LPSTARTUPINFOW lpStartupInfo,
							LPPROCESS_INFORMATION lpProcessInformation);
// ---------------------------------------------------------------------------
/*
 void DbgPrint( const char* format, ... ) {
 char* output = (char*)calloc(1024, 1);
 va_list args;
 va_start( args, format );
 vsprintf( output, format, args );
 va_end( args );
 OutputDebugStringA(output);
 free(output);
 }
 */

DWORD IATHook(wchar_t* NameOfModuletoHook, char* funcName, DWORD newFunc);
// ---------------------------------------------------------------------------
DWORD EATHook(wchar_t* NameOfModuletoHook, char* funcName, DWORD newFunc);
// ---------------------------------------------------------------------------
void __cdecl WriteMemory(unsigned long ulAddress, unsigned char ucAmount, ...);

// ---------------------------------------------------------------------------
typedef struct _SimpleString {
	char str[400];
	int length;
} SimpleString;

int* des_createKeys(char* key);
SimpleString* des(char* key, SimpleString* in, bool encrypt, int mode,
	char* iv);

// ---------------------------------------------------------------------------
class DesStream {
public:
	SimpleString* Data;

	DesStream(char* src, size_t length);
	DesStream();
	~DesStream();
	char* EncryStr(char* key);
	char* EncryStrCBC(char* key, char* iv);
	char* DecryStr(char* key);
	char* DecryStrCBC(char* key, char* iv);
	char* SubStr(int position, int length, char* buffer);
	char* SubStrData(int position);
};

char* StrToHex(unsigned char* buffer, unsigned int length, char* out);

// ---------------------------------------------------------------
typedef struct NODE {
	NODE* _1;
	NODE* _2;
} node;

class TBinTree {
public:
	node* head;

	TBinTree() {
		this->count = 0;
		this->depth = 10;
		head = new node;
		Grow(head);
	}

	TBinTree(int _depth) {
		this->count = 0;
		this->depth = _depth;
		head = new node;
		Grow(head);
	}

	void Grow(node* n) {
		if (count < depth) {
			count++;
			n->_1 = new node;
			n->_2 = new node;
			Grow(n->_1);
			Grow(n->_2);
			count--;
		}
		else
			n->_1 = n->_2 = NULL;
	}

	~TBinTree() {
		this->count = 0;
		Delete(head);
		delete head;
	}

	void Delete(node* n) {
		if (count < depth) {
			count++;
			Delete(n->_1);
			Delete(n->_2);
			delete n->_1;
			delete n->_2;
			count--;
		}
	}

private:
	int count;
	int depth;
};
// ---------------------------------------------------------------
#endif
