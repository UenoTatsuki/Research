#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_JUNCTION 20
#define NUMBER_OF_SINDOUSI_TATE 100
#define NUMBER_OF_SINDOUSI_YOKO 100
#define NUMBER_OF_SINDOUSI_TATE4 50
#define NUMBER_OF_SINDOUSI_YOKO4 50
#define START_OF_TRIGER 3500
#define END_OF_TRIGER 3510
#define START_OF_TRIGER4 3640
#define END_OF_TRIGER4 3645
#define NUM_PULSE 1

int main(){
    double Cj = NUMBER_OF_JUNCTION*10.0; //[aF]
    double C = 2.0;//[aF] 斜め方向のキャパシタ
    double Cx = 2.5;//[aF] 縦横方向のキャパシタ
    double Cs8 = 2.0;//[aF]
    double Cs4 = 3.5;//[aF]
    double R = 30.0; //[G]
    double Rj = 0.001;//[G]
    double Vd8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; //[V]
    double Vd4[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0}; //[V]
    double Vd1[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0}; //[V]
    double Vin = 0.01;//[V]
    double Vn8[NUMBER_OF_SINDOUSI_TATE+2][NUMBER_OF_SINDOUSI_YOKO+2] = {0.0};  //[V]
    double Vn4[NUMBER_OF_SINDOUSI_TATE4+2][NUMBER_OF_SINDOUSI_YOKO4+2] = {0.0};  //[V]
    double Vn1[NUMBER_OF_SINDOUSI_TATE+2][NUMBER_OF_SINDOUSI_YOKO+2] = {0.0};  //[V]
    double Q8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; 
    double Q4[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0}; 
    double Q1[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0}; 
    double t = 0.0; //[ns]
    double dt = 0.1, dq;
    double e = 0.1602,r;
    int L8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0};
    int L4[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0};
    int L1[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0};
    double q_sum8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double q_sum4[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    double q_sum1[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    double dEup8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEdown8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEup4[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    double dEdown4[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    double dEup1[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    double dEdown1[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    int up = 0;
    int down = 0;
    double wt = 0;
    int i, j = 0;
    double wt_min = 1000.0;
    int A, B = 0;
    int a, b = 0;
    int x, y = 0;
    int m = 0;
    int w = 0;
    int printkaisu = 0;
    //8結合層の周囲の振動子
    double Vl8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vr8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vu8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vb8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Va8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vc8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Ve8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vf8[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double V18[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; //中間振動子１と接続
    //4結合層の周囲の振動子
    double Vl4[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    double Vr4[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    double Vu4[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    double Vb4[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    double V14[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0}; //中間振動子１と接続
    //中間振動子の周囲振動子
    double V81[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};
    double V41[NUMBER_OF_SINDOUSI_TATE4+1][NUMBER_OF_SINDOUSI_YOKO4+1] = {0.0};

    double setting[NUMBER_OF_SINDOUSI_TATE][NUMBER_OF_SINDOUSI_YOKO] = { 0 };


    srand((unsigned)time(NULL));

    for (b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++) {
        for (a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++) {
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
   Vd8[2][2] = 0;
   Vd8[9][3] = 0;
   Vd8[3][9] = 0;
   Vd1[2][2] = 0;

    for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-2; b++){
        for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-2; a++){
            if((a+b)%2 == 0){
                Vd4[b][a] = -0.00743; //0.0078[V]
                Vd1[b][a] = -0.00760; //0.007877[V]
            }else{
                Vd4[b][a] = 0.00743;
                Vd1[b][a] = 0.00760;
            }
        }
    }

	while(t <= START_OF_TRIGER + 500){

        if(t > START_OF_TRIGER && t < END_OF_TRIGER){
            Vn8[8][0] = -Vin;
            Vn8[0][8] = -Vin;
        }else{
            Vn8[8][0] = 0;
            Vn8[0][8] = 0;
        }

        if(t > START_OF_TRIGER && t < END_OF_TRIGER){
            Vn8[10][0] = Vin;
            Vn8[9][1] = Vin;
            Vn8[0][10] = Vin;
            Vn8[1][9] = Vin;
        }else{
            Vn8[10][0] = 0;
            Vn8[9][1] = 0;
            Vn8[0][10] = 0;
            Vn8[1][9] = 0;
        }

        if(t > START_OF_TRIGER4 && t < END_OF_TRIGER4){
            Vn4[1][0] = -Vin;
            Vn4[0][0] = 0;
        }else{
            Vn4[1][0] = 0;
            Vn4[0][0] = 0;
        }

        //周囲の振動子と接続
        for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                Vl8[b][a] = Vn8[b][a-2];
                Vr8[b][a] = Vn8[b][a+2];
                Vu8[b][a] = Vn8[b+2][a];
                Vb8[b][a] = Vn8[b-2][a];
                Va8[b][a] = Vn8[b-1][a-1];
                Vc8[b][a] = Vn8[b-1][a+1];
                Ve8[b][a] = Vn8[b+1][a-1];
                Vf8[b][a] = Vn8[b+1][a+1];
                if(b % 2 == 0 && a % 2 == 0){
                    V18[b][a] = Vn1[b/2][a/2];
                }else{
                    V18[b][a] = 0;
                }
            }
        }
        
        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
                Vl4[b][a] = Vn4[b][a-1];
                Vr4[b][a] = Vn4[b][a+1];
                Vu4[b][a] = Vn4[b+1][a];
                Vb4[b][a] = Vn4[b-1][a];
                V14[b][a] = Vn1[b][a];
                V81[b][a] = Vn8[2*b][2*a];
                V41[b][a] = Vn4[b][a];
            }
        }
                
        //Vnの計算
        for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                if(b % 2 == 0 && a % 2 == 0){
                    q_sum8[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Q8[b][a]-Cx*Cj*(Vl8[b][a]+Vr8[b][a]+Vu8[b][a]+Vb8[b][a])-C*Cj*(Va8[b][a]+Vc8[b][a]+Ve8[b][a]+Vf8[b][a])-Cs8*Cj*V18[b][a])-Cj*L8[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs8)+Cj);
                }else{
                    q_sum8[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Q8[b][a]-Cx*Cj*(Vl8[b][a]+Vr8[b][a]+Vu8[b][a]+Vb8[b][a])-C*Cj*(Va8[b][a]+Vc8[b][a]+Ve8[b][a]+Vf8[b][a]))-Cj*L8[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+4*Cx)+Cj);
                }
            }
        }

        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
                q_sum4[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Q4[b][a]-C*Cj*(Vl4[b][a]+Vr4[b][a]+Vu4[b][a]+Vb4[b][a])-Cs4*Cj*V14[b][a])-Cj*L4[b][a]*e)/(NUMBER_OF_JUNCTION*(4*C+Cs4)+Cj);
                q_sum1[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Q1[b][a]-Cs4*Cj*V41[b][a]-Cs8*Cj*V81[b][a])-Cj*L1[b][a]*e)/(NUMBER_OF_JUNCTION*(Cs4+Cs8)+Cj);
            }
        }
        
        for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                Vn8[b][a] = q_sum8[b][a]/Cj;
            }
        }

        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
                Vn4[b][a] = q_sum4[b][a]/Cj;
                Vn1[b][a] = q_sum1[b][a]/Cj;
            }
        }

        

        //Vnの出力
        if(t >= START_OF_TRIGER){
            if(printkaisu == NUMBER_OF_JUNCTION*10){
                for (x = 0; x < NUMBER_OF_SINDOUSI_YOKO4-1; x++) {
                    for (y = 0; y < NUMBER_OF_SINDOUSI_TATE4; y++) {
                        if ((x + y) % 2 == 0) {
                            if (y == 0) {
                                printf("%d %d %f\n", x, y, -Vn1[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE4 - 1) {
                                printf("%d %d %f\n", x, y, Vn1[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x, y, Vn1[y][x + 1]);
                                printf("%d %d %f\n", x, y, -Vn1[y + 1][x + 1]);
                            }
                        } else {
                            if (y == 0) {
                                printf("%d %d %f\n", x, y, Vn1[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE4 - 1) {
                                printf("%d %d %f\n", x, y, -Vn1[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x, y, -Vn1[y][x + 1]);
                                printf("%d %d %f\n", x, y, Vn1[y + 1][x + 1]);
                            }
                        }
                    }
                    printf("\n");
                    for (y = 0; y < NUMBER_OF_SINDOUSI_TATE4; y++) {
                        if ((x + y) % 2 == 0) {
                            if (y == 0) {
                                printf("%d %d %f\n", x + 1, y, -Vn1[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE4 - 1) {
                                printf("%d %d %f\n", x + 1, y, Vn1[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x + 1, y, Vn1[y][x + 1]);
                                printf("%d %d %f\n", x + 1, y, -Vn1[y + 1][x + 1]);
                            }
                        } else {
                            if (y == 0) {
                                printf("%d %d %f\n", x + 1, y, Vn1[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE4 - 1) {
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
        for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
            for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                if(b % 2 == 0 && a % 2 == 0){
                    dEup8[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*L8[b][a])*(4*C+4*Cx+Cs8)*e+Cj*(2*Q8[b][a]-e)+2*Cx*Cj*(Vl8[b][a]+Vr8[b][a]+Vu8[b][a]+Vb8[b][a])+2*C*Cj*(Va8[b][a]+Vc8[b][a]+Ve8[b][a]+Vf8[b][a])+2*Cs8*Cj*V18[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs8)+Cj));
                    dEdown8[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*L8[b][a])*(4*C+4*Cx+2*Cs8)*e+Cj*(2*Q8[b][a]+e)+2*Cx*Cj*(Vl8[b][a]+Vr8[b][a]+Vu8[b][a]+Vb8[b][a])+2*C*Cj*(Va8[b][a]+Vc8[b][a]+Ve8[b][a]+Vf8[b][a])+2*Cs8*Cj*V18[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx+Cs8)+Cj));
                }else{
                    dEup8[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*L8[b][a])*(4*C+4*Cx)*e+Cj*(2*Q8[b][a]-e)+2*Cx*Cj*(Vl8[b][a]+Vr8[b][a]+Vu8[b][a]+Vb8[b][a])+2*C*Cj*(Va8[b][a]+Vc8[b][a]+Ve8[b][a]+Vf8[b][a]))/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx)+Cj));
                    dEdown8[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*L8[b][a])*(4*C+4*Cx)*e+Cj*(2*Q8[b][a]+e)+2*Cx*Cj*(Vl8[b][a]+Vr8[b][a]+Vu8[b][a]+Vb8[b][a])+2*C*Cj*(Va8[b][a]+Vc8[b][a]+Ve8[b][a]+Vf8[b][a]))/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+4*Cx)+Cj));
                }

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

        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
                dEup4[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*L4[b][a])*(4*C+Cs4)*e+Cj*(2*Q4[b][a]-e)+2*C*Cj*(Vl4[b][a]+Vr4[b][a]+Vu4[b][a]+Vb4[b][a])+2*Cs4*Cj*V14[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+Cs4)+Cj));
                dEdown4[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*L4[b][a])*(4*C+Cs4)*e+Cj*(2*Q4[b][a]+e)+2*C*Cj*(Vl4[b][a]+Vr4[b][a]+Vu4[b][a]+Vb4[b][a])+2*Cs4*Cj*V14[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(4*C+Cs4)+Cj));

                dEup1[b][a] = e*((-(NUMBER_OF_JUNCTION-1)+2*L1[b][a])*(Cs4+Cs8)*e+Cj*(2*Q1[b][a]-e)+2*Cs4*Cj*V41[b][a]+2*Cs8*Cj*V81[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(Cs4+Cs8)+Cj));
                dEdown1[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)-2*L1[b][a])*(Cs4+Cs8)*e+Cj*(2*Q1[b][a]+e)+2*Cs4*Cj*V41[b][a]+2*Cs8*Cj*V81[b][a])/(2*Cj*(NUMBER_OF_JUNCTION*(Cs4+Cs8)+Cj));

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

        if(up == 1 && w == 8){
            for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
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
            for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
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
            for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
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
            for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
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
            for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            L1[B][A] += 1;

            if(L1[B][A] == NUMBER_OF_JUNCTION){
                L1[B][A] = 0;
                Q1[B][A] -= e;
            }
            t += wt_min;
            up = 0;

        }else if(down == 1 && w == 1){
            for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*wt_min/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
                    Q4[b][a] += (Vd4[b][a]-Vn4[b][a])*wt_min/R;
                    Q1[b][a] += (Vd1[b][a]-Vn1[b][a])*wt_min/R;
                }
            }
            L1[B][A] -= 1;
            if(L1[B][A] == -NUMBER_OF_JUNCTION){
                L1[B][A] = 0;
                Q1[B][A] += e;
            }
            t += wt_min;
            down = 0;

        }else{
            for(b = 2; b < NUMBER_OF_SINDOUSI_TATE-1; b++){
                for(a = 2; a < NUMBER_OF_SINDOUSI_YOKO-1; a++){
                    Q8[b][a] += (Vd8[b][a]-Vn8[b][a])*dt/R;
                }
            }
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE4-1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO4-1; a++){
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
        w = 0;
	}
	return 0;
}
