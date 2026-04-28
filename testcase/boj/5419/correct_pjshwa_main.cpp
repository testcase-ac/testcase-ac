#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
typedef long long ll;
using namespace std;

const int MAX = 1e5 + 1;
int tree[1 << 18];

class SegmentTree {

public:
  SegmentTree() {
    n = MAX;
    memset(tree, 0, sizeof(tree));
  }

  void inc(int P) {
    __add(0, 0, n - 1, P, 1);
  }

  void dec(int P) {
    __add(0, 0, n - 1, P, -1);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

struct Point {
  int x, y;

  bool operator< (const Point &p) const {
    return x == p.x ? y > p.y : x < p.x;
  }
};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

void solve() {
  int n;
  cin >> n;
  vector<Point> xys(n);
  vector<int> ys(n);
  unordered_map<int, int, custom_hash> comp;

  for (int i = 0; i < n; i++) {
    cin >> xys[i].x >> xys[i].y;
    ys.emplace_back(xys[i].y);
  }
  sort(xys.begin(), xys.end());
  compress(ys);
  for (int i = 0; i < ys.size(); i++) comp[ys[i]] = i;

  SegmentTree s;
  for (int i = 0; i < n; i++) s.inc(comp[xys[i].y]);

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    s.dec(comp[xys[i].y]);
    ans += s.query(0, comp[xys[i].y]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
