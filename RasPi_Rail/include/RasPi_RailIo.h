/**
 * @file        RasPi_RailIo.h
 * @brief       Raspberry PiのGPIO/PWMによる鉄道模型制御 線路制御インタフェース設定
 * @author      Keitetsu
 * @date        2016/10/02
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    // __RASPI_RAILIO_H__


/**
 * @brief   線路制御インタフェースの初期化
 * @retval          RAIL_SUCCESS    正常終了
 * @retval          RAIL_FAILURE    異常終了
 */
int RasPi_initRailIo(void);


/**
 * @brief   線路制御インタフェースの設定
 * @param[in]       target          線路制御インタフェース情報
 * @retval          RAIL_SUCCESS    正常終了
 * @retval          RAIL_FAILURE    異常終了
 */
int RasPi_configRailIo(RAIL_IO_T target);

