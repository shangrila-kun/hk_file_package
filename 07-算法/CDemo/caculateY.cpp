#include<stdio.h>
int main(){
	int i = 2;
	double sum = 2.0;
	int temp = 1;
	do{
		temp = temp*i;
		sum +=1.0/temp;
		++i; 
	}while((1.0/temp)>=1e-7);
	printf("%.7f\n",sum);
	return 0;
}
