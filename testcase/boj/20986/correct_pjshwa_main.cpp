#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000, INF = 0x3f3f3f3f;
int H[MAX + 1], d[MAX + 10], inv[MAX + 1];

struct SegmentTree {
  vector<ll> t; ll (*op)(ll, ll);
  SegmentTree(ll e, ll f(ll, ll)): op(f) { t.resize(2 * MAX,e); }
  void update(int k, ll x) {
    for (t[k += MAX] = x; (k /= 2) >= 1; t[k] = op(t[2 * k], t[2 * k + 1]));
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
  for (int i = 1; i <= N; i++) cin >> H[i];

  SegmentTree rsq(0, [](ll x, ll y) { return x + y; });
  
  // if lower bound is l, how many moves are needed?
  for (int l = N; l >= 1; l--) {
    vector<int> B;
    for (int i = 1; i <= N; i++) {
      if (H[i] >= l) B.push_back(H[i]);
    }

    int z = B.size();
    for (int i = 0; i < z; i++) {
      inv[B[i]] = i;
      rsq.update(i, 0);
    }

    int res = INF, acc = 0;
    for (int u = l; u <= N; u++) {
      acc += inv[u] - rsq.query(inv[u] + 1, z - 1);
      res = min(res, acc + d[u + 1]);
      rsq.update(inv[u], 1);
    }

    d[l] = res;
  }

  cout << d[1] << '\n';
}

// 1. TC 간 전역 변수 초기화
// 2. int overflow 체크
// 3. edge case 체크
// 4. 자주 하는 실수
//   - long long에 sqrt() 사용
//   - multiset::count() 사용
int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
