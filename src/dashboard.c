/**
 * @file        dashboard.c
 * @brief       パワーパック 計器表示処理
 * @author      Keitetsu
 * @date        2016/11/03
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>

#include "powerpack.h"
#include "meter.h"
#include "dashboard.h"


// プロトタイプ宣言
/**
 * @brief   逆転ハンドル 目盛の表示
 */
static void printReverser(void);


/**
 * @brief   逆転ハンドル 位置の表示
 * @param[in]       reverser        逆転ハンドルのハンドル位置
 */
static void printReverserPosition(int reverser);


/**
 * @brief   常点灯出力調整ボリューム 目盛の表示
 */
static void printLightingVolumeScale(void);


/**
 * @brief   常点灯出力調整ボリューム 針の表示
 * @param[in]       light           常点灯出力指示値
 */
static void printLightingVolumeNeedle(int light);


/**
 * @brief   速度調整ボリューム 目盛の表示
 */
static void printSpeedometerScale(void);


/**
 * @brief   速度調整ボリューム 針の表示
 * @param[in]       speed           速度指示値
 */
static void printSpeedometerNeedle(int speed);


void initDashboard(POWERPACK_T powerpack)
{
    // 画面クリア
    printf("\x1b[2J");

    // カーソルを1行目先頭に移動
    printf("\x1b[1;1H");

    // 逆転ハンドル
    printReverser();
    printReverserPosition(powerpack.reverser);

    // 常点灯調整ボリューム
    printLightingVolumeScale();
    printLightingVolumeNeedle(powerpack.light);

    // 速度調整ボリューム
    printSpeedometerScale();
    printSpeedometerNeedle(powerpack.speed);

    // パワーパックの状態
    printPowerPackStatus(powerpack);

    // カーソルを待機位置に移動
    printf("\x1b[%d;1H", LINE_CURSOR);

    return;
}


void redisplayReverserPosition(int reverser)
{
    printf("\x1b[%d;1H", LINE_REVERSER_POSITION);
    printReverserPosition(reverser);
    printf("\x1b[%d;1H", LINE_CURSOR);

    return;
}


void redisplayLightingVolumeNeedle(int light)
{
    printf("\x1b[%d;1H", LINE_LIGHTINGVOLUME_NEEDLE);
    printLightingVolumeNeedle(light);
    printf("\x1b[%d;1H", LINE_CURSOR);

    return;
}


void redisplaySpeedometerNeedle(int speed)
{
    printf("\x1b[%d;1H", LINE_SPEEDOMETER_NEEDLE);
    printSpeedometerNeedle(speed);
    printf("\x1b[%d;1H", LINE_CURSOR);
    
    return;
}


void redisplayPowerPackStatus(POWERPACK_T powerpack)
{
    printf("\x1b[%d;1H", LINE_POWERPACK_STATUS);
    printPowerPackStatus(powerpack);
    printf("\x1b[%d;1H", LINE_CURSOR);
    
    return;
}


void printPowerPackStatus(POWERPACK_T powerpack)
{
    const char *reverser_position[POWERPACK_REVERSER_E_NUM] = {
        "  OFF  ",      // 切
        "<< F   ",      // 前
        "   R >>"       // 後
    };

    printf("\x1b[0K");
    printf("Reverser: %8s, Lighting Volume: %4d %%, Speed: %4d %%\n",
            reverser_position[powerpack.reverser],
            powerpack.light,
            powerpack.speed);

    return;
}


void printPowerPackRailPwmDuty(int pwm_duty)
{
    int pwm_duty_ratio;

    pwm_duty_ratio = (int)(((double)pwm_duty / POWERPACK_PWM_MAX) * 100);

    printf("PWM Duty: %4d / %4d ( %3d %%)\n",
            pwm_duty,
            POWERPACK_PWM_MAX,
            pwm_duty_ratio);

    return;
}


static void printReverser(void)
{
    printf("\x1b[0K");
    printf("\x1b[%dmF   OFF   R\x1b[39m\n", ESCCODE_REVERSER_CHAR);
    printf("\x1b[0K");
    printf("\x1b[%dm|\x1b[%dm----\x1b[%dm|\x1b[%dm----\x1b[%dm|\x1b[39m\n",
            ESCCODE_REVERSER_SCALE,     // F
            ESCCODE_REVERSER_LINE,
            ESCCODE_REVERSER_SCALE,     // OFF
            ESCCODE_REVERSER_LINE,
            ESCCODE_REVERSER_SCALE);    // R

    return;
}


static void printReverserPosition(int reverser)
{
    printf("\x1b[0K");
    switch(reverser) {
        case POWERPACK_OFF:
            printf("\x1b[%dm     *     \x1b[39m", ESCCODE_REVERSER_POSITION);
            break;
        case POWERPACK_FORWARD:
            printf("\x1b[%dm*          \x1b[39m", ESCCODE_REVERSER_POSITION);
            break;
        case POWERPACK_REVERSE:
            printf("\x1b[%dm          *\x1b[39m", ESCCODE_REVERSER_POSITION);
            break;
        default:
            printf("\x1b[%dm     *     \x1b[39m", ESCCODE_REVERSER_POSITION);
            break;
    }
    printf("\n");

    printf("\n");
    
    return;
}


static void printLightingVolumeScale(void)
{
    printMeter100Scale();

    return;
}


static void printLightingVolumeNeedle(int volume)
{
    printMeter100Needle(volume);

    return;
}


static void printSpeedometerScale(void)
{
    printMeter100Scale();

    return;
}


static void printSpeedometerNeedle(int speed)
{
    printMeter100Needle(speed);

    return;
}

