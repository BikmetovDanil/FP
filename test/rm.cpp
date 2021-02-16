#include <iostream>
using namespace std;

class RandomMatrix{
private:
	int n, m;
	int **matrix;
public:
	RandomMatrix(int n, int m){
		this->n = n;
		this->m = m;
		this->matrix = new int*[n];
		for(int i = 0; i < n; i++){
			this->matrix[i] = new int[m];
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; i++){
				this->matrix[i][j] = (rand() % 2) == 0;
			}
		}
	}
	void print(){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; i++){
				cout << this->matrix[i][j] << ' ';
			}
			cout << endl;
		}
	}
};

int main(){
	RandomMatrix m = RandomMatrix(3, 4);
	m.print();
	return 0;
}