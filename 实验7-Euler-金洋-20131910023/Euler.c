#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 999999999
#define MAXVERTEX 100

int M[MAXVERTEX][MAXVERTEX],X[MAXVERTEX],n;

int inEqualsOut() {
	int outdegree[MAXVERTEX],indegree[MAXVERTEX];
	int i,j;

	/*初始化*/
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
		if (outdegree[i]!=indegree[i]) return 0;//某顶点入度不等于出度，原图不是欧拉图；
	return 1;
}


/*X是否等于V   是:返回1;否:返回0*/
int equal() {
	//X[0]记录x集合中顶点个数
	return X[0]==n;
}



/* φ+(X)是否为空?  是:返回0;否:返回1*/
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



/* φ-(X)是否为空?  是:返回0;否:返回1*/
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

	//判断V1到其余顶点是否都有路
	X[1]=1;
	X[0]=1;
	for (i=2;i<=n;i++)  X[i]=0;
	while (!equal() && PHi_plus()) prim1();
	if (!equal()) return 0;

	//判断其余顶点到V1是否都有路
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
	printf("请输入D的顶点个数n=");
	scanf("%d",&n);
	printf("请输入D的邻接矩阵:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
			scanf("%d",&M[i][j]);
			if (M[i][j]==0) M[i][j]=MAXNUM;//没有边相连，将权值设为足够大
		}

	if (! inEqualsOut()) {
		printf("D不是有向欧拉图\n");
		exit(0);
	}

	if (stronglyConnected()) printf("D是有向欧拉图\n");
	else printf("D不是有向欧拉图\n");
}