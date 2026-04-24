#include <bits/stdc++.h>
using namespace std;
#define int long long
int f(char c) {
    switch(c) {
    	case 'A':
    	return 0;
    	case 'C':
    	return 1;
    	case 'G':
    	return 2;
    	case 'T':
    	return 3;
    }
    return -123456789;
}
struct node {
	int nxt[4], fail;
	bool leaf;
	node() {
		memset(nxt, 0, sizeof nxt);
		fail = 0;
		leaf = 0;
	}
	int& operator[](int t) {
		return nxt[t];
	}
};
struct Aho {
	vector<node> trie;
	Aho(vector<string> &v) {
		trie.emplace_back();
		for(string& s: v) {
			add(s);
		}
		queue<int> que;
		for(int i=0; i<4; i++) {
			if(trie[0][i])
				que.push(trie[0][i]);
		}
		while(que.size()) {
			int q = que.front();
			que.pop();
			for(int i=0; i<4; i++) {
				if(trie[q][i]) {
					int cur = trie[q].fail;
					while(cur && !trie[cur][i])
						cur = trie[cur].fail;
					cur = trie[cur][i];
					trie[trie[q][i]].fail = cur;

					if(trie[cur].leaf) trie[trie[q][i]].leaf = 1;
					que.push(trie[q][i]);
				}
			}
		}
	}
	void add(const string &s) {
		int cur = 0;
		for(char c: s) {
			int t = f(c);
			if(!trie[cur][t]) {
				trie[cur][t] = trie.size();
				trie.emplace_back();
			}
			cur = trie[cur][t];
		}
		trie[cur].leaf = 1;
	}
	int query(const string& s) {
		int cur = 0, ans = 0;
		for(char c: s) {
			int t = f(c);
			while(cur && !trie[cur][t]) {
				cur = trie[cur].fail;
			}
			cur = trie[cur][t];
			if(trie[cur].leaf)
				ans++;
		}
		return ans;
	}
};
void solve() {
	int n, m;
	cin >> n >> m;
	string s, t;
	cin >> s >> t;
	vector<string> v;
	v.push_back(t);
	for(int i=0; i<m; i++) {
		for(int j=i+1; j<m; j++) {
			string k = t.substr(0, i), tmp = t.substr(i, j-i+1);
			reverse(tmp.begin(), tmp.end());
			k += tmp;
			k += t.substr(j+1);
			v.push_back(k);
		}
	}
	Aho aho(v);
	cout << aho.query(s) << '\n';
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	for(int t=1; t<=T; t++) {
		solve();
	}
}
