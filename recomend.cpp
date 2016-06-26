#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
using namespace std;

int nUSER;
int nITEM;

float sim(int* evl, int a, int b){
    float asq=0, bsq=0;
    float sum_ab=0;
    for(int u=0;u<nUSER;u++){
        asq += evl[u+a*nUSER]*evl[u+a*nUSER];
        bsq += evl[u+b*nUSER]*evl[u+b*nUSER];
        sum_ab += evl[u+a*nUSER]*evl[u+b*nUSER];
    }
    asq = sqrt(asq);
    bsq = sqrt(bsq);
    return(sum_ab/(asq*bsq));
}

int main(){
    int n=0;
    cin >> nUSER >> nITEM >> n;
    int evl[nUSER*nITEM];
    for(int i=0;i<nUSER;i++){
        for(int j=0;j<nITEM;j++){
            evl[i+j*nUSER] = 0;
        }
    }
    for(int i=0;i<n;i++){
        int nu=0, ni=0, v=0;
        cin>>nu>>ni>>v;
        evl[(nu-1)+(ni-1)*nUSER] = v;
    }
    int m = 0, num = 0;
    cin>> m;
    vector<int> rlist;
    for(int i=0;i<m;i++){
        cin>>num;
        rlist.push_back(num);
    }
    
    float sMat[nITEM*nITEM];
    for(int i=0;i<nITEM;i++){
        for(int j=i+1;j<nITEM;j++){
            sMat[i+j*nITEM] = sim(evl, i, j);
            sMat[j+i*nITEM] = sMat[i+j*nITEM];
        }
        sMat[i+i*nITEM] = 0;
    }
    for(size_t i=0;i<rlist.size();i++){
        int counter = 0;
        cout<<rlist.at(i)<<" ";
        int k = rlist.at(i)-1;
        float max_t=0, bound=1;
        int rank_i[3] = {-1,-1,-1};
        while(counter<3){
            max_t=0;
            for(int j=0;j<nITEM;j++){
                if(max_t < sMat[k+j*nITEM] && sMat[k+j*nITEM] <= bound){
                    if(rank_i[0]!=j&&rank_i[1]!=j&&rank_i[2]!=j){
                        rank_i[counter] = j;
                        max_t = sMat[k+j*nITEM];
                    }
                }
            }
            bound = sMat[k+rank_i[counter]*nITEM];
            cout<<rank_i[counter]+1;
            if(counter<2) cout<<" ";
            counter++;
        }
        cout<<endl;
    }
    return(0);
}