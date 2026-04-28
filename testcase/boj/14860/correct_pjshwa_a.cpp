#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1.5e7;
const int MOD = 1e9+7;
vector<bool> sieve;
long long ipow(long long a, long long b)
{
    long long res = 1;
    while(b)
    {
        if(b&1) res = res*a%MOD;
        a = a*a%MOD;
        b /= 2;
    }
    return res;
}
void init()
{
    sieve.resize(MAXN+1, true);
    sieve[0] = false; sieve[1] = false;
    for(int i=2; i*i<=MAXN; ++i)
    {
        if(!sieve[i]) continue;
        for(int j=i*i; j<=MAXN; j += i)
            sieve[j] = false;
    }
}
int main()
{
    init();
    int N, M; scanf("%d%d", &N, &M);
    long long ans = 1;
    for(long long i=2; i<MAXN; ++i)
    {
        if(!sieve[i]) continue;
        for(long long int j=i; j<=MAXN; j *= i)
        {
            ans *= ipow(i, (N/j)*(M/j));
            ans %= MOD;
        }
    }
    printf("%lld\n", ans);
    return 0;
}

