#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX + 1];

void solve() {
  int N, M; cin >> N >> M;

  fill(A, A + N + 1, 1);
  while (M--) {
    int a, b, c; cin >> a >> b >> c;
    A[a] = max(A[a], c); A[b] = max(A[b], c);
  }

  for (int i = 1; i <= N; i++) cout << A[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
