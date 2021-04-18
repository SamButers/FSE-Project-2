#include "interruptions.h"

void pin25Interruption() {
	if(digitalRead(6))
		sendPinUpdate(25, 1);
	else
		sendPinUpdate(25, 0);
}

void pin26Interruption() {
	if(digitalRead(25))
		sendPinUpdate(26, 1);
	else
		sendPinUpdate(26, 0);
}

void pin05Interruption() {
	if(digitalRead(21))
		sendPinUpdate(5, 1);
	else
		sendPinUpdate(5, 0);
}

void pin06Interruption() {
	if(digitalRead(22))
		sendPinUpdate(6, 1);
	else
		sendPinUpdate(6, 0);
}

void pin12Interruption() {
	if(digitalRead(26))
		sendPinUpdate(12, 1);
	else
		sendPinUpdate(12, 0);
}

void pin16Interruption() {
	if(digitalRead(27))
		sendPinUpdate(16, 1);
	else
		sendPinUpdate(16, 0);
}

void pin20Interruption() {
	if(digitalRead(28))
		sendPinUpdate(20, 1);
	else
		sendPinUpdate(20, 0);
}

void pin21Interruption() {
	if(digitalRead(29))
		sendPinUpdate(21, 1);
	else
		sendPinUpdate(21, 0);
}
