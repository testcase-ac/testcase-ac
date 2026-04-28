#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, L; cin >> N >> L;

  vector<pll> A;
  for (int i = 0; i < N; ++i) {
    ll l, r; cin >> l >> r;
    A.emplace_back(l, r);
  }
  sort(A.begin(), A.end());

  ll p = 0, ans_x = 0;
  priority_queue<ll> wait;
  for (int i = 0; i < N; ++i) {
    auto [al, ar] = A[i];
    if (al > p) {
      ll t = wait.top(); wait.pop();
      p = t;
      ++ans_x;
    }
    assert(al <= p);
    wait.push(ar);
  }
  if (p < L) ++ans_x;
  cout << ans_x << ' ';

  ll max_y = N;
  vector<ll> xs;
  map<ll, int> dt;
  for (auto& [l, r] : A) {
    xs.push_back(l); ++dt[l];
    xs.push_back(r); --dt[r];
  }
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());

  ll cur_y = 0;
  for (ll x : xs) {
    if (x == L) break;
    cur_y += dt[x];
    max_y = min(max_y, cur_y);
  }
  cout << N + 1 - max_y << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
