#include <bits/stdc++.h>
using namespace std;
#define int long long

bool tell_truth[51];
vector<int> party[50];
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    int cnt;
    cin >> cnt;
    for(int i = 0; i < cnt; i++) {
        int t;
        cin >> t;
        tell_truth[t] = true;
    }

    for(int i = 0; i < m; i++) {
        int t;
        cin >> t;
        for(int j = 0; j < t; j++) {
            int x;
            cin >> x;
            party[i].push_back(x);
        }
    }
    while(true) {
        bool chk = 0;
        for(int i = 0; i < m; i++) {
            bool hastrue = 0;
            bool hasfalse = 0;
            for(int p: party[i]) {
                if(tell_truth[p]) {
                    hastrue = 1;
                } else {
                    hasfalse = 1;
                }
            }
            if(hastrue && hasfalse) {
                chk = 1;
                for(int p: party[i]) {
                    tell_truth[p] = true;
                }
            }
        }
        if(!chk)
            break;
    }
    int ans = 0;
    for(int i = 0; i < m; i++) {
        bool chk = 1;
        for(int p: party[i]) {
            if(tell_truth[p]) {
                chk = 0;
            }
        }
        if(chk)
            ans++;
    }
    cout << ans << '\n';
}
