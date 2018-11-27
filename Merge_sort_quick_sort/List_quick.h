//
//  List_quick.h
//  HW4_2
//
//  Created by Li M on 11/1/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#ifndef List_quick_h
#define List_quick_h
#include "sort.h"
class List_quick : public List{ // implement the quick sort algorithm
public:
   
    List_quick(const int numCo1=0,bool initRandom1=true):List(numCo1,initRandom1)
    {
    }
    
    void Sort(int p,int r) ;  //r在第一次迭代中取length（a)-1,p取1
    
    
};

#endif /* List_quick_h */
