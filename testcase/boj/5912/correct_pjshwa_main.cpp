#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int dt[MAX + 2];

void solve() {
  int N, Q;
  cin >> N >> Q;
  while (Q--) {
    int l, r;
    cin >> l >> r;
    dt[l]++;
    dt[r + 1]--;
  }

  vector<int> s;
  int cur = 0;
  for (int i = 1; i <= N; i++) {
    cur += dt[i];
    s.push_back(cur);
  }
  sort(s.begin(), s.end());

  // Print the median
  cout << s[N / 2] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
