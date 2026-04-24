#include <bits/stdc++.h>
using namespace std;
struct node {
    int p, pind, link = -1, dp = -1, dep = 0;
    vector<pair<int, int>> _nxt, _go;
    bool leaf = 0;
    node(int p, int pind) : p(p), pind(pind) {
    }
    int nxt(int t) {
        for(auto &[k, v]: _nxt) {
            if(k == t) {
                return v;
            }
        }
        return -1;
    }
    int go(int t) {
        for(auto &[k, v]: _go) {
            if(k == t) {
                return v;
            }
        }
        return -1;
    }
    void nxt_add(int t, int v) {
        _nxt.push_back({t, v});
    }
    void go_add(int t, int v) {
        _go.push_back({t, v});
    }
};
inline int f(char c) {
    return c - 'a';
}
struct Aho {
    vector<node> trie;
    Aho() {
        trie.reserve(4500000);
        trie.emplace_back(0, 0);
    }
    void add(string &s) {
        int cur = 0;
        for(int i = 0; i < s.size(); i++) {
            int c = f(s[i]);
            int cur_nxt = trie[cur].nxt(c);
            if(cur_nxt == -1) {
                trie[cur].nxt_add(c, trie.size());
                cur_nxt = trie.size();
                trie.emplace_back(cur, c);
                trie.back().dep = trie[cur].dep + 1;
            }
            cur = cur_nxt;
        }
        trie[cur].leaf = 1;
    }
    int go(int v, int t) {
        int ret = trie[v].go(t);
        if(ret == -1) {
            int nxt = trie[v].nxt(t);
            if(nxt == -1)
                ret = (v == 0 ? 0 : go(getlink(v), t));
            else
                ret = nxt;
        }
        return ret;
    }
    int getlink(int v) {
        if(trie[v].link == -1) {
            if(v == 0 || trie[v].p == 0)
                trie[v].link = 0;
            else
                trie[v].link = go(getlink(trie[v].p), trie[v].pind);
        }
        return trie[v].link;
    }
    int getdp(int v) {
        if(trie[v].dp == -1) {
            if(!v)
                trie[v].dp = 0;
            else if(trie[v].leaf)
                trie[v].dp = trie[v].dep;
            else
                trie[v].dp = getdp(getlink(v));
        }
        return trie[v].dp;
    }
    vector<pair<int, int>> query(string &s) {
        int cur = 0;

        vector<pair<int, int>> ret;
        for(int i = 0; i < s.size(); i++) {
            // printf("query at %d\n", i);
            cur = go(cur, f(s[i]));
            int dpval = getdp(cur);

            if(dpval) {
                ret.emplace_back(i - dpval + 1, i);
                // printf("pushed back %d %d\n", i - dpval + 1, i);
            }
        }
        return ret;
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n;
    string s;
    cin >> s;
    Aho aho;
    cin >> m;
    for(int i = 0; i < m; i++) {
        string t;
        cin >> t;
        aho.add(t);
    }
    vector<pair<int, int>> ans = aho.query(s);
    sort(ans.begin(), ans.end(), [](pair<int, int> &a, pair<int, int> &b) {
        return a.first < b.first;
    });
    int ansv = 0, cur = 0, endat = 0;
    for(int i = 0, j = 0; i < s.size(); i++) {
        while(j < ans.size() && i == ans[j].first) {
            cur = 1;
            endat = max(endat, ans[j].second);
            j++;
        }
        if(!cur) {
            ansv++;
        }
        if(i == endat) {
            cur = 0;
        }
    }
    cout << ansv;
}
