%ÊÖ¶¯µ÷
C=[-40;   -90];
A=[9 7;   7 20];
b=[56;   70];
Aeq=[];
beq=[];
lb=[5;    2];
ub=[inf;    inf];
[x,fval,exitflag]=linprog(C,A,b,Aeq,beq,lb,ub)