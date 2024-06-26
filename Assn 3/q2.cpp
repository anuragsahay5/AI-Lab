#include<bits/stdc++.h>
using namespace std;

void solveDisc(int n,char src,char dest,char aux){
    
    if(n==0) return; // no disc left, return

    solveDisc(n-1,src,aux,dest); // move the top n-1 disc from src to aux using dest pole
    cout<<"Move Disc "<<n<< " from "<<src<<" to "<<dest<<"\n"; // move the last disc from src to dest
    solveDisc(n-1,aux,dest,src); // move the remaining n-1 disc from aux to dest using src
}

int main(){
    solveDisc(3,'A','B','C');
    return 0;
}