#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> E(N+1);
    vector<vector<int>> dep(N+1);
    for(int i=1; i<=N; i++) {
        cin >> E[i];
        int d;
        cin >> d;
        while(d--) {
            int t;
            cin >> t;
            dep[i].push_back(t);
        }
    }
    auto solve = [&](int m) {
        queue<int> que;
        vector<int> in(N+1), mx(N+1);
        for(int i=1; i<=N; i++) {
            for(int a: dep[i]) {
                in[a]++;
            }
            mx[i] = m - E[i] + 1;
        }
        for(int i=1; i<=N; i++) {
            if(!in[i]) {
                que.push(i);
            }
        }
        while(que.size()) {
            int q = que.front();
            que.pop();
            for(int a: dep[q]) {
                mx[a] = min(mx[a], mx[q] - 1);
                in[a]--;
                if(!in[a]) {
                    que.push(a);
                }
            }
        }
        vector<int> v;
        for(int i=1; i<=N; i++) {
            v.push_back(mx[i]);
        }
        sort(v.begin(), v.end());
        for(int i=0; i<v.size(); i++) {
            if(i + 1 > v[i]) {
                return false;
            }
        }
        return true;
    };

    int l = N, r = 1e7;
    while(l < r) {
        int m = (l+r) / 2;
        if(solve(m)) {
            r = m;
        } else {
            l = m+1;
        }
    }
    cout << l << '\n';
}
