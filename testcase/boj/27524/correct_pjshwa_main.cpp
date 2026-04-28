#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

class Trie {
  // Children Nodes
  Trie* t[26];
  bool v[26];

public:
  // Max & min value of the subtree
  ll rmax = 0, rmin = 0;

  // Max & min value of children
  ll cmax = 0, cmin = 0;

  // Current value of node
  ll val = 0;

  Trie() {
    memset(v, 0, sizeof(v));
  }

  void add(string &str, int val, int idx) {
    if (idx == str.size()) {
      this->val = val;
      rmax = cmax + this->val;
      rmin = cmin + this->val;
      return;
    }

    int c = str[idx] - 'a';
    if (!v[c]) t[c] = new Trie(), v[c] = true;
    t[c]->add(str, val, idx + 1);

    cmax = 0, cmin = 0;
    for (int i = 0; i < 26; i++) {
      if (!v[i]) continue;
      cmax = max(cmax, t[i]->rmax);
      cmin = min(cmin, t[i]->rmin);
    }
    rmax = cmax + this->val;
    rmin = cmin + this->val;
  }

};

void solve() {
  Trie* t_pre = new Trie();
  Trie* t_suf = new Trie();

  int Q; cin >> Q;
  while (Q--) {
    string op, u; int x;
    cin >> op;
    if (op == "<") {
      cin >> u >> x;
      t_pre->add(u, x, 0);
    }
    if (op == ">") {
      cin >> u >> x;
      reverse(u.begin(), u.end());
      t_suf->add(u, x, 0);
    }
    if (op == "+") cout << t_pre->rmax + t_suf->rmax << '\n';
    if (op == "-") cout << t_pre->rmin + t_suf->rmin << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
