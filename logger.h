#ifndef LOGGER_H
#define LOGGER_H

#define BLACK "\33[0;30m"
#define RED "\33[0;31m"
#define GREEN "\33[0;32m"
#define YELLOW "\33[0;33m"
#define BLUE "\33[0;34m"
#define MAG "\33[0;35m"
#define CYN "\33[0;36m"
#define WHITE "\33[0;37m"

// #define LOG_DEBUG GREEN
// #define LOG_INFO BLUE
// #define LOG_WARN YELLOW
// #define LOG_ERROR RED

typedef enum{
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR, 
} log_level;

extern char* log_level_color[];
extern char* log_level_name[];

typedef enum{
    SHELL_DISABLE = 0,
    SHELL_ENABLE = 1
} shell_conf_t;


typedef struct{
    FILE *logFile;
    int current_level;
    shell_conf_t shellEnable;
    char* timeStringFormat;

    void (*init)(const char *filename, log_level color_prefix, shell_conf_t );
    void (*set_level)(log_level color_prefix);
    // set stringTime format
    void (*message)(const log_level color_prefix, const char *format, ...);
    void (*close)();
} logger_t;

extern logger_t logger;

#define log_debug(...) logger.message(LOG_DEBUG, __VA_ARGS__)
#define log_info(...)  logger.message(LOG_INFO,  __VA_ARGS__)
#define log_warn(...)  logger.message(LOG_WARN,  __VA_ARGS__)
#define log_error(...) logger.message(LOG_ERROR, __VA_ARGS__)

#endif