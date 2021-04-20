#ifndef CSV_H_
#define CSV_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ABERTURA_1 21 
#define ABERTURA_2 22 
#define ABERTURA_3 26 
#define ABERTURA_4 27 
#define ABERTURA_5 28 
#define ABERTURA_6 29 
#define PRESENCA_1 6 
#define PRESENCA_2 25 
#define ALARM_TOGGLE 42

#define AR_1 23
#define AR_2 24
#define LAMPADA_1 0
#define LAMPADA_2 1
#define LAMPADA_3 3
#define LAMPADA_4 2

extern FILE* csvFile;

int startCSV();
void closeCSV();
void writeCurrentDate();
void registerUserEvent(int id, int status);
void registerAlarmEvent(int id);

#endif