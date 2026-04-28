#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N; string s;  cin >> N >> s;
    set<int> S;
    for(int i=1; i<=N; ++i) if(s[i-1] == 'O') S.insert(i);
    int K; cin >> K; while(K--)
    {
        int x; cin >> x; if(S.count(x)) S.erase(x); else S.insert(x);
        int L = *S.rbegin() - (int)S.size();
        int R = (N+1) - (*S.begin() + (int)S.size());
        cout << min(L, R) << '\n';
    }
}
