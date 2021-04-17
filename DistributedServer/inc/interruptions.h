#ifndef INTERRUPTIONS_H_
#define INTERRUPTIONS_H_

#include <wiringPi.h>
#include "socket.h"

void pin25RisingInterruption();
void pin25FallingInterruption();

void pin26RisingInterruption();
void pin26FallingInterruption();

void pin05RisingInterruption();
void pin05FallingInterruption();

void pin06RisingInterruption();
void pin06FallingInterruption();

void pin12RisingInterruption();
void pin12FallingInterruption();

void pin16RisingInterruption();
void pin16FallingInterruption();

void pin20RisingInterruption();
void pin20FallingInterruption();

void pin21RisingInterruption();
void pin21FallingInterruption();

#endif