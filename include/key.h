/**
 * @file        key.h
 * @brief       キー入力処理
 * @author      Keitetsu
 * @date        2016/10/09
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#pragma once    // __KEY_H__


/**
 * @brief   キー入力設定の初期化
 * @retval          0               成功
 * @retval          1               失敗
 */
int openKey(void);


/**
 * @brief   キー入力設定の復元
 * @retval          0               成功
 * @retval          1               失敗
 */
int closeKey(void);


/**
 * @brief   キー入力の有無の取得
 * @retval          0               入力なし
 * @retval          1               入力あり
 */
int containsKey(void);


/**
 * @brief   キー入力の取得
 * @return          キー入力からの1文字取得結果
 */
int getKey(void);

