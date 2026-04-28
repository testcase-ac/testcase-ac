#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;
  vector<int> B(N);
  for (int i = 0; i < N; i++) cin >> B[i];

  map<int, int> t; int l = 0;
  multiset<int> vals;
  auto inc = [&](int x) {
    if (t.count(x)) vals.erase(vals.find(t[x]));

    t[x]++;
    vals.insert(t[x]);
  };
  auto dec = [&](int x) {
    vals.erase(vals.find(t[x]));
    t[x]--;

    if (t[x] == 0) t.erase(x);
    else vals.insert(t[x]);
  };

  int ans = 0;
  for (int i = 0; i < N; i++) {
    inc(B[i]);
    while (vals.size() > K + 1) {
      dec(B[l]);
      l++;
    }
    ans = max(ans, *vals.rbegin());
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
