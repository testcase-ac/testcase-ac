#include <stdio.h>
#include <string.h>

typedef unsigned long long llu;

llu power(int a, int r)
{
    llu sum = 1;
    for(int i = 1; i <= r; i++)
    {
        sum *= a;
    }
    return sum;
}

llu Euclide(llu a, llu b)
{
    llu r = a%b;
    if(r == 0)
    {
        return b;
    }
    return Euclide(b, r);
}

int main()
{
    int N, K;
    llu rsp[41][41];
    llu sum[2] = {0, 0};
    memset(rsp, 0, sizeof(rsp));
    scanf("%d %d", &N, &K);
    rsp[0][0] = 1;
    for(int i = 1; i <= N; i++)
    {
        for(int j = K; j >= 0; j--)
        {
            for(int k = K-1; k >= 0; k--)
            {
                if(j > 0 && k != K)
                {
                    rsp[j][k] += rsp[j-1][k];
                    if(j == K)
                    {
                        sum[1] += rsp[j][k]*power(3, N-i);
                        rsp[j][k] = 0;
                    }
                }
                if(k > 0 && j != K)
                {
                    rsp[j][k] += rsp[j][k-1];
                }
            }
        }
    }
    sum[0] = power(3, N);
    llu gcd = Euclide(sum[0], sum[1]);
    sum[0] /= gcd;
    sum[1] /= gcd;
    printf("%llu %llu", sum[1], sum[0]);
}
