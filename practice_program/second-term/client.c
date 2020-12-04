#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFSIZE 256              /* バッファサイズ */
#define ERR -1                   /* システムコールのエラー */
#define SERVER_SOCKET "mysocket" /* サーバのソケットの名前（パス名） */

main(int argc, char *argv[])
{
    int sockfd;                /* socket()の返すファイル記述子 */
    struct sockaddr_un server; /* サーバプロセスのソケットアドレス情報 */
    struct hostent *hp;        /* ホスト情報 */
    static char buf[BUFSIZE];  /* メッセージを格納するバッファ */
    int msglen;                /* メッセージ長 */

    /* ソケットの作成 */
    if ((sockfd = socket(PF_UNIX, SOCK_STREAM, 0)) == ERR)
        exit(1);

    /* サーバプロセスのソケットアドレス情報の設定 */
    bzero((char *)&server, sizeof(server)); /* アドレス情報構造体の初期化 */
    server.sun_family = PF_UNIX;            /* プロトコルファミリの設定 */
    strcpy(server.sun_path, SERVER_SOCKET); /* ソケットの名前（パス名）の設定 */

    /* 接続要求の発信 */
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == ERR)
        exit(1);

    /* サーバプロセスへのメッセージ送信 */
    printf("Message >");
    scanf("%s", buf);
    write(sockfd, buf, strlen(buf));

    /* サーバプロセスからのメッセージ受信 */
    bzero(buf, BUFSIZE);
    read(sockfd, buf, BUFSIZE);
    printf("received message: %s\n", buf);

    close(sockfd); /* ソケットのクローズ */

    return 0; /* 正常終了 */
}