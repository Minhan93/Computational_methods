//
//  matrix.h
//  HW4_1
//
//  Created by Li M on 11/1/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include <iostream>
#include <ctime>
#include <assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<vector>
#include <time.h>

using namespace std;

class Matrix{
private:

    
    //helper functions - useful for finding the inverse
    //    void subtractRow(int i, int j);                    //Subtracts row j from row i
    //    void swapRows(int i, int j);                    //Swaps rows i and j
    //    void multiplyRow(int i, double d);                //Multiplies row i by constant d
    //    int **matbeg, *matind;
    //    int *A, *IA,*JA;
    
    
public:
    int row;
    int col;
    int **matbeg, *matind;


    //    enum matrixFormat {rowOrdered, colOrdered, dense};

    
    Matrix(
                 const int numCols=0,
                 const int numRows=0,
           const bool initRandom=false
           );
        

//    ~Matrix();
    
    Matrix& operator=(Matrix& m);                    //overload assignment operator
    friend ostream& operator<<(ostream& os,const Matrix& m);  //overload "<<"
    friend Matrix operator *(Matrix& h,Matrix& m); //overload mat mult
    Matrix operator +(const Matrix& m); //overload mat mult
    Matrix operator -(const Matrix& m); //overload mat mult
    friend Matrix Strassen(Matrix& h,Matrix& m, int N); //
    friend void Strassen1(Matrix& A,Matrix& B,Matrix& C, int N);
    friend void deleteM(Matrix& m);
    
    
};









#endif /* matrix_h */
