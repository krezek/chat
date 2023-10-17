#include "platform.h"

#include "log.h"

static FILE* g_log_file;
static CRITICAL_SECTION g_file_guard;

void Logger_init()
{
	errno_t err;

	err = fopen_s(&g_log_file, "log.txt", "a+");
	if (err)
		fprintf(stderr, "Cannot open 'log.txt' file.\n");

	InitializeCriticalSection(&g_file_guard);
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

	EnterCriticalSection(&g_file_guard);
	
	t = time(NULL);
	thID = GetCurrentThreadId();

	localtime_s(&tm, &t);
	asctime_s(buf, 100, &tm);

	fwprintf(g_log_file, L"%S%s|%d|%s\n", buf, cat, thID, msg);
	fflush(g_log_file);

	LeaveCriticalSection(&g_file_guard);
}

void Log_info(const wchar_t* msg)
{
	Log_func(L"INFO", msg);
}

void Log_error(const wchar_t* msg)
{
	Log_func(L"ERROR", msg);
}
