#include<stdio.h>
#define MAXVERTEX 100

void main() {
	int M[MAXVERTEX][MAXVERTEX],outdegree[MAXVERTEX],indegree[MAXVERTEX];
	int i,j,n;

	//freopen("Outdegree&Indegree.in", "r", stdin);
	printf("�����붥�����n=");
	scanf("%d",&n);


	/*��ʼ��*/
	for (i=1;i<=n;i++) {
		outdegree[i]=0;
		indegree[i]=0;
	}



	printf("����������ͼ���ڽӾ���:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
		   scanf("%d",&M[i][j]);
		   outdegree[i]+=M[i][j];
		   indegree[j]+=M[i][j];
		}

	
	printf("	Outdegree	Indegree\n");
	for (i=1;i<=n;i++)
		printf("%d	%8d	%8d\n",i,outdegree[i],indegree[i]);  


}