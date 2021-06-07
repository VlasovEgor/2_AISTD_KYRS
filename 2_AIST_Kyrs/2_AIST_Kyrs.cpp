#include <Windows.h>
#include<iostream>
#include< iomanip >
#include <fstream>
#include<string>
#include  "Push_flow.h"

using namespace std;
using namespace Push_flow;


int main()
{
    ifstream file("С:\\text.txt");
    string line; int size;
    if (!file.is_open())
        cout << "The file cannot be opened!" << endl;
    else
    {
        getline(file, line);
        size = atoi(line.c_str());
        int** Matrix = new int* [size];
        for (int i = 0; i < size; i++)
            Matrix[i] = new int[size];
        char* tops = new char[size];
        matrixentry(file, Matrix, size, tops);
        int** matrixflow = new int* [size];
        for (int i = 0; i < size; i++)
            matrixflow[i] = new int[size];
        algorithm(Matrix, matrixflow, size);
        matrix(Matrix, size);
        matrix(matrixflow, size);
    }
    return 0;
}