#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

const int MAX = 50, INF = 0x3f3f3f3f;
const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX];
int A[MAX][MAX];
int N, Kc, pi, pj;

bool check(int minH, int maxH) {
  memset(vis, false, sizeof(vis));

  queue<pii> q;
  q.push({pi, pj});
  vis[pi][pj] = true;

  int cKc = 0;
  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();

    if (board[i][j] == 'K') cKc++;

    for (int k = 0; k < 8; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
      if (vis[ni][nj]) continue;
      if (A[ni][nj] < minH || A[ni][nj] > maxH) continue;

      vis[ni][nj] = true;
      q.push({ni, nj});
    }
  }

  return cKc == Kc;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> board[i];

  int L;
  vector<int> heights;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    cin >> A[i][j];
    if (board[i][j] == 'P') L = A[i][j], pi = i, pj = j;
    if (board[i][j] == 'K') Kc++;

    heights.push_back(A[i][j]);
  }

  compress(heights);
  int z = heights.size();

  int ans = INF;
  for (int i = 0; i < z; i++) {
    int H = heights[i];
    if (H > L) break;

    int left = i, right = z;
    while (left < right) {
      int mid = (left + right) / 2;
      if (heights[mid] >= L && check(H, heights[mid])) right = mid;
      else left = mid + 1;
    }
    if (left < z) ans = min(ans, heights[left] - H);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
