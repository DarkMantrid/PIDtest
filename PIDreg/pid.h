#ifndef PID_H_
#define PID_H_

#include <stdio.h>
#include <stdlib.h>

struct pid
{
	double target;
	double output;
	double input;
	double kp;
	double ki;
	double kd;
	double last_error;
	double delta;		 /* Derivata av föregående fel */
	double integrate;	 /* integral av föregående fel */
	double output_min;
	double output_max;
};

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
			  const double kd);



/********************************************************************************
* pid_regulate: Regulates output value of PID controller on the basis of new input.
*
*           - new_input: New input value of PID controller.
********************************************************************************/
void pid_regulate(struct pid* self,
				  const double new_input);

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
			   const double kd);


/********************************************************************************
* pid_print: Prints target value, input, output and last measured error for PID
*        controller. The output is printed in the terminal with one decimal
*        as default.
*
*        - ostream     : Reference to output stream used (default = std::cout).
*        - num_decimals: Number of printed decimals per parameter (default = 1).
********************************************************************************/
void pid_print(const struct pid* self,
			   FILE* ostream);




#endif 
