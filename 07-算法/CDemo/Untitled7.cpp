#include<stdio.h>
#define INF 1000000000
int main(){
	int num,start,value,min,max,i;//个数 ,起始值 
	double sum = 0;
	min = INF;max = -INF;i = 0;
	while(scanf("%d",&num)==1&&num){
			start=0;
			while(start<num){
				scanf("%d",&value);
				if(value>max) max = value;
				if(value<min) min = value;
				sum +=value; 
				++start; 
			}
			if(i)  printf("\n");
			printf("Case %d: %d %d %.3f\n",++i,min,max,sum/num);
		}
		return 0;
	}
