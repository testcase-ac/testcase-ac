#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX];

void solve() {
  int N, M, K;
  cin >> N >> M >> K;
  for (int i = 0; i < N; i++) cin >> a[i];
  sort(a, a + N);
  reverse(a, a + N);

  int s = M * K;
  for (int i = 0; i < N; i++) {
    s -= a[i];
    if (s <= 0) {
      cout << i + 1 << '\n';
      return;
    }
  }
  cout << "STRESS\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
