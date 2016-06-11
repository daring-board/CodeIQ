#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

struct Card{
    int sval;
    int rval;
};

struct SubProblem{
	Card target;
	int depth;
	int result;
	vector<Card> list;
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
	vector<int> m_set;
    vector<int> result;
	stack<SubProblem> st;

	void function(Card target, int depth, int ret, vector<Card> cList, bool flag){
		int value = flag? target.sval: target.rval;
		vector<Card> list(cList);
		ret += value*pow(size-depth);
		for(auto itr = list.begin(); itr != list.end(); ++itr) {
			if(itr->sval==target.sval && itr->rval==target.rval){
				list.erase(itr);
				break;
			}
		}
		vector<Card> copy(list);
        while(!copy.empty()){
            Card next_t = copy.back();
            copy.pop_back();
			int tmp1 = ret + next_t.sval*pow(size-(depth+1));
			int tmp2 = ret + next_t.rval*pow(size-(depth+1));
			int err = abs(num-ret);
			SubProblem sp = {next_t, depth+1, ret, list};
			if(err==0) st.push(sp);
			else{
				if((err>=abs(num-tmp1))||(err>=abs(num-tmp2))){
					st.push(sp);
				}
			}
        }
	}

	bool evalute(int ret, Card target, bool flag){
		ret += ((flag)? target.sval: target.rval);
		if(ret < pow(size-1) && ret!=0) return(false);
        if(err > abs(num-ret)){
            err = abs(num-ret);
            result.clear();
            result.push_back(ret);
        }else if(err == abs(num-ret)){
            err = abs(num-ret);
            result.push_back(ret);
        }
		if(err == 0) return(true);
        return(false);
	}

public:
    DFS(int n, int m){
        size = n;
        num = m;
        err = pow(size);
		for(int i=size;i>0;i--){
			m_set.push_back(m/pow(i-1));
			m -= (m/pow(i-1))*pow(i-1);
		}
    }
    
	vector<int>getResult(){
		return(result);
	}

    void explor(Card t, int d, int r, vector<Card> cL){
		SubProblem sb = {t, d, r, cL};
		st.push(sb);
		while( !st.empty() ){
			sb = st.top();
			st.pop();
			if(sb.depth == size){
				if( evalute(sb.result, sb.target, true) ) break;
				if( evalute(sb.result, sb.target, false) ) break;
			}else if(sb.depth==0){
				for(size_t i=0;i<sb.list.size();i++){
					Card target = sb.list.at(i);
					SubProblem sp = {target, sb.depth+1, 0, sb.list};
					if(((m_set.at(0)+2>target.sval)&&(m_set.at(0)-2<target.sval))
						||((m_set.at(0)+2>target.rval)&&(m_set.at(0)-2<target.rval))){
						st.push(sp);
					}
				}
			}else if(sb.depth >= 1 && sb.depth < size-1){
				int d = sb.depth-1;
				int m_d = m_set.at(d);
				switch(m_d)
				{
				case 0:
					if(sb.target.sval==9||sb.target.sval==0||sb.target.sval==1){
						function(sb.target, sb.depth, sb.result, sb.list, true);
					}
					if(sb.target.rval==9||sb.target.rval==0||sb.target.rval==1){
						function(sb.target, sb.depth, sb.result, sb.list, false);
					}
					break;
				case 9:
					if(sb.target.sval==8||sb.target.sval==9||sb.target.sval==0){
						function(sb.target, sb.depth, sb.result, sb.list, true);
					}
					if(sb.target.rval==8||sb.target.rval==9||sb.target.rval==0){
						function(sb.target, sb.depth, sb.result, sb.list, false);
					}
					break;
				default:
					if(((m_d+2>sb.target.sval)&&(m_d-2<sb.target.sval))){
						function(sb.target, sb.depth, sb.result, sb.list, true);
					}
					if(((m_d+2>sb.target.rval)&&(m_d-2<sb.target.rval))){
						function(sb.target, sb.depth, sb.result, sb.list, false);
					}
					int err = pow(size);
					for(int i=m_d-2;i<m_d+2;i++){
						int tmp = 0;
						if(i >= 0){ 
							tmp = sb.result + i*pow(size-(sb.depth+1));
							if(err > abs(num-tmp)) err = abs(num-tmp);
						}
					}
					int tmp1 = sb.result + sb.target.sval*pow(size-(sb.depth+1));
					int tmp2 = sb.result + sb.target.rval*pow(size-(sb.depth+1));
					if(err>=abs(num-tmp1)){
						function(sb.target, sb.depth, sb.result, sb.list, true);
					}
					if(err>=abs(num-tmp2)){
						function(sb.target, sb.depth, sb.result, sb.list, false);
					}
					break;
				}
				
			}else if(sb.depth < size){
				function(sb.target, sb.depth, sb.result, sb.list, true);
				function(sb.target, sb.depth, sb.result, sb.list, false);
			}
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
	bool flag = false;
	for(size_t i=0;i<cList.size();i++){
		if(cList.at(i).sval != 0) break;
		if(cList.at(i).rval != 0) break;
		if(i == cList.size()-1) flag = true;
	}
    if(cList.size() < n || flag){
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

	Card start = {0, 0};
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
    return(0);
}