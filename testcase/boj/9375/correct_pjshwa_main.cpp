#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int t, n;
  map<string, int> m;
  string s;

  cin >> t;
  while (t--) {
    cin >> n;
    m.clear();

    while (n--) {
      cin >> s >> s;
      if (!m.count(s)) m[s] = 0;
      m[s]++;
    }

    long long ans = 1;
    for (auto e : m) ans *= (e.second + 1);
    cout << ans - 1 << '\n';
  }
}
