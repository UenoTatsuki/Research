#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double makerand() {
    double r;
    rand(); rand(); rand();
    r = rand();
    return r / RAND_MAX;
}

int main(){
    double Cj = 10.0;
    double C = 2.0;
    double C1 = 2.0;
    double C2 = 2.0;
    double R = 6;
    double Rj = 0.001;
    double Vd1 = -0.0055;
    double Vd2 = 0.0055;
    double Vd3 = -0.0055;
    double Vn[2] = {0};
    double V1 = 0; //トリガ用
    double V2 = 0; //トリガ用
    double Q[2] = {0};
    double q1, q2;
    double t = 0;
    double dt = 0.1, wt[2] = {0}, dq = 0.0, dE[2] = {0}, Ganma, T, Tmin;
    int dx;
    double e = 0.1602, r;
    double x;
    
    srand((unsigned)time(NULL));
    while (t <= 2000.0){

        //トリガを印加
        if(t > 500 && t < 500.5){
            V1 = -0.01;
        }else{
            V1 = 0.0;
        }
        if(t > 1500 && t < 1500.5){
            V2 = -0.01;
        }else{
            V2 = 0.0;
        }

        //qの更新
        q1 = (C*(-Q[0] + Cj * V1 + C1 * (V1 - Vn[1]))) / (C + C1 + Cj);
        q2 = (C1*(-Q[0] + Cj * Vn[1] + C * (Vn[1] - V1))) / (C + C1 + Cj);
        Vn[0] = (q1 + q2 + Q[0]) / Cj;

        q1 = (C1*(-Q[1] + Cj * Vn[0] + C2 * (Vn[0] - Vn[2]))) / (C1 + C2 + Cj);
        q2 = (C2*(-Q[1] + Cj * Vn[2] + C1 * (Vn[2] - Vn[0]))) / (C1 + C2 + Cj);
        Vn[1] = (q1 + q2 + Q[1]) / Cj;

        q1 = (C*(-Q[2] + Cj * V2 + C2 * (V2 - Vn[1]))) / (C + C2 + Cj);
        q2 = (C2*(-Q[2] + Cj * Vn[1] + C * (Vn[1] - V2))) / (C + C2 + Cj);
        Vn[2] = (q1 + q2 + Q[2]) / Cj;
        
        //Vnを出力
        printf("%f %f %f %f\n", t, Vn[0], Vn[1], Vn[2]);

        //dEを計算
        dE[0] = -e * (e + 2 * (Q[0] + C * V1 + C1 * Vn[1])) / (2 * (C + C1 + Cj));
        dE[1] = e * (-e + 2 * (Q[1] + C1 * Vn[0] + C2 * Vn[2])) / (2 * (C1 + C2 + Cj));
        dE[2] = -e * (e + 2 * (Q[2] + C * V2 + C2 * Vn[1])) / (2 * (C + C2 + Cj));

        //dEの評価
        Tmin = dt;
        dx = 0;
        for (i=0;i<3;i++){

            if (dE[i] > 0){
                r = makerand();
                Ganma = dE[i] / (e * e * Rj);
                T = (1 / Ganma) * log10(1 / r);
                if (T < Tmin){
                    Tmin = T;
                    dx = i;
                }
            }
        }

        if (Tmin != dt){
            if (dx == 0 || dx == 2){
                Q[dx] += e;
            }
            else{
                Q[dx] -= e;
            }
        }
        
        Q[0] += dt * (Vd1 - Vn[0]) / R;
        Q[1] += dt * (Vd2 - Vn[1]) / R;
        Q[2] += dt * (Vd3 - Vn[2]) / R;

        t += Tmin;
        


    }

}