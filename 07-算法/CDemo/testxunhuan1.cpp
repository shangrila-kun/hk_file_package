#include<stdio.h>
#include<time.h> 
int main(){
	long sum = 0;
	int n;
	long factorial;
	int i = 1;
	scanf("%d",&n);
	do{
		factorial = 1;//ÿִ��һ��ѭ���壬��Ҫ������������ʼ���� 
		for(int j = 1;j<=i;j++){
			factorial*= j;
		}
		sum+=factorial;
	}while(++i<=n&&n<=1000000);
	printf("%ld\n",sum);
	printf("Time used =%.2f\n",(double)clock()/CLOCKS_PER_SEC);
	return 0; 
}
