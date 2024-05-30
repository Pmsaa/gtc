#include "caterpillar.h"

#define LOG_TAG "caterpillar"
#define LOG_OUTPUT_LEVEL LOG_INFO
#include "log.h"

void caterpillar_calculate(struct caterpillar *catp)
{
    float wheel_rpm[2] = {0};
	
    wheel_rpm[0] = catp->speed.vx * 1.11f + catp->param.wheel_tread / 2 * catp->speed.vw * 1.11f;	// m/s	
    wheel_rpm[1] = catp->speed.vx * 1.11f - catp->param.wheel_tread / 2 * catp->speed.vw * 1.11f;

	wheel_rpm[0] = wheel_rpm[0] / CATERPILLAR_MAX_SPEED * 100;		// percentage
	wheel_rpm[1] = wheel_rpm[1] / CATERPILLAR_MAX_SPEED * 100;		// percentage

	CAT_VAL_LIMIT(wheel_rpm[0], -100, 100);
	CAT_VAL_LIMIT(wheel_rpm[1], -100, 100);
	
    catp->caterpillar_rpm[0] = (int16_t)wheel_rpm[0];
    catp->caterpillar_rpm[1] = (int16_t)wheel_rpm[1];
}

void caterpillar_set_speed(struct caterpillar *catp, float vx, float vy, float vw)
{
    catp->speed.vx = vx;
    catp->speed.vy = vy;
    catp->speed.vw = vw;
}
