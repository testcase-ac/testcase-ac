#include <stdio.h>

typedef long long ll;

int dotcount(int w, int h, int wd, int hd);
int Euclide(int a, int b);
ll combi(ll n, ll r);

int main()
{
    int N, M;
    ll sum;
    scanf("%d %d", &N, &M);
    sum = combi((N+1)*(M+1), 3);
    sum -= combi(N+1, 3)*(M+1);
    sum -= combi(M+1, 3)*(N+1);
    for(int i = 1; i <= N/2; i++)
    {
        for(int j = 1; j <= M/2; j++)
        {
            if(Euclide(i, j) == 1)
            {
                ll k = 2, w = N-2*i+1, d = M-2*j+1;
                while(1)
                {
                    ll wdsum = w*d;
                    w -= i; d -= j;
                    if(w <= 0 || d <= 0)
                    {
                        w += i; d += j;
                        break;
                    }
                    wdsum -= w*d;
                    sum -= wdsum*combi(k++, 2)*2;
                }
                sum -= combi(k, 2)*w*d*2;
            }
        }
    }
    printf("%lld", sum);
}

int Euclide(int a, int b)
{
    int r = a%b;
    if (r == 0)
    {
        return b;
    }
    return Euclide(b, r);
}

ll combi(ll n, ll r)
{
    ll sum = 1;
    for(ll i = 1; i <= r; i++)
    {
        sum *= n-i+1;
        sum /= i;
    }
    return sum;
}
