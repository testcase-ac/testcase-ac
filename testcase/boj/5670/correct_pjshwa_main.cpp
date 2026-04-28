#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class TrieNode {
public:
  bool valid;
  int child[26], ccnt;

  TrieNode() {
    valid = false;
    ccnt = 0;
    memset(child, -1, sizeof(child));
  }
};

class Trie {
  string tmp;
private:
  int _newNode() {
    TrieNode tmp;
    trie.push_back(tmp);
    return trie.size() - 1;
  }

  void _add(string &str, int node, int idx) {
    if (idx == str.size()) {
      trie[node].valid = true; return;
    }
    int c = str[idx] - 'a';
    if (trie[node].child[c] == -1) {
      int next = _newNode();
      trie[node].ccnt++;
      trie[node].child[c] = next;
    }
    _add(str, trie[node].child[c], idx + 1);
  }
public:
  vector<TrieNode> trie;

  Trie() {
    _newNode();
  }

  void add(string &str) {
    _add(str, 0, 0);
  }

  int presses(string &str) {
    int now = 0, res = 0;
    for (int i = 0; i < str.size(); i++) {
      int c = str[i] - 'a';
      if (i == 0 || (trie[now].ccnt + trie[now].valid) > 1) res++;
      now = trie[now].child[c];
    }
    return res;
  }

};

int n;
void solve() {
  Trie *t = new Trie();
  vector<string> words(n);
  for (int i = 0; i < n; i++) cin >> words[i], t->add(words[i]);

  int ans = 0;
  for (int i = 0; i < n; i++) ans += t->presses(words[i]);

  cout << fixed << setprecision(2) << (double)ans / n << '\n';
  delete t;
}

int main() {
  fast_io();

  while (cin >> n) solve();
}
