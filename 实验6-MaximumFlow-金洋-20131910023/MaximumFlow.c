#include <stdio.h>
#include <string.h>
#define MAXNUM 999999999
#define MAXVERTEX 100

int n,arcNum;//顶点数、弧数
int VS,VT;//起点终点
int C[MAXVERTEX][MAXVERTEX],F[MAXVERTEX][MAXVERTEX];//C,F分别记录N的容量、流量
int Cf[MAXVERTEX][MAXVERTEX];//剩余网络权值
int LAM[MAXVERTEX],L[MAXVERTEX],X[MAXVERTEX];



void input() {
	int i;
	int u,v,cc;//输入时的临时变量

	//freopen("MaximumFlow.in", "r", stdin);
	printf("请输入顶点个数n=");
	scanf("%d",&n);
	printf("请输入弧数arcNum=");
	scanf("%d",&arcNum);

	
	memset(C, 0, sizeof(C));//容量初始为全0
	memset(F, 0, sizeof(F));//流量初始为全0
	

	printf("请分别输入%d条弧的顶点、容量:\n",arcNum);
	for (i=0;i<arcNum;i++) {
		scanf("%d %d %d",&u,&v,&cc);
		C[u][v]=cc;
	}


	printf("起点Vs=");
	scanf("%d",&VS);
	printf("终点Vt=");
	scanf("%d",&VT);
}




/*构造剩余网络*/
void buildNf() {
	int i,j;

	memset(Cf, 0, sizeof(Cf));
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			if (C[i][j]) {
				Cf[i][j]=C[i][j]-F[i][j];
				Cf[j][i]=F[i][j];
		}
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (Cf[i][j]==0) 
				Cf[i][j]=MAXNUM;//去掉Nf中容量值为0的所有弧
}



/*最短路径初始化*/
void shortestPathInitial() {
	int i;
	for (i=1;i<=n;i++) {
		X[i]=0; 
		LAM[i]=MAXNUM;
	}
	LAM[VS]=0;

	X[VS]=1;
	X[0]=1;//X[0]记录X集合中顶点个数,初始时Vs进入X集合	
	for (i=1;i<=n;i++) L[i]=0;
}


/*φ(X)是否为空?  是:返回0;否:返回1*/
int PHi(int M[MAXVERTEX][MAXVERTEX]) {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[i][j]<MAXNUM)) return(1);
	return(0);
}

/*最短路*/
void prim(int M[MAXVERTEX][MAXVERTEX]) {
	int i,j,min;
	int x,y;
	
	min=MAXNUM;

	for(i=1;i<=n;i++)
		if (X[i])
			for(j=1;j<=n;j++)
				if (!X[j]  && i!=j && LAM[i]+M[i][j]<min ) {
					min=LAM[i]+M[i][j];
					x=i;
					y=j;
				}					
	if (min!=MAXNUM) {		
		X[y]=1;
		X[0]++;
		L[y]=x;
		LAM[y]=min;
	}
}

/*改变N中的流量*/
void changeFlow() {
	int theta=MAXNUM;
	int y=VT;
	while (L[y]!=0) {
		if (theta>Cf[L[y]][y] ) theta=Cf[L[y]][y];
		if (theta>Cf[y][L[y]] ) theta=Cf[y][L[y]];
		y=L[y];	
	}

	y=VT;
	while (L[y]!=0) {
		if (F[L[y]][y]<C[L[y]][y]) F[L[y]][y]+=theta;
		if (F[y][L[y]]>0) F[y][L[y]]-=theta;
		y=L[y];
	}
}

/*输出*/
void display() {
	int i,j,vf=0;
	printf("最大流情况下的流为:\n");
	for(i=1;i<=n;i++) {
		for (j=1;j<=n;j++) printf("%4d",F[i][j]);
		printf("\n");
	}
	
	for(i=1;i<=n;i++) vf+=F[VS][i];
	printf("最大流量为:%d\n",vf);
}


void main() {  
	input();
	while (1) {
		buildNf();
		shortestPathInitial();//最短路径初始化
		while (!X[VT] && PHi(Cf)) prim(Cf);
		if (X[VT]) changeFlow();
		else break;
	}
	display();	
}