#include <stdio.h>
#define MAXNUM 999999999
#define MAXVERTEX 100

int M[MAXVERTEX][MAXVERTEX],X[MAXVERTEX],LAM[MAXVERTEX],L[MAXVERTEX][MAXVERTEX],n,VS,VT;


/*φ(X)是否为空?  是:返回0;否:返回1*/
int PHi() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[i][j]<MAXNUM)) return(1);
	return(0);
}

void prim() {
	int i,j,min;
	int now[MAXVERTEX];//表示某顶点是否在这一轮反圈中选边时被加入X集合; 

	for (i=1;i<=n;i++) now[i]=0;
	min=MAXNUM;

	for(i=1;i<=n;i++)
		if (X[i])
			for(j=1;j<=n;j++)
				if (!X[j]  && i!=j && LAM[i]+M[i][j]<min )
					min=LAM[i]+M[i][j];
					
	if (min!=MAXNUM) {
		
		for(i=1;i<=n;i++)
			if (X[i])
				for(j=1;j<=n;j++)
					if ( (!X[j] || now[j]) && i!=j && LAM[i]+M[i][j]==min ) {
						LAM[j]=min;
						X[j]=1;
						now[j]=1;
						//X[0]++;
						L[j][i]=1;//表示弧(i,j)有可能在最终形成的最短路上
						
					}	
	}
}


int display(int v) {
	int i;
	if (v==VS) return 0;
	for (i=1;i<=n;i++) 
		if (L[v][i]) {
			display(i);
			printf("(%d,%d)\n",i,v);
		}
	return 0;
}


void main() {  
	int i,j;
	//freopen("S-P.in", "r", stdin);
	printf("请输入顶点个数n=");
	scanf("%d",&n);
	printf("请输入有向图的邻接矩阵:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
			scanf("%d",&M[i][j]);
			if (M[i][j]==0) M[i][j]=MAXNUM;//没有边相连，将权值设为足够大
		}
	printf("起点Vs=");
	scanf("%d",&VS);
	printf("终点Vt=");
	scanf("%d",&VT);


	
	//X[0]=1;//X[0]记录X集合中顶点个数
	for (i=1;i<=n;i++) {
		X[i]=0; 
		LAM[i]=MAXNUM;
	}
	X[VS]=1;
	LAM[VS]=0;
	
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			L[i][j]=0;

	

   
	while (!X[VT] && PHi()) prim();

	if (X[VT]) {
		printf("所有最短路径构成的子图的边集为:\n");
		display(VT);
		printf("最短路径长为%d.\n",LAM[VT]);
	}
	else printf("从Vs到Vt不存在最短路.\n");
}