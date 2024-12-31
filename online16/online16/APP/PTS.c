
#define F_L  M1
#define F_R  M2
#define B_L  M3
#define B_4  M4

#include "MOTOR_int.h"


PTS_Forward(void)
{
	MOTOR_CW(F_L);
	MOTOR_CW(B_L);
}