#include <bits/stdc++.h>
#define int long long
using namespace std;
using pii = pair<int,int>;

int32_t main() {
    cin.tie(0) -> sync_with_stdio(false);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pii> v(n);
    for(int i=0; i<n; i++) {
        cin >> v[i].first >> v[i].second;
    }
    while(q--) {
        int min_dist = 1e10, cnt=0;
        vector<int> s(3);
        int a, b;
        cin >> a >> b;
        for(int i=0; i<n; i++) {
            auto& p = v[i];
            int dist =  (p.first - a) * (p.first - a) + (p.second - b) * (p.second - b);
            if(dist < min_dist) {
                cnt = 1;
                min_dist = dist;
                s[0] = i+1;
            }
            else if(dist == min_dist) {
                cnt++;
                if(cnt <= 3) {
                    s[cnt-1] = i+1;
                }
            }
        }
        if(cnt == 1) {
            cout << "REGION" << " " << s[0] << "\n";
        }
        else if(cnt == 2) {
            cout << "LINE" << " " << s[0] << " " << s[1] << "\n";
        }
        else {
            cout << "POINT" << "\n";
        }
    }
}
