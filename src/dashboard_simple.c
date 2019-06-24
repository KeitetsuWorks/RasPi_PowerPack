/**
 * @file        dashboard_simple.c
 * @brief       パワーパック 計器表示処理（シンプル表示）
 * @author      Keitetsu
 * @date        2016/12/08
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>

#include "powerpack.h"
#include "dashboard_simple.h"


/**
 * @brief   パワーパックの状態 テキスト表示
 * @param[in]       powerpack       パワーパックの状態管理構造体
 */
static void printPowerPackStatus(POWERPACK_T powerpack);


/**
 * @brief   出力制御信号のPWMデューティ テキスト表示
 * @param[in]       pwm_duty        出力制御信号のPWMデューティ
 */
static void printPowerPackRailPwmDuty(int pwm_duty);


void initSimpleDashboard(
        POWERPACK_T powerpack,
        int pwm_duty)
{
    printPowerPackStatus(powerpack);
    printPowerPackRailPwmDuty(pwm_duty);
    printf("\n");

    return;
}


void redisplaySimpleDashboard(
        POWERPACK_T powerpack,
        int pwm_duty)
{
    printPowerPackStatus(powerpack);
    printPowerPackRailPwmDuty(pwm_duty);
    printf("\n");

    return;
}


static void printPowerPackStatus(POWERPACK_T powerpack)
{
    const char *reverser_position[POWERPACK_REVERSER_E_NUM] = {
        "  OFF  ",      // 切
        "<< F   ",      // 前
        "   R >>"       // 後
    };

    printf("Reverser: %8s, Lighting Volume: %4d %%, Speed: %4d %%\n",
            reverser_position[powerpack.reverser],
            powerpack.light,
            powerpack.speed);

    return;
}


static void printPowerPackRailPwmDuty(int pwm_duty)
{
    int pwm_duty_ratio;

    pwm_duty_ratio = (int)(((double)pwm_duty / POWERPACK_PWM_MAX) * 100);

    printf("PWM Duty: %4d / %4d ( %3d %%)\n",
            pwm_duty,
            POWERPACK_PWM_MAX,
            pwm_duty_ratio);

    return;
}

