#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4, INF = 0x3f3f3f3f;
int deg[MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    deg[u]++;
    deg[v]++;
  }

  for (int i = 0; i < n; i++) {
    cout << "i = " << i << ", deg[i] = " << deg[i] << endl;
  }

  vector<pii> dv(n);
  for (int i = 0; i < n; i++) dv[i] = {deg[i], i};
  sort(dv.begin(), dv.end());

  int left = 0, right = n + 1;
  while (left < right) {
    int mid = (left + right) / 2;

    cout << "mid = " << mid << endl;

    queue<int> q;
    for (int i = mid - 1; i >= 0; i--) q.push(dv[i].first);

    int vslot = 2, vused = q.size();
    while (!q.empty()) {
      int u = q.front(); q.pop();
      vslot += (u - 2);
    }

    cout << "vused = " << vused << ", vslot = " << vslot << endl;

    if (vused + vslot > n) right = mid;
    else left = mid + 1;
  }

  if (left == 0) {
    cout << n << '\n' << n << ' ' << n - 1 << '\n';
    for (int i = 0; i < n - 1; i++) cout << i << ' ' << i + 1 << '\n';
    return;
  }

  queue<int> q, wait;
  wait.push(dv[left - 1].second);
  for (int i = left - 2; i >= 0; i--) q.push(dv[i].second);
  for (int i = left; i < n; i++) {
    int v = dv[i].second;
    deg[v] = INF;
    q.push(v);
  }

  vector<pii> edges;
  while (!q.empty()) {
    int v = q.front(); q.pop();

    int f = wait.front();
    edges.push_back({f, v});

    deg[f]--;
    deg[v]--;
    if (deg[f] == 0) wait.pop();
    if (deg[v] > 0) wait.push(v);
  }

  cout << n - left << '\n' << n << ' ' << n - 1 << '\n';
  for (auto& [u, v] : edges) cout << u << ' ' << v << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
