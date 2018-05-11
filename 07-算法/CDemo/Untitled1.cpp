#include <stdio.h>
#include <time.h>  
typedef struct{
	double avg;//平均值 
	double std;//标准值 
	double max;//最大值 
	double min;//最小值 
}pwdata; 
typedef struct{
	time_t t;//时间 
	char pw[];//通道
	pwdata *wind_speed;
	pwdata *wind_direction;
	pwdata *pressure;
	pwdata *temperature;
}data;
int main(){
	printf("hello11");
}
