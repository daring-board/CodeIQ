#include <iostream>
#define CNUM 6

using namespace std;

int calucrate(int N){
    int coin[CNUM] = {1, 5, 10, 50, 100, 500};
    int *M = new int[(N+1)*CNUM];
    if(N == 0) return(0);
    for(int i=0;i<CNUM;i++){
        M[i+0*CNUM] = 1;
        M[i+1*CNUM] = 1;
    }
    for(int i=1;i<=N;i++){
        M[0+i*CNUM] = 1;
        M[1+i*CNUM] = i/coin[1]+1;
        if(i < 5){
            for(int j=2;j<CNUM;j++){
                M[j+i*CNUM] = 1;
            }
        }
    }
    
    for(int k=2;k<CNUM;k++){
        for(int i=5;i<=N;i++){
            int tmp = 0;
            if(i>=coin[k]){
                M[k+i*CNUM] = M[(k-1)+i*CNUM] + M[k+(i-coin[k])*CNUM];
            }else{
                M[k+i*CNUM] = M[(k-1)+i*CNUM];
            }
        }
    }
    
    return(M[CNUM*(N+1)-1]);
}

int main(){
    int num=0;
    cin>>num;
    cout<<calucrate(num)<<endl;
    return(0);
}