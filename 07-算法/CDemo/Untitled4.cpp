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


INPUT��data1
OUTPUT: Validation results 
if(the average wind speed in 1 hour is <6.0m/s )
if(Change in hourly average temperature < 5��C)
if(The 3-hour mean pressure change is <1kPa)
if(|V50-V30|<4.0m/s&&|V50-V10|<8.0m/s&&)//Wind speed difference corresponding to two heights
if(|D50-D30|<30��|||D50-D30|>330��) 
if(the wind speed channel is between 0m/s and 90m/s)
if(the wind direction channel is between 0�� and 360��)
if(The average pressure channel is between 50kPa and 110kPa)




��1��	����ͬ�߶��ٽ�ͨ��������ֲ��
��2��	�ڽ���ͬ�߶�ͬʱ��������ֲ��
��3��	����ͬ�߶��ٽ�ʱ��������ֲ��





��ѹͨ����ƽ��ֵ�Ƿ��� 50kPa��110kPa֮�䣻


/*Produce 2 ���ٲ岹*/
INPUT��data1,data2, a,b,r //1�š�2�Ų�������ݡ���������Է���ϵ��
OUTPUT��data1  //������������






/*Produce 2 getIbytimestamp ��������ǿ�ȹ�ʽ*/  
INPUT: data1 ,I0 ,timestamp1,timestamp2,height
OUTPUT: I
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
OUTPUT: I
switch(times){
	case 10min : { 
	return  the maximum of 6 turbulence calculations per hour;
	break;
	}
	case 1h : {
		return Using a value calculation;
		break;
	} 
	case 1year: {
		return Avg(getI_by_timestamp_height());
		break;
	}
} 




INPUT: data1 ,I0 ,timestamp1,timestamp2
OUTPUT: I//����ǿ�� 
switch(times){
	case 10min : { 
	return  the maximum of 6 turbulence calculations per hour;
		I =getIbytime(data1 ,I0 ,timestamp1,timestamp2);//������Ϊ��10min���ӣ���ȡ����ǿ�� 
		if(I>I0) I0=I;
		return I0;
		break;
	}
	case 1h : {
		return getIbytime(data1 ,I0 ,timestamp1,timestamp2);//��ȡÿСʱ������ǿ�� 
		break;
	} 
} 

INPUT: data1,timestamp1,timestamp2
OUTPUT: I
 



/*Produce 4 getYearAvgI*/
INPUT: data1 ,timestamp1,timestamp2,height
OUTPUT: I 
compared(previous wind speed);
if(data1.speed>14.6&&data1.speed<=15.5){
 return Avg(getI_by_timestamp_height(data1));	
}  






