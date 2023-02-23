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

#endif
