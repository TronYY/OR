#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define	 LENF sizeof(float)
#define	 LENINT sizeof(int)
#define MAX 1000000
int N;		//N Ϊ���߱�������
int NA;		//NAΪ�����˹���������߱����ܸ���
int M;		//MΪԼ���������������Ǹ���������Ĭ�����о��߱���Ϊ�Ǹ�
int	objType;//Ŀ�꺯������ 1 for Max;0 for Min;
float *C;	//��ֵϵ��
float *C1;	//���׶η���һ�׶εļ�ֵϵ��
float **A;	//Լ������ϵ������
float *b;	//Լ�������޶�ϵ��
int *BASIS;	//��������ڵ�����
int *STATUS;//������״̬,��ʾ�Ƿ��ǻ�����
float *SIGMA; //��������
int DIRE[3];	//�ֱ����Լ��������<=,>=,=����������


/*�����η���ʼ��*/
void initSimplex() {
	int i,j;
	printf("\n\n");
	printf("���������Թ滮���������Ϣ(�ѻ�Ϊ��׼��,����֪��ʼ�����н���������ڵ��к�):\n");	

	printf("��������߱�������N=");
	scanf("%d",&N);
	printf("������Լ������(��Ĭ�����о��߱���Ϊ�Ǹ�)����M=");
	scanf("%d",&M);

	/*��̬����������C[N],Ŀ�꺯����ֵϵ��*/
	C=(float*) malloc((N+1)*LENF);
	printf("������Ŀ�꺯����ֵϵ��:\n");
	for (i=1;i<=N;i++) 
		scanf("%f",&C[i]);
	
	/*��̬����������A[M][N],Լ������ϵ��*/
	A=(float**)malloc((M+1)*sizeof(float*)); //��һά 
	for(i=1;i<=M; i++)
		A[i]=(float*)malloc((N+1)* LENF);//�ڶ�ά 
	printf("������Լ������ϵ��:\n");
	for (i=1;i<=M;i++)
		for (j=1;j<=N;j++)
			scanf("%f",&A[i][j]);


	/*����b*/
	b=(float*) malloc((M+1)*LENF);
	printf("�������Ӧ˳���b:\n");
	for (i=1;i<=M;i++) scanf("%f",&b[i]);


	/*�����ʼ�����н���������ڵ��к�*/
	BASIS=(int*) malloc((M+1)*LENINT);
	STATUS=(int*) malloc((N+1)*LENINT);
	for (i=0;i<=N;i++) STATUS[i]=0;//��ʼʱ���еı������Ƿǻ�����
	printf("�������ʼ�����н���������ڵ��к�:");
	for (i=1;i<=M;i++)	{
		scanf("%d",&BASIS[i]);
		STATUS[BASIS[i]]=i;
	}
	SIGMA=(float*) malloc((N+1)*LENF);
	
}

/*���׶η���ʼ��*/
void initTwoPhase() {
	int i,j,n;//nΪ��ʼʱ���߱�������
	int kr;//ʣ�������ʼֵ
	int ka;//�˹�������ʼֵ
	printf("\n\n");
	printf("���������Թ滮�����ʼ�����Ϣ:\n");	

	printf("��������߱�������n=");
	scanf("%d",&n);

	printf("������Լ������(��Ĭ�����о��߱���Ϊ�Ǹ�)����M=");
	scanf("%d",&M);

	printf("������Լ��������\"<=\"��������:");
	scanf("%d",&DIRE[0]);
	printf("������Լ��������\">=\"��������:");
	scanf("%d",&DIRE[1]);
	printf("������Լ��������\"=\"��������:");
	scanf("%d",&DIRE[2]);

	N=n+DIRE[0]+DIRE[1];//ԭLP��׼���¾��߱����ܸ���
	NA=N+DIRE[1]+DIRE[2];//�����˹���������߱����ܸ���

	if (N==NA) {
		printf("������ʽ�����Թ滮����δ�����˹�����������κ��������׶η����.");
		exit (0);
	}

	/*�˴�����Ҫ���ʼ����Ϊ��׼�ͣ�����ͨ�������׼�ͣ���ͨ�������仯Ϊ��׼��*/
	printf("������Ŀ�꺯������(1 for max��0 for min):");
	scanf("%d",&objType);

	C=(float*) malloc((N+1)*LENF);
	printf("������Ŀ�꺯����ֵϵ��:\n");
	for (i=1;i<=n;i++) {
		scanf("%f",&C[i]);
		if (!objType) C[i]=-C[i];//��Ŀ�꺯����minʱ����ת��Ϊ��max
	}
	for (i=n+1;i<=N;i++) C[i]=0;
	

	A=(float**)malloc((M+1)*sizeof(float*)); //��һά 
	for(i=1;i<=M; i++)
		A[i]=(float*)malloc((NA+1)* LENF);//�ڶ�ά 
	BASIS=(int*) malloc((M+1)*LENINT);
	STATUS=(int*) malloc((NA+1)*LENINT);
	for (i=0;i<=NA;i++) STATUS[i]=0;//��ʼʱ���еı������Ƿǻ�����
	
	/* ���ٵ�һ�׶εļ�ֵϵ������C1,������max�� */
	C1=(float*) malloc((NA+1)*LENF);
	for (i=1;i<=NA;i++) C1[i]=0;

	kr=n+1;//ʣ������±��ʼֵ
	ka=N+1;//�˹������±��ʼֵ
	
	for (i=1;i<=DIRE[0];i++){
		printf("�������%d��\"<=\"���������ϵ��:",i);
		for (j=1;j<=n;j++) scanf("%f",&A[i][j]);
		for (;j<=NA;j++) A[i][j]=0;
		A[i][kr]=1;//ʣ�����
		STATUS[kr]=i;//��ʣ����������
		BASIS[i]=kr;
		kr++;
	}
	for (;i<=DIRE[0]+DIRE[1];i++){
		printf("�������%d��\">=\"���������ϵ��:",i-DIRE[0]);
		for (j=1;j<=n;j++) scanf("%f",&A[i][j]);
		for (;j<=NA;j++) A[i][j]=0;
		A[i][kr]=-1;//ʣ�����
		A[i][ka]=1;//�˹�����
		C1[ka]=-1;
		STATUS[ka]=i;//�˹�������������
		BASIS[i]=ka;
		kr++;
		ka++;
	}
	for (;i<=M;i++){
		printf("�������%d��\"=\"���������ϵ��:",i-DIRE[0]-DIRE[1]);
		for (j=1;j<=n;j++) scanf("%f",&A[i][j]);
		for (;j<=NA;j++) A[i][j]=0;
	
		A[i][ka]=1;//�˹�����
		C1[ka]=-1;
		STATUS[ka]=i;//�˹�������������
		BASIS[i]=ka;
		ka++;
	}

	/*����b*/
	b=(float*) malloc((M+1)*LENF);
	printf("�������Ӧ˳���b:\n");
	for (i=1;i<=M;i++) scanf("%f",&b[i]);

	SIGMA=(float*) malloc((NA+1)*LENF);
	
}


/*�����׼��*/
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


/* ����Ŀ�꺯��ֵCN*b */
float computeObj(float *C,int n) {
	float z=0;
	int i;

	for (i=1;i<=M;i++)
		z+=C[BASIS[i]]*b[i];
	return z;
}



/*�����*/
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



/*�������Ц�*/
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




/*���������Ƿ��з�����˹�����*/
int nonZeroArtiVarInBasis(int m,int n) {
	int i;
	for (i=1;i<=M;i++)
		if (BASIS[i]>m && fabs(b[i])>=1e-7) return 1;
	return 0;

}



/*�ж��Ƿ����ĳ�ǻ�����������Ϊ0;  ����:����1   ������:����0*/
int existNonbasisEqus0(int n) {
	int i;
	for (i=1;i<=n;i++)
		if (STATUS[i]==0 && fabs(SIGMA[i])<1e-7)
			return 1;
	return 0;
}




/* �����η� C:Ŀ�꺯����ֵϵ��; m:���˹��������� n:���߱����ܸ���*/
int simplex(float *C,int m,int n) {
	int i,j,flag,k,l;
	float theta,t;
	float pivot;//��Ԫ��


	while (1) {
		computeSigma(C,n);
		

		for (i=1;i<=n;i++) {
			if (SIGMA[i]>=1e-7) break; //���ڦ�i>0
		}

		k=i;




		/*���Ц�<=0*/
		if (i==(n+1))
			/*�޿��н⣬��������*/
			if (nonZeroArtiVarInBasis(m,n)) {
				printf("�޿��н�\n");
				return 0;
			}
			/*��������Ž⣬��������
			else if (existNonbasisEqus0(n)){
				printf("��������Ž�,����һ�������:\n");
				displaySolution(C,n);
				return 1;
			}*/
			/*Ψһ���Ž⣬��������*/
			else {
				printf("�����Ž�:\n");
				displaySolution(C,n);
				return 1;
			}

	


		/*�����Ƿ����޽��*/
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
				printf("���޽��\n");
				return 0;	
			}
		}




		/*�����*/
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



		
		/*  xkΪ�������,l�ж�Ӧ�Ļ�����Ϊ��������  */
		STATUS[BASIS[l]]=0;
		STATUS[k]=l;
		BASIS[l]=k;

		/*��ת����*/
	
		pivot=A[l][k];
		b[l]=b[l]/pivot;
		for (j=1;j<=n;j++) A[l][j]=A[l][j]/pivot;//��l�в���
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
	printf("1.�����η�\n2.���׶η�\n");
	printf("��ѡ���LP�ķ���:");
	scanf("%d",&choice);
	
	if (choice==1) {
		initSimplex();
		printf("\n��׼������:\n");
		output(C,N);
		simplex(C,N,N);
	}

	else if (choice==2){
		initTwoPhase();
		printf("\n��ʼ��׼������:\n");
		output(C,N);

		printf("�����˹�������,��һ�׶α�׼������:\n");
		output(C1,NA);

		printf("\n��һ�׶����:\n");
		firstPhase=simplex(C1,N,NA);

		if (firstPhase) {
			printf("\n�ڶ��׶����:\n");
			simplex(C,N,N);
		}
		else printf("��ԭLP�޿��н�\n");
		

	}

	//fclose(stdin);
	release();  //������Ϊ�˽�ʡ�ռ䣬ʹ���˼�����̬���飬���չ淶����̬����ʹ�������Ҫ�ͷ�	

}