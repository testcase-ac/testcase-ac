#include <bits/stdc++.h>
using namespace std;
const int SQRT = 175;
struct node {
    short nxt[26];
    int cnt;
    node() {
        memset(nxt, -1, sizeof nxt);
        cnt = 0;
    }
};
struct trie {
    vector<node> nodes;
    trie() {
        nodes.emplace_back();
    }
    void add(string s) {
        int cur = 0;
        for(char c: s) {
            int t = c - 'a';
            if(nodes[cur].nxt[t] == -1) {
                nodes[cur].nxt[t] = nodes.size();
                nodes.emplace_back();
                nodes.back().cnt++;
            } else {
                nodes[nodes[cur].nxt[t]].cnt++;
            }
            cur = nodes[cur].nxt[t];
        }
    }
    int search(string s) {
        int ans = 0, cur = 0;
        for(char c: s) {
            int t = c - 'a';
            if(nodes[cur].nxt[t] == -1)
                break;
            cur = nodes[cur].nxt[t];
            ans += nodes[cur].cnt; // ! order

        }
        return ans;
    }
};
trie tries[SQRT];
map<string, int> first_pos;
vector<string> arr[SQRT];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i=0; i<N; i++) {
        string s;
        cin >> s;
        int buk = i / SQRT;
        arr[buk].push_back(s);
        tries[buk].add(s);
        //printf("add to buk = %d\n", buk);
        if(!first_pos.count(s)) {
            first_pos[s] = i;
        }
    }
    int Q;
    cin >> Q;
    while(Q--) {
        string s;
        cin >> s;
        auto it = first_pos.find(s);
        int ans = 0;
        if(it == first_pos.end()) { // not found
            for(int buk=0; buk<=((N-1)/SQRT); buk++) {
                ans += tries[buk].search(s);
                ans += arr[buk].size();
            }
        } else {
            int edp = it->second;
            int edbuk = edp / SQRT, edpos = edp % SQRT;
            for(int buk=0; buk<edbuk; buk++) {
                ans += tries[buk].search(s);
                ans += arr[buk].size();
            }
            for(int i=0; i<edpos; i++) {
                string &cst = arr[edbuk][i];
                ans++;
                for(int j=0; j<cst.size() && j<s.size(); j++) {
                    if(cst[j] != s[j]) {
                        break;
                    }
                    ans++;
                }
            }
            ans += s.size() + 1;
        }
        cout << ans << '\n';
    }
}
