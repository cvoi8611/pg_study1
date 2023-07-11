
/*
    각각의 괄호들을 받으면서 짝을 유지하는지 확인하려면 입력받은 괄호 열기 '(' 가 괄호 닫기 ')'를 입력받을 떄까지
    한 곳에 저장해두어야 하므로 스택을 사용하였다.
    

    처음에 '.' 하나만 입력되면 break;
    
    str에 '.'이 입력될 때까지 str 내용을 확인
    괄호를 찾으면 스택에 넣고 top의 값이 +1
    괄호끼리 서로 짝이 맞으면 소멸하고 top의 값이 -1
    str에 '.' 입력되었을때 top이 -1로 모든 괄호들이 서로 짝을 맞아 모두 소멸하였으므로 yes
    그게 아니라면 no
    

*/

#include <stdio.h>

#define MAX 101

int main(){
    char str[MAX], stack[MAX];
    while (1){
        gets(str);
        if (str[0] == '.') break;
        int top = -1;
        for (int i = 0; str[i] != '.'; i++){
            if (str[i] == '(' || str[i] == '['){
                stack[++top] = str[i];
            }
            else if (str[i] == ')'){
                if (top > -1 && stack[top] == '('){
                    --top;
                }
                    
                else {
                    top = -2;
                    break;
                }
            }
            else if (str[i] == ']'){
                if (top > -1 && stack[top] == '['){
                    --top;
                }
                else{
                    top = -2;
                    break;
                }
            }
                
        }
        puts(top == -1 ? "yes" : "no");
    }
}





