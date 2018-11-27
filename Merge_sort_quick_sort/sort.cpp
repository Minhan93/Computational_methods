//
//  sort.cpp
//  HW4_2
//
//  Created by Li M on 11/1/18.
//  Copyright © 2018 Li M. All rights reserved.
//
#include "sort.h"
#include <stdio.h>
ostream& operator<<(ostream& os,const List& m)   //overload the output cout for matrix
{
    for (int i=0;i<m.N;i++)
    {os<<m.arr[i]<<" ";}
    return os;
}

List::List(      const int numCo,bool initRandom):N(numCo)          //constructor
{
    arr=new int [N];
    if (initRandom==true){
        for (int i=0;i<N;++i ){
            arr[i]=rand()%10000000;
        }
    }
    else{
        cout<<"Please input the element of the list"<<endl;
        for (int i=0;i<N;++i ){
            
            cin>>arr[i];
        }
    }
}

List::~List(){
    delete []arr;
}
void List::Sort(int a, int b){
   
}
