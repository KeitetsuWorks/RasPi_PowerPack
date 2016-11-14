/**
 * @file        timer.h
 * @brief       タイマー処理
 * @author      Keitetsu
 * @date        2016/11/14
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    // __TIMER_H__

#include <time.h>


/**
 * @name    TRUE/FALSE
 */
/*! @{ */
#ifndef TRUE
#define TRUE                1               /*!< 真 */
#endif

#ifndef FALSE
#define FALSE               0               /*!< 偽 */
#endif
/*! @} */


/**
 * @struct  timer_t
 * @brief   タイマ状態管理構造体
 *
 * @typedef TIMER_T
 * @brief   タイマ状態管理構造体
 */
typedef struct timer_t {
    int status;             /*!< タイマ状態 */
    time_t start;           /*!< タイマ開始時間 */
} TIMER_T;


// プロトタイプ宣言
/**
 * @brief   タイマの初期化
 * @param[out]      timer           タイマ状態管理構造体
 */
void initTimer(
        TIMER_T *timer);


/**
 * @brief   タイムアウトの判定
 * @param[in,out]   timer           タイマ状態管理構造体
 * @param[in]       enable          タイマイネーブル
 * @param[in]       period          タイムアウト時間
 * @retval          FALSE           タイムアウトなし
 * @retval          TRUE            タイムアウト発生
 */
int isTimeout(
        TIMER_T *timer,
        int enable,
        int period);

