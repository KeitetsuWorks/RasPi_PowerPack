/**
 * @file        powerpack.c
 * @brief       パワーパック メイン処理
 * @author      Keitetsu
 * @date        2016/10/02
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "RasPi_Rail.h"
#include "powerpack.h"
#include "help.h"
#include "dashboard.h"
#include "dashboard_simple.h"
#include "key.h"
#include "timer.h"


// プロトタイプ宣言
/**
 * @brief   パワーパックの線路制御インタフェース情報の初期化
 * @param[out]      rail            線路制御インタフェース情報
 */
static void initPowerPackRailIoInfo(
        RAIL_IO_T *rail);


/**
 * @brief   パワーパックの状態管理構造体の初期化
 * @param[out]      powerpack       パワーパックの状態管理構造体
 */
static void initPowerPackStatus(
        POWERPACK_T *powerpack);


/**
 * @brief   ユーザ操作を逆転ハンドル，速度および常点灯出力に反映
 * @param[in]       operation       ユーザ操作コード
 * @param[in,out]   powerpack       パワーパックの状態管理構造体
 */
static void updatePowerPackStatus(
        int operation,
        POWERPACK_T *powerpack);


/**
 * @brief   ユーザ操作の開始処理
 */
static void startPowerPackUserOperation(void);


/**
 * @brief   ユーザ操作の停止処理
 */
static void stopPowerPackUserOperation(void);


/**
 * @brief   キー入力からユーザ操作を取得
 * @return  パワーパックのユーザ操作コード
 */
static int getPowerPackUserOperation(void);


/**
 * @brief   ユーザ操作を逆転ハンドルに反映
 * @param[in]       operation       ユーザ操作コード
 * @param[in,out]   reverser        逆転ハンドルのハンドル位置
 */
static void updatePowerPackReverser(
        int operation,
        int *reverser);


/**
 * @brief   ユーザ操作を速度に反映
 * @param[in]       operation       ユーザ操作コード
 * @param[in,out]   speed           速度
 */
static void updatePowerPackSpeed(
        int operation,
        int *speed);


/**
 * @brief   ユーザ操作を常点灯出力に反映
 * @param[in]       operation       ユーザ操作コード
 * @param[in,out]   light           常点灯出力
 */
static void updatePowerPackLightingVolume(
        int operation,
        int *light);


/**
 * @brief   パワーパックの状態から，線路上の列車の進行方向を取得する（変換する）
 * @param[in]       powerpack       パワーパックの状態管理構造体
 * @return          線路上の列車の進行方向
 */
static int getPowerPackRailDirection(
        POWERPACK_T powerpack);


/**
 * @brief   パワーパックの状態から，出力制御信号のPWMデューティを取得する（計算する）
 * @param[in]       powerpack       パワーパックの状態管理構造体
 * @return          出力制御信号のPWMデューティ
 */
static int getPowerPackRailPwmDuty(
        POWERPACK_T powerpack);


/**
 * @brief   メイン関数
 * @retval  EXIT_SUCCESS    正常終了
 * @retval  EXIT_FAILURE    異常終了
 */
int main(
        int argc,
        char *argv[])
{
    RAIL_IO_T rail;             // 線路制御インタフェース情報
    int rail_direction;         // 線路上の列車の進行方向
    int rail_pwm_duty;          // 出力制御信号のPWMデューティ
    TIMER_T timer;              // 無操作検出タイマ
    int timer_enable;           // 無操作検出タイマのイネーブル
    int timer_period;           // 無操作検出タイマのタイムアウト時間
    int operation;              // ユーザ操作コード
    POWERPACK_T powerpack;      // パワーパックの状態
    POWERPACK_T powerpack_prev; // 前回のパワーパックの状態
    int flag_error;             // エラーフラグ
    int flag_exit;              // 終了フラグ
    int flag_simple;            // シンプル表示モードのイネーブルフラグ
    int flag_timer;             // 無操作検出タイマのイネーブルフラグ
    int retval;

    int opt, optlong_index;
    struct option longopts[] = {
        { "divisor",    required_argument,  NULL,   'd' },
        { "help",       no_argument,        NULL,   'h' },
        { "keymap",     no_argument,        NULL,   'k' },
        { "simple",     no_argument,        NULL,   's' },
        { "timer",      required_argument,  NULL,   't' },
        { "version",    no_argument,        NULL,   'v' },
        { 0,            0,                  0,      0   }
    };

    // 線路制御インタフェース情報の初期化
    initPowerPackRailIoInfo(&rail);
    rail_direction = RAIL_STOP;
    rail_pwm_duty = POWERPACK_PWM_MIN;

    // 無操作検出タイマ 初期化
    timer_enable = TRUE;
    initTimer(&timer);
    timer_period = POWERPACK_TIMEOUT_PERIOD_DEFAULT;
    
    // フラグの初期化
    flag_error = FALSE;
    flag_exit = FALSE;
    flag_simple = FALSE;
    flag_timer = TRUE;

    // コマンドオプション処理
    while((flag_error == FALSE) && (flag_exit == FALSE)) {
        opt = getopt_long(argc, argv, "d:hkst:v", longopts, &optlong_index);
        if(opt == -1) {
            break;
        }

        switch(opt) {
            case 'd':
                rail.pwm.divisor = atoi(optarg);
                if(rail.pwm.divisor < 1 || rail.pwm.divisor > 4095) {
                    printf("Error:  invalid pwm divisor value: %d\n",
                            rail.pwm.divisor);
                    flag_error = TRUE;
                }
                else {
                    printf("Info:   divisor value: %d\n", rail.pwm.divisor);
                }
                break;
            case 'h':
                printHelp();
                flag_exit = TRUE;
                break;
            case 'k':
                printKeymap();
                flag_exit = TRUE;
                break;
            case 's':
                flag_simple = TRUE;
                break;
            case 't':
                timer_period = atoi(optarg);
                if(timer_period == 0) {
                    printf("Info:   automatic stop timer: disable\n");
                    flag_timer = FALSE;
                }
                else if(timer_period < POWERPACK_TIMEOUT_PERIOD_MIN
                        || timer_period > POWERPACK_TIMEOUT_PERIOD_MAX) {
                    printf("Error:  invalid time-out period: %d\n",
                            timer_period);
                    flag_timer = FALSE;
                    flag_error = TRUE;
                }
                else {
                    printf("Info:   timer period: %d sec\n", timer_period);
                }
                break;
            case 'v':
                printVersion();
                flag_exit = TRUE;
                break;
            default:
                printf("Error:  invalid argument\n");
                flag_error = TRUE;
                break;
        }
    }

    if(flag_error != FALSE) {
        exit(EXIT_FAILURE);
    }

    if(flag_exit != FALSE) {
        exit(EXIT_SUCCESS);
    }

    // 線路制御インタフェースの初期化
    retval = RasPi_initRailIo();
    if(retval != RAIL_SUCCESS) {
        exit(EXIT_FAILURE);
    }

    // 線路制御インタフェースの設定
    retval = RasPi_configRailIo(rail);
    if(retval != RAIL_SUCCESS) {
        exit(EXIT_FAILURE);
    }

    // ユーザ操作の初期化
    operation = POWERPACK_NO_OPERATION;

    // パワーパックの状態の初期化
    initPowerPackStatus(&powerpack);
    powerpack_prev = powerpack;

    // ユーザインタフェースの初期化
    if(flag_simple == FALSE) {
        initDashboard(powerpack);
    }
    else {
        initSimpleDashboard(powerpack, rail_pwm_duty);
    }
    startPowerPackUserOperation();

    // メインループ処理
    flag_error = FALSE;
    flag_exit = FALSE;
    while((flag_error == FALSE) && (flag_exit == FALSE)) {
        // ユーザ操作の取得
        operation = getPowerPackUserOperation();

        // 無操作検出タイマ イネーブルフラグの更新
        if(flag_timer == TRUE && (operation == POWERPACK_NO_OPERATION)) {
            timer_enable = TRUE;
        }
        else {
            timer_enable = FALSE;
        }

        // 無操作検出タイマ タイムアウトの判定
        retval = isTimeout(
                &timer,
                timer_enable,
                timer_period);
        if(retval == TRUE) {    // タイムアウト発生の場合
            // ユーザ操作コードを非常制動に置換え
            operation = POWERPACK_BRAKE_E;
        }

        // 終了フラグの更新
        if(operation == POWERPACK_EXIT) {
            flag_exit = TRUE;
        }

        // ユーザ操作を進行方向，速度および常点灯出力に反映
        updatePowerPackStatus(operation, &powerpack);
        
        // 線路上の列車の進行方向の取得
        rail_direction = getPowerPackRailDirection(powerpack);

        // 出力制御信号のPWMデューティの取得
        rail_pwm_duty = getPowerPackRailPwmDuty(powerpack);

        // 進行方向/出力制御
        retval = RasPi_ctrlRailIo(rail, rail_direction, rail_pwm_duty);
        if(retval != RAIL_SUCCESS) {
            flag_error = TRUE;
        }

        // 計器表示の更新
        if(flag_simple == FALSE) {
            if(powerpack.reverser != powerpack_prev.reverser) {
                redisplayReverserPosition(powerpack.reverser);
            }
            if(powerpack.light != powerpack_prev.light) {
                redisplayLightingVolumeNeedle(powerpack.light);
            }
            if(powerpack.speed != powerpack_prev.speed) {
                redisplaySpeedometerNeedle(powerpack.speed);
            }
            if((powerpack.reverser != powerpack_prev.reverser)
                    || (powerpack.light != powerpack_prev.light)
                    || (powerpack.speed != powerpack_prev.speed)) {
                    redisplayPowerPackStatus(powerpack);
            }
        }
        else {
            if((powerpack.reverser != powerpack_prev.reverser)
                    || (powerpack.light != powerpack_prev.light)
                    || (powerpack.speed != powerpack_prev.speed)) {
                redisplaySimpleDashboard(powerpack, rail_pwm_duty);
            }
        }

        powerpack_prev = powerpack;

        usleep(25000);
    }

    // ユーザインタフェースの終了処理
    stopPowerPackUserOperation();

    if(flag_error != FALSE) {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}


static void initPowerPackRailIoInfo(
        RAIL_IO_T *rail)
{
    rail->forward.port = POWERPACK_FORWARD_PORT;
    rail->backward.port = POWERPACK_BACKWARD_PORT;
    rail->pwm.port = POWERPACK_PWM_PORT;
    rail->pwm.divisor = POWERPACK_PWM_DIVISOR;
    rail->pwm.range = POWERPACK_PWM_RANGE;
    rail->pwm.min = POWERPACK_PWM_MIN;
    rail->pwm.max = POWERPACK_PWM_MAX;

    return;
}


static void startPowerPackUserOperation(void)
{
    openKey();
}


static void stopPowerPackUserOperation(void)
{
    closeKey();
}


static int getPowerPackUserOperation(void)
{
    int operation;
    int key;
    
    operation = POWERPACK_NO_OPERATION;
    
    if(containsKey() != 0) {
        key = getKey();
        switch(key) {
            case 0x1B:
                if(containsKey() != 0) {
                    key = getKey();
                    switch(key) {
                        case 0x5B:
                            if(containsKey() != 0) {
                                key = getKey();
                                switch(key) {
                                    case 0x41:  // Up Arrow
                                        operation = POWERPACK_SPEED_UP;
                                        break;
                                    case 0x42:  // Down Arrow
                                        operation = POWERPACK_SPEED_DOWN;
                                        break;
                                    case 0x43:  // Right Arrow
                                        operation = POWERPACK_REVERSER_RSIDE;
                                        break;
                                    case 0x44:  // Left Arrow
                                        operation = POWERPACK_REVERSER_FSIDE;
                                        break;
                                    default:
                                        break;
                                }
                            }
                        default:
                            break;
                    }
                }
                else {  // ESC
                    operation = POWERPACK_EXIT;
                }
                break;
            case 0x20:  // SPACE
                operation = POWERPACK_BRAKE_E;
                break;
            case 'f':
                operation = POWERPACK_LIGHT_DOWN;
                break;
            case 'h':
                operation = POWERPACK_REVERSER_FSIDE;
                break;
            case 'j':
                operation = POWERPACK_SPEED_DOWN;
                break;
            case 'k':
                operation = POWERPACK_REVERSER_RSIDE;
                break;
            case 'r':
                operation = POWERPACK_LIGHT_UP;
                break;
            case 'u':
                operation = POWERPACK_SPEED_UP;
                break;
            default:
                break;
        }
    }

    return operation;
}


static void initPowerPackStatus(
        POWERPACK_T *powerpack)
{
    powerpack->reverser = POWERPACK_OFF;
    powerpack->speed = POWERPACK_SPEED_MIN;
    powerpack->light = POWERPACK_LIGHT_MIN;

    return;
}


static void updatePowerPackStatus(
        int operation,
        POWERPACK_T *powerpack)
{
    switch(operation) {
        case POWERPACK_REVERSER_FSIDE:
        case POWERPACK_REVERSER_RSIDE:
            updatePowerPackReverser(operation, &(powerpack->reverser));
            break;
        case POWERPACK_SPEED_UP:
        case POWERPACK_SPEED_DOWN:
            updatePowerPackSpeed(operation, &(powerpack->speed));
            break;
        case POWERPACK_LIGHT_UP:
        case POWERPACK_LIGHT_DOWN:
            updatePowerPackLightingVolume(operation, &(powerpack->light));
            break;
        case POWERPACK_BRAKE_E:
        case POWERPACK_EXIT:
            powerpack->reverser = POWERPACK_OFF;
            powerpack->speed = POWERPACK_SPEED_MIN;
            powerpack->light = POWERPACK_LIGHT_MIN;
            break;
        case POWERPACK_NO_OPERATION:
        default:
            break;
    }

    return;
}


static void updatePowerPackReverser(
        int operation,
        int *reverser)
{
    int reverser_work;

    reverser_work = *reverser;

    switch(operation) {
        case POWERPACK_REVERSER_FSIDE:
            switch(reverser_work) {
                case POWERPACK_OFF:
                    reverser_work = POWERPACK_FORWARD;
                    break;
                case POWERPACK_FORWARD:
                    break;
                case POWERPACK_REVERSE:
                    reverser_work = POWERPACK_OFF;
                    break;
                default:
                    reverser_work = POWERPACK_OFF;
                    break;
            }
            break;
        case POWERPACK_REVERSER_RSIDE:
            switch(reverser_work) {
                case POWERPACK_OFF:
                    reverser_work = POWERPACK_REVERSE;
                    break;
                case POWERPACK_FORWARD:
                    reverser_work = POWERPACK_OFF;
                    break;
                case POWERPACK_REVERSE:
                    break;
                default:
                    reverser_work = POWERPACK_OFF;
                    break;
            }
            break;
        default:
            break;
    }

    *reverser = reverser_work;

    return;
}


static void updatePowerPackSpeed(
        int operation,
        int *speed)
{
    int speed_work;

    speed_work = *speed;

    switch(operation) {
        case POWERPACK_SPEED_UP:
            speed_work += POWERPACK_SPEED_UP_STEP;
            break;
        case POWERPACK_SPEED_DOWN:
            speed_work -= POWERPACK_SPEED_DOWN_STEP;
            break;
        default:
            break;
    }
    
    if(speed_work > POWERPACK_SPEED_MAX) {
        speed_work = POWERPACK_SPEED_MAX;
    }
    else if(speed_work < POWERPACK_SPEED_MIN) {
        speed_work = POWERPACK_SPEED_MIN;
    }

    *speed = speed_work;

    return;
}


static void updatePowerPackLightingVolume(
        int operation,
        int *light)
{
    int light_work;

    light_work = *light;

    switch(operation) {
        case POWERPACK_LIGHT_UP:
            light_work += POWERPACK_LIGHT_UP_STEP;
            break;
        case POWERPACK_LIGHT_DOWN:
            light_work -= POWERPACK_LIGHT_DOWN_STEP;
            break;
        default:
            break;
    }
    
    if(light_work > POWERPACK_LIGHT_MAX) {
        light_work = POWERPACK_LIGHT_MAX;
    }
    else if(light_work < POWERPACK_LIGHT_MIN) {
        light_work = POWERPACK_LIGHT_MIN;
    }

    *light = light_work;

    return;
}


static int getPowerPackRailDirection(
        POWERPACK_T powerpack)
{
    int direction;

    direction = RAIL_STOP;

    switch(powerpack.reverser) {
        case POWERPACK_OFF:
            direction = RAIL_STOP;
            break;
        case POWERPACK_FORWARD:
            direction = RAIL_FORWARD;
            break;
        case POWERPACK_REVERSE:
            direction = RAIL_BACKWARD;
            break;
        default:
            direction = RAIL_STOP;
            break;
    }

    return direction;
}


static int getPowerPackRailPwmDuty(
        POWERPACK_T powerpack)
{
    int pwm_duty_light;
    int pwm_duty_speed;
    int pwm_duty;

    pwm_duty_light = (int)(POWERPACK_PWM_MAX * ((double)powerpack.light / POWERPACK_LIGHT_MAX));
    pwm_duty_speed = (int)((POWERPACK_PWM_MAX - pwm_duty_light) * ((double)powerpack.speed / POWERPACK_SPEED_MAX));
    pwm_duty = pwm_duty_light + pwm_duty_speed;

    if(pwm_duty > POWERPACK_PWM_MAX) {
        pwm_duty = POWERPACK_PWM_MAX;
    }
    else if(pwm_duty < POWERPACK_PWM_MIN) {
        pwm_duty = POWERPACK_PWM_MIN;
    }

    return pwm_duty;
}

