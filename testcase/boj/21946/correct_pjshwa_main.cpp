#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  ll tmask = (1LL << N) - 1;
  vector<ll> masks;
  for (int i = 0; i < M; ++i) {
    ll q, mask = 0; cin >> q;
    while (q--) {
      int x; cin >> x;
      mask |= (1LL << (x - 1));
    }
    masks.push_back(mask);
  }

  vector<int> candidates;
  for (int s = 0; s < (1 << M); ++s) {
    ll mask = tmask;
    for (int i = 0; i < M; ++i) {
      if (s & (1 << i)) mask ^= masks[i];
    }
    if (mask == 0) candidates.push_back(s);
  }

  // sort lexicographically
  sort(candidates.begin(), candidates.end(), [&](int a, int b) {
    int cnt_a = __builtin_popcount(a), cnt_b = __builtin_popcount(b);
    if (cnt_a != cnt_b) return cnt_a < cnt_b;
    for (int i = 0; i < M; ++i) {
      if ((a & (1 << i)) != (b & (1 << i))) return (a & (1 << i)) > (b & (1 << i));
    }
    return false;
  });

  int ans = candidates[0];
  cout << __builtin_popcount(ans) << '\n';
  for (int i = 0; i < M; ++i) {
    if (ans & (1 << i)) cout << i + 1 << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
