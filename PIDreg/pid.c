#include "pid.h"

/********************************************************************************
* pid_init: Initiates PID controller with specified parameters.
*
*       - target    : Desired output value.
*       - output_min: Minimum output value (default = 0).
*       - output_max: Maximum output value (default = 180).
*       - kp        : Proportional constant (default = 1.0).
*       - ki        : Integrate constant (default = 0.01).
*       - kd        : Derivate constant (default = 0.1).
********************************************************************************/
void pid_init(struct pid* self,
			  const double target,
			  const double output_min,
			  const double output_max,
			  const double kp,
			  const double ki,
			  const double kd)
{
	self->target = target;
	self->output = 0;
	self->input = 0;
	self->kp = kp;
	self->ki = ki;
	self->kd = kd;
	self->output_min = output_min;
	self->output_max = output_max;
	self->last_error = 0;
	self->integrate = 0;
	self->delta = 0;
	return;
}



/********************************************************************************
* pid_regulate: Regulates output value of PID controller on the basis of new input.
*
*           - new_input: New input value of PID controller.
********************************************************************************/
void pid_regulate(struct pid* self,
				  const double new_input)
{
	const double error = self->target - new_input;
	self->input = new_input;
	self->delta = error - self->last_error;
	self->integrate += error;
	
	self->output = self->target + self->kp * error + self->ki * self->integrate + self->kd * self->delta;

	if (self->output < self->output_min)
	{
		self->output = self->output_min;
	}
	else if (self->output > self->output_max)
	{
		self->output = self->output_max;
	}
	self->last_error = error;

	return;

}

/********************************************************************************
 * pid_controller: Initiates PID controller with specified parameters.
 *
 *                 - target    : Desired output value.
 *                 - output_min: Minimum output value (default = 0).
 *                 - output_max: Maximum output value (default = 180).
 *                 - kp        : Proportional constant (default = 1.0).
 *                 - ki        : Integrate constant (default = 0.01).
 *                 - kd        : Derivate constant (default = 0.1).
 ********************************************************************************/
pid_controller(struct pid* self,
			   const double target,
			   const double output_min,
			   const double output_max,
			   const double kp,
			   const double ki,
			   const double kd)
{

}


/********************************************************************************
* pid_print: Prints target value, input, output and last measured error for PID
*			 controller. The output is printed in the terminal with one decimal
*		     as default.
********************************************************************************/
void pid_print(const struct pid* self,
			   FILE* ostream)
{
	if (!ostream) ostream = stdout;
	fprintf(ostream, "--------------------------------------------------------------------\n");

	fprintf(ostream, "Target:\t\t%.1f\n", self->target);
	fprintf(ostream, "Input:\t\t%.1f\n", self->input);
	fprintf(ostream, "Output:\t\t%.1f\n", self->output);
	fprintf(ostream, "Error:\t\t%.1f\n", self->last_error);

	fprintf(ostream, "--------------------------------------------------------------------\n\n");
}