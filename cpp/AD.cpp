#include <iostream>
#include <ctime>
#include "binmatrix.h"
using namespace std;

struct set{
    int len;
    int *elems;
    set(){
        len = 0;
        elems = NULL;
    }
    set& operator+=(const int right){
        for(int k = 0; k < len; k++){
            if(elems[k] == right) return *this;
        }
        elems = (int*) realloc(elems, sizeof(int));
        elems[len] = right;
        len++;
        return *this;
    }
    int operator[](int i){
        assert(len > i);
        return elems[i];
    }
    int getLast(){
        if(len == 0) return -1;
        return elems[len-1];
    }
    void print(){
        for(int i = 0; i < len; i++){
            cout << elems[i] << ' ';
        }
        cout << endl;
    }
    ~set(){
        if(elems != NULL) delete[] elems;
    }
};

int main(int argc, char* argv[]){
    srand(time(NULL));
    int s = 100;
    Matrix test = Matrix(1000, 35);
    test.fill();
    Matrix tmp = Matrix(0, 0);
    tmp = test;
    int t = tmp.getFirstComCol(s);
    //set Q = set();
    while(t != -1){
        //Q += t;
        cout << t << ' ';
        tmp.update(t);
        t = tmp.getFirstComCol(s);
    }
    //Q.print();
    cout << endl;
    return 0;
}