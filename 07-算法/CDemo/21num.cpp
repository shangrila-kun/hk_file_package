#include<stdio.h>
#include<string.h> 
#define maxn 54
char ch[maxn];
int main() {
	int count = 0;//累加计数 
	gets(ch+2);
	
	int length = strlen(ch);//获取字符长度 
	for(int i=0;i<length;i++){	
		ch=ch+i;	
		if(ch!=','){
			if(ch=='2'||ch[i]=='3'||ch[i]=='4'||ch[i]=='5'||ch[i]=='6')
				count++;
			if(ch=='10'||ch[i]=='J'||ch[i]=='Q'||ch[i]=='K'||ch[i]=='A')
				count--; 
		}
	} 
	if(count>0){
		printf("%d %s \n",count,"Bet");	
	}else{
		printf("%d %s \n",count,"Hold");	
	}
	
}
