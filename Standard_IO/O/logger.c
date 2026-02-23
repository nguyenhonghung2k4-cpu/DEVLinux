#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>


static FILE *log_file_ptr = NULL;
static LogLevel current_min_level = LOG_INFO;


static const char *level_names[] = {
    "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
    "WARNING", "NOTICE", "INFO", "DEBUG"
};


static const char* get_basename(const char* path) {
    const char* base = strrchr(path, '/');
    const char* base_win = strrchr(path, '\\'); 
    if (base_win > base) {
        base = base_win;
    }
    return base ? base + 1 : path;
}

bool logger_init(const char *filepath, LogLevel min_level) {
    current_min_level = min_level;
    
   
    if (filepath != NULL) {
        log_file_ptr = fopen(filepath, "a");
        if (log_file_ptr == NULL) {
            return false;
        }
    }
    return true;
}

void logger_set_level(LogLevel min_level) {
    current_min_level = min_level;
}

void logger_log(LogLevel level, const char *file, int line, const char *format, ...) {
    
    if (level > current_min_level) {
        return;
    }

 
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char time_buffer[25];
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", tm_info);


    char message_buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(message_buffer, sizeof(message_buffer), format, args);
    va_end(args);

  
    const char* filename = get_basename(file);

 
    FILE *console_stream = (level <= LOG_ERROR) ? stderr : stdout;
    fprintf(console_stream, "[%s] [%s] [%s:%d] - %s\n",
            time_buffer, level_names[level], filename, line, message_buffer);


    if (log_file_ptr != NULL) {
        fprintf(log_file_ptr, "[%s] [%s] [%s:%d] - %s\n",
                time_buffer, level_names[level], filename, line, message_buffer);
    
        fflush(log_file_ptr); 
    }
}

void logger_close(void) {
    if (log_file_ptr != NULL) {
        fclose(log_file_ptr);
        log_file_ptr = NULL;
    }
}