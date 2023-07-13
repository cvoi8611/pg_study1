/*
계단의 개수마다 각각의 점수를 부여해야 하므로, 계단의 개수만큼 배열을 생성
계단에 점수를 부여하고 계단을 밟는 경우를 구함

계단의 갯수가 300이하의 자연수고 계단에 쓰여 있는 점수는 10,000 이하의 자연수 이므로
단순 반복은 수가 너무 커짐
-> 점화식 찾아서 대입

2번 연속해서 계단을 밟는 경우와
연속해서 밟지 않는 경우 2개의 경우가 존재하므로 이 2가지중 더 큰 값을 계단 i번째의 최대값으로 보면 된다

연속해서 계단을 밟는 경우 (XOO)/ [max value 값] + X + O + O         / max_value[i-3] + stair[i-1] + stair[i]
연속해서 계단을 밟지 않는 경우 (XO) / [max value 값] + X + O        / max_value[i-2] + stair[i]

둘 중 더 큰 값이 max_value[i] 이므로

점화식은
max_value[i]=max(max_value[i-3]+stair[i-1]+stair[i], max_value[i-2]+stair[i])
이다

i이 3 미만이면 max_value[i-3] max_value[0]보다 낮아지므로 값을 지정할 수 없음

따라서 i가 0 , 1 , 2 인 경우는 미리 지정하고 i가 3 이상인 지점부터 for 문으로 반복 구현


*/

#include <stdio.h>

int max_value[301];
int stair[301];


int max (int a, int b){
    return a > b ? a : b;
}

int main() {
    int t;
    scanf("%d", &t);

    for (int i = 1; i <= t; i++) {
        scanf("%d", &stair[i]);
    }

    max_value[0] = 0;
    max_value[1] = stair[1];
    max_value[2] = stair[1] + stair[2];

    for (int i = 3; i <= t; i++) {
        max_value[i] = stair[i] + (max(max_value[i - 2], stair[i - 1] + max_value[i - 3]));
    }

    printf("%d\n", max_value[t]);
    return 0;
}