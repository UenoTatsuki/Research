#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define e 0.1602 /* 電気素量 */
#define HOW_MANY_SINDOU_tate 22 /* 縦の振動子の数 */
#define HOW_MANY_SINDOU_yoko 22 /* 横の振動子の数 */
#define T_END 1550.0/* 試行時間[ns] */
#define dt 0.1 /* 刻み時間[ns] */
#define record_timing 1500.0 /* 撮影を始めるタイミング[ns] */
#define Trigger_Timing_1 1500.5 /* 1層目にトリガを印加するタイミング[ns] */
#define Trigger_Timing_2 1501.0
#define Trigger_Timing_3 1500.5 /*2層目にトリガを加えるタイミング*/
#define Trigger_Last 10 /* トリガの継続時間[ns] */
#define START_tate 0 /* トリガ電圧をかける縦の位置 */
#define START_yoko 11 /* トリガ電圧をかける横の位置 */

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
    double R1 = 10;//[G]
    double R2 = 10;//[G]
    double R3 = 10;//[G]
    double R4 = 10;//[G]
    double Cj = 10.0;//[aF]
    double C = 2.0;//[aF]
    double Cx = 2.0;//[aF]
    double Cs = 2.0;//[aF]
    double C1 = 0.5;//[aF]
    double C2 = 2.0;//[aF]
    double Vd1 = 0.00266;//[V]
    double Vd2 = 0.00302;//[V]
    double Vd3 = 0.00635;//[V]
    double Vin = 0.01;//[V]
    double Vin2 = 0.012;//[V]
    double Ganma1, Ganma2, Ganma3, Ganma4, T1, T2, T3, T4, w, r;
    double Tmin;
    double Trecord = record_timing;
    int tempx, tempy;
    int x, y; /* 作業変数 */
    srand((unsigned)time(NULL));

    double dtVd1[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 1層目のバイアス電圧Vdの配列 */
    double dtVd2[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 2層目のバイアス電圧Vdの配列 */
    double dtVd3[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };
    double dtVd4[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };
    double dtVn1[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 1層目のノード電圧Vnの配列 */
    double dtVn2[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 2層目のノード電圧Vnの配列 */
    double dtVn3[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };
    double dtVn4[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };
    double dtQ1[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 1層目のトンネル接合の電荷Qの配列 */
    double dtQ2[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 2層目のトンネル接合の電荷Qの配列 */
    double dtQ3[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };
    double dtQ4[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };
    double dtdE1[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 1層目のdEの配列 */
    double dtdE2[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 2層目のdEの配列 */
    double dtdE3[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };
    double dtdE4[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };
    double q1, q2, q3, q4, q5, q6, q7, q8, q9, q10; /* ノード間のキャパシタの電荷q 左右下上　右から左　左から右 */

    double setting[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };



    /* Vdが正負交互になるように値を代入 */
    for (y = 1; y < HOW_MANY_SINDOU_tate; y++) {
        for (x = 1; x < HOW_MANY_SINDOU_yoko; x++) {
            if (setting[y][x] == 1){
                dtVd1[y][x] = 0;
                dtVd2[y][x] = 0;
                dtVd3[y][x] = 0;
                dtVd4[y][x] = 0;
            } else {
                if ((x + y) % 2 == 0) {
                    dtVd1[y][x] = Vd1;
                    dtVd2[y][x] = Vd2;
                    dtVd3[y][x] = -Vd3;
                    dtVd4[y][x] = -Vd3;
                } else {
                    dtVd1[y][x] = -Vd1;
                    dtVd2[y][x] = -Vd2;
                    dtVd3[y][x] = Vd3;
                    dtVd4[y][x] = Vd3;
                }
            }
        }
    }

    while (t <= T_END) {

       /* 1層目でトリガを印加 */
        if (t > Trigger_Timing_1 && t < Trigger_Timing_1 + Trigger_Last) {
            dtVn1[START_tate][START_yoko] = Vin;
        } else {
            dtVn1[START_tate][START_yoko] = 0;
        }

        if (t > Trigger_Timing_2 && t < Trigger_Timing_2 + Trigger_Last) {
            dtVn1[0][13] = Vin;
            dtVn1[0][9] = Vin;
            dtVn1[9][0] = 0;
            dtVn1[13][0] = 0;
        } else {
            dtVn1[START_tate][START_yoko] = 0;
            dtVn1[0][13] = 0;
            dtVn1[0][9] = 0;
            dtVn1[9][0] = 0;
            dtVn1[13][0] = 0;
        }
        
        /* 2層目でトリガを印加 */
        if (t > Trigger_Timing_3 && t < Trigger_Timing_3 + Trigger_Last) {
            dtVn2[START_tate][START_yoko] = 0;
            dtVn2[0][12] = -Vin;
            dtVn2[0][10] = -Vin;
            dtVn2[9][0] = 0;
            dtVn2[11][0] = 0;
            dtVn2[13][0] = 0;
        } else{
            dtVn2[START_tate][START_yoko] = 0;
            dtVn2[0][13] = 0;
            dtVn2[0][9] = 0;
            dtVn2[11][0] = 0;
            dtVn2[9][0] = 0;
            dtVn2[13][0] = 0;
        }


        /* qの更新 */
        for (y = 1; y < HOW_MANY_SINDOU_tate - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko - 1; x++) {
                
                q1 = (C*(-dtQ1[y][x] + Cj * dtVn1[y][x - 1] + C * (3 * dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x]) + Cx * (4 * dtVn1[y][x - 1] - dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + C1 * (dtVn1[y][x - 1] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 4 * Cx + 2 * C1 + Cj);
                q2 = (C*(-dtQ1[y][x] + Cj * dtVn1[y][x + 1] + C * (-dtVn1[y][x - 1] + 3 * dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x]) + Cx * (4 * dtVn1[y][x + 1] - dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + C1 * (dtVn1[y][x + 1] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 4 * Cx + 2 * C1 + Cj);
                q3 = (C*(-dtQ1[y][x] + Cj * dtVn1[y - 1][x] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] + 3 * dtVn1[y - 1][x] - dtVn1[y + 1][x]) + Cx * (4 * dtVn1[y - 1][x] - dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + C1 * (dtVn1[y - 1][x] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 4 * Cx + 2 * C1 + Cj);
                q4 = (C*(-dtQ1[y][x] + Cj * dtVn1[y + 1][x] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] + 3 * dtVn1[y + 1][x]) + Cx * (4 * dtVn1[y + 1][x] - dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + C1 * (dtVn1[y + 1][x] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 4 * Cx + 2 * C1 + Cj);
                q5 = (Cx*(-dtQ1[y][x] + Cj * dtVn1[y - 1][x - 1] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn1[y - 1][x - 1]) + Cx * (3 * dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + C1 * (dtVn1[y - 1][x - 1] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 4 * Cx + 2 * C1 + Cj);
                q6 = (Cx*(-dtQ1[y][x] + Cj * dtVn1[y - 1][x + 1] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn1[y - 1][x + 1]) + Cx * (-dtVn1[y - 1][x - 1] + 3 * dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + C1 * (dtVn1[y - 1][x + 1] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 4 * Cx + 2 * C1 + Cj);
                q7 = (Cx*(-dtQ1[y][x] + Cj * dtVn1[y + 1][x - 1] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn1[y + 1][x - 1]) + Cx * (-dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] + 3 * dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + C1 * (dtVn1[y + 1][x - 1] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 4 * Cx + 2 * C1 + Cj);
                q8 = (Cx*(-dtQ1[y][x] + Cj * dtVn1[y + 1][x + 1] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn1[y + 1][x + 1]) + Cx * (-dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] + 3 * dtVn1[y + 1][x + 1]) + C1 * (dtVn1[y + 1][x + 1] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 4 * Cx + 2 * C1 + Cj);
                q9 = (C1*(-dtQ1[y][x] + Cj * dtVn3[y][x] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn3[y][x]) + Cx * (-dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1] + 4 * dtVn3[y][x]) + C1 * (dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 4 * Cx + 2 * C1 + Cj);
                q10 = (C1*(-dtQ1[y][x] + Cj * dtVn4[y][x] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn4[y][x]) + Cx * (-dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1] + 4 * dtVn4[y][x]) + C1 * (-dtVn3[y][x] + dtVn4[y][x]))) / (4 * C + 4 * Cx + 2 * C1 + Cj);
                /* Vnの更新 */
                dtVn1[y][x] = (q1 + q2 + q3 + q4 + q5 + q6 + q7 + q8 + q9 + q10 + dtQ1[y][x]) / Cj;
            }
        }

        for (y = 1; y < HOW_MANY_SINDOU_tate - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko - 1; x++) {
                q1 = (C*(-dtQ2[y][x] + Cj * dtVn2[y][x - 1] + C * (3 * dtVn2[y][x - 1] - dtVn2[y][x + 1] - dtVn2[y - 1][x] - dtVn2[y + 1][x]) + C2 * (dtVn2[y][x - 1] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 2 * C2 + Cj);
                q2 = (C*(-dtQ2[y][x] + Cj * dtVn2[y][x + 1] + C * (-dtVn2[y][x - 1] + 3 * dtVn2[y][x + 1] - dtVn2[y - 1][x] - dtVn2[y + 1][x]) + C2 * (dtVn2[y][x + 1] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 2 * C2 + Cj);
                q3 = (C*(-dtQ2[y][x] + Cj * dtVn2[y - 1][x] + C * (-dtVn2[y][x - 1] - dtVn2[y][x + 1] + 3 * dtVn2[y - 1][x] - dtVn2[y + 1][x]) + C2 * (dtVn2[y - 1][x] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 2 * C2 + Cj);
                q4 = (C*(-dtQ2[y][x] + Cj * dtVn2[y + 1][x] + C * (-dtVn2[y][x - 1] - dtVn2[y][x + 1] - dtVn2[y - 1][x] + 3 * dtVn2[y + 1][x]) + C2 * (dtVn2[y + 1][x] - dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 2 * C2 + Cj);
                q5 = (C2*(-dtQ2[y][x] + Cj * dtVn3[y][x] + C * (-dtVn2[y][x - 1] - dtVn2[y][x + 1] - dtVn2[y - 1][x] - dtVn2[y + 1][x] + 4 * dtVn3[y][x]) + C2 * (dtVn3[y][x] - dtVn4[y][x]))) / (4 * C + 2 * C2 + Cj);
                q6 = (C2*(-dtQ2[y][x] + Cj * dtVn4[y][x] + C * (-dtVn2[y][x - 1] - dtVn2[y][x + 1] - dtVn2[y - 1][x] - dtVn2[y + 1][x] + 4 * dtVn4[y][x]) + C2 * (-dtVn3[y][x] + dtVn4[y][x]))) / (4 * C + 2 * C2 + Cj);
                q7 = (C1*(-dtQ3[y][x] + Cj * dtVn1[y][x] + C2 * (dtVn1[y][x] - dtVn2[y][x]))) / (C1 + C2 + Cj);
                q8 = (C2*(-dtQ3[y][x] + Cj * dtVn2[y][x] + C1 * (dtVn2[y][x] - dtVn1[y][x]))) / (C1 + C2 + Cj);
                q9 = (C1*(-dtQ4[y][x] + Cj * dtVn1[y][x] + C2 * (dtVn1[y][x] - dtVn2[y][x]))) / (C1 + C2 + Cj);
                q10 = (C2*(-dtQ4[y][x] + Cj * dtVn2[y][x] + C1 * (dtVn2[y][x] - dtVn1[y][x]))) / (C1 + C2 + Cj);
                /* Vnの更新 */
                dtVn2[y][x] = (q1 + q2 + q3 + q4 + q5 + q6 + dtQ2[y][x]) / Cj;
                dtVn3[y][x] = (q7 + q8 + dtQ3[y][x]) / Cj;
                dtVn4[y][x] = (q9 + q10 + dtQ4[y][x]) / Cj;
            }
        }



        /* Vnの出力 */
        if (t > Trecord) {
            for (x = 0; x < HOW_MANY_SINDOU_yoko - 1; x++) {
                for (y = 0; y < HOW_MANY_SINDOU_tate; y++) {
                    if ((x + y) % 2 == 0) {
                        if (y == 0) {
                           printf("%d %d %f\n", x, y, dtVn1[y + 1][x + 1]);
//                            printf("%d %d %f\n", x, y, dtVn2[y + 1][x + 1]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate - 1) {
                           printf("%d %d %f\n", x, y, -dtVn1[y][x + 1]);
//                            printf("%d %d %f\n", x, y, -dtVn2[y][x + 1]);
                        }
                        else {
                            printf("%d %d %f\n", x, y, -dtVn1[y][x + 1]);
                            printf("%d %d %f\n", x, y, dtVn1[y + 1][x + 1]);
//                            printf("%d %d %f\n", x, y, -dtVn2[y][x + 1]);
//                            printf("%d %d %f\n", x, y, dtVn2[y + 1][x + 1]);
                        }
                    }
                    else {
                        if (y == 0) {
                            printf("%d %d %f\n", x, y, -dtVn1[y + 1][x + 1]);
//                            printf("%d %d %f\n", x, y, -dtVn2[y + 1][x + 1]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate - 1) {
                            printf("%d %d %f\n", x, y, dtVn1[y][x + 1]);
//                            printf("%d %d %f\n", x, y, dtVn2[y][x + 1]);
                        }
                        else {
                            printf("%d %d %f\n", x, y, dtVn1[y][x + 1]);
                            printf("%d %d %f\n", x, y, -dtVn1[y + 1][x + 1]);
//                            printf("%d %d %f\n", x, y, dtVn2[y][x + 1]);
//                            printf("%d %d %f\n", x, y, -dtVn2[y + 1][x + 1]);
                        }
                    }
                }
                printf("\n");
                for (y = 0; y < HOW_MANY_SINDOU_tate; y++) {
                    if ((x + y) % 2 == 0) {
                        if (y == 0) {
                            printf("%d %d %f\n", x + 1, y, dtVn1[y + 1][x + 1]);
//                            printf("%d %d %f\n", x + 1, y, dtVn2[y + 1][x + 1]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate - 1) {
                            printf("%d %d %f\n", x + 1, y, -dtVn1[y][x + 1]);
//                            printf("%d %d %f\n", x + 1, y, -dtVn2[y][x + 1]);
                        }
                        else {
                            printf("%d %d %f\n", x + 1, y, -dtVn1[y][x + 1]);
                            printf("%d %d %f\n", x + 1, y, dtVn1[y + 1][x + 1]);
//                            printf("%d %d %f\n", x + 1, y, -dtVn2[y][x + 1]);
//                            printf("%d %d %f\n", x + 1, y, dtVn2[y + 1][x + 1]);
                        }
                    }
                    else {
                        if (y == 0) {
                            printf("%d %d %f\n", x + 1, y, -dtVn1[y + 1][x + 1]);
//                            printf("%d %d %f\n", x + 1, y, -dtVn2[y + 1][x + 1]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate - 1) {
                            printf("%d %d %f\n", x + 1, y, dtVn1[y][x + 1]);
//                            printf("%d %d %f\n", x + 1, y, dtVn2[y][x + 1]);
                        }
                        else {
                            printf("%d %d %f\n", x + 1, y, dtVn1[y][x + 1]);
                            printf("%d %d %f\n", x + 1, y, -dtVn1[y + 1][x + 1]);
//                            printf("%d %d %f\n", x + 1, y, dtVn2[y][x + 1]);
//                            printf("%d %d %f\n", x + 1, y, -dtVn2[y + 1][x + 1]);
                        }
                    }
                }
                printf("\n");
            }
            printf("\n");
            Trecord += dt;
        }

        /* dEの計算 */
        for (y = 1; y < HOW_MANY_SINDOU_tate - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko - 1; x++) {
                if (dtVd1[y][x] > 0) {
                        dtdE1[y][x] = e * (-e + 2 * (dtQ1[y][x] + C * (dtVn1[y][x - 1] + dtVn1[y][x + 1] + dtVn1[y - 1][x] + dtVn1[y + 1][x]) + Cx * (dtVn1[y - 1][x - 1] + dtVn1[y - 1][x + 1] + dtVn1[y + 1][x - 1] + dtVn1[y + 1][x + 1]) + C1 * (dtVn3[y][x] + dtVn4[y][x]))) / (2 * (4 * C + 4 * Cx + 2 * C1 + Cj));
                }
                else {
                        dtdE1[y][x] = -e * (e + 2 * (dtQ1[y][x] + C * (dtVn1[y][x - 1] + dtVn1[y][x + 1] + dtVn1[y - 1][x] + dtVn1[y + 1][x]) + Cx * (dtVn1[y - 1][x - 1] + dtVn1[y - 1][x + 1] + dtVn1[y + 1][x - 1] + dtVn1[y + 1][x + 1]) + C1 * (dtVn3[y][x] + dtVn4[y][x]))) / (2 * (4 * C + 4 * Cx + 2 * C1 + Cj));
                }
                if (dtVd2[y][x] > 0) {
                        dtdE2[y][x] = e * (-e + 2 * (dtQ2[y][x] + C * (dtVn2[y][x - 1] + dtVn2[y][x + 1] + dtVn2[y - 1][x] + dtVn2[y + 1][x]) + C2 * (dtVn3[y][x] + dtVn4[y][x]))) / (2 * (4 * C + 2 * C2 + Cj));
                }
                else {
                        dtdE2[y][x] = -e * (e + 2 * (dtQ2[y][x] + C * (dtVn2[y][x - 1] + dtVn2[y][x + 1] + dtVn2[y - 1][x] + dtVn2[y + 1][x]) + C2 * (dtVn3[y][x] + dtVn4[y][x]))) / (2 * (4 * C + 2 * C2 + Cj));
                }
                if (dtVd3[y][x] > 0) {
                        dtdE3[y][x] = e * (-e + 2 * (dtQ3[y][x] + C1 * dtVn1[y][x] + C2 * dtVn2[y][x])) / (2 * (C1 + C2 + Cj));
                }
                else {
                        dtdE3[y][x] = -e * (e + 2 * (dtQ3[y][x] + C1 * dtVn1[y][x] + C2 * dtVn2[y][x])) / (2 * (C1 + C2 + Cj));
                }
                if (dtVd4[y][x] > 0) {
                        dtdE4[y][x] = e * (-e + 2 * (dtQ4[y][x] + C1 * dtVn1[y][x] + C2 * dtVn2[y][x])) / (2 * (C1 + C2 + Cj));
                }
                else {
                        dtdE4[y][x] = -e * (e + 2 * (dtQ4[y][x] + C1 * dtVn1[y][x] + C2 * dtVn2[y][x])) / (2 * (C1 + C2 + Cj));
                }
            }
        }

        Tmin = dt;
        tempx = 0;
        tempy = 0;
        w = 0;

        if (t > record_timing * 0.9) {
            /* dEの評価 */
            for (y = 1; y < HOW_MANY_SINDOU_tate - 1; y++) {
                for (x = 1; x < HOW_MANY_SINDOU_yoko - 1; x++) {
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
                    if (dtdE3[y][x] > 0) {
                        r = makerand();
                        Ganma3 = dtdE3[y][x] / (e * e * Rj);
                        T3 = (1 / Ganma3) * log10(1 / r);
                        if (T3 < Tmin) {
                            Tmin = T3;
                            tempx = x;
                            tempy = y;
                            w = 3;
                        }
                    }
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
            if (w == 1) {
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
            else if (w == 3){
                if (Tmin != dt) {
                    if (dtVd3[tempy][tempx] > 0) {
                        dtQ3[tempy][tempx] -= e;
                    } else {
                        dtQ3[tempy][tempx] += e;
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

        for (y = 1; y < HOW_MANY_SINDOU_tate - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko - 1; x++) {
                dtQ1[y][x] += dt * (dtVd1[y][x] - dtVn1[y][x]) / R1;
                dtQ2[y][x] += dt * (dtVd2[y][x] - dtVn2[y][x]) / R2;
                dtQ3[y][x] += dt * (dtVd3[y][x] - dtVn3[y][x]) / R3;
                dtQ4[y][x] += dt * (dtVd4[y][x] - dtVn4[y][x]) / R4;
            }
        }
        t += Tmin;
    }
}
