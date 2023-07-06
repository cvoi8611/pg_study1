
/*
	가장 앞에 있는 문서의 중요도를 확인 후, 다른 문서들과 중요도를 비교한 뒤, Queue의 가장 뒤에 재배치하거나 출력함
	문서의 중요도를 앞에서 확인, 뒤에서 수정하므로
	앞에서 데이터 삽입, 뒤에서 데이터 삭제가 가능한 Queue를 이용

	테스트케이스 수를 입력받고
    
    L1 : 문서의 개수(n)와 필요한 문서가 현재 놓여있는 queue의 위치(m)를 입력받음
    문서 개수(n)만큼 문서 중요도(arr[])를 하나씩 입력 받음
    
    문서 중요도중 가장 높은 값을 front가 가리킬 때까지 front값을 한 칸씩 옮김
    arr[front] 가 필요한 문서라면 break;
    필요한 문서가 아니라면 최댓값을 0으로 하고 다시 찾음
    
    L1을 테스트케이스 수만큼 반복
	
	
*/

#include <stdio.h>

int main(){
	int cnt, n, m;
	int i, j, k;
	int arr[101];

	scanf("%d", &cnt);

	for (i=0; i<cnt; i++){
		scanf("%d %d", &n, &m);
		int imp = 1;
		int front = 0;
		int max = 0;
		for (j=0; j<n; j++)
			scanf("%d", &arr[j]);
		while (1){
			for (k=0; k<n; k++) {
				if (arr[k] > max) max = arr[k];
			}
			while (arr[front] != max)
				front = (front + 1) % n;
			if (front == m) break;
			    arr[front] = 0;
			front = (front + 1) % n;
			max = 0;
			imp++;
		}
		printf("%d\n", imp);
	}
	return 0;
}