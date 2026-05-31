#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_JUNCTION 50
#define NUMBER_OF_SINDOUSI_TATE 50
#define NUMBER_OF_SINDOUSI_YOKO 50
#define START_OF_TRIGER 2500
#define END_OF_TRIGER 2505
#define NUM_PULSE 2

int main(){
    double Cj = NUMBER_OF_JUNCTION*10.0; //[aF]
    double C = 2.0;//[aF]
    double R = 0.3; //[G]
    double Rj = 0.001;//[G]
    double Vd[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0}; //[V]
    double Vds[2] = {0.0};
    double Vin = 0.01;//[V]
    double Vn[NUMBER_OF_SINDOUSI_TATE+2][NUMBER_OF_SINDOUSI_YOKO+2] = {0.0};  //[V]
    double Vns[2] = {0.0};
    double Q[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Qs[2] = {0.0}; 
    double t = 0.0; //[ns]
    double dt = 0.1, dq;
    double e = 0.1602,r;
    int L[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0};
    int Ls[2] = {0};
    double q_sum[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double qs[2] = {0.0};
    double dEup[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double dEdown[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
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
    int pulse[NUM_PULSE][2] = {{50,25}};
    int x, y = 0;
    int m = 0;
    int printkaisu = 0;
    double Vl[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vr[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vu[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double Vb[NUMBER_OF_SINDOUSI_TATE+1][NUMBER_OF_SINDOUSI_YOKO+1] = {0.0};
    double V1 = 0, V2 = 0, V3 = 0, V4 = 0, V5 = 0, V6 = 0, V7 = 0, V8 = 0;


    srand((unsigned)time(NULL));

    for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
        for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
            if((a+b)%2 == 0){
                Vd[b][a] = 0.00785;
            }else{
                Vd[b][a] = -0.00785;
            }
        }
    }

    Vds[0] = -0.0074;

    for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
        for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
            if((b < 22 && a < 22) || (b > 28 && a < 22) || a > 28){
                Vd[b][a] = 0;
            }else if ((b > 21 && b <29) && a == 21){
                Vd[b][a] = 0;
            }
        }
    }



	while(t <= START_OF_TRIGER + 500){

        if(t > START_OF_TRIGER && t < END_OF_TRIGER){
            for(m = 0; m < NUM_PULSE; m++){
                if((pulse[m][0]+pulse[m][1])%2 == 1){
                    Vn[pulse[m][0]][pulse[m][1]] = Vin;
                }else{
                    Vn[pulse[m][0]][pulse[m][1]] = -Vin;
                }
            }
        }else{
            for(m = 0; m < NUM_PULSE; m++){
                if((pulse[m][0]+pulse[m][1])%2 == 1){
                    Vn[pulse[m][0]][pulse[m][1]] = 0;
                }else{
                    Vn[pulse[m][0]][pulse[m][1]] = 0;
                }
            }
        }

        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
                if ((b == 22 && a == 22) || (b == 24 && a == 22) || (b == 26 && a == 22) || (b == 28 && a == 22)){
                    Vl[b][a] = Vns[0];
                    Vr[b][a] = Vn[b][a+1];
                    Vu[b][a] = Vn[b+1][a];
                    Vb[b][a] = Vn[b-1][a];
                }else if ((b == 22 && a == 20) || (b == 24 && a == 20) || (b == 26 && a == 20) || (b == 28 && a == 20)){
                    Vl[b][a] = Vn[b][a-1];
                    Vr[b][a] = Vns[0];
                    Vu[b][a] = Vn[b+1][a];
                    Vb[b][a] = Vn[b-1][a];
                }else{
                    Vl[b][a] = Vn[b][a-1];
                    Vr[b][a] = Vn[b][a+1];
                    Vu[b][a] = Vn[b+1][a];
                    Vb[b][a] = Vn[b-1][a];
                }
            }
        } 

        V1 = Vn[22][22], V2 = Vn[24][22], V3 = Vn[26][22], V4 = Vn[28][22], V5 = Vn[22][20], V6 = Vn[24][20], V7 = Vn[26][20], V8 = Vn[28][20];
                

        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
                q_sum[b][a] = (-NUMBER_OF_JUNCTION*(-Cj*Q[b][a]-C*Cj*(Vl[b][a]+Vr[b][a]+Vu[b][a]+Vb[b][a]))-Cj*L[b][a]*e)/(4*NUMBER_OF_JUNCTION*C+Cj);
            }
        }

        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
                Vn[b][a] = q_sum[b][a]/Cj;
            }
        }

        qs[0] = (-NUMBER_OF_JUNCTION*(-Cj*Qs[0]-C*Cj*(V1+V2+V3+V4+V5+V6+V7+V8))-Cj*Ls[0]*e)/(NUMBER_OF_JUNCTION*(8*C)+Cj);

        Vns[0] = qs[0]/Cj;

        if(t >= START_OF_TRIGER){
            if(printkaisu == NUMBER_OF_JUNCTION*10){
                for (x = 0; x < NUMBER_OF_SINDOUSI_YOKO-1; x++) {
                    for (y = 0; y < NUMBER_OF_SINDOUSI_TATE; y++) {
                        if ((x + y) % 2 == 0) {
                            if (y == 0) {
                                printf("%d %d %f\n", x, y, Vn[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x, y, -Vn[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x, y, -Vn[y][x + 1]);
                                printf("%d %d %f\n", x, y, Vn[y + 1][x + 1]);
                            }
                        } else {
                            if (y == 0) {
                                printf("%d %d %f\n", x, y, -Vn[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x, y, Vn[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x, y, Vn[y][x + 1]);
                                printf("%d %d %f\n", x, y, -Vn[y + 1][x + 1]);
                            }
                        }
                    }
                    printf("\n");
                    for (y = 0; y < NUMBER_OF_SINDOUSI_TATE; y++) {
                        if ((x + y) % 2 == 0) {
                            if (y == 0) {
                                printf("%d %d %f\n", x + 1, y, Vn[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x + 1, y, -Vn[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x + 1, y, -Vn[y][x + 1]);
                                printf("%d %d %f\n", x + 1, y, Vn[y + 1][x + 1]);
                            }
                        } else {
                            if (y == 0) {
                                printf("%d %d %f\n", x + 1, y, -Vn[y + 1][x + 1]);
                            } else if (y == NUMBER_OF_SINDOUSI_TATE - 1) {
                                printf("%d %d %f\n", x + 1, y, Vn[y][x + 1]);
                            } else {
                                printf("%d %d %f\n", x + 1, y, Vn[y][x + 1]);
                                printf("%d %d %f\n", x + 1, y, -Vn[y + 1][x + 1]);
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
        

        for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
            for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
                dEup[b][a] = e*((-(NUMBER_OF_JUNCTION-1)*4+2*4*L[b][a])*C*e+Cj*(2*Q[b][a]-e)+2*C*Cj*(Vl[b][a]+Vr[b][a]+Vu[b][a]+Vb[b][a]))/(2*Cj*(4*NUMBER_OF_JUNCTION*C+Cj));
                dEdown[b][a] = -e*(-(-(NUMBER_OF_JUNCTION-1)*4-2*4*L[b][a])*C*e+Cj*(2*Q[b][a]+e)+2*C*Cj*(Vl[b][a]+Vr[b][a]+Vu[b][a]+Vb[b][a]))/(2*Cj*(4*NUMBER_OF_JUNCTION*C+Cj));

                if(dEup[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION-L[b][a]; j++){
                        r = (double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEup[b][a])*log(1/r);
                        
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
                if(dEdown[b][a] > 0){
                    for(j = 0; j < NUMBER_OF_JUNCTION+L[b][a]; j++){
                        r=(double)rand()/RAND_MAX;
                        wt = (e*e*Rj/dEdown[b][a])*log(1/r);

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

        for(b = 0; b < 2; b++) {
            if (b == 0){
                dEups[b] = e*((-(NUMBER_OF_JUNCTION-1)*8+2*8*Ls[b])*C*e+Cj*(2*Qs[b]-e)+2*C*Cj*(V1+V2+V3+V4+V5+V6+V7+V8))/(2*Cj*(8*NUMBER_OF_JUNCTION*C+Cj));
                dEdowns[b] = -e*(-(-(NUMBER_OF_JUNCTION-1)*8-2*8*Ls[b])*C*e+Cj*(2*Qs[b]+e)+2*C*Cj*(V1+V2+V3+V4+V5+V6+V7+V8))/(2*Cj*(8*NUMBER_OF_JUNCTION*C+Cj));
            }
            if(dEups[b] > 0){
                for(i = 0; i < NUMBER_OF_JUNCTION-Ls[b]; i++){
                    r = (double)rand()/RAND_MAX;
                    wt = (e*e*Rj/dEups[b])*log(1/r);
                    
                    if(wt < dt && wt < wt_min){
                        up = 1;
                        down = 0;
                        wt_min = wt;
                        w = 2;
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
                        w = 2;
                        B = b;
                    }
                }
            }
        }

        if((up == 1) && (w == 1)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
                    Q[b][a] += (Vd[b][a]-Vn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;

            L[B][A] += 1;

            if(L[B][A] == NUMBER_OF_JUNCTION){
                L[B][A] = 0;
                Q[B][A] -= e;
            }
            t += wt_min;
            up = 0;


        }else if((down == 1) && (w == 1)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
                    Q[b][a] += (Vd[b][a]-Vn[b][a])*wt_min/R;
                }
            }

            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;

            L[B][A] -= 1;
            if(L[B][A] == -NUMBER_OF_JUNCTION){
                L[B][A] = 0;
                Q[B][A] += e;
            }
            t += wt_min;
            down = 0;


        }else if((up == 1) && (w == 2)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
                    Q[b][a] += (Vd[b][a]-Vn[b][a])*wt_min/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;

            Ls[B] += 1;

            if(Ls[B] == NUMBER_OF_JUNCTION){
                Ls[B] = 0;
                Qs[B] -= e;
            }
            t += wt_min;
            up = 0;


        }else if((down == 1) && (w == 2)){
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
                    Q[b][a] += (Vd[b][a]-Vn[b][a])*wt_min/R;
                }
            }

            Qs[0] += (Vds[0]-Vns[0])*wt_min/R;
            
            Ls[B] -= 1;
            if(Ls[B] == -NUMBER_OF_JUNCTION){
                Ls[B] = 0;
                Qs[B] += e;
            }
            t += wt_min;
            down = 0;


        }else{
            for(b = 1; b < NUMBER_OF_SINDOUSI_TATE+1; b++){
                for(a = 1; a < NUMBER_OF_SINDOUSI_YOKO+1; a++){
                    Q[b][a] += (Vd[b][a]-Vn[b][a])*dt/R;
                }
            }
            Qs[0] += (Vds[0]-Vns[0])*dt/R;
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
