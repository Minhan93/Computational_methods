//
//  List_merge.h
//  HW4_2
//
//  Created by Li M on 11/1/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#ifndef List_merge_h
#define List_merge_h
#include "sort.h"

class List_merge : public List{ // implement the quick sort algorithm
public:
    void merge( int low, int high, int mid);
    void Sort( int low, int high);
    List_merge(const int numCo1=0,bool initRandom1=true):List(numCo1,initRandom1)
    {
    }
    
    
    
};

#endif /* List_merge_h */
