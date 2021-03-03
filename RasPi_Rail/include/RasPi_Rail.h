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


/**
 * @name    関数戻り値
 */
/** @{ */
#define RAIL_SUCCESS                0x00000000      /**< 正常終了 */
#define RAIL_FAILURE                0x00000001      /**< 異常終了 */
/** @} */


/**
 * @name    エラー情報マスク
 */
/** @{ */
#define RAIL_INVALID_DIRECTION      0x00000002      /**< 無効な進行方向 */
#define RAIL_INVALID_PWM_DUTY       0x00000004      /**< 無効なPWMデューティ */
/** @} */


/**
 * @name    GPIOポートの論理
 */
/** @{ */
#define GPIO_LOW                    0               /**< Low */
#define GPIO_HIGH                   1               /**< High */
/** @} */


/**
 * @name    線路電源
 */
/** @{ */
#define RAIL_POWER_OFF              GPIO_LOW        /**< 線路電源OFF */
#define RAIL_POWER_ON               GPIO_HIGH       /**< 線路電源ON */
/** @} */


/**
 * @enum    rail_direction_e
 * @brief   線路上の列車の進行方向
 *
 * @typedef RAIL_DIRECTION_E
 * @brief   線路上の列車の進行方向
 */
typedef enum rail_direction_e {
    RAIL_STOP = 0,              /**< 停止 */
    RAIL_FORWARD,               /**< 前進 */
    RAIL_BACKWARD,              /**< 後進 */
    RAIL_BRAKE,                 /**< 制動 */
    RAIL_DIRECTION_E_NUM        /**< RAIL_DIRECTION_Eの列挙数 */
} RAIL_DIRECTION_E;


/**
 * @struct  rail_gpio_t
 * @brief   GPIOポートの情報
 *
 * @typedef RAIL_GPIO_T
 * @brief   GPIOポートの情報
 */
typedef struct rail_gpio_t {
    int port;                   /**< GPIOポート番号 */
} RAIL_GPIO_T;


/**
 * @struct  rail_pwm_t
 * @brief   PWMポートの情報
 *
 * @typedef RAIL_PWM_T
 * @brief   PWMポートの情報
 */
typedef struct rail_pwm_t {
    int port;                   /**< PWMポート番号 */
    int divisor;                /**< PWM制御用タイマの分周比 */
    int range;                  /**< PWM制御用タイマの分解能 */
    int min;                    /**< 最小PWMデューティ */
    int max;                    /**< 最大PWMデューティ */
} RAIL_PWM_T;


/**
 * @struct  rail_io_t
 * @brief   線路制御インタフェース情報
 *
 * @typedef RAIL_IO_T
 * @brief   線路制御インタフェース情報
 */
typedef struct rail_io_t {
    RAIL_GPIO_T forward;        /**< 前進制御信号のGPIOポート番号 */
    RAIL_GPIO_T backward;       /**< 後進制御信号のGPIOポート番号 */
    RAIL_PWM_T pwm;             /**< 出力制御信号のPWMポート番号 */
} RAIL_IO_T;


// RasPi_RailIo.h
/**
 * @brief   線路制御インタフェースの初期化
 * @retval          RAIL_SUCCESS    正常終了
 * @retval          RAIL_FAILURE    異常終了
 */
extern int RasPi_initRailIo(void);


/**
 * @brief   線路制御インタフェースの設定
 * @param[in]       target          線路制御インタフェース情報
 * @retval          RAIL_SUCCESS    正常終了
 * @retval          RAIL_FAILURE    異常終了
 */
extern int RasPi_configRailIo(RAIL_IO_T target);


// RasPi_ctrlRailIo.h
/**
 * @brief   進行方向/出力制御関数
 * @param[in]       target          線路制御インタフェース情報
 * @param[in]       direciton_req   線路上の列車の進行方向
 * @param[in]       pwm_duty_req    出力制御信号のPWMデューティ
 * @return          エラー情報
 */
extern int RasPi_ctrlRailIo(
        RAIL_IO_T target,
        int direciton_req,
        int pwm_duty_req);

