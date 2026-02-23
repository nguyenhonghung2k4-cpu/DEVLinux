#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>

/* * Defines 8 log levels according to the syslog standard. 
 * A lower numerical value corresponds to a higher priority. 
 */
typedef enum {
    LOG_EMERGENCY = 0,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

/* * Convenience Interface
 * This macro automatically captures __FILE__ and __LINE__ and passes them to the logger_log function.
 * It uses __VA_ARGS__ to support a variable number of arguments (variadic arguments).
 */
#define log_message(level, ...) logger_log(level, __FILE__, __LINE__, __VA_ARGS__)

/* * Initializes the logger. 
 * Returns true on success, false on failure (e.g., if the file cannot be opened).
 * If filepath is NULL, the logger will only output to the console. 
 */
bool logger_init(const char *filepath, LogLevel min_level);

/* * Changes the minimum log filtering level at runtime. 
 */
void logger_set_level(LogLevel min_level);

/* * Core function to write logs. 
 * (Users should use the log_message macro instead of calling this function directly). 
 */
void logger_log(LogLevel level, const char *file, int line, const char *format, ...);

/* * Closes the log file and cleans up resources. 
 */
void logger_close(void);

#endif /* LOGGER_H */