#include<stdio.h>
#include<string.h>
int main(){
	int n,x,y,hxnum;
	scanf("%d",&n);
	int a[n][n];
	memset(a,0,sizeof(a));
	x=0;y=n-1;hxnum=1;
	a[x][y] = hxnum;
	while(hxnum<n*n){
		while(x<n-1&&!a[x+1][y]){
			a[++x][y]=++hxnum;
			//printf("%d ",a[x][y]);
		}
		while(y>0&&!a[x][y-1]){
			a[x][--y]=++hxnum;
			//printf("%d ",a[x][y]);
		}
		while(x>0&&!a[x-1][y]){
			a[--x][y]=++hxnum;
			//printf("%d ",a[x][y]);
		}
		while(y<n-1&&!a[x][y+1]){
			a[x][++y]=++hxnum;
			//printf("%d ",a[x][y]);
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%3d ",a[i][j]);
		}
		printf("\n");
	}
}
