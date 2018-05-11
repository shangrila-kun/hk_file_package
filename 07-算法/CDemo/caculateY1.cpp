#include"stdio.h"
int main()
{
int i=2,s=1;
double e=2;
while(1.0/s>1e-7)
{
s=s*i;
e=e+1.0/s;
i++;
}
printf("%lf ",e);
}
