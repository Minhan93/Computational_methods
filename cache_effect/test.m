range=[0,100]; %consistent with C++ implication
% dimA=[1000,1000];
% dimB=[1000,1000];
N=[16	32	64	128	256	512	768	1024];
for i=1:8
    dimA=[N(i),N(i)];
    dimB=[N(i),N(i)];
    A=randi(range,dimA);
    B=randi(range,dimB);
    tic;
    C=matmul(A,B);
    toc;
end