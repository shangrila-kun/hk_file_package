#include<stdio.h>
#include<string.h>
#define maxn 100
int left,chance;
char s[maxn],s2[maxn];
int win,lose;
void guess(char ch){
	int bad = 1;
	for(int i=0;i < strlen(s);i++){
		if(s[i] == ch){
			left--;
			s[i] = ' ';
			bad = 0;
		}
		if(bad) --chance;
		if(!chance) lose = 1;
		if(!left) win = 1; 
	}
}
	int main(){
		int rnd;
		while(scanf("%d%s%s",&rnd,s,s2)==3 && rnd != -1){
			printf("Round %d \n",rnd);
			win = lose = 0;//求一组新数据之前要初始化
			left = strlen(s);
			chance = 7;
			for(int i = 0;i < strlen(s2);i++){
				guess(s2[i]);//猜一个字母
				if(win||lose) break;//检查状态 
			} 
			if(win) printf("you win \n");
			else if(lose) printf("you lose \n");
			else printf("you chickened out .\n");
		}
		return 0;
	}

