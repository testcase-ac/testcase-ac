#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN + 1], vis[MAXN + 1];

void solve() {
  int N, K, x; string S; cin >> N >> K >> S;
  for (int i = 1; i <= N; i++) cin >> x, A[x] = i;
  sort(S.begin(), S.end());

  string T(N, ' ');
  for (int i = 1; i <= N; ++i) {
    if (vis[i]) continue;

    vector<int> C{i};
    while (A[C.back()] != i) C.push_back(A[C.back()]);

    int Z = C.size();
    for (int j = 0; j < Z; ++j) {
      vis[C[j]] = 1;
      T[C[(j + K) % Z] - 1] = S[C[j] - 1];
    }
  }

  cout << T << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
