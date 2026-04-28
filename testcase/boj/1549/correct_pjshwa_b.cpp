#include <stdio.h>
#include <algorithm>
#include <climits>
 
using namespace std;
 
struct indexValue{
    long long value;
    int index;
 
};
 
long long A[4005];
indexValue B[4005]; //0 은 값어치 1은 인덱스 값 저장할 곳
long long minA[2] = { LONG_MAX, 0 };
 
 
long long ABS(long long a)
{
    return a > 0 ? a : -a;
}
 
bool cmp(const indexValue &u, const indexValue &v) {
    if (u.value < v.value) return true;
    else
        return false;
}
 
int main(void){
    int size;
    long long k;
    bool zero = false;
    scanf("%d", &size);
 
    for (int i = 0; i < size; i++)
        scanf("%lld", &A[i]);
 
    for (k = size / 2; k > 0; k--){
        indexValue temp;
        temp.value = A[0];
        temp.index = 0;
        B[0] = temp;
 
        for (int i = 1; i < size; i++)
        {
            indexValue tempPri = B[i - 1];
            temp.index = i;
            if (i < k)
                temp.value = tempPri.value + A[i];
            else
                temp.value = tempPri.value + A[i] - A[i - k];
 
            B[i] = temp;
        }
 
        sort(B + k - 1, B + size, cmp);
 
        for (int i = k - 1; i < size; i++)
        {
            for (int j = i + 1; j<size; j++){
 
                long long haha = ABS(indexValue(B[i]).value - indexValue(B[i + 1]).value);
                if (ABS(indexValue(B[i]).value - indexValue(B[j]).value) != haha)
                    break;
 
                if (ABS(indexValue(B[i]).index - indexValue(B[j]).index) >= k)
                {
                    if (minA[0] >ABS(indexValue(B[i]).value - indexValue(B[j]).value))
                    {
 
                        minA[0] = ABS(indexValue(B[i]).value - indexValue(B[j]).value);
                        minA[1] = k;
 
                    }
 
                    if (ABS(indexValue(B[i]).value - indexValue(B[j]).value) == 0)
                    {
                        zero = true;
                        break;
                    }
                }
 
            }
            if (zero == true)               break;
 
 
        }
        if (zero == true)
            break;
    }
 
    printf("%lld\n%lld\n", minA[1], minA[0]);
 
    return 0;
}

// https://www.acmicpc.net/source/19681135
