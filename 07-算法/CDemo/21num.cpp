#include<stdio.h>
#include<string.h> 
#define maxn 54
char ch[maxn];
int main() {
	int count = 0;//ÀÛ¼Ó¼ÆÊý 
	gets(ch);	
	printf("%d\n",length);
	for(int i=0;i<length;i++){		
		if(ch[i]!=','){
			if(ch[i]=='2'||ch[i]=='3'||ch[i]=='4'||ch[i]=='5'||ch[i]=='6')
				count++;
			if(ch[i]=='10'||ch[i]=='J'||ch[i]=='Q'||ch[i]=='K'||ch[i]=='A')
				count--; 
		}
	} 
	if(count>0){
		printf("%d %s \n",count,"Bet");	
	}else{
		printf("%d %s \n",count,"Hold");	
	}
	return 0;
	
	
}
