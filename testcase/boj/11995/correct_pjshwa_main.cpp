#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

const int MAX = 2e3;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
bool vis[(MAX + 1) * (MAX + 1) + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int a, b, n, m, x;
  cin >> a >> b >> n >> m;
  vector<int> hf(n + 2), vf(m + 2);
  hf[0] = 0, hf[n + 1] = a;
  vf[0] = 0, vf[m + 1] = b;
  for (int i = 1; i <= n; i++) cin >> hf[i];
  for (int i = 1; i <= m; i++) cin >> vf[i];
  sort(hf.begin(), hf.end());
  sort(vf.begin(), vf.end());

  // Prim's algorithm
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, 0});

  ll ans = 0;
  while (!pq.empty()) {
    auto[wgt, vtx] = pq.top();
    pq.pop();

    if (vis[vtx]) continue;
    vis[vtx] = true;

    ans += wgt;
    int vi = vtx / (m + 1), vj = vtx % (m + 1);

    for (int i = 0; i < 4; i++) {
      int ni = vi + dx[i], nj = vj + dy[i];
      if (ni < 0 || ni > n || nj < 0 || nj > m) continue;
      if (vis[ni * (m + 1) + nj]) continue;
      int dl = nj == vj ? vf[vj + 1] - vf[vj] : hf[vi + 1] - hf[vi];
      pq.push({dl, ni * (m + 1) + nj});
    }
  }

  cout << ans << '\n';
}
