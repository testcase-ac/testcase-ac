#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int A[MAXN], Kc[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 1; i < N; ++i) {
    if (A[i] > A[i - 1]) Kc[i] = Kc[i - 1] + 1;
    else if (A[i] < A[i - 1]) Kc[i] = Kc[i - 1] - 1;
    else Kc[i] = Kc[i - 1];
  }

  map<ll, int> acnt; int base = 0;
  for (int i = 0; i < N; ++i) {
    if (Kc[i] == 0) {
      if (A[i] == A[0]) ++base;
    } else {
      ll target = A[i] - A[0];
      if (target % Kc[i]) continue;
      ++acnt[target / Kc[i]];
    }
  }

  ll madd = 0, maddi = -1;
  for (auto& [v, c] : acnt) {
    if (madd < c) madd = c, maddi = v;
  }
  cout << base + madd << '\n' << maddi << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
