#include <iostream>
#include <ctime>
#include <vector>
#include <unistd.h>
#include "binmatrix.h"
using namespace std;

int main(int argc, char* argv[]){
    srand(time(NULL));
    int s = 100;
    Matrix test = Matrix(1000, 35);
    test.fill();
    //test.print();
    //cout << "***" << endl;
    Matrix tmp = Matrix(0, 0);
    Matrix p = Matrix(0, 0);
    tmp = test;
    int t = tmp.getFirstComCol(s);
    if(t == -1){
        cout << "Нет s-совместимых столбцов!" << endl;
        return 1;
    }
    int l = tmp.getLastComCol(s);
    vector<int> L(1);
    L[0] = l;
    vector<int> Q(0);
    //vector<vector<int>> max_set(0);
    int count = 0;
    int start = clock();
    while(t != -1){
        Q.push_back(t);
        tmp.update(t);
        t = tmp.getFirstComCol(s);
        /*for(int i = 0; i < Q.size(); i++){
            cout << Q[i] << ' ';
        }
        cout << endl;*/
        count++;
    }
    while(Q != L){
        tmp = test;
        tmp.update(Q);
        t = tmp.getFirstComCol(Q[Q.size()-1], s);
        if(t != -1){
            Q.push_back(t);
        }else{
            //max_set.push_back(Q);
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
                        t = test.getFirstComCol(Q[0], s);
                        Q.clear();
                        Q.push_back(t);
                    }else{
                        int pb = Q[Q.size()-2];
                        int lcom = Q[Q.size()-1];
                        Q.pop_back();
                        Q.pop_back();
                        Q.push_back(lcom);
                    }
                }
            }
        }
        /*for(int i = 0; i < Q.size(); i++){
            cout << Q[i] << ' ';
        }
        cout << endl;*/
        count++;
    }
    //cout << "***" << endl;
    int end = clock();
    cout << "Кол-во наборов: " << count << endl;
    cout << "Время в мс: " << (end - start) * 1000 / CLOCKS_PER_SEC << endl;
    return 0;
}