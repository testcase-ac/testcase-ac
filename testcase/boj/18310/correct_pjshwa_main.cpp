#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int P[MAX + 1];

void solve() {
  int N;
  cin >> N;

  ll val = 0;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    val += x;
    P[x]++;
  }

  int left = 0, ans;
  ll cur = val;
  for (int i = 1; i <= MAX; i++) {
    int right = N - left;
    cur += (left - right);
    if (cur < val) {
      ans = i;
      cur = val;
    }
    left += P[i];
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
