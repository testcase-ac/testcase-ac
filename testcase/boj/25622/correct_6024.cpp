#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 333334;
vector<int> adj[MX];
int dp[MX];
vector<int> groups[MX];
int find_one(int i, int p) {
    for(int a: adj[i]) {
        if(a == p) continue;
        if(dp[a] == 1) return a;
    }
    exit(1);
}
void dfs(int i, int p) {
    if(adj[i].size() == 1 && adj[i][0] == p) {
        dp[i] = 1;
        return;
    }
    int ones = 0, twos = 0, zeros = 0;
    for(int a: adj[i]) {
        if(a == p)
            continue;
        dfs(a, i);
        if(!dp[a])
            zeros++;
        else if(dp[a] == 1)
            ones++;
        else
            twos++;
    }
    int childs = ones + twos + zeros;
    int nums = ones + twos * 2;
    if(nums >= 3) {
        cout << "U";
        exit(0);
    }
    dp[i] = (nums + 1) % 3;
    if(!dp[i]) {
        groups[i].push_back(i);
        for(int a: adj[i]) {
            if(a == p)
                continue;
            if(dp[a] == 1) {
                groups[i].push_back(a);
            } else if(dp[a] == 2) {
                groups[i].push_back(a);
                groups[i].push_back(find_one(a, i));
            }
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    cout << "S\n";
    for(int i = 1; i <= N; i++) {
        if(groups[i].size()) {
            sort(groups[i].begin(), groups[i].end());
            for(int t: groups[i])
                cout << t << " ";
            cout << '\n';
        }
    }
}
