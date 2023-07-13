/*

행렬 곱셈 순서


행렬 곱셈 연산의 최솟값을 출력하기 위해선

행렬 A 부터 행렬 K 까지의 곱을 구한다고 가정
A~K 에서 절반으로 나누어서 A ~ E / F ~ K

행렬 의 곱 [a,b] x [b,c] 에서 행렬의 곱셈 연산 횟수는 a x b x c

dp[A][B] = 행렬 A에서 행렬 B까지 곱했을 때의 최소 곱셈 연산 횟수를 나타냄 = 행렬 A[a1,a2] , 행렬 B[b1,b2] 

->	행렬 [A] ~ [K] 의 최소 곱셈 연산 횟수 = dp[A][E] + dp[F][K]
dp[A][E] + dp[F][K]
	-> 행렬 A ~ 행렬 E + 행렬 F ~ 행렬 K
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define INF 1000000000

int N, r, c;
int sum[501], matrix[501][2], dp[501][501];

int main()
{
	cin >> N;

	for (int i = 1; i <= N; i++)    // i : 구간 범위의 크기
	{
		cin >> r >> c;
		matrix[i][0] = r;
		matrix[i][1] = c;
	}

	for (int i = 1; i < N; i++)
	{
		for (int j = 1; i + j <= N; j++)    // j : 구간 범위의 시작지점
		{
			dp[j][i + j] = INF;
			for (int k = j; k <= i + j; k++)    // k : 구간 범위를 나누는 기준점
			{
				dp[j][i + j] = min(dp[j][i + j], dp[j][k] + dp[k + 1][i + j] + matrix[j][0] * matrix[k][1] * matrix[i+j][1]);

				//dp j 부터 i 까지의 최소 곱셈 연산 횟수는
				/*	=	( 행렬 [j][i] ) , ( 행렬 [j][k] + 행렬 [k+1][i] + (N X M X K) ) 2개 중 더 작은 값이 행렬 [j][i]의 최소 곱셈 연산 횟수
				행렬 1 ~ 2 ~ 3 라고 가정하면
				N : 행렬 1 의 행
				M : 행렬 2 의 열
				K : 행렬 3 의 열
				*/
			}
		}

	}

	cout << dp[1][N];
	//1 - N번째의 행렬을 곱했을 때 연산의 최솟값

}
