#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

struct Rule
{
    char t;
    int p, q;
};

int N, move_to[50][105];
long long C, K, change[50][105];
char msg[105];
Rule rule[100005];

int main ()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> N >> C >> K;
    cin >> msg;
    
    for(int i = 0, j, k; i < C; ++i)
    {
        char t;
        cin >> t >> j >> k;
        rule[i] = {t, j, k};
    }

    int res[2][105];
    iota(res[0], res[0] + N, 0);

    if(C > K)
        C = K;
    
    for(int i = 0; i < C; ++i)
    {
        if(rule[i].t == 'S')
            swap(res[0][rule[i].p], res[0][rule[i].q]);
        else
            change[0][res[0][rule[i].p]] += rule[i].q;
    }
    for(int i = 0; i < N; ++i)
        move_to[0][res[0][i]] = i;
        
    int p = 0, t = 0;
    for( ; C * (1LL << (p + 1)) <= K; ++p, t = !t)
    {
        for(int i = 0; i < N; ++i)
            change[p+1][res[t][i]] = change[p][res[t][i]] + change[p][i];
        for(int i = 0; i < N; ++i)
            res[!t][move_to[p][i]] = res[t][i];
        for(int i = 0; i < N; ++i)
            move_to[p+1][res[!t][i]] = i;
    }

    K -= C * (1LL << p);
    for(int p2 = p - 1; p2 >= 0 && K > 0; --p2)
    {
        if(K < C * (1LL << p2))
            continue;
        K -= C * (1LL << p2);
        for(int i = 0; i < N; ++i)
            change[p][res[t][i]] += change[p2][i];
        for(int i = 0; i < N; ++i)
            res[!t][move_to[p2][i]] = res[t][i];
        t = !t;
    }

    for(int i = 0; i < K; ++i)
    {
        if(rule[i].t == 'S')
            swap(res[t][rule[i].p], res[t][rule[i].q]);
        else
            change[p][res[t][rule[i].p]] += rule[i].q;
    }

    char ans[105] = {};
    for(int i = 0; i < N; ++i)
        ans[i] = (msg[res[t][i]] - 'A' + change[p][res[t][i]]) % 26 + 'A';

    cout << ans;
    return 0;
}
