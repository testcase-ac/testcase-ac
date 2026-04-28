#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e6;
int p[MAX];

void solve() {
  int N; cin >> N;
  iota(p, p + N, 1);

  if (N % 4 == 2) {
    for (int i = 2; i < N; i += 4) swap(p[i], p[i + 1]);
  }
  else {
    for (int i = 1; i < N; i += 4) swap(p[i], p[i + 1]);
  }

  cout << "YES\n";
  for (int i = 0; i < N; i++) cout << p[i] << " \n"[i == N - 1];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
