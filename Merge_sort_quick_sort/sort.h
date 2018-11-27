//
//  sort.h
//  HW4_2
//
//  Created by Li M on 10/29/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#ifndef sort_h
#define sort_h
#include <iostream>
#include <ctime>
#include <assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<vector>
#include <time.h>
using namespace std;

class List{
protected:
    int N;
    int *arr;
    
public:
    List(      const int numCo=0,bool initRandom=true);
    ~List();
    friend ostream& operator<<(ostream& os,const List& m);  //overload "<<"
    virtual void Sort(int a, int b);
//    List& operator=(List& m);
 
};















#endif /* sort_h */
