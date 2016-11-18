/**
 * @file        RasPi_RailIo.c
 * @brief       Raspberry PiのGPIO/PWMによる鉄道模型制御 線路制御インタフェース設定
 * @author      Keitetsu
 * @date        2016/10/02
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>
#include <wiringPi.h>

#include "RasPi_Rail.h"
#include "RasPi_RailIo.h"


int RasPi_initRailIo(void)
{
    int result;
    int retval;

    result = RAIL_SUCCESS;
    retval = 0;

#ifdef _DEBUG_RASPI_RAILIO
    printf("Call:   RasPi_initRailIo\n");
#endif

    retval = wiringPiSetupGpio();
    if(retval == -1) {
#ifdef _DEBUG_RASPI_RAILIO
        printf("Error:  wiringPiSetupGpio\n");
#endif

        result = RAIL_FAILURE;
    }

#ifdef _DEBUG_RASPI_RAILIO
    printf("Return: RasPi_initRailIo: 0x%08x\n", result);
#endif

    return result;
}


int RasPi_configRailIo(RAIL_IO_T target)
{
    int direction;
    int pwm_duty;
    int result;
    int retval;
    
    result = RAIL_SUCCESS;
    retval = 0;

#ifdef _DEBUG_RASPI_RAILIO
    printf("Call:   RasPi_configRailIo\n");
#endif

#ifdef _DEBUG_RASPI_RAILIO
    printf("  Forward:  RasPi Port: %3d\n", target.forward.port);
    printf("  Backward: RasPi Port: %3d\n", target.backward.port);
    printf("  PWM:      RasPi Port: %3d\n", target.pwm.port);
    printf("            Divisor Value: %4d, Range: %4d (%4d - %4d)\n",
        target.pwm.divisor, target.pwm.range, target.pwm.min, target.pwm.max);
#endif

    direction = RAIL_STOP;
    pwm_duty = target.pwm.min;

    // GPIO設定
    pinMode(target.forward.port, target.forward.direction);
    pinMode(target.backward.port, target.backward.direction);

    // PWM設定
    pinMode(target.pwm.port, PWM_OUTPUT);
    pwmSetClock(target.pwm.divisor);
    pwmSetRange(target.pwm.range);
    pwmSetMode(PWM_MODE_MS);

    retval = RasPi_ctrlRailIo(target, direction, pwm_duty);
    result |= retval;
    if(retval != 0) {
#ifdef _DEBUG_RASPI_RAILIO
        printf("Error:  RasPi_ctrlRailIo\n");
#endif
    }

#ifdef _DEBUG_RASPI_RAILIO
    printf("Return: RasPi_configRailIo: 0x%08x\n", result);
#endif

    return result;
}

