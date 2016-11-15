/**
 * @file        RasPi_ctrlRailIo.c
 * @brief       Raspberry PiのGPIO/PWMによる鉄道模型制御 進行方向/出力制御
 * @author      Keitetsu
 * @date        2016/10/02
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>
#include <wiringPi.h>

#include "RasPi_Rail.h"
#include "RasPi_ctrlRailIo.h"


int RasPi_ctrlRailIo(
        RAIL_IO_T target,
        int direction_req,
        int pwm_duty_req)
{
    int forward_value, backward_value, pwm_duty;
    int result = RAIL_SUCCESS;

#ifdef _DEBUG_RASPI_CTRLRAILIO
    printf("Call:   RasPi_ctrlRailIo\n");
#endif

#ifdef _DEBUG_RASPI_CTRLRAILIO
    printf("  Direction: %4d\n", direction_req);
    printf("  Speed:     %4d\n", pwm_duty_req);
#endif

    switch(direction_req) {
        case RAIL_STOP:
            forward_value = RAIL_POWER_OFF;
            backward_value = RAIL_POWER_OFF;
            break;
        case RAIL_FORWARD:
            forward_value = RAIL_POWER_ON;
            backward_value = RAIL_POWER_OFF;
            break;
        case RAIL_BACKWARD:
            forward_value = RAIL_POWER_OFF;
            backward_value = RAIL_POWER_ON;
            break;
        case RAIL_BRAKE:
            forward_value = RAIL_POWER_ON;
            backward_value = RAIL_POWER_ON;
            break;
        default:
            forward_value = RAIL_POWER_OFF;
            backward_value = RAIL_POWER_OFF;
            result |= RAIL_INVALID_DIRECTION;
            break;
    }

    if(pwm_duty_req >= target.pwm.min && pwm_duty_req <= target.pwm.max) {
        pwm_duty = pwm_duty_req;
    }
    else {
        pwm_duty = target.pwm.min;
        result |= RAIL_INVALID_PWM_DUTY;
    }

    digitalWrite(target.forward.port, forward_value);
    digitalWrite(target.backward.port, backward_value);
    pwmWrite(target.pwm.port, pwm_duty);

#ifdef _DEBUG_RASPI_CTRLRAILIO
    printf("Return: RasPi_ctrlRailIo: 0x%08x\n", result);
#endif

    return result;
}

