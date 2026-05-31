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
#define Trigger_Timing_2 1505.0 /*2層目にトリガを加えるタイミング*/
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
    double Cj = 10.0;//[aF]
    double C = 2.0;//[aF]
    double Cx = 2.2;//[aF]
    double Cs = 2.0;//[aF]
    double Vd1 = 0.00255;//[V]
    double Vd2 = 0.00348;//[V]
    double Vin = 0.01;//[V]
    double Vin2 = 0.012;//[V]
    double Ganma1, Ganma2, T1, T2, w, r;
    double Tmin;
    double Trecord = record_timing;
    int tempx, tempy;
    int x, y; /* 作業変数 */
    srand((unsigned)time(NULL));

    double dtVd1[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 1層目のバイアス電圧Vdの配列 */
    double dtVd2[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 2層目のバイアス電圧Vdの配列 */
    double dtVn1[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 1層目のノード電圧Vnの配列 */
    double dtVn2[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 2層目のノード電圧Vnの配列 */
    double dtQ1[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 1層目のトンネル接合の電荷Qの配列 */
    double dtQ2[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 2層目のトンネル接合の電荷Qの配列 */
    double dtdE1[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 1層目のdEの配列 */
    double dtdE2[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };/* 2層目のdEの配列 */
    double q1, q2, q3, q4, q5, q6, q7, q8, q9; /* ノード間のキャパシタの電荷q 左右下上　右から左　左から右 */

    double setting[HOW_MANY_SINDOU_tate][HOW_MANY_SINDOU_yoko] = { 0 };



    /* Vdが正負交互になるように値を代入 */
    for (y = 1; y < HOW_MANY_SINDOU_tate; y++) {
        for (x = 1; x < HOW_MANY_SINDOU_yoko; x++) {
            if (setting[y][x] == 1){
                dtVd1[y][x] = 0;
                dtVd2[y][x] = 0;
            } else {
                if ((x + y) % 2 == 0) {
                    dtVd1[y][x] = Vd1;
                    dtVd2[y][x] = Vd2;
                } else {
                    dtVd1[y][x] = -Vd1;
                    dtVd2[y][x] = -Vd2;
                }
            }
        }
    }

    while (t <= T_END) {

        /* 1層目でトリガを印加 */
        if (t > Trigger_Timing_1 && t < Trigger_Timing_1 + Trigger_Last) {
            dtVn1[START_tate][START_yoko] = 0;
            dtVn1[0][14] = -Vin;
            dtVn1[0][8] = -Vin;
            dtVn1[9][0] = 0;
            dtVn1[13][0] = 0;
        } else {
            dtVn1[START_tate][START_yoko] = 0;
            dtVn1[0][14] = 0;
            dtVn1[0][8] = 0;
            dtVn1[9][0] = 0;
            dtVn1[13][0] = 0;
        }
        
        /* 2層目でトリガを印加 */
        if (t > Trigger_Timing_2 && t < Trigger_Timing_2 + Trigger_Last) {
            dtVn2[START_tate][START_yoko] = Vin;
            dtVn2[0][13] = Vin;
            dtVn2[0][9] = Vin;
            dtVn2[0][10] = -Vin;
            dtVn2[0][12] = -Vin;
            dtVn2[0][0] = 0;
        } else{
            dtVn2[START_tate][START_yoko] = 0;
            dtVn2[0][13] = 0;
            dtVn2[0][9] = 0;
            dtVn2[0][10] = 0;
            dtVn2[0][12] = 0;
            dtVn2[0][0] = 0;
        }


        /* qの更新 */
        for (y = 1; y < HOW_MANY_SINDOU_tate - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko - 1; x++) {
                
                q1 = (C*(-dtQ1[y][x] + Cj * dtVn1[y][x - 1] + C * (3 * dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x]) + Cx * (4 * dtVn1[y][x - 1] - dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + Cs * (dtVn1[y][x - 1] - dtVn2[y][x]))) / (4 * C + 4 * Cx + Cs + Cj);
                q2 = (C*(-dtQ1[y][x] + Cj * dtVn1[y][x + 1] + C * (-dtVn1[y][x - 1] + 3 * dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x]) + Cx * (4 * dtVn1[y][x + 1] - dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + Cs * (dtVn1[y][x + 1] - dtVn2[y][x]))) / (4 * C + 4 * Cx + Cs + Cj);
                q3 = (C*(-dtQ1[y][x] + Cj * dtVn1[y - 1][x] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] + 3 * dtVn1[y - 1][x] - dtVn1[y + 1][x]) + Cx * (4 * dtVn1[y - 1][x] - dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + Cs * (dtVn1[y - 1][x] - dtVn2[y][x]))) / (4 * C + 4 * Cx + Cs + Cj);
                q4 = (C*(-dtQ1[y][x] + Cj * dtVn1[y + 1][x] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] + 3 * dtVn1[y + 1][x]) + Cx * (4 * dtVn1[y + 1][x] - dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + Cs * (dtVn1[y + 1][x] - dtVn2[y][x]))) / (4 * C + 4 * Cx + Cs + Cj);
                q5 = (Cx*(-dtQ1[y][x] + Cj * dtVn1[y - 1][x - 1] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn1[y - 1][x - 1]) + Cx * (3 * dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + Cs * (dtVn1[y - 1][x - 1] - dtVn2[y][x]))) / (4 * C + 4 * Cx + Cs + Cj);
                q6 = (Cx*(-dtQ1[y][x] + Cj * dtVn1[y - 1][x + 1] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn1[y - 1][x + 1]) + Cx * (-dtVn1[y - 1][x - 1] + 3 * dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + Cs * (dtVn1[y - 1][x + 1] - dtVn2[y][x]))) / (4 * C + 4 * Cx + Cs + Cj);
                q7 = (Cx*(-dtQ1[y][x] + Cj * dtVn1[y + 1][x - 1] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn1[y + 1][x - 1]) + Cx * (-dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] + 3 * dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1]) + Cs * (dtVn1[y + 1][x - 1] - dtVn2[y][x]))) / (4 * C + 4 * Cx + Cs + Cj);
                q8 = (Cx*(-dtQ1[y][x] + Cj * dtVn1[y + 1][x + 1] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn1[y + 1][x + 1]) + Cx * (-dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] + 3 * dtVn1[y + 1][x + 1]) + Cs * (dtVn1[y + 1][x + 1] - dtVn2[y][x]))) / (4 * C + 4 * Cx + Cs + Cj);
                q9 = (Cs*(-dtQ1[y][x] + Cj * dtVn2[y][x] + C * (-dtVn1[y][x - 1] - dtVn1[y][x + 1] - dtVn1[y - 1][x] - dtVn1[y + 1][x] + 4 * dtVn2[y][x]) + Cx * (-dtVn1[y - 1][x - 1] - dtVn1[y - 1][x + 1] - dtVn1[y + 1][x - 1] - dtVn1[y + 1][x + 1] + 4 * dtVn2[y][x]))) / (4 * C + 4 * Cx + Cs + Cj);
                /* Vnの更新 */
                dtVn1[y][x] = (q1 + q2 + q3 + q4 + q5 + q6 + q7 + q8 + q9 + dtQ1[y][x]) / Cj;
            }
        }

        for (y = 1; y < HOW_MANY_SINDOU_tate - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko - 1; x++) {
                q1 = (C*(-dtQ2[y][x] + Cj * dtVn2[y][x - 1] + C * (3 * dtVn2[y][x - 1] - dtVn2[y][x + 1] - dtVn2[y - 1][x] - dtVn2[y + 1][x]) + Cs * (dtVn2[y][x - 1] - dtVn1[y][x]))) / (4 * C + Cs + Cj);
                q2 = (C*(-dtQ2[y][x] + Cj * dtVn2[y][x + 1] + C * (-dtVn2[y][x - 1] + 3 * dtVn2[y][x + 1] - dtVn2[y - 1][x] - dtVn2[y + 1][x]) + Cs * (dtVn2[y][x + 1] - dtVn1[y][x]))) / (4 * C + Cs + Cj);
                q3 = (C*(-dtQ2[y][x] + Cj * dtVn2[y - 1][x] + C * (-dtVn2[y][x - 1] - dtVn2[y][x + 1] + 3 * dtVn2[y - 1][x] - dtVn2[y + 1][x]) + Cs * (dtVn2[y - 1][x] - dtVn1[y][x]))) / (4 * C + Cs + Cj);
                q4 = (C*(-dtQ2[y][x] + Cj * dtVn2[y + 1][x] + C * (-dtVn2[y][x - 1] - dtVn2[y][x + 1] - dtVn2[y - 1][x] + 3 * dtVn2[y + 1][x]) + Cs * (dtVn2[y + 1][x] - dtVn1[y][x]))) / (4 * C + Cs + Cj);
                q5 = (Cs*(-dtQ2[y][x] + Cj * dtVn1[y][x] + C * (-dtVn2[y][x - 1] - dtVn2[y][x + 1] - dtVn2[y - 1][x] - dtVn2[y + 1][x] + 4 * dtVn1[y][x]))) / (4 * C + Cs + Cj);
                /* Vnの更新 */
                dtVn2[y][x] = (q1 + q2 + q3 + q4 + q5 + dtQ2[y][x]) / Cj;
            }
        }



        /* Vnの出力 */
        if (t > Trecord) {
            for (x = 0; x < HOW_MANY_SINDOU_yoko - 1; x++) {
                for (y = 0; y < HOW_MANY_SINDOU_tate; y++) {
                    if ((x + y) % 2 == 0) {
                        if (y == 0) {
//                           printf("%d %d %f\n", x, y, dtVn1[y + 1][x + 1]);
                            printf("%d %d %f\n", x, y, dtVn2[y + 1][x + 1]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate - 1) {
//                           printf("%d %d %f\n", x, y, -dtVn1[y][x + 1]);
                            printf("%d %d %f\n", x, y, -dtVn2[y][x + 1]);
                        }
                        else {
//                            printf("%d %d %f\n", x, y, -dtVn1[y][x + 1]);
//                            printf("%d %d %f\n", x, y, dtVn1[y + 1][x + 1]);
                            printf("%d %d %f\n", x, y, -dtVn2[y][x + 1]);
                            printf("%d %d %f\n", x, y, dtVn2[y + 1][x + 1]);
                        }
                    }
                    else {
                        if (y == 0) {
//                            printf("%d %d %f\n", x, y, -dtVn1[y + 1][x + 1]);
                            printf("%d %d %f\n", x, y, -dtVn2[y + 1][x + 1]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate - 1) {
//                            printf("%d %d %f\n", x, y, dtVn1[y][x + 1]);
                            printf("%d %d %f\n", x, y, dtVn2[y][x + 1]);
                        }
                        else {
//                            printf("%d %d %f\n", x, y, dtVn1[y][x + 1]);
//                            printf("%d %d %f\n", x, y, -dtVn1[y + 1][x + 1]);
                            printf("%d %d %f\n", x, y, dtVn2[y][x + 1]);
                            printf("%d %d %f\n", x, y, -dtVn2[y + 1][x + 1]);
                        }
                    }
                }
                printf("\n");
                for (y = 0; y < HOW_MANY_SINDOU_tate; y++) {
                    if ((x + y) % 2 == 0) {
                        if (y == 0) {
//                            printf("%d %d %f\n", x + 1, y, dtVn1[y + 1][x + 1]);
                            printf("%d %d %f\n", x + 1, y, dtVn2[y + 1][x + 1]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate - 1) {
//                            printf("%d %d %f\n", x + 1, y, -dtVn1[y][x + 1]);
                            printf("%d %d %f\n", x + 1, y, -dtVn2[y][x + 1]);
                        }
                        else {
//                            printf("%d %d %f\n", x + 1, y, -dtVn1[y][x + 1]);
//                            printf("%d %d %f\n", x + 1, y, dtVn1[y + 1][x + 1]);
                            printf("%d %d %f\n", x + 1, y, -dtVn2[y][x + 1]);
                            printf("%d %d %f\n", x + 1, y, dtVn2[y + 1][x + 1]);
                        }
                    }
                    else {
                        if (y == 0) {
//                            printf("%d %d %f\n", x + 1, y, -dtVn1[y + 1][x + 1]);
                            printf("%d %d %f\n", x + 1, y, -dtVn2[y + 1][x + 1]);
                        }
                        else if (y == HOW_MANY_SINDOU_tate - 1) {
//                            printf("%d %d %f\n", x + 1, y, dtVn1[y][x + 1]);
                            printf("%d %d %f\n", x + 1, y, dtVn2[y][x + 1]);
                        }
                        else {
//                            printf("%d %d %f\n", x + 1, y, dtVn1[y][x + 1]);
//                            printf("%d %d %f\n", x + 1, y, -dtVn1[y + 1][x + 1]);
                            printf("%d %d %f\n", x + 1, y, dtVn2[y][x + 1]);
                            printf("%d %d %f\n", x + 1, y, -dtVn2[y + 1][x + 1]);
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
                        dtdE1[y][x] = e * (-e + 2 * (dtQ1[y][x] + C * (dtVn1[y][x - 1] + dtVn1[y][x + 1] + dtVn1[y - 1][x] + dtVn1[y + 1][x]) + Cx * (dtVn1[y - 1][x - 1] + dtVn1[y - 1][x + 1] + dtVn1[y + 1][x - 1] + dtVn1[y + 1][x + 1]) + Cs * dtVn2[y][x])) / (2 * (4 * C + 4 * Cx + Cs + Cj));
                }
                else {
                        dtdE1[y][x] = -e * (e + 2 * (dtQ1[y][x] + C * (dtVn1[y][x - 1] + dtVn1[y][x + 1] + dtVn1[y - 1][x] + dtVn1[y + 1][x]) + Cx * (dtVn1[y - 1][x - 1] + dtVn1[y - 1][x + 1] + dtVn1[y + 1][x - 1] + dtVn1[y + 1][x + 1]) + Cs * dtVn2[y][x])) / (2 * (4 * C + 4 * Cx + Cs + Cj));
                }
                if (dtVd2[y][x] > 0) {
                        dtdE2[y][x] = e * (-e + 2 * (dtQ2[y][x] + C * (dtVn2[y][x - 1] + dtVn2[y][x + 1] + dtVn2[y - 1][x] + dtVn2[y + 1][x]) + Cs * dtVn1[y][x])) / (2 * (4 * C + Cs + Cj));
                }
                else {
                        dtdE2[y][x] = -e * (e + 2 * (dtQ2[y][x] + C * (dtVn2[y][x - 1] + dtVn2[y][x + 1] + dtVn2[y - 1][x] + dtVn2[y + 1][x]) + Cs * dtVn1[y][x])) / (2 * (4 * C + Cs + Cj));
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
            
        }

        for (y = 1; y < HOW_MANY_SINDOU_tate - 1; y++) {
            for (x = 1; x < HOW_MANY_SINDOU_yoko - 1; x++) {
                dtQ1[y][x] += dt * (dtVd1[y][x] - dtVn1[y][x]) / R1;
                dtQ2[y][x] += dt * (dtVd2[y][x] - dtVn2[y][x]) / R2;
            }
        }
        t += Tmin;
    }
}
