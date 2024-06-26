#include <bits/stdc++.h>

using namespace std;

struct state {
    int ml, cl, pos, mr, cr;
    state *parent;
    int op;
    bool operator==(const state & rhs) const{
        return ((ml == rhs.ml) && (cl == rhs.cl) && (mr == rhs.mr) && (cr == rhs.cr) && (pos  == rhs.pos));
    }
};

state * nextState(state *Z, const int j) {
  state * S = new state();
  (*S) = (*Z);
  S->op  = j;
  switch (j)
  {
    case 0: {  S->pos  -= 1; 
               S->ml += 0;
               S->cl += 1;
               S->mr -= 0;
               S->cr -= 1;}
            break;
    case 1: {  S->pos  -= 1;
               S->ml += 0;
               S->cl += 2;
               S->mr -= 0;
               S->cr -= 2;}
            break;  
    case 2: {  S->pos  -= 1;
               S->ml += 1;
               S->cl += 0;
               S->mr -= 1;
               S->cr -= 0;}
            break;  
    case 3: {  S->pos  -= 1;
               S->ml += 2;
               S->cl += 0;
               S->mr -= 2;
               S->cr -= 0;}
            break;  
    case 4: {  S->pos  -= 1;
               S->ml += 1;
               S->cl += 1;
               S->mr -= 1;
               S->cr -= 1;}
            break;  
    case 5: {  S->pos  += 1;
               S->mr += 0;
               S->cr += 1;
               S->ml -= 0;
               S->cl -= 1;}
            break;  
    case 6: {  S->pos  += 1;
               S->mr += 0;
               S->cr += 2;
               S->ml -= 0;
               S->cl -= 2;}
            break;  
    case 7: {  S->pos  += 1;
               S->mr += 1;
               S->cr += 0;
               S->ml -= 1;
               S->cl -= 0;}
            break;              
    case 8: {  S->pos  += 1;
               S->mr += 2;
               S->cr += 0;
               S->ml -= 2;
               S->cl -= 0;}
            break;                          
    case 9: {  S->pos  += 1;
               S->mr += 1;
               S->cr += 1;
               S->ml -= 1;
               S->cl -= 1;}
            break;                                      
  }
  return S;
}

bool validState(state *S){
  if(( S->cl < 0) || ( S->cl > 3)) return false;
  if(( S->cr < 0) || ( S->cr > 3)) return false;
  if(( S->ml < 0) || ( S->ml > 3)) return false;
  if(( S->mr < 0) || ( S->mr > 3)) return false;
  if(( S->pos != 0) && ( S->pos != 1))  return false;  
  if( (( S->cl >  S->ml) && ( S->ml > 0)) || (( S->cr >  S->mr) && ( S->mr > 0)) ) return false; // cannible outnumber missionaries
  return true;
}

bool notFound(state *s, vector<state *> &vis){
    for(int i=0; i<vis.size(); i++){
        if((*s) == (*(vis[i]))) return false;
    }
    return true;
}

void addChildren(queue<state *> &q, state *s, vector<state *> &vis){
    state *temp;
    for(int i=0; i<10; i++){
        temp = nextState(s, i);
        if(validState(temp) && notFound(temp, vis)) {
            temp->parent = s;
            q.push(temp);
        } else delete temp;
    } 
}

void printOP(int n) {
  switch (n)
  {
    case 0:  cout << "0 Missionaries ,1 cannibals ,from right to left" << endl; break;
    case 1:  cout << "0 Missionaries ,2 cannibals ,from right to left" << endl; break;
    case 2:  cout << "1 Missionaries ,0 cannibals ,from right to left" << endl; break;
    case 3:  cout << "2 Missionaries ,0 cannibals ,from right to left" << endl; break;
    case 4:  cout << "1 Missionaries ,1 cannibals ,from right to left" << endl; break;
    case 5:  cout << "0 Missionaries ,1 cannibals ,from left to right" << endl; break;
    case 6:  cout << "0 Missionaries ,2 cannibals ,from left to right" << endl; break;
    case 7:  cout << "1 Missionaries ,0 cannibals ,from left to right" << endl; break;
    case 8:  cout << "2 Missionaries ,0 cannibals ,from left to right" << endl; break;
    case 9:  cout << "1 Missionaries ,1 cannibals ,from left to right" << endl; break;
  }
}

int main(){

    bool fl=false;
    state START = {3,3,0,0,0,NULL,-1};
    state GOAL = {0,0,1,3,3,NULL};

    queue<state *> q;
    vector<state *> vis;

    q.push(&START);

    state* temp;

    while(!q.empty()){
        temp = q.front();
        q.pop();
        if((*temp) == GOAL){
            fl=true;
            break;
        } else{
            addChildren(q, temp, vis);
            vis.push_back(temp);
        }
    }

    if(fl){
        cout << "Path found!\n";
        cout << "missionary, cannibal, boat posn\n";

        stack<int> ops;
        for(state* i=temp; i!=NULL; i = i->parent){
            ops.push(i->op);
        }

        while(!ops.empty()){
            printOP(ops.top());
            ops.pop();
        }
    } else{
        cout << "Path not found!\n";
    }

    return 0;
}

