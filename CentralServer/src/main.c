#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ncurses.h>
#include "socket.h"
#include "pin.h"
#include "alarm.h"

int ALARM;

int initDevices() {
	int error, attempts = 0;

	while(1) {
		error = initClient();
		
		if(error)
			attempts++;
		else
			break;
		
		if(attempts >= 5) {
			printf("Client socket initialization error #%d\n", error);
			printf("%s\n", strerror(errno));
			return 1;
		}
		
		sleep(1);
	}
	
	if((error = initServer())) {
		printf("Server socket initialization error #%d\n", error);
		printf("%s\n", strerror(errno));
		return 1;
	}
	
	initscr();
	noecho();
	nodelay(stdscr, 1);
	
	return 0;
}

int checkInput() {
	int input = getch();
	
	switch(input) {
		case 10:
			return 1;
		default:
			return 0;
	}
}

void displayInformation(BMEData *bmeData) {
	clear();
	
	printw("================-BME Data-================\n");
	printw("Temperature: %f\n", bmeData->temperature);
	printw("Humidity: %f\n", bmeData->humidity);
	
	printw("================-PIN Data-================\n");
	printw("Sensor Abertura 01 (Porta Cozinha): %d\n", INPUT_PINS[0]);
	printw("Sensor Abertura 02 (Janela Cozinha): %d\n", INPUT_PINS[1]);
	printw("Sensor Abertura 03 (Porta Sala): %d\n", INPUT_PINS[2]);
	printw("Sensor Abertura 04 (Janela Sala): %d\n", INPUT_PINS[3]);
	printw("Sensor Abertura 05 (Janela Quarto 01): %d\n", INPUT_PINS[4]);
	printw("Sensor Abertura 06 (Janela Quarto 02): %d\n", INPUT_PINS[5]);
	printw("Sensor de Presença 01 (Sala): %d\n", INPUT_PINS[6]);
	printw("Sensor de Presença 02 (Cozinha): %d\n\n", INPUT_PINS[7]);
	
	printw("Ar-Condicionado 01 (Quarto 01)\n", OUTPUT_PINS[0]);
	printw("Ar-Condicionado 02 (Quarto 02)\n", OUTPUT_PINS[3]);
	printw("Lâmpada 01 (Cozinha)\n", OUTPUT_PINS[1]);
	printw("Lâmpada 02 (Sala)\n", OUTPUT_PINS[2]);
	printw("Lâmpada 03 (Quarto 01)\n", OUTPUT_PINS[5]);
	printw("Lâmpada 04 (Quarto 02)\n", OUTPUT_PINS[4]);
	
	printw("=================-ALARM-=================\n");
	printw("Alarm: %d\n", ALARM);
	
	printw("================---- -----================\n");
	printw("Press Enter to go to actions menu...\n");
}

void handleUserAction(int action) {
	clear();
	
	switch(action) {
		case 49:
			printw("=================-DEVICE-=================\n");
			printw("1. Lâmpada 01 (Cozinha)\n");
			printw("2. Lâmpada 02 (Sala)\n");
			printw("3. Lâmpada 03 (Quarto 01)\n");
			printw("4. Lâmpada 04 (Quarto 02)\n");
			printw("5. Ar-Condicionado 01 (Quarto 01)\n");
			printw("6. Ar-Condicionado 02 (Quarto 02)\n");
			
			int action = getch();
			
			int index = action - 49;
			OUTPUT_PINS[index] = sendPinUpdate(getOutputPinFromIndex(index));
			break;
		case 50:
			toggleAlarm();
			
		default:
			return;
	}
}

void handleUserInput() {
	clear();
	echo();
	nodelay(stdscr, 0);
	
	printw("==============-CHOOSE ACTION-==============\n");
	printw("1. Activate/Deactivate device\n");
	printw("2. Turn on/off alarm\n");
	
	printw("================---- -----================\n");
	
	int input = getch();
	handleUserAction(input);
	
	noecho();
	nodelay(stdscr, 1);
}

void mainLoop() {
	BMEData bmeData;
	
	while(1) {
		if(checkInput()) {
			handleUserInput();
			continue;
		}
		
		getBMEData(&bmeData);
		displayInformation(&bmeData);

		sleep(1);
	}
}

int main() {
	if(initDevices())
		return 0;
	
	mainLoop();
	
	return 0;
}