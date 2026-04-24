#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()

void solve() {
    int N;
    cin >> N;
    if(N%2 == 0) {
        cout << "No\n";
        return;
    }
    vector<pair<int,int>> v(N);
    rep(i, N) {
        v[i] = {i+1, 2*N-i};
    }
    int ptr = 0;
    for(int d=N/2; d>=1; d-=2) {
        swap(v[ptr].second, v[ptr+d].second);
        ptr++;
    }
    ptr = N/2+1;
    for(int d=N/2-1; d>=1; d-=2) {
        swap(v[ptr].second, v[ptr+d].second);
        ptr++;
    }
    cout << "Yes\n";
    sort(all(v), [](auto a, auto b){return a.first+a.second < b.first+b.second;});
    for(auto [a, b]: v) {
        cout << a << ' ' << b << '\n';
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
}
