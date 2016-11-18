/**
 * @file        help.c
 * @brief       ヘルプ/バージョン情報の表示関数
 * @author      Keitetsu
 * @date        2016/11/13
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>

#include "help.h"
#include "version.h"


void printHelp(void)
{
    printf("Usage: RasPi_PowerPack [OPTION...]\n");
    printf("\n");
    printf("  -d, --divisor=DIVISOR     set the divisor for PWM clock\n");
    printf("  -h, --help                give this help list\n");
    printf("  -k, --keymap              give the key map\n");
    printf("  -s, --simple              start in simple display mode\n");
    printf("  -t, --timer=PERIOD        set the time-out period (sec) to automatic stop\n");
    printf("                            default value is 600\n");
    printf("                              0:            disable automatic stop\n");
    printf("                              1 - 3600:     available time-out period\n");
    printf("  -v, --version             print program version\n");

    return;
}


void printKeymap(void)
{
    printf("RasPi_PowerPack Key Map\n");
    printf("\n");
    printf("  h, Left Arrow             change the reverser position to forward side\n");
    printf("  k, Right Arrow            change the reverser position to reverse side\n");
    printf("  u, Up Arrow               speed up\n");
    printf("  j, Down Arrow             speed down\n");
    printf("  r                         up the lighting volume\n");
    printf("  f                         down the lighting volume\n");
    printf("  Space                     emergency brake\n");
    printf("  Esc                       exit this program\n");

    return;
}


void printVersion(void)
{
    printf("Version: %s\n", VERSION);

    return;
}

