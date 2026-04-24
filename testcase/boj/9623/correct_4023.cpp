#include <bits/stdc++.h>
using namespace std;
#define int long long
struct elem {
    int sum, pos;
    bool operator<(const elem &a) const {
        return sum < a.sum;
    }
};
vector<elem> v;
int solve() {
    int N, X;
    cin >> N >> X;
    vector<int> A(N + 1), S(N + 1);
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
        S[i] = S[i - 1] + A[i];
    }
    v.clear();
    v.push_back({0, 0});
    int ans = INT_MAX;
    for(int i = 1; i <= N; i++) {
        int mx_sum = S[i] - X;
        auto it = upper_bound(v.begin(), v.end(), elem{mx_sum, 0});
        if(it != v.begin()) {
            ans = min(ans, i - prev(it)->pos);
        }
        while(v.size() && v.back().sum >= S[i]) {
            v.pop_back();
        }
        v.push_back({S[i], i});
    }
    return ans == INT_MAX ? -1 : ans;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        cout << solve() << '\n';
    }
}
