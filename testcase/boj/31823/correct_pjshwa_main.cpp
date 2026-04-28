#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<int> max_str(N, 0);
  vector<string> names(N);
  set<int> uniq_max_str;

  for (int i = 0; i < N; ++i) {
    int str = 0;
    for (int j = 0; j < M; ++j) {
      string o; cin >> o;
      if (o == ".") ++str;
      else {
        if (str > max_str[i]) max_str[i] = str;
        str = 0;
      }
    }
    if (str > max_str[i]) max_str[i] = str;
    uniq_max_str.insert(max_str[i]);
    cin >> names[i];
  }

  cout << uniq_max_str.size() << '\n';
  for (int i = 0; i < N; ++i) cout << max_str[i] << ' ' << names[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
