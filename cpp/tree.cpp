#include <iostream>
#include <vector>
using namespace std;

struct Node{
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
    void add(vector<int> q){
        Node node = Node(q);
        node.parent = this;
        nodes.push_back(&node);
    }
    Node& getParent(){
        return *parent;
    }
};

int main(int argc, char* argv[]){
    vector<int> Q1(3, (int) 1);
    vector<int> Q2 = Q1;
    Q2.push_back(2);
    vector<int> Q3 = Q1;
    Q3.push_back(3);
    
    Node tree = Node();
    tree.add(Q1);
    tree.add(Q2);
    tree.nodes[1]->add(Q3);

    return 0;
}