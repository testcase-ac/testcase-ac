#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

const int MAX = 1e5;
bool vis[MAX];
vector<pii> graph[MAX];
vector<pii> sortX, sortY, sortZ;

int main() {
  int n, a, b, c;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> a >> b >> c;
    sortX.push_back({a, i});
    sortY.push_back({b, i});
    sortZ.push_back({c, i});
  }
  sort(sortX.begin(), sortX.end());
  sort(sortY.begin(), sortY.end());
  sort(sortZ.begin(), sortZ.end());

  for (int i = 1; i < n; i++) {
    pii x1 = sortX[i - 1], y1 = sortX[i];
    pii x2 = sortY[i - 1], y2 = sortY[i];
    pii x3 = sortZ[i - 1], y3 = sortZ[i];
    graph[x1.second].push_back({abs(x1.first - y1.first), y1.second});
    graph[y1.second].push_back({abs(x1.first - y1.first), x1.second});
    graph[x2.second].push_back({abs(x2.first - y2.first), y2.second});
    graph[y2.second].push_back({abs(x2.first - y2.first), x2.second});
    graph[x3.second].push_back({abs(x3.first - y3.first), y3.second});
    graph[y3.second].push_back({abs(x3.first - y3.first), x3.second});
  }

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, 1});

  // Prim's algorithm
  ll ans = 0;
  int wgt, vtx, wgt_d, vtx_d;
  while (!pq.empty()) {
    tie(wgt, vtx) = pq.top();
    pq.pop();

    if (vis[vtx]) continue;
    vis[vtx] = true;
    ans += wgt;

    for (auto &x : graph[vtx]) {
      tie(wgt_d, vtx_d) = x;
      if (!vis[vtx_d]) pq.push({wgt_d, vtx_d});
    }
  }

  cout << ans;
}
