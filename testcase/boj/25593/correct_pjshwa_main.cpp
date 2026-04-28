#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;
const int hours[4] = {4, 6, 4, 10};

void solve() {
  int N;
  cin >> N;

  map<string, int> m;
  for (int i = 0; i < N; i++) {
    for (int w = 0; w < 4; w++) {
      for (int j = 0; j < 7; j++) {
        string s;
        cin >> s;
        if (s == "-") continue;

        m[s] += hours[w];
      }
    }
  }

  int minx = INF, maxx = -INF;
  for (auto [k, v] : m) {
    minx = min(minx, v);
    maxx = max(maxx, v);
  }

  if (maxx - minx <= 12) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
