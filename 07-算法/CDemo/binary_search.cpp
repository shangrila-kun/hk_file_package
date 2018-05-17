#include<iostream>
using namespace std;
int binary_search(int arr[], int n, int key){
	int left = 0;
	int right = n - 1;
	while (left <= right){
		int mid = left + ((right - left)>>1);
		if(arr[mid] > key){
			right = mid -1;
		}else if(arr[mid] < key){
			left = mid + 1;
		}else{
			return mid;
		}
	}
	return -1;
}
int binarySearch(int arr[], int left, int right, int key){
	int mid = left +((right - left)>>1);
	if(left > right) return -1;
	if(key == arr[mid] ) return mid;
	if(key < arr[mid]){
		return binarySearch(arr, left, mid-1, key);
	}
	if(key > arr[mid]){
		return binarySearch(arr, mid+1, right, key);
	}
}
int main(){
	int arr[5] = {1,3,5,9,10};
	int ret = binarySearch(arr,0,4,9);
	cout<<ret<<endl;
}
