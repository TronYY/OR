#include <stdio.h>
#define MAXNUM 999999999
#define MAXVERTEX 100

int M[MAXVERTEX][MAXVERTEX],X[MAXVERTEX],F[2][MAXVERTEX],n,Fnum,SUM;

/*X�Ƿ����V   ��:����1;��:����0*/
int equal() {
	//X[0]��¼x�����ж������
	return X[0]==n;
}

/*��(X)�Ƿ�Ϊ��?  ��:����0;��:����1*/
int PHi() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[i][j]<MAXNUM)) return(1);
	return(0);
}

void prim() {
	int i,j,min,x=0,y=0;
	min=MAXNUM;
	for(i=1;i<=n;i++)
		if (X[i])

		for(j=1;j<=n;j++)
			if ((!X[j])&&(i!=j))
				if (M[i][j]<min) {
					min=M[i][j];
					x=i;
					y=j;
				}
	if (min!=MAXNUM) {
		X[y]=1;
		X[0]++;
		Fnum++;
		F[0][Fnum]=x;
		F[1][Fnum]=y;
		SUM=SUM+min;
	}
}

void main() {  
	int i,j;
	//freopen("MST.in", "r", stdin);
	printf("�����붥�����n=");
	scanf("%d",&n);
	printf("�������ڽӾ���:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
			scanf("%d",&M[i][j]);
			if (M[i][j]==0) M[i][j]=MAXNUM;//û�б���������Ȩֵ��Ϊ�㹻��
		}

	X[1]=1;
	X[0]=1;//X[0]��¼x�����ж������
	for (i=2;i<=n;i++) X[i]=0; 
   
	while (!equal() && PHi()) prim();

	if (equal()) {
		printf("MST�ı߼�Ϊ:\n");
		for(i=1;i<=Fnum;i++)
			printf("[%d,%d]\n",F[0][i],F[1][i]);//���MST�ı߼���
		printf("The total weight is %d.\n",SUM);
	}
	else printf("G is not connected.\n");
}