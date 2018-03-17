function resultX=BranchBound(C,A,b,Aeq,beq,lb,ub)%未成功
%Input  -C 
%       -A 
%       -b 
%       -Aeq 
%       -beq 
%       -lb
%       -ub 以上输入参数含义同linprog()函数的参数
%       -m 未知元个数
%Output -X 1*m使用分支定界法得到的原约束条件下的整数解

m=length(C);%未知元个数

%参照课本(第四版)p137求解示意图
%我们以一颗树的形式来记录求解的子问题；
%第0层为B问题，标号1
%第1层为B1、B2问题，分别标号2、3；这一层对进行分支；依次类推

[x,fval,exitflag] =linprog(C,A,b,Aeq,beq,lb,ub);
if (exitflag~=1) 
    fprintf('无有限最优解解');
    return;
end;
abadon[1]=0;%表示该节点是否被剪支
X(1,1:m)=x;
Lb(1,1:m)=lb;
Ub(1,1:m)=ub;

zB=0;zU=fval;%上下界
for i=0:m
   for j=2^i:2^(i+1)-1
       if (abadon[floor(j/2)]==1)
           abadon[j]=1;
           continue;
       end
       
       if (j%2==0) 
           Lb(i,:)=Lb(floor(i/2),:);
           Ub(i,:)=Ub(floor(i/2),:);
           Ub(i,i)=floor(Ub(i,i));
           [x,fval,exitflag] =linprog(C,A,b,Aeq,beq,lb,ub);
           
       end
       
       
       
       
       
   end
end









