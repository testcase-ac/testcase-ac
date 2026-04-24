#include <bits/stdc++.h>
using namespace std;
#define int long long
int dist[50001];
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> sq;
    memset(dist, 0x3f, sizeof(dist));
    for(int i = 1; i <= 223; i++) {
        sq.push_back(i * i);
        dist[i * i] = 1;
    }
    for(int i = 1; i <= 50000; i++) {
        for(int j = 0; j < sq.size(); j++) {
            int nxt = i + sq[j];
            if(nxt > 50000) continue;
            if(dist[nxt] > dist[i] + 1) {
                dist[nxt] = dist[i] + 1;
            }
        }
    }
    int x;
    cin >> x;
    cout << dist[x] << '\n';
}
