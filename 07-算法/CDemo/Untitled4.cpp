/*Produce 1 examdata */
INPUT��data//���������
OUTPUT��data1  //���������Ĳ��������
for time to data.timestamp1 to data.timestamp2

	if(data.sixValue!=null){//������ʱ�����в��� 
		time+=10;
	}
    if(data.Allvalue==null){//����ʱ�����в��� 
		data.timestamp=time;
		time+=10;
	}
return data1

/*Produce 2 getIbytimestamp*/
INPUT: data1 ,I0 ,timestamp1,timestamp2,height
OUTPUT: I//����ǿ�� 
int dataNum = 0;		
doblue avg_speed =0.0,speed = 0.0,temp = 0.0,I = 0.0;
for(int time =timestamp1;time<timestamp2;time+10){
			if(data1.std!=null){
				speed+=data1.speed;
				++dataNum;
			}
		}
		avg_speed=speed/dataNum;
		for(int time =timestamp1;time<timestamp2;time+10){
			if(data1.std!=null){
				temp += (data1.speed-avg_speed)*(data1.speed-avg_speed);
			}
		}
I=sqrt(temp/dataNum);
return I;

/*Produce 3 getHourAvgI*/

INPUT: data1 ,I0 ,timestamp1,timestamp2
OUTPUT: I//����ǿ�� 
	int I0 =0;
switch(times){
	case 10min : {  
		I =getIbytime(data1 ,I0 ,timestamp1,timestamp2);
		if(I>I0) I0=I;
		return I0;
		break;
	}
	case 1h : {
		return getIbytime(data1 ,I0 ,timestamp1,timestamp2);
		break;
	} 
} 

/*Produce 4 getYearAvgI*/
INPUT: data1 ,I0 ,timestamp1,timestamp2
OUTPUT: I//����ǿ�� 


