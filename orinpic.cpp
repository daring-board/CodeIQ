#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int main(){
    int num = 0;
    cin>>num;
    
    long long *sol = new long long[num+1];
    sol[0] = 0, sol[1] = 0, sol[2] = 1;
    for(int i=3;i<=num;i++){
        sol[i] = 1 + 2*sol[i-1];
        if(i!=3) {
            int sum = 0;
            for(int j=3;j<i;j++){
                sum += sol[j];
            }
            sol[i] += sol[i-1]*sum;
        }
    }
    cout<<sol[num]<<endl;
}
