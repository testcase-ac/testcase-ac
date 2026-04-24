#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 524288;
int arr[MX * 2];
void update(int l, int r, int v) {
    l += MX, r += MX;
    while(l < r) {
        if(l & 1) {
            arr[l++] ^= v;
        }
        if(r & 1) {
            arr[--r] ^= v;
        }
        l /= 2, r /= 2;
    }
}
int query(int i) {
    i += MX;
    int res = 0;
    while(i) {
        res ^= arr[i];
        i /= 2;
    }
    return res;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arr[i + MX];
    }
    int q;
    cin >> q;
    while(q--) {
        int t, a;
        cin >> t >> a;
        if(t == 1) {
            int b, c;
            cin >> b >> c;
            update(a, b + 1, c);
        } else {
            cout << query(a) << '\n';
        }
    }
}
