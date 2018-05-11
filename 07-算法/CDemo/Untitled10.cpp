#include<stdio.h>
#include<string.h> 
#define MAX 100
int main(){
	char s[MAX];
	scanf("%s",s);
	//char a[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";//c语言特性，字符数组以/0结束。
	//int length = sizeof(a)-1;//求字符长度的实际长度 
	int length = strlen(s);
	printf("%d\n",length);
	for(int i=0;i<length;i++){
		for(int j=i;j<length+i;j++){
			int position = j%length; 
			printf("%c",s[position]);
		}
		printf("\n");
	}
	return 0; 
}
