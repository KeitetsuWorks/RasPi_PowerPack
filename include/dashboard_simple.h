/**
 * @file        dashboard_simple.h
 * @brief       パワーパック 計器表示処理（シンプル表示）
 * @author      Keitetsu
 * @date        2016/12/08
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    // __DASHBOARD_SIMPLE_H__


/**
 * @brief   パワーパック 計器表示の初期化（シンプル表示）
 * @param[in]       powerpack       パワーパックの状態管理構造体
 * @param[in]       pwm_duty        出力制御信号のPWMデューティ
 */
void initSimpleDashboard(
        POWERPACK_T powerpack,
        int pwm_duty);


/**
 * @brief   パワーパック 計器表示の更新（シンプル表示）
 * @param[in]       powerpack       パワーパックの状態管理構造体
 * @param[in]       pwm_duty        出力制御信号のPWMデューティ
 */
void redisplaySimpleDashboard(
        POWERPACK_T powerpack,
        int pwm_duty);

