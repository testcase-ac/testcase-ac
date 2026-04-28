#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5 + 10;
int A[MAX];

struct SegmentTree {
  vector<ll> t; ll (*op)(ll, ll);
  SegmentTree(ll e, ll f(ll, ll)): op(f) { t.resize(2 * MAX,e); }
  void update(int k, ll x) {
    for (t[k += MAX] += x; (k /= 2) >= 1; t[k] = op(t[2 * k], t[2 * k + 1]));
  }
  ll query(int a, int b) {
    ll r = t[0];
    for (a += MAX, b += MAX; a <= b; ++a /= 2, --b /= 2) {
      if (a & 1) r = op(r, t[a]);
      if (~b & 1) r = op(r, t[b]);
    }
    return r;
  }
};

void solve() {
  int N; cin >> N;

  SegmentTree rsq(0, [](ll x, ll y) { return x + y; });
  ll sum = 0; map<ll, ll> by_num;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    
    ll addend = rsq.query(A[i] + 1, N);
    sum += addend;
    by_num[A[i]] += addend;
    rsq.update(A[i], 1);
  }

  vector<ll> ans(N);
  for (int i = N - 1; i >= 0; i--) {
    sum -= by_num[i];
    ans[i] = sum;
  }

  for (int i = 0; i < N; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
