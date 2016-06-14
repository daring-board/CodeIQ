#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
using namespace std;

int main(){
    string line;
    vector<int> nums;
    int n, m;
    char c;
    cin>>n>>c>>m;
    getline(cin,line);
    for(;getline(cin,line);){
        nums.push_back(atoi(line.c_str()));
    }
    
	int t_n=0, x=0;
	int m_sum = 0;
    for(size_t i=0;i<nums.size();i++){
        m_sum += nums.at(i);
    }
    x = m_sum/n;

	while(true){
	    t_n = 0;
	    for(size_t i=0;i<nums.size();i++){
	        t_n += (int)(nums.at(i)/x)+1;
	    }
	    if(t_n > n){
	        x += x;
	    }else if(t_n < n){
	        x -= x/4;
	    }else break;
	}

    for(size_t i=0;i<nums.size();i++){
        cout<<(int)(nums.at(i)/x)+1<<endl;
    }
	
}