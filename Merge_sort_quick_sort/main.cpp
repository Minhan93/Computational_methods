//
//  main.cpp
//  HW4_2
//
//  Created by Li M on 10/29/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#include <iostream>
#include "sort.h"
#include "List_quick.h"
#include "List_merge.h"

int main(int argc, const char * argv[]){
    int which=1,size=10; // size is the dimension of the list
    bool randominit=true;// specify if read data from user 0 or just generate random data 1
    if (argc>1){
        size=atoi(argv[1]);
    }
    if (argc>2){
        which=atoi(argv[2]);  //0 then use quick sort, 1 then use merge sort
    }
    if (argc>3){
        randominit=atoi(argv[2]);
    }

    clock_t begin=clock();
    srand(time(NULL));
//    cout<<"hahha"<<endl;
    switch (which) {
        case 0:{
            List_quick ls(size,randominit);
           cout<<"ls is"<<ls<<endl;
            ls.Sort(0,size-1);
            cout<<"ls is"<<ls<<endl;
            break;}
        case 1:{
            List_merge ls1(size,randominit);
            cout<<"ls is"<<ls1<<endl;
            ls1.Sort(0, size-1);
            cout<<"ls is"<<ls1<<endl;
            break;}
            
        default:
            break;
    }
    clock_t end=clock();
    double elapsed=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"Time used with list length "<<size<<" on sort method "<<which<<" is "<<elapsed<<endl;
    return 0;
}
