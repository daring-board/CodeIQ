#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Node{
private:
    int index;
    int parent;
    vector<int> children;
    
public:
    Node(){
        parent = -1;
        children.clear();
    }
    
    void setId(int i){
        index = i;
    }
    
    int getId(){
        return(index);
    }
    
    void setParentId(int i){
        parent = i;
    }
    
    void addChild(int i){
        children.push_back(i);
    }
	
	vector<int> getChildren(){
		return(children);
	}
};

int depthFirstSearch(vector<Node*> tree, int num){
	bool* explored = new bool[tree.size()+1];
	stack<Node*> stack;

	//initialzation
	stack.push( tree.at(0) );
	for(unsigned int i=0;i<tree.size();i++){
		int id = tree.at(i)->getId();
		explored[id] = false;
	}
	
	int counter = 1;
	while( !stack.empty() ){
		Node* targetNode = stack.top();
		stack.pop();
		int id = targetNode->getId();
		if( !explored[id] ){
			//’TõNode‚Ì”»’è Start
			if(counter == num){
				return (id+1);
			}
			//End
			counter++;
			explored[id] = true;
			vector<int> children = targetNode->getChildren();
			if(children.size() == 0) continue;
			for(int i=children.size()-1;i>=0; i--){
				stack.push( tree.at(children.at(i)) );
			}
		}
	}
	return(-1);
}

int main(){
    int n=0, m=0;
    char c;
    string str;
    cin >> m >> n;

    int parentId = 0;
	vector<Node*> tree;

	for(int i = 0;i < m;i++){
		Node *node = new Node();
		node->setId(i);
		if(i >= 1){
			if(i%2 == 0) parentId = i/2-1;
			else parentId = (i-1)/2;
			if(parentId < m/2){
				tree.at(parentId)->addChild(i);
			}
			node->setParentId(parentId);
		}
		tree.push_back(node);
	}
	
    cout<<depthFirstSearch(tree, n);
    return(0);
}
    
    