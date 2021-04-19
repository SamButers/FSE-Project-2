#include "interruptions.h"

void pin25Interruption() {
	if(digitalRead(6))
		sendPinUpdate(6, 1);
	else
		sendPinUpdate(6, 0);
}

void pin26Interruption() {
	if(digitalRead(25))
		sendPinUpdate(25, 1);
	else
		sendPinUpdate(25, 0);
}

void pin05Interruption() {
	if(digitalRead(21))
		sendPinUpdate(21, 1);
	else
		sendPinUpdate(21, 0);
}

void pin06Interruption() {
	if(digitalRead(22))
		sendPinUpdate(22, 1);
	else
		sendPinUpdate(22, 0);
}

void pin12Interruption() {
	if(digitalRead(26))
		sendPinUpdate(26, 1);
	else
		sendPinUpdate(26, 0);
}

void pin16Interruption() {
	if(digitalRead(27))
		sendPinUpdate(27, 1);
	else
		sendPinUpdate(27, 0);
}

void pin20Interruption() {
	if(digitalRead(28))
		sendPinUpdate(28, 1);
	else
		sendPinUpdate(28, 0);
}

void pin21Interruption() {
	if(digitalRead(29))
		sendPinUpdate(29, 1);
	else
		sendPinUpdate(29, 0);
}
