#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

using namespace std;

struct Count7{
    int num;
    int counter;
};

int main(){
    string line;
    vector<int> nums;
    for(;getline(cin,line);){
        nums.push_back(atoi(line.c_str()));
    }
    
    int n_max = 0;
    for(size_t l=0;l<nums.size();l++){
        if(n_max < nums.at(l) ){
            n_max = nums.at(l);
        }
    }
    
    vector<int> list;
    int counter=0;
    for(int i=1;i<=n_max;i++){
        string str = to_string(i);
        for(unsigned int l=0;l<str.length();l++){
            if(str[l] == '7'){
                counter++;
            }
        }
        list.push_back(counter);
    }
    
    for(size_t i=0;i<nums.size();i++){
        cout<<list.at(nums.at(i)-1)<<endl;
    }
    return(0);
}