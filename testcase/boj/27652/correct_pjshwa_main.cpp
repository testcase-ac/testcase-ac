#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

class Trie {
public:
  ll siz = 0;

  // Children Nodes
  Trie* t[26];
  bool v[26];

  Trie() {
    memset(v, 0, sizeof(v));
  }

  void add(string &str, int val, int idx) {
    if (idx == str.size()) return;

    int c = str[idx] - 'a';
    if (!v[c]) t[c] = new Trie(), v[c] = true;
    t[c]->siz++;
    t[c]->add(str, val, idx + 1);
  }

  void del(string &str, int val, int idx) {
    if (idx == str.size()) return;

    int c = str[idx] - 'a';
    t[c]->siz--;
    t[c]->del(str, val, idx + 1);
  }
};

void solve() {
  int Q; cin >> Q;
  Trie* t_pre = new Trie();
  Trie* t_suf = new Trie();

  while (Q--) {
    string op, tar; cin >> op >> tar;
    if (op == "add") {
      string str; cin >> str;
      if (tar == "A") {
        t_pre->add(str, 0, 0);
      }
      else {
        reverse(str.begin(), str.end());
        t_suf->add(str, 0, 0);
      }
    }
    if (op == "delete") {
      string str; cin >> str;
      if (tar == "A") {
        t_pre->del(str, 0, 0);
      }
      else {
        reverse(str.begin(), str.end());
        t_suf->del(str, 0, 0);
      }
    }
    if (op == "find") {
      ll z = tar.size();
      ll res_l[z]{}, res_r[z]{};
      Trie* cur;

      cur = t_pre;
      for (int i = 0; i < z; i++) {
        int c = tar[i] - 'a';
        if (!cur->v[c]) break;

        res_l[i] = cur->t[c]->siz;
        cur = cur->t[c];
      }

      cur = t_suf;
      for (int i = z - 1; i >= 0; i--) {
        int c = tar[i] - 'a';
        if (!cur->v[c]) break;

        res_r[i] = cur->t[c]->siz;
        cur = cur->t[c];
      }

      ll res = 0;
      for (int i = 0; i < z - 1; i++) {
        res += res_l[i] * res_r[i + 1];
      }
      cout << res << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
