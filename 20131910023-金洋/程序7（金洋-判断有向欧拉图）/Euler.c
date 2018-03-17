#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 999999999
#define MAXVERTEX 100

int M[MAXVERTEX][MAXVERTEX],X[MAXVERTEX],n;

int inEqualsOut() {
	int outdegree[MAXVERTEX],indegree[MAXVERTEX];
	int i,j;

	/*��ʼ��*/
	for (i=1;i<=n;i++) {
		outdegree[i]=0;
		indegree[i]=0;
	}
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
		   outdegree[i]+=M[i][j];
		   indegree[j]+=M[i][j];
		}

	for (i=1;i<=n;i++)
		if (outdegree[i]!=indegree[i]) return 0;//ĳ������Ȳ����ڳ��ȣ�ԭͼ����ŷ��ͼ��
	return 1;
}


/*X�Ƿ����V   ��:����1;��:����0*/
int equal() {
	//X[0]��¼x�����ж������
	return X[0]==n;
}



/* ��+(X)�Ƿ�Ϊ��?  ��:����0;��:����1*/
int PHi_plus() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[i][j]<MAXNUM)) return(1);
	return(0);
}
void prim1() {
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
	}
}



/* ��-(X)�Ƿ�Ϊ��?  ��:����0;��:����1*/
int PHi_minus() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[j][i]<MAXNUM)) return(1);
	return(0);
}
void prim2() {
	int i,j,min,x=0,y=0;
	min=MAXNUM;
	for(i=1;i<=n;i++)
		if (X[i])

		for(j=1;j<=n;j++)
			if ((!X[j])&&(i!=j))
				if (M[j][i]<min) {
					min=M[j][i];
					x=i;
					y=j;
				}
	if (min!=MAXNUM) {
		X[y]=1;
		X[0]++;
	}
}



int stronglyConnected() {
	int i;

	//�ж�V1�����ඥ���Ƿ���·
	X[1]=1;
	X[0]=1;
	for (i=2;i<=n;i++)  X[i]=0;
	while (!equal() && PHi_plus()) prim1();
	if (!equal()) return 0;

	//�ж����ඥ�㵽V1�Ƿ���·
	X[1]=1;
	X[0]=1;
	for (i=2;i<=n;i++)  X[i]=0;
	while (!equal() && PHi_minus()) prim2();
	if (!equal()) return 0;
	
	return 1;


}



void main() {  
	int i,j;
	//freopen("Euler.in", "r", stdin);
	printf("������D�Ķ������n=");
	scanf("%d",&n);
	printf("������D���ڽӾ���:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
			scanf("%d",&M[i][j]);
			if (M[i][j]==0) M[i][j]=MAXNUM;//û�б���������Ȩֵ��Ϊ�㹻��
		}

	if (! inEqualsOut()) {
		printf("D��������ŷ��ͼ\n");
		exit(0);
	}

	if (stronglyConnected()) printf("D������ŷ��ͼ\n");
	else printf("D��������ŷ��ͼ\n");
}