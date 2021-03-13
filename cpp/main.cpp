#include "binmatrix.h"
#include "AD.h"

int main(int argc, char* argv[]){
    srand(time(NULL));
    Matrix test;
    test.readFromFile("./classK_enc.txt");
    test.print();
    cout << "***" << endl;
    AD ad(test, 0.07 * m);
    int time = ad.run();
    ad.printMaxCols();
    cout << "***" << endl;
    cout << "Частых наборов: " << ad.getAllColsNumber() << endl;
    cout << "Максимальных частых наборов: " << ad.getMaxColsNumber() << endl;
    cout << "Отработал за " << time << " мс" << endl;
    return 0;
}