
/*
    문제가 소수를 구하는 문제이며, 최대 100만까지 출력하므로 실행 시간을 단축하기 위해
    소수를 구하는 방식중 하나인 에라토스테네스의 체를 사용함

    isprime[] 배열을 사용하여 에라토스테네스의 체를 구현하였다
    M부터 N까지의 소수를 구해야 하므로

    isprime[x] = 1 이 나타내는 의미는 x가 소수임을 나타내는 상태이며
    2부터 최대값까지의 수를 isprime에 0을 할당하고 0이 할당된 값은 그대로 둔 채 1이 할당된 값만 비교한다

    이러한 과정을 2부터 N의 제곱근까지 반복 후, M ~ N을 출력함 대신, 소수만을 출력해야 하므로 isprime[]의 값이 1인 값만 출력함
*/

#include <stdio.h>
#include <math.h>

int main(){
    int a,b;
    scanf("%d %d",&a ,&b);
    int isprime[b];
    for (int i=2; i<=b; i++){
        isprime[i] = 1;
    }
    for (int i=2; i<=sqrt(b); i++){
        if(isprime[i] == 1){
            for (int j=2; i*j<=b; j++){
                isprime[i*j] = 0;
            }
        }
    }
    for(int i=a; i<=b; i++) {
        if(isprime[i] == 1) printf("%d\n", i);
    }
    return 0;
}