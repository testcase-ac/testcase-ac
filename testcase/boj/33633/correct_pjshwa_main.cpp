#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<ll> U = {1};
  while (--N) {
    vector<ll> nU;
    for (auto e : U) {
      nU.push_back(e * 2);
      if (e > 4 && e % 6 == 4) nU.push_back((e - 1) / 3);
    }
    U = nU;
  }

  sort(U.begin(), U.end());
  cout << U.size() << '\n';
  for (auto e : U) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
