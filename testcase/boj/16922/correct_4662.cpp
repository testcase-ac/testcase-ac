#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> st = {1, 5, 10, 50};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> cur = {0};
    for(int i = 0; i < N; i++) {
        vector<int> nxt;
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < cur.size(); k++) {
                nxt.push_back(cur[k] + st[j]);
            }
        }
        sort(nxt.begin(), nxt.end());
        nxt.erase(unique(nxt.begin(), nxt.end()), nxt.end());
        cur = nxt;
    }
    cout << cur.size() << '\n';
}
