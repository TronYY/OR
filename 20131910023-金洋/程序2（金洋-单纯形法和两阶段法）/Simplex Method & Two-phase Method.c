#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define	 LENF sizeof(float)
#define	 LENINT sizeof(int)
#define MAX 1000000
int N;		//N 为决策变量个数
int NA;		//NA为加上人工变量后决策变量总个数
int M;		//M为约束条件数（不含非负条件），默认所有决策变量为非负
int	objType;//目标函数类型 1 for Max;0 for Min;
float *C;	//价值系数
float *C1;	//两阶段法第一阶段的价值系数
float **A;	//约束条件系数矩阵
float *b;	//约束条件限额系数
int *BASIS;	//储存基所在的列数
int *STATUS;//基变量状态,提示是否是基变量
float *SIGMA; //检验数σ
int DIRE[3];	//分别代表约束条件中<=,>=,=的条件个数


/*单纯形法初始化*/
void initSimplex() {
	int i,j;
	printf("\n\n");
	printf("请输入线性规划问题相关信息(已化为标准型,且已知初始基可行解基变量所在的列号):\n");	

	printf("请输入决策变量个数N=");
	scanf("%d",&N);
	printf("请输入约束条件(已默认所有决策变量为非负)个数M=");
	scanf("%d",&M);

	/*动态分配了数组C[N],目标函数价值系数*/
	C=(float*) malloc((N+1)*LENF);
	printf("请输入目标函数价值系数:\n");
	for (i=1;i<=N;i++) 
		scanf("%f",&C[i]);
	
	/*动态分配了数组A[M][N],约束条件系数*/
	A=(float**)malloc((M+1)*sizeof(float*)); //第一维 
	for(i=1;i<=M; i++)
		A[i]=(float*)malloc((N+1)* LENF);//第二维 
	printf("请输入约束条件系数:\n");
	for (i=1;i<=M;i++)
		for (j=1;j<=N;j++)
			scanf("%f",&A[i][j]);


	/*输入b*/
	b=(float*) malloc((M+1)*LENF);
	printf("请输入对应顺序的b:\n");
	for (i=1;i<=M;i++) scanf("%f",&b[i]);


	/*输入初始基可行解基变量所在的列号*/
	BASIS=(int*) malloc((M+1)*LENINT);
	STATUS=(int*) malloc((N+1)*LENINT);
	for (i=0;i<=N;i++) STATUS[i]=0;//初始时所有的变量都是非基变量
	printf("请输入初始基可行解基变量所在的列号:");
	for (i=1;i<=M;i++)	{
		scanf("%d",&BASIS[i]);
		STATUS[BASIS[i]]=i;
	}
	SIGMA=(float*) malloc((N+1)*LENF);
	
}

/*两阶段法初始化*/
void initTwoPhase() {
	int i,j,n;//n为初始时决策变量个数
	int kr;//剩余变量初始值
	int ka;//人工变量初始值
	printf("\n\n");
	printf("请输入线性规划问题初始相关信息:\n");	

	printf("请输入决策变量个数n=");
	scanf("%d",&n);

	printf("请输入约束条件(已默认所有决策变量为非负)个数M=");
	scanf("%d",&M);

	printf("请输入约束条件中\"<=\"类条件数:");
	scanf("%d",&DIRE[0]);
	printf("请输入约束条件中\">=\"类条件数:");
	scanf("%d",&DIRE[1]);
	printf("请输入约束条件中\"=\"类条件数:");
	scanf("%d",&DIRE[2]);

	N=n+DIRE[0]+DIRE[1];//原LP标准型下决策变量总个数
	NA=N+DIRE[1]+DIRE[2];//加入人工变量后决策变量总个数

	if (N==NA) {
		printf("输入形式的线性规划问题未产生人工变量，请变形后再用两阶段法求解.");
		exit (0);
	}

	/*此处不再要求初始输入为标准型，我们通过输入标准型，但通过程序将其化为标准型*/
	printf("请输入目标函数类型(1 for max、0 for min):");
	scanf("%d",&objType);

	C=(float*) malloc((N+1)*LENF);
	printf("请输入目标函数价值系数:\n");
	for (i=1;i<=n;i++) {
		scanf("%f",&C[i]);
		if (!objType) C[i]=-C[i];//当目标函数求min时，则转化为求max
	}
	for (i=n+1;i<=N;i++) C[i]=0;
	

	A=(float**)malloc((M+1)*sizeof(float*)); //第一维 
	for(i=1;i<=M; i++)
		A[i]=(float*)malloc((NA+1)* LENF);//第二维 
	BASIS=(int*) malloc((M+1)*LENINT);
	STATUS=(int*) malloc((NA+1)*LENINT);
	for (i=0;i<=NA;i++) STATUS[i]=0;//初始时所有的变量都是非基变量
	
	/* 开辟第一阶段的价值系数矩阵C1,并化成max型 */
	C1=(float*) malloc((NA+1)*LENF);
	for (i=1;i<=NA;i++) C1[i]=0;

	kr=n+1;//剩余变量下标初始值
	ka=N+1;//人工变量下标初始值
	
	for (i=1;i<=DIRE[0];i++){
		printf("请输入第%d个\"<=\"条件的相关系数:",i);
		for (j=1;j<=n;j++) scanf("%f",&A[i][j]);
		for (;j<=NA;j++) A[i][j]=0;
		A[i][kr]=1;//剩余变量
		STATUS[kr]=i;//该剩余变量加入基
		BASIS[i]=kr;
		kr++;
	}
	for (;i<=DIRE[0]+DIRE[1];i++){
		printf("请输入第%d个\">=\"条件的相关系数:",i-DIRE[0]);
		for (j=1;j<=n;j++) scanf("%f",&A[i][j]);
		for (;j<=NA;j++) A[i][j]=0;
		A[i][kr]=-1;//剩余变量
		A[i][ka]=1;//人工变量
		C1[ka]=-1;
		STATUS[ka]=i;//人工变量做基变量
		BASIS[i]=ka;
		kr++;
		ka++;
	}
	for (;i<=M;i++){
		printf("请输入第%d个\"=\"条件的相关系数:",i-DIRE[0]-DIRE[1]);
		for (j=1;j<=n;j++) scanf("%f",&A[i][j]);
		for (;j<=NA;j++) A[i][j]=0;
	
		A[i][ka]=1;//人工变量
		C1[ka]=-1;
		STATUS[ka]=i;//人工变量做基变量
		BASIS[i]=ka;
		ka++;
	}

	/*输入b*/
	b=(float*) malloc((M+1)*LENF);
	printf("请输入对应顺序的b:\n");
	for (i=1;i<=M;i++) scanf("%f",&b[i]);

	SIGMA=(float*) malloc((NA+1)*LENF);
	
}


/*输出标准型*/
void output(float *C,int n) {
	int i,j;
	
	
	printf("Max Z=%0.1fX%d",C[1],1);
	for (i=2;i<=n;i++)
		printf("%+0.1fX%d",C[i],i);
	printf("\n");
	
	for (i=1;i<=M;i++) {
		printf("%0.1fX%d",A[i][1],1);
		for (j=2;j<=n;j++) 
			printf("%+0.1fX%d",A[i][j],j);
		printf("=%.1f\n",b[i]);
	
	}	
	for (j=1;j<=n-1;j++) printf("X%d,",j);
	printf("X%d>=0\n",n);
}


/* 计算目标函数值CN*b */
float computeObj(float *C,int n) {
	float z=0;
	int i;

	for (i=1;i<=M;i++)
		z+=C[BASIS[i]]*b[i];
	return z;
}



/*输出解*/
void displaySolution(float *C,int n) {
	int i;
	for (i=1;i<=n;i++){
		printf("X%d=",i);
		if (STATUS[i]==0) 
			printf("0\n");
		else 
			printf("%0.1f\n",b[STATUS[i]]);

	}
	printf("Max z=%0.1f\n",computeObj(C,n));

}



/*计算所有σ*/
void computeSigma(float *C,int n) {
	int i,j;
	float sum;
	for (i=1;i<=n;i++) 
		if (STATUS[i]>0) {
			SIGMA[i]=0;
			continue;
		}
		else {
			sum=0;
			for (j=1;j<=M;j++) 
				sum+=C[BASIS[j]]*A[j][i];
			SIGMA[i]=C[i]-sum;
		}
	
}




/*基变量中是否有非零的人工变量*/
int nonZeroArtiVarInBasis(int m,int n) {
	int i;
	for (i=1;i<=M;i++)
		if (BASIS[i]>m && fabs(b[i])>=1e-7) return 1;
	return 0;

}



/*判断是否存在某非基变量检验数为0;  存在:返回1   不存在:返回0*/
int existNonbasisEqus0(int n) {
	int i;
	for (i=1;i<=n;i++)
		if (STATUS[i]==0 && fabs(SIGMA[i])<1e-7)
			return 1;
	return 0;
}




/* 单纯形法 C:目标函数价值系数; m:非人工变量个数 n:决策变量总个数*/
int simplex(float *C,int m,int n) {
	int i,j,flag,k,l;
	float theta,t;
	float pivot;//主元素


	while (1) {
		computeSigma(C,n);
		

		for (i=1;i<=n;i++) {
			if (SIGMA[i]>=1e-7) break; //存在σi>0
		}

		k=i;




		/*所有σ<=0*/
		if (i==(n+1))
			/*无可行解，结束程序*/
			if (nonZeroArtiVarInBasis(m,n)) {
				printf("无可行解\n");
				return 0;
			}
			/*无穷多最优解，结束程序
			else if (existNonbasisEqus0(n)){
				printf("无穷多最优解,其中一组解如下:\n");
				displaySolution(C,n);
				return 1;
			}*/
			/*唯一最优解，结束程序*/
			else {
				printf("有最优解:\n");
				displaySolution(C,n);
				return 1;
			}

	


		/*检验是否有无界解*/
		flag=0;
		for (;i<=n;i++) {
			if (SIGMA[i]>=1e-7) {
				for (j=1;j<=M;j++)
					if (A[j][i]>=1e-7) break;
				if (j==M+1) {
					flag=1;
					
				}	
			}
			if (flag==1) {
				printf("有无界解\n");
				return 0;	
			}
		}




		/*计算θ*/
		l=0;
		theta=MAX;
		for (i=1;i<=M;i++) 
			if (A[i][k]>=1e-7) {
				t=b[i]/A[i][k];
				if (t<theta) {
					theta=t;
					l=i;
				}
			}



		
		/*  xk为换入变量,l行对应的基变量为换出变量  */
		STATUS[BASIS[l]]=0;
		STATUS[k]=l;
		BASIS[l]=k;

		/*旋转运算*/
	
		pivot=A[l][k];
		b[l]=b[l]/pivot;
		for (j=1;j<=n;j++) A[l][j]=A[l][j]/pivot;//第l行操作
		for (i=1;i<=M;i++) 
			if (i!=l) {
				float pivot2=A[i][k];
				for (j=1;j<=n;j++) A[i][j]=-A[l][j]*pivot2+A[i][j];
				b[i]=-b[l]*pivot2+b[i];
			}
	}
			
}


void release() {
	free(A);
	free(C);
	free(b);
	free(BASIS);
	free(STATUS);
	free(SIGMA);
	
}


void main() {
	int choice;
	int firstPhase;

	//freopen("Two-phase.in", "r", stdin);
	//freopen("2.in", "r", stdin);
	printf("1.单纯形法\n2.两阶段法\n");
	printf("请选择解LP的方法:");
	scanf("%d",&choice);
	
	if (choice==1) {
		initSimplex();
		printf("\n标准型如下:\n");
		output(C,N);
		simplex(C,N,N);
	}

	else if (choice==2){
		initTwoPhase();
		printf("\n初始标准型如下:\n");
		output(C,N);

		printf("加入人工变量后,第一阶段标准型如下:\n");
		output(C1,NA);

		printf("\n第一阶段求解:\n");
		firstPhase=simplex(C1,N,NA);

		if (firstPhase) {
			printf("\n第二阶段求解:\n");
			simplex(C,N,N);
		}
		else printf("即原LP无可行解\n");
		

	}

	//fclose(stdin);
	release();  //代码中为了节省空间，使用了几个动态数组，按照规范，动态数组使用完毕需要释放	

}