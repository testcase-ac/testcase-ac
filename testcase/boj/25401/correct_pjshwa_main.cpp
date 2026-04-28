#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 0x3f3f3f3f;
int ox[MAX], x[MAX], N;

void copy() {
  for (int i = 0; i < N; i++) x[i] = ox[i];
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> ox[i];

  int ans = INF;
  for (int s = 0; s < N; s++) for (int e = s + 1; e < N; e++) {
    int diff = ox[e] - ox[s];
    if (diff % (e - s)) continue;
    diff /= (e - s);

    copy();
    for (int j = s - 1; j >= 0; j--) x[j] = x[j + 1] - diff;
    for (int j = s + 1; j < N; j++) x[j] = x[j - 1] + diff;

    int cur = 0;
    for (int j = 0; j < N; j++) {
      if (x[j] != ox[j]) cur++;
    }

    ans = min(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
