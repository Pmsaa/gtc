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

#include "sbus.h"
#include "sys.h"

#define LOG_TAG "drv.sbus"
#define LOG_OUTPUT_LEVEL  LOG_INFO
#include "log.h"

static void get_t12_data(rc_device_t rc_dev, uint8_t *buff);
static void get_t12_state(rc_device_t rc_dev);

int32_t rc_device_register(rc_device_t rc_dev, const char *name)
{
    device_assert(rc_dev != NULL);

    ((device_t)rc_dev)->type = DEVICE_SBUS;

    rc_dev->get_data = get_t12_data;
    rc_dev->get_state = get_t12_state;

    device_init(&(rc_dev->parent), name);

    return E_OK;
}

int32_t rc_device_date_update(rc_device_t rc_dev, uint8_t *buff)
{
    if (rc_dev != NULL)
    {
        rc_dev->get_data(rc_dev, buff);
        rc_dev->get_state(rc_dev);
        return E_OK;
    }
    return -E_UNREGISTERED;
}

int32_t rc_device_get_state(rc_device_t rc_dev, uint16_t state)
{
    var_cpu_sr();

    enter_critical();

    if (rc_dev != NULL)
    {
        if ((rc_dev->state & state) == state)
        {
            exit_critical();
            return E_OK;
        }
        else
        {
            exit_critical();
            return -E_NOSTATE;
        } 
    }

    exit_critical();

    return -E_UNREGISTERED;
}

rc_info_t rc_device_get_info(rc_device_t rc_dev)
{
    device_assert(rc_dev != NULL);

    return &(rc_dev->rc_info);
}


static void get_t12_data(rc_device_t rc_dev, uint8_t *buff)
{
	if(buff[0] != 0x0f)
		return ;
	
    memcpy(&(rc_dev->last_rc_info), &rc_dev->rc_info, sizeof(struct rc_info));

    rc_info_t rc = &rc_dev->rc_info;

    rc->x2  = ((int16_t)buff[ 1] >> 0 | ((int16_t)buff[ 2] << 8 )) & 0x07FF;
	rc->x2 -= 1002;
    rc->y2  = ((int16_t)buff[ 2] >> 3 | ((int16_t)buff[ 3] << 5 )) & 0x07FF;
	rc->y2 -= 1002;
    rc->y1  = ((int16_t)buff[ 3] >> 6 | ((int16_t)buff[ 4] << 2 )  | (int16_t)buff[ 5] << 10 ) & 0x07FF;
	rc->y1 -= 1002;
    rc->x1  = ((int16_t)buff[ 5] >> 1 | ((int16_t)buff[ 6] << 7 )) & 0x07FF;
	rc->x1 -= 1002;

    rc->_e5 = ((int16_t)buff[ 6] >> 4 | ((int16_t)buff[ 7] << 4 )) & 0x07FF;
    rc->g6  = ((int16_t)buff[ 7] >> 7 | ((int16_t)buff[ 8] << 1 )  | (int16_t)buff[9] <<  9 ) & 0x07FF;
    rc->_h7 = ((int16_t)buff[ 9] >> 2 | ((int16_t)buff[10] << 6 )) & 0x07FF;
    rc->_f8 = ((int16_t)buff[10] >> 5 | ((int16_t)buff[11] << 3 )) & 0x07FF;
    
    rc->a9  = ((int16_t)buff[12] >> 0 | ((int16_t)buff[13] << 8 )) & 0x07FF;
    rc->b10 = ((int16_t)buff[13] >> 3 | ((int16_t)buff[14] << 5 )) & 0x07FF;
	rc->c11 = ((int16_t)buff[14] >> 6 | ((int16_t)buff[15] << 2 )  | (int16_t)buff[16] << 10 ) & 0x07FF;
	rc->d12 = ((int16_t)buff[16] >> 1 | ((int16_t)buff[17] << 7 )) & 0x07FF;
//    memset(pstRcCmd, 0, sizeof(struct rc_cmd));
}

static void get_t12_state(rc_device_t rc_dev)
{
	// ----------------------------------------------
	if(rc_dev->rc_info._e5 < SMALL_BOUNDARY)
	{
		rc_dev->state |= RC_E5_UP;
		rc_dev->state &= ~RC_E5_DOWN;
		rc_dev->state &= ~RC_E5_MID;
	}
	else if(rc_dev->rc_info._e5 > BIG_BOUNDARY)
	{
		rc_dev->state &= ~RC_E5_UP;
		rc_dev->state &= ~RC_E5_MID;
		rc_dev->state |= RC_E5_DOWN;
	}
	else 
	{
		rc_dev->state &= ~RC_E5_UP;
		rc_dev->state |= RC_E5_MID;
		rc_dev->state &= ~RC_E5_DOWN;
	}
	// ----------------------------------------------
	if(rc_dev->rc_info.g6 < SMALL_BOUNDARY)
	{
		rc_dev->state |= RC_G6_LEFT;
		rc_dev->state &= ~RC_G6_MID;
		rc_dev->state &= ~RC_G6_RIG;
	}
	else if(rc_dev->rc_info.g6 > BIG_BOUNDARY)
	{
		rc_dev->state &= ~RC_G6_LEFT;
		rc_dev->state &= ~RC_G6_MID;
		rc_dev->state |= RC_G6_RIG;
	}
	else
	{
		rc_dev->state &= ~RC_G6_LEFT;
		rc_dev->state |= RC_G6_MID;
		rc_dev->state &= ~RC_G6_RIG;
	}
	// -----------------------------------------------
	if(rc_dev->rc_info._h7 < SMALL_BOUNDARY)
	{
		rc_dev->state &= ~RC_H7_LEFT;
		rc_dev->state &= ~RC_H7_MID;
		rc_dev->state |= RC_H7_RIG;
	}
	else if(rc_dev->rc_info._h7 > BIG_BOUNDARY)
	{
		rc_dev->state |= RC_H7_LEFT;
		rc_dev->state &= ~RC_H7_MID;
		rc_dev->state &= ~RC_H7_RIG;
	}
	else
	{
		rc_dev->state &= ~RC_H7_LEFT;
		rc_dev->state |= RC_H7_MID;
		rc_dev->state &= ~RC_H7_RIG;
	}
	// --------------------------------------------
	if(rc_dev->rc_info._f8 < SMALL_BOUNDARY)
	{
		rc_dev->state |= RC_F8_UP;
		rc_dev->state &= ~RC_F8_MID;
		rc_dev->state &= ~RC_F8_DOWN;
	}
	if(rc_dev->rc_info._f8 > BIG_BOUNDARY)
	{
		rc_dev->state &= ~RC_F8_UP;
		rc_dev->state &= ~RC_F8_MID;
		rc_dev->state |= RC_F8_DOWN;
	}
	else
	{
		rc_dev->state &= ~RC_F8_UP;
		rc_dev->state |= RC_F8_MID;
		rc_dev->state &= ~RC_F8_DOWN;
	}
	return;
}
