/*
누적 합 배열을 생성하고 이 배열을 arr이라고 하면

M으로 나누어 떨어지는 누적합 구간을 구함
-> 누적합 구간 % M = 0 이 성립

i~j (j>=i) 의 누적합 구간은 arr[j] - arr[i]

즉, (arr[j] - arr[i]) % M = 0 이 성립하는 경우가 총 몇개인지를 구한다

(arr[j] - arr[i]) % M = 0
-> arr[j] % M = arr[i] % M 와 같음

예제를 위 공식을 사용해서 보자면

			1 2 3 1 2 -> 누적합 배열
	-> 		1 3 6 7 9
arr % M		1 0 0 1 0


arr % M = 1 인 조합 (0,3)
arr % M = 0 인 조합 (1,2) , (2,4) , (1,4)

총 4개

+

i 가 존재하지 않는 케이스도 성립 가능
arr % M = 0 인 경우 3개

따라서 총 7개




*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;

int N, M, x;
long long cnt[1001];
long long sum, ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		cin >> x;
		sum += x;
		cnt[sum % M]++;
	}

	for (int i = 0; i <= 1000; i++)
	{
		ans += cnt[i] * (cnt[i] - 1) / 2;
	}
	
	cout << cnt[0] + ans;
}