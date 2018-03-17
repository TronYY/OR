function resultX=BranchBound(C,A,b,Aeq,beq,lb,ub)%δ�ɹ�
%Input  -C 
%       -A 
%       -b 
%       -Aeq 
%       -beq 
%       -lb
%       -ub ���������������ͬlinprog()�����Ĳ���
%       -m δ֪Ԫ����
%Output -X 1*mʹ�÷�֧���編�õ���ԭԼ�������µ�������

m=length(C);%δ֪Ԫ����

%���տα�(���İ�)p137���ʾ��ͼ
%������һ��������ʽ����¼���������⣻
%��0��ΪB���⣬���1
%��1��ΪB1��B2���⣬�ֱ���2��3����һ��Խ��з�֧����������

[x,fval,exitflag] =linprog(C,A,b,Aeq,beq,lb,ub);
if (exitflag~=1) 
    fprintf('���������Ž��');
    return;
end;
abadon[1]=0;%��ʾ�ýڵ��Ƿ񱻼�֧
X(1,1:m)=x;
Lb(1,1:m)=lb;
Ub(1,1:m)=ub;

zB=0;zU=fval;%���½�
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









