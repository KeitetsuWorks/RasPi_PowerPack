/**
 * @file        dashboard.h
 * @brief       パワーパック 計器表示処理
 * @author      Keitetsu
 * @date        2016/11/03
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    // __DASHBOARD_H__


/**
 * @name    エスケープシーケンスによる表示スタイル設定
 */
/*! @{ */
#define ESCCODE_REVERSER_SCALE          36      /*!< 逆転ハンドルの目盛 */
#define ESCCODE_REVERSER_LINE           34      /*!< 逆転ハンドルの目盛線 */
#define ESCCODE_REVERSER_POSITION       33      /*!< 逆転ハンドルの位置 */
#define ESCCODE_REVERSER_CHAR           36      /*!< 逆転ハンドルの文字 */
/*! @} */


/**
 * @name    表示開始行（1行目基準）
 */
/*! @{ */
#define LINE_REVERSER_POSITION          3       /*!< 逆転ハンドル 位置の表示開始行 */
#define LINE_LIGHTINGVOLUME_NEEDLE      7       /*!< 常点灯調整ボリューム 針の表示開始行 */
#define LINE_SPEEDOMETER_NEEDLE         11      /*!< 速度調整ボリューム 針の表示開始行 */
#define LINE_POWERPACK_STATUS           13      /*!< パワーパックの状態 テキスト表示開始行 */
#define LINE_CURSOR                     14      /*!< カーソル待機行 */
/*! @} */


/**
 * @brief   パワーパック 計器表示の初期化
 * @param[in]       powerpack       パワーパックの状態管理構造体
 */
void initDashboard(POWERPACK_T powerpack);


/**
 * @brief   逆転ハンドル 位置の表示更新
 * @param[in]       reverser        逆転ハンドルのハンドル位置
 */
void redisplayReverserPosition(int reverser);


/**
 * @brief   常点灯出力調整ボリューム 針の表示更新
 * @param[in]       light           常点灯出力指示値
 */
void redisplayLightingVolumeNeedle(int light);


/**
 * @brief   速度調整ボリューム 針の表示更新
 * @param[in]       speed           速度指示値
 */
void redisplaySpeedometerNeedle(int speed);


/**
 * @brief   パワーパックの状態 テキスト表示更新
 * @param[in]       powerpack       パワーパックの状態管理構造体
 */
void redisplayPowerPackStatus(POWERPACK_T powerpack);

