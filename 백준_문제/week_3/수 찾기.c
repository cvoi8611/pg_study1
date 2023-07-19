/*
둘째 줄 수가 첫째 줄 수에 존재하는지 비교하며 수를 찾는 문제다

for문을 두번 이용해서 모든 수를 훑어보는 방법은 O(n^2) 이므로 
너무 오래 걸린다

첫째 줄 수를 작은 수부터 큰 수까지 정렬 한 뒤, 반씩 나눠가며 수를 찾아가는 방법인 이분 탐색을 이용하여
수를 비교하면 O(nlogn) 까지 줄일 수 있다

처음에 n값을 받고 n값만큼 배열 크기 할당, 수 입력
n 값 들어있는 배열 arr 순서대로 수 정렬 후

m 입력 받아 배열 arr2에 저장 후, 
j를 0부터 m까지 반복하여, arr에 arr2[j]의 원소가 존재하면 1을 출력, 값을 찾을 수 없으면 0을 출력한다
*/

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return *(int*)a > *(int*)b ? 1 : (*(int*)a < *(int*)b ? -1 : 0);
}

int binary_search(int arr[], int num, int size)
{
    int front, rear, pivot;
    front = 0;
    rear = size - 1;
    while (1) {
        pivot = (front + rear) / 2;
        if (arr[pivot] == num) return 1;
        if (arr[front] == num) return 1;
        if (arr[rear] == num) return 1;

        if (arr[pivot] < num)
            front = pivot + 1;
        else 
            rear = pivot - 1;
        if (front >= rear)
            return 0;
    }
}

int main(void){
    int n;
    scanf("%d", &n);
    int *arr = (int*)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    int m;
    scanf("%d", &m);
    int *arr2 = (int*)malloc(m * sizeof(int));

    for(int i = 0; i < m; i++){
        scanf("%d", &arr2[i]);
    }

    qsort(arr, n, sizeof(int), compare);

    for(int j = 0; j < m; j++){
        printf("%d\n", binary_search(arr, arr2[j], n));
    }
    return 0;
}