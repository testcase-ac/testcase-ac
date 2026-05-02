#include <iostream>
#include <array>
#include <algorithm>
#include <unordered_map>

using namespace std;

array<int, 200'000> arr, prv, nxt;
unordered_map<int, int> last;

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    last.clear();
    for (int i = 0; i < n; i++) {
        prv[i] = last.count(arr[i]) ? last[arr[i]] : -1;
        last[arr[i]] = i;
    }
    last.clear();
    for (int i = n-1; i >= 0; i--) {
        nxt[i] = last.count(arr[i]) ? last[arr[i]] : n;
        last[arr[i]] = i;
    }
    
    auto is_unique_in = [&](int x, int l, int r) -> bool {
        return !(l <= prv[x] && prv[x] <= r) && !(l <= nxt[x] && nxt[x] <= r);
    };

    auto rec = [&](const auto& self, int l, int r) -> bool {
        if (r <= l) { return false; }
        int sz = r-l+1;
        for (int k = 0; k <= (sz >> 1); k++) {
            int i = l+k, j = r-k;
            if (is_unique_in(i, l, r)) {
                return self(self, l, i-1) || self(self, i+1, r);
            }
            if (is_unique_in(j, l, r)) {
                return self(self, l, j-1) || self(self, j+1, r);
            }
        }
        return true;
    };

    cout << (rec(rec, 0, n-1) ? "boring" : "non-boring") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
