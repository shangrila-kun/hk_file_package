#include<stdio.h>
#include<string.h> 
#define MAX 100
int main(){
	char s[MAX];
	scanf("%s",s);
	//char a[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";//c�������ԣ��ַ�������/0������
	//int length = sizeof(a)-1;//���ַ����ȵ�ʵ�ʳ��� 
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
