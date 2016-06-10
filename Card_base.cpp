#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

struct Node{
    int val;
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
public:
    DFS(int n, int m){
        size = n;
        num = m;
        err = pow(size);
    }
    
	vector<int>getResult(){
		return(result);
	}

    void explor(Node target, int depth, int ret, vector<Node> cList){
        if(depth == size){
            ret += target.val*pow(depth-1);
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
        }else if(depth==0){
			depth++;
			for(size_t i=0;i<cList.size();i++){
				explor(cList.at(i), depth, 0, cList);
			}
		}else if(depth < size){
			vector<Node> list(cList);
			ret += target.val*pow(depth-1);
			for(auto itr = list.begin(); itr != list.end(); ++itr) {
				if(itr->val==target.val){
					list.erase(itr);
					break;
				}
			}
			vector<Node> copy(list);
			depth++;
            while(!copy.empty()){
                Node next_t = copy.back();
                copy.pop_back();
                explor(next_t, depth, ret, list);
            }
        }
    }
};    

int main(){
    int n=0, m=0;
    char c;
    string str;
    cin >> n >> c >> m>> c>> str;
    vector<Node> cList;
    for(size_t i=0;i<str.length();i+=2){
        Node node;
        node.val = atoi(&str.at(i));
        cList.push_back(node);
    }
	if(cList.size() < n){
		cout<<"-"<<endl;
		return(0);
	}
    
    Node start;
    start.val=0;
    DFS *dfs = new DFS(n, m);
    dfs->explor(start, 0, 0, cList);
	int ret1 = dfs->getResult().back(), ret2=0;
	int err = abs(m-ret1);
	vector<int> result = dfs->getResult();
	while(!result.empty()){
		int val=result.back();
		result.pop_back();
		if(err==abs(val-m) && val!=ret1){
			ret2 = val;
			break;
		}
	}
	if(ret1==0 && n!=1){
		cout<<"-"<<endl;
		return(0);
	}
	if(ret2 == 0) cout<<ret1<<endl;
	else cout<<min(ret1,ret2)<<","<<max(ret1,ret2)<<endl;
    return(0);
}