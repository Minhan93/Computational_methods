//
//  List_quick.cpp
//  HW4_2
//
//  Created by Li M on 11/1/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#include <stdio.h>
#include "List_quick.h"
void List_quick::Sort(int p,int r)   //r在第一次迭代中取length（a)-1,p取1
{
    double pivot=arr[p];
    int i=p;
    int j=r;
    while(i<j)
    {
        while (i<j&&arr[j]>=pivot)
            
            j--;arr[i]=arr[j];
        
        while (i<j&&arr[i]<=pivot)
            
            i++;arr[j]=arr[i];
        
    }
    arr[i]=pivot;
    if(p<i-1)
        Sort(p,i-1);
    if (r>i+1)
        Sort(i+1,r);
}
