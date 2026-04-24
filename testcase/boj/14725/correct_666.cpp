#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1001;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<map<string,int>> nodes(1);
    while(N--) {
        int k;
        cin >> k;
        int cur = 0;
        for(int i=0; i<k; i++) {
            string s;
            cin >> s;
            if(!nodes[cur][s]) {
                nodes[cur][s] = nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur][s];
        }
    }
    function<void(int,int)> dfs = [&](int i, int d) {
        for(auto &[k, v]: nodes[i]) {
            for(int t=0; t<d; t++) cout << '-';
            cout << k << '\n';
            dfs(v, d+2);
        }
    };
    dfs(0, 0);
}
