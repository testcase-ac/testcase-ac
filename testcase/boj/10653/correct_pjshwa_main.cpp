#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 1e9 + 7;
pair<int, int> posts[MAX];
int d[MAX][MAX];

int manhattan_dist(pii p1, pii p2) {
  return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main() {
  fast_io();

  int n, K;
  cin >> n >> K;
  for (int i = 0; i < n; i++) cin >> posts[i].first >> posts[i].second;

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) d[i][j] = INF;
  for (int k = 0; k <= K; k++) d[0][k] = 0;

  for (int i = 1; i < n; i++) for (int k = 0; k <= K; k++) for (int j = 0; j <= K; j++) {
    if (k + j > K) continue;
    if (i - 1 - j < 0) continue;
    d[i][k + j] = min(d[i][k + j], d[i - 1 - j][k] + manhattan_dist(posts[i], posts[i - 1 - j]));
  }
  cout << *min_element(d[n - 1], d[n - 1] + K + 1);
}
