#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_JUNCTION 20
#define NUMBER_OF_SINDOUSI_TATE 50
#define NUMBER_OF_SINDOUSI_YOKO 50
#define N_TATE 100
#define N_YOKO 100
#define START_OF_TRIGER 4000
#define END_OF_TRIGER 4050
#define START_OF_TRIGER4 4050
#define END_OF_TRIGER4 4055
#define NUM_PULSE 1

int main(){
    double Cj = NUMBER_OF_JUNCTION*10.0; //[aF]
    double C = 2.0;//[aF] 斜め方向のキャパシタ
    double Cx = 2.5;//[aF] 縦横方向のキャパシタ
    double Cs = 2.0;//[aF] 層間キャパシタ
    double Cs4 = 3.7;//[aF]
    double R = 25.0; //[G]
    double Rj = 0.001;//[G]
    double Vd1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; //[V]
    double Vd4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; //[V]
    double Vdt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; //[V]
    double Vdn[N_TATE+1][N_YOKO+1] = {0.0}; //[V]
    double Vds[2] = {0.0};
    double Vin = 0.01;//[V]
    double Vn1[NUMBER_OF_SINDOUSI_TATE+2][NUMBER_OF_SINDOUSI_YOKO+2] = {0.0};  //[V]
    double Vn4[NUMBER_OF_SINDOUSI_TATE+2][NUMBER_OF_SINDOUSI_YOKO+2] = {0.0};  //[V]
    double Vnt[NUMBER_OF_SINDOUSI_TATE+2][NUMBER_OF_SINDOUSI_YOKO+2] = {0.0};  //[V]
    double Vnn[N_TATE+1][N_YOKO+1] = {0.0};  //[V]
    double Vns[2] = {0.0};
    double Q1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Q4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Qt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Qn[N_TATE+1][N_YOKO+1] = {0.0}; 
    double Qs[2] = {0.0};
    double t = 0.0; //[ns]
    double dt = 0.1, dq;
    double e = 0.1602,r;
    int L1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0};
    int L4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0};
    int Lt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0};
    int Ln[N_TATE+1][N_YOKO+1] = {0};
    int Ls[2] = {0.0};
    double q1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double q4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double qt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double qn[N_TATE+1][N_YOKO+1] = {0.0};
    double qs[2] = {0.0};
    double dEup1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEdown1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEup4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEdown4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEupt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEdownt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEupn[N_TATE+1][N_YOKO+1] = {0.0};
    double dEdownn[N_TATE+1][N_YOKO+1] = {0.0};
    double dEups[2] = {0.0};
    double dEdowns[2] = {0.0};
    int up = 0;
    int down = 0;
    int w = 0;
    double wt = 0;
    int i, j = 0;
    double wt_min = 1000.0;
    int A, B = 0;
    int a, b = 0;
    int x, y = 0;
    int printkaisu = 0;
    //縦方向の周囲の振動子
    double Vlt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vrt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vut[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vbt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vat[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vct[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vet[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vft[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vst[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double V4t[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    //斜め方向の周囲の振動子
    double Vln[N_TATE+1][N_YOKO+1] = {0.0};
    double Vrn[N_TATE+1][N_YOKO+1] = {0.0};
    double Vun[N_TATE+1][N_YOKO+1] = {0.0};
    double Vbn[N_TATE+1][N_YOKO+1] = {0.0};
    double Van[N_TATE+1][N_YOKO+1] = {0.0};
    double Vcn[N_TATE+1][N_YOKO+1] = {0.0};
    double Ven[N_TATE+1][N_YOKO+1] = {0.0};
    double Vfn[N_TATE+1][N_YOKO+1] = {0.0};
    double Vsn[N_TATE+1][N_YOKO+1] = {0.0};
    double V1n[N_TATE+1][N_YOKO+1] = {0.0};
    //４結合層の周囲振動子
    double Vl4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vr4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vu4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vb4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double V84[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double V14[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    //斜め-４結合層間振動子の周囲振動子
    double V81[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double V41[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    //層間振動子の周囲の振動子
    double V1 = 0;
    double V2 = 0;
    double V3 = 0;
    double V4 = 0;
    double V5 = 0;
    double V6 = 0;
    double V7 = 0;
    double V8 = 0;
    double V9 = 0;
    double V10 = 0;
    double V11 = 0;
    double V12 = 0;

    double V13 = 0;
    double V17 = 0;
    double V15 = 0;
    double V16 = 0;

    double setting[N_TATE][N_YOKO] = { 0 };


    srand((unsigned)time(NULL));

    //バイアス電圧をかける
    for (b = 1; b < NUMBER_OF_SINDOUSI_TATE-2; b++) {
        for (a = 1; a < NUMBER_OF_SINDOUSI_YOKO-2; a++) {
            if (setting[b][a] == 1){
                Vdt[b][a] = 0;
            } else {
                if ((a + b) % 2 == 0) {
                    Vdt[b][a] = -0.00750;//閾値0.007729
                    Vd4[b][a] = -0.00738;//閾値0.007758
                    Vd1[b][a] = -0.00760;//閾値0.007868
                } else {
                    Vdt[b][a] = 0.00750;
                    Vd4[b][a] = 0.00738;
                    Vd1[b][a] = 0.00760;
                }
            }
        }
    }

    for (b = 2; b < N_TATE-1; b++) {
        for (a = 2; a < N_YOKO-1; a++) {
            if (setting[b][a] == 1){
                Vdn[b][a] = 0;
            } else {
                if (b % 2 == 0){
                    if ((a + b) % 2 == 0) {
                        Vdn[b][a] = 0.00747; //閾値0.007735[V]
                    } else {
                        Vdn[b][a] = -0.00747;
                    }
                }
                else{
                    if ((a + b) % 2 == 0) {
                        Vdn[b][a] = -0.00747;
                    } else {
                        Vdn[b][a] = 0.00747;
                    }
                }    
            }
        }
    }

    Vds[0] = -0.00745;
    Vds[1] = 0.00750;
    Vdn[9][3] = 0;
    Vdn[3][9] = 0;
    Vdn[3][91] = 0;
    Vdn[9][97] = 0;

	while(t <= START_OF_TRIGER + 500){

        //トリガを印加
        if(t > START_OF_TRIGER && t < END_OF_TRIGER){
            Vnn[10][0] = Vin;
            Vnn[9][1] = Vin;
            Vnn[8][0] = -Vin;
            Vnn[0][10] = Vin;
            Vnn[1][9] = Vin;
            Vnn[0][8] = -Vin;
            Vnn[10][100] = Vin;
            Vnn[9][99] = Vin;
            Vnn[8][100] = -Vin;
            Vnn[0][90] = Vin;
            Vnn[1][91] = Vin;
            Vnn[0][92] = -Vin;
        }else{
            Vnn[10][0] = 0;
            Vnn[9][1] = 0;
            Vnn[8][0] = 0;
            Vnn[0][10] = 0;
            Vnn[1][9] = 0;
            Vnn[0][8] = 0;
            Vnn[10][100] = 0;
            Vnn[9][99] = 0;
            Vnn[8][100] = 0;
            Vnn[0][90] = 0;
            Vnn[1][91] = 0;
            Vnn[0][92] = 0;
        }

        if(t > START_OF_TRIGER4 && t < END_OF_TRIGER4){
            Vn4[0][1] = -Vin;
            Vn4[0][47] = -Vin;
        }else{
            Vn4[0][1] = 0;
            Vn4[0][47] = 0;
        }

        //周囲の振動子と接続
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                Vlt[b][a] = Vnt[b][a-1];
                Vrt[b][a] = Vnt[b][a+1];
                Vut[b][a] = Vnt[b+1][a];
                Vbt[b][a] = Vnt[b-1][a];
                Vat[b][a] = Vnt[b-1][a-1];
                Vct[b][a] = Vnt[b-1][a+1];
                Vet[b][a] = Vnt[b+1][a-1];
                Vft[b][a] = Vnt[b+1][a+1];
                V4t[b][a] = Vn4[b][a];

                Vl4[b][a] = Vn4[b][a-1];
                Vr4[b][a] = Vn4[b][a+1];
                Vu4[b][a] = Vn4[b+1][a];
                Vb4[b][a] = Vn4[b-1][a];
                V14[b][a] = Vn1[b][a];
                V84[b][a] = Vnt[b][a];

                V81[b][a] = Vnn[2*b][2*a];
                V41[b][a] = Vn4[b][a];
                if((b == 26 && a == 29) || (b == 26 && a == 28) || (b == 26 && a == 30) || (b == 25 && a == 29) || (b == 26 && a == 21) || (b == 26 && a == 20) || (b == 26 && a == 22) || (b == 25 && a == 21)){
                    Vst[b][a] = Vns[0];
                }else{
                    Vst[b][a] = 0;
                }
            }
        }
        
        for(b = 2; b < N_TATE-1; b++){
            for(a = 2; a < N_YOKO-1; a++){
                Vln[b][a] = Vnn[b][a-2];
                Vrn[b][a] = Vnn[b][a+2];
                Vun[b][a] = Vnn[b+2][a];
                Vbn[b][a] = Vnn[b-2][a];
                Van[b][a] = Vnn[b-1][a-1];
                Vcn[b][a] = Vnn[b-1][a+1];
                Ven[b][a] = Vnn[b+1][a-1];
                Vfn[b][a] = Vnn[b+1][a+1];
                if(b % 2 == 0 && a % 2 == 0){
                    V1n[b][a] = Vn1[b/2][a/2];
                }else{
                    V1n[b][a] = 0;
                }
                if((b == 44 && a == 64) || (b == 44 && a == 36) || (b == 51 && a == 57) || (b == 51 && a == 43)){
                    Vsn[b][a] = Vns[0];
                }else if((b == 36 && a == 42) || (b == 36 && a == 58) || (b == 43 && a == 49) || (b == 43 && a == 51)){
                    Vsn[b][a] = Vns[1];
                }else{
                    Vsn[b][a] = 0;
                }
            }
        }

        V1 = Vnt[26][29];
        V2 = Vnt[26][28];
        V3 = Vnt[26][30];
        V4 = Vnt[25][29];
        V5 = Vnt[26][21];
        V6 = Vnt[26][20];
        V7 = Vnt[26][22];
        V8 = Vnt[25][21];
        V9 = Vnn[44][64];
        V10 = Vnn[44][36];
        V11 = Vnn[51][57];
        V12 = Vnn[51][43];

        V13 = Vnn[36][44];
        V17 = Vnn[36][56];
        V15 = Vnn[43][49];
        V16 = Vnn[43][51];
                
        //電荷計算
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                if((b == 26 && a == 29) || (b == 26 && a == 28) || (b == 26 && a == 30) || (b == 25 && a == 29) || (b == 26 && a == 21) || (b == 26 && a == 20) || (b == 26 && a == 22) || (b == 25 && a == 21)){
                    qt[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Qt[b][a]-C*Cj*(Vlt[b][a]+Vrt[b][a]+Vut[b][a]+Vbt[b][a])-Cx*Cj*(Vat[b][a]+Vct[b][a]+Vet[b][a]+Vft[b][a])-Cs4*Cj*V4t[b][a]-Cs*Cj*Vst[b][a])-Cj*Lt[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs4+Cs)+Cj);
                }else{
                    qt[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Qt[b][a]-C*Cj*(Vlt[b][a]+Vrt[b][a]+Vut[b][a]+Vbt[b][a])-Cx*Cj*(Vat[b][a]+Vct[b][a]+Vet[b][a]+Vft[b][a])-Cs4*Cj*V4t[b][a])-Cj*Lt[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs4)+Cj);
                }
                q4[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Q4[b][a]-C*Cj*(Vl4[b][a]+Vr4[b][a]+Vu4[b][a]+Vb4[b][a])-Cs4*Cj*V14[b][a]-Cs4*Cj*V84[b][a])-Cj*L4[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+2*Cs4)+Cj);
                q1[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Q1[b][a]-Cs4*Cj*V41[b][a]-Cs*Cj*V81[b][a])-Cj*L1[b][a]*e)/(NUMBER_OF_JUNCTION*(Cs4+Cs)+Cj);
            }
        }

        for(b = 2; b < N_TATE-1; b++){
            for(a = 2; a < N_YOKO-1; a++){
                if(b % 2 == 0 && a % 2 == 0){
                    if((b == 44 && a == 64) || (b == 44 && a == 36) || (b == 51 && a == 57) || (b == 51 && a == 43) || (b == 36 && a == 44) || (b == 36 && a == 56) || (b == 43 && a == 49) || (b == 43 && a == 51)){
                        qn[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Qn[b][a]-Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])-C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])-Cs*Cj*(V1n[b][a]+Vsn[b][a]))-Cj*Ln[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx+2*Cs)+Cj);
                    }else{
                        qn[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Qn[b][a]-Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])-C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])-Cs*Cj*V1n[b][a])-Cj*Ln[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj);
                    }
                }else{
                    if((b == 44 && a == 64) || (b == 44 && a == 36) || (b == 51 && a == 57) || (b == 51 && a == 43) || (b == 36 && a == 44) || (b == 36 && a == 56) || (b == 43 && a == 49) || (b == 43 && a == 51)){
                        qn[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Qn[b][a]-Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])-C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])-Cs*Cj*Vsn[b][a])-Cj*Ln[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj);
                    }else{
                        qn[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Qn[b][a]-Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])-C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a]))-Cj*Ln[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx)+Cj);
                    }
                }
            }
        }

        qs[0] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[0]-Cs*Cj*(V1+V2+V3+V4+V5+V6+V7+V8+V9+V10+V11+V12))-Cj*Ls[0]*e)/(NUMBER_OF_JUNCTION*(12*Cs)+Cj);
        qs[1] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[1]-Cs*Cj*(V13+V17+V15+V16))-Cj*Ls[1]*e)/(NUMBER_OF_JUNCTION*(4*Cs)+Cj);

        //ノード電圧計算
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                Vnt[b][a] = qt[b][a]/Cj;
                Vn4[b][a] = q4[b][a]/Cj;
                Vn1[b][a] = q1[b][a]/Cj;
            }
        }

        for(b = 2; b < N_TATE-1; b++){
            for(a = 2; a < N_YOKO-1; a++){
                Vnn[b][a] = qn[b][a]/Cj;
            }
        }

        Vns[0] = qs[0]/Cj;
        Vns[1] = qs[1]/Cj;

        //Vnの出力
        if(t >= START_OF_TRIGER){
            if(printkaisu == NUMBER_OF_JUNCTION*10){
                for (x = 0; x < NUMBER_OF_SINDOUSI_YOKO-1; x++) {
                    for (y = 0; y < NUMBER_OF_SINDOUSI_TATE; y++) {
                        if ((x + y) % 2 == 0) {
                            if (y == 0) {
                                printf("%d %d %f\n", x, y, -Vn4[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x, y, Vn4[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x, y, Vn4[y][x + 1]);
                                printf("%d %d %f\n", x, y, -Vn4[y + 1][x + 1]);
                            }
                        } else {
                            if (y == 0) {
                                printf("%d %d %f\n", x, y, Vn4[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x, y, -Vn4[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x, y, -Vn4[y][x + 1]);
                                printf("%d %d %f\n", x, y, Vn4[y + 1][x + 1]);
                            }
                        }
                    }
                    printf("\n");
                    for (y = 0; y < NUMBER_OF_SINDOUSI_TATE; y++) {
                        if ((x + y) % 2 == 0) {
                            if (y == 0) {
                                printf("%d %d %f\n", x + 1, y, -Vn4[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x + 1, y, Vn4[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x + 1, y, Vn4[y][x + 1]);
                                printf("%d %d %f\n", x + 1, y, -Vn4[y + 1][x + 1]);
                            }
                        } else {
                            if (y == 0) {
                                printf("%d %d %f\n", x + 1, y, Vn4[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x + 1, y, -Vn4[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x + 1, y, -Vn4[y][x + 1]);
                                printf("%d %d %f\n", x + 1, y, Vn4[y + 1][x + 1]);
                            }
                        }
                    }
                    printf("\n");
                }
                printf("\n");
                //printf("%f\n",t);
                printkaisu = 0;
            }else{
                printkaisu += 1;
            }
        }

        //dE計算
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){

                if((b == 26 && a == 29) || (b == 26 && a == 28) || (b == 26 && a == 30) || (b == 25 && a == 29) || (b == 26 && a == 21) || (b == 26 && a == 20) || (b == 26 && a == 22) || (b == 25 && a == 21)){
                    dEupt[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*Lt[b][a])*(4*C+4*Cx+Cs4+Cs)*e+Cj*(2*Qt[b][a]-e)+2*C*Cj*(Vlt[b][a]+Vrt[b][a]+Vut[b][a]+Vbt[b][a])+2*Cx*Cj*(Vat[b][a]+Vct[b][a]+Vet[b][a]+Vft[b][a])+2*Cs4*Cj*V4t[b][a]+2*Cs*Cj*Vst[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs4+Cs)+Cj));
                    dEdownt[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*Lt[b][a])*(4*C+4*Cx+Cs4+Cs)*e+Cj*(2*Qt[b][a]+e)+2*C*Cj*(Vlt[b][a]+Vrt[b][a]+Vut[b][a]+Vbt[b][a])+2*Cx*Cj*(Vat[b][a]+Vct[b][a]+Vet[b][a]+Vft[b][a])+2*Cs4*Cj*V4t[b][a]+2*Cs*Cj*Vst[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs4+Cs)+Cj));
                }else{
                    dEupt[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*Lt[b][a])*(4*C+4*Cx+Cs4)*e+Cj*(2*Qt[b][a]-e)+2*C*Cj*(Vlt[b][a]+Vrt[b][a]+Vut[b][a]+Vbt[b][a])+2*Cx*Cj*(Vat[b][a]+Vct[b][a]+Vet[b][a]+Vft[b][a])+2*Cs4*Cj*V4t[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs4)+Cj));
                    dEdownt[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*Lt[b][a])*(4*C+4*Cx+Cs4)*e+Cj*(2*Qt[b][a]+e)+2*C*Cj*(Vlt[b][a]+Vrt[b][a]+Vut[b][a]+Vbt[b][a])+2*Cx*Cj*(Vat[b][a]+Vct[b][a]+Vet[b][a]+Vft[b][a])+2*Cs4*Cj*V4t[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs4)+Cj));
                }

                dEup4[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*L4[b][a])*(4*C+2*Cs4)*e+Cj*(2*Q4[b][a]-e)+2*C*Cj*(Vl4[b][a]+Vr4[b][a]+Vu4[b][a]+Vb4[b][a])+2*Cs4*Cj*V14[b][a]+2*Cs4*Cj*V84[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+2*Cs4)+Cj));
                dEdown4[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*L4[b][a])*(4*C+2*Cs4)*e+Cj*(2*Q4[b][a]+e)+2*C*Cj*(Vl4[b][a]+Vr4[b][a]+Vu4[b][a]+Vb4[b][a])+2*Cs4*Cj*V14[b][a]+2*Cs4*Cj*V84[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+2*Cs4)+Cj));

                dEup1[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*L1[b][a])*(Cs4+Cs)*e+Cj*(2*Q1[b][a]-e)+2*Cs4*Cj*V41[b][a]+2*Cs*Cj*V81[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(Cs4+Cs)+Cj));
                dEdown1[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*L1[b][a])*(Cs4+Cs)*e+Cj*(2*Q1[b][a]+e)+2*Cs4*Cj*V41[b][a]+2*Cs*Cj*V81[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(Cs4+Cs)+Cj));

                if(dEupt[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION-Lt[b][a]; j++){
                        r = (double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEupt[b][a])*log(1/r);
                        
                        if(wt < dt && wt < wt_min){
                            up = 1;
                            down = 0;
                            wt_min = wt;
                            A = a;
                            B = b;
                            w = 8;
                        }
                    }
                }
                if(dEdownt[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION+Lt[b][a]; j++){
                        r=(double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEdownt[b][a])*log(1/r);

                        if(wt < dt && wt < wt_min){
                            up = 0;
                            down = 1;
                            wt_min = wt;
                            A = a;
                            B = b;
                            w = 8;
                        }
                    }
                }

                if(dEup4[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION-L4[b][a]; j++){
                        r = (double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEup4[b][a])*log(1/r);
                        
                        if(wt < dt && wt < wt_min){
                            up = 1;
                            down = 0;
                            wt_min = wt;
                            A = a;
                            B = b;
                            w = 4;
                        }
                    }
                }
                if(dEdown4[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION+L4[b][a]; j++){
                        r=(double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEdown4[b][a])*log(1/r);

                        if(wt < dt && wt < wt_min){
                            up = 0;
                            down = 1;
                            wt_min = wt;
                            A = a;
                            B = b;
                            w = 4;
                        }
                    }
                }

                if(dEup1[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION-L1[b][a]; j++){
                        r = (double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEup1[b][a])*log(1/r);
                        
                        if(wt < dt && wt < wt_min){
                            up = 1;
                            down = 0;
                            wt_min = wt;
                            A = a;
                            B = b;
                            w = 1;
                        }
                    }
                }
                if(dEdown1[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION+L1[b][a]; j++){
                        r=(double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEdown1[b][a])*log(1/r);

                        if(wt < dt && wt < wt_min){
                            up = 0;
                            down = 1;
                            wt_min = wt;
                            A = a;
                            B = b;
                            w = 1;
                        }
                    }
                }
            }
        }

        for(b = 2; b < N_TATE-1; b++){
            for(a = 2; a < N_YOKO-1; a++){
                
                if(b % 2 == 0 && a % 2 == 0){
                    if((b == 44 && a == 64) || (b == 44 && a == 36) || (b == 51 && a == 57) || (b == 51 && a == 43) || (b == 36 && a == 44) || (b == 36 && a == 56) || (b == 43 && a == 49) || (b == 43 && a == 51)){
                        dEupn[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*Ln[b][a])*(4*C+4*Cx+2*Cs)*e+Cj*(2*Qn[b][a]-e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])+2*Cs*Cj*(V1n[b][a]+Vsn[b][a]))/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+2*Cs)+Cj));
                        dEdownn[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*Ln[b][a])*(4*C+4*Cx+2*Cs)*e+Cj*(2*Qn[b][a]+e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])+2*Cs*Cj*(V1n[b][a]+Vsn[b][a]))/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+2*Cs)+Cj));
                    }else{
                        dEupn[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*Ln[b][a])*(4*C+4*Cx+Cs)*e+Cj*(2*Qn[b][a]-e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])+2*Cs*Cj*V1n[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj));
                        dEdownn[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*Ln[b][a])*(4*C+4*Cx+Cs)*e+Cj*(2*Qn[b][a]+e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])+2*Cs*Cj*V1n[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj));
                    }
                }else{
                    if((b == 44 && a == 64) || (b == 44 && a == 36) || (b == 51 && a == 57) || (b == 51 && a == 43) || (b == 36 && a == 44) || (b == 36 && a == 56) || (b == 43 && a == 49) || (b == 43 && a == 51)){
                        dEupn[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*Ln[b][a])*(4*C+4*Cx+Cs)*e+Cj*(2*Qn[b][a]-e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])+2*Cs*Cj*Vsn[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj));
                        dEdownn[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*Ln[b][a])*(4*C+4*Cx+Cs)*e+Cj*(2*Qn[b][a]+e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])+2*Cs*Cj*Vsn[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj));
                    }else{
                        dEupn[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*Ln[b][a])*(4*C+4*Cx)*e+Cj*(2*Qn[b][a]-e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a]))/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx)+Cj));
                        dEdownn[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*Ln[b][a])*(4*C+4*Cx)*e+Cj*(2*Qn[b][a]+e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a]))/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx)+Cj));
                    }
                }

                if(dEupn[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION-Ln[b][a]; j++){
                        r = (double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEupn[b][a])*log(1/r);
                        
                        if(wt < dt && wt < wt_min){
                            up = 1;
                            down = 0;
                            wt_min = wt;
                            A = a;
                            B = b;
                            w = 9;
                        }
                    }
                }
                if(dEdownn[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION+Ln[b][a]; j++){
                        r=(double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEdownn[b][a])*log(1/r);

                        if(wt < dt && wt < wt_min){
                            up = 0;
                            down = 1;
                            wt_min = wt;
                            A = a;
                            B = b;
                            w = 9;
                        }
                    }
                }
            }
        }

        for(b = 0; b < 2; b++) {
            if (b == 0){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*12+2*12*Ls[b])*Cs*e+Cj*(2*Qs[b]-e)+2*Cs*Cj*(V1+V2+V3+V4+V5+V6+V7+V8+V9+V10+V11+V12))/(2*Cj*(12*NUMBER_OF_JUNCTION*Cs+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*12-2*12*Ls[b])*Cs*e+Cj*(2*Qs[b]+e)+2*Cs*Cj*(V1+V2+V3+V4+V5+V6+V7+V8+V9+V10+V11+V12))/(2*Cj*(12*NUMBER_OF_JUNCTION*Cs+Cj));
            }else if (b == 1){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*4+2*4*Ls[b])*Cs*e+Cj*(2*Qs[b]-e)+2*Cs*Cj*(V13+V17+V15+V16))/(2*Cj*(4*NUMBER_OF_JUNCTION*Cs+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*4-2*4*Ls[b])*Cs*e+Cj*(2*Qs[b]+e)+2*Cs*Cj*(V13+V17+V15+V16))/(2*Cj*(4*NUMBER_OF_JUNCTION*Cs+Cj));
            }
            if(dEups[b] > 0){
                for(i = 0; i < NUMBER_OF_JUNCTION-Ls[b]; i++){
                    r = (double)rand()/RAND_MAX;
                    wt = (e*e*Rj/dEups[b])*log(1/r);
                    
                    if(wt < dt && wt < wt_min){
                        up = 1;
                        down = 0;
                        wt_min = wt;
                        w = 3;
                        B = b;
                    }
                }
            }
            if(dEdowns[b] > 0){
                for(i = 0; i < NUMBER_OF_JUNCTION+Ls[b]; i++){
                    r=(double)rand()/RAND_MAX;
                    wt = (e*e*Rj/dEdowns[b])*log(1/r);

                    if(wt < dt && wt < wt_min){
                        up = 0;
                        down = 1;
                        wt_min = wt;
                        w = 3;
                        B = b;
                    }
                }
            }
        }

        

        if((up == 1) && (w == 8)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*wt_min/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            Qs[1] += (Vds[1]-Vns[1])*wt_min/R;

            Lt[B][A] += 1;

            if(Lt[B][A] == NUMBER_OF_JUNCTION){
                Lt[B][A] = 0;
                Qt[B][A] -= e;
            }
            t += wt_min;
            up = 0;

        }else if((down == 1) && (w == 8)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*wt_min/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            Qs[1] += (Vds[1]-Vns[1])*wt_min/R;
            Lt[B][A] -= 1;
            if(Lt[B][A] == -NUMBER_OF_JUNCTION){
                Lt[B][A] = 0;
                Qt[B][A] += e;
            }
            t += wt_min;
            down = 0;


        }else if((up == 1) && (w == 9)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*wt_min/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            Qs[1] += (Vds[1]-Vns[1])*wt_min/R;

            Ln[B][A] += 1;

            if(Ln[B][A] == NUMBER_OF_JUNCTION){
                Ln[B][A] = 0;
                Qn[B][A] -= e;
            }
            t += wt_min;
            up = 0;

        }else if((down == 1) && (w == 9)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*wt_min/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            Qs[1] += (Vds[1]-Vns[1])*wt_min/R;
            Ln[B][A] -= 1;
            if(Ln[B][A] == -NUMBER_OF_JUNCTION){
                Ln[B][A] = 0;
                Qn[B][A] += e;
            }
            t += wt_min;
            down = 0;


        }else if((up == 1) && (w == 3)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*wt_min/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            Qs[1] += (Vds[1]-Vns[1])*wt_min/R;

            Ls[B] += 1;

            if(Ls[B] == NUMBER_OF_JUNCTION){
                Ls[B] = 0;
                Qs[B] -= e;
            }
            t += wt_min;
            up = 0;

        }else if((down == 1) && (w == 3)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*wt_min/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            Qs[1] += (Vds[1]-Vns[1])*wt_min/R;
            Ls[B] -= 1;
            if(Ls[B] == -NUMBER_OF_JUNCTION){
                Ls[B] = 0;
                Qs[B] += e;
            }
            t += wt_min;
            down = 0;

        }else if((up == 1) && (w == 4)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*wt_min/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            Qs[1] += (Vds[1]-Vns[1])*wt_min/R;

            L4[B][A] += 1;

            if(L4[B][A] == NUMBER_OF_JUNCTION){
                L4[B][A] = 0;
                Q4[B][A] -= e;
            }
            t += wt_min;
            up = 0;

        }else if((down == 1) && (w == 4)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*wt_min/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            Qs[1] += (Vds[1]-Vns[1])*wt_min/R;
            L4[B][A] -= 1;
            if(L4[B][A] == -NUMBER_OF_JUNCTION){
                L4[B][A] = 0;
                Q4[B][A] += e;
            }
            t += wt_min;
            down = 0;


        }else if((up == 1) && (w == 1)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*wt_min/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            Qs[1] += (Vds[1]-Vns[1])*wt_min/R;

            L1[B][A] += 1;

            if(L1[B][A] == NUMBER_OF_JUNCTION){
                L1[B][A] = 0;
                Q1[B][A] -= e;
            }
            t += wt_min;
            up = 0;

        }else if((down == 1) && (w == 1)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*wt_min/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            Qs[1] += (Vds[1]-Vns[1])*wt_min/R;
            L1[B][A] -= 1;
            if(L1[B][A] == -NUMBER_OF_JUNCTION){
                L1[B][A] = 0;
                Q1[B][A] += e;
            }
            t += wt_min;
            down = 0;


        }
        else{
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Qt[b][a] += (Vdt[b][a]-Vnt[b][a])*dt/R;
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*dt/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*dt/R;
                }
            }
            for(b = 2; b < N_TATE-1; b++){
                for(a = 2; a < N_YOKO-1; a++){
                    Qn[b][a] += (Vdn[b][a]-Vnn[b][a])*dt/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*dt/R;
            Qs[1] += (Vds[1]-Vns[1])*dt/R;
            t += dt;
        }
        
        up = 0;
        down = 0;
        wt = 1000.0;
        wt_min = 1000.0;
        A = 0;
        B = 0;
	}
	return 0;
}
