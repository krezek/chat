#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>

#include "log.h"

static FILE* g_log_file;
CRITICAL_SECTION CriticalSection;

void Logger_init()
{
	errno_t err;

	err = fopen_s(&g_log_file, "log.txt", "a+");
	if (err)
		fprintf(stderr, "Cannot open 'log.txt' file.\n");

	InitializeCriticalSection(&CriticalSection);
}

void Logger_destroy()
{
	fclose(g_log_file);
}

static void Log_func(const wchar_t* cat, const wchar_t* msg)
{
	char buf[100];
	time_t t;
	struct tm tm;
	DWORD thID;

	EnterCriticalSection(&CriticalSection);
	
	t = time(NULL);
	thID = GetCurrentThreadId();

	localtime_s(&tm, &t);
	asctime_s(buf, 100, &tm);

	fwprintf(g_log_file, L"%S%s|%d|%s\n", buf, cat, thID, msg);

	LeaveCriticalSection(&CriticalSection);
}

void Log_info(const wchar_t* msg)
{
	Log_func(L"INFO", msg);
}

void Log_error(const wchar_t* msg)
{
	Log_func(L"ERROR", msg);
}
