#include "csv.h"

FILE* csvFile;

int startCSV() {
	csvFile = fopen("./data.csv", "w");
	fprintf(csvFile, "DATE,EVENT,EVENT_DATA\n");
	
	if(csvFile == NULL)
		return 1;
	
	return 0;
}

void writeCurrentDate() {
	time_t currentTime;
	struct tm *timeInfo;
	
	time(&currentTime);
	timeInfo = localtime(&currentTime);
	
	fprintf(csvFile, "%02d/%02d/%d %02d:%02d:%02d,", timeInfo->tm_mday, timeInfo->tm_mon, 1900 + timeInfo->tm_year, timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
}
void registerUserEvent(int id, int status) {
	writeCurrentDate();
	fprintf(csvFile, "USER_ACTION,");
	
	switch(id) {
		case AR_1:
			fprintf(csvFile, "AR CONDICIONADO 1 ");
			break;
		case AR_2:
			fprintf(csvFile, "AR CONDICIONADO 2 ");
			break;
		case LAMPADA_1:
			fprintf(csvFile, "LAMPADA 1 ");
			break;
		case LAMPADA_2:
			fprintf(csvFile, "LAMPADA 2 ");
			break;
		case LAMPADA_3:
			fprintf(csvFile, "LAMPADA 3 ");
			break;
		case LAMPADA_4:
			fprintf(csvFile, "LAMPADA 4 ");
			break;
		case ALARM_TOGGLE:
			fprintf(csvFile, "ALARM ");
			break;
		default:
			fprintf(csvFile, "NULL\n");
			return;
	}
	
	if(status)
		fprintf(csvFile, "ON\n");
	else
		fprintf(csvFile, "OFF\n");
}

void registerAlarmEvent(int id) {
	writeCurrentDate();
	fprintf(csvFile, "ALARM,");
	
	switch(id) {
		case ABERTURA_1:
			fprintf(csvFile, "ABERTURA 1\n");
			break;
		case ABERTURA_2:
			fprintf(csvFile, "ABERTURA 2\n");
			break;
		case ABERTURA_3:
			fprintf(csvFile, "ABERTURA 3\n");
			break;
		case ABERTURA_4:
			fprintf(csvFile, "ABERTURA 4\n");
			break;
		case ABERTURA_5:
			fprintf(csvFile, "ABERTURA 5\n");
			break;
		case ABERTURA_6:
			fprintf(csvFile, "ABERTURA 6\n");
			break;
		case PRESENCA_1:
			fprintf(csvFile, "PRESENCA 1\n");
			break;
		case PRESENCA_2:
			fprintf(csvFile, "PRESENCA 2\n");
			break;
		default:
			fprintf(csvFile, "NULL\n");
			return;
	}
}

void closeCSV() {
	fclose(csvFile);
}