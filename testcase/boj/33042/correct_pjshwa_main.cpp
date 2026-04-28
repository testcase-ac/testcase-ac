#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  map<string, int> tal;
  for (int i = 1; i <= N; ++i) {
    string S; cin >> S;
    if (++tal[S] == 5) return cout << i << '\n', void();
  }
  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
