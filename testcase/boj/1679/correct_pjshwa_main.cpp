#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, MAXV = 50001;
int A[MAX + 1];
bool vis[MAXV + 1];

void solve() {
  int N, K; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  cin >> K;

  vis[0] = 1;
  for (int it = 0; it < K; it++) {
    vector<int> nxt;
    for (int v = 0; v <= MAXV; v++) {
      if (vis[v]) nxt.push_back(v);
    }

    while (!nxt.empty()) {
      int v = nxt.back(); nxt.pop_back();
      for (int i = 0; i < N; i++) vis[v + A[i]] = 1;
    }
  }

  for (int v = 1; v <= MAXV; v++) {
    if (vis[v]) continue;

    if (v & 1) cout << "jjaksoon ";
    else cout << "holsoon ";

    cout << "win at " << v << '\n';

    return;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
