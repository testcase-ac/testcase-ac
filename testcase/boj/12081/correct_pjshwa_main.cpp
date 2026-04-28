#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXA = 2e6;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int A[MAXA + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";
  int S, R, C; cin >> S >> R >> C;

  memset(A, 0, sizeof(A)); int maxx = 0;
  for (int i = 0; i < S; ++i) {
    int x; string a; cin >> x >> a;
    if (a == "R") A[x] = 1;
    else A[x] = -1;
    maxx = max(maxx, x);
  }

  int dir = 0, ci = 0, cj = 0;
  deque<pii> dq;
  set<pii> loc, food;
  dq.push_back({0, 0}); loc.insert({0, 0});

  for (int x = 1; x <= maxx + R + C; ++x) {
    int ni = (ci + dx[dir] + R) % R, nj = (cj + dy[dir] + C) % C;
    if ((ni + nj) % 2 == 1 && !food.count({ni, nj})) food.insert({ni, nj});
    else {
      auto [li, lj] = dq.back(); dq.pop_back();
      loc.erase({li, lj});
    }
    dq.push_front({ni, nj});

    if (loc.count({ni, nj})) break;
    loc.insert({ni, nj});

    dir = (dir + 4 + A[x]) % 4;
    ci = ni, cj = nj;
  }

  cout << dq.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
