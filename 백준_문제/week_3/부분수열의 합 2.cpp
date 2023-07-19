/*
양수인 부분 수열들만 따로 나열하여, 나열한 부분 수열을 절반으로 나눈다
절반으로 나눈 부분 수열들의 모든 경우의 합을 각각 구한다

절반으로 나누지 않으면, 최대 O(n^40) 이 걸리는 문제이지만
절반으로 나누면, 최대 O(n^20)*2 이 걸리므로 더 빠르게 결과를 도출할 수 있다 

0~n/2 까지의 부분 수열의 합을 map 자료구조를 통해 넣어주고,
n/2~n 까지의 부분 수열의 합을 구할때 map[S-sum] 형태로 기존에 넣었던 값과 합이 S가 되면, 결과를 1씩 더한다

S가 0이면 왼쪽, 오른쪽 배열 둘다 공집합이므로 -1
*/

#include <iostream>
#include <map>
using namespace std;

int num[41];
int n, s;
map<int, int> total;
long long ret = 0;

void leftSum(int st, int sum) {
	if (st == n / 2) {
		total[sum]++;
		return;
	}
	leftSum(st + 1, sum);
	leftSum(st + 1, sum + num[st]);
}

void rightSum(int m, int sum) {
	if (m == n) {
		ret += total[s - sum];
		return;
	}
	rightSum(m + 1, sum);
	rightSum(m + 1, sum + num[m]);
}

int main() {
	cin.tie(0); cout.tie(0);
	ios_base::sync_with_stdio(NULL);
	cin >> n >> s;
	for (int i = 0; i < n; i++)
		cin >> num[i];
	leftSum(0, 0);
	rightSum(n / 2, 0);
	if (s == 0)
		cout << ret - 1;
	else
		cout << ret;
}