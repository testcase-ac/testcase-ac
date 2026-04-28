#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N;
  cin >> N;
  vector<pair<string, string>> topics;
  for (int i = 0; i < N; i++) {
    string a, b;
    cin >> a >> b;
    topics.emplace_back(a, b);
  }

  int ans = 0;
  for (int state = 0; state < (1 << N); state++) {
    set<string> f, s;
    for (int i = 0; i < N; i++) {
      if (state & (1 << i)) continue;
      f.insert(topics[i].first);
      s.insert(topics[i].second);
    }

    bool able = true;
    for (int i = 0; i < N; i++) {
      if (state & (1 << i)) {
        if (f.count(topics[i].first) && s.count(topics[i].second)) continue;

        able = false;
        break;
      }
    }

    if (able) ans = max(ans, __builtin_popcount(state));
  }

  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
