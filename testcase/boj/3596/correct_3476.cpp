#include <bits/stdc++.h>
using namespace std;
int grundy[2001], n;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        set<int> st;
        for(int j = 0; j < i / 2 + 1; j++) {
            int l = max(0, j - 2), r = max(0, i - j - 3);
            int g = grundy[l] ^ grundy[r];
            st.insert(g);
        }
        while(st.count(grundy[i])) {
            grundy[i]++;
        }
    }
    cout << (grundy[n] ? 1 : 2);
}
