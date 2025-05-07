#ifndef LOGGER_C
#define LOGGER_C

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "logger.h"

char* log_level_color[] = {GREEN, BLUE, YELLOW, RED};
char* log_level_name[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

void log_init(const char *filename, log_level level, shell_conf_t shellEnable){


    logger.logFile = fopen(filename, "a+");
    if (logger.logFile == NULL){
        perror("Error during open logfile: ");
        exit(EXIT_FAILURE);
    }

    logger.current_level = level;

    logger.shellEnable = shellEnable;

}


void log_set_level(log_level level){

    logger.current_level = level;

}


void log_message(const log_level level, const char *formatString, ...){

    time_t now;
    struct tm *info;
    char buffer[80];

    time(&now); // tempo attuale
    info = localtime(&now); // convertsione al formato locale

    strftime(buffer, sizeof(buffer), logger.timeStringFormat, info);


    va_list args;
    va_start(args, formatString); // specifico l'ultimo parametro con nome

    if (logger.shellEnable){
        // if(logger.current_level )
        printf("[%s] %s ", buffer, log_level_color[level]); // imposto il colore

        vprintf(formatString, args);  

        printf("\033[0;37m \n"); // resetto il colore
    }

    if (logger.logFile != NULL){

        va_list args_copy;
        va_copy(args_copy, args); // Copia la lista prima di riutilizzarla

        fprintf(logger.logFile, "[%s] (%s): ", buffer, log_level_name[level]);
        vfprintf(logger.logFile, formatString, args_copy);
        fprintf(logger.logFile, "\n"); // newline manuale

        va_end(args_copy);

    }else{
        printf("ERROR LOGGER FILE\n");
    }

    va_end(args);

}


void log_close(){

    fclose(logger.logFile);

}


logger_t logger = {
    .logFile          = NULL,
    .current_level    = LOG_DEBUG,
    .shellEnable      = SHELL_DISABLE,
    .timeStringFormat = "%d-%m-%Y %H:%M:%S",
    .init             = log_init,
    .set_level        = log_set_level,
    .message          = log_message,
    .close            = log_close
};

#endif