#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

int N, M, d_min = 10000;
struct position{
    int i;
    int j;
};
enum direction{ U=3, D=0, L=2, R=1};
struct node{
	position pos;
	int counter;
	int estimate;
	direction d;
};
struct dsc{
	bool operator() (node x, node y) const{
		return(x.counter+x.estimate > y.counter+y.estimate);
	}
};
int equals(position a, position b);
void change(int *board, position pos, int val);
int check(int *board, position pos, int counter);
position move(position pos, direction d);
void bfs(int *board, position pos, int counter, direction d);
void explor(int *board);

int main(void){
    cin>>M>>N;
    int *board = new int[N*M];
    memset(board, 0, sizeof(board));
    char c;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cin>>c;
            int v = 3;
            if( c == '.') v = 0;
            board[j+i*N] = v;
        }
    }
    board[(N-1)+(M-1)*N] = 2;
    explor(board);
    cout<<d_min<<endl;
}

int equals(position a, position b){
    if((a.i == b.i)&&(a.j == b.j)){
        return(1);
    }
    return(0);
}

void change(int *board, position pos, int val){
    if(board[pos.j+pos.i*N] <= 1){
        board[pos.j+pos.i*N] = val;
    }
}

position move(position pos, direction d){
    position tmp;
    switch(d){
        case U:
            tmp.i = pos.i-1;
			tmp.j = pos.j;
            break;
        case D:
            tmp.i = pos.i+1;
			tmp.j = pos.j;
			break;
        case L:
			tmp.i = pos.i;
			tmp.j = pos.j-1;
			break;
        case R:
			tmp.i = pos.i;
			tmp.j = pos.j+1;
            break;
    }
    return(tmp);
}

int check(int *board, position pos, int counter){
    if(pos.i < 0) return(0);
    if(pos.j < 0) return(0);
    if(pos.i >= M) return(0);
    if(pos.j >= N) return(0);
    if(counter >= d_min) return(0);
    if(board[pos.j+pos.i*N] == 2) return(1);
    if(board[pos.j+pos.i*N] != 0) return(0);
    return(1);
}

void bfs(int *board, position pos, int counter, direction d){
	int dir = 4;
	priority_queue<node, vector<node>, dsc> que;
	node root = {pos, counter, 1, d};
	que.push(root);
	while(!que.empty()){
		node n = que.top();
		que.pop();
		if(board[n.pos.j+n.pos.i*N] == 2 && n.counter < d_min){
			d_min = n.counter;
			for(int i=0;i<M;i++){
				for(int j=0;j<N;j++){
					cout<<board[j+i*N]<<" ";
				}
				cout<<endl;
			}
			continue;
		}
		change(board, n.pos, 1);
		for(int i=0;i<dir;i++){
			node tmp = {
				move(n.pos, (direction)i),
				((direction)i==n.d)? n.counter: n.counter+1,
				1, (direction)i};
			if(check(board, tmp.pos, tmp.counter)){
				que.push(tmp);
			}
		}
	}
}

void explor(int *board){
    position start = {0, 0};
    position goal = {M-1, N-1};
    if(equals(start, goal)){
        d_min = 0;
        return;
    }    
	bfs(board, start, -1, U);
}
