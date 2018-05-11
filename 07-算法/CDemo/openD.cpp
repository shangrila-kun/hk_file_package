#include<stdio.h>
#include<string.h>
#define maxn 1010
int a[maxn];
int main(){
    memset(a,0,sizeof(a));//Êı×éaÖÃÎª0
    int p,t,first;
    first = 0;
    scanf("%d%d",&t,&p);
    for(int i=1;i<=p;i++){
	for(int j=1;j<=t;j++){
	    if(j%i==0){
		a[j] = !a[j];
	    }
	}
    }
    for(int i=1;i<=t;i++){
    	if(a[i]){
    		if(first){
    			printf(" ");
	    		printf("%d",i);	
    		}else{
    			first=1;
	    		printf("%d",i);
    		}
    	}
    }
    return 0;
}
