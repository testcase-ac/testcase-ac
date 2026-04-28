#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K;
  cin >> N >> K;

  int p[N];
  for (int i = 0; i < N; ++i) p[i] = i;

  int dis = 0x3f3f3f3f;
  do {
    if (p[0] != 0) continue;

    int l = p[0], f = 1;
    for (int i = 1; i < N; i++) {
      if (abs(l - p[i]) > K) f = 0;
      if (((l + 1) & (p[i] + 1)) == 0) f = 0;
      l = p[i];
    }
    if (abs(l - p[0]) > K) f = 0;
    if (((l + 1) & (p[0] + 1)) == 0) f = 0;
    if (!f) continue;

    int cur = 0;
    for (int i = 1; i < N; i++) cur += abs(p[i] - p[i - 1]);
    cur += abs(p[0] - p[N - 1]);
    dis = min(dis, cur);

  } while (next_permutation(p, p + N));

  cout << dis << '\n';
  do {

    if (p[0] != 0) continue;

    int l = p[0], f = 1;
    for (int i = 1; i < N; i++) {
      if (abs(l - p[i]) > K) f = 0;
      if (((l + 1) & (p[i] + 1)) == 0) f = 0;
      l = p[i];
    }
    if (abs(l - p[0]) > K) f = 0;
    if (((l + 1) & (p[0] + 1)) == 0) f = 0;
    if (!f) continue;

    int cur = 0;
    for (int i = 1; i < N; i++) cur += abs(p[i] - p[i - 1]);
    cur += abs(p[0] - p[N - 1]);

    if (cur == dis) {
      for (int i = 0; i < N; i++) cout << p[i] + 1 << ' ';
      cout << "1\n";
    }

  } while (next_permutation(p, p + N));

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
