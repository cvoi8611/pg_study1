'''

온도의 배열을 arr[0] ~ arr[k] 라고 하면
첫번째 0~k번째 온도의 합 = A 라고 할 떄
두번째 온도의 합은 = A + arr[k+1] - arr[0] = B
세번째 온도의 합은 = B + arr[k+2] - arr[1] = C .... 이런식으로 점화식이 생성된다

저렇게 모든 온도의 합을 리스트에 넣고, 리스트에 포함된 원소들중 최대값을 출력하면 된다

'''


def sequence(temperture_list, K):
    temp_k_days_list = [sum(temperture_list[:K])]
    for i in range(1, len(temperture_list) - K + 1):
        sum_k_temp = temp_k_days_list[-1] + temperture_list[i+K-1] - temperture_list[i-1]
        
        #print('temp[-1] + temperature[i+K-1] + temperatur[i-1] = '+str(temp_k_days_list[-1])+'+'+str(temperture_list[i+K-1])+'-'+str(temperture_list[i-1]))
        #print(sum_k_temp)

        temp_k_days_list.append(sum_k_temp)
        
    return max(temp_k_days_list)

if __name__ == "__main__":
    N, K = map(int, input().split())
    temperture_list = list(map(int, input().split()))
    print(sequence(temperture_list, K))