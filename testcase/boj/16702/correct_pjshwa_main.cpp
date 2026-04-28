#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
ll d[MAX + 1];

void solve() {
  int N;
  cin >> N;
  cout << d[N] << '\n';
}

int main() {
  fast_io();

  for (int a = 1; a <= 100; a++) for (int b = a + 1; b <= 1000; b++) {
    for (int c = a * b * (b + 1); c <= MAX; c += a * b) {
      d[c]++;
    }
  }
  for (int i = 1; i <= MAX; i++) d[i] += d[i - 1];

  int t = 1;
  cin >> t;
  while (t--) solve();
}
