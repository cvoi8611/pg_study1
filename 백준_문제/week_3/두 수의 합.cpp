/*
둘째 줄에 입력받는 수들중 2개를 합하여 셋째 줄에 입력받는 x 값이 나오는 경우가 몇 번인지 출력하는 문제이다

둘째 줄에 입력받은 수들을 크기 순서대로 나열한 뒤, 입력받은 수들을 순차적으로 하나씩 비교하면 오래 걸리므로
첫번째 수(Ai) 는 순서대로 하나씩 지정하고, 두번째 수(Aj) 는 이분 탐색으로 A와 B의 합이 X가 되는 수를 탐색한다

만약 탐색이 된다면 result값에 1을 더하고, 탐색하지 못했다면 첫번째 수(Ai)의 인덱스에 +1 한다

첫번째 수의 인덱스가 마지막에 도달하면 result값을 2로 나눈 값을 출력한다
result값을 2로 나누는 이유는 만약 X = 15 이고, Ai, Aj가 각각 10,5 일떄, 5,10 인 경우도 result값에 1을 더할 것이다
그러나 i < j 이므로 Ai, Aj 가 각각 10, 5 인 경우는 해당되지 않으므로 2를 나누는 것이다

*/
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 100000;

int arr[MAX];
int main(void)

{
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        int N, X;
        cin >> N;
 
        for (int i = 0; i < N; i++)
                 cin >> arr[i];
        cin >> X;
    
        sort(arr, arr + N);
        int result = 0;
        for (int i = 0; i < N; i++)
        {
                 int low = 0, high = N - 1;
                 while (low <= high)
                 {
                         int mid = (low + high) / 2;
                         if (arr[mid] == X - arr[i])
                         {
                                 result++;
                                 break;
                         }
                         else if (arr[mid] < X - arr[i])
                                 low = mid + 1;
                         else
                                 high = mid - 1;
                 }
        }
        cout << result / 2 << "\n";
        return 0;
}