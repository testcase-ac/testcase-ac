#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX];

bool consec(string s) {
  int n = s.size();
  for (int i = 0; i < n - 1; i++) {
    if (s[i + 1] != s[i] + 1) return false;
  }
  return true;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i];

  int ans = -1;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    if (i == j) continue;
    if (consec(to_string(a[i] * a[j]))) ans = max(ans, a[i] * a[j]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
