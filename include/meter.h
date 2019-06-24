/**
 * @file        meter.h
 * @brief       メーター表示処理
 * @author      Keitetsu
 * @date        2016/11/03
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    // __METER_H__


/**
 * @name    エスケープシーケンスによる表示スタイル設定
 */
/*! @{ */
#define ESCCODE_METER_SCALE_LARGE   36              /*!< メーターの大目盛 */
#define ESCCODE_METER_SCALE_SMALL   36              /*!< メーターの小目盛 */
#define ESCCODE_METER_SCALE_LINE    34              /*!< メーターの目盛線 */
#define ESCCODE_METER_NEEDLE        33              /*!< メーターの針 */
#define ESCCODE_METER_CHAR          36              /*!< メーターの文字 */
/*! @} */


/**
 * @brief   百分率メーター 目盛の表示
 */
void printMeter100Scale(void);


/**
 * @brief   百分率メーター 針の表示
 * @param[in]       value           指示値
 */
void printMeter100Needle(int value);

