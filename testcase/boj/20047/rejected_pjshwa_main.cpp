#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int d[MAX + 1][3], N;
string S, T, U = "";
bool f;

bool r(int i, int state) {
  if (d[i][state] != -1) return d[i][state];
  if (i == N) return d[i][state] = state == 2;

  bool res = false;
  int si = i - state;

  if (si < S.size() && S[si] == T[i]) res |= r(i + 1, state);
  if (state < 2 && U[state] == T[i]) res |= r(i + 1, state + 1);

  return d[i][state] = res;
}

void solve() {
  cin >> N >> S >> T;
  int i, j;
  cin >> i >> j;

  if (S == T) return cout << "YES\n", void();
  if (S[i] == S[j]) return cout << "NO\n", void();

  string NS = "";
  for (int l = 0; l < S.size(); l++) {
    if (l == i || l == j) U += S[l];
    else NS += S[l];
  }
  S = NS;

  memset(d, -1, sizeof(d));
  if (r(0, 0)) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
