#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
string A[MAX][MAX];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> A[i][j];

  set<string> ans;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (j < M - 1 && A[i][j] == A[i][j + 1]) ans.insert(A[i][j]);
    if (i < N - 1 && A[i][j] == A[i + 1][j]) ans.insert(A[i][j]);

    if (j < M - 2 && A[i][j] == A[i][j + 2]) ans.insert(A[i][j]);
    if (i < N - 2 && A[i][j] == A[i + 2][j]) ans.insert(A[i][j]);
  }

  if (ans.empty()) cout << "MANIPULATED\n";
  else for (auto& s : ans) cout << s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
