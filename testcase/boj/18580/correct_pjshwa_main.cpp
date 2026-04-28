#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int P[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> P[i];

  int a = 0;
  for (int i = 1; i < N; ++i) a += P[i] < P[i - 1];

  if (a == 0) cout << "Bob\n";
  else if (N & 1) cout << "Alice\n";
  else cout << "Bob\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
