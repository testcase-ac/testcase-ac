#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1e5 + 10, INF = 1e18;

struct SegmentTree {
  vector<ll> t; ll (*op)(ll,ll);
  SegmentTree(ll e, ll f(ll,ll)): op(f) {t.resize(2*MAX,e);}
  void update(int k, ll x) {
    for (t[k += MAX] = x; (k /= 2) >= 1; t[k] = op(t[2*k],t[2*k+1]));
  }
  ll query(int a, int b) {
    ll r = t[0];
    for (a += MAX, b += MAX; a <= b; ++a /= 2, --b /= 2) {
      if (a&1) r = op(r,t[a]);
      if (~b&1) r = op(r,t[b]);
    }
    return r;
  }
};

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, E; cin >> N >> E;
  vector<tii> A(N);
  for (int i = 0; i < N; i++) {
    int x, y, c; cin >> x >> y >> c;
    A[i] = {x, y, c};
  }
  sort(A.begin(), A.end(), [](tii a, tii b) {
    return get<1>(a) > get<1>(b);
  });

  SegmentTree rxq_r(-INF, [](ll x,ll y){return max(x,y);}),
              rxq_l(-INF, [](ll x,ll y){return max(x,y);});

  for (int x = 0; x < MAX; x++) {
    rxq_r.update(x, 0);
    rxq_l.update(x, -E);
  }

  ll ly = -1, ans = 0;
  vector<pii> xs;

  auto process = [&]() {
    sort(xs.begin(), xs.end());

    ll pre_l = rxq_l.query(0, MAX - 1) - E, pre_r = rxq_r.query(0, MAX - 1) - E;

    for (auto [x, c] : xs) {
      ll ori = rxq_r.query(x, x);
      ll nxt = max(rxq_r.query(0, x) + c, pre_l + c);
      if (nxt > ori) rxq_r.update(x, nxt);
    }

    reverse(xs.begin(), xs.end());

    for (auto [x, c] : xs) {
      ll ori = rxq_l.query(x, x);
      ll nxt = max(rxq_l.query(x, MAX - 1) + c, pre_r + c);
      if (nxt > ori) rxq_l.update(x, nxt);
    }

    ans = max(ans, rxq_r.query(0, MAX - 1));
    ans = max(ans, rxq_l.query(0, MAX - 1));

    xs.clear();
  };

  for (int i = 0; i < N; i++) {
    auto [x, y, c] = A[i];

    if (ly == y) xs.push_back({x, c});
    else {
      process();
      xs.push_back({x, c});
      ly = y;
    }
  }
  process();

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
