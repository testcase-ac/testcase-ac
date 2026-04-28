#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S; int N, H;
vector<int> C;

void dfs(int i) {
  if (i == H) {
    vector<int> P(2 * H - 1, 0);
    for (int i = 0; i < H; ++i) for (int j = 0; j < H; ++j) {
      P[i + j] += C[i] * C[j];
      P[i + j] %= 10;
    }

    bool f = true;
    for (int i = 0; i < 2 * H - 1; ++i) if (P[i] != S[i] - '0') {
      f = false;
      break;
    }
    if (!f) return;

    for (int x : C) cout << x; cout << '\n';
    exit(0);
  }

  for (int d = 0; d < 10; ++d) {
    C.push_back(d);

    int Z = C.size(); vector<int> P(Z, 0);
    for (int i = 0; i < Z; ++i) for (int j = 0; j < Z; ++j) {
      if (i + j >= Z) continue;
      P[i + j] += C[i] * C[j];
      P[i + j] %= 10;
    }

    bool f = true;
    for (int i = 0; i < Z; ++i) if (P[i] != S[i] - '0') {
      f = false;
      break;
    }
    if (f) dfs(i + 1);

    C.pop_back();
  }
}

void solve() {
  cin >> S; N = S.size();
  if (N % 2 == 0) return cout << "-1\n", void();

  H = (N + 1) / 2;
  dfs(0);
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
