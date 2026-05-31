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
#define Trigger_Timing_2 1500.5 //1層目の両側でトリガを印加するタイミング
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
    double R8 = 12;//[G]
    double R4 = 12;
    double R1 = 12;
    double Cj = 10.0;//[aF]
    double C8 = 2.5;//[aF]
    double Cx = 2.0;//[aF]
    double C4 = 1.5;//[aF]
    double C1 = 1.0;//[aF]
    double C2 = 2.5;//[aF]
    double Vd8 = 0.00255;//[V]
    double Vd4 = 0.00402;//[V]
    double Vd1 = 0.00567;//[V]
    double Vin = 0.008;//[V]
    double Ganma8, Ganma4, Ganma1, Ganma2, T8, T4, T1, T2, r, w;
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

    //結合振動子１個目の設定
    double dtVd1[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* バイアス電圧Vdの配列 */
    double dtVn1[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* ノード電圧Vnの配列 */
    double dtQ1[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* トンネル接合の電荷Qの配列 */
    double dtdE1[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* dEの配列 */

    //結合振動子２個目の設定
    double dtVd2[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* バイアス電圧Vdの配列 */
    double dtVn2[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* ノード電圧Vnの配列 */
    double dtQ2[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* トンネル接合の電荷Qの配列 */
    double dtdE2[HOW_MANY_SINDOU_tate4][HOW_MANY_SINDOU_yoko4] = { 0 };/* dEの配列 */

    double q1, q2, q3, q4, q5, q6, q7, q8, q9, q10; /* ノード間のキャパシタの電荷q 左右下上　右から左　左から右 */

    double setting[HOW_MANY_SINDOU_tate8][HOW_MANY_SINDOU_yoko8] = { 0 };



    /* 8結合層Vdが正負交互になるように値を代入 */
    for (y = 2; y < HOW_MANY_SINDOU_tate8; y++) {
        for (x = 2; x < HOW_MANY_SINDOU_yoko8; x++) {
            if (setting[y][x] == 1){
                dtVd8[y][x] = 0;
            } else {
                if (y % 2 == 0){
                    if ((x + y) % 2 == 0) {
                        dtVd8[y][x] = Vd8;
                    } else {
                        dtVd8[y][x] = -Vd8;
                    }
                }
                else{
                    if ((x + y) % 2 == 0) {
                        dtVd8[y][x] = -Vd8;
                    } else {
                        dtVd8[y][x] = Vd8;
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
                    dtVd4[y][x] = -Vd4;
                    dtVd1[y][x] = -Vd1;
                    dtVd2[y][x] = 0;
                } else {
                    dtVd4[y][x] = Vd4;
                    dtVd1[y][x] = Vd1;
                    dtVd2[y][x] = 0;
                }
            }
        }
    }

   dtVd1[1][1] = 0;

    while (t <= T_END) {

        /* トリガを印加 */
        if (t > Trigger_Timing_1 && t < Trigger_Timing_1 + Trigger_Last) {
            dtVn8[START_tate][START_yoko] = 0;
        }
        else {
            dtVn8[START_tate][START_yoko] = 0;
        }
        if (t > Trigger_Timing_2 && t < Trigger_Timing_2 + Trigger_Last) {
            dtVn8[0][10] = Vin;
            dtVn8[0][8] = -Vin;
            dtVn8[1][9] = Vin;
            dtVn8[10][0] = Vin;
            dtVn8[8][0] = -Vin;
            dtVn8[9][1] = Vin;
        }
        else {
            dtVn8[0][10] = 0;
            dtVn8[0][8] = 0;
            dtVn8[1][9] = 0;
            dtVn8[10][0] = 0;
            dtVn8[8][0] = 0;
            dtVn8[9][1] = 0;
        }
        if (t > Trigger_Timing_3 && t < Trigger_Timing_3 + Trigger_Last) {
            dtVn4[1][1] = Vin;
            dtVn4[0][2] = Vin;
            dtVn4[2][0] = Vin;
        }
        else {
            dtVn4[1][1] = 0;
            dtVn4[0][2] = 0;
            dtVn4[2][0] = 0;
        }


        /* qの更新 */
        for (y = 2; y < HOW_MANY_SINDOU_tate8 - 2; y++) {
            for (x = 2; x < HOW_MANY_SINDOU_yoko8 - 2; x++) {
                if (y % 2 == 0 && x % 2 == 0){
                    q1 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y][x - 2] + C8 * (3 * dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y][x - 2] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y][x - 2] - dtVn1[y / 2][x / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q2 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y][x + 2] + C8 * (-dtVn8[y][x - 2] + 3 * dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y][x + 2] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y][x + 2] - dtVn1[y / 2][x / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q3 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 2][x] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] + 3 * dtVn8[y - 2][x] - dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y - 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y - 2][x] - dtVn1[y / 2][x / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q4 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 2][x] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] + 3 * dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y + 2][x] - dtVn1[y / 2][x / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q5 = (Cx*(-dtQ8[y][x] + Cj * dtVn8[y - 1][x - 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y - 1][x - 1]) + Cx * (3 * dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y - 1][x - 1] - dtVn1[y / 2][x / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q6 = (Cx*(-dtQ8[y][x] + Cj * dtVn8[y - 1][x + 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y - 1][x + 1]) + Cx * (-dtVn8[y - 1][x - 1] + 3 * dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y - 1][x + 1] - dtVn1[y / 2][x / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q7 = (Cx*(-dtQ8[y][x] + Cj * dtVn8[y + 1][x - 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y + 1][x - 1]) + Cx * (-dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] + 3 * dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y + 1][x - 1] - dtVn1[y / 2][x / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q8 = (Cx*(-dtQ8[y][x] + Cj * dtVn8[y + 1][x + 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y + 1][x + 1]) + Cx * (-dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] + 3 * dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y + 1][x + 1] - dtVn1[y / 2][x / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q9 = (C1*(-dtQ8[y][x] + Cj * dtVn1[y / 2][x / 2] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn1[y / 2][x / 2]) + Cx * (-dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1] + 4 * dtVn1[y / 2][x / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                }
                else if ((x + y) % 2 == 0){
                    q1 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y][x - 2] + C8 * (3 * dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y][x - 2] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y][x - 2] - dtVn2[(y - 1) / 2][(x - 1) / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q2 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y][x + 2] + C8 * (-dtVn8[y][x - 2] + 3 * dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y][x + 2] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y][x + 2] - dtVn2[(y - 1) / 2][(x - 1) / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q3 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 2][x] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] + 3 * dtVn8[y - 2][x] - dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y - 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y - 2][x] - dtVn2[(y - 1) / 2][(x - 1) / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q4 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 2][x] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] + 3 * dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y + 2][x] - dtVn2[(y - 1) / 2][(x - 1) / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q5 = (Cx*(-dtQ8[y][x] + Cj * dtVn8[y - 1][x - 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y - 1][x - 1]) + Cx * (3 * dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y - 1][x - 1] - dtVn2[(y - 1) / 2][(x - 1) / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q6 = (Cx*(-dtQ8[y][x] + Cj * dtVn8[y - 1][x + 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y - 1][x + 1]) + Cx * (-dtVn8[y - 1][x - 1] + 3 * dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y - 1][x + 1] - dtVn2[(y - 1) / 2][(x - 1) / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q7 = (Cx*(-dtQ8[y][x] + Cj * dtVn8[y + 1][x - 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y + 1][x - 1]) + Cx * (-dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] + 3 * dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y + 1][x - 1] - dtVn2[(y - 1) / 2][(x - 1) / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q8 = (Cx*(-dtQ8[y][x] + Cj * dtVn8[y + 1][x + 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y + 1][x + 1]) + Cx * (-dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] + 3 * dtVn8[y + 1][x + 1]) + C1 * (dtVn8[y + 1][x + 1] - dtVn2[(y - 1) / 2][(x - 1) / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                    q9 = (C1*(-dtQ8[y][x] + Cj * dtVn2[(y - 1) / 2][(x - 1) / 2] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn2[(y - 1) / 2][(x - 1) / 2]) + Cx * (-dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1] + 4 * dtVn2[(y - 1) / 2][(x - 1) / 2]))) / (4 * C8 + 4 * Cx + C1 + Cj);
                }
                else{
                    q1 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y][x - 2] + C8 * (3 * dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y][x - 2] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (4 * C8 + 4 * Cx + Cj);
                    q2 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y][x + 2] + C8 * (-dtVn8[y][x - 2] + 3 * dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y][x + 2] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (4 * C8 + 4 * Cx + Cj);
                    q3 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 2][x] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] + 3 * dtVn8[y - 2][x] - dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y - 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (4 * C8 + 4 * Cx + Cj);
                    q4 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 2][x] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] + 3 * dtVn8[y + 2][x]) + Cx * (4 * dtVn8[y + 2][x] - dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (4 * C8 + 4 * Cx + Cj);
                    q5 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 1][x - 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y - 1][x - 1]) + Cx * (3 * dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (4 * C8 + 4 * Cx + Cj);
                    q6 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y - 1][x + 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y - 1][x + 1]) + Cx * (-dtVn8[y - 1][x - 1] + 3 * dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (4 * C8 + 4 * Cx + Cj);
                    q7 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 1][x - 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y + 1][x - 1]) + Cx * (-dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] + 3 * dtVn8[y + 1][x - 1] - dtVn8[y + 1][x + 1]))) / (4 * C8 + 4 * Cx + Cj);
                    q8 = (C8*(-dtQ8[y][x] + Cj * dtVn8[y + 1][x + 1] + C8 * (-dtVn8[y][x - 2] - dtVn8[y][x + 2] - dtVn8[y - 2][x] - dtVn8[y + 2][x] + 4 * dtVn8[y + 1][x + 1]) + Cx * (-dtVn8[y - 1][x - 1] - dtVn8[y - 1][x + 1] - dtVn8[y + 1][x - 1] + 3 * dtVn8[y + 1][x + 1]))) / (4 * C8 + 4 * Cx + Cj);
                    q9 = 0;
                }
                /* 8結合層のVnの更新 */
                dtVn8[y][x] = (q1 + q2 + q3 + q4 + q5 + q6 + q7 + q8 + q9 + dtQ8[y][x]) / Cj;
            }
        }

        for (y = 1; y < HOW_MANY_SINDOU_tate4 - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko4 - 1; x++) {
                q1 = (C4*(-dtQ4[y][x] + Cj * dtVn4[y][x - 1] + C4 * (3 * dtVn4[y][x - 1] - dtVn4[y][x + 1] - dtVn4[y - 1][x] - dtVn4[y + 1][x]) + C2 * (dtVn4[y][x - 1] - dtVn1[y][x]))) / (4 * C4 + C2 + Cj);
                q2 = (C4*(-dtQ4[y][x] + Cj * dtVn4[y][x + 1] + C4 * (-dtVn4[y][x - 1] + 3 * dtVn4[y][x + 1] - dtVn4[y - 1][x] - dtVn4[y + 1][x]) + C2 * (dtVn4[y][x + 1] - dtVn1[y][x]))) / (4 * C4 + C2 + Cj);
                q3 = (C4*(-dtQ4[y][x] + Cj * dtVn4[y - 1][x] + C4 * (-dtVn4[y][x - 1] - dtVn4[y][x + 1] + 3 * dtVn4[y - 1][x] - dtVn4[y + 1][x]) + C2 * (dtVn4[y - 1][x] - dtVn1[y][x]))) / (4 * C4 + C2 + Cj);
                q4 = (C4*(-dtQ4[y][x] + Cj * dtVn4[y + 1][x] + C4 * (-dtVn4[y][x - 1] - dtVn4[y][x + 1] - dtVn4[y - 1][x] + 3 * dtVn4[y + 1][x]) + C2 * (dtVn4[y + 1][x] - dtVn1[y][x]))) / (4 * C4 + C2 + Cj);
                q5 = (C2*(-dtQ4[y][x] + Cj * dtVn1[y][x] + C4 * (-dtVn4[y][x - 1] - dtVn4[y][x + 1] - dtVn4[y - 1][x] - dtVn4[y + 1][x] + 4 * dtVn1[y][x]))) / (4 * C4 + C2 + Cj);
                q7 = (C1*(-dtQ1[y][x] + Cj * dtVn8[2 * y][2 * x] + C2 * (dtVn8[2 * y][2 * x] - dtVn4[y][x]))) / (C1 + C2 + Cj);
                q8 = (C2*(-dtQ1[y][x] + Cj * dtVn4[y][x] + C1 * (-dtVn8[2 * y][2 * x] + dtVn4[y][x]))) / (C1 + C2 + Cj);
                q9 = (C1*(-dtQ2[y][x] + Cj * dtVn8[(2 * y) + 1][(2 * x) + 1])) / (C1 + Cj);
                /* 4結合層のVnの更新 */
                dtVn4[y][x] = (q1 + q2 + q3 + q4 + q5 + dtQ4[y][x]) / Cj;
                dtVn1[y][x] = (q7 + q8 + dtQ1[y][x]) / Cj;
                dtVn2[y][x] = (q9 + dtQ2[y][x]) / Cj;
            }
        }



        /* Vnの出力 */
        printf("%f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",t, dtVn4[1][5], dtVn4[10][14], dtVn4[14][10], dtVn8[4][14], dtVn1[3][15], dtVn1[4][15], dtVn1[3][14], dtVn1[4][14], dtVn2[2][2], dtVn1[3][3], dtVn2[3][3], dtVn2[2][2], dtVn2[2][3]);


        /* dEの計算 */
        for (y = 2; y < HOW_MANY_SINDOU_tate8 - 2; y++) {
            for (x = 2; x < HOW_MANY_SINDOU_yoko8 - 2; x++) {
                if (y % 2 == 0 && x % 2 == 0){
                    if (dtVd8[y][x] > 0) {
                        dtdE8[y][x] = e * (-e + 2 * (dtQ8[y][x] + C8 * (dtVn8[y][x - 2] + dtVn8[y][x + 2] + dtVn8[y - 2][x] + dtVn8[y + 2][x]) + Cx * (dtVn8[y - 1][x - 1] + dtVn8[y - 1][x + 1] + dtVn8[y + 1][x - 1] + dtVn8[y + 1][x + 1]) + C1 * dtVn1[y / 2][x / 2])) / (2 * (4 * C8 + 4 * Cx + C1 + Cj));
                    }
                    else {
                        dtdE8[y][x] = -e * (e + 2 * (dtQ8[y][x] + C8 * (dtVn8[y][x - 2] + dtVn8[y][x + 2] + dtVn8[y - 2][x] + dtVn8[y + 2][x]) + Cx * (dtVn8[y - 1][x - 1] + dtVn8[y - 1][x + 1] + dtVn8[y + 1][x - 1] + dtVn8[y + 1][x + 1]) + C1 * dtVn1[y / 2][x / 2])) / (2 * (4 * C8 + 4 * Cx + C1 + Cj));
                    }
                }
                else if ((x + y) % 2 == 0){
                    if (dtVd8[y][x] > 0) {
                        dtdE8[y][x] = e * (-e + 2 * (dtQ8[y][x] + C8 * (dtVn8[y][x - 2] + dtVn8[y][x + 2] + dtVn8[y - 2][x] + dtVn8[y + 2][x]) + Cx * (dtVn8[y - 1][x - 1] + dtVn8[y - 1][x + 1] + dtVn8[y + 1][x - 1] + dtVn8[y + 1][x + 1]) + C1 * dtVn2[(y - 1) / 2][(x - 1) / 2])) / (2 * (4 * C8 + 4 * Cx + C1 + Cj));
                    }
                    else {
                        dtdE8[y][x] = -e * (e + 2 * (dtQ8[y][x] + C8 * (dtVn8[y][x - 2] + dtVn8[y][x + 2] + dtVn8[y - 2][x] + dtVn8[y + 2][x]) + Cx * (dtVn8[y - 1][x - 1] + dtVn8[y - 1][x + 1] + dtVn8[y + 1][x - 1] + dtVn8[y + 1][x + 1]) + C1 * dtVn2[(y - 1) / 2][(x - 1) / 2])) / (2 * (4 * C8 + 4 * Cx + C1 + Cj));
                    }
                }
                else{
                    if (dtVd8[y][x] > 0) {
                        dtdE8[y][x] = e * (-e + 2 * (dtQ8[y][x] + C8 * (dtVn8[y][x - 2] + dtVn8[y][x + 2] + dtVn8[y - 2][x] + dtVn8[y + 2][x]) + Cx * (dtVn8[y - 1][x - 1] + dtVn8[y - 1][x + 1] + dtVn8[y + 1][x - 1] + dtVn8[y + 1][x + 1]))) / (2 * (4 * C8 + 4 * Cx + Cj));
                    }
                    else {
                        dtdE8[y][x] = -e * (e + 2 * (dtQ8[y][x] + C8 * (dtVn8[y][x - 2] + dtVn8[y][x + 2] + dtVn8[y - 2][x] + dtVn8[y + 2][x]) + Cx * (dtVn8[y - 1][x - 1] + dtVn8[y - 1][x + 1] + dtVn8[y + 1][x - 1] + dtVn8[y + 1][x + 1]))) / (2 * (4 * C8 + 4 * Cx + Cj));
                    }
                }
            }
        }

        for (y = 1; y < HOW_MANY_SINDOU_tate4 - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko4 - 1; x++) {
                if (dtVd4[y][x] > 0) {
                        dtdE4[y][x] = e * (-e + 2 * (dtQ4[y][x] + C4 * (dtVn4[y][x - 1] + dtVn4[y][x + 1] + dtVn4[y - 1][x] + dtVn4[y + 1][x]) + C2 * dtVn1[y][x])) / (2 * (4 * C4 + C2 + Cj));
                }
                else {
                        dtdE4[y][x] = -e * (e + 2 * (dtQ4[y][x] + C4 * (dtVn4[y][x - 1] + dtVn4[y][x + 1] + dtVn4[y - 1][x] + dtVn4[y + 1][x]) + C2 * dtVn1[y][x])) / (2 * (4 * C4 + C2 + Cj));        
                }
                if (dtVd1[y][x] > 0) {
                        dtdE1[y][x] = e * (-e + 2 * (dtQ1[y][x] + C1 * dtVn8[2 * y][2 * x] + C2 * dtVn4[y][x])) / (2 * (C1 + C2 + Cj));
                }
                else {
                        dtdE1[y][x] = -e * (e + 2 * (dtQ1[y][x] + C1 * dtVn8[2 * y][2 * x] + C2 * dtVn4[y][x])) / (2 * (C1 + C2 + Cj));
                }
                if (dtVd2[y][x] > 0) {
                        dtdE2[y][x] = e * (-e + 2 * (dtQ2[y][x] + C1 * dtVn8[(2 * y) + 1][(2 * x) + 1])) / (2 * (C1 + Cj));
                }
                else {
                        dtdE2[y][x] = -e * (e + 2 * (dtQ2[y][x] + C1 * dtVn8[(2 * y) + 1][(2 * x) + 1])) / (2 * (C1 + Cj));
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
                    if (dtdE1[y][x] > 0) {
                        r = makerand();
                        Ganma1 = dtdE1[y][x] / (e * e * Rj);
                        T1 = (1 / Ganma1) * log10(1 / r);
                        if (T1 < Tmin) {
                            Tmin = T1;
                            tempx = x;
                            tempy = y;
                            w = 1;
                        }
                    }
                    if (dtdE2[y][x] > 0) {
                        r = makerand();
                        Ganma2 = dtdE2[y][x] / (e * e * Rj);
                        T2 = (1 / Ganma2) * log10(1 / r);
                        if (T2 < Tmin) {
                            Tmin = T2;
                            tempx = x;
                            tempy = y;
                            w = 2;
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
            else if (w == 1){
                if (Tmin != dt) {
                    if (dtVd1[tempy][tempx] > 0) {
                        dtQ1[tempy][tempx] -= e;
                    } else {
                        dtQ1[tempy][tempx] += e;
                    }
                }
            }
            else if (w == 2){
                if (Tmin != dt) {
                    if (dtVd2[tempy][tempx] > 0) {
                        dtQ2[tempy][tempx] -= e;
                    } else {
                        dtQ2[tempy][tempx] += e;
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
                dtQ1[y][x] += dt * (dtVd1[y][x] - dtVn1[y][x]) / R1;
                dtQ2[y][x] += dt * (dtVd2[y][x] - dtVn2[y][x]) / R1;
            }
        }
        t += Tmin;
    }
}

