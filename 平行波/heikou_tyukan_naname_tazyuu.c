#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_JUNCTION 20
//4結合層のサイズ
#define NUMBER_OF_SINDOUSI_TATE 25 
#define NUMBER_OF_SINDOUSI_YOKO 25
//8結合層のサイズ
#define NUMBER_OF_SINDOUSI_TATE8 50
#define NUMBER_OF_SINDOUSI_YOKO8 50
#define START_OF_TRIGER 2500
#define END_OF_TRIGER 3000
#define NUM_PULSE 1

int main(){
    double Cj = NUMBER_OF_JUNCTION*10.0; //[aF]
    double Cj1 = 10;
    double C = 2.0;//[aF] 斜め方向のキャパシタ
    double Cx = 2.5;//[aF] 縦横方向のキャパシタ
    double Cs = 2.0;//[aF] //層間キャパシタ
    double R = 10.0; //[G]
    double Rj = 0.001;//[G]
    double Vd8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0}; //[V]
    double Vd4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; //[V]
    double Vd1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; //[V]
    double Vin = 0.01;//[V]
    double Vn8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};  //[V]
    double Vn4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};  //[V]
    double Vn1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};  //[V]
    double Q8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0}; 
    double Q4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; 
    double Q1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double t = 0.0; //[ns]
    double dt = 0.1, dq;
    double e = 0.1602,r;
    int L8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0};
    int L4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0};
    double q_sum8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double q_sum4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double q4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double q8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEup8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double dEup4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEup1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEdown8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double dEdown4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEdown1[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    int up = 0;
    int down = 0;
    double wt = 0;
    int w = 0;
    int i, j = 0;
    double wt_min = 1000.0;
    int A, B = 0;
    int a, b = 0;
    int pulse1[NUM_PULSE][2] = {{0,6}};
    int pulse2[NUM_PULSE][2] = {{6,0}};
    int x, y = 0;
    int m = 0;
    int printkaisu = 0;
    //8結合層の周囲の振動子
    double Vl8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double Vr8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double Vu8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double Vb8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double V18[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double V28[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double V38[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double V48[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    double Vs8[NUMBER_OF_SINDOUSI_TATE8+1][NUMBER_OF_SINDOUSI_YOKO8+1] = {0.0};
    //4結合層の周囲の振動子
    double Vl4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vr4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vu4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vb4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vs4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};

    //中間層の周囲の振動子
    double V8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; //8結合層と接続
    double V4[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; //4結合層と接続

    double setting[NUMBER_OF_SINDOUSI_TATE8][NUMBER_OF_SINDOUSI_YOKO8] = { 0 };


    srand((unsigned)time(NULL));

    //8結合層にバイアス電圧をかける
    for (b = 2; b < NUMBER_OF_SINDOUSI_TATE8-2; b++) {
        for (a = 2; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++) {
            if (setting[b][a] == 1){
                Vd8[b][a] = 0;
            } else {
                if (b % 2 == 0){
                    if ((a + b) % 2 == 0) {
                        Vd8[b][a] = 0.00750; //閾値0.007743[V]
                    } else {
                        Vd8[b][a] = -0.00750;
                    }
                }
                else{
                    if ((a + b) % 2 == 0) {
                        Vd8[b][a] = -0.00750;
                    } else {
                        Vd8[b][a] = 0.00750;
                    }
                }
                
            }
        }
    }

    //4結合層と中間層にバイアス電圧をかける
    for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
        for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
            if((a+b)%2 == 0){
                Vd4[b][a] = -0.00755; //0.0078098[V]
                Vd1[b][a] = -0.00568;
            }else{
                Vd4[b][a] = 0.00755;
                Vd1[b][a] = 0.00568;
            }
        }
    }

    //ループ開始
	while(t <= START_OF_TRIGER + 500){

        //8結合層にトリガ
        if(t > START_OF_TRIGER && t < END_OF_TRIGER){
            Vn8[8][0] = -Vin;
            Vn8[0][8] = -Vin;
            Vn8[10][0] = Vin;
            Vn8[9][1] = Vin;
            Vn8[0][10] = Vin;
            Vn8[1][9] = Vin;
        }else{
            Vn8[8][0] = 0;
            Vn8[0][8] = 0;
            Vn8[10][0] = 0;
            Vn8[9][1] = 0;
            Vn8[0][10] = 0;
            Vn8[1][9] = 0;
        }

        //4結合層にトリガ
        if(t > START_OF_TRIGER + 50 && t < END_OF_TRIGER){
            Vn4[1][1] = Vin;
        }else{
            Vn4[1][1] = 0;
        }


        // if(t > START_OF_TRIGER && t < END_OF_TRIGER){
        //     for(m = 0; m < NUM_PULSE; m++){
        //         if((pulse1[m][0]+pulse1[m][1])%2 == 1){
        //             Vn[pulse1[m][0]][pulse1[m][1]] = Vin;
        //         }else{
        //             Vn[pulse1[m][0]][pulse1[m][1]] = Vin;
        //         }
        //     }
        // }else{
        //     for(m = 0; m < NUM_PULSE; m++){
        //         if((pulse1[m][0]+pulse1[m][1])%2 == 1){
        //             Vn[pulse1[m][0]][pulse1[m][1]] = 0;
        //         }else{
        //             Vn[pulse1[m][0]][pulse1[m][1]] = 0;
        //         }
        //     }
        // }

        // if(t > START_OF_TRIGER && t < END_OF_TRIGER){
        //     for(m = 0; m < NUM_PULSE; m++){
        //         if((pulse2[m][0]+pulse2[m][1])%2 == 1){
        //             Vn[pulse2[m][0]][pulse2[m][1]] = Vin;
        //         }else{
        //             Vn[pulse2[m][0]][pulse2[m][1]] = Vin;
        //         }
        //     }
        // }else{
        //     for(m = 0; m < NUM_PULSE; m++){
        //         if((pulse2[m][0]+pulse2[m][1])%2 == 1){
        //             Vn[pulse2[m][0]][pulse2[m][1]] = 0;
        //         }else{
        //             Vn[pulse2[m][0]][pulse2[m][1]] = 0;
        //         }
        //     }
        // }

        //周囲の振動子と接続
        for(b = 2; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
            for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                Vl8[b][a] = Vn8[b][a-2];
                Vr8[b][a] = Vn8[b][a+2];
                Vu8[b][a] = Vn8[b+2][a];
                Vb8[b][a] = Vn8[b-2][a];
                V18[b][a] = Vn8[b-1][a-1];
                V28[b][a] = Vn8[b-1][a+1];
                V38[b][a] = Vn8[b+1][a-1];
                V48[b][a] = Vn8[b+1][a+1];
                if(b % 2 == 0 && a % 2 == 0){
                    Vs8[b][a] = Vn1[b/2][a/2];
                }else{
                    Vs8[b][a] = 0;
                }
            }
        }
        
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                Vl4[b][a] = Vn4[b][a-1];
                Vr4[b][a] = Vn4[b][a+1];
                Vu4[b][a] = Vn4[b+1][a];
                Vb4[b][a] = Vn4[b-1][a];
                Vs4[b][a] = Vn1[b][a];
                V8[b][a] = Vn8[2*b][2*a];
                V4[b][a] = Vn4[b][a];
            }
        }
                
        //電荷の計算
        for(b = 2; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
            for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                q_sum8[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Q8[b][a]-Cx*Cj*(Vl8[b][a]+Vr8[b][a]+Vu8[b][a]+Vb8[b][a])-C*Cj*(V18[b][a]+V28[b][a]+V38[b][a]+V48[b][a]))-Cs*Cj*Vs8[b][a]-Cj*L8[b][a]*e)/(4*NUMBER_OF_JUNCTION*(C+Cx)+NUMBER_OF_JUNCTION*Cs+Cj);
            }
        }

        for(b = 2; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
            for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                Vn8[b][a] = q_sum8[b][a]/Cj;
            }
        }

        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                q_sum4[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Q4[b][a]-C*Cj*(Vl4[b][a]+Vr4[b][a]+Vu4[b][a]+Vb4[b][a]))-Cs*Cj*Vs4[b][a]-Cj*L4[b][a]*e)/(4*NUMBER_OF_JUNCTION*C+NUMBER_OF_JUNCTION*Cs+Cj);
                q4[b][a] = (Cs*(-Q1[b][a] + Cj1 * V4[b][a] + Cs * (V4[b][a] - V8[b][a]))) / (2 * Cs + Cj1);
                q8[b][a] = (Cs*(-Q1[b][a] + Cj1 * V8[b][a] + Cs * (V8[b][a] - V4[b][a]))) / (2 * Cs + Cj1);
            }
        }

        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                Vn4[b][a] = q_sum4[b][a]/Cj;
                Vn1[b][a] = (Q1[b][a]+q4[b][a]+q8[b][a])/Cj1;
            }
        }

        //Vnの出力
        if(t >= START_OF_TRIGER){
            if(printkaisu == NUMBER_OF_JUNCTION*10){
                for (x = 0; x < NUMBER_OF_SINDOUSI_YOKO-1; x++) {
                    for (y = 0; y < NUMBER_OF_SINDOUSI_TATE; y++) {
                        if ((x + y) % 2 == 0) {
                            if (y == 0) {
                                printf("%d %d %f\n", x, y, -Vn1[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x, y, Vn1[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x, y, Vn1[y][x + 1]);
                                printf("%d %d %f\n", x, y, -Vn1[y + 1][x + 1]);
                            }
                        } else {
                            if (y == 0) {
                                printf("%d %d %f\n", x, y, Vn1[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x, y, -Vn1[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x, y, -Vn1[y][x + 1]);
                                printf("%d %d %f\n", x, y, Vn1[y + 1][x + 1]);
                            }
                        }
                    }
                    printf("\n");
                    for (y = 0; y < NUMBER_OF_SINDOUSI_TATE; y++) {
                        if ((x + y) % 2 == 0) {
                            if (y == 0) {
                                printf("%d %d %f\n", x + 1, y, -Vn1[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x + 1, y, Vn1[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x + 1, y, Vn1[y][x + 1]);
                                printf("%d %d %f\n", x + 1, y, -Vn1[y + 1][x + 1]);
                            }
                        } else {
                            if (y == 0) {
                                printf("%d %d %f\n", x + 1, y, Vn1[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x + 1, y, -Vn1[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x + 1, y, -Vn1[y][x + 1]);
                                printf("%d %d %f\n", x + 1, y, Vn1[y + 1][x + 1]);
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
        
        //dEの計算
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                dEup8[b][a] = e*((-(NUMBER_OF_JUNCTION-1)*1+2*L8[b][a])*(4*C+4*Cx+Cs)*e+Cj*(2*Q8[b][a]-e)+2*Cx*Cj*(Vl8[b][a]+Vr8[b][a]+Vu8[b][a]+Vb8[b][a])+2*C*Cj*(V18[b][a]+V28[b][a]+V38[b][a]+V48[b][a])+2*Cs*Cj*Vs8[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj));
                dEdown8[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)*1-2*L8[b][a])*(4*C+4*Cx+Cs)*e+Cj*(2*Q8[b][a]+e)+2*Cx*Cj*(Vl8[b][a]+Vr8[b][a]+Vu8[b][a]+Vb8[b][a])+2*C*Cj*(V18[b][a]+V28[b][a]+V38[b][a]+V48[b][a])+2*Cs*Cj*Vs8[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs)+Cj));

                if(dEup8[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION-L8[b][a]; j++){
                        r = (double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEup8[b][a])*log(1/r);
                        
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
                if(dEdown8[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION+L8[b][a]; j++){
                        r=(double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEdown8[b][a])*log(1/r);

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
            }
        }

        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                dEup4[b][a] = e*((-(NUMBER_OF_JUNCTION-1)*1+2*L4[b][a])*(4*C+Cs)*e+Cj*(2*Q4[b][a]-e)+2*C*Cj*(Vl4[b][a]+Vr4[b][a]+Vu4[b][a]+Vb4[b][a])+2*Cs*Cj*Vs4[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+Cs)+Cj));
                dEdown4[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)*1-2*L4[b][a])*(4*C+Cs)*e+Cj*(2*Q4[b][a]+e)+2*C*Cj*(Vl4[b][a]+Vr4[b][a]+Vu4[b][a]+Vb4[b][a])+2*Cs*Cj*Vs4[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+Cs)+Cj));

                dEup1[b][a] = e * (-e + 2 * (Q1[b][a] + Cs * (V8[b][a]+V4[b][a]))) / (2 * (2 * Cs + Cj1));
                dEdown1[b][a] = -e * (e + 2 * (Q1[b][a] + Cs * (V8[b][a]+V4[b][a]))) / (2 * (2 * Cs + Cj1));

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
                if(dEdown1[b][a] > 0){
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

        //トンネルする振動子を決定
        if(up == 1 && w == 8){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            L8[B][A] += 1;

            if(L8[B][A] == NUMBER_OF_JUNCTION){
                L8[B][A] = 0;
                Q8[B][A] -= e;
            }
            t += wt_min;
            up = 0;
        }else if(down == 1 && w == 8){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            L8[B][A] -= 1;
            if(L8[B][A] == -NUMBER_OF_JUNCTION){
                L8[B][A] = 0;
                Q8[B][A] += e;
            }
            t += wt_min;
            down = 0;
        }else if(up == 1 && w == 4){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            L4[B][A] += 1;

            if(L4[B][A] == NUMBER_OF_JUNCTION){
                L4[B][A] = 0;
                Q4[B][A] -= e;
            }
            t += wt_min;
            up = 0;
        }else if(down == 1 && w == 4){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            L4[B][A] -= 1;
            if(L4[B][A] == -NUMBER_OF_JUNCTION){
                L4[B][A] = 0;
                Q4[B][A] += e;
            }
            t += wt_min;
            down = 0;
        }else if(up == 1 && w == 1){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            Q1[B][A] -= e;
            t += wt_min;
            up = 0;
        }else if(down == 1 && w == 1){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            Q1[B][A] += e;
            t += wt_min;
            down = 0;
        }else{
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE8-2; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO8-2; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*dt/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*dt/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*dt/R;
                }
            }
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
