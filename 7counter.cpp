#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <math.h>

using namespace std;

int getDigOne(int num){
    return( (num < 7)? 0: 1);
}

int getDigNum(int num, int d){
    return(num*d*pow(10, d-1));
}

int main(){
    string line;
    vector<int> nums;
    for(;getline(cin,line);){
        nums.push_back(atoi(line.c_str()));
    }
    
    for(size_t i=0;i<nums.size();i++){
        int result = 0;
        int num = nums.at(i);
        int d = (int)log10(num)+1;
        for(int i=d-1;i>=0;i--){
            int n = num/pow(10, i);
            if( i != 0){
                if( n == 7){
                    result += getDigNum(n, i)+(num-n*pow(10, i))+1;
                }else if( n > 7){
                    result += getDigNum(n, i)+pow(10, i);
                }else{
                    result += getDigNum(n, i);
                }
            }else{
                result += getDigOne(n);
            }
            num -= n*pow(10, i);
        }
        cout<<result<<endl;
    }
    
    return(0);
}