#include "binmatrix.h"

class AD{
private:
    Matrix matrix;
    column mask;
    typedef vector<int> cols;
    int s;
public:
    vector<cols> all_cols;
    vector<cols> max_cols;
    AD(Matrix& matrix, int s){
        this->matrix = matrix;
        this->s = s;
    }
    // Возвращает время работы в миллисекундах
    int run(){
        Matrix tmp;
        Matrix p;
        tmp = matrix;
        int t = tmp.getFirstComCol(s);
        if(t == -1){
            cout << "Нет s-совместимых столбцов!" << endl;
            return -1;
        }
        int l = tmp.getLastComCol(s);
        cols L(1);
        L[0] = l;
        cols Q(0);
        int start = clock();
        while(t != -1){
            Q.push_back(t);
            tmp.update(t);
            t = tmp.getFirstComCol(t, s);
            all_cols.push_back(Q);
        }
        while(Q != L){
            tmp = matrix;
            tmp.update(Q);
            t = tmp.getFirstComCol(Q[Q.size()-1], s);
            if(t != -1){
                Q.push_back(t);
            }else{
                if(isMax(Q)) max_cols.push_back(Q);
                if(Q.size() == 1){
                    t = matrix.getFirstComCol(Q[0], s);
                    if(t == -1) break;
                    Q[0] = t;
                }else if(Q.size() > 1){
                    int pb = Q[Q.size()-1];
                    Q.pop_back();
                    p = matrix;
                    p.update(Q);
                    int lcom = p.getFirstComCol(pb, s);
                    Q.push_back(pb);
                    if(lcom != -1){
                        Q.pop_back();
                        Q.push_back(lcom);
                    }else{
                        if(Q.size() == 2){
                            t = matrix.getFirstComCol(Q[0], s);
                            Q.clear();
                            Q.push_back(t);
                        }else{
                            int pb = Q[Q.size()-2];
                            Q.pop_back();
                            Q.pop_back();
                            p = matrix;
                            p.update(Q);
                            t = p.getFirstComCol(pb, s);
                            Q.push_back(t);
                        }
                    }
                }
            }
            all_cols.push_back(Q);
        }
        if(isMax(Q)) max_cols.push_back(Q);
        int end = clock();
        return (end - start) * 1000 / CLOCKS_PER_SEC;
    }
    bool isMax(cols col){
        mask.reset();
        mask.flip();
        for(int k = 0; k < col.size(); k++){
            mask = mask & matrix[col[k]];
        }
        int i = 0;
        for(int j = 0; j < n; j++){
            if(j != col[i]){
                if ((mask & matrix[j]).count() >= s) return false;
            }else i++;
        }
        return true;
    }
    void printAllCols(){
        if(all_cols.empty()) return;
        for(int i = 0; i < all_cols.size(); i++){
            for(int j = 0; j < all_cols[i].size(); j++){
                cout << all_cols[i][j] << ' ';
            }
            cout << endl;
        }
    }
    int getAllColsNumber(){
        return all_cols.size();
    }
    void printMaxCols(){
        if(max_cols.empty()) return;
        for(int i = 0; i < max_cols.size(); i++){
            for(int j = 0; j < max_cols[i].size(); j++){
                cout << max_cols[i][j] << ' ';
            }
            cout << endl;
        }
    }
    int getMaxColsNumber(){
        return max_cols.size();
    }
};