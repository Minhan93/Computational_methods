//
//  matrix.cpp
//  HW4_1
//
//  Created by Li M on 11/1/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#include <stdio.h>
#include "matrix.h"
Matrix::Matrix(
               const int numCols,
               const int numRows,
               const bool initRandom
               ):row(numRows) ,col(numCols)        //constructor
{
    matbeg = new int *[row];
    matind = new int [row*col];
    for (int i = 0; i < numRows; i++) {
        matbeg[i]=matind+i*col;
    }
    
    if (initRandom==true){
        for (int i=0;i<numRows;++i ){
            for (int j=0;j<col; ++j){
                matbeg[i][j]=rand()%6;
                
            }
        }
    }
    else{
        for (int i=0;i<numRows;++i ){
            for (int j=0;j<col; ++j){
                matbeg[i][j]=0;
            }
        }
    }
    
    
}


Matrix::~Matrix(){
    delete []matind;
    delete []matbeg;
//    for (int i=0;i<row;i++){
//
//    }
    
    
}


Matrix operator *(Matrix& h,Matrix& m) //overload * operator support dense*dense and CSR*CSC or CSR*CSR
{
    Matrix temp(m.row,m.col,0);
    for (int i=0; i<h.row; ++i){
        for (int j=0; j<m.col; ++j)
        {
            for (int k=0; k<h.col; ++k)
                temp.matbeg[i][j]+=h.matbeg[i][k]*m.matbeg[k][j];
        }
    }
    return temp;
}


Matrix& Matrix::operator=(Matrix& m)                //overload assignment operator
{
    if (this==&m)
        return *this;

    row=m.row;
    col=m.col;
    
    
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            matbeg[i][j]=m.matbeg[i][j];
            
        }
    }
    
    return *this;
}

Matrix operator +(Matrix& h,Matrix& m){
    assert(h.row==m.row&&h.col==m.col);
    Matrix temp(m.row,m.col,0);
    for (int i=0;i<m.row;i++){
        for (int j=0;j<m.col;j++){
            temp.matbeg[i][j]=h.matbeg[i][j]+m.matbeg[i][j];
            
        }
    }
    return temp;
    
}

Matrix operator -(Matrix& h,Matrix& m){
    assert(h.row==m.row&&h.col==m.col);
    Matrix temp(m.row,m.col,0);
    for (int i=0;i<m.row;i++){
        for (int j=0;j<m.col;j++){
            temp.matbeg[i][j]=h.matbeg[i][j]-m.matbeg[i][j];
            
        }
    }
    return temp;
    
}



Matrix Strassen(Matrix& A,Matrix& B, int N){
    N=N/2;


    if (N<=1){
        cout<<"A  is \n"<<A<<endl;
        cout<<"B  is \n"<<B<<endl;
        Matrix temp1=A*B;
        cout<<"return is"<<temp1<<endl;
        return temp1;
        
//        for (int i=0;i<N;i++){
//            for (int j=0;j<N;j++){
//                temp.matbeg[i][j]=temp1.matbeg[i][j];
//
//            }
//        }
    }
    Matrix temp(A.row,B.col,0);
        Matrix A11(N,N,0);
        Matrix A12(N,N,0);
        Matrix A21(N,N,0);
        Matrix A22(N,N,0);
        Matrix B11(N,N,0);
        Matrix B12(N,N,0);
        Matrix B21(N,N,0);
        Matrix B22(N,N,0);
        Matrix M1(N,N,0);
        Matrix M2(N,N,0);
        Matrix M3(N,N,0);
        Matrix M4(N,N,0);
        Matrix M5(N,N,0);
        Matrix M6(N,N,0);
        Matrix M7(N,N,0);
        for (int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                A11.matbeg[i][j]=A.matbeg[i][j];
                A12.matbeg[i][j]=A.matbeg[i][j+N];
                A21.matbeg[i][j]=A.matbeg[i+N][j];
                A22.matbeg[i][j]=A.matbeg[i+N][j+N];
                
                B11.matbeg[i][j]=B.matbeg[i][j];
                B12.matbeg[i][j]=B.matbeg[i][j+N];
                B21.matbeg[i][j]=B.matbeg[i+N][j];
                B22.matbeg[i][j]=B.matbeg[i+N][j+N];
                
            }
        }
//        cout<<"A11  is \n"<<A11<<endl;
//        cout<<"A12  is \n"<<A12<<endl;
//        cout<<"A21  is \n"<<A21<<endl;
//        cout<<"A22  is \n"<<A22<<endl;
//        cout<<"B11  is\n "<<B11<<endl;
//        cout<<"B12  is \n"<<B12<<endl;
//        cout<<"B21  is \n"<<B21<<endl;
//        cout<<"B22  is \n"<<B22<<endl;
    
#pragma omp parallel sections
        {
#pragma omp section
            {
            Matrix temp11=A12-A22;
            Matrix temp12=B21+B22;
            Matrix temp13=Strassen(temp11, temp12, N);
            M1=temp13;
                cout<<"temp11 is \n"<<temp11<<endl;
                cout<<"temp12 is \n"<<temp12<<endl;

            cout<<"M1 is \n"<<M1<<endl;
            }
#pragma omp section
            {
            Matrix temp21=A11+A22;
            Matrix temp22=B11+B22;
            Matrix temp23=Strassen(temp21, temp22,N);
            M2=temp23;
                cout<<"temp21 is \n"<<temp21<<endl;
                cout<<"temp22 is \n"<<temp22<<endl;
                cout<<"A11 is \n"<<A11<<endl;
                cout<<"A12 is\n"<<A12<<endl;
                cout<<"M2 is \n"<<M2<<endl;

            }
#pragma omp section
            {
            Matrix temp31=A11-A21;
            Matrix temp32=B11+B12;
            Matrix temp33=Strassen(temp31, temp32, N);
            M3=temp33;
                cout<<"temp31 is \n"<<temp31<<endl;
                cout<<"temp32 is \n"<<temp32<<endl;
                cout<<"A11 is \n"<<A11<<endl;
                cout<<"A12 is\n"<<A12<<endl;
                cout<<"M3 is \n"<<M3<<endl;

            }
#pragma omp section
            {
                cout<<"A11 is \n"<<A11<<endl;
                cout<<"A12 is\n"<<A12<<endl;
            Matrix temp41=A11+A12;
            Matrix temp42=Strassen(temp41, B22, N);
            M4=temp42;
                                cout<<"temp41 is \n"<<temp41<<endl;
                cout<<"M4 is \n"<<M4<<endl;

            }
#pragma omp section
            {
            Matrix temp51=B12-B22;
            Matrix temp52=Strassen(A11, temp51, N);
            M5=temp52;
                                cout<<"temp51 is \n"<<temp51<<endl;
                cout<<"M5 is \n"<<M5<<endl;

            }
#pragma omp section
            {
            Matrix temp61=B21-B11;
            Matrix temp62=Strassen(A22, temp61, N);
            M6=temp62;
                                cout<<"temp61 is \n"<<temp61<<endl;
                cout<<"M6 is \n"<<M6<<endl;

            }
#pragma omp section
            {
            Matrix temp71=A21+A22;
            Matrix temp72=Strassen(temp71, B11, N);
            M7=temp72;
                                cout<<"temp71 is \n"<<temp71<<endl;
                cout<<"M7 is \n"<<M7<<endl;

        }
        }
        
        Matrix temp81=M1+M2;
        Matrix temp82=temp81-M4;
        Matrix C11=temp82+M6;
        
        Matrix C12=M4+M5;
        
        Matrix C21=M6+M7;
        
        Matrix temp91=M2-M3;
        Matrix temp92=temp91+M5;
        Matrix C22=temp92-M7;
        cout<<"C11 is\n"<<C11<<endl;
        cout<<"C12 is\n"<<C12<<endl;
        cout<<"C21 is\n"<<C21<<endl;
        cout<<"C22 is\n"<<C22<<endl;
        

        
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++){
                temp.matbeg[i][j]=C11.matbeg[i][j];
                temp.matbeg[i][j+N]=C12.matbeg[i][j];
                temp.matbeg[i+N][j]=C21.matbeg[i][j];
                temp.matbeg[i+N][j+N]=C22.matbeg[i][j];
                
            }
        }
        cout<<"temp is"<<temp<<endl;
        return temp;

 
    
}






ostream& operator<<(ostream& os,const Matrix& m)   //overload the output cout for matrix
{
    for (int i=0;i<m.row;i++)
    {for (int j=0;j<m.col;j++)
    {os<<m.matbeg[i][j]<<" ";}
        os<<"\n";
    }
    
    return os;
}
