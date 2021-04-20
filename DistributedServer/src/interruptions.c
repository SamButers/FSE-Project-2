#include "interruptions.h"

void generalInterruption(int pin) {
	int pinValue = digitalRead(pin);
	
	if(pinValue)
		sendPinUpdate(pin, 1);
	else
		sendPinUpdate(pin, 0);
}

void pin25Interruption() {
	generalInterruption(6);
}

void pin26Interruption() {
	generalInterruption(25);
}

void pin05Interruption() {
	generalInterruption(21);
}

void pin06Interruption() {
	generalInterruption(22);
}

void pin12Interruption() {
	generalInterruption(26);
}

void pin16Interruption() {
	generalInterruption(27);
}

void pin20Interruption() {
	generalInterruption(28);
}

void pin21Interruption() {
	generalInterruption(29);
}
