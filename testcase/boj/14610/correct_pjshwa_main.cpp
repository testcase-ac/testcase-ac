#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool S[10];
int C[100], B[100][10];

void solve() {
  int N, M;
  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    cin >> C[i];
    if (C[i] == 0 || C[i] == M) return cout << "NO\n", void();
    for (int j = 0; j < M; j++) {
      cin >> B[i][j];
      if (B[i][j] == 1) {
        S[j] = true;
        C[i]--;
      }
    }
  }

  for (int j = 0; j < M; j++) {
    if (S[j]) continue;

    bool ok = false;
    for (int i = 0; i < N; i++) {
      if (C[i] > 0 && B[i][j] == -1) {
        C[i]--;
        B[i][j] = 1;
        ok = true;
        break;
      }
    }
    if (!ok) return cout << "NO\n", void();
  }

  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
