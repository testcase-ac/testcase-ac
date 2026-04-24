#include <bits/stdc++.h>
using namespace std;
#define int long long
struct egg {
    int s, w;
};

vector<egg> eggs;
int ans = 0;
void rec(int t) {
    if(t == eggs.size()) {
        int cnt = 0;
        for(int i = 0; i < eggs.size(); i++) {
            if(eggs[i].s <= 0) {
                cnt++;
            }
        }
        ans = max(ans, cnt);
        return;
    }
    bool has_target = 0;
    for(int i = 0; i < eggs.size(); i++) {
        if(eggs[i].s <= 0 || eggs[t].s <= 0 || i == t) {
            continue;
        }
        has_target = 1;
        eggs[i].s -= eggs[t].w;
        eggs[t].s -= eggs[i].w;
        rec(t + 1);
        eggs[i].s += eggs[t].w;
        eggs[t].s += eggs[i].w;
    }
    if(!has_target) {
        rec(t + 1);
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    eggs.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> eggs[i].s >> eggs[i].w;
    }
    rec(0);
    cout << ans << '\n';
}
