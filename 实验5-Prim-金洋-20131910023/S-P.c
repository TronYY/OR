#include <stdio.h>
#define MAXNUM 999999999
#define MAXVERTEX 100

int M[MAXVERTEX][MAXVERTEX],X[MAXVERTEX],LAM[MAXVERTEX],L[MAXVERTEX][MAXVERTEX],n,VS,VT;


/*��(X)�Ƿ�Ϊ��?  ��:����0;��:����1*/
int PHi() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[i][j]<MAXNUM)) return(1);
	return(0);
}

void prim() {
	int i,j,min;
	int now[MAXVERTEX];//��ʾĳ�����Ƿ�����һ�ַ�Ȧ��ѡ��ʱ������X����; 

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
						L[j][i]=1;//��ʾ��(i,j)�п����������γɵ����·��
						
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
	printf("�����붥�����n=");
	scanf("%d",&n);
	printf("����������ͼ���ڽӾ���:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
			scanf("%d",&M[i][j]);
			if (M[i][j]==0) M[i][j]=MAXNUM;//û�б���������Ȩֵ��Ϊ�㹻��
		}
	printf("���Vs=");
	scanf("%d",&VS);
	printf("�յ�Vt=");
	scanf("%d",&VT);


	
	//X[0]=1;//X[0]��¼X�����ж������
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
		printf("�������·�����ɵ���ͼ�ı߼�Ϊ:\n");
		display(VT);
		printf("���·����Ϊ%d.\n",LAM[VT]);
	}
	else printf("��Vs��Vt���������·.\n");
}