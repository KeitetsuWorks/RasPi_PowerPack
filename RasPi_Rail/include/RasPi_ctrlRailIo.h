/**
 * @file        RasPi_ctrlRailIo.h
 * @brief       Raspberry PiのGPIO/PWMによる鉄道模型制御 進行方向/出力制御
 * @author      Keitetsu
 * @date        2016/10/02
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    // __RASPI_CTRLRAILIO_H__


/**
 * @brief   進行方向/出力制御関数
 * @param[in]       target          線路制御インタフェース情報
 * @param[in]       direciton_req   線路上の列車の進行方向
 * @param[in]       pwm_duty_req    出力制御信号のPWMデューティ
 * @return          エラー情報
 */
int RasPi_ctrlRailIo(
        RAIL_IO_T target,
        int direciton_req,
        int pwm_duty_req);

