#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e4;
vector<int> rules[MAX + 1];
int pt[MAX + 1], res[MAX + 1], cards[MAX + 1];
int C;
map<int, vector<int>> c2p;
vector<int> cur;

void dfs(int i) {
  if (i == C) {
    for (int p : cur) cout << p << ' ';
    cout << '\n';
    exit(0);
  }

  int card = res[i];
  for (int p : c2p[card]) {
    if (pt[p] == rules[p].size()) continue;
    int rule = rules[p][pt[p]];
    int pcard = cards[rule];
    
    if (card == pcard) {
      pt[p]++;
      cur.push_back(p);
      dfs(i + 1);
      cur.pop_back();
      pt[p]--;
    }
  }
}

void solve() {
  int N;
  cin >> N >> C;
  for (int i = 0; i < C; i++) cin >> res[i];
  for (int i = 1; i <= N; i++) {
    int K;
    cin >> K;
    rules[i].resize(K);
    for (int j = 0; j < K; j++) cin >> rules[i][j];
  }
  for (int i = 1; i <= C; i++) {
    string S;
    cin >> S >> cards[i];
  }

  for (int i = 1; i <= N; i++) for (int j : rules[i]) c2p[cards[j]].push_back(i);

  dfs(0);
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
