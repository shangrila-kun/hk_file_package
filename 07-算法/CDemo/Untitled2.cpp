#include <stdio.h>  
#include <time.h>  
  
int main(int argc, const char * argv[])  
{  
    time_t t;  
    struct tm *p;  
    t=1384936600;  
    p=gmtime(&t);  
    char s[100];  
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", p);  
    printf("%d: %s\n", (int)t, s);  
    return 0;  
}  


