/**
 * @file        timer.c
 * @brief       タイマー処理
 * @author      Keitetsu
 * @date        2016/11/14
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>
#include <time.h>

#include "timer.h"


void initTimer(
        TIMER_T *timer)
{
    timer->status = FALSE;              // タイマ停止
    timer->start = (time_t)0;           // タイマ開始時間の初期化
    
    return;
}


int isTimeout(
        TIMER_T *timer,
        int enable,
        int period)
{
    time_t end;
    time_t interval;
    int timeout;

#ifdef _DEBUG_TIMER
    printf("Call:   isTimeout\n");
#endif

#ifdef _DEBUG_TIMER
    printf("  enable:   0x%08x\n", enable);
    printf("  status:   0x%08x\n", timer->status);
    printf("  start:    %ld\n", (long)timer->start);
    printf("  period:   %d\n", period);
#endif

    timeout = FALSE;

    if(enable == TRUE) {                // タイマ有効の場合
        if(timer->status == TRUE) {     // タイマ動作中の場合
            time(&end);
            interval = end - timer->start;
#ifdef _DEBUG_TIMER
            printf("  end:      %ld\n", (long)end);
            printf("  interval: %ld\n", (long)interval);
#endif

            if(interval >= period) {    // タイムアウト発生の場合
                timeout = TRUE;
            }
        }
        else {                          // タイマ停止中の場合
            timer->status = TRUE;
            time(&(timer->start));
#ifdef _DEBUG_TIMER
            printf("  start:    %ld\n", (long)timer->start);
#endif
        }
    }
    else{                               // タイマ無効の場合
        initTimer(timer);
    }

#ifdef _DEBUG_TIMER
    printf("Return: isTimeout: 0x%08x\n", timeout);
#endif

    return timeout;
}

