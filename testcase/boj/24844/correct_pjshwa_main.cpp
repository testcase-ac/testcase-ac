#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4;
bitset<MAX + 1> banned[MAX + 1];
ll ans[MAX + 1];

tuple<ll, int, int> ask(int l, int r) {
  cout << "? " << l << ' ' << r << endl;
  ll x; int i, j;
  cin >> x >> i >> j;
  return {x, i, j};
}

void solve() {
  int N;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    for (int j = i; j >= 1; j--) {
      if (banned[i][j]) continue;

      auto [s, lb, rb] = ask(j, i);

      banned[rb][lb] = true;
      for (int k = i - 1; k >= j; k--) s -= ans[k];
      ans[i] = s;
      break;
    }
  }

  cout << "!\n";
  for (int i = 1; i <= N; i++) cout << ans[i] << ' ';
  cout << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
