/**
 * @file        powerpack.h
 * @brief       パワーパック 定数定義
 * @author      Keitetsu
 * @date        2016/10/02
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    // __POWERPACK_H__


/**
 * @name    TRUE/FALSE
 */
/*! @{ */
#ifndef TRUE
#define TRUE                                1           /*!< 真 */
#endif

#ifndef FALSE
#define FALSE                               0           /*!< 偽 */
#endif
/*! @} */


/**
 * @name    線路制御インタフェース
 */
/*! @{ */
#define POWERPACK_FORWARD_PORT              22          /*!< 前進信号のGPIOポート番号 */
#define POWERPACK_BACKWARD_PORT             23          /*!< 後進信号のGPIOポート番号 */
#define POWERPACK_PWM_PORT                  18          /*!< 速度制御信号のPWMポート番号 */
#define POWERPACK_PWM_DIVISOR               3           /*!< PWM制御用タイマの分周比（約25kHz） */
#define POWERPACK_PWM_RANGE                 256         /*!< PWM制御用タイマの分解能 */
#define POWERPACK_PWM_MIN                   0           /*!< 最低PWMデューティ */
#define POWERPACK_PWM_MAX                   255         /*!< 最大PWMデューティ */
/*! @} */


/**
 * @name    パワーパックの設定
 */
/*! @{ */
#define POWERPACK_SPEED_MIN                 0           /*!< パワーパックの最低速度 */
#define POWERPACK_SPEED_MAX                 100         /*!< パワーパックの最高速度 */
#define POWERPACK_SPEED_UP_STEP             2           /*!< パワーパックの加速度 */
#define POWERPACK_SPEED_DOWN_STEP           2           /*!< パワーパックの減速度 */
#define POWERPACK_LIGHT_MIN                 0           /*!< パワーパックの最小常点灯出力 */
#define POWERPACK_LIGHT_MAX                 100         /*!< パワーパックの最大常点灯出力 */
#define POWERPACK_LIGHT_UP_STEP             2           /*!< パワーパックの常点灯出力上昇度 */
#define POWERPACK_LIGHT_DOWN_STEP           2           /*!< パワーパックの常点灯出力下降度 */
/*! @} */


/**
 * @name    タイムアウト時間の有効範囲
 */
/*! @{ */
#define POWERPACK_TIMEOUT_PERIOD_MIN        1           /*!< 最短タイムアウト時間（秒） */
#define POWERPACK_TIMEOUT_PERIOD_MAX        3600        /*!< 最長タイムアウト時間（秒） */
#define POWERPACK_TIMEOUT_PERIOD_DEFAULT    600         /*!< 既定タイムアウト時間（秒） */
/*! @} */


/**
 * @enum    powerpack_operation_e
 * @brief   パワーパックのユーザ操作コード
 *
 * @typedef POWERPACK_OPERATION_E
 * @brief   パワーパックのユーザ操作コード
 */
typedef enum powerpack_operation_e {
    POWERPACK_NO_OPERATION = 0, /*!< 操作なし */
    POWERPACK_EXIT,             /*!< パワーパックの終了 */
    POWERPACK_REVERSER_FSIDE,   /*!< 逆転ハンドル 前側 */
    POWERPACK_REVERSER_RSIDE,   /*!< 逆転ハンドル 後側 */
    POWERPACK_SPEED_UP,         /*!< 加速 */
    POWERPACK_SPEED_DOWN,       /*!< 減速 */
    POWERPACK_LIGHT_UP,         /*!< 常点灯出力増 */
    POWERPACK_LIGHT_DOWN,       /*!< 常点灯出力減 */
    POWERPACK_BRAKE_E,          /*!< 非常制動 */
    POWERPACK_OPERATION_E_NUM   /*!< POWERPACK_OPERATION_E_NUMの列挙数 */
} POWERPACK_OPERATION_E;


/**
 * @enum    powerpack_reverser_e
 * @brief   逆転ハンドルのハンドル位置
 *
 * @typedef POWERPACK_REVERSER_E
 * @brief   逆転ハンドルのハンドル位置
 */
typedef enum powerpack_reverser_e {
    POWERPACK_OFF = 0,          /*!< 切 */
    POWERPACK_FORWARD,          /*!< 前 */
    POWERPACK_REVERSE,          /*!< 後 */
    POWERPACK_REVERSER_E_NUM    /*!< POWERPACK_REVERSER_Eの列挙数 */
} POWERPACK_REVERSER_E;


/**
 * @struct  powerpack_t
 * @brief   パワーパックの状態管理構造体
 *
 * @typedef POWERPACK_T
 * @brief   パワーパックの状態管理構造体
 */
typedef struct powerpack_t {
    int reverser;               /*!< 逆転ハンドルのハンドル位置 */
    int speed;                  /*!< 速度 */
    int light;                  /*!< 常点灯出力 */
} POWERPACK_T;

