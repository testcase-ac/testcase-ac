#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K;
    cin >> N >> K;
    vector<int> D(N), L(K);
    for (int &x: D) cin >> x;
    for(int &x: L) cin >> x;
    sort(D.begin(), D.end(), greater<int>());
    multiset<int> ms(L.begin(), L.end());
    int ans = 0;
    for(int x: D) {
        int a = 2*x, b = 3*x;
        auto it = ms.lower_bound(a + b);
        if(it == ms.end()) {
            auto it_b = ms.lower_bound(b);
            if(it_b == ms.end()) {
                return !(cout << "NIE");
            }
            ms.erase(it_b);
            auto it_a = ms.lower_bound(a);
            if(it_a == ms.end()) {
                return !(cout << "NIE");
            }
            ms.erase(it_a);
            ans += 2;
        } else {
            ms.erase(it);
            ans++;
        }
    }
    cout << ans;
}
