#ifndef __CATERPILLAR_H
#define __CATERPILLAR_H

#include "stm32f1xx_hal.h"

#define CATERPILLAR_MAX_SPEED	1.11	// [mm/s]
#define CATERPILLAR_MAX_RPM		3000	// rpm
#define CATERPILLAR_TREAD	  	1.40    // [m]

#define CAT_VAL_LIMIT(val, min, max) \
  do                                 \
  {                                  \
    if ((val) <= (min))              \
    {                                \
      (val) = (min);                 \
    }                                \
    else if ((val) >= (max))         \
    {                                \
      (val) = (max);                 \
    }                                \
  } while (0)

struct caterpillar_structure
{
	float wheel_tread;
};

struct caterpillar_speed
{
	float vx;
	float vy;
	float vw;
};

struct caterpillar_gyro
{
	float yaw_angle;
	float yaw_rate;
};

struct caterpillar
{
	struct caterpillar_structure param;
	struct caterpillar_speed speed;
	int16_t caterpillar_rpm[2];
};

void caterpillar_calculate(struct caterpillar *catp);
void caterpillar_set_speed(struct caterpillar *catp, float vx, float vy, float vw);

#endif // __CATERPILLAR_H
