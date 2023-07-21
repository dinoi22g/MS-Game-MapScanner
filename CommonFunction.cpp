//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonFunction.h"
//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Winternl.h>
#include <limits.h>
//---------------------------------------------------------------------------
void* __memset(void *ptr, int value, size_t num)
{
	unsigned char* p=(unsigned char*)ptr;
	while(num--)
		*p++ = (unsigned char)value;
	return ptr;
}
//---------------------------------------------------------------------------
void* __memcpy( void *dst, const void *src, unsigned int len )
{
   register char *d;
   register char *s;

   if (len == 0)
	  return dst;

   if ( dst > src ) {
      d = (char *)dst + len - 1;
      s = (char *)src + len - 1;
	  while ( len >= 4 ) {
         *d-- = *s--;
         *d-- = *s--;
         *d-- = *s--;
         *d-- = *s--;
         len -= 4;
      }
      while ( len-- ) {
         *d-- = *s--;
      }
   } else if ( dst < src ) {
      d = (char *)dst;
	  s = (char *)src;
	  while ( len >= 4 ) {
		 *d++ = *s++;
		 *d++ = *s++;
		 *d++ = *s++;
		 *d++ = *s++;
		 len -= 4;
	  }
	  while ( len-- ) {
		 *d++ = *s++;
	  }
   }
   return dst;
}
//---------------------------------------------------------------------------
void __memzero(void *ptr, size_t num)
{
	union { void *vp; unsigned long *ulp; unsigned char *ucp; } u;
	int i;

	u.vp = ptr;

	for (i = num >> 5; i > 0; i--) {
		*u.ulp++ = 0;
		*u.ulp++ = 0;
		*u.ulp++ = 0;
		*u.ulp++ = 0;
		*u.ulp++ = 0;
		*u.ulp++ = 0;
		*u.ulp++ = 0;
		*u.ulp++ = 0;
	}

	if (num & 1 << 4) {
		*u.ulp++ = 0;
		*u.ulp++ = 0;
		*u.ulp++ = 0;
		*u.ulp++ = 0;
	}

	if (num & 1 << 3) {
		*u.ulp++ = 0;
		*u.ulp++ = 0;
	}

	if (num & 1 << 2)
		*u.ulp++ = 0;

	if (num & 1 << 1) {
		*u.ucp++ = 0;
		*u.ucp++ = 0;
	}

	if (num & 1)
		*u.ucp++ = 0;
}
//---------------------------------------------------------------------------
char *
__strcpy(register char *to, register const char *from)
{
	char *save = to;

	for (; (*to = *from) != 0; ++from, ++to);
	return(save);
}
//---------------------------------------------------------------------------
wchar_t *
__wcscpy(wchar_t* dst, const wchar_t* src)
{
	wchar_t *cp;

	cp = dst;
	while ((*cp++ = *src++) != L'\0')
		;

	return (dst);
}
//---------------------------------------------------------------------------
size_t
__strlen(const char *str)
{
	const char *s;

	for (s = str; *s; ++s);
	return(s - str);
}
//---------------------------------------------------------------------------
size_t
__wcslen(const wchar_t *s)
{
	const wchar_t *p;

	p = s;
	while (*p)
		p++;

	return p - s;
}
//---------------------------------------------------------------------------
char *
__strcat(char * s, const char * append)
{
	char *save = s;

	for (; *s; ++s);
	while ((*s++ = *append++));
	return(save);
}
//---------------------------------------------------------------------------
wchar_t *
__wcscat(wchar_t *s1, const wchar_t *s2)
{
	wchar_t *cp;

	cp = s1;
	while (*cp != L'\0')
		cp++;
	while ((*cp++ = *s2++) != L'\0')
		;

	return (s1);
}
//---------------------------------------------------------------------------
char *
__strncat(char * dst, const char * src, size_t n)
{
	if (n != 0) {
		char *d = dst;
		const char *s = src;

		while (*d != 0)
			d++;
		do {
			if ((*d = *s++) == 0)
				break;
			d++;
		} while (--n != 0);
		*d = 0;
	}
	return (dst);
}
//---------------------------------------------------------------------------
wchar_t *
__wcsncat(wchar_t * dst, const wchar_t * src, size_t n)
{
	wchar_t *p;
	wchar_t *q;
	const wchar_t *r;

	p = dst;
	while (*p)
		p++;
	q = p;
	r = src;
	while (*r && n) {
		*q++ = *r++;
		n--;
	}
	*q = '\0';
	return dst;
}
//---------------------------------------------------------------------------
int __strcmp(const char *pStr1, const char *pStr2)
{
	char c1, c2;
	int v;

	do {
		c1 = *pStr1++;
		c2 = *pStr2++;
		v = (int)c1 - (int)c2;
	} while ((v == 0) && (c1 != '\0'));
	return v;
}
//---------------------------------------------------------------------------
int __wcscmp(const wchar_t* cs,const wchar_t * ct)
{
  while (*cs == *ct)
  {
	if (*cs == 0)
	  return 0;
	cs++;
	ct++;
  }
  return *cs - *ct;
}
//---------------------------------------------------------------------------
int __stricmp(const char *s1, const char *s2)
{
  while (toupper(*s1) == toupper(*s2))
  {
    if (*s1 == 0)
      return 0;
    s1++;
    s2++;
  }
  return toupper(*(unsigned const char *)s1) - toupper(*(unsigned const char *)(s2));
}
//---------------------------------------------------------------------------
int __wcsicmp(const wchar_t* cs,const wchar_t * ct)
{
	while (towlower(*cs) == towlower(*ct))
  	{
    		if (*cs == 0)
      			return 0;
    		cs++;
    		ct++;
  	}
  	return towlower(*cs) - towlower(*ct);

}
//---------------------------------------------------------------------------
char *
__strupr (char* a)
{
  char *ret = a;

  while (*a != '\0')
    {
      if (islower (*a))
	*a = toupper (*a);
      ++a;
    }

  return ret;
}
//---------------------------------------------------------------------------
wchar_t *__wcsupr(wchar_t *x)
{
	wchar_t  *y=x;

	while (*y) {
		*y=towupper(*y);
		y++;
	}
	return x;
}
//---------------------------------------------------------------------------
int __strncmp(
	register const char *s1,
	register const char *s2,
	register size_t n
	)
{

	if (n == 0)
		return (0);
	do {
		if (*s1 != *s2++)
			return (*(const unsigned char *)s1 -
				*(const unsigned char *)(s2 - 1));
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return (0);
}
//---------------------------------------------------------------------------
int __cdecl __wcsncmp (
        const wchar_t * first,
        const wchar_t * last,
        size_t count
        )
{
        if (!count)
                return(0);

        while (--count && *first && *first == *last)
        {
                first++;
                last++;
        }

        return((int)(*first - *last));
}
//---------------------------------------------------------------------------
char * __cdecl __strstr (
        const char * src,
        const char * what
        )
{
        char *cp = (char *) src;
        char *s1, *s2;

        while (*cp)
        {
                s1 = cp;
                s2 = (char *) what;

                while ( *s1 && *s2 && !(*s1-*s2) )
                        s1++, s2++;

                if (!*s2)
                        return(cp);

                cp++;
        }

        return(NULL);
}
//---------------------------------------------------------------------------
wchar_t * __cdecl __wcsstr (
        const wchar_t * src,
        const wchar_t * what
        )
{
        wchar_t *cp = (wchar_t *) src;
        wchar_t *s1, *s2;

        while (*cp)
        {
                s1 = cp;
                s2 = (wchar_t *) what;

                while ( *s1 && *s2 && !(*s1-*s2) )
                        s1++, s2++;

                if (!*s2)
                        return(cp);

                cp++;
        }

        return(NULL);
}
//---------------------------------------------------------------------------
char *
__strchr(const char *s, int ch)
{
	 /* scan from left to right */
	 while (*s) {
			 /* if we hit it, return it */
			 if (*s==ch) {
					 return (char *)s;
			 }
			 s++;
	 }

	 /* if we were looking for the 0, return that */
	 if (*s==ch) {
			 return (char *)s;
	 }

	 /* didn't find it */
	 return NULL;
}
//---------------------------------------------------------------------------
wchar_t * __cdecl __wcschr (
        const wchar_t * string,
        wchar_t ch
        )
{
        while (*string && *string != (wchar_t)ch)
                string++;

        if (*string == (wchar_t)ch)
                return((wchar_t *)string);
        return(NULL);
}
//---------------------------------------------------------------------------
char* __substr(char *string, int position, int length)
{
   char *pointer;
   int c;

   pointer = new char[length+1];

   if (pointer == NULL)
		return NULL;

   for (c = 0 ; c < position ; c++)
      string++;

   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *string;
	  string++;
   }

   *(pointer+c) = '\0';

   return pointer;
}
//---------------------------------------------------------------------------
/*
 * Convert a string to an unsigned long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
unsigned long
__strtoul(const char* nptr,char ** endptr,int base)
{
	const char *s = nptr;
	unsigned long acc;
	unsigned char c;
	unsigned long cutoff;
	int neg = 0, any, cutlim;

	/*
	 * See strtol for comments as to the logic used.
	 */
	do {
		c = *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
	cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;
	for (acc = 0, any = 0;; c = *s++) {
		if (!isascii(c))
			break;
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = ULONG_MAX;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
		*((const char **)endptr) = any ? s - 1 : nptr;
	return (acc);
}
//---------------------------------------------------------------------------
/*
 * The table below is used to convert from ASCII digits to a
 * numerical equivalent.  It maps from '0' through 'z' to integers
 * (100 for non-digit characters).
 */

static char cvtIn[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,		/* '0' - '9' */
    100, 100, 100, 100, 100, 100, 100,		/* punctuation */
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,	/* 'A' - 'Z' */
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35,
    100, 100, 100, 100, 100, 100,		/* punctuation */
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,	/* 'a' - 'z' */
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35};

/*
 *----------------------------------------------------------------------
 *
 * strtoul --
 *
 *	Convert an ASCII string into an integer.
 *
 * Results:
 *	The return value is the integer equivalent of string.  If endPtr
 *	is non-NULL, then *endPtr is filled in with the character
 *	after the last one that was part of the integer.  If string
 *	doesn't contain a valid integer value, then zero is returned
 *	and *endPtr is set to string.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

unsigned long int
__strtoul2(const char* string,char ** endPtr,int base)
	/*const char *string;		String of ASCII digits, possibly
							  * preceded by white space.  For bases
							  * greater than 10, either lower- or
							  * upper-case digits may be used.

	char **endPtr;		 Where to store address of terminating
				 * character, or NULL.
	int base;			/* Base for conversion.  Must be less
				 * than 37.  If 0, then the base is chosen
				 * from the leading characters of string:
				 * "0x" means hex, "0" means octal, anything
				 * else means decimal.
				 */
{
    register CONST char *p;
    register unsigned long int result = 0;
    register unsigned digit;
    int anyDigits = 0;
    int negative=0;
    int overflow=0;

    /*
     * Skip any leading blanks.
     */

	p = string;
    while (isspace(UCHAR(*p))) {
	p += 1;
    }
    if (*p == '-') {
        negative = 1;
        p += 1;
    } else {
        if (*p == '+') {
            p += 1;
        }
    }

    /*
     * If no base was provided, pick one from the leading characters
     * of the string.
     */

    if (base == 0)
    {
	if (*p == '0') {
	    p += 1;
	    if ((*p == 'x') || (*p == 'X')) {
		p += 1;
		base = 16;
	    } else {

		/*
		 * Must set anyDigits here, otherwise "0" produces a
		 * "no digits" error.
		 */

		anyDigits = 1;
		base = 8;
	    }
	}
	else base = 10;
    } else if (base == 16) {

	/*
	 * Skip a leading "0x" from hex numbers.
	 */

	if ((p[0] == '0') && ((p[1] == 'x') || (p[1] == 'X'))) {
	    p += 2;
	}
    }

    /*
     * Sorry this code is so messy, but speed seems important.  Do
     * different things for base 8, 10, 16, and other.
     */

    if (base == 8) {
	unsigned long maxres = ULONG_MAX >> 3;
	for ( ; ; p += 1) {
	    digit = *p - '0';
	    if (digit > 7) {
		break;
	    }
	    if (result > maxres) { overflow = 1; }
	    result = (result << 3);
	    if (digit > (ULONG_MAX - result)) { overflow = 1; }
	    result += digit;
	    anyDigits = 1;
	}
    } else if (base == 10) {
	unsigned long maxres = ULONG_MAX / 10;
	for ( ; ; p += 1) {
	    digit = *p - '0';
	    if (digit > 9) {
		break;
	    }
	    if (result > maxres) { overflow = 1; }
	    result *= 10;
	    if (digit > (ULONG_MAX - result)) { overflow = 1; }
	    result += digit;
	    anyDigits = 1;
	}
    } else if (base == 16) {
	unsigned long maxres = ULONG_MAX >> 4;
	for ( ; ; p += 1) {
	    digit = *p - '0';
	    if (digit > ('z' - '0')) {
		break;
	    }
	    digit = cvtIn[digit];
	    if (digit > 15) {
		break;
	    }
	    if (result > maxres) { overflow = 1; }
	    result = (result << 4);
	    if (digit > (ULONG_MAX - result)) { overflow = 1; }
	    result += digit;
	    anyDigits = 1;
	}
    } else if ( base >= 2 && base <= 36 ) {
	unsigned long maxres = ULONG_MAX / base;
	for ( ; ; p += 1) {
	    digit = *p - '0';
	    if (digit > ('z' - '0')) {
		break;
	    }
	    digit = cvtIn[digit];
	    if (digit >= ( (unsigned) base )) {
		break;
	    }
	    if (result > maxres) { overflow = 1; }
	    result *= base;
	    if (digit > (ULONG_MAX - result)) { overflow = 1; }
	    result += digit;
	    anyDigits = 1;
	}
    }

    /*
     * See if there were any digits at all.
     */

    if (!anyDigits) {
	p = string;
    }

	if (endPtr != 0) {
	/* unsafe, but required by the strtoul prototype */
	*endPtr = (char *) p;
    }

    if (overflow) {
	return ULONG_MAX;
    }
    if (negative) {
	return -result;
    }
	return result;
}
//---------------------------------------------------------------------------
PTEB __stdcall __NtCurrentTeb()
{
	PTEB Result;
	__asm mov eax,fs:[0x18]
	__asm mov Result,eax
	return Result;
}
//---------------------------------------------------------------------------
PPEB __stdcall __NtCurrentPeb()
{
	PPEB Result;
	__asm mov eax,fs:[0x30]
	__asm mov Result,eax
	return Result;
}
//---------------------------------------------------------------------------
DWORD __stdcall __GetLastError()
{
	DWORD Result;
	__asm mov eax,fs:[0x34]
	__asm mov Result,eax
	return Result;
}
//---------------------------------------------------------------------------
HANDLE __stdcall __GetCurrentProcess()
{
	return (HANDLE)0xFFFFFFFF;
}
//---------------------------------------------------------------------------
DWORD __stdcall __GetCurrentThreadId()
{
	DWORD Result;
	__asm mov eax,fs:[0x18]
	__asm mov eax,[eax+0x24]
	__asm mov Result,eax
	return Result;
}
//---------------------------------------------------------------------------
HANDLE __stdcall __GetCurrentThread()
{
	return (HANDLE)0xFFFFFFFE;
}
//---------------------------------------------------------------------------
void* __GetProcAddress(
	HMODULE hModule,    // handle to DLL module
	LPCSTR lpProcName   // function name
	)
{
	int i=0;
	char *pRet = NULL;
	PIMAGE_DOS_HEADER pImageDosHeader = NULL;
	PIMAGE_NT_HEADERS pImageNtHeader = NULL;
	PIMAGE_EXPORT_DIRECTORY pImageExportDirectory = NULL;

	pImageDosHeader=(PIMAGE_DOS_HEADER)hModule;
	pImageNtHeader=(PIMAGE_NT_HEADERS)((DWORD)hModule+pImageDosHeader->e_lfanew);
	pImageExportDirectory=(PIMAGE_EXPORT_DIRECTORY)((DWORD)hModule+pImageNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	DWORD dwExportRVA = pImageNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	DWORD dwExportSize = pImageNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

	DWORD *pAddressOfFunction = (DWORD*)(pImageExportDirectory->AddressOfFunctions + (DWORD)hModule);
	DWORD *pAddressOfNames = (DWORD*)(pImageExportDirectory->AddressOfNames + (DWORD)hModule);
	DWORD dwNumberOfNames = (DWORD)(pImageExportDirectory->NumberOfNames);
	DWORD dwBase = (DWORD)(pImageExportDirectory->Base);

	WORD *pAddressOfNameOrdinals = (WORD*)(pImageExportDirectory->AddressOfNameOrdinals + (DWORD)hModule);

	//這個是查一下是按照什麼方式（函數名稱or函數序號）來查函數地址的
	DWORD dwName = (DWORD)lpProcName;
	if ((dwName & 0xFFFF0000) == 0)
	{
		goto xuhao;
	}

	for (i=0; i<(int)dwNumberOfNames; i++)
	{
		char *strFunction = (char *)(pAddressOfNames[i] + (DWORD)hModule);
		if (__strcmp(strFunction, (char *)lpProcName) == 0)
		{
			pRet = (char *)(pAddressOfFunction[pAddressOfNameOrdinals[i]] + (DWORD)hModule);
			goto _exit11;
		}
	}
	//這個是通過以序號的方式來查函數地址的
xuhao:
	if (dwName < dwBase || dwName > dwBase + pImageExportDirectory->NumberOfFunctions - 1)
	{
		return 0;
	}
	pRet = (char *)(pAddressOfFunction[dwName - dwBase] + (DWORD)hModule);
_exit11:
	//判斷得到的地址有沒有越界
	if ((DWORD)pRet<dwExportRVA+(DWORD)hModule || (DWORD)pRet > dwExportRVA+ (DWORD)hModule + dwExportSize)
	{
		return (void*)pRet;
	}
	char pTempDll[100] = {0};
	char pTempFuction[100] = {0};
	__strcpy(pTempDll, pRet);
	char *p = __strchr(pTempDll, '.');
	if (!p)
	{
		return (void*)pRet;
	}
	*p = 0;
	__strcpy(pTempFuction, p+1);
	__strcat(pTempDll, ".dll");
	HMODULE h = LoadLibraryA(pTempDll);
	if (h == NULL)
	{
		return (void*)pRet;
	}
	return __GetProcAddress(h, pTempFuction);
}
//---------------------------------------------------------------------------
HMODULE __stdcall __GetModuleHandleW(wchar_t* lpModuleName)
{
	HMODULE Result = NULL;
	wchar_t CurModuleName[300];
	wchar_t ModuleName[300];
	PPEB CurPEB = __NtCurrentPeb();
	PPEB_LDR_DATA_ CurLdr = (PPEB_LDR_DATA_)CurPEB->Ldr;
	PLDR_MODULE CurDll = (PLDR_MODULE)CurLdr->InLoadOrderModuleList.Flink;
	if(!lpModuleName)
		Result = (HMODULE)CurDll->BaseAddress;
	else
	{
		__wcscpy(ModuleName, lpModuleName);
		__wcsupr(ModuleName);
		while (CurDll->BaseAddress != NULL)
		{
			__wcscpy(CurModuleName, CurDll->BaseDllName.Buffer);
			__wcsupr(CurModuleName);
			if (__wcscmp(ModuleName, CurModuleName) == 0) {
				Result = (HMODULE)CurDll->BaseAddress;
				break;
			}
			CurDll = (PLDR_MODULE)CurDll->InLoadOrderModuleList.Flink;
		}
	}
	return Result;
}

wchar_t* __GetModuleFullNameW(wchar_t* lpModuleName)
{
	wchar_t* Result = NULL;
	wchar_t CurModuleName[300];
	wchar_t ModuleName[300];
	PPEB CurPEB = __NtCurrentPeb();
	PPEB_LDR_DATA_ CurLdr = (PPEB_LDR_DATA_)CurPEB->Ldr;
	PLDR_MODULE CurDll = (PLDR_MODULE)CurLdr->InLoadOrderModuleList.Flink;
	if(!lpModuleName)
		Result = CurDll->FullDllName.Buffer;
	else
	{
		__wcscpy(ModuleName, lpModuleName);
		__wcsupr(ModuleName);
		while (CurDll->BaseAddress != NULL)
		{
			__wcscpy(CurModuleName, CurDll->BaseDllName.Buffer);
			__wcsupr(CurModuleName);
			if (__wcscmp(ModuleName, CurModuleName) == 0) {
				Result = CurDll->FullDllName.Buffer;
				break;
			}
			CurDll = (PLDR_MODULE)CurDll->InLoadOrderModuleList.Flink;
		}
	}
	return Result;
}

wchar_t* __GetImagePathName()
{
	PRTL_USER_PROCESS_PARAMETERS p = __NtCurrentPeb()->ProcessParameters;
	return p->ImagePathName.Buffer;
}
//---------------------------------------------------------------------------
const wchar_t* __GetExeName()
{
	PPEB CurPEB = __NtCurrentPeb();
	PPEB_LDR_DATA_ CurLdr = (PPEB_LDR_DATA_)CurPEB->Ldr;
	PLDR_MODULE CurDll = (PLDR_MODULE)CurLdr->InLoadOrderModuleList.Flink;
	return CurDll->BaseDllName.Buffer;
}
// ---------------------------------------------------------------------------
typedef LONG (WINAPI *LPNtQueryInformationProcess)(HANDLE ProcessHandle, ULONG ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);
ULONG_PTR GetParentProcessId() // By Napalm @ NetCore2K
{
	ULONG_PTR pbi[6];
	ULONG ulSize = 0;
	LPNtQueryInformationProcess __NtQueryInformationProcess;
	__NtQueryInformationProcess = (LPNtQueryInformationProcess)__GetProcAddress(__GetModuleHandleW(L"NTDLL.DLL"), "NtQueryInformationProcess");
	if (__NtQueryInformationProcess) {
		if (__NtQueryInformationProcess(GetCurrentProcess(), 0, &pbi, sizeof(pbi),
			&ulSize) >= 0 && ulSize == sizeof(pbi))
			return pbi[5];
	}
	return (ULONG_PTR) - 1;
}
// ---------------------------------------------------------------------------
typedef NTSTATUS
(NTAPI
*LPZwProtectVirtualMemory) (
							IN HANDLE ProcessHandle,
							IN OUT PVOID *BaseAddress,
							IN OUT PULONG ProtectSize,
							IN ULONG NewProtect,
							OUT PULONG OldProtect
							);


NTSTATUS
NTAPI
__ZwProtectVirtualMemory(
						IN HANDLE ProcessHandle,
						IN OUT PVOID *BaseAddress,
						IN OUT PULONG ProtectSize,
						IN ULONG NewProtect,
						OUT PULONG OldProtect
						)
{
	LPZwProtectVirtualMemory ZwProtectVirtualMemory = (LPZwProtectVirtualMemory)__GetProcAddress( __GetModuleHandleW(L"ntdll.dll"), "ZwProtectVirtualMemory" );
	return ZwProtectVirtualMemory(ProcessHandle, BaseAddress, ProtectSize, NewProtect, OldProtect);
}
// ---------------------------------------------------------------------------
__declspec(naked)
BOOL
WINAPI
__VirtualProtectEx(
    __in  HANDLE hProcess,
    __in  LPVOID lpAddress,
    __in  SIZE_T dwSize,
    __in  DWORD flNewProtect,
    __out PDWORD lpflOldProtect
    )
{
	__asm{
		push ebp
		mov ebp,esp
		push esi
		push edi
		push [ebp+0x18]
		push [ebp+0x14]
		lea eax,[ebp+0x10]
		push eax
		lea eax,[ebp+0x0C]
		push eax
		push [ebp+0x08]
		call __ZwProtectVirtualMemory
		xor eax,eax
		inc eax
		pop edi
		pop esi
		pop ebp
		ret 0x0014
	}
}
// ---------------------------------------------------------------------------
typedef BOOL (WINAPI *LPCreateProcessInternalW)(HANDLE,LPCWSTR,LPWSTR,LPSECURITY_ATTRIBUTES,LPSECURITY_ATTRIBUTES,BOOL,DWORD,LPVOID,LPCWSTR,LPSTARTUPINFOW,LPPROCESS_INFORMATION,PHANDLE);
LPCreateProcessInternalW __CreateProcessInternalW;

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

BOOL WINAPI __CreateProcessW(
							LPCWSTR lpApplicationName,
							LPWSTR lpCommandLine,
							LPSECURITY_ATTRIBUTES lpProcessAttributes,
							LPSECURITY_ATTRIBUTES lpThreadAttributes,
							BOOL bInheritHandles,
							DWORD dwCreationFlags,
							LPVOID lpEnvironment,
							LPCWSTR lpCurrentDirectory,
							LPSTARTUPINFOW lpStartupInfo,
							LPPROCESS_INFORMATION lpProcessInformation
							)
{
	__CreateProcessInternalW = (LPCreateProcessInternalW)__GetProcAddress( __GetModuleHandleW(L"kernel32.dll"), "CreateProcessInternalW" );
	if(__CreateProcessInternalW)
		return __CreateProcessInternalW( NULL, lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation, NULL );
	return false;
}
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

DWORD IATHook(wchar_t* NameOfModuletoHook, char* funcName, DWORD newFunc)
{
	HMODULE hMod = __GetModuleHandleW(NameOfModuletoHook);
	IMAGE_DOS_HEADER* pDosHeader;
	IMAGE_OPTIONAL_HEADER* pOptHeader;
	IMAGE_IMPORT_DESCRIPTOR* pImportDesc;
	if(hMod)
	{
		pDosHeader = (IMAGE_DOS_HEADER*)hMod;
		pOptHeader = (IMAGE_OPTIONAL_HEADER*)((BYTE*)hMod + pDosHeader->e_lfanew +24);
		pImportDesc = (IMAGE_IMPORT_DESCRIPTOR*) ((BYTE*)hMod + pOptHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress); //what is the rule of adding them?
		while ( pImportDesc->FirstThunk )
		{
			//char * pszDllName = (char*) ((BYTE*)hMod + pImportDesc->Name);
			IMAGE_THUNK_DATA* pThunk = (IMAGE_THUNK_DATA*)((BYTE*)hMod + pImportDesc->OriginalFirstThunk);
			int n = 0;
			while ( pThunk->u1.Function )
			{
				char* pszFunName = (char*)((BYTE*)hMod + (DWORD)pThunk->u1.AddressOfData + 2);
				PDWORD lpAddr = (DWORD*)((BYTE*)hMod + pImportDesc->FirstThunk) + n;
				if( !( (DWORD)pszFunName & IMAGE_ORDINAL_FLAG32 ) )
				{
					//如果不是用ordinal導入的話
					if(__strcmp(pszFunName, funcName) == 0)
					{
						DWORD ret = *lpAddr;
/*
							DbgPrint("Found in module: %s, function: %s, IAT address: 0x%08X", pszDllName, pszFunName, lpAddr);
							DbgPrint("%s original address: 0x%08X", pszFunName, *lpAddr);
							DbgPrint("%s new address: 0x%08X", pszFunName, newFunc);
							OutputDebugString(L"ZwProtectVirtualMemory");
*/
						DWORD OldProtect;
						__VirtualProtectEx( __GetCurrentProcess(), (void*)lpAddr, 4, PAGE_EXECUTE_READWRITE, &OldProtect);
						*(DWORD *)lpAddr = newFunc;
						__VirtualProtectEx( __GetCurrentProcess(), (void*)lpAddr, 4, OldProtect, &OldProtect);
						if(ret == *lpAddr)
							return 0;
						else
							return ret;
					}
				}
				n++;
				pThunk++;
			}
			pImportDesc++;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
DWORD EATHook(wchar_t* NameOfModuletoHook, char* funcName, DWORD newFunc)
{
	int i=0;
	DWORD pRet = NULL;
	HMODULE hModule = __GetModuleHandleW(NameOfModuletoHook);
	PIMAGE_DOS_HEADER pImageDosHeader = NULL;
	PIMAGE_NT_HEADERS pImageNtHeader = NULL;
	PIMAGE_EXPORT_DIRECTORY pImageExportDirectory = NULL;

	if(hModule)
	{
		pImageDosHeader = (PIMAGE_DOS_HEADER)hModule;
		pImageNtHeader=(PIMAGE_NT_HEADERS)((DWORD)hModule+pImageDosHeader->e_lfanew);
		pImageExportDirectory=(PIMAGE_EXPORT_DIRECTORY)((DWORD)hModule+pImageNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

		DWORD dwExportRVA = pImageNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
		DWORD dwExportSize = pImageNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

		DWORD *pAddressOfFunction = (DWORD*)(pImageExportDirectory->AddressOfFunctions + (DWORD)hModule);
		DWORD *pAddressOfNames = (DWORD*)(pImageExportDirectory->AddressOfNames + (DWORD)hModule);
		DWORD dwNumberOfNames = (DWORD)(pImageExportDirectory->NumberOfNames);

		WORD *pAddressOfNameOrdinals = (WORD*)(pImageExportDirectory->AddressOfNameOrdinals + (DWORD)hModule);

		for (i=0; i<(int)dwNumberOfNames; i++)
		{
			char *strFunction = (char *)(pAddressOfNames[i] + (DWORD)hModule);
			if (__strcmp(strFunction, (char *)funcName) == 0)
			{
				DWORD* lpAddr = &pAddressOfFunction[pAddressOfNameOrdinals[i]];
				pRet = *lpAddr + (DWORD)hModule;
				//判斷得到的地址有沒有越界
				if ((DWORD)pRet<dwExportRVA+(DWORD)hModule || (DWORD)pRet > dwExportRVA+ (DWORD)hModule + dwExportSize)
				{
					DWORD OldProtect;
					__VirtualProtectEx( __GetCurrentProcess(), (void*)lpAddr, 4, PAGE_EXECUTE_READWRITE, &OldProtect);
					*(DWORD *)lpAddr = newFunc - (DWORD)hModule;
					__VirtualProtectEx( __GetCurrentProcess(), (void*)lpAddr, 4, OldProtect, &OldProtect);
					if(pRet == *lpAddr)
						return NULL;
					else
						return pRet;
				}
				break;
			}
		}
	}
	return NULL;
}
//---------------------------------------------------------------------------
void __cdecl WriteMemory( unsigned long ulAddress,unsigned char ucAmount, ...)
{
   DWORD dwOldProtect;
	VirtualProtect((void*)ulAddress, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect);//Unprotect memory

   va_list* va = new va_list;
   va_start(*va, ucAmount);

   for (unsigned char ByteToWrite = va_arg(*va, unsigned char), ucIndex = 0; ucIndex < ucAmount; ucIndex++, ByteToWrite = va_arg(*va, unsigned char))
   {
      *(unsigned char*)(ulAddress + ucIndex) = ByteToWrite;
   }

   va_end(*va);
   delete va;
  VirtualProtect((void*)ulAddress, 5, dwOldProtect, &dwOldProtect);//revert back to the original.
}
//---------------------------------------------------------------------------
//Des Kernel:
//(1)des_createKeys
//this  takes  as  input  a  64  bit  key  (even  though  only  56  bits  are  used)
//as  an  array  of  2  integers,  and  returns  16  48  bit  keys
//(2)des
//this takes the key, the message, and whether to encrypt or decrypt


int*  des_createKeys  (char* key)  {
	//declaring  this  locally  speeds  things  up  a  bit
	unsigned int pc2bytes0[]    =  {0,0x4,0x20000000,0x20000004,0x10000,0x10004,0x20010000,0x20010004,0x200,0x204,0x20000200,0x20000204,0x10200,0x10204,0x20010200,0x20010204};
	unsigned int pc2bytes1[]    =  {0,0x1,0x100000,0x100001,0x4000000,0x4000001,0x4100000,0x4100001,0x100,0x101,0x100100,0x100101,0x4000100,0x4000101,0x4100100,0x4100101};
	unsigned int pc2bytes2[]    =  {0,0x8,0x800,0x808,0x1000000,0x1000008,0x1000800,0x1000808,0,0x8,0x800,0x808,0x1000000,0x1000008,0x1000800,0x1000808};
	unsigned int pc2bytes3[]    =  {0,0x200000,0x8000000,0x8200000,0x2000,0x202000,0x8002000,0x8202000,0x20000,0x220000,0x8020000,0x8220000,0x22000,0x222000,0x8022000,0x8222000};
	unsigned int pc2bytes4[]    =  {0,0x40000,0x10,0x40010,0,0x40000,0x10,0x40010,0x1000,0x41000,0x1010,0x41010,0x1000,0x41000,0x1010,0x41010};
	unsigned int pc2bytes5[]    =  {0,0x400,0x20,0x420,0,0x400,0x20,0x420,0x2000000,0x2000400,0x2000020,0x2000420,0x2000000,0x2000400,0x2000020,0x2000420};
	unsigned int pc2bytes6[]    =  {0,0x10000000,0x80000,0x10080000,0x2,0x10000002,0x80002,0x10080002,0,0x10000000,0x80000,0x10080000,0x2,0x10000002,0x80002,0x10080002};
	unsigned int pc2bytes7[]    =  {0,0x10000,0x800,0x10800,0x20000000,0x20010000,0x20000800,0x20010800,0x20000,0x30000,0x20800,0x30800,0x20020000,0x20030000,0x20020800,0x20030800};
	unsigned int pc2bytes8[]    =  {0,0x40000,0,0x40000,0x2,0x40002,0x2,0x40002,0x2000000,0x2040000,0x2000000,0x2040000,0x2000002,0x2040002,0x2000002,0x2040002};
	unsigned int pc2bytes9[]    =  {0,0x10000000,0x8,0x10000008,0,0x10000000,0x8,0x10000008,0x400,0x10000400,0x408,0x10000408,0x400,0x10000400,0x408,0x10000408};
	unsigned int pc2bytes10[]  =  {0,0x20,0,0x20,0x100000,0x100020,0x100000,0x100020,0x2000,0x2020,0x2000,0x2020,0x102000,0x102020,0x102000,0x102020};
	unsigned int pc2bytes11[]  =  {0,0x1000000,0x200,0x1000200,0x200000,0x1200000,0x200200,0x1200200,0x4000000,0x5000000,0x4000200,0x5000200,0x4200000,0x5200000,0x4200200,0x5200200};
	unsigned int pc2bytes12[]  =  {0,0x1000,0x8000000,0x8001000,0x80000,0x81000,0x8080000,0x8081000,0x10,0x1010,0x8000010,0x8001010,0x80010,0x81010,0x8080010,0x8081010};
	unsigned int pc2bytes13[]  =  {0,0x4,0x100,0x104,0,0x4,0x100,0x104,0x1,0x5,0x101,0x105,0x1,0x5,0x101,0x105};
	unsigned int masks[]  =  {0xFFFFFFFF,0x7FFFFFFF,0x3FFFFFFF,0x1FFFFFFF,0x0FFFFFFF,0x07FFFFFF,0x03FFFFFF,0x01FFFFFF,0x00FFFFFF,0x007FFFFF,0x003FFFFF,0x001FFFFF,0x000FFFFF,0x0007FFFF,0x0003FFFF,0x0001FFFF,0x0000FFFF,0x00007FFF,0x00003FFF,0x00001FFF,0x00000FFF,0x000007FF,0x000003FF,0x000001FF,0x000000FF,0x0000007F,0x0000003F,0x0000001F,0x0000000F,0x00000007,0x00000003,0x00000001,0x00000000};

	//how  many  iterations  (1  for  des,  3  for  triple  des)
	int iterations  =  ((__strlen(key)  >=  24)  ?  3  :  1);
	//now  define  the  DesLeft  shifts  which  need  to  be  done
	int shifts[]  =  {0,  0,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  0};
	//stores  the  return  keys
	int *keys = new int[32*iterations];  //  size  =  32  *  iterations  but  you  don't  specify  this  in  php
	//other  variables
	int m = 0;
	int n = 0;
	int temp;

	unsigned int DesLeft, DesRight;
	unsigned int DesLefttemp, DesRighttemp;

	for  (int j=0;  j<iterations;  j++)  {  //either  1  or  3  iterations
		key[m] = key[m];
		temp = (unsigned char)key[m]  <<  24;
		temp |= (unsigned char)key[m+1]  <<  16;
		temp |= (unsigned char)key[m+2]  <<  8;
		temp |= (unsigned char)key[m+3];

		DesLeft  =  ((unsigned char)key[m]  <<  24)  |  ((unsigned char)key[m+1]  <<  16)  |  ((unsigned char)key[m+2]  <<  8)  |  (unsigned char)key[m+3];
		DesRight  =  ((unsigned char)key[m+4]  <<  24)  |  ((unsigned char)key[m+5]  <<  16)  |  ((unsigned char)key[m+6]  <<  8)  |  (unsigned char)key[m+7];
		m+=8;
		temp  =  ((DesLeft  >>  4  &  masks[4])  ^  DesRight)  &  0x0f0f0f0f;  DesRight  ^=  temp;  DesLeft  ^=  (temp  <<  4);
        temp  =  ((DesRight  >>  16  &  masks[16])  ^  DesLeft)  &  0x0000ffff;  DesLeft  ^=  temp;  DesRight  ^=  (temp  <<  16);
        temp  =  ((DesLeft  >>  2  &  masks[2])  ^  DesRight)  &  0x33333333;  DesRight  ^=  temp;  DesLeft  ^=  (temp  <<  2);
        temp  =  ((DesRight  >>  16  &  masks[16])  ^  DesLeft)  &  0x0000ffff;  DesLeft  ^=  temp;  DesRight  ^=  (temp  <<  16);
        temp  =  ((DesLeft  >>  1  &  masks[1])  ^  DesRight)  &  0x55555555;  DesRight  ^=  temp;  DesLeft  ^=  (temp  <<  1);
        temp  =  ((DesRight  >>  8  &  masks[8])  ^  DesLeft)  &  0x00ff00ff;  DesLeft  ^=  temp;  DesRight  ^=  (temp  <<  8);
        temp  =  ((DesLeft  >>  1  &  masks[1])  ^  DesRight)  &  0x55555555;  DesRight  ^=  temp;  DesLeft  ^=  (temp  <<  1);

        //the  DesRight  side  needs  to  be  shifted  and  to  get  the  last  four  bits  of  the  DesLeft  side
        temp  =  (DesLeft  <<  8)  |  ((DesRight  >>  20  &  masks[20])  &  0x000000f0);
        //DesLeft  needs  to  be  put  upside  down
		DesLeft  =  (DesRight  <<  24)  |  ((DesRight  <<  8)  &  0xff0000)  |  ((DesRight  >>  8  &  masks[8])  &  0xff00)  |  ((DesRight  >>  24  &  masks[24])  &  0xf0);
        DesRight  =  temp;

        //now  go  through  and  perform  these  shifts  on  the  DesLeft  and  DesRight  keys
        for  (int i=0;  i  <  16;  i++)  {
            //shift  the  keys  either  one  or  two  bits  to  the  DesLeft
            if  (shifts[i]  >  0)  {
                  DesLeft  =  ((DesLeft  <<  2)  |  (DesLeft  >>  26  &  masks[26]));
				  DesRight  =  ((DesRight  <<  2)  |  (DesRight  >>  26  &  masks[26]));
            }
			else  {
                  DesLeft  =  ((DesLeft  <<  1)  |  (DesLeft  >>  27  &  masks[27]));
                  DesRight  =  ((DesRight  <<  1)  |  (DesRight  >>  27  &  masks[27]));
            }
            DesLeft  =  DesLeft  &  -0xf;
            DesRight  =  DesRight  &  -0xf;

            //now  apply  PC-2,  in  such  a  way  that  E  is  easier  when  encrypting  or  decrypting
            //this  conversion  will  look  like  PC-2  except  only  the  last  6  bits  of  each  byte  are  used
            //rather  than  48  consecutive  bits  and  the  order  of  lines  will  be  according  to
            //how  the  S  selection  functions  will  be  applied:  S2,  S4,  S6,  S8,  S1,  S3,  S5,  S7
            DesLefttemp  =  pc2bytes0[DesLeft  >>  28  &  masks[28]]  |  pc2bytes1[(DesLeft  >>  24  &  masks[24])  &  0xf]
                            |  pc2bytes2[(DesLeft  >>  20  &  masks[20])  &  0xf]  |  pc2bytes3[(DesLeft  >>  16  &  masks[16])  &  0xf]
							|  pc2bytes4[(DesLeft  >>  12  &  masks[12])  &  0xf]  |  pc2bytes5[(DesLeft  >>  8  &  masks[8])  &  0xf]
                            |  pc2bytes6[(DesLeft  >>  4  &  masks[4])  &  0xf];
            DesRighttemp  =  pc2bytes7[DesRight  >>  28  &  masks[28]]  |  pc2bytes8[(DesRight  >>  24  &  masks[24])  &  0xf]
                                |  pc2bytes9[(DesRight  >>  20  &  masks[20])  &  0xf]  |  pc2bytes10[(DesRight  >>  16  &  masks[16])  &  0xf]
                                |  pc2bytes11[(DesRight  >>  12  &  masks[12])  &  0xf]  |  pc2bytes12[(DesRight  >>  8  &  masks[8])  &  0xf]
                                |  pc2bytes13[(DesRight  >>  4  &  masks[4])  &  0xf];
            temp  =  ((DesRighttemp  >>  16  &  masks[16])  ^  DesLefttemp)  &  0x0000ffff;
            keys[n+0]  =  DesLefttemp  ^  temp;
			keys[n+1]  =  DesRighttemp  ^  (temp  <<  16);
			n = n + 2;
        }
    }  //for  each  iterations
    //return  the  keys  we've  created
	return  keys;
}  //end  of  des_createKeys
SimpleString* des(char* key, SimpleString* in, bool encrypt, int mode, char* iv)  {
	//declaring  this  locally  speeds  things  up  a  bit
	unsigned int spfunction1[]  =  {0x1010400,0,0x10000,0x1010404,0x1010004,0x10404,0x4,0x10000,0x400,0x1010400,0x1010404,0x400,0x1000404,0x1010004,0x1000000,0x4,0x404,0x1000400,0x1000400,0x10400,0x10400,0x1010000,0x1010000,0x1000404,0x10004,0x1000004,0x1000004,0x10004,0,0x404,0x10404,0x1000000,0x10000,0x1010404,0x4,0x1010000,0x1010400,0x1000000,0x1000000,0x400,0x1010004,0x10000,0x10400,0x1000004,0x400,0x4,0x1000404,0x10404,0x1010404,0x10004,0x1010000,0x1000404,0x1000004,0x404,0x10404,0x1010400,0x404,0x1000400,0x1000400,0,0x10004,0x10400,0,0x1010004};
    unsigned int spfunction2[]  =  {0x80108020,0x80008000,0x8000,0x108020,0x100000,0x20,0x80100020,0x80008020,0x80000020,0x80108020,0x80108000,0x80000000,0x80008000,0x100000,0x20,0x80100020,0x108000,0x100020,0x80008020,0,0x80000000,0x8000,0x108020,0x80100000,0x100020,0x80000020,0,0x108000,0x8020,0x80108000,0x80100000,0x8020,0,0x108020,0x80100020,0x100000,0x80008020,0x80100000,0x80108000,0x8000,0x80100000,0x80008000,0x20,0x80108020,0x108020,0x20,0x8000,0x80000000,0x8020,0x80108000,0x100000,0x80000020,0x100020,0x80008020,0x80000020,0x100020,0x108000,0,0x80008000,0x8020,0x80000000,0x80100020,0x80108020,0x108000};
    unsigned int spfunction3[]  =  {0x208,0x8020200,0,0x8020008,0x8000200,0,0x20208,0x8000200,0x20008,0x8000008,0x8000008,0x20000,0x8020208,0x20008,0x8020000,0x208,0x8000000,0x8,0x8020200,0x200,0x20200,0x8020000,0x8020008,0x20208,0x8000208,0x20200,0x20000,0x8000208,0x8,0x8020208,0x200,0x8000000,0x8020200,0x8000000,0x20008,0x208,0x20000,0x8020200,0x8000200,0,0x200,0x20008,0x8020208,0x8000200,0x8000008,0x200,0,0x8020008,0x8000208,0x20000,0x8000000,0x8020208,0x8,0x20208,0x20200,0x8000008,0x8020000,0x8000208,0x208,0x8020000,0x20208,0x8,0x8020008,0x20200};
    unsigned int spfunction4[]  =  {0x802001,0x2081,0x2081,0x80,0x802080,0x800081,0x800001,0x2001,0,0x802000,0x802000,0x802081,0x81,0,0x800080,0x800001,0x1,0x2000,0x800000,0x802001,0x80,0x800000,0x2001,0x2080,0x800081,0x1,0x2080,0x800080,0x2000,0x802080,0x802081,0x81,0x800080,0x800001,0x802000,0x802081,0x81,0,0,0x802000,0x2080,0x800080,0x800081,0x1,0x802001,0x2081,0x2081,0x80,0x802081,0x81,0x1,0x2000,0x800001,0x2001,0x802080,0x800081,0x2001,0x2080,0x800000,0x802001,0x80,0x800000,0x2000,0x802080};
    unsigned int spfunction5[]  =  {0x100,0x2080100,0x2080000,0x42000100,0x80000,0x100,0x40000000,0x2080000,0x40080100,0x80000,0x2000100,0x40080100,0x42000100,0x42080000,0x80100,0x40000000,0x2000000,0x40080000,0x40080000,0,0x40000100,0x42080100,0x42080100,0x2000100,0x42080000,0x40000100,0,0x42000000,0x2080100,0x2000000,0x42000000,0x80100,0x80000,0x42000100,0x100,0x2000000,0x40000000,0x2080000,0x42000100,0x40080100,0x2000100,0x40000000,0x42080000,0x2080100,0x40080100,0x100,0x2000000,0x42080000,0x42080100,0x80100,0x42000000,0x42080100,0x2080000,0,0x40080000,0x42000000,0x80100,0x2000100,0x40000100,0x80000,0,0x40080000,0x2080100,0x40000100};
    unsigned int spfunction6[]  =  {0x20000010,0x20400000,0x4000,0x20404010,0x20400000,0x10,0x20404010,0x400000,0x20004000,0x404010,0x400000,0x20000010,0x400010,0x20004000,0x20000000,0x4010,0,0x400010,0x20004010,0x4000,0x404000,0x20004010,0x10,0x20400010,0x20400010,0,0x404010,0x20404000,0x4010,0x404000,0x20404000,0x20000000,0x20004000,0x10,0x20400010,0x404000,0x20404010,0x400000,0x4010,0x20000010,0x400000,0x20004000,0x20000000,0x4010,0x20000010,0x20404010,0x404000,0x20400000,0x404010,0x20404000,0,0x20400010,0x10,0x4000,0x20400000,0x404010,0x4000,0x400010,0x20004010,0,0x20404000,0x20000000,0x400010,0x20004010};
	unsigned int spfunction7[]  =  {0x200000,0x4200002,0x4000802,0,0x800,0x4000802,0x200802,0x4200800,0x4200802,0x200000,0,0x4000002,0x2,0x4000000,0x4200002,0x802,0x4000800,0x200802,0x200002,0x4000800,0x4000002,0x4200000,0x4200800,0x200002,0x4200000,0x800,0x802,0x4200802,0x200800,0x2,0x4000000,0x200800,0x4000000,0x200800,0x200000,0x4000802,0x4000802,0x4200002,0x4200002,0x2,0x200002,0x4000000,0x4000800,0x200000,0x4200800,0x802,0x200802,0x4200800,0x802,0x4000002,0x4200802,0x4200000,0x200800,0,0x2,0x4200802,0,0x200802,0x4200000,0x800,0x4000002,0x4000800,0x800,0x200002};
    unsigned int spfunction8[]  =  {0x10001040,0x1000,0x40000,0x10041040,0x10000000,0x10001040,0x40,0x10000000,0x40040,0x10040000,0x10041040,0x41000,0x10041000,0x41040,0x1000,0x40,0x10040000,0x10000040,0x10001000,0x1040,0x41000,0x40040,0x10040040,0x10041000,0x1040,0,0,0x10040040,0x10000040,0x10001000,0x41040,0x40000,0x41040,0x40000,0x10041000,0x1000,0x40,0x10040040,0x1000,0x41040,0x10001000,0x40,0x10000040,0x10040000,0x10040040,0x10000000,0x40000,0x10001040,0,0x10041040,0x40040,0x10000040,0x10040000,0x10001000,0x10001040,0,0x10041040,0x41000,0x41000,0x1040,0x1040,0x40040,0x10000000,0x10041000};
    unsigned int masks[]  =  {0xFFFFFFFF,0x7FFFFFFF,0x3FFFFFFF,0x1FFFFFFF,0x0FFFFFFF,0x07FFFFFF,0x03FFFFFF,0x01FFFFFF,0x00FFFFFF,0x007FFFFF,0x003FFFFF,0x001FFFFF,0x000FFFFF,0x0007FFFF,0x0003FFFF,0x0001FFFF,0x0000FFFF,0x00007FFF,0x00003FFF,0x00001FFF,0x00000FFF,0x000007FF,0x000003FF,0x000001FF,0x000000FF,0x0000007F,0x0000003F,0x0000001F,0x0000000F,0x00000007,0x00000003,0x00000001,0x00000000};

    int *keys;
	int m;
    unsigned int temp, right1, right2, DesLeft, DesRight;
    int *looping;
    unsigned int cbcleft, cbcleft2, cbcright, cbcright2;
    int endloop, loopinc;
	int len, iterations;
	int chunk, resultLength, tempresultLength;
	char* message;
	char result[300];
	char tempresult[300];
	SimpleString* final = new SimpleString;
	__memset( (void*)final->str,0,sizeof(final->str) );
	final->length = 0;

	iterations  =  (( __strlen(key)  >=  24)  ?  9  :  3);  //single  or  triple  des
	//create the 16 or 48 subkeys we will need
	keys = des_createKeys(key);
	m=0; cbcleft=0; cbcleft2=0; cbcright=0; cbcright2=0; chunk=0;
	message = in->str;
	len = in->length;
	//set up the loops for single and triple des
	if  (iterations  ==  3)
	{
		looping  =  new int[3];
		if(encrypt)
		{
			looping[0] = 0;
			looping[1] = 32;
			looping[2] = 2;
		}
		else
		{
			looping[0] = 30;
			looping[1] = -2;
			looping[2] = -2;
		}
	}
    else
	{
		looping  =  new int[9];
		if(encrypt)
		{
			looping[0] = 0;
			looping[1] = 32;
			looping[2] = 2;
			looping[3] = 62;
			looping[4] = 30;
			looping[5] = -2;
			looping[6] = 64;
			looping[7] = 96;
			looping[8] = 2;
		}
		else
		{
			looping[0] = 94;
			looping[1] = 62;
			looping[2] = -2;
			looping[3] = 32;
			looping[4] = 64;
			looping[5] = 2;
			looping[6] = 30;
			looping[7] = -2;
			looping[8] = -2;
		}
	}

	message[len] = '\0';
	message[len+1] = '\0';
	message[len+2] = '\0';
	message[len+3] = '\0';
	message[len+4] = '\0';
	message[len+5] = '\0';
	message[len+6] = '\0';
	message[len+7] = '\0';


	//store the result here
	__memset( (void*)result, 0, sizeof(result) );
	__memset( (void*)tempresult, 0, sizeof(tempresult));

	if( mode == 1)//CBC mode
    {
	   cbcleft  =  ((unsigned char)iv[m]  <<  24)  |  ((unsigned char)iv[m+1]  <<  16)  |  ((unsigned char)iv[m+2]  <<  8)  |  (unsigned char)iv[m+3];
	   cbcright  =  ((unsigned char)iv[m+4]  <<  24)  |  ((unsigned char)iv[m+5]  <<  16)  |  ((unsigned char)iv[m+6]  <<  8)  |  (unsigned char)iv[m+7];
	   m=0;
    }

	resultLength = 0;
	tempresultLength = 0;

    //loop through each 64 bit chunk of the message
	while  (m  <  len)  {
		DesLeft  =  ((unsigned char)message[m]  <<  24)  |  ((unsigned char)message[m+1]  <<  16)  |  ((unsigned char)message[m+2]  <<  8)  |  (unsigned char)message[m+3];
		DesRight  =  ((unsigned char)message[m+4]  <<  24)  |  ((unsigned char)message[m+5]  <<  16)  |  ((unsigned char)message[m+6]  <<  8)  |  (unsigned char)message[m+7];
		m+=8;

        //for Cipher Block Chaining mode, xor the message with the previous result
        if ( mode == 1 )
        {
            if  (encrypt)
            {
                DesLeft  ^=  cbcleft;
                DesRight  ^=  cbcright;
            }
            else
            {
                cbcleft2  =  cbcleft;
                cbcright2  =  cbcright;
                cbcleft  =  DesLeft;
                cbcright  =  DesRight;
            }
        }

        //first  each  64  but  chunk  of  the  message  must  be  permuted  according  to  IP
        temp  =  ((DesLeft  >>  4  &  masks[4])  ^  DesRight)  &  0x0f0f0f0f;  DesRight  ^=  temp;  DesLeft  ^=  (temp  <<  4);
		temp  =  ((DesLeft  >>  16  &  masks[16])  ^  DesRight)  &  0x0000ffff;  DesRight  ^=  temp;  DesLeft  ^=  (temp  <<  16);
		temp  =  ((DesRight  >>  2  &  masks[2])  ^  DesLeft)  &  0x33333333;  DesLeft  ^=  temp;  DesRight  ^=  (temp  <<  2);
        temp  =  ((DesRight  >>  8  &  masks[8])  ^  DesLeft)  &  0x00ff00ff;  DesLeft  ^=  temp;  DesRight  ^=  (temp  <<  8);
        temp  =  ((DesLeft  >>  1  &  masks[1])  ^  DesRight)  &  0x55555555;  DesRight  ^=  temp;  DesLeft  ^=  (temp  <<  1);

        DesLeft  =  ((DesLeft  <<  1)  |  (DesLeft  >>  31  &  masks[31]));
        DesRight  =  ((DesRight  <<  1)  |  (DesRight  >>  31  &  masks[31]));

        //do  this  either  1  or  3  times  for  each  chunk  of  the  message
		for  (int j=0;  j<iterations;  j+=3)  {
            endloop  =  looping[j+1];
            loopinc  =  looping[j+2];
            //now  go  through  and  perform  the  encryption  or  decryption
            for  (int i=looping[j];  i!=endloop;  i+=loopinc)  {  //for  efficiency
				right1  =  DesRight  ^  keys[i];
                right2  =  ((DesRight  >>  4  &  masks[4])  |  (DesRight  <<  28))  ^  keys[i+1];
                //the  result  is  attained  by  passing  these  bytes  through  the  S  selection  functions
                temp  =  DesLeft;
				DesLeft  =  DesRight;
                DesRight  =  temp  ^  (spfunction2[(right1  >>  24  &  masks[24])  &  0x3f]  |  spfunction4[(right1  >>  16  &  masks[16])  &  0x3f]
                            |  spfunction6[(right1  >>    8  &  masks[8])  &  0x3f]  |  spfunction8[right1  &  0x3f]
                            |  spfunction1[(right2  >>  24  &  masks[24])  &  0x3f]  |  spfunction3[(right2  >>  16  &  masks[16])  &  0x3f]
                            |  spfunction5[(right2  >>    8  &  masks[8])  &  0x3f]  |  spfunction7[right2  &  0x3f]);
            }
            temp  =  DesLeft;  DesLeft  =  DesRight;  DesRight  =  temp;  //unreverse  DesLeft  and  DesRight
        }  //for  either  1  or  3  iterations


        //move  then  each  one  bit  to  the  DesRight
        DesLeft  =  ((DesLeft  >>  1  &  masks[1])  |  (DesLeft  <<  31));
        DesRight  =  ((DesRight  >>  1  &  masks[1])  |  (DesRight  <<  31));

        //now  perform  IP-1,  which  is  IP  in  the  opposite  direction
        temp  =  ((DesLeft  >>  1  &  masks[1])  ^  DesRight)  &  0x55555555;  DesRight  ^=  temp;  DesLeft  ^=  (temp  <<  1);
        temp  =  ((DesRight  >>  8  &  masks[8])  ^  DesLeft)  &  0x00ff00ff;  DesLeft  ^=  temp;  DesRight  ^=  (temp  <<  8);
        temp  =  ((DesRight  >>  2  &  masks[2])  ^  DesLeft)  &  0x33333333;  DesLeft  ^=  temp;  DesRight  ^=  (temp  <<  2);
        temp  =  ((DesLeft  >>  16  &  masks[16])  ^  DesRight)  &  0x0000ffff;  DesRight  ^=  temp;  DesLeft  ^=  (temp  <<  16);
        temp  =  ((DesLeft  >>  4  &  masks[4])  ^  DesRight)  &  0x0f0f0f0f;  DesRight  ^=  temp;  DesLeft  ^=  (temp  <<  4);

        //for  Cipher  Block  Chaining  mode,  xor  the  message  with  the  previous  result
        if  (mode  ==  1)
		{
			if  (encrypt)
			{
				cbcleft  =  DesLeft;
				cbcright  =  DesRight;
			}
			else
			{
				DesLeft  ^=  cbcleft2;
				DesRight  ^=  cbcright2;
			}
		}
		tempresult[tempresultLength++]  += (char)(DesLeft>>24  &  masks[24]);
		tempresult[tempresultLength++]  += (char)((DesLeft>>16  &  masks[16])  &  0xff);
		tempresult[tempresultLength++]  += (char)((DesLeft>>8  &  masks[8])  &  0xff);
		tempresult[tempresultLength++]  += (char)(DesLeft  &  0xff);
		tempresult[tempresultLength++]  += (char)(DesRight>>24  &  masks[24]);
		tempresult[tempresultLength++]  += (char)((DesRight>>16  &  masks[16])  &  0xff);
		tempresult[tempresultLength++]  += (char)((DesRight>>8  &  masks[8])  &  0xff);
		tempresult[tempresultLength++]  += (char)(DesRight  &  0xff);

		chunk  +=  8;
		if  (chunk  ==  512)  {
			__memcpy( (void*)(result+resultLength), tempresult,  tempresultLength );
			resultLength  +=  tempresultLength;
			tempresultLength = 0;
			__memset( (void*)tempresult, 0, sizeof(tempresult));
			chunk  =  0;
		}
	}  //for  every  8  characters,  or  64  bits  in  the  message
	delete looping;
	delete keys;
	//return  the  result  as  an  array
	__memcpy( (void*)(result+resultLength), (void*)tempresult,  tempresultLength );
	resultLength  +=  tempresultLength;

	__memcpy( (void*)final->str, (void*)result, resultLength );
	final->length = resultLength;
	return  final;
}  //end  of  des


DesStream::DesStream(char* src, size_t length)
{
	Data = new SimpleString;
	__memset( (void*)Data->str, 0, sizeof(Data->str) );
	__memcpy( (void*)Data->str, (void*)src, length);
	Data->length = length;
}
DesStream::DesStream()
{
	Data = new SimpleString;
	__memset( (void*)Data->str, 0, sizeof(Data->str) );
	Data->length = 0;
}
DesStream::~DesStream()
{
	delete Data;
}
char* DesStream::EncryStr(char* key)
{
	SimpleString* newstr = des(key,Data,1,0,"");
	delete Data;
	Data = newstr;
	return Data->str;
}
char* DesStream::EncryStrCBC(char* key,char* iv)
{
	SimpleString* newstr = des(key,Data,1,1,iv);
	delete Data;
	Data = newstr;
	return Data->str;
}
char* DesStream::DecryStr(char* key)
{
	SimpleString* newstr = des(key,Data,0,0,"");
	delete Data;
	Data = newstr;
	return Data->str;
}
char* DesStream::DecryStrCBC(char* key, char* iv)
{
	SimpleString* newstr = des(key,Data,0,1,iv);
	delete Data;
	Data = newstr;
	return Data->str;
}
char* DesStream::SubStr(int position, int length, char* buffer)
{
	int c;
	char* string = this->Data->str;

	for (c = 0 ; c < position ; c++)
	  string++;

	for (c = 0 ; c < length ; c++)
	{
	  *(buffer+c) = *string;
	  string++;
	}

	*(buffer+c) = '\0';
	return buffer;
}
char* DesStream::SubStrData(int position)
{
	char buffer[100];
	Data->length -= position;//Length of new data
	this->SubStr(position, Data->length, buffer);
	__memcpy( Data->str, buffer, Data->length);
	Data->str[Data->length] = '\0';
	return Data->str;
}
//---------------------------------------------------------------------------
char* StrToHex(unsigned char* buffer, unsigned int length, char* out)
{
	char hexes[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(unsigned int i=0; i<length; i++)
	{
		out[2*i] = hexes[buffer[i] >> 4];
		out[2*i+1] = hexes[buffer[i] & 0x0F];
	}
	out[2*length] = '\0';
	return out;
}
//---------------------------------------------------------------------------
