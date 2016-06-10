#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

struct Card{
    int sval;
    int rval;
};

int pow(int n){
    int x = 1;
    for(int i=0;i<n;i++){
        x *= 10;
    }
    return(x);
}

class DFS{
private:
    int size;
    int num;
    int err;
    vector<int> result;

	void function(Card target, int depth, int ret, vector<Card> cList, bool flag){
		int value = flag? target.sval: target.rval;
		vector<Card> list(cList);
		ret += value*pow(depth-1);
		for(auto itr = list.begin(); itr != list.end(); ++itr) {
			if(itr->sval==target.sval && itr->rval==target.rval){
				list.erase(itr);
				break;
			}
		}
		vector<Card> copy(list);
		depth++;
        while(!copy.empty()){
            Card next_t = copy.back();
            copy.pop_back();
            explor(next_t, depth, ret, list);
        }
	}

	void evalute(int ret, Card target, bool flag){
		ret += (flag)? target.sval*pow(size-1): target.rval*pow(size-1);
		if(ret < pow(size-1) && ret!=0) return;
        if(err > abs(num-ret)){
            err = abs(num-ret);
            result.clear();
            result.push_back(ret);
        }else if(err == abs(num-ret)){
            err = abs(num-ret);
            result.push_back(ret);
        }
        return;
	}

public:
    DFS(int n, int m){
        size = n;
        num = m;
        err = pow(size);
    }
    
	vector<int>getResult(){
		return(result);
	}

    void explor(Card target, int depth, int ret, vector<Card> cList){
        if(depth == size){
			evalute(ret, target, true);
			evalute(ret, target, false);
        }else if(depth==0){
			depth++;
			for(size_t i=0;i<cList.size();i++){
				explor(cList.at(i), depth, 0, cList);
			}
		}else if(depth < size){
			function(target, depth, ret, cList, true);
			function(target, depth, ret, cList, false);
        }
    }
};    

class OPT{
private:
	int size;
	vector<Card> list;

public:
	OPT(int n, vector<Card> clist){
		size = n;
		vector<Card> copy(clist);
		list = copy;
	}

	int minimize(){
		int ret=0;
		int index=list.size();
		int d=size;
		while(d > 0){
			int tmp = pow(size);
			for(int i=0;i<list.size();i++){
				int value = min(list.at(i).sval, list.at(i).rval);
				if(d==size && value==0)	value = max(list.at(i).sval, list.at(i).rval);
				if(tmp > value){
					tmp = value;
					index = i;
				}
			}
			list.erase(list.begin()+index);
			ret += tmp*pow(d-1);
			d--;
		}
		return(ret);
	}

	int maximize(){
		int ret=0;
		int index=list.size();
		int d=size;
		while(d > 0){
			int tmp = 0;
			for(int i=0;i<list.size();i++){
				int value = max(list.at(i).sval, list.at(i).rval);
				if(tmp < value){
					tmp = value;
					index = i;
				}
			}

			list.erase(list.begin()+index);
			ret += tmp*pow(d-1);
			d--;
		}
		return(ret);
	}
};


int main(){
	clock_t time_s = clock();    // スタート時間
    int n=0, m=0;
    char c;
    string str;
    cin >> n >> c >> m>> c>> str;
    vector<Card> cList;
    for(size_t i=0;i<str.length();i+=3){
        Card card;
        card.sval = atoi(&str.at(i))/10;
        card.rval = atoi(&str.at(i))%10;
        cList.push_back(card);
    }
    if(cList.size() < n){
        cout<<"-"<<endl;
        return(0);
    }
	if(m < pow(n-1) ){
		OPT *mini = new OPT(n, cList);
		cout<<mini->minimize()<<endl;
        return(0);
    }
	if(m > pow(n) ){
		OPT *maxi = new OPT(n, cList);
		cout<<maxi->maximize()<<endl;
        return(0);
    }

	Card start;
	start.sval = 0;
	start.rval = 0;
	DFS *dfs = new DFS(n, m);
	dfs->explor(start, 0, 0, cList);
	vector<int> result = dfs->getResult();
	int ret1 = result.back(), ret2=0;
	int err = abs(m-ret1);
	if(ret1==0 && n!=1){
		cout<<"-"<<endl;
		return(0);
	}
	if(err==0){
		cout<<ret1<<endl;
		return(0);
	}

	while(!result.empty()){
		int val=result.back();
		result.pop_back();
		if(err==abs(val-m) && val!=ret1){
			ret2 = val;
			break;
		}
	}
	if(ret2 == 0) cout<<ret1<<endl;
	else cout<<min(ret1,ret2)<<","<<max(ret1,ret2)<<endl;

	clock_t time_e = clock();     // 終了時間
    cout << "duration = " << (double)(time_e - time_s) / CLOCKS_PER_SEC << "sec.\n";

    return(0);
}