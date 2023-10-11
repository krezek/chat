#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

#include "log.h"

static FILE* g_log_file;

void Logger_init()
{
	errno_t err;

	err = fopen_s(&g_log_file, "log.txt", "a+");
	if (err)
		fprintf(stderr, "Cannot open 'log.txt' file.\n");
}

void Logger_destroy()
{
	fclose(g_log_file);
}

static void Log_func(const wchar_t* cat, const wchar_t* msg)
{

}
