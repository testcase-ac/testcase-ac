#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N, K, ans;
vector<int> O;
void dfs(vector<int> V, int i) {
  int cur = 0;
  for (int i = 0; i < N; ++i) cur += V[i] == O[i];
  ans = max(ans, cur);

  if (i == K) return;

  for (int p = 0; p < N; ++p) {
    vector<int> W1 = V;
    for (int j = p + 1; j < N; ++j) W1[j - 1] = W1[j];
    W1[N - 1] = -1;
    dfs(W1, i + 1);

    vector<int> W2 = V;
    for (int j = N - 1; j > p; --j) W2[j] = W2[j - 1];
    W2[p] = -1;
    dfs(W2, i + 1);
  }
}

void solve() {
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    O.push_back(x);
  }

  vector<int> V;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    V.push_back(x);
  }

  dfs(V, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
