#include <stdio.h>
#include <string.h>
#define MAXNUM 999999999
#define MAXVERTEX 100

int n,arcNum;//������������
int VS,VT;//����յ�
int C[MAXVERTEX][MAXVERTEX],F[MAXVERTEX][MAXVERTEX];//C,F�ֱ��¼N������������
int Cf[MAXVERTEX][MAXVERTEX];//ʣ������Ȩֵ
int LAM[MAXVERTEX],L[MAXVERTEX],X[MAXVERTEX];



void input() {
	int i;
	int u,v,cc;//����ʱ����ʱ����

	//freopen("MaximumFlow.in", "r", stdin);
	printf("�����붥�����n=");
	scanf("%d",&n);
	printf("�����뻡��arcNum=");
	scanf("%d",&arcNum);

	
	memset(C, 0, sizeof(C));//������ʼΪȫ0
	memset(F, 0, sizeof(F));//������ʼΪȫ0
	

	printf("��ֱ�����%d�����Ķ��㡢����:\n",arcNum);
	for (i=0;i<arcNum;i++) {
		scanf("%d %d %d",&u,&v,&cc);
		C[u][v]=cc;
	}


	printf("���Vs=");
	scanf("%d",&VS);
	printf("�յ�Vt=");
	scanf("%d",&VT);
}




/*����ʣ������*/
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
				Cf[i][j]=MAXNUM;//ȥ��Nf������ֵΪ0�����л�
}



/*���·����ʼ��*/
void shortestPathInitial() {
	int i;
	for (i=1;i<=n;i++) {
		X[i]=0; 
		LAM[i]=MAXNUM;
	}
	LAM[VS]=0;

	X[VS]=1;
	X[0]=1;//X[0]��¼X�����ж������,��ʼʱVs����X����	
	for (i=1;i<=n;i++) L[i]=0;
}


/*��(X)�Ƿ�Ϊ��?  ��:����0;��:����1*/
int PHi(int M[MAXVERTEX][MAXVERTEX]) {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[i][j]<MAXNUM)) return(1);
	return(0);
}

/*���·*/
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

/*�ı�N�е�����*/
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

/*���*/
void display() {
	int i,j,vf=0;
	printf("���������µ���Ϊ:\n");
	for(i=1;i<=n;i++) {
		for (j=1;j<=n;j++) printf("%4d",F[i][j]);
		printf("\n");
	}
	
	for(i=1;i<=n;i++) vf+=F[VS][i];
	printf("�������Ϊ:%d\n",vf);
}


void main() {  
	input();
	while (1) {
		buildNf();
		shortestPathInitial();//���·����ʼ��
		while (!X[VT] && PHi(Cf)) prim(Cf);
		if (X[VT]) changeFlow();
		else break;
	}
	display();	
}