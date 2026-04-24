#include <bits/stdc++.h>
using namespace std;
const int MX = 10000;
#define int long long
vector<vector<int>> adj, adjt;
stack<int> st;
vector<char> seen;
vector<vector<int>> cc;
void dfs1(int i) {
    seen[i] = true;
    for(int a: adj[i]) {
        if(!seen[a])
            dfs1(a);
    }
    st.push(i);
}
void dfs2(int i) {
    seen[i] = true;
    cc.back().push_back(i);
    for(int a: adjt[i]) {
        if(!seen[a])
            dfs2(a);
    }
}
void scc(int v) {
    fill(seen.begin(), seen.end(), false);
    for(int i=0; i<v; i++)
        if(!seen[i])
            dfs1(i);
    fill(seen.begin(), seen.end(), false);
    while(!st.empty()) {
        int i = st.top();
        st.pop();
        if(!seen[i]) {
            cc.emplace_back();
            dfs2(i);
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    map<string, int> mp;
    vector<string> v;
    map<string, vector<string>> adj_raw;
    auto add_node = [&](string s) {
        if(mp.count(s))
            return;
        mp[s] = v.size();
        v.push_back(s);
    };
    for(int i=0; i<N; i++) {
        string s;
        cin >> s;
        add_node(s);
        int m;
        cin >> m;
        while(m--) {
            string t;
            cin >> t;
            add_node(t);
            adj_raw[s].push_back(t);
        }
    }
    adj.resize(v.size());
    adjt.resize(v.size());
    seen.resize(v.size());
    for(auto &[a, vec]: adj_raw) {
        for(string b: vec) {
            // printf("adding edge %s -> %s. number is %d -> %d\n", b.c_str(), a.c_str(), mp[b], mp[a]);
            adj[mp[b]].push_back(mp[a]);
            adjt[mp[a]].push_back(mp[b]);
        }
    }
    vector<int> score(v.size(), 1);
    scc(v.size());
    for(int i=0; i<cc.size(); i++) {
        for(int a: cc[i]) {
            // printf("score of %s is %d\n", v[a].c_str(), score[a]);
            for(int b: adj[a]) {
                if(find(cc[i].begin(), cc[i].end(), b) != cc[i].end()) {
                    continue;
                }
                // printf("added score of %s to %s\n", v[a].c_str(), v[b].c_str());
                score[b] += score[a];
            }
        }
    }
    string qry;
    cin >> qry;
    cout << score[mp[qry]] << '\n';
}
