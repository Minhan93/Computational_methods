//
//  main.cpp
//  ISE407_hw01
//
//  Created by Li M on 9/10/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#include <stdio.h>
#include "cache_line.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/sysctl.h>

using namespace std;
//First implication
int ** matmult1 (int ** A, int * dimA, int ** B, int * dimB){
    int rowA= dimA[0];
    int colA= dimA[1];
    int rowB= dimB[0];
    int colB= dimB[1];
    int **elements;
    elements =  new int *[rowA];
    for (int i=0; i<rowA; ++i) {
        elements[i] = new int [colB];
    }
    for (int i=0; i<rowA; ++i)
    {
        
        for (int j=0; j<colB; ++j)
        {
            elements[i][j]=0;
        }
    }
    
    if (colA != rowB){
        throw "The dimensions of two matrices should match\n";
        
    }

    for (int i=0; i<rowA;++i){
        for (int j=0;j<colB;++j){
            for (int k=0;k<colA;++k){
                elements[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
        

    return elements;
}


// Second implication
int ** matmult2 (int ** A, int * dimA, int ** B, int * dimB){
    int rowA= dimA[0];
    int colA= dimA[1];
    int rowB= dimB[0];
    int colB= dimB[1];
    int **elements,**B_t; //B_t is the transpose of B
    elements =  new int *[rowA];
    for (int i=0; i<rowA; ++i) {
        elements[i] = new int [colB];
    }
    B_t =  new int *[colB];
    for (int i=0; i<colB; ++i) {
        B_t[i] = new int [rowB];
    }
    
    for (int i=0; i<colB;++i){
        for (int j=0;j<rowB;++j){
            B_t[i][j]=B[j][i];
        }
    }
    for (int i=0; i<rowA; ++i)
    {
        
        for (int j=0; j<colB; ++j)
        {
            elements[i][j]=0;
        }
    }
    

    
    if (colA != rowB){
        throw "The dimensions of two matrices should match\n";
        
    }
    
    for (int i=0; i<rowA;++i){
        for (int j=0;j<colB;++j){
            for (int k=0;k<colA;++k){
                elements[i][j]+=A[i][k]*B_t[j][k];
            }
        }
    }
    
    
    return elements;
}


/*Third implication*/
int ** matmult3 (int ** A, int * dimA, int ** B, int * dimB){
    int rowA= dimA[0];
    int colA= dimA[1];
    int rowB= dimB[0];
    int colB= dimB[1];
    int **elements;
    
    int CLS=cache_line_size();
    const int SM=(CLS/sizeof(int));  // SM=16; if the cache_line_h is not working
    
    elements =  new int *[rowA];
    for (int i=0; i<rowA; ++i) {
        elements[i] = new int [colB];
    }
    for (int i=0; i<rowA; ++i)
    {

        for (int j=0; j<colB; ++j)
        {
            elements[i][j]=0;
        }
    }
    
//    elements= (int **)malloc(rowA * sizeof(int*));
//    for(int i = 0; i < rowA; i++) elements[i] = (int *)malloc(colB * sizeof(int));
    
//    int *elements = (int *)malloc(rowA * colB * sizeof(int));
//    for (int i=0; i<rowA; ++i)
//    {
//
//        for (int j=0; j<colB; ++j)
//        {
//            elements[i*colB+j]=0;
//        }
//    }

    
    if (colA != rowB){
        throw "The dimensions of two matrices should match\n";
        
    }
    

    int * rres;
    int* rA;
    int* rB;
    int i2;
    int k2;
    for (int i=0; i<rowA;i+=SM){
        for (int j=0;j<colB;j+=SM){
            for (int k=0;k<colA;k+=SM){
                for (i2=0, rres=&elements[i][j],rA=&A[i][k];i2<SM;++i2){
                    for ( k2=0,rB=&B[k][j];k2<SM;++k2){
                        for (int j2=0;j2<SM;++j2){
                            rres[j2]+=rA[k2]*rB[j2];

                        }
                        rB=&B[k+k2+1][j];
                    }
                    rres=&elements[i+i2+1][j];
                    rA=&A[i+i2+1][k];
                }
            }
        }
    }
/* replace with the following in the loop if don't want to deal with 'SM not divided by N' case.*/
    //rowA-i>=SM?(i2<SM):(i2<rowA%SM)     colA-k>=SM?(k2<SM):(k2<colA%SM)  colB-j>=SM?(j2<SM):(j2<colB%SM)
    
    
    return elements;

}

/* Fourth implication */
int ** matmult4 (int ** A, int * dimA, int ** B, int * dimB){
    int rowA= dimA[0];
    int colA= dimA[1];
    int rowB= dimB[0];
    int colB= dimB[1];
    int **elements;

    int CLS=cache_line_size();
    const int SM=(CLS/sizeof(int));
    
    elements =  new int *[rowA];
    for (int i=0; i<rowA; ++i) {
        elements[i] = new int [colB];
    }
    for (int i=0; i<rowA; ++i)
    {

        for (int j=0; j<colB; ++j)
        {
            elements[i][j]=0;
        }
    }
    
    

    
    if (colA != rowB){
        throw "The dimensions of two matrices should match\n";
        
    }
    
    for (int r=0; r<rowA;r+=SM){
        for (int c=0;c<colB;c+=SM){
            for (int k=0;k<colA;k+=SM){
                for (int r2=0;r2<SM;++r2){
                    for (int k2=0;k2<SM;++k2){
                        for (int c2=0;c2<SM;++c2){
                            elements[r+r2][c+c2]+=A[r+r2][k+k2]*B[k+k2][c+c2];
                        }
                    }
                }
            }
        }
    }
    
    //rowA-r>=SM?(r2<SM):(r2<rowA%SM)    colA-k>=SM?(k2<SM):(k2<colA%SM)
    
    return elements;
}



//initialize a random matrix
int ** random_init(int *dimA){
    int rowA= dimA[0];
    int colA= dimA[1];
    int **elements;
    srand (time(NULL));
    elements =  new int *[rowA];
    for (int i=0; i<rowA; ++i) {
        elements[i] = new int [colA];
    }
    // Initialize value for the matrix
    for (int i=0; i<rowA; ++i)
    {
        
        for (int j=0; j<colA; ++j)
        {
            elements[i][j]=rand()%6;
        }
    }
    return elements;
}


/* destructor, free memory */
void mat_destructor(int **matrix, int rows){
for (int i = 0; i < rows; ++i)
delete [] matrix[i];
delete [] matrix;
}

/* Helper function to print matrix */
void print_matrix(int **A,int *dimA){
    int rowA= dimA[0];
    int colA= dimA[1];
    for (int i=0;i<rowA;i++)
        {for (int j=0;j<colA;j++)
            {cout<<A[i][j]<<" ";}
        cout<<"\n";
    }
}

int main(int argc, const char * argv[]) {
    int **A,**B,**C1,**C2,**C3,**C4;
    int dimA[]={16,16};
    int dimB[]={16,16};
    int dimC[]={dimA[0],dimB[1]};
    A=random_init(dimA);
    B=random_init(dimB);
    
//    struct timespec start, finish;
//    double elapsed;
//    clock_gettime(CLOCK_MONOTONIC, &start);
    clock_t begin1 = clock();
    C1=matmult1(A, dimA, B, dimB);
//    clock_gettime(CLOCK_MONOTONIC, &finish);
//    elapsed = (finish.tv_sec - start.tv_sec);
//    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
//    cout<<"time used on version 2 is \n "<<elapsed<<endl;
    clock_t end1 = clock();
    double elapsed_secs1 = double(end1 - begin1) / CLOCKS_PER_SEC;
    cout<<"time used on version 1 is \n "<<elapsed_secs1<<endl;
    
    begin1 = clock();
    C2=matmult2(A, dimA, B, dimB);
    end1 = clock();
    elapsed_secs1 = double(end1 - begin1) / CLOCKS_PER_SEC;
    cout<<"time used on version 2 is \n "<<elapsed_secs1<<endl;
    
    begin1 = clock();
    C3=matmult3(A, dimA, B, dimB);
    end1 = clock();
    elapsed_secs1 = double(end1 - begin1) / CLOCKS_PER_SEC;
    cout<<"time used on version 3 is \n "<<elapsed_secs1<<endl;
    
    begin1 = clock();
    C4=matmult4(A, dimA, B, dimB);
    end1 = clock();
    elapsed_secs1 = double(end1 - begin1) / CLOCKS_PER_SEC;
    cout<<"time used on version 4 is \n "<<elapsed_secs1<<endl;

    

//    cout<<"Matrix A is \n";
//    print_matrix(A, dimA);
//    cout<<"Matrix B is \n";
//    print_matrix(B, dimB);
//    cout<<"The matrix product from version1 is \n";
//    print_matrix(C1, dimC);
//    cout<<"The matrix product from version2 is \n";
//    print_matrix(C2, dimC);
//    cout<<"The matrix product from version3 is \n";
//    print_matrix(C3, dimC);
//    cout<<"The matrix product from version4 is \n";
//    print_matrix(C4, dimC);

    mat_destructor(A,dimA[0]); // free memory
    mat_destructor(B,dimB[0]);
    mat_destructor(C1,dimC[0]);
    mat_destructor(C2,dimC[0]);
    mat_destructor(C3,dimC[0]);
    mat_destructor(C4,dimC[0]);
    return 0;


    
    
}


















