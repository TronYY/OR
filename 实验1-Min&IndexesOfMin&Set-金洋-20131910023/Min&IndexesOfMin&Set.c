#include <stdio.h>
#include <math.h>
#define MAXNUM 10000
#define MAX 1000000
void main() {
	float a[MAXNUM],b[MAXNUM],c[MAXNUM],min;
	int i,indexOfMin,n,indexNum,index[MAXNUM];

	/*Input*/
	printf("Please input n:");
	scanf("%d",&n);

	printf("Please enter the array a:\n");
	for(i=1;i<=n;i++)
		scanf("%f",&a[i]);
	printf("Please enter the array b:\n");
	for(i=1;i<=n;i++)
		scanf("%f",&b[i]);
	
	/*Calculate*/
	for(i=1;i<=n;i++) {
		if ( fabs(b[i])<1e-7 ) //判断b[i]==0? 考虑到浮点类型的精度问题，使用绝对值与10^-7比较
			c[i]=MAX;
		else
			c[i]=a[i]/b[i];
	}

	min=MAX;
	indexOfMin=0;
	for(i=1;i<=n;i++) {
		if (c[i]<min) {
			min=c[i];
			indexOfMin=i;
		}
	}

	indexNum=1;
	index[indexNum]=indexOfMin;
	for(i=indexOfMin+1;i<=n;i++) {
		if (c[i]==min) {
			indexNum++;
			index[indexNum]=i;
		}
	}

	/*Output*/
	printf("The oiginal data:a,b,c\n");
	for (i=1;i<=n;i++) {
		printf("%3d:%16.2f,%16.2f,%16.2f\n",i,a[i],b[i],c[i]);//输出结果保留两位小数
	}
	printf("\nThe minimum is %16.2f\n",min);
	printf("The indexes of minimum: ");
	for (i=1;i<=indexNum;i++)
		printf("%d ",index[i]);
	printf("\n");
}