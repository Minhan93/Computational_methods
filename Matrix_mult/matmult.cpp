//
//  main.cpp
//  HW3
//
//  Created by Li M on 10/8/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#include <iostream>
#include "sMatrix.h"
using namespace std;

int main(int argc, const char * argv[]){
    int which=1,dim=atoi(argv[1]);
    double dense=1.0;
    if (argc>2){
        which=atoi(argv[2]);
    }
    if (argc>3){
        dense=stof(argv[3]);
    }
    clock_t begin=clock();
    switch (which) {
        case 0:{
            SparseMatrix m1(0,1,dim,dim,dense); // two dense
            SparseMatrix m2(0,1,dim,dim,dense);
            m1*m2;
            break;}
        case 1:{
            SparseMatrix m3(1,1,dim,dim,dense); // CSR*CSR
            SparseMatrix m4(1,1,dim,dim,dense);
            m3*m4;
            break;}
            
        case 2:{
            SparseMatrix m5(2,1,dim,dim,dense); //CSC*CSC
            SparseMatrix m6(2,1,dim,dim,dense);
            m5*m6;
            break;}
        case 3:{
            SparseMatrix m7(1,1,dim,dim,dense); //CSR*CSC
            SparseMatrix m8(2,1,dim,dim,dense);
            m7*m8;
            break;}
        case 4:{
            SparseMatrix m9(1,1,dim,dim,dense); // transfer CSR to CSC then multiply
            SparseMatrix m10(1,1,dim,dim,dense);
            SparseMatrix m11=csr_csc(m10);
            m9*m11;
            break;}
        case 5:{
            SparseMatrix m12(2,1,dim,dim,dense); // transfer CSC to CSR then multiply
            SparseMatrix m13(2,1,dim,dim,dense);
            SparseMatrix m14=csr_csc(m12);
            m14*m13;
            break;}
            
        default:
            break;
    }
    clock_t end=clock();
    double elapsed=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"Time used with dimension "<<dim<<" on version "<<which<<" and density "<<dense<<" is "<<elapsed<<endl;
    return 0;
}
//
//    SparseMatrix m1(1,1,dim,dim,0.2);
//    SparseMatrix m2(2,1,dim,dim,0.3);
//    SparseMatrix m3(1,1,dim,dim,0.6);
//    SparseMatrix m4(2,1,dim,dim,0.2);

//    cout<<endl<<m1;
//    for (int i=0;i<m1.row+1;i++){
//        cout<<m1.IA[i]<<endl;
//    }

//

//
//    cout<<"m1 is"<<m1;                          test matrix multiplication
//    cout<<"m2 is"<<m2;
//cout<<"m1 m2 matrix product is"<<m1*m2;
//    cout<<"m1 is"<<m1;
//    cout<<"m3 is"<<m3;
//   cout<<"m1 m3 matrix product is"<<m1*m3;
//       cout<<"m1 m1 matrix product is"<<m1*m1;
//           cout<<"m2 m2 matrix product is"<<m2*m2;
    

//       cout<<"m1 is \n"<<m1;                  test format transformation
//   SparseMatrix m5=csr_csc(m1);
//  cout<<"matrix product is \n"<<m5;
//    cout<<"m2 is \n"<<m2;
//    SparseMatrix m6=csr_csc(m2);

//
    
    // cout<<"m1 is \n"<<m1;
    //    printmat(m1);
    //    m1.addelement(88, 1, 2);
    //
    //    cout<<"m1 is \n"<<m1;
    //    printmat(m1);




