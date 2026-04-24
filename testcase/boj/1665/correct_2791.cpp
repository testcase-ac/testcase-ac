#include <bits/stdc++.h>
using namespace std;
#define int long long
struct train {
    int l, r;
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<train> A(N);
    for(int i = 0; i < N; i++) {
        cin >> A[i].l >> A[i].r;
    }
    int M;
    cin >> M;
    vector<train> B(M);
    for(int i = 0; i < M; i++) {
        cin >> B[i].l >> B[i].r;
    }
    vector<pair<int, int>> diffs;
    for(auto a: A) {
        for(auto b: B) {
            diffs.push_back({a.l + b.l - 1, 1});
            diffs.push_back({a.l + b.r, -1});

            diffs.push_back({a.r + b.l, -1});
            diffs.push_back({a.r + b.r + 1, 1});
        }
    }
    sort(diffs.begin(), diffs.end());
    int pos = 0, slope = 0, overlap = 0, ans = 0, ansoverlap = 0;
    for(auto pr: diffs) {
        auto t = pr.first - pos;
        overlap += t * slope;
        pos = pr.first;
        slope += pr.second;
        if(overlap > ansoverlap) {
            ans = pr.first;
            ansoverlap = overlap;
        }
    }
    cout << ans - 1;
}
