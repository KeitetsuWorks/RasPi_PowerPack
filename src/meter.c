/**
 * @file        meter.c
 * @brief       メーター表示処理
 * @author      Keitetsu
 * @date        2016/11/03
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>

#include "meter.h"


void printMeter100Scale(void)
{
    printf("\x1b[0K");
    printf("\x1b[%dm0   10   20   30   40   50   60   70   80   90  100\x1b[39m\n",
            ESCCODE_METER_CHAR);
    printf("\x1b[0K");
    printf("\x1b[%dm|\x1b[%dm----\x1b[%dm+\x1b[%dm----\x1b[%dm|\x1b[%dm----\x1b[%dm+\x1b[%dm----\x1b[%dm|\x1b[%dm----\x1b[%dm+\x1b[%dm----\x1b[%dm|\x1b[%dm----\x1b[%dm+\x1b[%dm----\x1b[%dm|\x1b[%dm----\x1b[%dm+\x1b[%dm----\x1b[%dm|\x1b[39m\n",
            ESCCODE_METER_SCALE_LARGE,  // 0
            ESCCODE_METER_SCALE_LINE,
            ESCCODE_METER_SCALE_SMALL,  // 10
            ESCCODE_METER_SCALE_LINE,
            ESCCODE_METER_SCALE_LARGE,  // 20
            ESCCODE_METER_SCALE_LINE,
            ESCCODE_METER_SCALE_SMALL,  // 30
            ESCCODE_METER_SCALE_LINE,
            ESCCODE_METER_SCALE_LARGE,  // 40
            ESCCODE_METER_SCALE_LINE,
            ESCCODE_METER_SCALE_SMALL,  // 50
            ESCCODE_METER_SCALE_LINE,
            ESCCODE_METER_SCALE_LARGE,  // 60
            ESCCODE_METER_SCALE_LINE,
            ESCCODE_METER_SCALE_SMALL,  // 70
            ESCCODE_METER_SCALE_LINE,
            ESCCODE_METER_SCALE_LARGE,  // 80
            ESCCODE_METER_SCALE_LINE,
            ESCCODE_METER_SCALE_SMALL,  // 90
            ESCCODE_METER_SCALE_LINE,
            ESCCODE_METER_SCALE_LARGE); // 100

    return;
}


void printMeter100Needle(int value)
{
    int i;

    if(value < 0) {
        value = 0;
    }
    else if(value > 100) {
        value = 100;
    }

    printf("\x1b[0K");
    printf("\x1b[%dm", ESCCODE_METER_NEEDLE);
    for(i = 0; i < (value / 2); i++) {
        printf("=");
    }
    printf("^");
    printf("\x1b[39m");
    printf("\n");
    
    printf("\n");

    return;
}

