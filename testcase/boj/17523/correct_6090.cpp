#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> S, E, A;
int M, N, R;
bool ok(int i, int j) {
    if(i > j) swap(i, j);
    return i + R >= j;
}
vector<pair<int,int>> ans;
void apply(int from, int to) {
    if(from == to) return;
    bool rev = 0;
    if(from > to) {
        swap(from, to);
        rev = 1;
    }
    int cur = from;
    vector<pair<int, int>> v;
    for(int i=from, j=from; i<to; i=j) {
        while(j + 1 <= to && ok(A[i], A[j+1]))
            j++;
        if(i == j) {
            cout << -1;
            exit(0);
        }
        v.push_back({i, j});
    }
    if(rev) {
        reverse(v.begin(), v.end());
        for(auto &[a, b]: v) swap(a, b);
    }
    ans.insert(ans.end(), v.begin(), v.end());
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> M >> N >> R;
    S.resize(M+1);
    E.resize(M+1);
    A.resize(N+1);
    for(int i=1; i<=N; i++) {
        cin >> A[i];
    }
    for(int i=0; i<M; i++) {
        cin >> S[i];
    }
    for(int i=0; i<M; i++) {
        cin >> E[i];
    }
    for(int i=0, j=0; i<M; i=j) {
        while(j < M && (S[i] < E[i]) == (S[j] < E[j])) {
            j++;
        }
        if(S[i] < E[i]) {
            for(int t=j-1; t>=i; t--) {
                apply(S[t], E[t]);
            }
        } else {
            for(int t=i; t<j; t++)
                apply(S[t], E[t]);
        }
    }
    cout << ans.size() << '\n';
    for(auto [a, b]: ans) {
        cout << a << ' ' << b << '\n';
    }
}
