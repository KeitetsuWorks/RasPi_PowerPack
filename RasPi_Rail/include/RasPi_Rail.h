/**
 * @file        RasPi_Rail.h
 * @brief       Raspberry PiのGPIO/PWMによる鉄道模型制御
 * @author      Keitetsu
 * @date        2016/10/02
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    // __RASPI_RAIL_H__

#include <wiringPi.h>


/**
 * @name    関数戻り値
 */
/*! @{ */
#define RAIL_SUCCESS                0x00000000      /*!< 正常終了 */
#define RAIL_FAILURE                0x00000001      /*!< 異常終了 */
/*! @} */


/**
 * @name    エラー情報マスク
 */
/*! @{ */
#define RAIL_INVALID_DIRECTION      0x00000002      /*!< 無効な進行方向 */
#define RAIL_INVALID_PWM_DUTY       0x00000004      /*!< 無効なPWMデューティ */
/*! @} */


/**
 * @name    GPIOポートの入出力方向
 */
/*! @{ */
#define GPIO_INPUT                  INPUT           /*!< GPIO入力ポート */
#define GPIO_OUTPUT                 OUTPUT          /*!< GPIO出力ポート */
/*! @} */


/**
 * @name    線路電源
 */
/*! @{ */
#define RAIL_POWER_OFF              GPIO_LOW        /*!< 線路電源ON */
#define RAIL_POWER_ON               GPIO_HIGH       /*!< 線路電源OFF */
/*! @} */


/**
 * @enum    gpio_value_e
 * @brief   GPIOポートの論理
 *
 * @typedef GPIO_VALUE_E
 * @brief   GPIOポートの論理
 */
typedef enum gpio_value_e {
    GPIO_LOW = 0,               /*!< Low */
    GPIO_HIGH,                  /*!< High */
    GPIO_VALUE_E_NUM            /*!< GPIO_VALUE_Eの列挙数 */
} GPIO_VALUE_E;


/**
 * @enum    rail_direction_e
 * @brief   線路上の列車の進行方向
 *
 * @typedef RAIL_DIRECTION_E
 * @brief   線路上の列車の進行方向
 */
typedef enum rail_direction_e {
    RAIL_STOP = 0,              /*!< 停止 */
    RAIL_FORWARD,               /*!< 前進 */
    RAIL_BACKWARD,              /*!< 後進 */
    RAIL_BRAKE,                 /*!< 制動 */
    RAIL_DIRECTION_E_NUM        /*!< RAIL_DIRECTION_Eの列挙数 */
} RAIL_DIRECTION_E;


/**
 * @struct  gpio_t
 * @brief   GPIOポートの情報
 *
 * @typedef GPIO_T
 * @brief   GPIOポートの情報
 */
typedef struct gpio_t {
    int port;                   /*!< GPIOポート番号 */
    int direction;              /*!< GPIOポートの入出力方向 */
} GPIO_T;


/**
 * @struct  pwm_t
 * @brief   PWMポートの情報
 *
 * @typedef PWM_T
 * @brief   PWMポートの情報
 */
typedef struct pwm_t {
    int port;                   /*!< PWMポート番号 */
    int divisor;                /*!< PWM制御用タイマの分周比 */
    int range;                  /*!< PWM制御用タイマの分解能 */
    int min;                    /*!< 最小PWMデューティ */
    int max;                    /*!< 最大PWMデューティ */
} PWM_T;


/**
 * @struct  rail_io_t
 * @brief   線路制御インタフェース情報
 *
 * @typedef RAIL_IO_T
 * @brief   線路制御インタフェース情報
 */
typedef struct rail_io_t {
    GPIO_T forward;             /*!< 前進制御信号のGPIOポート番号 */
    GPIO_T backward;            /*!< 後進制御信号のGPIOポート番号 */
    PWM_T pwm;                  /*!< 出力制御信号のPWMポート番号 */
} RAIL_IO_T;


// プロトタイプ宣言
// RasPi_RailIo.h
extern int RasPi_initRailIo(void);
extern int RasPi_configRailIo(RAIL_IO_T target);

// RasPi_ctrlRailIo.h
extern int RasPi_ctrlRailIo(
        RAIL_IO_T target,
        int direciton_req,
        int pwm_duty_req);

