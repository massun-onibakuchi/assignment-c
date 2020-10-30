#include <stdio.h>
#define MAXTIME 200 
//ロジスティック写像のパラメータaの下限
#define MAXCOEF 4
//ロジスティック写像のパラメータaの上限
#define MINCOEF 2.8
//ロジスティック写像の初期値
#define INITIALVALUE 0.3

/**
 * @summary
 * ロジスティック写像のパラメータをa=2.8から3.9に変化させた時の結果をcsvに出力する.
 */

float logistic(float a, float x);
void output(FILE *fd, float mult, int maxtime, float min, float max, float x0);

int main(int argc, char *argv[])
{
    FILE *fd = fopen("./../logistic-map-loopV3.csv", "w");
    float x0 = INITIALVALUE;

    //初期値を指定した場合
    if (argc > 1)
        sscanf(argv[1], "%f", &x0);

    printf("x0=%f\n", x0);

    // aが2.8から3.57まではaを0.01刻みで変化させ結果を出力する
    output(fd, 0.01, MAXTIME, MINCOEF, 3.57, x0);
    // aが3.57から4.0まではaを0.001刻みで変化させ結果を出力する
    output(fd, 0.001, MAXTIME, 3.57, MAXCOEF, x0);

    fclose(fd);

    return 0;
}

/**
 * ロジスティック写像を行い与えられたx(t)に対してx(t+1)を返す．
 * @param a 正の定数
 * @param x 変数x(t)
 */
float logistic(float a, float x)
{
    return a * x * (1 - x);
}

/**
 * ロジスティック写像を用いて指定した範囲におけるパラメータaに対するx(t)をcsv形式で出力する
 * @param fd 出力するファイルのポインタ
 * @param mult パラメータaをいくつ刻みで変化させるか
 * @param maxtime 最大のtime
 * @param min パラメータaの最小値
 * @param max  パラメータaの最大値
 * @param x0 xの初期値
 */
void output(FILE *fd, float mult, int maxtime, float min, float max, float x0)
{
    //ロジスティック写像のパラメータa
    float coef;
    //初期値
    float x = x0;
    // 変化させる最大値
    int max_coef = max / mult;

    //aを変化させる
    for (int i = min / mult; i < max_coef; i++)
    {
        coef = i * mult;
        // ロジスティック写像の収束解を計算
        for (int time = 0; time < maxtime; time++)
        {
            x = logistic(coef, x);
        }

        printf("a=%f ,x=%f\n", coef, x);
        //ファイルに出力
        fprintf(fd, "%f,%f\n", coef, x);
    }
}