#ifndef _DRV_H
#define _DRV_H

#include <windows.h>
#include "MEPCIOINI.H"
#include "MEPCIODEV.H"

int initMotionCard(double U, double V, double W, LIOISR TimerFunction);
int enableHDTimer(int interval);	// unit : ms
int disableHDTimer(void);
int closeMotionCard(void);
int putAxisValue(int axis, int increment);

#endif