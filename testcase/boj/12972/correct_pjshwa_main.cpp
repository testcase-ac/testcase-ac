#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  map<int, int> t;
  set<int> a;
  for (int i = 0; i < N * N; i++) {
    int x;
    cin >> x;
    t[x]++;
    a.insert(-x);
  }

  vector<int> occ;
  for (auto k : a) {
    k = -k;

    // how many occurences of having itself as gcd of some bigger number?
    int it = 0;
    for (int e : occ) {
      int g = __gcd(k, e);
      if (g == k) it++;
    }

    for (int i = 0;; i++) {
      if (2 * i * it + i * i != t[k]) continue;

      for (int e : occ) {
        int g = __gcd(k, e);
        t[g] -= 2 * i;
      }

      for (int j = 0; j < i; j++) occ.push_back(k);
      break;
    }
  }

  for (int e : occ) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
