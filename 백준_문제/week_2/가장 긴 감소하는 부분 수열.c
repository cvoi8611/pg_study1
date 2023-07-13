/*
가장 긴 감소하는 부분 수열

수열 하나를 입력받고, count 배열에다 수열왼쪽에 자기 자신보다 큰 수가 있으면 1씩 증가시킨다
그 후, count 배열에서 가장 큰 값을 가져옴

count 배열에서 가장 큰 값 = 수열에서 가장 긴 감소하는 부분 수열의 길이

*/

#include <stdio.h>
#include <stdlib.h>
#define math_max(a, b) a > b ? a : b


int main(){
    int t;
    scanf("%d",&t);
    int arr[1001];
    int count[1001]={0};
    for (int i=0; i<t; i++){
        scanf("%d",&arr[i]);
        count[i] = 1;
    }

    for (int i=t-1; i>=0; i--){
        for (int j=t-1; j>i; j--){
            if (arr[i] > arr[j] & count[i] < count[j] + 1){
                count[i] = count[j] + 1;
            }
        }
    }
    int max = 0;
	for (int i = 0; i < t; i++) {
		max = math_max(max, count[i]);
	}
	printf("%d", max);
    return 0;
}