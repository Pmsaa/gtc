/****************************************************************************
 *  Copyright (C) 2020 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef __SBUS_H__
#define __SBUS_H__

#include "device.h"

#define SMALL_BOUNDARY	400
#define BIG_BOUNDARY	1500

#define RC_DEV_MAX		1722
#define RC_DEV_MIN		282

#define RC_E5_UP		(1 << 0U)
#define RC_E5_MID		(1 << 1U)
#define RC_E5_DOWN		(1 << 2U)

#define RC_G6_LEFT		(1 << 3U)
#define RC_G6_MID		(1 << 4U)
#define RC_G6_RIG		(1 << 5U)

#define RC_H7_LEFT		(1 << 6U)
#define RC_H7_MID		(1 << 7U)
#define RC_H7_RIG		(1 << 8U)

#define RC_F8_UP		(1 << 9U)
#define RC_F8_MID		(1 << 10U)
#define RC_F8_DOWN		(1 << 11U)

typedef struct rc_device *rc_device_t;
typedef struct rc_info *rc_info_t;

// #pragma pack(push, 1)

/**
  * @brief  remote control information
  */
struct rc_info
{
    /* rocker channel information */
    int16_t x2;		// left 282;default 1002;right 1722;
    int16_t y2;		// up 282;default 1002;down 1722;
    int16_t y1;		// up 1722;default 1002;down 282;
    int16_t x1;		// left 282;default 1002;right 1722;

	// 400  1500
    uint16_t _e5;	// down 1722
    uint16_t g6;	// left 282; mid 1002; right 1722
	uint16_t _h7;	// left 1722
	uint16_t _f8;	// down 1722
	
	uint16_t a9;	// default 282;press 1722;long press 1002
	uint16_t b10;	// default 282;press 1722;long press 1002
	uint16_t c11;	// default 282;press 1722;long press 1002
	uint16_t d12;	// default 282;press 1722;long press 1002
	
};

struct rc_device
{
    struct device parent;
    struct rc_info rc_info;
    struct rc_info last_rc_info;
    uint16_t state;
    void (*get_data)(rc_device_t, uint8_t *);
    void (*get_state)(rc_device_t);
};

int32_t rc_device_register(rc_device_t rc_dev, const char *name);
int32_t rc_device_date_update(rc_device_t rc_dev, uint8_t *buff);
int32_t rc_device_get_state(rc_device_t rc_dev, uint16_t state);
rc_info_t rc_device_get_info(rc_device_t rc_dev);
rc_device_t rc_device_find(const char *name);


#endif // __DBUS_H__
