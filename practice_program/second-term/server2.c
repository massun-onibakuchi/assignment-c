#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h> /* for signal */

#define BUFSIZE 256              /* バッファサイズ */
#define ERR -1                   /* システムコールのエラー */
#define SERVER_SOCKET "mysocket" /* サーバのソケットの名前（パス名） */

void sigmsg(void);

main(int argc, char *argv[])
{
    int sockfd;                /* socket()の返すファイル記述子 */
    int ns;                    /* accept()の返すファイル記述子 */
    struct sockaddr_un server; /* サーバプロセスのソケットアドレス情報 */
    struct sockaddr_un client; /* クライアントプロセスのソケットアドレス情報 */
    socklen_t fromlen;         /* クライアントプロセスのソケットアドレス情報の長さ */
    static char buf[BUFSIZE];  /* メッセージを格納するバッファ */
    int msglen;                /* メッセージ長 */

    /* ソケットの作成 */
    if ((sockfd = socket(PF_UNIX, SOCK_STREAM, 0)) == ERR)
        exit(1);

    /* サーバプロセスのソケットアドレス情報の設定 */
    bzero((char *)&server, sizeof(server)); /* アドレス情報構造体の初期化 */
    server.sun_family = PF_UNIX;            /* プロトコルファミリの設定 */
    strcpy(server.sun_path, SERVER_SOCKET); /* ソケットの名前（パス名）の設定 */

    unlink(SERVER_SOCKET); /* ソケットに対応したファイルの削除 */

    /* ソケットへの名前づけ */
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == ERR)
        exit(1);

    /* 接続要求の受け入れ準備 */
    if (listen(sockfd, 5) == ERR)
        exit(1);

    /* 接続要求の許可 */
    bzero((char *)&client, sizeof(client));
    fromlen = sizeof(client);
    ns = accept(sockfd, (struct sockaddr *)&client, &fromlen);

    if (signal(SIGINT, (void *)sigmsg) == SIG_ERR)
    { /* SIGINT --> "sigmsg" is called */
        /* in case of error */
        perror("signal");
        exit(1);
    }

    while (1)
    {
        /* クライアントプロセスからのメッセージ受信 */
        bzero(buf, BUFSIZE);
        read(ns, buf, BUFSIZE);
        printf("received message: %s\n", buf);

        /* クライアントプロセスへのメッセージ送信 */
        printf("Message >");
        scanf("%s", buf);
        write(ns, buf, strlen(buf));
    }
    /* 終了処理 */
    close(ns);     /* accept()で返されたファイル記述子のクローズ */
    close(sockfd); /* ソケットのクローズ */

    return 0; /* 正常終了 */
}

void sigmsg(void)
{
    printf("*** Interrupted !! ***\n");
    kill(getpid(), SIGINT);
    exit(0);
}