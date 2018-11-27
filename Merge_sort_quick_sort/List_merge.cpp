//
//  List_merge.cpp
//  HW4_2
//
//  Created by Li M on 11/1/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#include <stdio.h>
#include "List_merge.h"
void List_merge::merge( int low, int high, int mid)
{
    int size=0;
    while (*(arr++)!='\0')
        size++;
    arr-=size+1;
    int *c=new int[size];
    int i, j, k;
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (arr[i] < arr[j])
        {
            c[k] = arr[i];
            i++;
        }
        else
        {
            c[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)
    {
        arr[i] = c[i];
    }
}

void List_merge::Sort( int low, int high)
{
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        Sort(low,mid);
        Sort(mid+1,high);
        merge(low,high,mid);
    }
    return;
}
