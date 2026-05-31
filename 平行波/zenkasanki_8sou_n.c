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
#define START_OF_TRIGER1 4080
#define END_OF_TRIGER1 4130
#define START_OF_TRIGER4 4070
#define END_OF_TRIGER4 4075
#define START_OF_TRIGER5 4150
#define END_OF_TRIGER5 4155
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
    double Vds[8] = {0.0};
    double Vin = 0.007;//[V]
    double Vn1[NUMBER_OF_SINDOUSI_TATE+2][NUMBER_OF_SINDOUSI_YOKO+2] = {0.0};  //[V]
    double Vn4[NUMBER_OF_SINDOUSI_TATE+2][NUMBER_OF_SINDOUSI_YOKO+2] = {0.0};  //[V]
    double Vnt[NUMBER_OF_SINDOUSI_TATE+2][NUMBER_OF_SINDOUSI_YOKO+2] = {0.0};  //[V]
    double Vnn[N_TATE+1][N_YOKO+1] = {0.0};  //[V]
    double Vns[8] = {0.0};
    double Q1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Q4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Qt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Qn[N_TATE+1][N_YOKO+1] = {0.0}; 
    double Qs[8] = {0.0};
    double t = 0.0; //[ns]
    double dt = 0.1, dq;
    double e = 0.1602,r;
    int L1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0};
    int L4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0};
    int Lt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0};
    int Ln[N_TATE+1][N_YOKO+1] = {0};
    int Ls[8] = {0.0};
    double q1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double q4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double qt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double qn[N_TATE+1][N_YOKO+1] = {0.0};
    double qs[8] = {0.0};
    double dEup1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEdown1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEup4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEdown4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEupt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEdownt[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEupn[N_TATE+1][N_YOKO+1] = {0.0};
    double dEdownn[N_TATE+1][N_YOKO+1] = {0.0};
    double dEups[8] = {0.0};
    double dEdowns[8] = {0.0};
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
    //0
    double V1 = 0;
    double V2 = 0;
    double V3 = 0;
    double V4 = 0;
    //1
    double V5 = 0;
    double V6 = 0;
    double V7 = 0;
    double V8 = 0;
    double V9 = 0;
    double V10 = 0;
    double V11 = 0;
    double V12 = 0;
    double V13 = 0;
    double V15 = 0;
    double V16 = 0;
    double V17 = 0;
    //2
    double V18 = 0;
    double V19 = 0;
    double V20 = 0;
    double V21 = 0;
    //3
    double V22 = 0;
    double V23 = 0;
    double V24 = 0;
    double V25 = 0;
    double V26 = 0;
    double V27 = 0;
    double V28 = 0;
    double V29 = 0;
    double V30 = 0;
    double V31 = 0;
    double V32 = 0;
    double V33 = 0;
    //4
    double V34 = 0;
    double V35 = 0;
    double V36 = 0;
    double V37 = 0;
    //5
    double V38 = 0;
    double V39 = 0;
    double V40 = 0;
    double V42 = 0;
    double V43 = 0;
    double V44 = 0;
    double V45 = 0;
    double V46 = 0;
    double V47 = 0;
    double V48 = 0;
    double V49 = 0;
    double V50 = 0;
    //6
    double V51 = 0;
    double V52 = 0;
    double V53 = 0;
    double V54 = 0;
    //7
    double V55 = 0;
    double V56 = 0;
    double V57 = 0;
    double V58 = 0;
    double V59 = 0;
    double V60 = 0;
    double V61 = 0;
    double V62 = 0;
    double V63 = 0;
    double V64 = 0;
    double V65 = 0;
    double V66 = 0;

    double setting[N_TATE][N_YOKO] = { 0 };

    srand((unsigned)time(NULL));

    //バイアス電圧をかける
    for (b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++) {
        for (a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++) {
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

    for (b = 25; b < 30; b++) {
        for (a = b - 4; a < 26; a++) {
            Vd4[b][a] = 0;
        }
    }
    Vdn[49][43] = 0;
    Vdn[57][51] = 0;

    Vds[0] = 0.00725;
    Vds[1] = -0.00745;
    Vds[2] = 0.00725;
    Vds[3] = -0.00745;
    Vds[4] = 0.00725;
    Vds[5] = -0.00745;
    Vds[6] = 0.00725;
    Vds[7] = -0.00745;

	while(t <= START_OF_TRIGER + 500){

        //トリガを印加
        if(t > START_OF_TRIGER && t < END_OF_TRIGER){
            Vnt[42][0] = Vin;
            Vnt[34][0] = Vin;
            Vnt[50][8] = Vin;
            Vnt[50][16] = Vin;
        }else{
            Vnt[42][0] = 0;
            Vnt[34][0] = 0;
            Vnt[50][8] = 0;
            Vnt[50][16] = 0;
        }

        if(t > START_OF_TRIGER1 && t < END_OF_TRIGER1){
            Vnt[50][34] = Vin;
            Vnt[50][42] = Vin;
            Vnt[16][0] = Vin;
            Vnt[8][0] = Vin;
        }else{
            Vnt[50][34] = 0;
            Vnt[50][42] = 0;
            Vnt[16][0] = 0;
            Vnt[8][0] = 0;
        }

        if(t > START_OF_TRIGER4 && t < END_OF_TRIGER4){
            Vn4[50][12] = Vin;
            Vn4[0][38] = Vin;
        }else{
            Vn4[50][12] = 0;
            Vn4[0][38] = 0;
        }

        if(t > START_OF_TRIGER5 && t < END_OF_TRIGER5){
            Vn4[50][38] = Vin;
            Vn4[12][0] = Vin;
        }else{
            Vn4[50][38] = 0;
            Vn4[12][0] = 0;
        }

        //周囲の振動子と接続
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
                if((b == 48 && a == 8) || (b == 42 && a == 2) || (b == 42 && a == 9) || (b == 41 && a == 8)){
                    Vst[b][a] = Vns[0];
                }else if ((b == 45 && a == 16) || (b == 38 && a == 16) || (b == 34 && a == 5) || (b == 34 && a == 12)){
                    Vst[b][a] = Vns[1];
                }else if ((b == 22 && a == 8) || (b == 16 && a == 9) || (b == 15 && a == 8) || (b == 16 && a == 2)){
                    Vst[b][a] = Vns[2];
                }else if ((b == 19 && a == 16) || (b == 12 && a == 16) || (b == 8 && a == 12) || (b == 8 && a == 5)){
                    Vst[b][a] = Vns[3];
                }else if ((b == 48 && a == 34) || (b == 42 && a == 28) || (b == 42 && a == 35) || (b == 41 && a == 34)){
                    Vst[b][a] = Vns[4];
                }else if ((b == 45 && a == 42) || (b == 38 && a == 42) || (b == 34 && a == 31) || (b == 34 && a == 38)){
                    Vst[b][a] = Vns[5];
                }else if ((b == 22 && a == 34) || (b == 16 && a == 28) || (b == 16 && a == 35) || (b == 15 && a == 34)){
                    Vst[b][a] = Vns[6];
                }else if ((b == 8 && a == 31) || (b == 8 && a == 38) || (b == 12 && a == 42) || (b == 19 && a == 42)){
                    Vst[b][a] = Vns[7];
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
                if((b == 68 && a == 24) || (b == 69 && a == 23) || (b == 69 && a == 25) || (b == 67 && a == 23) || (b == 76 && a == 32) || (b == 77 && a == 31) || (b == 77 && a == 33) || (b == 75 && a == 31)){
                    Vsn[b][a] = Vns[1];
                }else if((b == 16 && a == 24) || (b == 17 && a == 23) || (b == 17 && a == 25) || (b == 15 && a == 23) || (b == 24 && a == 32) || (b == 25 && a == 31) || (b == 25 && a == 33) || (b == 23 && a == 31)){
                    Vsn[b][a] = Vns[3];
                }else if((b == 68 && a == 76) || (b == 69 && a == 75) || (b == 69 && a == 77) || (b == 67 && a == 75) || (b == 76 && a == 84) || (b == 77 && a == 83) || (b == 77 && a == 85) || (b == 75 && a == 83)){
                    Vsn[b][a] = Vns[5];
                }else if((b == 16 && a == 76) || (b == 17 && a == 75) || (b == 17 && a == 77) || (b == 15 && a == 75) || (b == 24 && a == 84) || (b == 25 && a == 83) || (b == 25 && a == 85) || (b == 23 && a == 83)){
                    Vsn[b][a] = Vns[7];
                }else{
                    Vsn[b][a] = 0;
                }
            }
        }
        //0
        V1 = Vnt[48][8];
        V2 = Vnt[42][2];
        V3 = Vnt[42][9];
        V4 = Vnt[41][8];
        //1
        V5 = Vnt[45][16];
        V6 = Vnt[38][16];
        V7 = Vnt[34][5];
        V8 = Vnt[34][12];
        V9 = Vnn[68][24];
        V10 = Vnn[69][23];
        V11 = Vnn[69][25];
        V12 = Vnn[67][23];
        V13 = Vnn[76][32];
        V15 = Vnn[77][31];
        V16 = Vnn[77][33];
        V17 = Vnn[75][31];
        //2
        V18 = Vnt[22][8];
        V19 = Vnt[16][9];
        V20 = Vnt[15][8];
        V21 = Vnt[16][2];
        //3
        V22 = Vnt[19][16];
        V23 = Vnt[12][16];
        V24 = Vnt[8][12];
        V25 = Vnt[8][5];
        V26 = Vnn[16][24];
        V27 = Vnn[17][23];
        V28 = Vnn[17][25];
        V29 = Vnn[15][23];
        V30 = Vnn[24][32];
        V31 = Vnn[25][31];
        V32 = Vnn[25][33];
        V33 = Vnn[23][31];
        //4
        V34 = Vnt[48][34];
        V35 = Vnt[42][28];
        V36 = Vnt[42][35];
        V37 = Vnt[41][34];
        //5
        V38 = Vnt[45][42];
        V39 = Vnt[38][42];
        V40 = Vnt[34][31];
        V42 = Vnt[34][38];
        V43 = Vnn[68][76];
        V44 = Vnn[69][75];
        V45 = Vnn[69][77];
        V46 = Vnn[67][75];
        V47 = Vnn[76][84];
        V48 = Vnn[77][83];
        V49 = Vnn[77][85];
        V50 = Vnn[75][83];
        //6
        V51 = Vnt[22][34];
        V52 = Vnt[16][28];
        V53 = Vnt[16][35];
        V54 = Vnt[15][34];
        //7
        V55 = Vnt[8][31];
        V56 = Vnt[8][38];
        V57 = Vnt[12][42];
        V58 = Vnt[19][42];
        V59 = Vnn[16][76];
        V60 = Vnn[17][75];
        V61 = Vnn[17][77];
        V62 = Vnn[15][75];
        V63 = Vnn[24][84];
        V64 = Vnn[25][83];
        V65 = Vnn[25][85];
        V66 = Vnn[23][83];

        // ここまでやった(5月14日)
        // 一応座標のチェックをもう一回やる

                
        //電荷計算
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
                if((b == 48 && a == 8) || (b == 42 && a == 2) || (b == 42 && a == 9) || (b == 41 && a == 8) || (b == 45 && a == 16) || (b == 38 && a == 16) || (b == 34 && a == 5) || (b == 34 && a == 12) || (b == 22 && a == 8) || (b == 16 && a == 9) || (b == 15 && a == 8) || (b == 16 && a == 2) || (b == 19 && a == 16) || (b == 12 && a == 16) || (b == 8 && a == 12) || (b == 8 && a == 5) || (b == 48 && a == 34) || (b == 42 && a == 28) || (b == 42 && a == 35) || (b == 41 && a == 34) || (b == 45 && a == 42) || (b == 38 && a == 42) || (b == 34 && a == 31) || (b == 34 && a == 38) || (b == 22 && a == 34) || (b == 16 && a == 28) || (b == 16 && a == 35) || (b == 15 && a == 34) || (b == 8 && a == 31) || (b == 8 && a == 38) || (b == 12 && a == 42) || (b == 19 && a == 42)){
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
                    if((b == 68 && a == 76) || (b == 69 && a == 75) || (b == 69 && a == 77) || (b == 67 && a == 75) || (b == 76 && a == 84) || (b == 77 && a == 83) || (b == 77 && a == 85) || (b == 75 && a == 83) || (b == 16 && a == 76) || (b == 17 && a == 75) || (b == 17 && a == 77) || (b == 15 && a == 75) || (b == 24 && a == 84) || (b == 25 && a == 83) || (b == 25 && a == 85) || (b == 23 && a == 83) || (b == 16 && a == 24) || (b == 17 && a == 23) || (b == 17 && a == 25) || (b == 15 && a == 23) || (b == 24 && a == 32) || (b == 25 && a == 31) || (b == 25 && a == 33) || (b == 23 && a == 31) || (b == 68 && a == 24) || (b == 69 && a == 23) || (b == 69 && a == 25) || (b == 67 && a == 23) || (b == 76 && a == 32) || (b == 77 && a == 31) || (b == 77 && a == 33) || (b == 75 && a == 31)){
                        qn[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Qn[b][a]-Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])-C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])-Cs*Cj*(V1n[b][a]+Vsn[b][a]))-Cj*Ln[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx+2*Cs)+Cj);
                    }else{
                        qn[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Qn[b][a]-Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])-C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])-Cs*Cj*V1n[b][a])-Cj*Ln[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj);
                    }
                }else{
                    if((b == 68 && a == 76) || (b == 69 && a == 75) || (b == 69 && a == 77) || (b == 67 && a == 75) || (b == 76 && a == 84) || (b == 77 && a == 83) || (b == 77 && a == 85) || (b == 75 && a == 83) || (b == 16 && a == 76) || (b == 17 && a == 75) || (b == 17 && a == 77) || (b == 15 && a == 75) || (b == 24 && a == 84) || (b == 25 && a == 83) || (b == 25 && a == 85) || (b == 23 && a == 83) || (b == 16 && a == 24) || (b == 17 && a == 23) || (b == 17 && a == 25) || (b == 15 && a == 23) || (b == 24 && a == 32) || (b == 25 && a == 31) || (b == 25 && a == 33) || (b == 23 && a == 31) || (b == 68 && a == 24) || (b == 69 && a == 23) || (b == 69 && a == 25) || (b == 67 && a == 23) || (b == 76 && a == 32) || (b == 77 && a == 31) || (b == 77 && a == 33) || (b == 75 && a == 31)){
                        qn[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Qn[b][a]-Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])-C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])-Cs*Cj*Vsn[b][a])-Cj*Ln[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj);
                    }else{
                        qn[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Qn[b][a]-Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])-C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a]))-Cj*Ln[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx)+Cj);
                    }
                }
            }
        }

        qs[0] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[0]-Cs*Cj*(V1+V2+V3+V4))-Cj*Ls[0]*e)/(NUMBER_OF_JUNCTION*(4*Cs)+Cj);
        qs[1] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[1]-Cs*Cj*(V5+V6+V7+V8+V9+V10+V11+V12+V13+V15+V16+V17))-Cj*Ls[1]*e)/(NUMBER_OF_JUNCTION*(12*Cs)+Cj);
        qs[2] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[2]-Cs*Cj*(V18+V19+V20+V21))-Cj*Ls[2]*e)/(NUMBER_OF_JUNCTION*(4*Cs)+Cj);
        qs[3] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[3]-Cs*Cj*(V22+V23+V24+V25+V26+V27+V28+V29+V30+V31+V32+V33))-Cj*Ls[3]*e)/(NUMBER_OF_JUNCTION*(12*Cs)+Cj);
        qs[4] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[4]-Cs*Cj*(V34+V35+V36+V37))-Cj*Ls[4]*e)/(NUMBER_OF_JUNCTION*(4*Cs)+Cj);
        qs[5] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[5]-Cs*Cj*(V38+V39+V40+V42+V43+V44+V45+V46+V47+V48+V49+V50))-Cj*Ls[5]*e)/(NUMBER_OF_JUNCTION*(12*Cs)+Cj);
        qs[6] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[6]-Cs*Cj*(V51+V52+V53+V54))-Cj*Ls[6]*e)/(NUMBER_OF_JUNCTION*(4*Cs)+Cj);
        qs[7] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[7]-Cs*Cj*(V55+V56+V57+V58+V59+V60+V61+V62+V63+V64+V65+V66))-Cj*Ls[7]*e)/(NUMBER_OF_JUNCTION*(12*Cs)+Cj);

        //ノード電圧計算
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
        Vns[2] = qs[2]/Cj;
        Vns[3] = qs[3]/Cj;
        Vns[4] = qs[4]/Cj;
        Vns[5] = qs[5]/Cj;
        Vns[6] = qs[6]/Cj;
        Vns[7] = qs[7]/Cj;

        //Vnの出力
        if (t >= START_OF_TRIGER) {
            if(printkaisu == NUMBER_OF_JUNCTION*10){
                for (x = 0; x < N_YOKO - 1; x++) {
                    for (y = 0; y < N_TATE - 1; y++) {
                        if ((x + y) % 2 == 0) {
                            if (y == 0) {
                                printf("%d %d %f\n", x, y, Vnn[y + 2][x + 2]);
                            }
                            else if (y == N_TATE - 2) {
                                printf("%d %d %f\n", x, y, Vnn[y][x + 2]);
                            }
                            else {
                                if (y % 2 == 0){
                                    printf("%d %d %f\n", x, y, Vnn[y + 1][x + 2]);
                                    printf("%d %d %f\n", x, y, Vnn[y + 2][x + 2]);
                                }
                                else{
                                    printf("%d %d %f\n", x, y, -Vnn[y + 1][x + 2]);
                                    printf("%d %d %f\n", x, y, -Vnn[y + 2][x + 2]);
                                }
                            }
                        }
                        else {
                            if (y == 0) {
                                printf("%d %d %f\n", x, y, -Vnn[y + 2][x + 2]);
                            }
                            else if (y == N_TATE - 2) {
                                printf("%d %d %f\n", x, y, -Vnn[y][x + 2]);
                            }
                            else {
                                if (y % 2 == 0){
                                    printf("%d %d %f\n", x, y, -Vnn[y + 1][x + 2]);
                                    printf("%d %d %f\n", x, y, -Vnn[y + 2][x + 2]);
                                }
                                else{
                                    printf("%d %d %f\n", x, y, Vnn[y + 1][x + 2]);
                                    printf("%d %d %f\n", x, y, Vnn[y + 2][x + 2]);
                                }
                            }
                        }
                    }
                    printf("\n");
                    for (y = 0; y < N_TATE - 1; y++) {
                        if ((x + y) % 2 == 0) {
                            if (y == 0) {
                                printf("%d %d %f\n", x + 1, y, Vnn[y + 2][x + 2]);
                            }
                            else if (y == N_TATE - 2) {
                                printf("%d %d %f\n", x + 1, y, Vnn[y][x + 2]);
                            }
                            else {
                                if (y % 2 == 0){
                                    printf("%d %d %f\n", x + 1, y, Vnn[y + 1][x + 2]);
                                    printf("%d %d %f\n", x + 1, y, Vnn[y + 2][x + 2]);
                                }
                                else{
                                    printf("%d %d %f\n", x + 1, y, -Vnn[y + 1][x + 2]);
                                    printf("%d %d %f\n", x + 1, y, -Vnn[y + 2][x + 2]);
                                }
                            }
                        }
                        else {
                            if (y == 0) {
                                printf("%d %d %f\n", x + 1, y, -Vnn[y + 2][x + 2]);
                            }
                            else if (y == N_TATE - 2) {
                                printf("%d %d %f\n", x + 1, y, -Vnn[y][x + 2]);
                            }
                            else {
                                if (y % 2 == 0){
                                    printf("%d %d %f\n", x + 1, y, -Vnn[y + 1][x + 2]);
                                    printf("%d %d %f\n", x + 1, y, -Vnn[y + 2][x + 2]);
                                }
                                else{
                                    printf("%d %d %f\n", x + 1, y, Vnn[y + 1][x + 2]);
                                    printf("%d %d %f\n", x + 1, y, Vnn[y + 2][x + 2]);
                                }
                            }
                        }
                    }
                    printf("\n");
                }
                printf("\n");
                printkaisu = 0;
            } else {
                printkaisu += 1;
            }
        }
        
        //dE計算
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){

                if((b == 48 && a == 8) || (b == 42 && a == 2) || (b == 42 && a == 9) || (b == 41 && a == 8) || (b == 45 && a == 16) || (b == 38 && a == 16) || (b == 34 && a == 5) || (b == 34 && a == 12) || (b == 22 && a == 8) || (b == 16 && a == 9) || (b == 15 && a == 8) || (b == 16 && a == 2) || (b == 19 && a == 16) || (b == 12 && a == 16) || (b == 8 && a == 12) || (b == 8 && a == 5) || (b == 48 && a == 34) || (b == 42 && a == 28) || (b == 42 && a == 35) || (b == 41 && a == 34) || (b == 45 && a == 42) || (b == 38 && a == 42) || (b == 34 && a == 31) || (b == 34 && a == 38) || (b == 22 && a == 34) || (b == 16 && a == 28) || (b == 16 && a == 35) || (b == 15 && a == 34) || (b == 8 && a == 31) || (b == 8 && a == 38) || (b == 12 && a == 42) || (b == 19 && a == 42)){
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
                    if((b == 68 && a == 76) || (b == 69 && a == 75) || (b == 69 && a == 77) || (b == 67 && a == 75) || (b == 76 && a == 84) || (b == 77 && a == 83) || (b == 77 && a == 85) || (b == 75 && a == 83) || (b == 16 && a == 76) || (b == 17 && a == 75) || (b == 17 && a == 77) || (b == 15 && a == 75) || (b == 24 && a == 84) || (b == 25 && a == 83) || (b == 25 && a == 85) || (b == 23 && a == 83) || (b == 16 && a == 24) || (b == 17 && a == 23) || (b == 17 && a == 25) || (b == 15 && a == 23) || (b == 24 && a == 32) || (b == 25 && a == 31) || (b == 25 && a == 33) || (b == 23 && a == 31) || (b == 68 && a == 24) || (b == 69 && a == 23) || (b == 69 && a == 25) || (b == 67 && a == 23) || (b == 76 && a == 32) || (b == 77 && a == 31) || (b == 77 && a == 33) || (b == 75 && a == 31)){
                        dEupn[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*Ln[b][a])*(4*C+4*Cx+2*Cs)*e+Cj*(2*Qn[b][a]-e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])+2*Cs*Cj*(V1n[b][a]+Vsn[b][a]))/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+2*Cs)+Cj));
                        dEdownn[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*Ln[b][a])*(4*C+4*Cx+2*Cs)*e+Cj*(2*Qn[b][a]+e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])+2*Cs*Cj*(V1n[b][a]+Vsn[b][a]))/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+2*Cs)+Cj));
                    }else{
                        dEupn[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*Ln[b][a])*(4*C+4*Cx+Cs)*e+Cj*(2*Qn[b][a]-e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])+2*Cs*Cj*V1n[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj));
                        dEdownn[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*Ln[b][a])*(4*C+4*Cx+Cs)*e+Cj*(2*Qn[b][a]+e)+2*Cx*Cj*(Vln[b][a]+Vrn[b][a]+Vun[b][a]+Vbn[b][a])+2*C*Cj*(Van[b][a]+Vcn[b][a]+Ven[b][a]+Vfn[b][a])+2*Cs*Cj*V1n[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj));
                    }
                }else{
                    if((b == 68 && a == 76) || (b == 69 && a == 75) || (b == 69 && a == 77) || (b == 67 && a == 75) || (b == 76 && a == 84) || (b == 77 && a == 83) || (b == 77 && a == 85) || (b == 75 && a == 83) || (b == 16 && a == 76) || (b == 17 && a == 75) || (b == 17 && a == 77) || (b == 15 && a == 75) || (b == 24 && a == 84) || (b == 25 && a == 83) || (b == 25 && a == 85) || (b == 23 && a == 83) || (b == 16 && a == 24) || (b == 17 && a == 23) || (b == 17 && a == 25) || (b == 15 && a == 23) || (b == 24 && a == 32) || (b == 25 && a == 31) || (b == 25 && a == 33) || (b == 23 && a == 31) || (b == 68 && a == 24) || (b == 69 && a == 23) || (b == 69 && a == 25) || (b == 67 && a == 23) || (b == 76 && a == 32) || (b == 77 && a == 31) || (b == 77 && a == 33) || (b == 75 && a == 31)){
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

        for(b = 0; b < 8; b++) {
            if (b == 0){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*4+2*4*Ls[b])*Cs*e+Cj*(2*Qs[b]-e)+2*Cs*Cj*(V1+V2+V3+V4))/(2*Cj*(4*NUMBER_OF_JUNCTION*Cs+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*4-2*4*Ls[b])*Cs*e+Cj*(2*Qs[b]+e)+2*Cs*Cj*(V1+V2+V3+V4))/(2*Cj*(4*NUMBER_OF_JUNCTION*Cs+Cj));
            }else if (b == 1){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*12+2*12*Ls[b])*Cs*e+Cj*(2*Qs[b]-e)+2*Cs*Cj*(V5+V6+V7+V8+V9+V10+V11+V12+V13+V15+V16+V17))/(2*Cj*(12*NUMBER_OF_JUNCTION*Cs+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*12-2*12*Ls[b])*Cs*e+Cj*(2*Qs[b]+e)+2*Cs*Cj*(V5+V6+V7+V8+V9+V10+V11+V12+V13+V15+V16+V17))/(2*Cj*(12*NUMBER_OF_JUNCTION*Cs+Cj));
            }else if (b == 2){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*4+2*4*Ls[b])*Cs*e+Cj*(2*Qs[b]-e)+2*Cs*Cj*(V18+V19+V20+V21))/(2*Cj*(4*NUMBER_OF_JUNCTION*Cs+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*4-2*4*Ls[b])*Cs*e+Cj*(2*Qs[b]+e)+2*Cs*Cj*(V18+V19+V20+V21))/(2*Cj*(4*NUMBER_OF_JUNCTION*Cs+Cj));
            }else if (b == 3){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*12+2*12*Ls[b])*Cs*e+Cj*(2*Qs[b]-e)+2*Cs*Cj*(V22+V23+V24+V25+V26+V27+V28+V29+V30+V31+V32+V33))/(2*Cj*(12*NUMBER_OF_JUNCTION*Cs+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*12-2*12*Ls[b])*Cs*e+Cj*(2*Qs[b]+e)+2*Cs*Cj*(V22+V23+V24+V25+V26+V27+V28+V29+V30+V31+V32+V33))/(2*Cj*(12*NUMBER_OF_JUNCTION*Cs+Cj));
            }else if (b == 4){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*4+2*4*Ls[b])*Cs*e+Cj*(2*Qs[b]-e)+2*Cs*Cj*(V34+V35+V36+V37))/(2*Cj*(4*NUMBER_OF_JUNCTION*Cs+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*4-2*4*Ls[b])*Cs*e+Cj*(2*Qs[b]+e)+2*Cs*Cj*(V34+V35+V36+V37))/(2*Cj*(4*NUMBER_OF_JUNCTION*Cs+Cj));
            }else if (b == 5){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*12+2*12*Ls[b])*Cs*e+Cj*(2*Qs[b]-e)+2*Cs*Cj*(V38+V39+V40+V42+V43+V44+V45+V46+V47+V48+V49+V50))/(2*Cj*(12*NUMBER_OF_JUNCTION*Cs+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*12-2*12*Ls[b])*Cs*e+Cj*(2*Qs[b]+e)+2*Cs*Cj*(V38+V39+V40+V42+V43+V44+V45+V46+V47+V48+V49+V50))/(2*Cj*(12*NUMBER_OF_JUNCTION*Cs+Cj));
            }else if (b == 6){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*4+2*4*Ls[b])*Cs*e+Cj*(2*Qs[b]-e)+2*Cs*Cj*(V51+V52+V53+V54))/(2*Cj*(4*NUMBER_OF_JUNCTION*Cs+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*4-2*4*Ls[b])*Cs*e+Cj*(2*Qs[b]+e)+2*Cs*Cj*(V51+V52+V53+V54))/(2*Cj*(4*NUMBER_OF_JUNCTION*Cs+Cj));
            }else if (b == 7){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*12+2*12*Ls[b])*Cs*e+Cj*(2*Qs[b]-e)+2*Cs*Cj*(V55+V56+V57+V58+V59+V60+V61+V62+V63+V64+V65+V66))/(2*Cj*(12*NUMBER_OF_JUNCTION*Cs+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*12-2*12*Ls[b])*Cs*e+Cj*(2*Qs[b]+e)+2*Cs*Cj*(V55+V56+V57+V58+V59+V60+V61+V62+V63+V64+V65+V66))/(2*Cj*(12*NUMBER_OF_JUNCTION*Cs+Cj));
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
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*wt_min/R;
            Qs[3] += (Vds[3]-Vns[3])*wt_min/R;
            Qs[4] += (Vds[4]-Vns[4])*wt_min/R;
            Qs[5] += (Vds[5]-Vns[5])*wt_min/R;
            Qs[6] += (Vds[6]-Vns[6])*wt_min/R;
            Qs[7] += (Vds[7]-Vns[7])*wt_min/R;

            Lt[B][A] += 1;

            if(Lt[B][A] == NUMBER_OF_JUNCTION){
                Lt[B][A] = 0;
                Qt[B][A] -= e;
            }
            t += wt_min;
            up = 0;

        }else if((down == 1) && (w == 8)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*wt_min/R;
            Qs[3] += (Vds[3]-Vns[3])*wt_min/R;
            Qs[4] += (Vds[4]-Vns[4])*wt_min/R;
            Qs[5] += (Vds[5]-Vns[5])*wt_min/R;
            Qs[6] += (Vds[6]-Vns[6])*wt_min/R;
            Qs[7] += (Vds[7]-Vns[7])*wt_min/R;

            Lt[B][A] -= 1;
            if(Lt[B][A] == -NUMBER_OF_JUNCTION){
                Lt[B][A] = 0;
                Qt[B][A] += e;
            }
            t += wt_min;
            down = 0;


        }else if((up == 1) && (w == 9)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*wt_min/R;
            Qs[3] += (Vds[3]-Vns[3])*wt_min/R;
            Qs[4] += (Vds[4]-Vns[4])*wt_min/R;
            Qs[5] += (Vds[5]-Vns[5])*wt_min/R;
            Qs[6] += (Vds[6]-Vns[6])*wt_min/R;
            Qs[7] += (Vds[7]-Vns[7])*wt_min/R;

            Ln[B][A] += 1;

            if(Ln[B][A] == NUMBER_OF_JUNCTION){
                Ln[B][A] = 0;
                Qn[B][A] -= e;
            }
            t += wt_min;
            up = 0;

        }else if((down == 1) && (w == 9)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*wt_min/R;
            Qs[3] += (Vds[3]-Vns[3])*wt_min/R;
            Qs[4] += (Vds[4]-Vns[4])*wt_min/R;
            Qs[5] += (Vds[5]-Vns[5])*wt_min/R;
            Qs[6] += (Vds[6]-Vns[6])*wt_min/R;
            Qs[7] += (Vds[7]-Vns[7])*wt_min/R;

            Ln[B][A] -= 1;
            if(Ln[B][A] == -NUMBER_OF_JUNCTION){
                Ln[B][A] = 0;
                Qn[B][A] += e;
            }
            t += wt_min;
            down = 0;


        }else if((up == 1) && (w == 3)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*wt_min/R;
            Qs[3] += (Vds[3]-Vns[3])*wt_min/R;
            Qs[4] += (Vds[4]-Vns[4])*wt_min/R;
            Qs[5] += (Vds[5]-Vns[5])*wt_min/R;
            Qs[6] += (Vds[6]-Vns[6])*wt_min/R;
            Qs[7] += (Vds[7]-Vns[7])*wt_min/R;

            Ls[B] += 1;

            if(Ls[B] == NUMBER_OF_JUNCTION){
                Ls[B] = 0;
                Qs[B] -= e;
            }
            t += wt_min;
            up = 0;

        }else if((down == 1) && (w == 3)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*wt_min/R;
            Qs[3] += (Vds[3]-Vns[3])*wt_min/R;
            Qs[4] += (Vds[4]-Vns[4])*wt_min/R;
            Qs[5] += (Vds[5]-Vns[5])*wt_min/R;
            Qs[6] += (Vds[6]-Vns[6])*wt_min/R;
            Qs[7] += (Vds[7]-Vns[7])*wt_min/R;

            Ls[B] -= 1;
            if(Ls[B] == -NUMBER_OF_JUNCTION){
                Ls[B] = 0;
                Qs[B] += e;
            }
            t += wt_min;
            down = 0;

        }else if((up == 1) && (w == 4)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*wt_min/R;
            Qs[3] += (Vds[3]-Vns[3])*wt_min/R;
            Qs[4] += (Vds[4]-Vns[4])*wt_min/R;
            Qs[5] += (Vds[5]-Vns[5])*wt_min/R;
            Qs[6] += (Vds[6]-Vns[6])*wt_min/R;
            Qs[7] += (Vds[7]-Vns[7])*wt_min/R;

            L4[B][A] += 1;

            if(L4[B][A] == NUMBER_OF_JUNCTION){
                L4[B][A] = 0;
                Q4[B][A] -= e;
            }
            t += wt_min;
            up = 0;

        }else if((down == 1) && (w == 4)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*wt_min/R;
            Qs[3] += (Vds[3]-Vns[3])*wt_min/R;
            Qs[4] += (Vds[4]-Vns[4])*wt_min/R;
            Qs[5] += (Vds[5]-Vns[5])*wt_min/R;
            Qs[6] += (Vds[6]-Vns[6])*wt_min/R;
            Qs[7] += (Vds[7]-Vns[7])*wt_min/R;

            L4[B][A] -= 1;
            if(L4[B][A] == -NUMBER_OF_JUNCTION){
                L4[B][A] = 0;
                Q4[B][A] += e;
            }
            t += wt_min;
            down = 0;


        }else if((up == 1) && (w == 1)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*wt_min/R;
            Qs[3] += (Vds[3]-Vns[3])*wt_min/R;
            Qs[4] += (Vds[4]-Vns[4])*wt_min/R;
            Qs[5] += (Vds[5]-Vns[5])*wt_min/R;
            Qs[6] += (Vds[6]-Vns[6])*wt_min/R;
            Qs[7] += (Vds[7]-Vns[7])*wt_min/R;

            L1[B][A] += 1;

            if(L1[B][A] == NUMBER_OF_JUNCTION){
                L1[B][A] = 0;
                Q1[B][A] -= e;
            }
            t += wt_min;
            up = 0;

        }else if((down == 1) && (w == 1)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*wt_min/R;
            Qs[3] += (Vds[3]-Vns[3])*wt_min/R;
            Qs[4] += (Vds[4]-Vns[4])*wt_min/R;
            Qs[5] += (Vds[5]-Vns[5])*wt_min/R;
            Qs[6] += (Vds[6]-Vns[6])*wt_min/R;
            Qs[7] += (Vds[7]-Vns[7])*wt_min/R;

            L1[B][A] -= 1;
            if(L1[B][A] == -NUMBER_OF_JUNCTION){
                L1[B][A] = 0;
                Q1[B][A] += e;
            }
            t += wt_min;
            down = 0;
        }
        else{
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO; a++){
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
            Qs[2] += (Vds[2]-Vns[2])*dt/R;
            Qs[3] += (Vds[3]-Vns[3])*dt/R;
            Qs[4] += (Vds[4]-Vns[4])*dt/R;
            Qs[5] += (Vds[5]-Vns[5])*dt/R;
            Qs[6] += (Vds[6]-Vns[6])*dt/R;
            Qs[7] += (Vds[7]-Vns[7])*dt/R;
            
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
