#include <bits/stdc++.h>
using namespace std;
struct node {
	int nxt[26], go[26], p, pind, link = -1, dp = -1;
	bool leaf = 0;
	node() {
		memset(nxt, -1, sizeof nxt);
		memset(go, -1, sizeof go);
	}
};
inline int f(char c) {
	return c-'a';
}
struct Aho {
	vector<node> trie;
	int nxt = 1;
	Aho() {
		trie.resize(100007);
		trie[0].p = trie[0].link = 0;
	}
	void add(string &s) {
		int cur = 0;
		for(int i=0; i<s.size(); i++) {
			int &n = trie[cur].nxt[f(s[i])];
			if(n == -1)
				n = nxt++;
			trie[n].p = cur;
			trie[n].pind = f(s[i]);
			cur = n;
		}
		trie[cur].leaf = 1;
	}
	int go(int v, int t) {
		int& ret = trie[v].go[t];
		if(ret == -1) {
			if(trie[v].nxt[t] == -1)
				ret = (v == 0 ? 0 : go(getlink(v), t)); // trying to find suffix link from root results in infinite recursion
			else
				ret = trie[v].nxt[t];
		}
		return ret;
	}
	int getlink(int v) {
		if(trie[v].link == -1) {
			if(v == 0 || trie[v].p == 0)
				trie[v].link = 0; // if length is 0 or 1, only proper suffix is empty string. general case would lead to self.
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
				trie[v].dp = 1;
			else
				trie[v].dp = getdp(trie[v].p) || getdp(getlink(v));
		}
		return trie[v].dp;
	}
	bool query(string &s) {
		int cur = 0;
		for(int i=0; i<s.size(); i++) {
			cur = go(cur, f(s[i]));
			if(getdp(cur))
				return 1;
		}
		return 0;
	}
};

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	Aho aho;
	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		aho.add(s);
	}
	int q;
	cin >> q;
	while(q--) {
		string s;
		cin >> s;
		cout << (aho.query(s) ? "YES\n" : "NO\n");
	}
}
