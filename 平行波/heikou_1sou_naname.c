#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define e 0.1602 /* 電気素量 */
#define HOW_MANY_SINDOU_tate8 48 /* 8結合層の縦の振動子の数 */
#define HOW_MANY_SINDOU_yoko8 48 /* 8結合層の横の振動子の数 */
#define HOW_MANY_SINDOU_tate4 24 /* 4結合層の縦の振動子の数 */
#define HOW_MANY_SINDOU_yoko4 24 /* 4結合層の横の振動子の数 */
#define T_END 1550.0/* 試行時間[ns] */
#define dt 0.1 /* 刻み時間[ns] */
#define record_timing 1500.0 /* 撮影を始めるタイミング[ns] */
#define Trigger_Timing_1 1500.5 /* 1層目でトリガを印加するタイミング[ns] */
#define Trigger_Timing_2 1502.0 //1層目の両側でトリガを印加するタイミング
#define Trigger_Timing_3 1510.0 //2層目でトリガを印加するタイミング
#define Trigger_Last 20 /* トリガの継続時間[ns] */
#define START_tate 1 /* トリガ電圧をかける縦の位置 */
#define START_yoko 1 /* トリガ電圧をかける横の位置 */

/*左右上下*/

double makerand() {
    double r;
    rand(); rand(); rand();
    r = rand();
    return r / RAND_MAX;
}

int main() {
    double t = 0.0;//[ns]
    double Rj = 0.001;//[G]
    double R8 = 6;//[G]
    double R4 = 6;
    double Cj = 10.0;//[aF]
    double C8 = 2.0;//[aF]
    double C4 = 2.0;//[aF]
    double Cs = 1.0;//[aF]
    double Vd8 = 0.00230;//[V]
    double Vd4 = 0.00348;//[V]
    double Vin = 0.01;//[V]
    double Ganma8, Ganma4, T8, T4, r, w;
    double Tmin;
    double Trecord = record_timing;
    int tempx, tempy;
    int x, y; /* 作業変数 */
    srand((unsigned)time(NULL));

    //8結合層の設定
    double dtVd8[HOW_MANY_SINDOU_tate8][HOW_MANY_SINDOU_yoko8] = { 0 };/* バイアス電圧Vdの配列 */
    double dtVn8[HOW_MANY_SINDOU_tate8][HOW_MANY_SINDOU_yoko8] = { 0 };/* ノード電圧Vnの配列 */
    double dtQ8[HOW_MANY_SINDOU_tate8][HOW_MANY_SINDOU_yoko8] = { 0 };/* トンネル接合の電荷Qの配列 */
    double dtdE8[HOW_MANY_SINDOU_tate8][HOW_MANY_SINDOU_yoko8] = { 0 };/* dEの配列 */

    //4結合層の設定
    double dtVd4[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* バイアス電圧Vdの配列 */
    double dtVn4[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* ノード電圧Vnの配列 */
    double dtQ4[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* トンネル接合の電荷Qの配列 */
    double dtdE4[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* dEの配列 */
    double q1, q2, q3, q4, q5, q6, q7, q8, q9; /* ノード間のキャパシタの電荷q 左右下上　右から左　左から右 */

    double setting[HOW_MANY_SINDOU_tate8][HOW_MANY_SINDOU_yoko8] = { 0 };



    /* 8結合層Vdが正負交互になるように値を代入 */
    for (y = 2; y < HOW_MANY_SINDOU_tate8; y++) {
        for (x = 2; x < HOW_MANY_SINDOU_yoko8; x++) {
            if (setting[y][x] == 1){
                dtVd8[y][x] = 0;
            } else {
                if (y % 2 == 0){
                    if ((x + y) % 2 == 0) {
                        dtVd8[y][x] = -Vd8;
                    } else {
                        dtVd8[y][x] = Vd8;
                    }
                }
                else{
                    if ((x + y) % 2 == 0) {
                        dtVd8[y][x] = Vd8;
                    } else {
                        dtVd8[y][x] = -Vd8;
                    }
                }
                
            }
        }
    }

    for (y = 1; y < HOW_MANY_SINDOU_tate4; y++) {
        for (x = 1; x < HOW_MANY_SINDOU_yoko4; x++) {
            if (setting[y][x] == 1){
                dtVd4[y][x] = 0;
            } else {
                if ((x + y) % 2 == 0) {
                    dtVd4[y][x] = Vd4;
                } else {
                    dtVd4[y][x] = -Vd4;
                }
            }
        }
    }

    while (t <= T_END) {

        /* トリガを印加 */
        if (t > Trigger_Timing_1 && t < Trigger_Timing_1 + Trigger_Last) {
            dtVn8[START_tate][START_yoko] = -Vin;
        }
        else {
            dtVn8[START_tate][START_yoko] = 0;
        }
        if (t > Trigger_Timing_2 && t < Trigger_Timing_2 + Trigger_Last) {
            dtVn8[0][6] = -Vin;
            dtVn8[6][0] = -Vin;
        }
        else {
            dtVn8[0][6] = 0;
            dtVn8[6][0] = 0;
        }
        if (t > Trigger_Timing_3 && t < Trigger_Timing_3 + Trigger_Last) {
            dtVn4[0][0] = Vin;
            dtVn4[0][3] = Vin;
            dtVn4[3][0] = Vin;
        }
        else {
            dtVn4[0][0] = 0;
            dtVn4[0][3] = 0;
            dtVn4[3][0] = 0;
        }


        /* qの更新 */
        for (y = 2; y < HOW_MANY_SINDOU_tate8 - 2; y++) {
            for (x = 2; x < HOW_MANY_SINDOU_yoko8 - 2; x++) {
                if (y % 2 == 0 && x % 2 == 0){
                    q1 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y][x - 2] + C8 * (7 * dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + Cs * (dtVn8[y][x - 2] - dtVn4[y / 2][x / 2]))) / (8 * C8 + Cs + Cj);
                    q2 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y][x + 2] + C8 * (-dtVn8[y][x - 2] + 7 * dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + Cs * (dtVn8[y][x + 2] - dtVn4[y / 2][x / 2]))) / (8 * C8 + Cs + Cj);
                    q3 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 2][x] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] + 7 * dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + Cs * (dtVn8[y - 2][x] - dtVn4[y / 2][x / 2]))) / (8 * C8 + Cs + Cj);
                    q4 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 2][x] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - 7 * dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + Cs * (dtVn8[y][x - 2] - dtVn4[y / 2][x / 2]))) / (8 * C8 + Cs + Cj);
                    q5 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 1][x - 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 7 * dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + Cs * (dtVn8[y - 1][x - 1] - dtVn4[y / 2][x / 2]))) / (8 * C8 + Cs + Cj);
                    q6 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 1][x + 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] + 7 * dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + Cs * (dtVn8[y - 1][x + 1] - dtVn4[y / 2][x / 2]))) / (8 * C8 + Cs + Cj);
                    q7 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 1][x - 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] + 7 * dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + Cs * (dtVn8[y + 1][x - 1] - dtVn4[y / 2][x / 2]))) / (8 * C8 + Cs + Cj);
                    q8 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 1][x + 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] + 7 * dtVn8[y + 1][x + 1]) + Cs * (dtVn8[y + 1][x + 1] - dtVn4[y / 2][x / 2]))) / (8 * C8 + Cs + Cj);
                    q9 = (Cs*(-dtQ8[y][x] + Cj * dtVn4[y / 2][x / 2] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1] + 8 * dtVn4[y / 2][x / 2]))) / (8 * C8 + Cs + Cj);
                }
                else{
                    q1 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y][x - 2] + C8 * (7 * dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) )) / (8 * C8 + Cj);
                    q2 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y][x + 2] + C8 * (-dtVn8[y][x - 2] + 7 * dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (8 * C8 + Cj);
                    q3 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 2][x] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] + 7 * dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (8 * C8 + Cj);
                    q4 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 2][x] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - 7 * dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (8 * C8 + Cj);
                    q5 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 1][x - 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 7 * dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (8 * C8 + Cj);
                    q6 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 1][x + 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] + 7 * dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (8 * C8 + Cj);
                    q7 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 1][x - 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] + 7 * dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (8 * C8 + Cj);
                    q8 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 1][x + 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] + 7 * dtVn8[y + 1][x + 1]))) / (8 * C8 + Cj);
                    q9 = 0;
                }
                /* 8結合層のVnの更新 */
                dtVn8[y][x] = (q1 + q2 + q3 + q4 + q5 + q6 + q7 + q8 + q9 + dtQ8[y][x]) / Cj;
            }
        }

        for (y = 1; y < HOW_MANY_SINDOU_tate4 - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko4 - 1; x++) {
                q1 = (C4*(-dtQ4[y][x] + Cj * dtVn4[y][x - 1] + C4 * (3 * dtVn4[y][x - 1] - dtVn4[y][x + 1] - dtVn4[y - 1][x] - dtVn4[y + 1][x]) + Cs * (dtVn4[y][x - 1] - dtVn8[2 * y][2 * x]))) / (4 * C4 + Cs + Cj);
                q2 = (C4*(-dtQ4[y][x] + Cj * dtVn4[y][x + 1] + C4 * (-dtVn4[y][x - 1] + 3 * dtVn4[y][x + 1] - dtVn4[y - 1][x] - dtVn4[y + 1][x]) + Cs * (dtVn4[y][x + 1] - dtVn8[2 * y][2 * x]))) / (4 * C4 + Cs + Cj);
                q3 = (C4*(-dtQ4[y][x] + Cj * dtVn4[y - 1][x] + C4 * (-dtVn4[y][x - 1] - dtVn4[y][x + 1] + 3 * dtVn4[y - 1][x] - dtVn4[y + 1][x]) + Cs * (dtVn4[y - 1][x] - dtVn8[2 * y][2 * x]))) / (4 * C4 + Cs + Cj);
                q4 = (C4*(-dtQ4[y][x] + Cj * dtVn4[y + 1][x] + C4 * (-dtVn4[y][x - 1] - dtVn4[y][x + 1] - dtVn4[y - 1][x] + 3 * dtVn4[y + 1][x]) + Cs * (dtVn4[y + 1][x] - dtVn8[2 * y][2 * x]))) / (4 * C4 + Cs + Cj);
                q5 = (Cs*(-dtQ4[y][x] + Cj * dtVn8[2 * y][2 * x] + C4 * (-dtVn4[y][x - 1] - dtVn4[y][x + 1] - dtVn4[y - 1][x] - dtVn4[y + 1][x] + 4 * dtVn8[2 * y][2 * x]))) / (4 * C4 + Cs + Cj);
                /* 4結合層のVnの更新 */
                dtVn4[y][x] = (q1 + q2 + q3 + q4 + q5 + dtQ4[y][x]) / Cj;
            }
        }



        /* Vnの出力 */
        if (t > Trecord) {
            for (x = 0; x < HOW_MANY_SINDOU_yoko8 - 1; x++) {
                for (y = 0; y < HOW_MANY_SINDOU_tate8 - 1; y++) {
                    if ((x + y) % 2 == 0) {
                        if (y == 0) {
                            printf("%d %d %f\n", x, y, -dtVn8[y + 2][x + 2]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate8 - 2) {
                            printf("%d %d %f\n", x, y, -dtVn8[y][x + 2]);
                        }
                        else {
                            if (y % 2 == 0){
                                printf("%d %d %f\n", x, y, -dtVn8[y + 1][x + 2]);
                                printf("%d %d %f\n", x, y, -dtVn8[y + 2][x + 2]);
                            }
                            else{
                                printf("%d %d %f\n", x, y, dtVn8[y + 1][x + 2]);
                                printf("%d %d %f\n", x, y, dtVn8[y + 2][x + 2]);
                            }
                        }
                    }
                    else {
                        if (y == 0) {
                            printf("%d %d %f\n", x, y, dtVn8[y + 2][x + 2]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate8 - 2) {
                            printf("%d %d %f\n", x, y, dtVn8[y][x + 2]);
                        }
                        else {
                            if (y % 2 == 0){
                                printf("%d %d %f\n", x, y, dtVn8[y + 1][x + 2]);
                                printf("%d %d %f\n", x, y, dtVn8[y + 2][x + 2]);
                            }
                            else{
                                printf("%d %d %f\n", x, y, -dtVn8[y + 1][x + 2]);
                                printf("%d %d %f\n", x, y, -dtVn8[y + 2][x + 2]);
                            }
                        }
                    }
                }
                printf("\n");
                for (y = 0; y < HOW_MANY_SINDOU_tate8 - 1; y++) {
                    if ((x + y) % 2 == 0) {
                        if (y == 0) {
                            printf("%d %d %f\n", x + 1, y, -dtVn8[y + 2][x + 2]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate8 - 2) {
                            printf("%d %d %f\n", x + 1, y, -dtVn8[y][x + 2]);
                        }
                        else {
                            if (y % 2 == 0){
                                printf("%d %d %f\n", x + 1, y, -dtVn8[y + 1][x + 2]);
                                printf("%d %d %f\n", x + 1, y, -dtVn8[y + 2][x + 2]);
                            }
                            else{
                                printf("%d %d %f\n", x + 1, y, dtVn8[y + 1][x + 2]);
                                printf("%d %d %f\n", x + 1, y, dtVn8[y + 2][x + 2]);
                            }
                        }
                    }
                    else {
                        if (y == 0) {
                            printf("%d %d %f\n", x + 1, y, dtVn8[y + 2][x + 2]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate8 - 2) {
                            printf("%d %d %f\n", x + 1, y, dtVn8[y][x + 2]);
                        }
                        else {
                            if (y % 2 == 0){
                                printf("%d %d %f\n", x + 1, y, dtVn8[y + 1][x + 2]);
                                printf("%d %d %f\n", x + 1, y, dtVn8[y + 2][x + 2]);
                            }
                            else{
                                printf("%d %d %f\n", x + 1, y, -dtVn8[y + 1][x + 2]);
                                printf("%d %d %f\n", x + 1, y, -dtVn8[y + 2][x + 2]);
                            }
                        }
                    }
                }
                printf("\n");
            }
            printf("\n");
            Trecord += dt;
        }


        /* dEの計算 */
        for (y = 2; y < HOW_MANY_SINDOU_tate8 - 2; y++) {
            for (x = 2; x < HOW_MANY_SINDOU_yoko8 - 2; x++) {
                if (y % 2 == 0 && x % 2 == 0){
                    if (dtVd8[y][x] > 0) {
                        dtdE8[y][x] = e * (-e + 2 * (dtQ8[y][x] + C8 * (dtVn8[y][x - 2] + dtVn8[y][x + 2] + dtVn8[y - 2][x] + dtVn8[y + 2][x] + dtVn8[y - 1][x - 1] + dtVn8[y - 1][x + 1] + dtVn8[y + 1][x - 1] + dtVn8[y + 1][x + 1]) + Cs * dtVn4[y / 2][x / 2])) / (2 * (8 * C8 + Cs + Cj));
                    }
                    else {
                        dtdE8[y][x] = -e * (e + 2 * (dtQ8[y][x] + C8 * (dtVn8[y][x - 2] + dtVn8[y][x + 2] + dtVn8[y - 2][x] + dtVn8[y + 2][x] + dtVn8[y - 1][x - 1] + dtVn8[y - 1][x + 1] + dtVn8[y + 1][x - 1] + dtVn8[y + 1][x + 1]) + Cs * dtVn4[y / 2][x / 2])) / (2 * (8 * C8 + Cs + Cj));
                    }
                }
                else{
                    if (dtVd8[y][x] > 0) {
                            dtdE8[y][x] = e * (-e + 2 * (dtQ8[y][x] + C8 * (dtVn8[y][x - 2] + dtVn8[y][x + 2] + dtVn8[y - 2][x] + dtVn8[y + 2][x] + dtVn8[y - 1][x - 1] + dtVn8[y - 1][x + 1] + dtVn8[y + 1][x - 1] + dtVn8[y + 1][x + 1]))) / (2 * (8 * C8 + Cj));
                    }
                    else {
                            dtdE8[y][x] = -e * (e + 2 * (dtQ8[y][x] + C8 * (dtVn8[y][x - 2] + dtVn8[y][x + 2] + dtVn8[y - 2][x] + dtVn8[y + 2][x] + dtVn8[y - 1][x - 1] + dtVn8[y - 1][x + 1] + dtVn8[y + 1][x - 1] + dtVn8[y + 1][x + 1]))) / (2 * (8 * C8 + Cj));
                    }
                }
            }
        }

        for (y = 1; y < HOW_MANY_SINDOU_tate4 - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko4 - 1; x++) {
                if (dtVd4[y][x] > 0) {
                        dtdE4[y][x] = e * (-e + 2 * (dtQ4[y][x] + C4 * (dtVn4[y][x - 1] + dtVn4[y][x + 1] + dtVn4[y - 1][x] + dtVn4[y + 1][x]) + Cs * dtVn8[2 * y][2 * x])) / (2 * (4 * C4 + Cs + Cj));
                }
                else {
                        dtdE4[y][x] = -e * (e + 2 * (dtQ4[y][x] + C4 * (dtVn4[y][x - 1] + dtVn4[y][x + 1] + dtVn4[y - 1][x] + dtVn4[y + 1][x]) + Cs * dtVn8[2 * y][2 * x])) / (2 * (4 * C4 + Cs + Cj));
                }
            }
        }

        Tmin = dt;
        tempx = 0;
        tempy = 0;

        if (t > record_timing * 0.9) {
            /* dEの評価 */
            for (y = 2; y < HOW_MANY_SINDOU_tate8 - 2; y++) {
                for (x = 2; x < HOW_MANY_SINDOU_yoko8 - 2; x++) {
                    if (dtdE8[y][x] > 0) {
                        r = makerand();
                        Ganma8 = dtdE8[y][x] / (e * e * Rj);
                        T8 = (1 / Ganma8) * log10(1 / r);
                        if (T8 < Tmin) {
                            Tmin = T8;
                            tempx = x;
                            tempy = y;
                            w = 8;
                        }
                    }
                }
            }

            for (y = 1; y < HOW_MANY_SINDOU_tate4 - 1; y++) {
                for (x = 1; x < HOW_MANY_SINDOU_yoko4 - 1; x++) {
                    if (dtdE4[y][x] > 0) {
                        r = makerand();
                        Ganma4 = dtdE4[y][x] / (e * e * Rj);
                        T4 = (1 / Ganma4) * log10(1 / r);
                        if (T4 < Tmin) {
                            Tmin = T4;
                            tempx = x;
                            tempy = y;
                            w = 4;
                        }
                    }
                }
            }

            /* Qの更新 */
            if (w == 8) {
                if (Tmin != dt) {
                    if (dtVd8[tempy][tempx] > 0) {
                        dtQ8[tempy][tempx] -= e;
                    } else {
                        dtQ8[tempy][tempx] += e;
                    }
                }
            }
            else if (w == 4){
                if (Tmin != dt) {
                    if (dtVd4[tempy][tempx] > 0) {
                        dtQ4[tempy][tempx] -= e;
                    } else {
                        dtQ4[tempy][tempx] += e;
                    }
                }
            }
        }

        for (y = 2; y < HOW_MANY_SINDOU_tate8 - 2; y++) {
            for (x = 2; x < HOW_MANY_SINDOU_yoko8 - 2; x++) {
                dtQ8[y][x] += dt * (dtVd8[y][x] - dtVn8[y][x]) / R8;
            }
        }
        for (y = 1; y < HOW_MANY_SINDOU_tate4 - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko4 - 1; x++) {
                dtQ4[y][x] += dt * (dtVd4[y][x] - dtVn4[y][x]) / R4;
            }
        }
        t += Tmin;
    }
}
