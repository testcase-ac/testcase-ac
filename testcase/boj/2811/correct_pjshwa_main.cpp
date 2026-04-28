#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];
bool gift[MAX];

void solve() {
  int n;
  cin >> n;

  bool sad = false;
  int streak = 0;
  vector<pii> periods;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    if (sad) {
      if (x >= 0) {
        periods.push_back({i - streak, streak});
        sad = false;
        streak = 0;
      }
      else streak++;
    }
    else {
      if (x < 0) {
        sad = true;
        streak = 1;
      }
    }
  }
  if (sad) periods.push_back({n - streak, streak});

  int mstreak = 0;
  for (auto [s, o] : periods) {
    mstreak = max(mstreak, o);
  }

  for (auto [s, o] : periods) {
    for (int i = s - 1; i >= 0 && i >= s - 2 * o; i--) gift[i] = true;
  }

  int mval = 0;
  for (auto [s, o] : periods) {
    if (o < mstreak) continue;

    int mcur = 0;
    for (int i = s - 3 * o; i < s - 2 * o; i++) {
      if (i < 0 || gift[i]) continue;
      mcur++;
    }
    mval = max(mval, mcur);
  }

  int ans = 0;
  for (int i = 0; i < n; i++) ans += gift[i];

  cout << ans + mval << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
