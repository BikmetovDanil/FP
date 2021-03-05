#include "binmatrix.h"
#include "AD.h"
//#include "DepthProject.h"

int main(int argc, char* argv[]){
    srand(time(NULL));
    Matrix test;
    test.fill(); // Случайное заполнение матрицы (равномерное распределение)
    //test.print();
    cout << "***" << endl;
    const int cycles = 20;
    int time = 0, all_cols = 0, max_cols = 0;
    for(int i = 0; i < cycles; i++){
        AD algorithm(test, m / 10);
        time += algorithm.run();
        all_cols += algorithm.getAllColsNumber();
        max_cols += algorithm.getMaxColsNumber();
    }
    cout << "***" << endl << "Всего наборов: " << all_cols / cycles << endl;
    //algorithm.printAllCols();
    cout << "***" << endl << "Из них максимальных наборов:" << max_cols / cycles << endl;
    //algorithm.printMaxCols();
    cout << "***" << endl << "Алгоритм отработал за " << time / cycles << " микросекунд" << endl;
    return 0;
}