#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S, cur;
int N, ok, V[10];

void dfs(int i, int f) {
  if (i == N) {
    if (!f) {
      ok = 1;
      cout << cur << '\n';
    }
    return;
  }
  for (char c = '0'; c <= '9'; c++) {
    if (f && c < S[i]) continue;
    if (V[c - '0']) continue;

    V[c - '0'] = 1;
    cur += c;
    dfs(i + 1, f && c <= S[i]);
    cur.pop_back();
    V[c - '0'] = 0;

    if (ok) return;
  }
}

void solve() {
  cin >> S; N = S.size();
  if (N > 10) return cout << "-1\n", void();
  if (S == "9") return cout << "10\n", void();

  string biggest = "";
  for (int i = 0; i < N; ++i) biggest += '9' - i;
  if (biggest <= S) {
    S = "1";
    for (int i = 0; i < N; ++i) S += '0';
    N = S.size();
  }
  if (N > 10) return cout << "-1\n", void();

  memset(V, 0, sizeof V);
  ok = 0; dfs(0, 1);
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
