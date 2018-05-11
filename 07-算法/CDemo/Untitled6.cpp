#define LOCAL
#include<stdio.h>
#define INF 1000000000
#define path_in "in.txt"
#define path_out "out.txt"
int main(){
	#ifdef LOCAL
		freopen(path_in,"r",stdin);
		freopen(path_out,"w",stdout);
	#endif
	int x, n = 0,min = INF, max = -INF, s = 0;
	while (scanf("%d",&x)==1)
	{
		s += x;
		if(x < min) min = x;
		if(x > max) max = x;
		n++;
	}
	printf("%d %d %.3f\n", min, max, (double)s/n);
	return 0;
}
