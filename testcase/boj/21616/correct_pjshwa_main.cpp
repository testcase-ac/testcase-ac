#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e6;
int R[MAX + 1], C[MAX + 1];

void solve() {
  int N, M, Q; cin >> N >> M >> Q;
  while (Q--) {
    string U; int V; cin >> U >> V;
    if (U == "R") R[V] ^= 1;
    else C[V] ^= 1;
  }

  ll rcnt = 0, ccnt = 0;
  for (int i = 1; i <= N; i++) rcnt += R[i];
  for (int i = 1; i <= M; i++) ccnt += C[i];
  
  ll ans = rcnt * (M - ccnt) + ccnt * (N - rcnt);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
