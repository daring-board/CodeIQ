#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int size = 10;

int countAria(char* world, int x, int y){
    int counter = 0;
    for(int i=x;i<x+size/2;i++){
        for(int j=y;j<y+size/2;j++){
            if(world[j+i*size] != 'G') continue;
            counter++;
        }
    }
    return(counter);
}

void searchAria(char* world){
    int num = 0, tmp = 0;
    int x = -1, y = -1;
    for(int i=0;i<size/2+1;i++){
        for(int j=0;j<size/2+1;j++){
            tmp = countAria(world, i, j);
            if(tmp > num){
                x = j;
                y = i;
                num = tmp;
            }
        }
    }
    cout<<"{\"x\":"<<x<<",\"y\":"<<y<<",\"g\":"<<num<<"}"<<endl;
}

int main(){
    string line;
    char *world = new char[size*size];
    int counter = 0;
    for(;getline(cin,line);){
        for(int i=0;i<line.size();i++){
            world[i+counter*size] = toupper(line[i]);
        }
        counter++;
    }
    searchAria(world);
}


wwGwwwwwGG
Gwwwwwwwww
wwwwwwwwww
Gwwwwwwwww
wwwwGwwGww
wGwwwwwwww
wwwGGwwwww
wwwwwwGwww
wwwwGGwwww
GwwwGGwGwG

wwwwwwwGww
wwGGwwwGww
wwwwGwwwww
wGwwwwwwww
wwwwwGGwGG
wwwwwwGwww
wwwwGGwGww
wwwwwGwGGw
wwGGwwGwGG
wwGwGwwGwG

{"x":3,"y":5,"g":8}

{"x"3,"y":5,"g":8}