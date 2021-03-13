#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;
const int m = 40, n = 44;
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
    void toFile(const string path) const{
        std::ofstream out;
        out.open(path);
        if(out.is_open()){
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    out << (int) matrix[j][i] << ' ';
                }
                out << endl;
            }
        }else{
            cout << "Can't open file" << endl;
        }
    }
    void toFileForFP(const string path) const{
        std::ofstream out;
        out.open(path);
        if(out.is_open()){
            out << n << endl;
            out << m << endl;
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    out << (int) matrix[j][i];
                    if(j != n - 1) out << ',';
                }
                out << endl;
            }
        }else{
            cout << "Can't open file" << endl;
        }
    }
    void readFrom(const string path){
        string line;
        std::ifstream in(path);
        if (in.is_open()){
            while (getline(in, line)){
                cout << line << endl;
            }
        }
        in.close();
    }
    void readFromFile(const char* fname){
        FILE * matrix_;
        char c;
        int k;
        matrix_ = fopen(fname, "r");
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                fscanf(matrix_, "%d", &k);
                if(k) matrix[j].set(i);
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