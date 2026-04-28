#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
vector<int> graph[MAX + 1];
bool neg[MAX + 1], bombed[MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  while (M--) {
    int Ui, Vi;
    cin >> Ui >> Vi;
    graph[Ui].push_back(Vi);
    graph[Vi].push_back(Ui);
  }

  int K;
  cin >> K;
  set<int> P;
  for (int i = 0; i < K; i++) {
    int x;
    cin >> x;
    P.insert(x);
  }

  for (int i = 1; i <= N; i++) {
    if (P.count(i)) continue;

    neg[i] = 1;
    for (int u : graph[i]) neg[u] = 1;
  }

  for (int i = 1; i <= N; i++) {
    if (neg[i]) continue;

    bombed[i] = 1;
    for (int u : graph[i]) bombed[u] = 1;
  }

  for (int x : P) {
    if (!bombed[x]) return cout << "-1\n", void();
  }

  int T = 0;
  for (int i = 1; i <= N; i++) if (!neg[i]) T++;

  cout << T << '\n';
  for (int i = 1; i <= N; i++) if (!neg[i]) cout << i << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
