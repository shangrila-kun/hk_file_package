#include <stdio.h>
#include <time.h>
int total;  
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
}Data;
int caculateI(int i,Data data);//��������ǿ�� 
int main(){
	
	
}
int caculateI(int i,Data data,int totalNum){
	switch(i){
		case 0:{
			
			break;
		}
		case 1:{
			
			break;
		}
	} 
}


