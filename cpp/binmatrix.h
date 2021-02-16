#pragma once

#include <iostream>
#include <ctime>
#include <cassert>
using namespace std;

class Matrix{
private:
    int m, n;
    char **matrix;
public:
    Matrix(int m, int n){
        this->m = m;
        this->n = n;
        matrix = new char*[m];
        for(int i = 0; i < m; i++){
            matrix[i] = new char[n];
        }
    }
    Matrix& operator=(const Matrix& b){
        for(int i = 0; i < m; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
        m = b.m;
        n = b.n;
        matrix = new char*[m];
        for(int i = 0; i < m; i++){
            matrix[i] = new char[n];
            for(int j = 0; j < n; j++){
                matrix[i][j] = b[i][j];
            }
        }
        return *this;
    }
    char* operator[](int n) const{
        return matrix[n];
    }
    void fill(){
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                matrix[i][j] = rand() % 2;
            }
        }
    }
    void print() const{
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                cout << (int) matrix[i][j] << ' ';
            }
            cout << endl;
        }
    }
    int getFirstComCol(int s) const{
        for(int j = 0; j < n; j++){
            int c = 0;
            for(int i = 0; i < m; i++){
                if(matrix[i][j]) c++;
            }
            if(c >= s) return j;
        }
        return -1;
    }
    void update(int col){
        for(int i = 0; i < m; i++){
            if(matrix[i][col] == 0){
                for(int j = 0; j < n; j++){
                    matrix[i][j] = 0;
                }
            }else matrix[i][col] = 0;
        }
    }
    ~Matrix(){
        for(int i = 0; i < m; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
};