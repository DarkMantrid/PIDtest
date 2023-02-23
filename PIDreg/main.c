#include "pid.h"
#include "tof_sensor.h"

int main(void)
{
	struct pid pid1;
	struct tof_sensor tof1;

	pid_init(&pid1, 10, 0, 20, 1, 0.01, 0.1);
	tof_sensor_init(&tof1, 0, 20);
	
	while (1)
	{
		printf("Enter value for TOF-sensor: \n");
		tof_sensor_read(&tof1);
		pid_regulate(&pid1, tof1.val);
		pid_print(&pid1, 0);
	}

	return 0;
}