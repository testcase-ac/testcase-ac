#include <bits/stdc++.h>
using namespace std;
#define int long long
struct room {
    char type;
    int amt;
    vector<int> adj;
    void read() {
        string s;
        cin >> s;
        type = s[0];
        cin >> amt;
        while(true) {
            int t;
            cin >> t;
            if(t == 0) break;
            adj.push_back(t);
        }
    }
};
int32_t main() {
    while(true) {
        int n;
        cin >> n;
        if(!n)
            break;
        vector<room> rooms(n + 1);
        for(int i = 1; i <= n; i++) {
            rooms[i].read();
        }
        vector<int> dp(n + 1, -1);
        if(rooms[1].type == 'T' && rooms[1].amt > 0) {
            cout << "No\n";
            continue;
        }
        if(rooms[1].type == 'L') {
            dp[1] = rooms[1].amt;
        } else {
            dp[1] = 0;
        }
        queue<int> que;
        que.push(1);
        while(que.size()) {
            int q = que.front();
            que.pop();
            // printf("arrive at %d for dp %d\n", q, dp[q]);
            for(int i: rooms[q].adj) {
                int nxt = dp[q];
                if(rooms[i].type == 'T') {
                    nxt -= rooms[i].amt;
                } else if(rooms[i].type == 'L') {
                    nxt = max(rooms[i].amt, nxt);
                }
                if(nxt > dp[i]) {
                    dp[i] = nxt;
                    que.push(i);
                    // printf("push at i=%d, nxt=%d\n", i, nxt);
                }
            }
        }
        cout << (dp[n] >= 0 ? "Yes\n" : "No\n");
        // printf("-------------\n");
    }
}
