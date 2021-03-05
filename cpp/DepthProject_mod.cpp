#include "binmatrix.h"
#include <unistd.h>

/*
    column здесь = bitvector в оригинале
*/

class DepthProject{
private:
    Matrix matrix;
    typedef vector<int> cols;
    typedef vector<int> rows;
    typedef vector<column> database;
    vector<cols> all_cols;
    vector<cols> max_cols;
    int s;
    void DepthFirst(cols N, database T, column B){
        B = CreateBitvector(N, B);
        cols E = GenerateCandidates(N, B);
        // cols E = Count(N, T, B, C);
        for(int i = 0; i < E.size(); i++){
            cols _N = N;
            _N.push_back(E[i]);
            all_cols.push_back(_N);
            DepthFirst(_N, T, B);
        }
        if(E.size() == 0){
            if(isMax(N, B)) max_cols.push_back(N);
        }
    }
    // Первая реализация
    /*cols GenerateCandidates(cols N){
        if(N.size() == 0){
            cols items(m);
            for(int j = 0; j < m; j++){
                items.push_back(j);
            }
            return items;
        }else{
            cols items;
            int i = 0;
            for(int j = 0; j < n; j++){
                if(j != N[i]){
                    if((matrix[N[i]] & matrix[j]) == matrix[N[i]])
                        items.push_back(j);
                }else i++;
            }
            return items;
        }
    }*/
    // Вторая реализация
    // Маска B нужна для того, чтобы отсечь нечастые расширения
    cols GenerateCandidates(cols N, column B){
        if(N.size() == 0){
            cols items;
            for(int j = 0; j < n; j++){
                if(matrix[j].count() >= s)
                    items.push_back(j);
            }
            return items;
        }else{
            cols items;
            for(int j = N[N.size()-1] + 1; j < n; j++){
                if((B & matrix[j]).count() >= s)
                    items.push_back(j);
            }
            return items;
        }
    }
    cols Count(cols N, database T, column B, cols C){
        cols items;
        for(int j = 0; j < C.size(); j++){
            if((B & matrix[j]).count() >= s)
                items.push_back(j);
        }
        return items;
    }
    column CreateBitvector(cols N, column B){
        if(N.size() == 0) return B;
        return B & matrix[N[N.size() - 1]];
    }
    bool isMax(cols N, column B){
        B.reset();
        B.flip();
        for(int k = 0; k < N.size(); k++){
            B = B & matrix[N[k]];
        }
        int i = 0;
        for(int j = 0; j < n; j++){
            if(j != N[i]){
                if ((B & matrix[j]).count() >= s) return false;
            }else i++;
        }
        return true;
    }
public:
    DepthProject(Matrix& matrix, int s){
        this->matrix = matrix;
        this->s = s;
    }
    int run(){
        int start = clock();
        cols N;
        database T;
        for(int j = 0; j < n; j++) T.push_back(matrix[j]);
        column B;
        B.reset();
        B.flip();
        DepthFirst(N, T, B);
        int end = clock();
        return (end - start) * 1000 / CLOCKS_PER_SEC;
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