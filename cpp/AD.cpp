#include <iostream>
#include <ctime>
#include <vector>
#include <unistd.h>
#include "binmatrix.h"
using namespace std;

int main(int argc, char* argv[]){
    srand(time(NULL));
    int s = 3;
    Matrix test = Matrix(6, 6);
    test.fill();
    test.print();
    cout << "***" << endl;
    Matrix tmp = Matrix(0, 0);
    Matrix p = Matrix(0, 0);
    tmp = test;
    int t = tmp.getFirstComCol(s); // t != -1 (!!!)
    int l = tmp.getLastComCol(s);
    vector<int> L(1);
    L[0] = l;
    vector<int> Q(0);
    vector<vector<int>> max_set(0);
    while(t != -1){
        Q.push_back(t);
        tmp.update(t);
        t = tmp.getFirstComCol(s);
        for(int i = 0; i < Q.size(); i++){
            cout << Q[i] << ' ';
        }
        cout << endl;
    }
    while(Q != L){
        tmp = test;
        tmp.update(Q);
        t = tmp.getFirstComCol(Q[Q.size()-1], s);
        if(t != -1){
            Q.push_back(t);
        }else{
            max_set.push_back(Q);
            if(Q.size() == 1){
                t = test.getFirstComCol(Q[0], s);
                if(t == -1) break;
                Q[0] = t;
            }else if(Q.size() > 1){
                int pb = Q[Q.size()-1];
                Q.pop_back();
                p = test;
                p.update(Q);
                int lcom = p.getFirstComCol(pb, s);
                Q.push_back(pb);
                if(lcom != -1){
                    Q.pop_back();
                    Q.push_back(lcom);
                }else{
                    if(Q.size() == 2){
                        //cout << "b" << endl;
                        //t = test.getFirstComCol(pb, s);
                        //if(t == -1) break;
                        t = test.getFirstComCol(Q[0], s);
                        Q.clear();
                        Q.push_back(t);
                    }else{
                        //cout << "c" << endl;
                        int pb = Q[Q.size()-2];
                        int lcom = Q[Q.size()-1];
                        Q.pop_back();
                        Q.pop_back();
                        //p = test;
                        //p.update(Q);
                        //int lcom = p.getFirstComCol(pb, s);
                        Q.push_back(lcom);
                    }
                }
            }
        }
        for(int i = 0; i < Q.size(); i++){
            cout << Q[i] << ' ';
        }
        cout << endl;
    }
    cout << "***" << endl;
    /*for(int i = 0; i < max_set.size(); i++){
        for(int j = 0; j < max_set[0].size(); j++){
            cout << max_set[i][j] << ' ';
        }
        cout << endl;
    }*/
    return 0;
}