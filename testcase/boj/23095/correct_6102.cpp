#include <bits/stdc++.h>
using namespace std;
char arr[102][102];
vector<vector<int>> adj;
vector<char> seen;
vector<pair<int,int>> nodes;
vector<tuple<int,int,int,int>> ans;
int N;
char tgt;
bool same_set(int r1, int c1, int r2, int c2) {
    if(tgt == 'R') {
        return r1 == r2 || c1 == c2;
    } else if(tgt == 'Q') {
        return r1 == r2 || c1 == c2 || abs(r1 - r2) == abs(c1 - c2);
    } else if(tgt == 'B') {
        return abs(r1 - r2) == abs(c1 - c2);
    } else if(tgt == 'N') {
        int d1 = abs(r1 - r2), d2 = abs(c1 - c2);
        return (d1 == 1 && d2 == 2) || (d1 == 2 && d2 == 1);
    } else if(tgt == 'K') {
        int d1 = abs(r1 - r2), d2 = abs(c1 - c2);
        return d1 <= 1 && d2 <= 1;
    }
}
void dfs(int i, int p) {
    if(seen[i]) return;
    seen[i] = 1;
    for(int a: adj[i]) {
        dfs(a, i);
    }
    if(p != -1)
        ans.push_back({nodes[i].first, nodes[i].second, nodes[p].first, nodes[p].second});
}
int main() {
    cin >> N >> tgt;
    // 1851
    for(int i=1; i<=N; i++) {
        cin >> (arr[i]+1);
    }
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            if(arr[i][j] == tgt) {
                nodes.push_back({i, j});
            }
        }
    }
    adj.resize(nodes.size());
    seen.resize(nodes.size());
    // printf("node size = %d\n", nodes.size());
    for(int i=0; i<nodes.size(); i++) {
        auto [r1, c1] = nodes[i];
        for(int j=0; j<nodes.size(); j++) {
            if(i == j) continue;
            auto [r2, c2] = nodes[j];
            if(same_set(r1, c1, r2, c2)) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    dfs(0, -1);
    if(ans.size() != nodes.size() - 1) {
        return !(cout << "NO");
    }
    cout << "YES\n";
    for(auto [a, b, c, d]: ans) {
        cout << a << ' ' << b  << ' ' << c << ' ' << d << '\n';
    }
    
}
