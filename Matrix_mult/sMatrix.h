//
//  sMatrix.h
//  HW3
//
//  Created by Li M on 10/10/18.
//  Copyright © 2018 Li M. All rights reserved.
//

#ifndef sMatrix_h
#define sMatrix_h


#include <iostream>
#include <ctime>
#include <assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<vector>
#include <time.h>

using namespace std;

class SparseMatrix{
protected:

    //helper functions - useful for finding the inverse
    //    void subtractRow(int i, int j);                    //Subtracts row j from row i
    //    void swapRows(int i, int j);                    //Swaps rows i and j
    //    void multiplyRow(int i, double d);                //Multiplies row i by constant d
//    int **matbeg, *matind;
//    int *A, *IA,*JA;

    
public:
    int row;
    int col;
    int form;
    int **matbeg, *matind;
    int *A, *IA,*JA;
    int nnz;
    float den;

//    enum matrixFormat {rowOrdered, colOrdered, dense};

    

    
    SparseMatrix(const int format=1,
                 const bool initRandom=false,
                 const int numCols=0,
                 const int numRows=0,
                 const float density=0.1):form(format),row(numRows) ,col(numCols),den(density)          //constructor
    {   nnz=floor(row*col*den);
        srand(2431);
        if (format==0){
            matbeg = new int *[row];
            matind = new int [row*col];
            for (int i = 0; i < numRows; i++) {
                matbeg[i]=matind+i*col;
            }
            
            if (initRandom==true){
                for (int i=0;i<numRows;++i ){
                    for (int j=0;j<col; ++j){
                        matbeg[i][j]=rand()%6;
                        
                    }
                }
            }
            else{
                for (int i=0;i<numRows;++i ){
                    for (int j=0;j<col; ++j){
                        matbeg[i][j]=0;
                    }
                }
            }
        }
        
        if (format==1){
            if (initRandom==true){
                int num=floor(density*col*row);
//                cout<<"num is "<<num<<endl;
                A=new int [num];
                IA=new int [row+1];
                JA= new int [num];
                for (int i=0; i<row+1;i++){
                    IA[i]=0;
                }
                for (int i=0; i<num;i++){
                    A[i]=rand()%10;
                }
                int *idx=new int [col*row];
                for (int i=0;i<col*row;i++){
                    idx[i]=i;
                }
                random_shuffle(&idx[0], &idx[col*row]); // shuffle to get random idx from 0~num
                
                int *idc=new int[num];
                memcpy(idc,idx,num*sizeof(int));
                sort(idc, idc+num);         // idc is array index the num nonzero elements when flatten the matrix
                
                for (int i=0;i<num;i++){
                    
                    IA[idc[i]/col]++;
                    JA[i]=idc[i]%col;
                    
                }
                for (int j=0,cum=0;j<row;++j){
                    int tem=IA[j];
                    IA[j]=cum;
                    cum+=tem;
                    //cout<<"IA"<<IA[j]<<"cum is"<<cum<<"tem is"<<tem<< endl;
                    
                }
                IA[col]=num;    // the step to get IA, JA from the above array index
                
    
            }
            else{
                int num=floor(density*col*row);  // initialize to zero matrix otherwise
                A=new int [num];
                IA=new int [row+1];
                JA= new int [num];
                for (int i=0;i<num;i++){
                    A[i]=0;
                    JA[i]=0;
                    
                }
                for (int i=0;i<row+1;i++){
                    IA[i]=0;
                }
            }
            
            
            
        }
        
        if (format==2){
            if (initRandom==true){
                int num=floor(density*col*row);
//                cout<<"num is "<<num<<endl;
                A=new int [num];
                IA=new int [col+1];
                JA= new int [num];
                for (int i=0; i<col+1;i++){
                    IA[i]=0;
                }
                for (int i=0; i<num;i++){
                    A[i]=rand()%10;
                }
                int *idx=new int [col*row];
                for (int i=0;i<col*row;i++){
                    idx[i]=i;
                }
                random_shuffle(&idx[0], &idx[col*row]); // shuffle to get random idx from 0~nnz
                
                int *idc=new int[num];
                memcpy(idc,idx,num*sizeof(int));
                sort(idc, idc+num);  // get index for the m nonzero elements
                
                for (int i=0;i<num;i++){
                    IA[idc[i]/row]++;
                    JA[i]=idc[i]%row;
                    
                }
                for (int j=0,cum=0;j<col;j++){
                    int tem=IA[j];
                    IA[j]=cum;
                    cum+=tem;
                    
                }
                IA[row]=num;
            }
            else{
                int num=floor(density*col*row);
                A=new int [num];
                IA=new int [col+1];
                JA= new int [num];
                for (int i=0;i<num;i++){
                    A[i]=0;
                    JA[i]=0;
                    
                }
                for (int i=0;i<col+1;i++){
                    IA[i]=0;
                }
            }
            
            
            
            
        }
        
        
        
        
        
        
        
        
        
    }
    ~SparseMatrix(){
        if (form==0){
            delete []matbeg;
            delete []matind;
        }
        else{

        delete []A;
        delete []IA;
        delete []JA;
        }
        
    }
    
    SparseMatrix& operator=(SparseMatrix& m);                    //overload assignment operator
    void addelement(int val,int ridx, int cidx);                // add element to matrix
    friend ostream& operator<<(ostream& os,const SparseMatrix& m);  //overload "<<"
    friend SparseMatrix operator *(SparseMatrix& h,SparseMatrix& m); //overload mat mult
    friend SparseMatrix csr_csc(SparseMatrix& h);               //coverse between csr csc
    friend void printmat(SparseMatrix& h);                      // print A,IA,JA

    
};















void SparseMatrix::addelement(int val,int ridx, int cidx){
    int idx=-1;
    int ridx1=(form==1)?ridx:cidx;
    int cidx1=(form==1)?cidx:ridx;
    int row1=(form==1)?row:col;
    
    bool flag=true; //true mean the new element is taking a spot that was empty earlier
    for (int j=IA[ridx1];j<IA[ridx1+1];j++){
        if (cidx1<=JA[j]){
            idx=j;
            if (JA[j]==cidx1){
                flag=false;
            }
        }
     
    }
    if (idx==-1){
        idx=IA[ridx1+1];
    }
        
    cout<<"idx is"<<idx<<endl;
    
    if (flag==false){ //simply add element and only A is changed.
        A[idx]+=val;
    }
    else{
        for(int i=ridx1+1;i<row1+1;i++){
            IA[i]++;
        }
        

//        memcpy(A1, A,NN*sizeof(int));
//        memcpy(JA1, JA,NN*sizeof(int));
        
        nnz+=1;
        int * tempadd=NULL; // tempory address location
        int * tempadd2=NULL;
        while(tempadd==NULL){
            tempadd=(int*) realloc(A,nnz);
        }
        while(tempadd2==NULL){
            tempadd2=(int*) realloc(JA,nnz);
        }
        
        A=tempadd;
        JA=tempadd2;
        
        for (int i=nnz-1;i>idx;i--){
            A[i]=A[i-1];
            JA[i]=JA[i-1];
        }
        
        A[idx]=val;
        JA[idx]=cidx1;
        
        
    }
    
    
}





SparseMatrix& SparseMatrix::operator=(SparseMatrix& m)                //overload assignment operator
{
    if (this==&m)
        return *this;
    row=m.row;
    col=m.col;
    den=m.den;
    delete [] A;
    delete [] IA;
    delete [] JA;
    
    int num=floor(den*col*row);
//    cout<<"num is "<<num<<endl;
    A=new int [num];
    IA=new int [row+1];
    JA= new int [num];
    
    for (int i=0;i<num;i++){
        A[i]=m.A[i];
        JA[i]=m.JA[i];
        
    }
    int N1=(m.form==1)?m.row:m.col;
    for (int i=0;i<N1+1;i++){
        IA[i]=m.IA[i];
    }
    return *this;
}


SparseMatrix csr_csc(SparseMatrix& h){  // Transfer the formats between csc and csr
    
    int nnz=floor(h.den*h.col*h.row);

    SparseMatrix v(3-h.form,false,h.col,h.row,h.den);
    
    
    for(int n=0;n<nnz;n++){
        v.IA[h.JA[n]]++;
        
    }
    int N1=(h.form==1)?h.col:h.row;
    int N2=(h.form==1)?h.row:h.col;
    for (int j=0,cum=0;j<N1;j++){
        int tem=v.IA[j];
//        cout<<"j is"<<j <<"; v IA is"<<v.IA[j]<<endl;
        v.IA[j]=cum;
        cum+=tem;
        
    }
    v.IA[N1]=nnz;
    for (int i=0;i<N2;i++){
        for(int jj=h.IA[i];jj<h.IA[i+1];jj++){
            int colum=h.JA[jj];
            int dest=v.IA[colum];
            v.JA[dest]=i;
            v.A[dest]=h.A[jj];
            v.IA[colum]++;
        }
    }
    for (int j=0,last=0;j<N1;j++){
        int temp=v.IA[j];
        v.IA[j]=last;
        last=temp;
    }
    
    return v;
    
}




SparseMatrix operator *(SparseMatrix& h,SparseMatrix& m)
//overload * operator support dense*dense and CSR*CSC or CSR*CSR

{
    

    SparseMatrix temp(0,0,h.row,m.col);
    assert(h.col==m.row);
    if (h.form==1&& m.form==2){
        for (int i=0; i<h.row; ++i)
        {
            
            for (int j=h.IA[i]; j<h.IA[i+1]; ++j)
            {
                int colum=h.JA[j];
                int rval=h.A[j];
                for (int k=0; k<m.col; ++k){
                    for (int w=m.IA[k];w<m.IA[k+1];w++){
                        if (m.JA[w]==colum){
                            temp.matbeg[i][k]+=rval*m.A[w];
                        }
                    }
                }
                    
            }
        }
        
    }
    else if (h.form==0&&m.form==0){
        for (int i=0; i<h.row; ++i){
            for (int j=0; j<m.col; ++j)
            {
                for (int k=0; k<h.col; ++k)
                   temp.matbeg[i][j]+=h.matbeg[i][k]*m.matbeg[k][j];
            }
        }
    }
    else if (h.form==2&&m.form==2){  //CSC * CSC
        int N1=h.col;
        int N2=m.col;
        int N3=m.row;
        for (int i=0;i<N1;i++){
            for (int j=h.IA[i];j<h.IA[i+1];j++){
                int rcol=h.JA[j];
                int rval=h.A[j];
                for (int k=0;k<N3;k++){
                    int NN=int(floor(m.row*m.col*m.den));
                    int *idx=new int[NN];
                    int ct=0;
                    for (int ii=0;ii<NN;ii++){
                        if (m.JA[ii]==k){
                            idx[ct]=ii;
                            ct++;
                        }
                    }
                    for (int w=0;w<ct;w++){
                        for (int t=0;t<N2;t++){
                            if (m.IA[t]<=idx[w]&&idx[w]<m.IA[t+1]){
                                if (t==rcol){
                                    temp.matbeg[i][k]+=rval*m.A[idx[w]];
                                }
                            }
                        }
                    }
                }
            }
        }
    
    }
    else if(h.form==1&&m.form==1){ //CSR * CSR
        for (int i=0;i<h.row;i++){
            for (int j=h.IA[i];j<h.IA[i+1];j++){
                int rval=h.A[j];
                for (int k=m.IA[m.JA[j]];k<m.IA[m.JA[j]+1];k++){
                    temp.matbeg[i][m.JA[k]]=rval*m.A[k];
                }
            }
            
        }
    }

    return temp;
    
    
    
    
}










ostream& operator<<(ostream& os,const SparseMatrix& m)   //overload the output cout for matrix
{
    if (m.form==0){
        for (int i=0;i<m.row;i++)
        {for (int j=0;j<m.col;j++)
        {os<<m.matbeg[i][j]<<" ";}
            os<<"\n";
        }
        
    }
    
    if (m.form==1){
        for (int i=0;i<m.row;i++){
            for (int j=m.IA[i];j<m.IA[i+1];j++){
                os<<"("<<i<<","<<m.JA[j] <<")"<<" "<<m.A[j]<<endl;
            }
        }
      
    }
    if (m.form==2){
        for (int i=0;i<m.col;i++){
            for (int j=m.IA[i];j<m.IA[i+1];j++){
                os<<"("<<m.JA[j]<<","<<  i<<")"<<" "<<m.A[j]<<endl;
            }
        }
        
    }

    return os;
}



void printmat(SparseMatrix& h){
    if (h.form==1){
        cout<<"A is \n";
        for(int i=0;i<h.nnz;i++){
            cout<<h.A[i]<<endl;
        }
        cout<<"JA is \n";
        for(int i=0;i<h.nnz;i++){
            cout<<h.JA[i]<<endl;
        }
        cout<<"IA is \n";
        for(int i=0;i<=h.row;i++){
            cout<<h.IA[i]<<endl;
        }
    }
}


#endif /* sMatrix_h */
