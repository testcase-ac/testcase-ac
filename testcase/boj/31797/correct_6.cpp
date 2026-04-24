#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> v;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        v.push_back({a, i+1});
        v.push_back({b, i+1});
    }
    sort(v.begin(), v.end());
    cout << v[(N-1)%(2*M)].second;
}
