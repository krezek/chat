#ifndef _LOG_H_
#define _LOG_H_

void Logger_init();
void Logger_destroy();

void Log_info(const wchar_t* msg);
void Log_error(const wchar_t* msg);

#endif /* _LOG_H_ */
