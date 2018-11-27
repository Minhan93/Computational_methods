//
//  main.cpp
//  HW4_1
//
//  Created by Li M on 11/1/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#include <iostream>
#include"matrix.h"
#ifdef _OPENMP
#include <omp.h>
#endif
int main(int argc, const char * argv[]) {
    int size=4;
    int thread=2;
    if (argc>1){
            size=atoi(argv[1]);
    }

    if (argc>2){
        thread=atoi(argv[2]);
    }
    srand(time(NULL));
    double start,end;
    Matrix m1(size,size,1);
    if (size<5){
    cout<<"m1 is "<<m1<<endl;
    }
    Matrix m2(size,size,1);
    if (size<5){
    cout<<"m2 is "<<m2<<endl;
    }
//    if (size<10){
//    cout<<"m1 is \n"<<m1;
//    cout<<"m2 is \n"<<m2;
//    }
//    Matrix m3=m1-m2;
//    cout<<"m1 is \n"<<m1;
//    cout<<"m2 is \n"<<m2;
//    cout<<"m3 is \n"<<m3;




#ifdef _OPENMP
    omp_set_dynamic(0);     // Explicitly disable dynamic teams
    omp_set_num_threads(thread);

    start = omp_get_wtime();
    clock_t begin = clock();

    Matrix MM=Strassen(m1, m2, size);

    clock_t endclock = clock();
    end = omp_get_wtime();
    if (size<5){
        cout<<"m1,m2 product using openMP is \n"<<MM;
    }

    double elapsed_secs = end - start;
    double elapsed_secsclock = double(endclock - begin) / CLOCKS_PER_SEC;
    cout<<"Time used with openMP"<< " is "<<elapsed_secsclock << endl;
#else
    clock_t begin = clock();

    Matrix CC=Strassen(m1, m2, size);
    clock_t endclock = clock();

    double elapsed=double(endclock-begin)/CLOCKS_PER_SEC;
    if (size<5){
        cout<<"m1,m2 product without using openMP is\n"<<CC;
    }
    cout<<"Time used without openMP"<< " is "<<elapsed << endl;
#endif

    return 0;
}
