#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

using vint = vector<int>;
using vll = vector<ll>;
using vld = vector<ld>;
using vpii = vector<pii>;
using vpil = vector<pil>;
using vpli = vector<pli>;
using vpll = vector<pll>;

#define x first
#define y second
#define all(v) (v).begin(),(v).end()
#define ints(args...) int args; readln(args);
#define lls(args...) ll args; readln(args);
#define strs(args...) string args; readln(args);

template<typename... Args>
void readln(Args&... args) { ((cin >> args), ...); }
template<typename... Args>
void writeln(Args... args) { ((cout << args << " "), ...); cout << '\n'; }

int main() {
  ios::sync_with_stdio(false); cin.tie(nullptr);

  ints(n, m, w, h);
  vpii a(n + m);
  vint xs, ys;
  for(pii &p : a) {
    cin >> p.x >> p.y;
    xs.push_back(p.x + 1);
    xs.push_back(p.x - w);
    ys.push_back(p.y + 1);
    ys.push_back(p.y - h);
  }
  sort(all(xs));
  sort(all(ys));
  xs.erase(unique(all(xs)), xs.end());
  ys.erase(unique(all(ys)), ys.end());
  int A = xs.size(), B = ys.size();

  vector<vector<tuple<int, int, int>>> uv(A + 1);
  for(int i = 0; i < n + m; i++) {
    int sx = int(lower_bound(all(xs), a[i].x - w) - xs.begin());
    int ex = int(upper_bound(all(xs), a[i].x) - xs.begin() - 1);
    int sy = int(lower_bound(all(ys), a[i].y - h) - ys.begin());
    int ey = int(upper_bound(all(ys), a[i].y) - ys.begin() - 1);
    uv[sx].emplace_back(sy, ey, (i < n ? 1 : -1));
    uv[ex + 1].emplace_back(sy, ey, (i < n ? -1 : 1));
  }

  struct Seg {
    int sz;
    vint l;
    vpii mx, mn;
    Seg(int n) {
      for(sz = 1; sz < n; sz *= 2);
      mx.resize(2 * sz);
      mn.resize(2 * sz);
      l.resize(2 * sz);
      for(int i = sz; i < 2 * sz; i++) mx[i] = mn[i] = pii(0, i - sz);
      for(int i = sz - 1; i; i--) {
        mx[i] = mx[2 * i + 1];
        mn[i] = mn[2 * i];
      }
    }
    void add(int x, int v) {
      mx[x].x += v;
      mn[x].x += v;
      l[x] += v;
    }
    void u(int s, int e, int v, int x, int p, int q) {
      if(e < p || q < s) return;
      if(s <= p && q <= e) { add(x, v); return; }
      add(2 * x, l[x]);
      add(2 * x + 1, l[x]);
      l[x] = 0;
      u(s, e, v, 2 * x, p, (p + q) / 2);
      u(s, e, v, 2 * x + 1, (p + q) / 2 + 1, q);
      mx[x] = max(mx[2 * x], mx[2 * x + 1]);
      mn[x] = min(mn[2 * x], mn[2 * x + 1]);
    }
    void u(int s, int e, int v) { u(s, e, v, 1, 0, sz - 1); }
  } S(B);
  
  int ans = 0, ax, ay;
  for(int i = 0; i < A; i++) {
    for(auto [x, y, z] : uv[i]) S.u(x, y, z);
    pii t = (abs(S.mx[1].x) > abs(S.mn[1].x) ? S.mx[1] : S.mn[1]);
    if(abs(t.x) > ans) {
      ans = abs(t.x);
      ax = xs[i];
      ay = ys[t.y];
    }
  }
  cout << ans << '\n' << ax << ' ' << ay << '\n';
  return 0;
}