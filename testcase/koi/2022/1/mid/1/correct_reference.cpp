//
// Official Solution
// Author: Jongseo Lee (@leejseo)
//
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long ll;

int N;
ll S[2];
ll ans[2];

int main(void)
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
    {
        int x;
        scanf("%d", &x);
        S[x % 2]++;
        ans[x % 2] += S[(x + 1) % 2];
    }
    printf("%lld\n", min(ans[0], ans[1]));
}