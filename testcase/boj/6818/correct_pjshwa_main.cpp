#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 30000, MAXM = 1000;
int N, M, B[MAXM + 5];
vector<tuple<int, int, int, int>> C;

void f(int i) {
  memset(B, 0, sizeof(B));
  for (auto& [x, y, r, b] : C) {
    if (abs(x - i) > r) continue;
    int h = abs(x - i);
    int w = sqrt(r * r - h * h);

    for (int j = max(0, y - w);; ++j) {
      int sq_d = (i - x) * (i - x) + (j - y) * (j - y);
      if (sq_d > r * r) continue;
      B[j] += b;
      break;
    }
    for (int j = min(M, y + w);; ++j) {
      int sq_d = (i - x) * (i - x) + (j - y) * (j - y);
      if (j <= M && sq_d <= r * r) continue;
      B[j] -= b;
      break;
    }
  }
  for (int j = 1; j <= M; ++j) B[j] += B[j - 1];
}

void solve() {
  int K; cin >> N >> M >> K;
  while (K--) {
    int x, y, r, b; cin >> y >> x >> r >> b;
    C.emplace_back(x, y, r, b);
  }

  int maxb = 0, maxc = 0;
  for (int i = 1; i <= N; ++i) {
    f(i);
    for (int j = 1; j <= M; ++j) maxb = max(maxb, B[j]);
  }
  cout << maxb << '\n';

  for (int i = 1; i <= N; ++i) {
    f(i);
    for (int j = 1; j <= M; ++j) maxc += (B[j] == maxb);
  }
  cout << maxc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
