#include <bits/stdc++.h>
using namespace std;
bool seen[10001][500];
bool no[10001];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int t;
        cin >> t;
        no[t] = 1;
    }
    queue<pair<int, int>> q;
    q.push({1,0});
    int t = 0;
    auto chk = [&](int a, int b) {
        if(a > N || b <= 0) {
            return;
        }
        if(no[a]) return;
        if(seen[a][b]) return;
        seen[a][b] = 1;
        q.push({a, b});
    };
    while(q.size()) {
        int s = q.size();
        while(s--) {
            auto [a, b] = q.front();
            if(a == N)
                return !(cout << t);
            q.pop();
            chk(a + b - 1, b - 1);
            chk(a + b, b);
            chk(a + b + 1, b + 1);
        }
        t++;
    }
    cout << -1;
}
