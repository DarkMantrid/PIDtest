#ifndef SERVO_H_
#define SERVO_H_

#include "pid.h"
#include "tof_sensor.h"

struct servo
{
	struct pid pid;
	struct tof_sensor left_sensor;
	struct tof_sensor right_sensor;
};

/********************************************************************************
* servo_init:	Initierar servo motor med angivna parametrar.
* 
*				- self
*				- target_angle
*				- angle_min		(0 = helt åt vänster)
*				- angle_max		(100 = helt åt höger)
*				- input_min		(lägsta tillåtna insignal)
*				- input_max		(högsta tillåtna insignal)
*				- kp			(förstärkningsfaktor för PID-regs P-del.
*				- ki			(förstärkningsfaktor för PID-regs I-del.
*				- kd			(förstärkningsfaktor för PID-regs D-del.
********************************************************************************/
static inline void servo_init(struct servo* self,
							  const double target_angle,
							  const double angle_min,
							  const double angle_max,
							  const double input_min,
						      const double input_max,
							  const double kp,
							  const double ki,
							  const double kd)
{
	pid_init(&self->pid, target_angle, angle_min, angle_max, kp, ki, kd);
	tof_sensor_init(&self->left_sensor, input_min, input_max);
	tof_sensor_init(&self->right_sensor, input_min, input_max);
	return;
}

static inline double servo_target(const struct servo* self)
{
	return self->pid.target;
}

static inline double servo_input(const struct servo* self)
{
	return self->pid.input;
}

static inline double servo_output(const struct servo* self)
{
	return self->pid.output;
}

/********************************************************************************
* servo_input_range:
********************************************************************************/
static inline double servo_input_range(const struct servo* self)
{
	return tof_sensor_range(&self->left_sensor);
}

static inline double servo_input_differens(const struct servo* self)
{
	return self->left_sensor.val - self->right_sensor.val;
}

static inline double servo_absolute_angle(const struct servo* self)
{
	return (servo_input_differens(self) + servo_input_range(self) / 2);
}

static inline double servo_mapped_input(const struct servo* self)
{
	const double normalized_input = servo_absolute_angle(self) / 1023.0;
	return normalized_input * 180.0;
}

static inline void servo_print(const struct servo* self)
{
	printf("----------------------------------------------------------------------------------------------------\n");
	printf("Target angle: %.1f degrees\n", servo_target(self));
	printf("Input angle: %.1f degrees\n", servo_mapped_input(self));
	printf("Output angle: %.1f degrees\n", servo_output(self));

	const double relative_angle = servo_output(self) - servo_target(self);

	if (relative_angle > 0)
	{
		printf("Servo angled %.1f degrees to the right\n", relative_angle);
	}
	else if (relative_angle < 0)
	{
		printf(" Servo angled %.1f degrees to the left\n", -relative_angle);
	}
	else
	{
		printf("Servo angled right at the target\n");
	}

	printf("----------------------------------------------------------------------------------------------------\n\n");
}

static inline void servo_run(struct servo* self)
{
	printf("Enter value for left TOF sensor: \n");
	tof_sensor_read(&self->left_sensor);

	printf("Enter value for right TOF sensor: \n");
	tof_sensor_read(&self->right_sensor);

	pid_regulate(&self->pid, servo_mapped_input(self));
	servo_print(self);
}

#endif
