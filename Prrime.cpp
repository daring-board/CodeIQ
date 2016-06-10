#include <iostream>
using namespace std;

int main(){
    int size = 10;
    int n_in[size], n_max=0;
    for(int i=0;i<size;i++){
        cin>> n_in[i];
    }
    n_max = n_in[size-1];
    int prime[n_max];
    int count=0;
    
    prime[count++] = 2;
    prime[count++] = 3;
    
    for(int num=5; num<=n_max; num+=2){
        bool flag=false;
        for(int i=0; prime[i]*prime[i]<=num;i++){
            if(num%prime[i] == 0){
                flag = true;
                break;
            }
        }
        if(!flag) prime[count++] = num;
    }
    
    for(int i=0;i<size;i++){
        for(int j=0;j<=count;j++){
            if(n_in[i] <= prime[j] || j==count){
                cout<<j<<endl;
                break;
            }
        }
    }
    return(0);
}