#include <stdio.h>
#include <time.h>  
typedef struct{
	double avg;//ƽ��ֵ 
	double std;//��׼ֵ 
	double max;//���ֵ 
	double min;//��Сֵ 
}pwdata; 
typedef struct{
	time_t t;//ʱ�� 
	char pw[];//ͨ��
	pwdata *wind_speed;
	pwdata *wind_direction;
	pwdata *pressure;
	pwdata *temperature;
}data;
int main(){
	printf("hello11");
}
