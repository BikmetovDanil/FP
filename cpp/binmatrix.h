#pragma once

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
const int m = 6000, n = 20;
using column = std::bitset<m>;

class Matrix{
private:
    column matrix[n];
public:
    column mask;
    Matrix(){
        mask.reset();
        mask.flip();
    }
    void fill(){
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(rand() % 2) matrix[j].set(i);
            }
        }
    }
    column operator[](int n) const{
        return matrix[n];
    }
    void print() const{
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                cout << (int) matrix[j][i] << ' ';
            }
            cout << endl;
        }
    }
    int getFirstComCol(int s) const{
        for(int j = 0; j < n; j++){
            if((mask & matrix[j]).count() >= s) return j;
        }
        return -1;
    }
    int getFirstComCol(int col, int s) const{
        for(int j = col+1; j < n; j++){
            if((mask & matrix[j]).count() >= s) return j;
        }
        return -1;
    }
    int getLastComCol(int s) const{
        for(int j = n-1; j >= 0; j--){
            if((mask & matrix[j]).count() >= s) return j;
        }
        return -1;
    }
    void update(int col){
        mask = mask & matrix[col];
        /*for(int i = 0; i < m; i++){
            if(matrix[col][i] == 0){
                for(int j = 0; j < n; j++){
                    matrix[j].reset(i);
                }
            }else matrix[col].reset(i);
        }*/
    }
    void update(vector<int> cols){
        for(int k = 0; k < cols.size(); k++){
            this->update(cols[k]);
        }
    }
    void clear(){
        for(int j = 0; j < n; j++){
            matrix[j].reset();
        }
    }
    bool empty() const{
        for(int j = 0; j < n; j++){
            if(matrix[j].any()) return false;
        }
        return true;
    }
    int getRowsNum() const{
        return m;
    }
    int getColumnsNum() const{
        return n;
    }
};