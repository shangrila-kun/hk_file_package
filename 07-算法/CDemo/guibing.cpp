#include<iostream>
#define INF 10000000
using namespace std;
void merge(int arr[],int ,int ,int );
void merge_sort(int arr[],int ,int);
int main(){
	int arr[10] = {5,6,7,9,8,4,2,3,1,0};  
	int p=0,r=9;  
    merge_sort(arr,p,r);  
    for(int i=0;i<=r;i++)  
        cout<<arr[i]<<",";  
    cout<<endl;  
    return 0; 
}
void merge(int arr[],int p,int q,int r){
	int n1 = q - p + 1;//p到q的元素个数
	int n2 = r - q;//q+1到r的元素个数
	int* p1 = new int[n1+1];//每个动态数组的最后一位用于存放哨兵元素。
	int* p2 = new int[n2+1];
	for(int i=0;i<n1;i++){
		p1[i] = arr[p+i];
	}
	for(int i=0;i<n2;i++){
		p2[i] = arr[q+i+1];
	}
	p1[n1]=INF;
	p2[n2]=INF;
	int i=0,j=0;
	for(int k=p;k<=r;k++){
		if(p1[i]<=p2[j]){
			arr[k] = p1[i];
			i++;
		}else{
			arr[k] = p2[j];
			j++;
		}
	}	
}
void merge_sort(int arr[], int p,int r){
	if(p<r){
		int q = (p+r)/2;
		merge_sort(arr,p,q);
		merge_sort(arr,q+1,r);
		merge(arr,p,q,r);
	}
}
