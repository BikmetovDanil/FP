#include "binmatrix.h"
#include <unistd.h>

struct Node{
    vector<int> childs;
    vector<int> cols;
    Node* parent;
    vector<Node*> nodes;
    Node(){
        parent = NULL;
        cols.reserve(0);
    }
    Node(vector<int> q){
        cols = q;
    }
    Node* add(int q){
        vector<int> Q = cols;
        Q.push_back(q);
        Node *node = new Node(Q);
        node->parent = this;
        nodes.push_back(node);
        return node;
    }
    Node& getParent(){
        return *parent;
    }
    void del(){
        if(nodes.size() == 0) delete this;
        for(int i = 0; i < nodes.size(); i++){
            nodes[i]->del();
        }
    }
    void print(){
        for(int i = 0; i < nodes.size(); i++){
            nodes[i]->print();
        }
        for(int i = 0; i < cols.size(); i++){
            cout << cols[i] << ' ';
        }
        cout << endl;
    }
};

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
    Node tree;
    int count = 0, max_count = 0;
    void DepthFirst(Node* N, database T, column B){
        B = CreateBitvector(N, B, T);
        cols C = GenerateCandidates(N);
        cols E = Count(N, T, B, C);
        N->childs = E;
        // T = Project(T, E, B);
        for(int i = 0; i < E.size(); i++){
            count++;
            DepthFirst(N->add(E[i]), T, B);
        }
        if(E.size() == 0){
            if(isMax(N, B)) max_count++;
        }
    }
    cols GenerateCandidates(Node* N){
        cols items;
        if(N->cols.size() == 0){
            for(int j = 0; j < n; j++){
                items.push_back(j);
            }
        }else{
            int size = N->parent->childs.size();
            int from = N->cols[N->cols.size() - 1];
            for(int i = 0; i < size; i++){
                if(N->parent->childs[i] > from)
                    items.push_back(N->parent->childs[i]);
            }
        }
        return items;
    }
    cols Count(Node* N, database T, column B, cols C){
        cols items;
        for(int j = 0; j < C.size(); j++){
            if((B & matrix[C[j]]).count() >= s)
                items.push_back(C[j]);
        }
        return items;
    }
    column CreateBitvector(Node* N, column B, database T){
        if(N->cols.size() == 0) return B;
        return B & matrix[N->cols[N->cols.size() - 1]];
    }
    database Project(database T, cols E, column B){
        database _T;
        for(int j = 0; j < T.size(); j++){
            if((B & T[j]).count() >= s)
                _T.push_back(T[j]);
        }
        return _T;
    }
    bool isMax(Node* N, column B){
        /*B.reset();
        B.flip();
        for(int k = 0; k < N->cols.size(); k++){
            B = B & matrix[N->cols[k]];
        }*/
        int i = 0;
        for(int j = 0; j < n; j++){
            if(j != N->cols[i]){
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
    // Возвращает время в микросекундах
    int run(){
        int start = clock();
        count = 0;
        max_count = 0;
        cols N;
        database T;
        // for(int j = 0; j < n; j++) T.push_back(matrix[j]);
        column B;
        B.reset();
        B.flip();
        DepthFirst(&tree, T, B);
        int end = clock();
        // cout << "На самом деле частых наборов: " << counter << endl;
        return (end - start) * 1000000 / CLOCKS_PER_SEC;
    }
    void printAllCols(){
        tree.print();
    }
    int getAllColsNumber(){
        return count;
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
        return max_count;
    }
    ~DepthProject(){
        tree.del();
    }
};