#include "pid.h"
#include "tof_sensor.h"
#include "servo.h"

int main(void)
{
	struct pid pid1;
	struct tof_sensor tof1;
	struct servo servo1;

	servo_init(&servo1, 90, 30, 150, 0, 1023, 1, 0.01, 0.1);

	
	while (1)
	{
		servo_run(&servo1);
	}

	return 0;
}