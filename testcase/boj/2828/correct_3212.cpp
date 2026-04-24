#include <bits/stdc++.h>
using namespace std;
vector<int> apple, pos;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, J;
    cin >> N >> M >> J;
    int l = 1, ans = 0;
    for(int i=0; i<J; i++) {
        int r = l + M - 1;
        int a;
        cin >> a;
        if(a < l) {
            int dist = l-a;
            ans += dist;
            l -= dist;
        } else if(a > r) {
            int dist = a - r;
            ans += dist;
            l += dist;
        }
    }
    cout << ans;
}
