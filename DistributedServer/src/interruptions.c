#include "interruptions.h"

void pin25RisingInterruption() {
	sendPinUpdate(25, 1);
}
void pin25FallingInterruption() {
	sendPinUpdate(25, 0);
}

void pin26RisingInterruption() {
	sendPinUpdate(26, 1);
}
void pin26FallingInterruption() {
	sendPinUpdate(26, 0);
}

void pin05RisingInterruption() {
	sendPinUpdate(5, 1);
}
void pin05FallingInterruption() {
	sendPinUpdate(5, 0);
}

void pin06RisingInterruption() {
	sendPinUpdate(6, 1);
}
void pin06FallingInterruption() {
	sendPinUpdate(6, 0);
}

void pin12RisingInterruption() {
	sendPinUpdate(12, 1);
}
void pin12FallingInterruption() {
	sendPinUpdate(12, 0);
}

void pin16RisingInterruption() {
	sendPinUpdate(16, 1);
}
void pin16FallingInterruption() {
	sendPinUpdate(16, 0);
}

void pin20RisingInterruption() {
	sendPinUpdate(20, 1);
}
void pin20FallingInterruption() {
	sendPinUpdate(20, 0);
}

void pin21RisingInterruption() {
	sendPinUpdate(21, 1);
}
void pin21FallingInterruption() {
	sendPinUpdate(21, 0);
}