#ifndef TOF_SENSOR_H_
#define TOF_SENSOR_H_

#include <stdio.h>
#include <stdlib.h>

static void readline(char* s, const int size)
{
	fgets(s, size, stdin);
	printf("\n");

	for (char* i = s; *i; ++i)
	{
		if (*i == '\n')
		{
			*i = '\0';
		}
	}
	return;
}

static double get_double(void)
{
	char s[20] = { '\0' };
	readline(s, sizeof(s));

	for (char* i = s; *i; ++i)
	{
		if (*i == ',')
		{
			*i = '.';
		}
	}
	return atof(s); // Typomvandlar text till tal.
}

/********************************************************************************
 * tof_sensor:	Struct för implementering av TOF-sensor, som känner av
 *				avstånd mellan angivet min- & maxvärden.
 ********************************************************************************/

struct tof_sensor
{
	double val;
	double min_val;
	double max_val;
};

/********************************************************************************
 * tof_sensor_init:	Initierar TOF-sensor med angivet min- och maxvärde
 * 
 *					-self
 *					-min_val
 *					-max_val
 ********************************************************************************/

static inline void tof_sensor_init(struct tof_sensor* self,
								   const double min_val,
								   const double max_val)
{
	self->val = 0;
	self->min_val = min_val;
	self->max_val = max_val;
	return;
}

/********************************************************************************
 * tof_sensor_range:	Retrunerar värdet av tof-sensorns insignal,
 *						dvs differensen mellan max/min.
 *
 ********************************************************************************/

static inline double tof_sensor_range(const struct tof_sensor* self)
{
	return self->max_val - self->min_val;
}

/********************************************************************************
 * tof_sensor_read:		Läser in ett sensorvärde från terminalen och kontrollerar
 *						att det ligger mellan angiet min/max värde.	
 *						Annars justering
 *						
 *
 ********************************************************************************/
static inline void tof_sensor_read(struct tof_sensor* self)
{
	self->val = get_double();

	if (self->val > self->max_val)
	{
		self->val = self->max_val;
	}
	else if (self->val < self->min_val)
	{
		self->val = self->min_val;
	}
	return;
}

#endif 