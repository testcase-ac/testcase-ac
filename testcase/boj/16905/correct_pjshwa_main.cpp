#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct BitTrieNode {
  // Children Nodes
  BitTrieNode* t[2];
  bool v[2]{};
};

class BitTrie {
  BitTrieNode* root;

public:

  BitTrie() {
    root = new BitTrieNode();
  }

  int find_xor_max(int num) {
    BitTrieNode* cur = root;
    int ret = 0;
    for (int i = 28; i >= 0; --i) {
      int c = (num >> i) & 1;
      if (cur->v[c ^ 1]) {
        ret |= (1 << i);
        cur = cur->t[c ^ 1];
      }
      else cur = cur->t[c];
    }
    return ret;
  }

  void add(int num) {
    BitTrieNode* cur = root;
    for (int i = 28; i >= 0; --i) {
      int c = (num >> i) & 1;
      if (!cur->v[c]) {
        cur->t[c] = new BitTrieNode();
        cur->v[c] = true;
      }
      cur = cur->t[c];
    }
  }
};

const int MAX = 1000;
int V[MAX], U[MAX];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> V[i];
  for (int i = 0; i < M; ++i) cin >> U[i];

  vector<int> VO, VE, UO, UE;
  for (int i = 0; i < N; ++i) {
    int x = 0;
    for (int j = i; j < N; ++j) {
      x ^= V[j];
      ((j - i) % 2 ? VE : VO).push_back(x);
    }
  }
  for (int i = 0; i < M; ++i) {
    int x = 0;
    for (int j = i; j < M; ++j) {
      x ^= U[j];
      ((j - i) % 2 ? UE : UO).push_back(x);
    }
  }

  int ans = 0;
  ans = max(ans, *max_element(VE.begin(), VE.end()));
  ans = max(ans, *max_element(UE.begin(), UE.end()));

  BitTrie* t = new BitTrie();
  for (int o : VO) t->add(o);
  for (int o : UO) ans = max(ans, t->find_xor_max(o));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
