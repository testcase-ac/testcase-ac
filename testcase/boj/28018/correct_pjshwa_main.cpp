#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int D[MAX + 10];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    int s, e; cin >> s >> e;
    D[s]++; D[e + 1]--;
  }
  for (int i = 0; i < MAX; i++) D[i + 1] += D[i];

  int Q; cin >> Q;
  while (Q--) {
    int x; cin >> x;
    cout << D[x] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
