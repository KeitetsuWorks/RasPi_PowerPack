/**
 * @file        key.c
 * @brief       キー入力処理
 * @author      Keitetsu
 * @date        2016/10/09
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>


static struct termios tio_backup;
static int fdflag_backup;


int openKey(void)
{
    struct termios tio;
    int retval;
    
    // 端末設定のバックアップ
    retval = tcgetattr(STDIN_FILENO, &tio);
    if(retval == -1) {
        perror("tcgetattr");

        return 1;
    }
    tio_backup = tio;

    // 非カノニカルモードを有効化．入力文字のエコーを無効化
    tio.c_lflag &= ~(ICANON | ECHO);
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 0;

    // 端末設定を適用
    retval = tcsetattr(STDIN_FILENO, TCSANOW, &tio);
    if(retval == -1) {
        perror("tcsetattr");

        return 1;
    }
    
    setbuf(stdout, NULL);

    return 0;
}


int closeKey(void)
{
    int retval;

    // 端末設定を復元
    retval = tcsetattr(STDIN_FILENO, TCSANOW, &tio_backup);
    if(retval == -1) {
        perror("tcsetattr");

        return 1;
    }

    return 0;
}


int containsKey(void)
{
    int retval;
    int key;
    
    // ファイルディスクリプタのバックアップ
    fdflag_backup = fcntl(STDIN_FILENO, F_GETFL, 0);
    if(fdflag_backup == -1) {
        perror("fcntl");

        return 0;
    }

    // ファイルディスクリプタの設定
    retval = fcntl(STDIN_FILENO, F_SETFL, fdflag_backup | O_NONBLOCK);
    if(retval == -1) {
        perror("fcntl");

        return 0;
    }

    // キーボード読込み
    key = getchar();
    
    // ファイルディスクリプタの復元
    retval = fcntl(STDIN_FILENO, F_SETFL, fdflag_backup);
    if(retval == -1) {
        perror("fcntl");

        return 0;
    }

    if(key == EOF) {
        return 0;
    }
    
    ungetc(key, stdin);
    
    return 1;
}


int getKey(void)
{
    int key;
    
    key = getchar();

    return key;
}

