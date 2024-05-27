#ifndef __CATERPILLAR_H
#define __CATERPILLAR_H

struct capterpillar_structure
{
	float wheel;
}

struct caterpillar_speed
{
	float vx;
	float vy;
	float vw;
}

struct caterpillar_gyro
{
	float yaw_angle;
	float yaw_rate;
}

struct catperpillar
{
	struct caterpillar_structure;
	struct caterpillar_speed;
	float capterpillar_rpm[2];
}

#endif // __CATERPILLAR_H
