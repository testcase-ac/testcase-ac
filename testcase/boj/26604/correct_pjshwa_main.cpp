#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> B(N);
  for (int i = 0; i < N; i++) cin >> B[i];

  vector<int> ans(N), A(N), vis(N + 1);
  iota(A.begin(), A.end(), 1);
  for (int i = N - 1; i >= 0; i--) {
    for (int j = 0; j <= i; j++) B[j] ^= A[j];
    ans[i] = B[i]; vis[ans[i]] = 1;

    vector<int> nA;
    for (int l = 1; l <= N; l++) if (!vis[l]) nA.push_back(l);
    A = nA;
  }

  for (int i = 0; i < N; i++) cout << ans[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
