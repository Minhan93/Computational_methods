function C =matmul(A,B)
[rowA,colA]=size(A);
[rowB,colB]=size(B);
C=zeros(rowA,colB);
for i=1:rowA
    for j=1:colB
        for k=1:colA
            C(i,j)=C(i,j)+A(i,k)*B(k,j);
        end
    end
    
end
